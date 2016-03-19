#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "types.hpp"
#include "MemoryMappedModule.hpp"

#include <vector>

const int MEMORY_SIZE = 65536; 

class Memory {
public: 
    Memory(int size = MEMORY_SIZE); 
    
    // read calls to memory mapped modules
    uint8  read_8(uint16 address); 
    uint16 read_16(uint16 address); // (endianess!)
    
    // write calls to memory mapped modules 
    bool write_8(uint16 address, uint8 value); 
    bool write_16(uint16 address, uint16 value); // (think of endianess!)
    bool set_verbose(bool verbose); 
    bool is_verbose(); 
    
    // map module into memory (using addresses stored in MemoryMappedModule) 
    void connect(MemoryMappedModule* mmm); 
    
    // map module into memory to given address (IO Ports e.g.) 
    void connect(MemoryMappedModule* mmm, uint16 address); 
    
    // map module into memory in given area (helpful for Modules with several memory areas like GPU)
    void connect(MemoryMappedModule* mmm, uint16 start_address, uint16 end_address); 
    
private: 
    std::vector<MemoryMappedModule*> _mmms; 
    std::vector<uint8> _data; // TODO: remove this and only provide access to connected modules 
    bool _verbose; 
}; 

#endif