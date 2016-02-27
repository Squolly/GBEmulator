#ifndef __INSTRUCTION_SET_HPP__
#define __INSTRUCTION_SET_HPP__

#include "Instruction.hpp"

//   Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
//		  uint8 opcode, const uint8 bytes, const uint8 cycles, bool verbose = false); 
	
const bool VERBOSE_FLAG = false; 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

// 0x00 NOP
struct NOP_In : public Instruction { NOP_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x01 LD BC, d16 
struct LD_BC_d16_In : public Instruction { LD_BC_d16_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x02 LD (BC), A 
struct LD_mBC_A_In : public Instruction { LD_mBC_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x03 INC BC
struct INC_BC_In : public Instruction { INC_BC_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x04 INC B
struct INC_B_In : public Instruction { INC_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x05 DEC B
struct DEC_B_In : public Instruction { DEC_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x06 LD B, d8
struct LD_B_d8_In : public Instruction { LD_B_d8_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x07 RLCA
struct RLCA_In : public Instruction { RLCA_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x08 LD (a16), SP
struct LD_a16_SP_In : public Instruction { LD_a16_SP_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x09 ADD HL, BC
struct ADD_HL_BC_In : public Instruction { ADD_HL_BC_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0A LD A, (BC)
struct LD_A_mBC_In : public Instruction { LD_A_mBC_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0B DEC BC
struct DEC_BC_In : public Instruction { DEC_BC_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0C INC C
struct INC_C_In : public Instruction { INC_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0D DEC C
struct DEC_C_In : public Instruction { DEC_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0E LD C, d8
struct LD_C_d8_In : public Instruction { LD_C_d8_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// 0x0F RRCA
struct RRCA_In : public Instruction { RRCA_In(); virtual void op(LR35902& cpu, Memory& memory); }; 

// Constructors
NOP_In::NOP_Instruction()             : Instruction( "NOP",        "NOP", "----", 0x00, 1,  4, VERBOSE_FLAG) { } // 0x00
LD_BC_d16_In::LD_BC_d16_Instruction() : Instruction(  "LD", "LD BC, d16", "----", 0x01, 3, 12, VERBOSE_FLAG) { } // 0x01
LD_mBC_A_In::LD_mBC_A_Instruction()   : Instruction(  "LD", "LD (BC), A", "----", 0x02, 1,  8, VERBOSE_FLAG) { } // 0x02
INC_BC_In::INC_BC_In()                : Instruction( "INC",     "INC BC", "----", 0x03, 1,  8, VERBOSE_FLAG) { } // 0x03
INC_B_In::INC_B_In()                  : Instruction( "INC",      "INC B", "Z0H-", 0x04, 1,  4, VERBOSE_FLAG) { } // 0x04
DEC_B_In::DEC_B_In()                  : Instruction( "DEC",      "DEC B", "Z1H-", 0x05, 1,  4, VERBOSE_FLAG) { } // 0x05
LD_B_d8_In::LD_B_d8_In()              : Instruction(  "LD",   "LD B, d8", "----", 0x06, 2,  8, VERBOSE_FLAG) { } // 0x06
RLCA_In::RLCA_In()                    : Instruction("RLCA",       "RLCA", "000C", 0x07, 1,  4, VERBOSE_FLAG) { } // 0x07
LD_a16_SP_In::LD_a16_SP_In()          : Instruction(  "LD", "LD a16, SP", "----", 0x08, 3, 20, VERBOSE_FLAG) { } // 0x08
ADD_HL_BC_In::ADD_HL_BC_In()          : Instruction( "ADD", "ADD HL, BC", "-0HC", 0x09, 1,  8, VERBOSE_FLAG) { } // 0x09
LD_A_mBC_In::LD_A_mBC_In()            : Instruction(  "LD", "LD A, (BC)", "----", 0x0A, 1,  8, VERBOSE_FLAG) { } // 0x0A
DEC_BC_In::DEC_BC_In()                : Instruction( "DEC",     "DEC BC", "----", 0x0B, 1,  8, VERBOSE_FLAG) { } // 0x0B
INC_C_In::INC_C_In()                  : Instruction( "INC",      "INC C", "Z0H-", 0x0C, 1,  4, VERBOSE_FLAG) { } // 0x0C
DEC_C_In::DEC_C_In()                  : Instruction( "DEC",      "DEC C", "Z1H-", 0x0D, 1,  4, VERBOSE_FLAG) { } // 0x0D
LD_C_d8_In::LD_C_d8_In()              : Instruction(  "LD",   "LD C, d8", "----", 0x0E, 2,  8, VERBOSE_FLAG) { } // 0x0E
RRCA_In::RRCA_In()                    : Instruction("RRCA",       "RRCA", "000C", 0x0F, 1,  4, VERBOSE_FLAG) { } // 0x0F

// Instruction Implementation
void       NOP_In::op(LR35902& cpu, Memory& memory) {  }                                                          // 0x00
void LD_BC_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.BC = memory.read_u16(cpu.registers.PC + 1); } // 0x01
void  LD_mBC_A_In::op(LR35902& cpu, Memory& memory) { memory.write_u8(cpu.registers.BC, cpu.registers.A); }       // 0x02
void    INC_BC_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.BC); }                      // 0x03
void     INC_B_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.B); }                        // 0x04  
void     DEC_B_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.B); }                        // 0x05 
void   LD_B_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = memory.read_u8(cpu.registers.PC + 1); }   // 0x06
void      RLCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_left_reg_a(); }                                   // 0x07
void LD_a16_SP_In::op(LR35902& cpu, Memory& memory) { uint16 addr = memory.read_u16(cpu.registers.PC + 1);        // 0x08
                                                      memory.write_u16(addr, cpu.registers.SP); }                 
void ADD_HL_BC_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.BC); }        // 0x09
void  LD_A_mBC_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.BC); }       // 0x0A
void    DEC_BC_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.BC);  }                     // 0x0B
void     INC_C_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.C);  }                       // 0x0C
void     DEC_C_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.C);  }                       // 0x0D
void   LD_C_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = memory.read_u8(cpu.registers.PC + 1);  }  // 0x0E
void      RRCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_right_reg_a();  }                                 // 0x0F


// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================


// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================


// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================


// =================================================================================================
// OpCodes 0x50 - 0x5F
// =================================================================================================


// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================


// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================


// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================


// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================


// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================


// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================


// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================


// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================


// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================


// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================
#endif __INSTRUCTION_SET_HPP__