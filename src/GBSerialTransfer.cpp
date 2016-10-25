#include "GBSerialTransfer.hpp"

#include <iostream>

GBSerialTransfer::GBSerialTransfer(uint32 start_address, uint32 end_address, 
    const std::string& name, 
    const std::string& description) : 
    MemoryMappedModule(name, description, start_address, end_address), 
    _data(0), _transfer(false), _internalClock(false) {
        
 }
 
void GBSerialTransfer::operate() {
    // todo 
}

uint8 GBSerialTransfer::read_8(uint16 address) {
    uint8 rel_addr = relative_address(address); 
    
    switch(rel_addr) {
        case 0x00: // 0xFF01 (SB) 
            return _data; 
            
        // TODO: use info? 
        case 0x01: // 0xFF02 (SC) 
        {
            uint8 _info = 0; 
            if(_transfer) 
                _info |= 0x80; // set bit 7
            if(_internalClock) 
                _info |= 0x01; // set bit 0 
        }
    }
}

void GBSerialTransfer::write_8(uint16 address, uint8 value) {
    uint8 rel_addr = relative_address(address); 
    
    switch(rel_addr) {
        case 0x00: // 0xFF01 (SB) 
             _data = value; 
             break; 
            
        case 0x01: // 0xFF02 (SC) 
            _transfer = value & 0x80; 
            _internalClock = value & 0x01; // set bit 0 
            break; 
    }
    std::cout << "Serial Transfer (write access): " << std::endl; 
    std::cout << "    [Data   = " << (int)_data << "]" << std::endl; 
    std::cout << "    Transfer: " << (_transfer ? "Start Transfer" : "No Transfer") << std::endl; 
    std::cout << "    Clock   : " << (_internalClock ? "Internal" : "External") << std::endl; 
    // std::cin.get(); 
}