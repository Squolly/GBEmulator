#ifndef SFML_GBSOUND_HPP__
#define SFML_GBSOUND_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"
#include "Sound/GBSound.hpp"
#include <SFML/Audio.hpp>
#include <atomic>
#include <thread>

#include <chrono>

class SFML_GBSound : public GBSound, public sf::SoundStream {
public: 
        std::array<sf::Int16, 1024> _block; 
        int _current_block_idx; 
        uint32 _last_cycle_counter; 
        uint32 _next_cycle_counter; 
        uint32 _nextDebug; 
        
        SFML_GBSound(const std::string& name = std::string("SFML Sound"), 
                const std::string& description = std::string("SFML Sound Module")) 
        : GBSound(name, description),
        _current_block_idx(0),
        _samples(Synth::BUFFER_SIZE, 0),
        _last_cycle_counter(0),
        _next_cycle_counter(0),
        _nextDebug(0),
        _quit_thread(true) {
            initialize(1, 22050); 
        }
        
        virtual ~SFML_GBSound() { }
    
    void start_sound_grabber() {
        _quit_thread = false; 
        // _sound_grabber_thread = std::make_shared<std::thread>(&SFML_GBSound::sound_grabber, this); 
    }
    
    void end_sound_grabber() {
        _quit_thread = true; 
       //  _sound_grabber_thread->join(); 
    }
    
    void sound_grabber(uint32 cycle_counter) {
        // get new data from channels
        
         if(cycle_counter > _nextDebug)  {
            std::lock_guard<std::mutex> lg(_prepared_samples_mutex); 
            // std::cout << "Prepared: " << _prepared_samples.size() << std::endl; 
            _nextDebug += 20000; 
         }
            
        if(cycle_counter < _next_cycle_counter) 
            return; 
        
        _next_cycle_counter += 196; 
        
        int channel1 = ch1.synth.get_current_output(); 
        int channel2 = ch2.synth.get_current_output(); 
        int channel3 = ch3.synth.get_current_output(); 
        
        int mix = channel1 + channel2 + channel3; 
        _block[_current_block_idx++] = mix; 
        
        bool sleep_a_bit = false; 
        if(_current_block_idx >= _block.size()) {
            std::lock_guard<std::mutex> lg(_prepared_samples_mutex); 
            
            for(int i=0; i<_block.size(); ++i)   {
                _prepared_samples.push_back(_block[i]); 
            }
            // std::cout << "Added new block." << std::endl; 
            if(_prepared_samples.size() > 1024 * 4) {
                sleep_a_bit = true; 
            }
            _current_block_idx = 0; 
        }
        
        if(sleep_a_bit) 
            std::this_thread::sleep_for(std::chrono::duration<double>(1./22050. * 1024 * 1.5));
    }
    
    virtual bool onGetData(Chunk& chunk) {
        bool filled = false; 
        while(!filled) {
            {
                std::lock_guard<std::mutex> lg(_prepared_samples_mutex);
                filled = !(_prepared_samples.size() < 1); 
            }
//             std::cout << "." << std::endl; 
            std::this_thread::sleep_for(std::chrono::duration<double>(1./22050. * 1024)); 
        }
        
        {
            std::lock_guard<std::mutex> lg(_prepared_samples_mutex);
            _samples = _prepared_samples; 
            _prepared_samples.clear(); 
        }
        chunk.samples = &_samples[0];
        chunk.sampleCount = _samples.size(); 
        return true; 
    }
    
    virtual bool onGetData2(Chunk& chunk)
    {
        sf::sleep(sf::milliseconds(1));
        
        // generate samples
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch1;
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch2;
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch3;
        int minimum_data_size = 0; 
        int num_samples = 0; 
            
        const int num_min_data = 2; 
        while(minimum_data_size < num_min_data) {
            sf::sleep(sf::milliseconds(1));
            if( ch1.synth.check_queue(num_min_data)  || ch2.synth.check_queue(num_min_data) ||  ch3.synth.check_queue(num_min_data)) {
                if(ch1.synth.get_size() >= num_min_data) data_ch1 = ch1.synth.get_queue();
                if(ch2.synth.get_size() >= num_min_data) data_ch2 = ch2.synth.get_queue();
                if(ch3.synth.get_size() >= num_min_data) data_ch3 = ch3.synth.get_queue();
                
                minimum_data_size = std::max(data_ch1.size(), data_ch2.size());
                minimum_data_size = std::max(minimum_data_size, (int)data_ch3.size());
                num_samples = minimum_data_size * Synth::BUFFER_SIZE;
            }
        }
        if(minimum_data_size) {
            _samples = std::vector<sf::Int16>(num_samples); 
            int idx=0; 
            sf::Int16 last_val = 0; 
            while( !data_ch1.empty() || !data_ch2.empty() || !data_ch3.empty() ) {
                std::array<int, Synth::BUFFER_SIZE>& arr_ch1 = data_ch1.front(); 
                std::array<int, Synth::BUFFER_SIZE>& arr_ch2 = data_ch2.front();
                std::array<int, Synth::BUFFER_SIZE>& arr_ch3 = data_ch3.front();
                // if(!data_ch1.empty()) arr_ch1 = data_ch1.front(); 
                // if(!data_ch2.empty()) arr_ch2 = data_ch2.front(); 
                // if(!data_ch3.empty()) arr_ch3 = data_ch3.front(); 
                for(int i=0; (!data_ch1.empty() && i<arr_ch1.size()) || (!data_ch2.empty() && i<arr_ch2.size()) || (!data_ch3.empty() && i<arr_ch3.size()); ++i) {
					sf::Int16 val = 0;//  ( arr_ch1[i] + arr_ch2[i]  +arr_ch3[i]);
					int chs = 0; 
                    int val32 = 0; 
                    if(!data_ch1.empty() && i<arr_ch1.size()) {val32 += arr_ch1[i]; chs++;} 
                    if(!data_ch2.empty() && i<arr_ch2.size()) {val32 += arr_ch2[i]; chs++;}
                    if(!data_ch3.empty() && i<arr_ch3.size()) {val32 += arr_ch3[i]; chs++;}
                    // val = ((int)last_val + val) / 2; 
                    val = val32;
                    // std::cout << val << std::endl; 
                    _samples[idx] = val;
                    // std::cout << (int)arr[i]; 
                    ++idx; 
                }
                 if(!data_ch1.empty()) data_ch1.pop();
                 if(!data_ch2.empty()) data_ch2.pop();
                 if(!data_ch3.empty()) data_ch3.pop(); 
            }
        }
        else {
            _samples = std::vector<sf::Int16>(Synth::BUFFER_SIZE, 0); 
            num_samples = Synth::BUFFER_SIZE; 
        }
        chunk.samples = &_samples[0];
        chunk.sampleCount = num_samples; 
        return true; 
    }
    
    virtual void onSeek(sf::Time timeOffset)
    {
    }
    
    std::vector<sf::Int16> _samples; 
    
    std::vector<sf::Int16> _prepared_samples; 
    std::mutex _prepared_samples_mutex; 
    
    std::shared_ptr<std::thread> _sound_grabber_thread; 
    std::atomic_bool _quit_thread; 
};

#endif
