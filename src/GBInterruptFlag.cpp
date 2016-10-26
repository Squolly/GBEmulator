#include "GBInterruptFlag.hpp"

#include <algorithm> 
#include <iostream>

GBInterruptFlag::GBInterruptFlag(uint32 start_address, uint32 end_address, 
    const std::string& name, 
    const std::string& description) : 
    MemoryMappedModule(name, description, start_address, end_address), 
    _verbose(false)
    { }
    
void GBInterruptFlag::operate() { }

uint8 set_bit(uint8 reg, int bit, bool value) {
    uint8 mask = 1 << bit; 
    reg = reg & (~mask); 
    if(value) 
        reg |= (mask); 
    return reg; 
}

/*
 *    VBlank = 0, 
    LCDC   = 1, 
    Timer  = 2, 
    Serial_IO = 3, 
    Joystick = 4 
*/

void GBInterruptFlag::set_interrupt(Interrupt interrupt) {
    int bit = -1; 
    switch(interrupt) {
        case Interrupt::VBlank: 
            bit = 0; 
            break; 
            
        case Interrupt::LCDC: 
            bit = 1; 
            break; 

        case Interrupt::Timer: 
            bit = 2; 
            break; 
            
        case Interrupt::Serial_IO: 
            bit = 3; 
            break; 
            
        case Interrupt::Joystick: 
            bit = 4; 
            break; 
    }
    
    if(bit < 0) 
        return; 
    
    _interrupt_flags = set_bit(_interrupt_flags, bit, true); 
}

void GBInterruptFlag::clear_interrupt(Interrupt interrupt) {
    int bit = -1; 
    switch(interrupt) {
        case Interrupt::VBlank: 
            bit = 0; 
            break; 
            
        case Interrupt::LCDC: 
            bit = 1; 
            break; 

        case Interrupt::Timer: 
            bit = 2; 
            break; 
            
        case Interrupt::Serial_IO: 
            bit = 3; 
            break; 
            
        case Interrupt::Joystick: 
            bit = 4; 
            break; 
    }
    
    if(bit < 0) 
        return; 
    
    _interrupt_flags = set_bit(_interrupt_flags, bit, false); 
}

uint8 GBInterruptFlag::read_8(uint16 address) {
    if(address != _start_address) {
        std::cout << "invalid address: " << address << std::endl; 
        return 0xFF; 
    }
    
    return _interrupt_flags; 
}
void GBInterruptFlag::write_8(uint16 address, uint8 value) {
    if(address != _start_address) {
        std::cout << "invalid address: " << address << std::endl; 
        return; 
    }
    
    _interrupt_flags = value; 
    
    if(_verbose) {
        std::cout << describe_state() << std::endl; 
    }
}
        
std::string GBInterruptFlag::describe_state() {
    std::string desc; 
    const int ind = 4; 
    
    auto do_ind = [](int ind) { 
        std::string s; 
        s.insert(s.end(), ind, ' '); 
        return s; 
    }; 
    
    desc += "Interrupt Flags: \n"; 
    desc += do_ind(ind) + describe("VBlank    ", vblank_occurred()) + "\n"; 
    desc += do_ind(ind) + describe("LCDC      ", lcdc_occurred()) + "\n";
    desc += do_ind(ind) + describe("Timer     ", timer_occurred()) + "\n";
    desc += do_ind(ind) + describe("Serial I/O", serial_io_complete_occurred()) + "\n";
    desc += do_ind(ind) + describe("Joystick  ", joystick_occurred()) + "\n";
    return desc; 
}

std::string GBInterruptFlag::describe(const std::string name, bool is_enabled) {
    return name + ": " + (is_enabled ? "enabled" : "disabled"); 
}