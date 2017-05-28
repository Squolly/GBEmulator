#ifndef __GB_SERIAL_TRANSFER_HPP__
#define __GB_SERIAL_TRANSFER_HPP__

#include "MemoryMappedModule.hpp"

class GBSerialTransfer : public MemoryMappedModule { // TODO
    public:
        GBSerialTransfer(uint32 start_address, uint32 end_address, 
                const std::string& name = std::string("Serial Transfer Module"), 
                const std::string& description = std::string("Serial Transfer Module")); 
        
    virtual void operate(); 
    virtual uint8 read_8(uint16 address); 
    virtual void write_8(uint16 address, uint8 value); 
    
    private:
        uint8 _data; // R/W data read or to be written
        bool  _transfer; // false: no transfer, true: start transfer
        bool _internalClock; // false: external (500KHz max.), true: internal (8192Hz)
        bool _verbose; 
};

#endif