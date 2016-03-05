#ifndef __GBRAM_HPP__
#define __GBRAM_HPP__

#include "MemoryMappedModule.hpp"

class GBRAM {
	public:
		GBRAM(const uint32 start_address, const uint32 end_address, 
				const std::string& name = std::string("RAM Module"), 
				const std::string& description = std::string("RAM - Random Access Memory") : 
				MemoryMappedModule(name, description, start_address, end_address) { }
	private:
};

#endif
