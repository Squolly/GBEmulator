#ifndef __GBROM_HPP__
#define __GBROM_HPP__

#include "MemoryMappedModule.hpp"

class GBROM {
	public:
		GBROM(const uint32 start_address, const uint32 end_address, 
				const std::string& name = std::string("ROM Module"), 
				const std::string& description = std::string("ROM - Read Only Memory") : 
				MemoryMappedModule(name, description, start_address, end_address) { }
	private:
};

#endif
