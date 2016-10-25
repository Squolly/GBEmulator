#ifndef __GBINTERRUPTENABLE_HPP__
#define __GBINTERRUPTENABLE_HPP__

#include "MemoryMappedModule.hpp"

class GBInterruptEnable : public MemoryMappedModule {
public: 
        GBInterruptEnable(uint32 start_address, uint32 end_address, const std::string& name = std::string("Interrupt Enable Register"), 
                 const std::string& description = std::string("Interrupt Enable Register for Masking Interrupts"));
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void write_8(uint16 address, uint8 value); 
        
        std::string describe_state(); // return string with current mask description
        std::string describe(const std::string name, bool is_enabled); 
        
        bool vblank_enabled() { return interrupt_enable_register & 0x1; }
        bool lcdc_enabled() { return interrupt_enable_register & 0x2; }
        bool timer_overflow_enabled() { return interrupt_enable_register & 0x4; }
        bool serial_io_complete_enabled() { return interrupt_enable_register & 0x8; }
        bool joystick_enabled() { return interrupt_enable_register & 0x10; }
        
        void set_verbose(bool verbose) { _verbose = verbose; }
        bool verbose() { return _verbose; }
private: 
        uint8 interrupt_enable_register; 
        bool _verbose; 
};

#endif
