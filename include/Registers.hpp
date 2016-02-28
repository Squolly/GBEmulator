#ifndef __REGISTERS_HPP__
#define __REGISTERS_HPP__

#include "types.hpp"

const uint8 BITMASK_7 = 0x80; 
const uint8 BITMASK_6 = 0x40; 
const uint8 BITMASK_5 = 0x20; 
const uint8 BITMASK_4 = 0x10; 
const uint8 BITMASK_3 = 0x06; 
const uint8 BITMASK_2 = 0x04; 
const uint8 BITMASK_1 = 0x02; 
const uint8 BITMASK_0 = 0x01; 

struct Registers {
    Registers() : AF(0), BC(0), DE(0), HL(0) {}; 
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
    
    // Flags: Register F
    //        7 6 5 4 3 2 1 0
    //        Z N H C 0 0 0 0
    
    void set_z() { F |= BITMASK_7; } // set zero
    void set_n() { F |= BITMASK_6; } // set subtract
    void set_h() { F |= BITMASK_5; } // set half carry
    void set_c() { F |= BITMASK_4; } // set carry
    
    void clear_z() { F = F & ( ~BITMASK_7 ); } // clear zero
    void clear_n() { F = F & ( ~BITMASK_6 ); } // clear subtract
    void clear_h() { F = F & ( ~BITMASK_5 ); } // clear half carry
    void clear_c() { F = F & ( ~BITMASK_4 ); } // clear carry
    
    uint8 z() { return F & BITMASK_7; } // return zero
    uint8 n() { return F & BITMASK_6; } // return subtract
    uint8 h() { return F & BITMASK_5; } // return half carry
    uint8 c() { return F & BITMASK_4; } // return carry
}; 


#endif