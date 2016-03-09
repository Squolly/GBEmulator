#ifndef __GB_VIDEO_HPP__
#define __GB_VIDEO_HPP__

#include "MemoryMappedModule.hpp"

class GBVideo : public MemoryMappedModule {
    public: 
        GBVideo(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("First Video Module"), 
                const std::string& description = std::string("This Video Module should be used for testing.")) : 
                MemoryMappedModule(name, description, start_address, end_address) { }
                
    private:     
}; 

#endif