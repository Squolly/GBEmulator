#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include "types.hpp"

struct Registers {
    Registers() {}; 
    ~Registers() {}; 


    // Note: Hi and Lo depend on internal memory layout
    //       endianess does matter, change in future

    // Accumulator (A) & Flags (F)
    union { struct { uint8 F; uint8 A; }; uint16 AF; }; // 16 Bit: AF, Hi: A, Lo: F

    // BC 
    union { struct { uint8 C; uint8 B; }; uint16 BC; }; // 16 Bit: BC, Hi: B, Lo: C

    // DE
    union { struct { uint8 E; uint8 D; }; uint16 DE; }; // 16 Bit: DE, Hi: D, Lo: E

    // HL 
    union { struct { uint8 L; uint8 H; }; uint16 HL; }; // 16 Bit: HL, Hi: H, Lo: L

    // programm counter / pointer
    uint16 PC;

    // stack pointer 
    uint16 SP; 
}; 

struct Memory {
    std::vector<uint8> data; 
    
    Memory(const int size); 
    uint8  read_u8(const uint16 address); 
    uint16 read_u16(const uint16 address);
    bool   write_u8(const uint8 address, const uint8 value); 
    bool   write_u16(const uint8 address, const uint8 value); 
}; 

#endif