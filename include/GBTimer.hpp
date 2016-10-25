#ifndef GBTIMER_HPP__
#define GBTIMER_HPP__

#include "MemoryMappedModule.hpp"

class GBTimer : public MemoryMappedModule {
public: 
        GBTimer(uint32 start_address, uint32 end_address, const std::string& name = std::string("Timer Module"), 
                 const std::string& description = std::string("Timer Module"));
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void write_8(uint16 address, uint8 value); 
        
        uint32 elapsed_cycles() { return _current_cpu_cycles - _last_cpu_cycles; }
        void update_cycles(uint32 current_cpu_cycles) { 
            _last_cpu_cycles = _current_cpu_cycles; 
            _current_cpu_cycles = current_cpu_cycles; 
            _timer_update_cycles += elapsed_cycles(); 
            _divider_update_cycles += elapsed_cycles();
        }
        
        void request_timer_interrupt() { _timer_interrupt = true; }
        bool timer_interrupt_request() { return _timer_interrupt; }
        void clear_timer_interrupt() { _timer_interrupt = false; }
        
        void set_verbose(bool verbose) { _verbose = verbose; }
        bool verbose() { return _verbose; }
private: 
        bool _verbose; 
        
        uint8 _divider_register; 
        uint8 _timer_counter; 
        uint8 _timer_modulo; 
        uint8 _timer_control; 
        
        bool _timer_stop; 
        uint8 _input_clock; 
        
        uint32 _current_cpu_cycles; 
        uint32 _last_cpu_cycles; 
        uint32 _timer_update_cycles; 
        uint32 _divider_update_cycles; 
        
        bool _timer_interrupt; 
};

#endif
