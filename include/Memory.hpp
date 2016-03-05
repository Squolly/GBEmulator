#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "types.hpp"
#include "MemoryMappedModule.hpp"

#include <vector>

const int MEMORY_SIZE = 65536; 

struct Memory {
    std::vector<uint8> data; // TODO: remove this and only provide access to connected modules 
    
    Memory(int size = MEMORY_SIZE); 
    
    // read calls to memory mapped modules
    uint8  read_u8(const uint16 address); 
    uint16 read_u16(const uint16 address); // (endianess!)
    
    // write calls to memory mapped modules 
    bool   write_u8(const uint16 address, const uint8 value); 
    bool   write_u16(const uint16 address, const uint16 value); // (think of endianess!)
    
    void connect(MemoryMappedModule* mmm); 
}; 

#endif