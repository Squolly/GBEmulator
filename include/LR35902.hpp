#ifndef __LR35902_HPP__
#define __LR35902_HPP__

typedef unsigned short ushort; 
typedef unsigned char  uchar; 

struct Registers {
    Registers() {}; 
    ~Registers() {}; 


    // Note: Hi and Lo depend on internal memory layout
    //       endianess does matter, change in future

    // Accumulator (A) & Flags (F)
    union { struct { uchar F; uchar A; }; ushort AF; }; // 16 Bit: AF, Hi: A, Lo: F

    // BC 
    union { struct { uchar C; uchar B; }; ushort BC; }; // 16 Bit: BC, Hi: B, Lo: C

    // DE
    union { struct { uchar E; uchar D; }; ushort DE; }; // 16 Bit: DE, Hi: D, Lo: E

    // HL 
    union { struct { uchar L; uchar H; }; ushort HL; }; // 16 Bit: HL, Hi: H, Lo: L

    // programm counter / pointer
    ushort PC;

    // stack pointer 
    ushort SP; 
}; 

class LR35902 {
public: 


private: 


}; 

#endif
