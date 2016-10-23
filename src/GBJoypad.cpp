#include "GBJoypad.hpp"

#include <cassert>

#include <iostream>

GBJoypad::GBJoypad(uint32 start_address, uint32 end_address, 
                 const std::string& name /* = std::string("Gameboy Joypad Module") */, 
                 const std::string& description /* = std::string("A simple gameboy joypad module") */) : 
                 MemoryMappedModule(name, description, start_address, end_address), 
                 _button_start(false), _button_select(false), 
                 _button_up(false), _button_down(false), _button_left(false), _button_right(false), 
                 _button_a(false), _button_b(false), 
                 _chosen_bit(0) {
}

void GBJoypad::operate() {
    // nothing to do currently
}

uint8 GBJoypad::read_8(uint16 address) {
    // do not care about address, joypad is mapped to 0xFF00 only in GB
    uint8 value = 0; 
    
    if(_chosen_bit == 5) {
        value = value | 0xE0; 
        if(!_button_down)
            value = value | 0x08; // 0000 1000 
        if(!_button_up) 
            value = value | 0x04; // 0000 0100
        if(!_button_left) 
            value = value | 0x02; // 0000 0010
        if(!_button_right)
            value = value | 0x01; // 0000 0001 
    }
    else if(_chosen_bit == 4) {
        value = value | 0xD0; 
        if(!_button_start)
            value = value | 0x08; // 0000 1000 
        if(!_button_select) 
            value = value | 0x04; // 0000 0100
        if(!_button_b) 
            value = value | 0x02; // 0000 0010
        if(!_button_a)
            value = value | 0x01; // 0000 0001 
    }
       
   // std::cout << "Returning joypad value: " << (int)value << std::endl; 
   return value; 
}

// TODO: currently wrong implementation
// first: write 0 in bit 4 or bit 5, this chooses the lines to pick values from when read
void GBJoypad::write_8(uint16 address, uint8 value) {
    if(address != 0xFF00) 
        assert(0); 
    // std::cout << "Access to joypad: " << (int)value << std::endl; 
    if(value & 0x20) {
        _chosen_bit = 5; 
        // std::cout << "Chosen: " << (int)_chosen_bit << std::endl; 
    }
    if(value & 0x10)  {
        _chosen_bit = 4; 
        // std::cout << "Chosen: " << (int)_chosen_bit << std::endl; 
    }
}

void GBJoypad::start(bool pressed /* = false */) {
    _button_start = pressed; 
}

void GBJoypad::select(bool pressed /* = false */) {
    _button_select = pressed; 
}

void GBJoypad::up(bool pressed /* = false */) {
    _button_up = pressed; 
}

void GBJoypad::down(bool pressed /* = false */) {
    _button_down = pressed; 
}

void GBJoypad::left(bool pressed /* = false */) {
    _button_left = pressed; 
}

void GBJoypad::right(bool pressed /* = false */) {
    _button_right = pressed; 
}

void GBJoypad::a(bool pressed /* = false */) {
    _button_a = pressed; 
}

void GBJoypad::b(bool pressed /* = false */) {
    _button_b = pressed; 
}