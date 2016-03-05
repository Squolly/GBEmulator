#ifndef __GBROM_HPP__
#define __GBROM_HPP__

#include "MemoryMappedModule.hpp"

/*
Cartridge Module
Should be able to read files (ROMs) of different formats
Has internally a few RAM and ROM Modules that should be mapped correctly (Look at different layout formats)
access for there has to catch specific address requests and react to them 
as some of them may exchange internal Modules that should be remapped (via connect by Memory) to 
the correct region
*/
class GBCartridge : public MemoryMappedModule {
    public:
        GBCartridge(const uint32 start_address, const uint32 end_address, 
                const std::string& name = std::string("Game Boy (Standard Cartridge)"), 
                const std::string& description = std::string("Initial Cartridge Module. Should be exchanged with more specific ones.")) : 
                MemoryMappedModule(name, description, start_address, end_address) { }
    private:
};

#endif
