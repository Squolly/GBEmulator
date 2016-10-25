#ifndef GBINTERRUPTFLAG_HPP__
#define GBINTERRUPTFLAG_HPP__

#include "MemoryMappedModule.hpp"

enum class Interrupt {
    VBlank = 0, 
    LCDC   = 1, 
    Timer  = 2, 
    Serial_IO = 3, 
    Joystick = 4
}; 

class GBInterruptFlag : public MemoryMappedModule {
public: 
        GBInterruptFlag(uint32 start_address, uint32 end_address, const std::string& name = std::string("Interrupt Flags"), 
                 const std::string& description = std::string("Interrupt Flags"));
        
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void write_8(uint16 address, uint8 value); 
        
        std::string describe_state(); // return string with current interrupt description
        std::string describe(const std::string name, bool occurred); 
        
        void set_interrupt(Interrupt interrupt); 
        void clear_interrupt(Interrupt interrupt); 
        
        bool vblank_occurred() { return _interrupt_flags & 0x1; }
        bool lcdc_occurred() { return _interrupt_flags & 0x2; }
        bool timer_occurred() { return _interrupt_flags & 0x4; }
        bool serial_io_complete_occurred() { return _interrupt_flags & 0x8; }
        bool joystick_occurred() { return _interrupt_flags & 0x10; }
        
        void set_verbose(bool verbose) { _verbose = verbose; }
        bool verbose() { return _verbose; }
private: 
        uint8 _interrupt_flags; 
        bool _verbose; 
};

#endif
