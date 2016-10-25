#include "Cartridge/GBMBC1.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

GBMBC1::GBMBC1(uint32 start_address, uint32 end_address, const std::string& name, const std::string& description) : 
            MemoryMappedModule(name, description, start_address, end_address), 
            _permanent_ROM(start_address, end_address, name, description), 
            _selected_ROM(1), 
            _selected_RAM(0), 
            _ram_enabled(false), 
            _num_rom_banks(0),
            _num_ram_banks(0), 
            _selection_mode(false),
            _type(0) { 
                
}

uint8 GBMBC1::read_8(uint16 address) {
    // stay in ROM 
    if(address >= 0x0000 && address < 0x3FFF) {
        return _switchable_ROM[0].read_8(address); 
    }
    else if(address >= 0x4000 && address < 0x8000) {
        return _switchable_ROM[_selected_ROM].read_8(address); 
    }
    else if(address >= 0xA000 && address < 0xC000 && _ram_enabled) {
        return _switchable_RAM[_selected_RAM].read_8(address); 
    }
    else; 
        // std::cout << "Illegal read." << std::endl; 
    return -1; 
}

void  GBMBC1::write_8(uint16 address, uint8 value) { 
    // RAM Enable (00h disable, xAh enable)
    if(address >= 0x0000 && address <= 0x1FFF) {
        if(value & 0xF == 0xA) {
            _ram_enabled = true; 
        }
        else {
            _ram_enabled = false; 
        }
        std::cout << "External RAM enabled: " << (_ram_enabled ? "true" : "false") << std::endl; 
    }
    
    // ROM Bank Number
    else if(address >= 0x2000 && address <= 0x3FFF) {
        // special case for 00h, 20h ...
        value &= 0x1F; // only 5 bits
        if((value >> 4) % 2 == 0 && (value & 0xF) == 0 )
            value += 1; 
        _selected_ROM = (_selected_ROM & 0x60) | value; 
        // std::cout << "ROM Bank selected: " << _selected_ROM << std::endl; 
        _selected_ROM &= (_switchable_ROM.size() - 1); 
    }
    
    // RAM Bank Number OR Upper Bits of ROM Bank Number
    else if(address >= 0x4000 && address <= 0x5FFF) {
        value &= 0x3; 
        if(_selection_mode) { // RAM selection 
            _selected_RAM = value; 
            _selected_RAM &= (_switchable_RAM.size() - 1); 
            std::cout << "RAM Bank selected: " << _selected_ROM << std::endl; 
        }
        else { // Bit 5 and 6 of ROM selection
            _selected_ROM &= 0x1F; // mask in case some upper bits set 
            _selected_ROM |= value << 5; 
            std::cout << "ROM Bank selected (Bits 5 and 6): " << _selected_ROM << std::endl;
            // hack to prevent invalid rom bank
            _selected_ROM &= (_switchable_ROM.size() - 1); 
        }
    }
    
    else if(address >= 0x6000 && address <= 0x7FFF) {
        std::cout << "Value: " << (int)(value) << std::endl; 
        value &= 1; 
        if(value) { // RAM Banking Mode
            _selection_mode = true; 
        }
        else {
            _selection_mode = false; 
        }
        std::cout << "Setting selection mode: " << (_selection_mode ? "true" : "false") << std::endl; 
    }
    else if(address >= 0xA000 && address <= 0xC000) {
        std::cout << "Writing to external RAM" << std::endl; 
        std::cout << "External RAM banks: " << _num_ram_banks << std::endl; 
        if(_ram_enabled) {
            _switchable_RAM[_selected_RAM].write_8(address, value); 
        }
        else {
            std::cout << "RAM not enabled!" << std::endl; 
        }
    }
    else
        std::cout << "Illegal write." << std::endl; 
}
      
void GBMBC1::read_file(const std::string& filename) {
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
            data.at(i) = value; 
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
    
    std::cout << "Cartridge Type (" << (int)data[0x147] << "): "; 
    _type = data[0x147]; 
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
    
    if(data[0x147] != 0x01 && data[0x147] != 0x02 && data[0x147] != 0x03 && data[0x147] != 0x06) {
        std::cerr << "No MBC1 cartridge: " << (int)data[0x147] << std::endl; 
    }
    
    std::cout << "ROM Size: "; 
    
    _num_rom_banks = 0; 
    switch(data[0x148]) {
        case 0x00: std::cout << "256Kbit =  32KByte =   2 banks" << std::endl; _num_rom_banks = 2; break;
        case 0x01: std::cout << "512Kbit =  64KByte =   4 banks" << std::endl; _num_rom_banks = 4; break;
        case 0x02: std::cout << "  1Mbit = 128KByte =   8 banks" << std::endl; _num_rom_banks = 8; break;
        case 0x03: std::cout << "  2Mbit = 256KByte =  16 banks" << std::endl; _num_rom_banks = 16; break;
        case 0x04: std::cout << "  4Mbit = 512KByte =  32 banks" << std::endl; _num_rom_banks = 32; break;
        case 0x05: std::cout << "  8Mbit =   1MByte =  64 banks" << std::endl; _num_rom_banks = 64; break;
        case 0x06: std::cout << " 16Mbit =   2MByte = 128 banks" << std::endl; _num_rom_banks = 128; break;
        
        case 0x52: std::cout << "  9Mbit = 1.1MByte =  72 banks" << std::endl; _num_rom_banks = 72; break;
        case 0x53: std::cout << " 10Mbit = 1.2MByte =  80 banks" << std::endl; _num_rom_banks = 80; break;
        case 0x54: std::cout << " 12Mbit = 1.5MByte =  96 banks" << std::endl; _num_rom_banks = 96; break;
        default: std::cout << "Unknown ROM Size" << std::endl; break; 
    }
    // switchable ROM is always located from 0x4000 to 0x7FFF (unless its bank 0) 
    _switchable_ROM = std::vector<GBROM>(_num_rom_banks, GBROM(0x4000, 0x8000)); 
    _switchable_ROM[0] = GBROM(0x0000, 0x4000); 
    std::cout << "ROM Banks: " << _num_rom_banks << std::endl; 
    for(auto& r : _switchable_ROM) {
        r.init(r.size()); // init all ROM to 16kb
    }

    std::cout << "RAM Size: "; 
    int ram_size = 0; 
    switch(data[0x149]) {
        case 0x00: std::cout << "None" << std::endl; break;
        case 0x01: std::cout << " 16Kbit =   2KByte =   1 banks" << std::endl; _num_ram_banks = 1; ram_size = (1 << 11); break;
        case 0x02: std::cout << " 64Kbit =   8KByte =   1 banks" << std::endl; _num_ram_banks = 1; ram_size = (1 << 13); break;
        case 0x03: std::cout << "256Kbit =  32KByte =   4 banks" << std::endl; _num_ram_banks = 4; ram_size = (1 << 13); break;
        case 0x04: std::cout << "  1Mbit = 128KByte = 16 banks" << std::endl; _num_ram_banks = 16; ram_size = (1 << 13); break;
        default: std::cout << "Unknown RAM Size" << std::endl; break; 
    }
    if(_num_ram_banks != 0) {
        // ignore ram size for now 
        _switchable_RAM = std::vector<GBRAM>(_num_ram_banks, GBRAM(0xA000, 0xC000)); //  8kb
        std::cout << "RAM Banks: " << _num_ram_banks << std::endl; 
        for(auto& r : _switchable_RAM) {
            r.init(r.size()); 
        }
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
    // _permanent_ROM.init(0x8000); 
    
    // fill all ROM
    if(data.size() < _num_rom_banks * 0x4000) {
        std::cerr << "[Cartridge] Error: File to small" << std::endl; 
        return; 
    }
    
    for(int rom_i=0; rom_i<_num_rom_banks; ++rom_i) {
        std::cout << "Rom " << rom_i << std::endl; 
        for(int i=0; i<0x4000; ++i) {
            int addr = i; 
            if(rom_i != 0) {
                addr += 0x4000; 
            }
            _switchable_ROM.at(rom_i).write_8_rom(addr, data.at(i + rom_i * 0x4000)); 
        }
    }
    std::cout << "Filling done." << std::endl; 
}