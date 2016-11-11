#ifndef SWEEP_SQUARE_WAVE_HPP__
#define SWEEP_SQUARE_WAVE_HPP__

#include "MemoryMappedModule.hpp"
#include "GBRAM.hpp"

#include "Sound/SquareWave.hpp"
#include "Sound/Synth.hpp"

#include <array>
#include <queue> 
#include <mutex>
#include <iostream>
#include <iomanip> 
#include <algorithm>


class Memory; 

class SweepSquareWave : public SquareWave {
public: 
    // Synth synth;
    
    SweepSquareWave() : SquareWave(), 
        _sweep_time(0), 
        _sweep_time_ctr(0), 
        _sweep_increase(false), 
        _sweep_shift(0)
        {

        }
    
    void clock_sweep() {
        std::cout << "Sweep: " << _on << " - " << _sweep_time << std::endl; 
        if(!_on || _sweep_time == 0) {
            return; 
        }
        
        std::cout << "Sweeping!" << std::endl; 
        
        _sweep_time_ctr--; 
        if(_sweep_time_ctr <= 0) {
            _sweep_time_ctr += _sweep_time; 
            
            // X(t) = X(t-1) +/- X(t-1)/2^n
            int new_rate; 
            if(_sweep_increase) {
                new_rate = _rate + _rate / std::pow(2, _sweep_shift); 
            }
            else {
                new_rate = _rate - _rate / std::pow(2, _sweep_shift); 
            }
            std::cout << "new rate: " << new_rate << std::endl; 
            if(new_rate < 0)  {
                new_rate = 0; 
                _sweep_time = 0; 
            }
            if(new_rate > 2047) {
                new_rate = 2047; 
                _sweep_time = 0; 
            }
            set_rate(new_rate); 
        }
        
    }
    
    virtual void clock_modulation() { 
        _modulation_phase = (_modulation_phase + 1) & 7; 
        
        if(!_on) 
            return; 
        
        switch(_modulation_phase) {
            case 2: 
            case 6: 
               clock_sweep(); 

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
    
    void set_sweep_time(int time) { if(!time) time = 8; _sweep_time = time; _sweep_time_ctr = time; }
    void set_sweep_increase(bool inc) { _sweep_increase = inc; }
    void set_sweep_shift(int shift) { _sweep_shift = shift; }
    
protected: 
    int _sweep_time; 
    int _sweep_time_ctr; 
    bool _sweep_increase; 
    int _sweep_shift; 
/* 
  Bit 6-4 - Sweep Time
  Bit 3   - Sweep Increase/Decrease
             0: Addition    (frequency increases)
             1: Subtraction (frequency decreases)
  Bit 2-0 - Number of sweep shift (n: 0-7)
  */
};

#endif
