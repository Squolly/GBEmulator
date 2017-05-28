#ifndef SFML_GBSOUND_HPP__
#define SFML_GBSOUND_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"
#include "Sound/GBSound.hpp"
#include <SFML/Audio.hpp>

class SFML_GBSound : public GBSound, public sf::SoundStream {
public: 
        SFML_GBSound(const std::string& name = std::string("SFML Sound"), 
                const std::string& description = std::string("SFML Sound Module")) 
        : GBSound(name, description), 
        _samples(Synth::BUFFER_SIZE, 0) {
            initialize(1, 44100 / 2); 
        }
        
        virtual ~SFML_GBSound() { }
        
    virtual bool onGetData(Chunk& chunk)
    {
        sf::sleep(sf::milliseconds(1));
        
        // generate samples
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch1;
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch2;
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch3;
        int minimum_data_size = 0; 
        int num_samples = 0; 
            
        const int num_min_data = 8; 
        while(minimum_data_size < num_min_data) {
            sf::sleep(sf::milliseconds(1));
            if(ch1.synth.check_queue(num_min_data) || ch2.synth.check_queue(num_min_data) || ch3.synth.check_queue(num_min_data)) {
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
};

#endif
