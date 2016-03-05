#ifndef __GBSOUND_HPP__
#define __GBSOUND_HPP__

#include "MemoryMappedModule.hpp"

class GBSound : public MemoryMappedModule {
    public:
        GBSound(const uint32 start_address, const uint32 end_address, 
                const std::string& name = std::string("First Sound Module"), 
                const std::string& description = std::string("This Sound Module should be used for testing.")) : 
                MemoryMappedModule(name, description, start_address, end_address) { }
    private:
};

#endif
