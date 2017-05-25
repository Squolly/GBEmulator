#include "GBTimer.hpp"
#include "Utility/ScopedTimer.hpp" 

#include <algorithm> 
#include <iostream>

GBTimer::GBTimer(uint32 start_address, uint32 end_address, 
    const std::string& name, 
    const std::string& description) : 
    MemoryMappedModule(name, description, start_address, end_address), 
    _verbose(false), 
    _divider_register(0), 
    _timer_counter(0),
    _timer_modulo(0),
    _timer_control(0), 
    _timer_stop(false),  
    _input_clock(0), 
    _timer_interrupt(false), 
    _current_cpu_cycles(0),  
    _last_cpu_cycles(0), 
    _timer_update_cycles(0), 
    _divider_update_cycles(0) 
    { }
    
void GBTimer::operate() { 
    const uint32 clock_speed_gb = 4194304; // 41943040.; // Hz
    const uint32 divider_cycles = clock_speed_gb / 16384; 
    const uint32 mode_0_cycles = clock_speed_gb / 4096; 
    const uint32 mode_1_cycles = clock_speed_gb / 262144; 
    const uint32 mode_2_cycles = clock_speed_gb / 65536; 
    const uint32 mode_3_cycles = clock_speed_gb / 16348; 
    
    while(_divider_update_cycles > divider_cycles) { // 16384 Hz
        _divider_register++; 
        _divider_update_cycles -= divider_cycles; 
		// std::cout << "Divider update: " << (int)_divider_register << std::endl; 
    }
    
    double cycles_needed = 0; 
    switch(_input_clock) {
        case 0: // 4096 Hz
            cycles_needed = mode_0_cycles; 
            break; 
            
        case 1: // 262144 Hz
            cycles_needed = mode_1_cycles; 
            break; 
            
        case 2: // 65536 Hz
            cycles_needed = mode_2_cycles; 
            break; 
            
        case 3: // 16348 Hz
            cycles_needed = mode_3_cycles; 
            break;
        
        default: 
            std::cout << "[Timer] Error! Unknown Timer Mode." << std::endl; 
            break; 
    }
    
    
    // if timer on
    if(_timer_stop) {
        // if(_verbose) std::cout << (int)_timer_update_cycles << " - " << cycles_needed << std::endl; 
        while(_timer_update_cycles > cycles_needed) {
            ScopedTimer st("Timer Increase"); 
            if(_verbose) std::cout << "Timer cycles needed: " << cycles_needed << std::endl; 
            _timer_counter++; 
            _timer_update_cycles -= (int)cycles_needed; 
            if(_verbose) std::cout << "up " << (int)_timer_update_cycles << " - " << cycles_needed << std::endl;
            if(_timer_counter == 0) {
                request_timer_interrupt(); 
                _timer_counter = _timer_modulo; 
				std::cout << "Timer interrupt." << std::endl; 
            }
        }
    }
}


uint8 GBTimer::read_8(uint16 address) {
    switch(address) {
        case 0xFF04: // DIV - Divider Register
            return _divider_register; 
            
        case 0xFF05: 
            return _timer_counter; 
            
        case 0xFF06: 
            return _timer_modulo; 
            
        case 0xFF07: 
            return _timer_control; 
    }
    
    std::cout << "[Timer] Error: unknown address (read)" << std::endl; 
	return 0xFF; 
}

void GBTimer::write_8(uint16 address, uint8 value) {
    switch(address) {
        case 0xFF04: // DIV - Divider Register
            _divider_register = 0; // writing resets this
            break; 
            
        case 0xFF05: 
            _timer_counter = value; 
            break; 
            
        case 0xFF06: 
            _timer_modulo = value; 
            break; 
            
        case 0xFF07:
            _timer_stop = value & 0x4;  // bit 2
            _input_clock = value & 0x3; // bits 0 & 1
            _timer_control = value; 
             if(_verbose) {
                 std::cout << "[Timer] Changed status (" << (_timer_stop ? "running" : "stopped") << ", Input Clock: " << (int)_input_clock << ")" << std::endl;  
            }
            break; 
            
        default:
            std::cout << "[Timer] Error: unknown address (write)" << std::endl; 
            break; 
    }
}