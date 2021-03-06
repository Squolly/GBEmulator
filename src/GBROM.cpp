#include "GBROM.hpp"

#include <iostream>

GBROM::GBROM(uint32 start_address, uint32 end_address, 
    const std::string& name /* = std::string("ROM Module") */, 
    const std::string& description /* = std::string("ROM - Read Only Memory") */) : 
    MemoryMappedModule(name, description, start_address, end_address) {
        
 }
    
void GBROM::operate() { 
    // tick
}

uint8 GBROM::read_8(uint16 address) { 
    const uint16 relative = relative_address(address); 
    return _data[relative]; 
}

void GBROM::write_8(uint16 address, uint8 value) { 
    // _data[address] = value; 
} // won't write in ROM

void GBROM::init(int size) {
    _data = std::vector<uint8>(size, 0); 
}

void GBROM::write_8_rom(uint16 address, uint8 value) {
    const uint16 relative = relative_address(address); 
    // std::cout << "Relative: " << relative << std::endl; 
    _data.at(relative) = value; 
}