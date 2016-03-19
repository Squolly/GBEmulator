#include "Memory.hpp"

#include <cassert> 
#include <iostream>
 
 Memory::Memory(int size) : _mmms(MEMORY_SIZE, static_cast<MemoryMappedModule*>(0)) {
     
 }
 
 uint8 Memory::read_8(uint16 address) {
     std::cout << "Reading (8 bit): " << address << " "; 
     if(_mmms[address] == NULL) {
         std::cout << "Not mapped. Skipping" << std::endl; 
         return 0; 
     }
     uint8 value = _mmms[address]->read_8(address); 
     std::cout << " returning: " << (int)value << std::endl; 
     return value; 
 }
 
 uint16 Memory::read_16(uint16 address) {
     uint16 value = 0; 
     std::cout << "Reading (16 bit): " << address << " "; 
     value = (read_8(address + 1) << 8) | read_8(address); 
     std::cout << " returning: " << (int)value << std::endl; 
     return value; 
 }
 
 bool Memory::write_8(uint16 address, uint8 value) {
      if(_mmms[address] == NULL) {
         std::cout << "Not mapped. Skipping" << std::endl; 
         return 0; 
     }
     std::cout << "Writing (8 bit)... " << address << " <- " << (int)value << std::endl; 
     _mmms[address]->write_8(address, value); 
 }
 
 bool Memory::write_16(uint16 address, uint16 value) {
     write_8(address, value & 0xFF); 
     write_8(address + 1, (value >> 8) & 0xFF); 
     std::cout << "Writing (16 bit)... " << address << " <- " << (int)value << std::endl; 
 }
 
 void Memory::connect(MemoryMappedModule* mmm) {
     assert(mmm != 0); 

     for(uint32 i = mmm->start_address(); i < mmm->end_address(); ++i) {
         _mmms[i] = mmm; 
     }
 }
 
// map module into memory to given address (IO Ports e.g.) 
void Memory::connect(MemoryMappedModule* mmm, uint16 address) {
     assert(mmm != 0); 
     
     _mmms[address] = mmm; 
}
    
// map module into memory in given area (helpful for Modules with several memory areas like GPU)
void Memory::connect(MemoryMappedModule* mmm, uint16 start_address, uint16 end_address) {
     assert(mmm != 0); 

     for(uint32 i = start_address; i < end_address; ++i) {
         _mmms[i] = mmm; 
     }
}
