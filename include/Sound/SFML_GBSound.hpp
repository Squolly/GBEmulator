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
            initialize(1, 44100); 
        }
        
        virtual ~SFML_GBSound() { }
        
    virtual bool onGetData(Chunk& chunk)
    {
        // generate samples
        //std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch1 = ch1.synth.get_queue();
        // std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch2 = ch2.synth.get_queue();
        std::queue<std::array<int, Synth::BUFFER_SIZE> > data_ch3 = ch3.synth.get_queue();
        
        int minimum_data_size = std::min(data_ch3.size(), data_ch3.size()); 
        int num_samples = minimum_data_size * Synth::BUFFER_SIZE; 
        if(minimum_data_size) {
            _samples = std::vector<sf::Int16>(num_samples); 
            int idx=0; 
            sf::Int16 last_val = 0; 
            while(/* !data_ch1.empty() && !data_ch2.empty() && */!data_ch3.empty() ) {
                // std::array<int, Synth::BUFFER_SIZE>& arr_ch1 = data_ch1.front(); 
                // std::array<int, Synth::BUFFER_SIZE>& arr_ch2 = data_ch2.front(); 
                std::array<int, Synth::BUFFER_SIZE>& arr_ch3 = data_ch3.front(); 
                for(int i=0; i<arr_ch3.size(); ++i) {
                    sf::Int16 val = (/* arr_ch1[i] + arr_ch2[i] + */ arr_ch3[i]); 
                    // val = ((int)last_val + val) / 2; 
                    _samples[idx] = val;
                    // std::cout << (int)arr[i]; 
                    ++idx; 
                }
                // data_ch1.pop();
                // data_ch2.pop();
                data_ch3.pop(); 
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
