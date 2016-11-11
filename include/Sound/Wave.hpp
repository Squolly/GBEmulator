#ifndef WAVE_HPP__
#define WAVE_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"

#include "Sound/Synth.hpp"

#include <array>
#include <queue> 
#include <mutex>
#include <iostream>
#include <iomanip> 


class Memory; 

class Wave {
public: 
    Synth synth;
    
    Wave() : 
        _frequency_timer_period(0),  // depends on rate
        _modulation_period(8192),
        _rate(0), 
        _sound_length(0), 
        _initial(false), 
        _counter(false), 
        _modulation_phase(-1), 
        _on(false), 
        _output_level(0), 
        _current_pos(0),
        _wave_ram(0xFF30, 0xFF3F)
    { 
        _wave_ram.init(_wave_ram.size()); 
    }
    
    void clock_length() {
        if(_sound_length > 0 && _counter) {
            _sound_length--; 
            std::cout << "Counter: "  << _sound_length << std::endl; 
            if(_sound_length == 0) { // Off
                _on = false; 
            }
        }
        else if(_sound_length == 0 && _counter) {
            _on = false; 
        }
        else if(!_counter) {
            _on = true; 
        }
    }
    
    virtual void clock_modulation() { 
        _modulation_phase = (_modulation_phase + 1) & 7; 
        
        if(!_on) 
            return; 
        
        switch(_modulation_phase) {
            case 2: 
            case 6: 
                // fall through
                
            case 0: 
            case 4: 
                clock_length(); 
                break; 
                
            case 7:
                break; 
        }
        
    } // make it possible to handle sweep and envelope
    
    void clock_wave() { // generate wave 
        if(!_on) {
            return; 
        }
        uint8 data = _wave_ram.read_8(0xFF30 + (_current_pos >> 1)); 
        int volume = ((_current_pos & 1) ? (data & 0xF) : ((data >> 4) & 0xF)); 
        // std::cout << volume << std::endl; 
        if(_output_level == 0) 
            volume = 0; 
        else {
            // _volume = (volume >> (_output_level - 1));
            _volume = volume * 2; 
        }
        
        _current_pos++; 
        if(_current_pos >= 32)
            _current_pos -= 32; 
    }
    
    void tick(int cycles) {
        // check timer 
        _modulation_period -= cycles; 
        if(_modulation_period <= 0) {
            _modulation_period = 8192; 
            clock_modulation(); 
        }
        
        _frequency_timer_period -= cycles; 
        if(_frequency_timer_period <= 0) {
            for(int i=0; i< _frequency_timer_period + cycles; ++i) {
                synth.out(_volume); 
            }
            _frequency_timer_period += (2048 - _rate) * 2; 
            clock_wave(); 
            for(int i=0; i< -_frequency_timer_period; ++i) {
                synth.out(_volume); 
            }
        }
        else {
            for(int i=0; i< cycles; ++i) {
                synth.out(_volume); 
            }
        }
    }
    
    void set_rate(int new_rate) {
        _frequency_timer_period = (2048 - new_rate) * 2; 
        _rate = new_rate; 
    }
    
    void set_initial_volume(int volume) {
        _volume = volume; 
    }
    
    void set_sound_length(int sound_length) {
        _sound_length = 256 - sound_length; 
    }
    
    
    void set_initial(bool initial) {
        _initial = initial; // restart
        if(!_initial) {
            _on = true; 
        }
    }
    
    void set_counter(bool use_counter) {
        _counter = use_counter; 
    }
    
    void set_on(bool on) {
        _on = on; 
    }
    
    int current_volume() {
        return _volume; 
    }
    
    void set_output_level(int level) { _output_level = level; }
    
    GBRAM& wave_ram() { return _wave_ram; }
    
protected: 
    
    int _modulation_period; 
    int _frequency_timer_period;

    int  _volume; 
    int  _rate;
    int  _sound_length; 
    bool _initial; 
    int  _modulation_phase; 
    bool _counter; 
    int  _wave_phase; 
    bool _on; 
    
    int _output_level; 
    int _current_pos; 
    GBRAM _wave_ram; 
    
};

#endif
