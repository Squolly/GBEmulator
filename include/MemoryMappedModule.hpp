#ifndef __MEMORYMAPPED_MODULE_HPP__
#define __MEMORYMAPPED_MODULE_HPP__

#include "Module.hpp"
#include "types.hpp" 

#include <vector>

class MemoryMappedModule : public Module {
    public:
        MemoryMappedModule(const std::string& name, const std::string& description, 
                           const uint32 start_address, const uint32 end_address) : 
                           _start_address(start_address), _end_address(end_address), _size(end_address-start_address), Module(name, description) { }
            
        uint32 start_address() { return _start_address; }
        uint32 end_address() { return _end_address; }
        uint32 size() { return _size; }
        
        virtual uint8 read_8(uint16 address) { if(!check_bounds(address)) return -1; return _data[address]; }
        virtual void  write_8(uint16 address, uint8 value) { if(!check_bounds(address)) return; _data[address] = value; }
        
        bool  check_bounds(uint16 address) { return (address >= _start_address && address < _end_address); }
        
    private:
        uint32 _start_address; // beginning of memory mapped area
        uint32 _end_address;   // end of memory mapped area
        uint32 _size;          // size of memory mapped area
        
        std::vector<uint8> _data; // TODO: temporary, should be replaced with true implementation
}; 

#endif