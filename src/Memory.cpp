#include "Memory.hpp"

#include <cassert> 
#include <iostream>
 
 Memory::Memory(int size) : _mmms(MEMORY_SIZE, static_cast<MemoryMappedModule*>(0)), _verbose(false) {
     
 }
 
 uint8 Memory::read_8(uint16 address) {
     if(_verbose) std::cout << "Reading (8 bit): " << address << " "; 
     if(_mmms[address] == NULL) {
         std::cout << "Not mapped. Skipping" << std::endl; 
         return 0; 
     }
     uint8 value = _mmms[address]->read_8(address); 
     if(_verbose) std::cout << " returning: " << (int)value << std::endl; 
     return value; 
 }
 
 uint16 Memory::read_16(uint16 address) {
     uint16 value = 0; 
     if(_verbose) std::cout << "Reading (16 bit): " << address << " "; 
     value = (read_8(address + 1) << 8) | read_8(address); 
     if(_verbose) std::cout << " returning: " << (int)value << std::endl; 
     return value; 
 }
 
 bool Memory::write_8(uint16 address, uint8 value) {
      if(_mmms[address] == NULL) {
         std::cout << "Not mapped. Skipping" << std::endl; 
         return 0; 
     }
     if(_verbose) std::cout << "Writing (8 bit)... " << address << " <- " << (int)value << std::endl; 
     _mmms[address]->write_8(address, value); 
 }
 
 bool Memory::write_16(uint16 address, uint16 value) {
     write_8(address, value & 0xFF); 
     write_8(address + 1, (value >> 8) & 0xFF); 
     if(_verbose) std::cout << "Writing (16 bit)... " << address << " <- " << (int)value << std::endl; 
 }
 
bool Memory::set_verbose(bool verbose) {
    _verbose = verbose; 
}

bool Memory::is_verbose() {
    return _verbose; 
}
    
 void Memory::connect(MemoryMappedModule* mmm) {
     assert(mmm != 0); 

     std::cout << std::hex; 
     std::cout << "["; 
     std::cout << (int)mmm->start_address() << " - "; 
     std::cout << (int)mmm->end_address(); 
     std::cout << "]: connecting " << mmm->name() << std::endl; 
     
     for(uint32 i = mmm->start_address(); i < mmm->end_address(); ++i) {
         _mmms[i] = mmm; 
     }
 }
 
// map module into memory to given address (IO Ports e.g.) 
void Memory::connect(MemoryMappedModule* mmm, uint16 address) {
     assert(mmm != 0); 
     
     std::cout << "[" << (int)address << "]: connecting " << mmm->name() << std::endl; 
     
     _mmms[address] = mmm; 
}
    
// map module into memory in given area (helpful for Modules with several memory areas like GPU)
void Memory::connect(MemoryMappedModule* mmm, uint16 start_address, uint16 end_address) {
     assert(mmm != 0); 
     
     std::cout << std::hex; 
     std::cout << "["; 
     std::cout << (int)start_address << " - "; 
     std::cout << (int)end_address; 
     std::cout << "]: connecting " << mmm->name() << std::endl; 
     
     for(uint32 i = start_address; i < end_address; ++i) {
         _mmms[i] = mmm; 
     }
}
