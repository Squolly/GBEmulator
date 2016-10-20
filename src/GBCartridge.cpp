#include "GBCartridge.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

GBCartridge::GBCartridge(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description) : 
            MemoryMappedModule(name, description, start_address, end_address), 
            _permanent_ROM(start_address, end_address, name, description) { 
                
}

uint8 GBCartridge::read_8(uint16 address) {
    // stay in ROM 
    if(address >= 0x0000 && address < 0x8000) {
        return _permanent_ROM.read_8(address); 
    }
}

void  GBCartridge::write_8(uint16 address, uint8 value) { 
    // stay in ROM 
    if(address >= 0x0000 && address < 0x8000) {
        return _permanent_ROM.write_8(address, value); 
    }
}
      
void GBCartridge::read_file(const std::string& filename) {
    std::ifstream in(filename.c_str()); 
    
    if(!in.is_open()) {
        std::cout << "Unable to open plain ROM Data file " << filename << std::endl; 
        return; 
    }
   
    in.seekg(0, std::ios_base::end); 
    int file_size = in.tellg(); 
    in.seekg(0, std::ios_base::beg); 
    
    std::vector<uint8> data(file_size, 0); 
    std::cout << "File size: " << file_size << std::endl; 
    
    // read whole file for now
    for(int i=0; i<file_size; ++i) {
        uint8 value;
        if(in.get((char&)value)) {
            data[i] = value; 
        }
        // std::cout << "value: " << std::hex << (int)data[0] << std::endl; 
    }
    
    // output header for debug
    std::cout << "Nintendo Logo: " << std::endl; 
    
    for(int i=0x104, n = 0; i<0x134; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(data[i]) << " "; 
        if(++n % 16 == 0) 
            std::cout << std::endl; 
    }
    
    std::cout << std::endl; 
    std::cout << "Title of game: " << std::endl; 
    for(int i=0x134; i<0x142; ++i) {
        std::cout << (char)data[i]; 
    }
    std::cout << std::endl; 
    
    switch(data[0x143]) {
        case 0x80: std::cout << "Color GB"; break; 
        default:   std::cout << "Not Color GB"; break; 
    }
    std::cout << std::endl; 
    
    std::cout << "Licence code: " << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x144] << " "; 
    std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x145] << std::endl; 
    
    std::cout << std::endl; 
    
    std::cout << "GB/SGB Indicator: "; 
    switch(data[0x146]) {
        case 0x00: std::cout << "GameBoy" << std::endl;       break; 
        case 0x03: std::cout << "Super GameBoy" << std::endl; break; 
    }
    
    std::cout << std::endl;
    
    std::cout << "Cartridge Type: "; 
    switch(data[0x147]) {
        case 0x00: std::cout << "ROM ONLY" << std::endl; break; 
        case 0x01: std::cout << "ROM + MBC1" << std::endl; break; 
        case 0x02: std::cout << "ROM + MBC1 + RAM" << std::endl; break; 
        case 0x03: std::cout << "ROM + MBC1 + RAM + BATTERY" << std::endl; break; 
        case 0x05: std::cout << "ROM + MBC2" << std::endl; break; 
        case 0x06: std::cout << "ROM + MBC1 + BATTERY" << std::endl; break; 
        case 0x08: std::cout << "ROM + RAM" << std::endl; break; 
        case 0x09: std::cout << "ROM + RAM + BATTERY" << std::endl; break; 
        case 0x0B: std::cout << "ROM + MMM01" << std::endl; break; 
        case 0x0C: std::cout << "ROM + MMM01 + SRAM" << std::endl; break; 
        case 0x0D: std::cout << "ROM + MBC3 + TIMER + BATTERY" << std::endl; break; 
        case 0x0F: std::cout << "ROM + MBC3 + TIMER + BATTERY" << std::endl; break; 
        case 0x10: std::cout << "ROM + MBC3 + TIMER + RAM + BATERY" << std::endl; break; 
        case 0x11: std::cout << "ROM + MBC3" << std::endl; break; 
        
        case 0x12: std::cout << "ROM + MBC3 + RAM" << std::endl; break; 
        case 0x13: std::cout << "ROM + MBC3 + RAM + BATTERY" << std::endl; break; 
        case 0x19: std::cout << "ROM + MBC5" << std::endl; break; 
        case 0x1A: std::cout << "ROM + MBC5 + RAM" << std::endl; break; 
        case 0x1B: std::cout << "ROM + MBC5 + RAM + BATTERY" << std::endl; break; 
        case 0x1C: std::cout << "ROM MBC5 + RUMBLE" << std::endl; break; 
        case 0x1D: std::cout << "ROM MBC5 + RUMBLE + SRAM" << std::endl; break; 
        case 0x1E: std::cout << "ROM MBC5 + RUMBLE + SRAM + BATTERY" << std::endl; break; 
        case 0x1F: std::cout << "Pocket Camera" << std::endl; break; 
        case 0xFD: std::cout << "Bandai TAMA5" << std::endl; break; 
        case 0xFE: std::cout << "Hudson HuC-3" << std::endl; break; 
        case 0xFF: std::cout << "Hudson HuC-1" << std::endl; break; 
        default: std::cout << "Unknown Cartridge type" << std::endl; break; 
    }
    
    std::cout << "ROM Size: "; 
    switch(data[0x148]) {
        case 0x00: std::cout << "256Kbit =  32KByte =   2 banks" << std::endl; break;
        case 0x01: std::cout << "512Kbit =  64KByte =   4 banks" << std::endl; break;
        case 0x02: std::cout << "  1Mbit = 128KByte =   8 banks" << std::endl; break;
        case 0x03: std::cout << "  2Mbit = 256KByte =  16 banks" << std::endl; break;
        case 0x04: std::cout << "  4Mbit = 512KByte =  32 banks" << std::endl; break;
        case 0x05: std::cout << "  8Mbit =   1MByte =  64 banks" << std::endl; break;
        case 0x06: std::cout << " 16Mbit =   2MByte = 128 banks" << std::endl; break;
        
        case 0x52: std::cout << "  9Mbit = 1.1MByte =  72 banks" << std::endl; break;
        case 0x53: std::cout << " 10Mbit = 1.2MByte =  80 banks" << std::endl; break;
        case 0x54: std::cout << " 12Mbit = 1.5MByte =  96 banks" << std::endl; break;
        default: std::cout << "Unknown ROM Size" << std::endl; break; 
    }
    
    std::cout << "RAM Size: "; 
    switch(data[0x149]) {
        case 0x00: std::cout << "None" << std::endl; break;
        case 0x01: std::cout << " 16Kbit =   2KByte =   1 banks" << std::endl; break;
        case 0x02: std::cout << " 64Kbit =   8KByte =   1 banks" << std::endl; break;
        case 0x03: std::cout << "256Kbit =  32KByte =   4 banks" << std::endl; break;
        case 0x04: std::cout << "  1Mbit = 128KByte = 16 banks" << std::endl; break;
        default: std::cout << "Unknown RAM Size" << std::endl; break; 
    }
    
    std::cout << "Destination Code: "; 
    switch(data[0x14A]) {
        case 0x00: std::cout << "Japanese" << std::endl; break;
        case 0x01: std::cout << "Non-Japanese" << std::endl; break;
        default: std::cout << "Unknown Destination Code" << std::endl; break; 
    }
    
    std::cout << "Licence Code (old): "; 
    switch(data[0x14B]) {
        case 0x33: std::cout << "Check Obove Licence Code" << std::endl; break;
        case 0x79: std::cout << "Accolade" << std::endl; break;
        case 0xA4: std::cout << "Konami" << std::endl; break;
        default: std::cout << "Unknown Licence Code (old)" << std::endl; break; 
    }
    
    std::cout << "Mask ROM Version number: "; 
    std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x14C] << std::endl; 
    
    std::cout << "Complement Check: "; 
    std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x14D] << std::endl; 
    
    std::cout << "Checksum: "; 
    std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x14E] << " "; 
    std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)data[0x14F]; 
    std::cout << std::endl; 

    std::cout << "Filling data in Modules..." << std::endl; 
    std::cout << "Here only ROM 32k..." << std::endl; 
    _permanent_ROM.init(0x8000); 
    for(int i=0; i<0x8000; ++i) {
        _permanent_ROM.write_8_rom(i, data[i]); 
    }
    std::cout << "Filling done." << std::endl; 
}