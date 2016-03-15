#include "GBRAM.hpp"

GBRAM::GBRAM(uint32 start_address, uint32 end_address, 
    const std::string& name /* = std::string("ROM Module") */, 
    const std::string& description /* = std::string("ROM - Read Only Memory") */) : 
    MemoryMappedModule(name, description, start_address, end_address) {
        
 }
    
void GBRAM::operate() { 
    // tick
}

uint8 GBRAM::read_8(uint16 address) { 
    return _data[address]; 
}

void GBRAM::write_8(uint16 address, uint8 value) { 
    _data[address] = value; 
} // won't write in ROM

void GBRAM::init(int size) {
    _data = std::vector<uint8>(size, 0); 
}