#include "Memory.hpp"

#include <cassert> 
#include <iostream>
#include <iomanip> 
#include <fstream>

#include "Utility/ScopedTimer.hpp"

#include "Cartridge/GBMBC1.hpp" 

 Memory::Memory(int size) : _mmms(MEMORY_SIZE, nullptr), _verbose(false) {
     
 }
 
 uint8 Memory::read_8(uint16 address) {
     ScopedTimer st("Memory::read_8"); 
     
     if(_verbose) std::cout << "[Memory]: Reading (8 bit): " << address << " "; 
     if(_mmms[address] == nullptr) {
         std::cout << "[Memory]: Not mapped. Skipping (Read of address " << (int)address << ")" << std::endl; 
         return 0; 
     }
     
     //if(address >= 0x0000 && address < 0x8000 && !_boot) {
     //    return reinterpret_cast<GBMBC1*>(_mmms[address])->read_8(address); 
     //}
     
     uint8 value = _mmms[address]->read_8(address); 
     if(_verbose) std::cout << "[Memory]:     returning: " << (int)value << std::endl; 
     return value; 
 }
 
 uint16 Memory::read_16(uint16 address) {
     ScopedTimer st("Memory::read_16"); 
     
     uint16 value = 0; 
     if(_verbose) std::cout << "[Memory]: Reading (16 bit): " << address << " "; 
     value = (read_8(address + 1) << 8) | read_8(address); 
     if(_verbose) std::cout << "[Memory]:     returning: " << (int)value << std::endl; 
     return value; 
 }
 
 bool Memory::write_8(uint16 address, uint8 value) {
     ScopedTimer st("Memory::write_8"); 

      if(_mmms[address] == nullptr) {
         std::cout << "[Memory]: Not mapped. Skipping. (Write to " << (int)address << ")" << std::endl; 
         return 0; 
     }
     
    //if(address >= 0x0000 && address < 0x8000 && !_boot) {
    //     reinterpret_cast<GBMBC1*>(_mmms[address])->write_8(address, value); 
    //     return true; 
    // }

     if(_verbose) std::cout << "[Memory]: Writing (8 bit)... " << address << " <- " << (int)value << std::endl; 
     _mmms[address]->write_8(address, value); 
     return true; 
 }
 
 bool Memory::write_16(uint16 address, uint16 value) {
     ScopedTimer st("Memory::write_16"); 
     
     write_8(address, value & 0xFF); 
     write_8(address + 1, (value >> 8) & 0xFF); 
     if(_verbose) std::cout << "[Memory]: Writing (16 bit)... " << address << " <- " << (int)value << std::endl; 
     return true; 
 }
 
bool Memory::set_verbose(bool verbose) {
    _verbose = verbose; 
	return true; 
}

bool Memory::is_verbose() {
    return _verbose; 
}
    
 void Memory::connect(MemoryMappedModule* mmm) {
     // ScopedTimer st("Memory::connect(MMM)"); 
     assert(mmm != 0); 

     std::cout << std::hex; 
     std::cout << "[Memory]: ["; 
     std::cout << (int)mmm->start_address() << " - "; 
     std::cout << (int)mmm->end_address(); 
     std::cout << "]: connecting " << mmm->name() << std::endl; 
     
     for(uint32 i = mmm->start_address(); i < mmm->end_address(); ++i) {
         _mmms[i] = mmm; 
     }
 }
 
// map module into memory to given address (IO Ports e.g.) 
void Memory::connect(MemoryMappedModule* mmm, uint16 address) {
    // ScopedTimer st("Memory::connect(MMM_U16)"); 
    
     assert(mmm != 0); 
     
     std::cout << "[Memory]: [" << (int)address << "]: connecting " << mmm->name() << std::endl; 
     
     _mmms[address] = mmm; 
}
    
// map module into memory in given area (helpful for Modules with several memory areas like GPU)
void Memory::connect(MemoryMappedModule* mmm, uint16 start_address, uint16 end_address) {
    // ScopedTimer st("Memory::connect(MMM_U16_U16)"); 
     assert(mmm != 0); 
     
     std::cout << std::hex; 
     std::cout << "[Memory]: ["; 
     std::cout << (int)start_address << " - "; 
     std::cout << (int)end_address; 
     std::cout << "]: connecting " << mmm->name() << std::endl; 
     
     for(uint32 i = start_address; i < end_address; ++i) {
         _mmms[i] = mmm; 
     }
}

void Memory::dump() {
    std::ofstream out ("dump.txt"); 
    
    for(int i=0; i<65535; ++i) {
        if(i % 32 == 0) {
            out << std::endl; 
            out << std::hex << std::setw(10) << std::setfill(' ') << i <<": "; 
        }
        out << std::hex << std::setw(2) << std::setfill('0') << (int)read_8(i) << " "; 
    }
}
