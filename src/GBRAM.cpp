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
    uint16 relative = relative_address(address); 
    // hack for memory echo of 8k 0xE000 area
    if(_start_address == 0xC000 && relative >= 0xE000-0xC000)
        relative -= (0xE000 - 0xC000); 
    return _data[relative]; 
}

void GBRAM::write_8(uint16 address, uint8 value) { 
    uint16 relative = relative_address(address); 
    // hack for memory echo of 8k 0xE000 area
    if(_start_address == 0xC000 && relative >= 0xE000-0xC000)
        relative -= (0xE000 - 0xC000); 
    _data[relative] = value; 
} // won't write in ROM

void GBRAM::init(int size) {
    _data = std::vector<uint8>(size, 0); 
}