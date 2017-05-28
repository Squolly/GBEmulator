#ifndef SQUARE_WAVE_HPP__
#define SQUARE_WAVE_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"

#include "Sound/Synth.hpp"

#include <array>
#include <queue> 
#include <mutex>
#include <iostream>
#include <iomanip> 


class Memory; 

class SquareWave {
public: 
    Synth synth;
    
    SquareWave() : 
        _frequency_timer_period(0),  // depends on rate
        _modulation_period(8192),
        _volume(0), 
        _rate(0), 
        _sound_length(0), 
        _wave_duty(2), 
        _initial(false), 
        _counter(false), 
        _modulation_phase(-1), 
        _on(false), 
        _duty(false), 
        _current_buffer_time(0),  
        _current_buffer_delay(1)
        {

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
    
    void clock_volume() {
        if(!_on) 
            return; 
        
        if(!_volume_env_sweep) {// n = 0 -> stop
            return; 
        }
        _volume_env_sweep_ctr--; 
        if(_volume_env_sweep_ctr == 0) {
            _volume_env_sweep_ctr = _volume_env_sweep; 
            
            // do volume env
            if(_volume_env_increase && _volume < 15) {
                _volume++; 
            }
            
            if(!_volume_env_increase && _volume > 0) 
                _volume--; 
        }
    }
    
    virtual void clock_modulation() { 
        _modulation_phase = (_modulation_phase + 1) & 7; 
        
        if(!_on) 
            return; 
        
        switch(_modulation_phase) {
            case 2: 
            case 6: 
                // clock_sweep(); 

                // fall through
                
            case 0: 
            case 4: 
                clock_length(); 
                break; 
                
            case 7:
                clock_volume(); 
                break; 
        }
        
    } // make it possible to handle sweep and envelope
    
    void clock_wave() { // generate wave 
        if(!_on) {
            _wave_phase = (_wave_phase++) & 7; 
            return; 
        }
        
        static int const duty_offsets [4] = { 1, 1, 3, 7 };
        static int const duties       [4] = { 1, 2, 4, 6 };
        
        const int duty_select = 0; 
        int duty_offset = duty_offsets[duty_select]; 
        int duty = duties[duty_select]; 
        
        int ph = (_wave_phase + duty_offset) & 7; 
        
        ph = (ph + 1) & 7; 
        if(ph == 0 || ph == duty) {
            // hi and lo play
            _duty = !_duty; // toggle lo and hi
            // amp += delta; 
            // delta = -delta; 
        }
        // fill_buffer((_duty ? _volume : 0)); 
        
        _wave_phase = (ph - duty_offset) & 7; 
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
                synth.out(_duty ? _volume : 0); 
            }
            _frequency_timer_period += (2048 - _rate) * 4; 
            clock_wave(); 
            for(int i=0; i< -_frequency_timer_period; ++i) {
                synth.out(_duty ? _volume : 0); 
            }
        }
        else {
            for(int i=0; i< cycles; ++i) {
                synth.out(_duty ? _volume : 0); 
            }
        }
    }
    
    void set_rate(int new_rate) {
        _frequency_timer_period = (2048 - new_rate) * 4; 
        _rate = new_rate; 
        // we have 44100 Hz 
        // Frequency is 131072/(2048-x) Hz
        _current_buffer_delay = 44100 / ( 131072/(2048-new_rate) * 8) ; 
        // std::cout << "delay: " << std::dec << _current_buffer_delay << std::hex << std::endl; 
    }
    
    void set_initial_volume(int volume) {
        _volume = volume; 
    }
    
    void set_sound_length(int sound_length) {
        _sound_length = 64 - sound_length; 
    }
    
    void set_wave_duty(int wave_duty) {
        _wave_duty = wave_duty; 
    }
    
    void set_initial(bool initial) {
        _initial = initial; // restart
        if(!_initial) {
            _on = true; 
            _shadow_rate = _rate; 
        }
    }
    
    void set_counter(bool use_counter) {
        _counter = use_counter; 
    }
    
    void set_on(bool on) {
        _on = on; 
    }
    
    bool current_duty() {
        return _duty; 
    }
    
    int current_volume() {
        return _volume; 
    }
    
    // volume envelope
    void set_volume_env_increase(bool inc) { _volume_env_increase = inc; }
    void set_volume_env_initial(int initial_volume) { _volume_env_initial = initial_volume; }
    void set_volume_env_sweep(int sweeps) { if(!sweeps) sweeps = 8; _volume_env_sweep = sweeps; _volume_env_sweep_ctr = sweeps; }
    
protected: 
    
    int _modulation_period; 
    int _frequency_timer_period;
    int _current_buffer_time; 
    int _current_buffer_delay; 

    int  _volume; 
    int  _rate;
    int  _shadow_rate; 
    int  _sound_length; 
    int  _wave_duty; 
    bool _initial; 
    int  _modulation_phase; 
    bool _counter; 
    int  _wave_phase; 
    bool _on; 

    bool _volume_env_increase; 
    int _volume_env_initial; 
    int _volume_env_sweep; 
    int _volume_env_sweep_ctr; 
    
    bool _duty; 
    
};

#endif
