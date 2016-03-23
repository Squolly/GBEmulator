#include <iostream>
#include <sstream>

#include "LR35902.hpp"
#include "GBROM.hpp" 
#include "GBCartridge.hpp"
#include "GBJoypad.hpp"
#include "SFML_GBVideo.hpp"

#include "Instruction.hpp"

#include <fstream>
#include <cstdlib> 
#include <limits>


std::string show_bcd(uint8 v) {
    std::stringstream ss; 
    ss << (int)((v >> 4)&0xF) << (int)((v)&0xF); 
    return ss.str(); 
}

int main() {
    LR35902 cpu; 
    GBROM  rom(0x0000, 0x0100);             rom.init(rom.size()); 
    GBRAM  zero_page_ram(0xFF80, 0xFFFF);   zero_page_ram.init(zero_page_ram.size()); 
    GBRAM  internal_ram(0xC000, 0xFE00);    internal_ram.init(internal_ram.size()); 
    GBRAM  switchable_ram(0xA000, 0xC000);   switchable_ram.init(switchable_ram.size());  
    GBJoypad joypad(0xFF00, 0xFF01); 
 
    SFML_GBVideo video(0x8000, 0xA000); 
    cpu.memory.connect(&zero_page_ram); 
    cpu.memory.connect(&internal_ram); 
    cpu.memory.connect(&switchable_ram); 
    video.init(); 
    video.connect_to_memory(cpu.memory); 
    
    // fill rom with boot info
    std::fstream in("data/DMG_ROM.bin", std::ios::in | std::ios::binary);
    if(!in.is_open()) {
        std::cout << "Not able to find Boot ROM. Please change your path" << std::endl; 
        return 1; 
    }
    uint16 addr  = 0x0000; 
    std::cout << "reading" << std::endl; 
    std::vector<uint8> data; 
    uint8 value;
    while(in.get((char&)value)) {
        rom.write_8_rom(addr, value&0xFF); 
        addr++; 
    }

    std::cout << "Read " << addr << " bytes." << std::endl; 
    char g; 
   //  std::cin >> g; 
    
    // read cartridge
    GBCartridge gbc(0x0000, 0x8000); 
    gbc.read_file("data/Bounce.gb"); 
    cpu.memory.connect(&gbc); 
    // map cartridge to memory
    // now printing dissassembly // rom will overwrite gbc entries
    cpu.memory.connect(&rom); 
    cpu.disassemble(); 
    cpu.init(); 
    
    
    int a  = 0; 
    bool once = false; 
    bool use_breakpoint = true; 
    bool verbose_instruction = false; 
    cpu.memory.set_verbose(false); 
    bool switched = false; 
    cpu.memory.connect(&joypad); 
    for(int i=0; i<100000000; ++i) {
        if(!cpu.debug_hold) {
            cpu.single_step(verbose_instruction);  

            // system("sleep 0.0001");
            if(use_breakpoint) {
                if(!once && cpu.registers.PC == 0xe60) {
                    once = true; 
                    cpu.memory.dump(); 
                    verbose_instruction = true; 
                    break; 
                }
             //    if(once) 
                  //   std::cin >> a; 
            }
            if(!switched && cpu.registers.PC >= 0xff) {
                std::cout << "Connecting rom..." << std::endl; 
                cpu.memory.connect(&gbc); 
                switched = true; 
            }
        }
        else break; 
        video.execute(); 
    }
    
    std::string input; 
    
    bool done = false;

    while(!done) {
        std::getline(std::cin, input); 
        std::cout << "Eingabe war: " << input << std::endl; 
        switch(input[0]) {
            case 'q': 
                done = true; 
                break; 
                
            case 't': 
            {
                std::cout << "Instruction Trace: " << cpu.trace.size() << " entries." << std::endl; 
                std::cout << "Printing last 20 instructions and states: " << std::endl; 
                for(int i=std::max(0, (int)cpu.trace.size()-20), iEnd = cpu.trace.size(); i != iEnd; ++i) {
                    cpu.print_state(cpu.trace[i].registers_before); 
                    std::cout << "Instruction: " << cpu.trace[i].instruction->alt_name << std::endl; 
                }
                cpu.print_state(cpu.trace.back().registers_after);
            }
            break; 
            
            case 's': 
            {
                 cpu.single_step(verbose_instruction);  
                 cpu.print_state();
            }
            break; 
            
            default: 
                std::cout << "Unknown option." << std::endl; 
                break; 
        }
    }
    
}