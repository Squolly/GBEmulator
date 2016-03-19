#include <iostream>
#include <sstream>

#include "LR35902.hpp"
#include "GBROM.hpp" 
#include "GBCartridge.hpp"
#include "GBVideo.hpp"

#include <fstream>
#include <cstdlib> 

std::string show_bcd(uint8 v) {
    std::stringstream ss; 
    ss << (int)((v >> 4)&0xF) << (int)((v)&0xF); 
    return ss.str(); 
}

int main() {
    LR35902 cpu; 
    GBROM  rom(0x0000, 0x0100);             rom.init(rom.size()); 
    GBRAM  zero_page_ram(0xFF80, 0xFFFF);   zero_page_ram.init(zero_page_ram.size()); 
    GBRAM  sprite_ram(0xFE00, 0xFFA0);      sprite_ram.init(sprite_ram.size()); 
    GBRAM  internal_ram(0xC000, 0xE000);    internal_ram.init(internal_ram.size()); 
    GBRAM  switchable_ram(0xA000, 0xC000);   switchable_ram.init(switchable_ram.size());  
 
    GBVideo video(0x8000, 0xA000); 
    video.init(); 
    video.connect_to_memory(cpu.memory); 
    cpu.memory.connect(&zero_page_ram); 
    cpu.memory.connect(&sprite_ram); 
    cpu.memory.connect(&internal_ram); 
    cpu.memory.connect(&switchable_ram); 

    
    // fill rom with boot info
    std::fstream in("data/DMG_ROM.bin", std::ios::in | std::ios::binary);
    if(!in.is_open()) {
        std::cout << "Not able to find Boot ROM. Please change your path" << std::endl; 
        return 1; 
    }
    uint16 addr  = 0x0000; 
    std::cout << "reading" << std::endl; 
    std::vector<uint8> data; 
    while(!in.eof()) {
        uint8 value;
        in.get((char&)value); 
        rom.write_8_rom(addr, value&0xFF); 
        addr++; 
    }
    std::cout << "Read " << addr << " bytes." << std::endl; 

    // read cartridge
    GBCartridge gbc(0x0000, 0x8000); 
    gbc.read_file("data/Bounce.gb"); 
    cpu.memory.connect(&gbc); 
    // map cartridge to memory
    // now printing dissassembly // rom will overwrite gbc entries
    cpu.memory.connect(&rom); 
    cpu.disassemble(); 
    cpu.init(); 
    
    /* 
    int a  = 0; 
    bool once = false; 
    for(int i=0; i<100000000; ++i) {
        cpu.single_step();  

        // system("sleep 0.0001");
        if(cpu.registers.PC == 0x55)
            once = true; 
        if(once)
            std::cin >> a; 
    }
    */
}