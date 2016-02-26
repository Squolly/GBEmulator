#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "types.hpp"

#include <vector>

struct Memory {
    std::vector<uint8> data; 
    
    Memory(const int size); 
    uint8  read_u8(const uint16 address); 
    uint16 read_u16(const uint16 address);
    bool   write_u8(const uint16 address, const uint8 value); 
    bool   write_u16(const uint16 address, const uint16 value); 
}; 

#endif