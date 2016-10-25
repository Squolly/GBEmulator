#include "GBInterruptEnable.hpp"

#include <algorithm> 
#include <iostream>

GBInterruptEnable::GBInterruptEnable(uint32 start_address, uint32 end_address, 
    const std::string& name, 
    const std::string& description) : 
    MemoryMappedModule(name, description, start_address, end_address), 
    interrupt_enable_register(0), 
    _verbose(false)
    { }
    
void GBInterruptEnable::operate() { }
uint8 GBInterruptEnable::read_8(uint16 address) {
    if(address != _start_address) {
        std::cout << "invalid address: " << address << std::endl; 
        return 0xFF; 
    }
    
    return interrupt_enable_register; 
}
void GBInterruptEnable::write_8(uint16 address, uint8 value) {
    if(address != _start_address) {
        std::cout << "invalid address: " << address << std::endl; 
        return; 
    }
    
    interrupt_enable_register = value; 
    
    if(_verbose) {
        std::cout << describe_state() << std::endl; 
    }
}
        
std::string GBInterruptEnable::describe_state() {
    std::string desc; 
    const int ind = 4; 
    
    auto do_ind = [](int ind) { 
        std::string s; 
        s.insert(s.end(), ind, ' '); 
        return s; 
    }; 
    
    desc += "Interrupt Enable Flags: \n"; 
    desc += do_ind(ind) + describe("VBlank    ", vblank_enabled()) + "\n"; 
    desc += do_ind(ind) + describe("LCDC      ", lcdc_enabled()) + "\n";
    desc += do_ind(ind) + describe("Timer     ", timer_overflow_enabled()) + "\n";
    desc += do_ind(ind) + describe("Serial I/O", serial_io_complete_enabled()) + "\n";
    desc += do_ind(ind) + describe("Joystick  ", joystick_enabled()) + "\n";
    return desc; 
}

std::string GBInterruptEnable::describe(const std::string name, bool is_enabled) {
    return name + ": " + (is_enabled ? "enabled" : "disabled"); 
}