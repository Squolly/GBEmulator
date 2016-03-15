#ifndef __GBROM_HPP__
#define __GBROM_HPP__

#include "MemoryMappedModule.hpp"

class GBROM : public MemoryMappedModule {
    public:
        GBROM(uint32 start_address, uint32 end_address,
                const std::string& name = std::string("ROM Module"), 
                const std::string& description = std::string("ROM - Read Only Memory")
             ); 
                
        virtual void operate(); 
        virtual uint8 read_8(uint16 address); 
        virtual void  write_8(uint16 address, uint8 value); 
        virtual void  init(int size); 
        virtual void  write_8_rom(uint16 address, uint8 value); 
        
    private:
        
        std::vector<uint8> _data; 
};

#endif
