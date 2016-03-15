#ifndef __GBRAM_HPP__
#define __GBRAM_HPP__

#include "MemoryMappedModule.hpp"

class GBRAM : public MemoryMappedModule {
    public:
        GBRAM(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("RAM Module"), 
                const std::string& description = std::string("RAM - Random Access Memory")); 
        
    virtual void operate(); 
    virtual uint8 read_8(uint16 address); 
    virtual void write_8(uint16 address, uint8 value); 
    void init(int size); 
    
    private:
};

#endif
