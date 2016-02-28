#ifndef __INSTRUCTION_SET_HPP__
#define __INSTRUCTION_SET_HPP__

#include "Instruction.hpp"

//   Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
//		  uint8 opcode, const uint8 bytes, const uint8 cycles, bool verbose = false); 
	
const bool VERBOSE_FLAG = false; 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================


struct NOP_In : public Instruction { NOP_In(); virtual void op(LR35902& cpu, Memory& memory); };                 // 0x00 NOP
struct LD_BC_d16_In : public Instruction { LD_BC_d16_In(); virtual void op(LR35902& cpu, Memory& memory); };     // 0x01 LD BC, d16 
struct LD_mBC_A_In : public Instruction { LD_mBC_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x02 LD (BC), A 
struct INC_BC_In : public Instruction { INC_BC_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x03 INC BC
struct INC_B_In : public Instruction { INC_B_In(); virtual void op(LR35902& cpu, Memory& memory); };             // 0x04 INC B
struct DEC_B_In : public Instruction { DEC_B_In(); virtual void op(LR35902& cpu, Memory& memory); };             // 0x05 DEC B
struct LD_B_d8_In : public Instruction { LD_B_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };         // 0x06 LD B, d8
struct RLCA_In : public Instruction { RLCA_In(); virtual void op(LR35902& cpu, Memory& memory); };               // 0x07 RLCA
struct LD_a16_SP_In : public Instruction { LD_a16_SP_In(); virtual void op(LR35902& cpu, Memory& memory); };     // 0x08 LD (a16), SP
struct ADD_HL_BC_In : public Instruction { ADD_HL_BC_In(); virtual void op(LR35902& cpu, Memory& memory); };     // 0x09 ADD HL, BC
struct LD_A_mBC_In : public Instruction { LD_A_mBC_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x0A LD A, (BC)
struct DEC_BC_In : public Instruction { DEC_BC_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x0B DEC BC
struct INC_C_In : public Instruction { INC_C_In(); virtual void op(LR35902& cpu, Memory& memory); };             // 0x0C INC C
struct DEC_C_In : public Instruction { DEC_C_In(); virtual void op(LR35902& cpu, Memory& memory); };             // 0x0D DEC C
struct LD_C_d8_In : public Instruction { LD_C_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };         // 0x0E LD C, d8
struct RRCA_In : public Instruction { RRCA_In(); virtual void op(LR35902& cpu, Memory& memory); };               // 0x0F RRCA

// Constructors
NOP_In::NOP_In()                      : Instruction( "NOP",        "NOP", "----", 0x00, 1,  4, VERBOSE_FLAG) { } // 0x00
LD_BC_d16_In::LD_BC_d16_In()          : Instruction(  "LD", "LD BC, d16", "----", 0x01, 3, 12, VERBOSE_FLAG) { } // 0x01
LD_mBC_A_In::LD_mBC_A_In()            : Instruction(  "LD", "LD (BC), A", "----", 0x02, 1,  8, VERBOSE_FLAG) { } // 0x02
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
void      RLCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_left_c_reg_a(); }                                 // 0x07
void LD_a16_SP_In::op(LR35902& cpu, Memory& memory) { uint16 addr = memory.read_u16(cpu.registers.PC + 1);        // 0x08
                                                      memory.write_u16(addr, cpu.registers.SP); }                 
void ADD_HL_BC_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.BC); }        // 0x09
void  LD_A_mBC_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.BC); }       // 0x0A
void    DEC_BC_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.BC);  }                     // 0x0B
void     INC_C_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.C);  }                       // 0x0C
void     DEC_C_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.C);  }                       // 0x0D
void   LD_C_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = memory.read_u8(cpu.registers.PC + 1);  }  // 0x0E
void      RRCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_right_c_reg_a();  }                               // 0x0F


// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================


struct STOP_In : public Instruction { STOP_In(); virtual void op(LR35902& cpu, Memory& memory); };                // 0x10 STOP
struct LD_DE_d16_In : public Instruction { LD_DE_d16_In(); virtual void op(LR35902& cpu, Memory& memory); };         // 0x11 LD DE, d16
struct LD_mDE_A_In : public Instruction { LD_mDE_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x12 LD (DE), A
struct INC_DE_In : public Instruction { INC_DE_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x13 INC DE
struct INC_D_In : public Instruction { INC_D_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x14 INC D
struct DEC_D_In : public Instruction { DEC_D_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x15 DEC D
struct LD_D_d8_In : public Instruction { LD_D_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x16 LD D, d8
struct RLA_In : public Instruction { RLA_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x17 RLA
struct JR_r8_In : public Instruction { JR_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x18 JR r8
struct ADD_HL_DE_In : public Instruction { ADD_HL_DE_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x19 ADD HL, DE
struct LD_A_mDE_In : public Instruction { LD_A_mDE_In(); virtual void op(LR35902& cpu, Memory& memory); };        // 0x1A LD A, (DE)
struct DEC_DE_In : public Instruction { DEC_DE_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x1B DEC DE
struct INC_E_In : public Instruction { INC_E_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x1C INC E
struct DEC_E_In : public Instruction { DEC_E_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x1D DEC E
struct LD_E_d8_In : public Instruction { LD_E_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x1E LD E, d8
struct RRA_In : public Instruction { RRA_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x1F RRA

// Constructors
STOP_In::STOP_In()                    : Instruction("STOP",     "STOP 0", "----", 0x10, 2,  4, VERBOSE_FLAG) { }  // 0x10
LD_DE_d16_In::LD_DE_d16_In()          : Instruction(  "LD", "LD DE, d16", "----", 0x11, 3, 12, VERBOSE_FLAG) { }  // 0x11
LD_mDE_A_In::LD_mDE_A_In()            : Instruction(  "LD", "LD (DE), A", "----", 0x12, 1,  8, VERBOSE_FLAG) { }  // 0x12
INC_DE_In::INC_DE_In()                : Instruction( "INC",     "INC DE", "----", 0x13, 1,  8, VERBOSE_FLAG) { }  // 0x13
INC_D_In::INC_D_In()                  : Instruction( "INC",      "INC D", "Z0H-", 0x14, 1,  4, VERBOSE_FLAG) { }  // 0x14
DEC_D_In::DEC_D_In()                  : Instruction( "DEC",      "DEC D", "Z1H-", 0x15, 1,  4, VERBOSE_FLAG) { }  // 0x15
LD_D_d8_In::LD_D_d8_In()              : Instruction(  "LD",   "LD D, d8", "----", 0x16, 2,  8, VERBOSE_FLAG) { }  // 0x16
RLA_In::RLA_In()                      : Instruction( "RLA",        "RLA", "000C", 0x17, 1,  4, VERBOSE_FLAG) { }  // 0x17
JR_r8_In::JR_r8_In()                  : Instruction(  "JR",      "JR r8", "----", 0x18, 2, 12, VERBOSE_FLAG) { }  // 0x18
ADD_HL_DE_In::ADD_HL_DE_In()          : Instruction( "ADD", "ADD HL, DE", "-0HC", 0x19, 1,  8, VERBOSE_FLAG) { } // 0x19
LD_A_mDE_In::LD_A_mDE_In()            : Instruction(  "LD", "LD A, (DE)", "----", 0x1A, 1,  8, VERBOSE_FLAG) { } // 0x1A
DEC_DE_In::DEC_DE_In()                : Instruction( "DEC",     "DEC DE", "----", 0x1B, 1,  8, VERBOSE_FLAG) { } // 0x1B
INC_E_In::INC_E_In()                  : Instruction( "INC",      "INC E", "Z0H-", 0x1C, 1,  4, VERBOSE_FLAG) { } // 0x1C
DEC_E_In::DEC_E_In()                  : Instruction( "DEC",      "DEC E", "Z1H-", 0x1D, 1,  4, VERBOSE_FLAG) { } // 0x1D
LD_E_d8_In::LD_E_d8_In()              : Instruction(  "LD",   "LD E, d8", "----", 0x1E, 2,  8, VERBOSE_FLAG) { } // 0x1E
RRA_In::RRA_In()                      : Instruction( "RRA",        "RRA", "000C", 0x1F, 1,  4, VERBOSE_FLAG) { } // 0x1F

// Instruction Implementation
void      STOP_In::op(LR35902& cpu, Memory& memory) { cpu.running = false; }                                      // 0x10                                                       // 0x10
void LD_DE_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.DE = memory.read_u16(cpu.registers.PC + 1); } // 0x11
void  LD_mDE_A_In::op(LR35902& cpu, Memory& memory) { memory.write_u8(cpu.registers.DE, cpu.registers.A);}        // 0x12
void    INC_DE_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.DE); }                      // 0x13
void     INC_D_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.D); }                        // 0x14
void     DEC_D_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.D); }                        // 0x15
void   LD_D_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = memory.read_u8(cpu.registers.PC + 1); }   // 0x16
void       RLA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_left_reg_a();  }                                  // 0x17
void     JR_r8_In::op(LR35902& cpu, Memory& memory) { uint8 r8 = memory.read_u8(cpu.registers.PC + 1);            // 0x18
                                                      if(r8 <= 0x7F) cpu.registers.PC += r8; 
                                                      else cpu.registers.PC -= (((~r8) + 1) & 0x7F); }
void ADD_HL_DE_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.DE); }        // 0x19
void  LD_A_mDE_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.DE); }       // 0x1A
void    DEC_DE_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.DE);  }                     // 0x1B
void     INC_E_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.E);  }                       // 0x1C
void     DEC_E_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.E);  }                       // 0x1D
void   LD_E_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = memory.read_u8(cpu.registers.PC + 1);  }  // 0x1E
void       RRA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_right_reg_a();  }                                  // 0x1F

// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

struct JR_NZ_r8_In : public Instruction { JR_NZ_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };        // 0x20 JR NZ, r8
struct LD_HL_d16_In : public Instruction { LD_HL_d16_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x21 LD HL, d16
struct LD_mHLp_A_In : public Instruction { LD_mHLp_A_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x22 LD (HL+), A
struct INC_HL_In : public Instruction { INC_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x23 INC HL
struct INC_H_In : public Instruction { INC_H_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x24 INC H
struct DEC_H_In : public Instruction { DEC_H_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x25 DEC D
struct LD_H_d8_In : public Instruction { LD_H_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x26 LD H, d8
struct DAA_In : public Instruction { DAA_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x27 DDA
struct JR_Z_r8_In : public Instruction { JR_Z_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x28 JR Z, r8
struct ADD_HL_HL_In : public Instruction { ADD_HL_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x29 ADD HL, HL
struct LD_A_mHLp_In : public Instruction { LD_A_mHLp_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x2A LD A, (HL+)
struct DEC_HL_In : public Instruction { DEC_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x2B DEC HL
struct INC_L_In : public Instruction { INC_L_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x2C INC L
struct DEC_L_In : public Instruction { DEC_L_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x2D DEC L
struct LD_L_d8_In : public Instruction { LD_L_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x2E LD L, d8
struct CPL_In : public Instruction { CPL_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x2F CPL


JR_NZ_r8_In::JR_NZ_r8_In()            : Instruction( "JR",   "JR NZ, r8", "----", 0x20, 2, 12 /* /8 */, VERBOSE_FLAG) { } // 0x20
LD_HL_d16_In::LD_HL_d16_In()          : Instruction( "LD",  "LD HL, d16", "----", 0x21, 3, 12, VERBOSE_FLAG) { }  // 0x21
LD_mHLp_A_In::LD_mHLp_A_In()          : Instruction( "LD", "LD (HL+), A", "----", 0x22, 1,  8, VERBOSE_FLAG) { }  // 0x22
INC_HL_In::INC_HL_In()                : Instruction( "INC",     "INC HL", "----", 0x23, 1,  8, VERBOSE_FLAG) { }  // 0x23
INC_H_In::INC_H_In()                  : Instruction( "INC",      "INC H", "Z0H-", 0x24, 1,  4, VERBOSE_FLAG) { }  // 0x24
DEC_H_In::DEC_H_In()                  : Instruction( "DEC",      "DEC H", "Z1H-", 0x25, 1,  4, VERBOSE_FLAG) { }  // 0x25
LD_H_d8_In::LD_H_d8_In()              : Instruction( "LD",    "LD H, d8", "----", 0x26, 2,  8, VERBOSE_FLAG) { }  // 0x26
DAA_In::DAA_In()                      : Instruction( "DAA",        "DAA", "Z-0C", 0x27, 1,  4, VERBOSE_FLAG) { }  // 0x27
JR_Z_r8_In::JR_Z_r8_In()              : Instruction(  "JR",         "JR", "----", 0x28, 2,  12 /* /8 */, VERBOSE_FLAG) { } // 0x28
ADD_HL_HL_In::ADD_HL_HL_In()          : Instruction( "ADD", "ADD HL, HL", "-0HC", 0x29, 1,  8, VERBOSE_FLAG) { } // 0x29
LD_A_mHLp_In::LD_A_mHLp_In()          : Instruction(  "LD","LD A, (HL+)", "----", 0x2A, 1,  8, VERBOSE_FLAG) { } // 0x2A
DEC_HL_In::DEC_HL_In()                : Instruction( "DEC",     "DEC HL", "----", 0x2B, 1,  8, VERBOSE_FLAG) { } // 0x2B
INC_L_In::INC_L_In()                  : Instruction( "INC",      "INC L", "Z0H-", 0x2C, 1,  4, VERBOSE_FLAG) { } // 0x2C
DEC_L_In::DEC_L_In()                  : Instruction( "DEC",      "DEC L", "Z1H-", 0x2D, 1,  4, VERBOSE_FLAG) { } // 0x2D
LD_L_d8_In::LD_L_d8_In()              : Instruction(  "LD",   "LD L, d8", "----", 0x2E, 2,  8, VERBOSE_FLAG) { } // 0x2E
CPL_In::CPL_In()                      : Instruction( "CPL",        "CPL", "-11-", 0x2F, 1,  4, VERBOSE_FLAG) { } // 0x2F


void  JR_NZ_r8_In::op(LR35902& cpu, Memory& memory) { if(!cpu.registers.z()) {                                    // 0x20
                                                          uint8 off = memory.read_u8(cpu.registers.PC + 1); 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                          cpu.registers.PC -= bytes;  } } // bytes will be added after execution
void LD_HL_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.HL = memory.read_u16(cpu.registers.PC + 1); } // 0x21
void LD_mHLp_A_In::op(LR35902& cpu, Memory& memory) { memory.write_u8(cpu.registers.HL, cpu.registers.A);         // 0x22
                                                      cpu.inc_16bit_reg(cpu.registers.HL); } 
void    INC_HL_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.HL); }                      // 0x23
void     INC_H_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.H); }                        // 0x24
void     DEC_H_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.H); }                        // 0x25
void   LD_H_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = memory.read_u8(cpu.registers.PC + 1); }   // 0x26
void       DAA_In::op(LR35902& cpu, Memory& memory) { cpu.dda(); }                                                // 0x27
void   JR_Z_r8_In::op(LR35902& cpu, Memory& memory) { if(cpu.registers.z()) {                                     // 0x28
                                                          uint8 off = memory.read_u8(cpu.registers.PC + 1); 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                          cpu.registers.PC -= bytes;  } } // bytes will be added after execution
void ADD_HL_HL_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.HL); }        // 0x29
void LD_A_mHLp_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.HL);         // 0x2A
                                                      cpu.inc_16bit_reg(cpu.registers.HL); }
void    DEC_HL_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.HL);  }                     // 0x2B
void     INC_L_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.L);  }                       // 0x2C
void     DEC_L_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.L);  }                       // 0x2D
void   LD_L_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = memory.read_u8(cpu.registers.PC + 1);  }  // 0x2E
void       CPL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = (~cpu.registers.A)&0xFF; 
                                                      cpu.registers.set_n(); cpu.registers.set_h(); }             // 0x2F

// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

struct JR_NC_r8_In : public Instruction { JR_NC_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };        // 0x30 JR NC, r8
struct LD_SP_d16_In : public Instruction { LD_SP_d16_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x31 LD SP, d16
struct LD_mHLm_A_In : public Instruction { LD_mHLm_A_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x32 LD (HL-), A
struct INC_SP_In : public Instruction { INC_SP_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x33 INC SP
struct INC_mHL_In : public Instruction { INC_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x34 INC (HL)
struct DEC_mHL_In : public Instruction { DEC_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x35 DEC (HL)
struct LD_mHL_d8_In : public Instruction { LD_mHL_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x36 LD (HL), d8
struct SCF_In : public Instruction { SCF_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x37 SCF
struct JR_C_r8_In : public Instruction { JR_C_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x38 JR C, r8
struct ADD_HL_SP_In : public Instruction { ADD_HL_SP_In(); virtual void op(LR35902& cpu, Memory& memory); };      // 0x39 ADD HL, SP
struct LD_A_mHLm_In : public Instruction { LD_A_mHLm_In(); virtual void op(LR35902& cpu, Memory& memory); };        // 0x1A LD A, (HL-)
struct DEC_SP_In : public Instruction { DEC_SP_In(); virtual void op(LR35902& cpu, Memory& memory); };            // 0x3B DEC SP
struct INC_A_In : public Instruction { INC_A_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x3C INC A
struct DEC_A_In : public Instruction { DEC_A_In(); virtual void op(LR35902& cpu, Memory& memory); };              // 0x3D DEC A 
struct LD_A_d8_In : public Instruction { LD_A_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };          // 0x3E LD A, d8
struct CCF_In : public Instruction { CCF_In(); virtual void op(LR35902& cpu, Memory& memory); };                  // 0x3F CCF


JR_NC_r8_In::JR_NC_r8_In()            : Instruction(  "JR",  "JR NC, r8", "----", 0x30, 2, 12 /* /8 */, VERBOSE_FLAG) { } // 0x30
LD_SP_d16_In::LD_SP_d16_In()          : Instruction(  "LD", "LD SP, d16", "----", 0x31, 3, 12, VERBOSE_FLAG) { }  // 0x31
LD_mHLm_A_In::LD_mHLm_A_In()          : Instruction(  "LD","LD (HL-), A", "----", 0x32, 1,  8, VERBOSE_FLAG) { }  // 0x32
INC_SP_In::INC_SP_In()                : Instruction( "INC",     "INC SP", "----", 0x33, 1,  8, VERBOSE_FLAG) { }  // 0x33
INC_mHL_In::INC_mHL_In()              : Instruction( "INC",   "INC (HL)", "Z0H-", 0x34, 1, 12, VERBOSE_FLAG) { }  // 0x34
DEC_mHL_In::DEC_mHL_In()              : Instruction( "DEC",   "DEC (HL)", "Z1H-", 0x35, 1, 12, VERBOSE_FLAG) { }  // 0x35
LD_mHL_d8_In::LD_mHL_d8_In()          : Instruction(  "LD","LD (HL), d8", "----", 0x36, 2, 12, VERBOSE_FLAG) { }  // 0x36
SCF_In::SCF_In()                      : Instruction( "SCF",        "SCF", "-001", 0x37, 1,  4, VERBOSE_FLAG) { }  // 0x37
JR_C_r8_In::JR_C_r8_In()              : Instruction(  "JR",         "JR", "----", 0x38, 2,  12 /* /8 */, VERBOSE_FLAG) { } // 0x38
ADD_HL_SP_In::ADD_HL_SP_In()          : Instruction( "ADD", "ADD HL, SP", "-0HC", 0x39, 1,  8, VERBOSE_FLAG) { }  // 0x39
LD_A_mHLm_In::LD_A_mHLm_In()          : Instruction(  "LD","LD A, (HL-)", "----", 0x3A, 1,  8, VERBOSE_FLAG) { } // 0x3A
DEC_SP_In::DEC_SP_In()                : Instruction( "DEC",     "DEC SP", "----", 0x3B, 1,  8, VERBOSE_FLAG) { } // 0x3B
INC_A_In::INC_A_In()                  : Instruction( "INC",      "INC A", "Z0H-", 0x3C, 1,  4, VERBOSE_FLAG) { } // 0x3C
DEC_A_In::DEC_A_In()                  : Instruction( "DEC",      "DEC A", "Z1H-", 0x3D, 1,  4, VERBOSE_FLAG) { } // 0x3D
LD_A_d8_In::LD_A_d8_In()              : Instruction(  "LD",   "LD A, d8", "----", 0x1E, 2,  8, VERBOSE_FLAG) { } // 0x3E
CCF_In::CCF_In()                      : Instruction( "CCF",        "CCF", "-00C", 0x3F, 1,  4, VERBOSE_FLAG) { } // 0x3F


void  JR_NC_r8_In::op(LR35902& cpu, Memory& memory) { if(!cpu.registers.c()) {                                    // 0x30
                                                          uint8 off = memory.read_u8(cpu.registers.PC + 1); 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                          cpu.registers.PC -= bytes;  } } // bytes will be added after execution
void LD_SP_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.SP = memory.read_u16(cpu.registers.PC + 1); } // 0x31
void LD_mHLm_A_In::op(LR35902& cpu, Memory& memory) { memory.write_u8(cpu.registers.HL, cpu.registers.A);         // 0x32
                                                      cpu.dec_16bit_reg(cpu.registers.HL); } 
void    INC_SP_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.SP); }                      // 0x33
void   INC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 value = memory.read_u8(cpu.registers.HL);             // 0x34
                                                      cpu.inc_8bit_reg(value); 
                                                      memory.write_u8(cpu.registers.HL, value); }                     
void   DEC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 value = memory.read_u8(cpu.registers.HL);             // 0x35
                                                      cpu.dec_8bit_reg(value); 
                                                      memory.write_u8(cpu.registers.HL, value); }
void LD_mHL_d8_In::op(LR35902& cpu, Memory& memory) { memory.write_u8(cpu.registers.HL, memory.read_u8(cpu.registers.PC + 1)); }  // 0x36
void       SCF_In::op(LR35902& cpu, Memory& memory) { cpu.registers.clear_n(); cpu.registers.clear_h(); cpu.registers.set_c(); }  // 0x37
void   JR_C_r8_In::op(LR35902& cpu, Memory& memory) { if(cpu.registers.c()) {                                    // 0x38
                                                          uint8 off = memory.read_u8(cpu.registers.PC + 1); 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                          cpu.registers.PC -= bytes;  } } // bytes will be added after execution
void ADD_HL_SP_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.SP); }       // 0x39
void LD_A_mHLm_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.HL);        // 0x3A
                                                      cpu.dec_16bit_reg(cpu.registers.HL); }
void    DEC_SP_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.SP);  }                    // 0x3B
void     INC_A_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.A);  }                      // 0x3C
void     DEC_A_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.A);  }                      // 0x3D
void   LD_A_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_u8(cpu.registers.PC + 1);  } // 0x3E 
void       CCF_In::op(LR35902& cpu, Memory& memory) { cpu.registers.clear_n(); cpu.registers.clear_h();          // 0x3F complement carry
                                                      if(cpu.registers.c()) cpu.registers.clear_c(); 
                                                      else                  cpu.registers.set_c(); } 

// =================================================================================================
// OpCodes 0x40 - 0x4F
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

#endif