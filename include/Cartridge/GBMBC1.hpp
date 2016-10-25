#ifndef GBMBC1_HPP__
#define GBMBC1_HPP__

#include "MemoryMappedModule.hpp"
#include "Memory.hpp" 
#include "GBROM.hpp" 
#include "GBRAM.hpp"

/*
Cartridge Module MBC1
Should be able to read files (ROMs) of different formats
Has internally a few RAM and ROM Modules that should be mapped correctly (Look at different layout formats)
access for there has to catch specific address requests and react to them 
as some of them may exchange internal Modules that should be remapped (via connect by Memory) to 
the correct region
*/
class GBMBC1 : public MemoryMappedModule {
    public:
        GBMBC1(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("Game Boy (MBC1 Cartridge)"), 
                const std::string& description = std::string("Initial Cartridge Module. Should be exchanged with more specific ones.")); 

                virtual uint8 read_8(uint16 address); 
                virtual void  write_8(uint16 address, uint8 value); 
                
                virtual void read_file(const std::string& filename); 
                virtual void operate() { }
    private:
        Memory _memory; 
        GBROM  _permanent_ROM; 
        std::vector<GBROM> _switchable_ROM; 
        std::vector<GBRAM> _switchable_RAM; 
        
        uint16 _selected_ROM; 
        uint16 _selected_RAM; 
        
        bool _ram_enabled; 
        bool _selection_mode; 
        
        int _num_rom_banks; 
        int _num_ram_banks; 
        
        uint8 _type; 
};

#endif
