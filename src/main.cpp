#include <iostream>
#include <sstream>

#include "LR35902.hpp"
#include "GBROM.hpp" 

#include <fstream>

std::string show_bcd(uint8 v) {
    std::stringstream ss; 
    ss << (int)((v >> 4)&0xF) << (int)((v)&0xF); 
    return ss.str(); 
}

int main() {
    LR35902 cpu; 
    GBROM* rom = new GBROM(0x0000, 0x0100); 
    
    // fill rom with boot info
    std::fstream in("data/DMG_ROM.bin", std::ios::in | std::ios::binary);
    if(!in.is_open()) {
        std::cout << "Not able to find Boot ROM. Please change your path" << std::endl; 
        return 1; 
    }
    uint16 addr  = 0x0000; 
    std::cout << "reading" << std::endl; 
    while(!in.eof()) {
        uint8 value;
        in.get((char&)value); 
        rom->write_8(addr, value&0xFF); 
        addr++; 
    }
    std::cout << "Read " << addr << " bytes." << std::endl; 
    
    // now printing dissassembly
    cpu.disassemble(rom, 0x0000, 0x0100); 
    
    delete rom; 
    
}