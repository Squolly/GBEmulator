#include "InstructionSet_PrefixCB.hpp"

#include "Memory.hpp"
#include "LR35902.hpp"

const bool VERBOSE_FLAG = false; 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

   CB_RLC_B_In::CB_RLC_B_In()        : Instruction("RLC",   "RLC B", "Z00C", 0x00, 2,  8, VERBOSE_FLAG) { } // 0xCB 00
   CB_RLC_C_In::CB_RLC_C_In()        : Instruction("RLC",   "RLC C", "Z00C", 0x01, 2,  8, VERBOSE_FLAG) { } // 0xCB 01
   CB_RLC_D_In::CB_RLC_D_In()        : Instruction("RLC",   "RLC D", "Z00C", 0x02, 2,  8, VERBOSE_FLAG) { } // 0xCB 02
   CB_RLC_E_In::CB_RLC_E_In()        : Instruction("RLC",   "RLC E", "Z00C", 0x03, 2,  8, VERBOSE_FLAG) { } // 0xCB 03
   CB_RLC_H_In::CB_RLC_H_In()        : Instruction("RLC",   "RLC H", "Z00C", 0x04, 2,  8, VERBOSE_FLAG) { } // 0xCB 04
   CB_RLC_L_In::CB_RLC_L_In()        : Instruction("RLC",   "RLC L", "Z00C", 0x05, 2,  8, VERBOSE_FLAG) { } // 0xCB 05
 CB_RLC_mHL_In::CB_RLC_mHL_In()      : Instruction("RLC","RLC (HL)", "Z00C", 0x06, 2, 16, VERBOSE_FLAG) { } // 0xCB 06
   CB_RLC_A_In::CB_RLC_A_In()        : Instruction("RLC",   "RLC A", "Z00C", 0x07, 2,  8, VERBOSE_FLAG) { } // 0xCB 07
   CB_RRC_B_In::CB_RRC_B_In()        : Instruction("RRC",   "RLC B", "Z00C", 0x08, 2,  8, VERBOSE_FLAG) { } // 0xCB 08
   CB_RRC_C_In::CB_RRC_C_In()        : Instruction("RRC",   "RLC C", "Z00C", 0x09, 2,  8, VERBOSE_FLAG) { } // 0xCB 09
   CB_RRC_D_In::CB_RRC_D_In()        : Instruction("RRC",   "RLC D", "Z00C", 0x0A, 2,  8, VERBOSE_FLAG) { } // 0xCB 0A
   CB_RRC_E_In::CB_RRC_E_In()        : Instruction("RRC",   "RLC E", "Z00C", 0x0B, 2,  8, VERBOSE_FLAG) { } // 0xCB 0B
   CB_RRC_H_In::CB_RRC_H_In()        : Instruction("RRC",   "RLC H", "Z00C", 0x0C, 2,  8, VERBOSE_FLAG) { } // 0xCB 0C
   CB_RRC_L_In::CB_RRC_L_In()        : Instruction("RRC",   "RLC L", "Z00C", 0x0D, 2,  8, VERBOSE_FLAG) { } // 0xCB 0D
 CB_RRC_mHL_In::CB_RRC_mHL_In()      : Instruction("RRC","RLC (HL)", "Z00C", 0x0E, 2, 16, VERBOSE_FLAG) { } // 0xCB 0E
   CB_RRC_A_In::CB_RRC_A_In()        : Instruction("RRC",   "RLC A", "Z00C", 0x0F, 2,  8, VERBOSE_FLAG) { } // 0xCB 0F

// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================

   CB_RL_B_In::CB_RL_B_In()         : Instruction(  "RL",   "RL B", "Z00C", 0x10, 2,  8, VERBOSE_FLAG) { } // 0xCB 10
   CB_RL_C_In::CB_RL_C_In()         : Instruction(  "RL",   "RL C", "Z00C", 0x11, 2,  8, VERBOSE_FLAG) { } // 0xCB 11
   CB_RL_D_In::CB_RL_D_In()         : Instruction(  "RL",   "RL D", "Z00C", 0x12, 2,  8, VERBOSE_FLAG) { } // 0xCB 12
   CB_RL_E_In::CB_RL_E_In()         : Instruction(  "RL",   "RL E", "Z00C", 0x13, 2,  8, VERBOSE_FLAG) { } // 0xCB 13
   CB_RL_H_In::CB_RL_H_In()         : Instruction(  "RL",   "RL H", "Z00C", 0x14, 2,  8, VERBOSE_FLAG) { } // 0xCB 14
   CB_RL_L_In::CB_RL_L_In()         : Instruction(  "RL",   "RL L", "Z00C", 0x15, 2,  8, VERBOSE_FLAG) { } // 0xCB 15
 CB_RL_mHL_In::CB_RL_mHL_In()       : Instruction(  "RL","RL (HL)", "Z00C", 0x16, 2, 16, VERBOSE_FLAG) { } // 0xCB 16
   CB_RL_A_In::CB_RL_A_In()         : Instruction(  "RL",   "RL A", "Z00C", 0x17, 2,  8, VERBOSE_FLAG) { } // 0xCB 17
   CB_RR_B_In::CB_RR_B_In()         : Instruction(  "RR",   "RL B", "Z00C", 0x18, 2,  8, VERBOSE_FLAG) { } // 0xCB 18
   CB_RR_C_In::CB_RR_C_In()         : Instruction(  "RR",   "RL C", "Z00C", 0x19, 2,  8, VERBOSE_FLAG) { } // 0xCB 19
   CB_RR_D_In::CB_RR_D_In()         : Instruction(  "RR",   "RL D", "Z00C", 0x1A, 2,  8, VERBOSE_FLAG) { } // 0xCB 1A
   CB_RR_E_In::CB_RR_E_In()         : Instruction(  "RR",   "RL E", "Z00C", 0x1B, 2,  8, VERBOSE_FLAG) { } // 0xCB 1B
   CB_RR_H_In::CB_RR_H_In()         : Instruction(  "RR",   "RL H", "Z00C", 0x1C, 2,  8, VERBOSE_FLAG) { } // 0xCB 1C
   CB_RR_L_In::CB_RR_L_In()         : Instruction(  "RR",   "RL L", "Z00C", 0x1D, 2,  8, VERBOSE_FLAG) { } // 0xCB 1D
 CB_RR_mHL_In::CB_RR_mHL_In()       : Instruction(  "RR","RL (HL)", "Z00C", 0x1E, 2, 16, VERBOSE_FLAG) { } // 0xCB 1E
   CB_RR_A_In::CB_RR_A_In()         : Instruction(  "RR",   "RL A", "Z00C", 0x1F, 2,  8, VERBOSE_FLAG) { } // 0xCB 1F
   
// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

  CB_SLA_B_In::CB_SLA_B_In()        : Instruction("SLA",   "SLA B", "Z00C", 0x20, 2,  8, VERBOSE_FLAG) { } // 0xCB 20
  CB_SLA_C_In::CB_SLA_C_In()        : Instruction("SLA",   "SLA C", "Z00C", 0x21, 2,  8, VERBOSE_FLAG) { } // 0xCB 21
  CB_SLA_D_In::CB_SLA_D_In()        : Instruction("SLA",   "SLA D", "Z00C", 0x22, 2,  8, VERBOSE_FLAG) { } // 0xCB 22
  CB_SLA_E_In::CB_SLA_E_In()        : Instruction("SLA",   "SLA E", "Z00C", 0x23, 2,  8, VERBOSE_FLAG) { } // 0xCB 23
  CB_SLA_H_In::CB_SLA_H_In()        : Instruction("SLA",   "SLA H", "Z00C", 0x24, 2,  8, VERBOSE_FLAG) { } // 0xCB 24
  CB_SLA_L_In::CB_SLA_L_In()        : Instruction("SLA",   "SLA L", "Z00C", 0x25, 2,  8, VERBOSE_FLAG) { } // 0xCB 25
CB_SLA_mHL_In::CB_SLA_mHL_In()      : Instruction("SLA","SLA (HL)", "Z00C", 0x26, 2, 16, VERBOSE_FLAG) { } // 0xCB 26
  CB_SLA_A_In::CB_SLA_A_In()        : Instruction("SLA",   "SLA A", "Z00C", 0x27, 2,  8, VERBOSE_FLAG) { } // 0xCB 27
  CB_SRA_B_In::CB_SRA_B_In()        : Instruction("SRA",   "SRA B", "Z000", 0x28, 2,  8, VERBOSE_FLAG) { } // 0xCB 28
  CB_SRA_C_In::CB_SRA_C_In()        : Instruction("SRA",   "SRA C", "Z000", 0x29, 2,  8, VERBOSE_FLAG) { } // 0xCB 29
  CB_SRA_D_In::CB_SRA_D_In()        : Instruction("SRA",   "SRA D", "Z000", 0x2A, 2,  8, VERBOSE_FLAG) { } // 0xCB 2A
  CB_SRA_E_In::CB_SRA_E_In()        : Instruction("SRA",   "SRA E", "Z000", 0x2B, 2,  8, VERBOSE_FLAG) { } // 0xCB 2B
  CB_SRA_H_In::CB_SRA_H_In()        : Instruction("SRA",   "SRA H", "Z000", 0x2C, 2,  8, VERBOSE_FLAG) { } // 0xCB 2C
  CB_SRA_L_In::CB_SRA_L_In()        : Instruction("SRA",   "SRA L", "Z000", 0x2D, 2,  8, VERBOSE_FLAG) { } // 0xCB 2D
CB_SRA_mHL_In::CB_SRA_mHL_In()      : Instruction("SRA","SRA (HL)", "Z000", 0x2E, 2, 16, VERBOSE_FLAG) { } // 0xCB 2E
  CB_SRA_A_In::CB_SRA_A_In()        : Instruction("SRA",   "SRA A", "Z000", 0x2F, 2,  8, VERBOSE_FLAG) { } // 0xCB 2F
  
// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

  CB_SWAP_B_In::CB_SWAP_B_In()      : Instruction("SWAP",   "SWAP B", "Z000", 0x30, 2,  8, VERBOSE_FLAG) { } // 0xCB 30
  CB_SWAP_C_In::CB_SWAP_C_In()      : Instruction("SWAP",   "SWAP C", "Z000", 0x31, 2,  8, VERBOSE_FLAG) { } // 0xCB 31
  CB_SWAP_D_In::CB_SWAP_D_In()      : Instruction("SWAP",   "SWAP D", "Z000", 0x32, 2,  8, VERBOSE_FLAG) { } // 0xCB 32
  CB_SWAP_E_In::CB_SWAP_E_In()      : Instruction("SWAP",   "SWAP E", "Z000", 0x33, 2,  8, VERBOSE_FLAG) { } // 0xCB 33
  CB_SWAP_H_In::CB_SWAP_H_In()      : Instruction("SWAP",   "SWAP H", "Z000", 0x34, 2,  8, VERBOSE_FLAG) { } // 0xCB 34
  CB_SWAP_L_In::CB_SWAP_L_In()      : Instruction("SWAP",   "SWAP L", "Z000", 0x35, 2,  8, VERBOSE_FLAG) { } // 0xCB 35
CB_SWAP_mHL_In::CB_SWAP_mHL_In()    : Instruction("SWAP","SWAP (HL)", "Z000", 0x36, 2, 16, VERBOSE_FLAG) { } // 0xCB 36
  CB_SWAP_A_In::CB_SWAP_A_In()      : Instruction("SWAP",   "SWAP A", "Z000", 0x37, 2,  8, VERBOSE_FLAG) { } // 0xCB 37
   CB_SRL_B_In::CB_SRL_B_In()       : Instruction( "SRL",    "SRL B", "Z00C", 0x38, 2,  8, VERBOSE_FLAG) { } // 0xCB 38
   CB_SRL_C_In::CB_SRL_C_In()       : Instruction( "SRL",    "SRL C", "Z00C", 0x39, 2,  8, VERBOSE_FLAG) { } // 0xCB 39
   CB_SRL_D_In::CB_SRL_D_In()       : Instruction( "SRL",    "SRL D", "Z00C", 0x3A, 2,  8, VERBOSE_FLAG) { } // 0xCB 3A
   CB_SRL_E_In::CB_SRL_E_In()       : Instruction( "SRL",    "SRL E", "Z00C", 0x3B, 2,  8, VERBOSE_FLAG) { } // 0xCB 3B
   CB_SRL_H_In::CB_SRL_H_In()       : Instruction( "SRL",    "SRL H", "Z00C", 0x3C, 2,  8, VERBOSE_FLAG) { } // 0xCB 3C
   CB_SRL_L_In::CB_SRL_L_In()       : Instruction( "SRL",    "SRL L", "Z00C", 0x3D, 2,  8, VERBOSE_FLAG) { } // 0xCB 3D
 CB_SRL_mHL_In::CB_SRL_mHL_In()     : Instruction( "SRL", "SRL (HL)", "Z00C", 0x3E, 2, 16, VERBOSE_FLAG) { } // 0xCB 3E
   CB_SRL_A_In::CB_SRL_A_In()       : Instruction( "SRL",    "SRL A", "Z00C", 0x3F, 2,  8, VERBOSE_FLAG) { } // 0xCB 3F
   
   
   

// Implementation of OpCode functionallity 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

void   CB_RLC_B_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.B); }                 // 0xCB 00
void   CB_RLC_C_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.C); }                 // 0xCB 01
void   CB_RLC_D_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.D); }                 // 0xCB 02
void   CB_RLC_E_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.E); }                 // 0xCB 03
void   CB_RLC_H_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.H); }                 // 0xCB 04
void   CB_RLC_L_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.L); }                 // 0xCB 05
void CB_RLC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.rlc(v);  memory.write_8(cpu.registers.HL, v);} // 0xCB 06
void   CB_RLC_A_In::op(LR35902& cpu, Memory& memory) { cpu.rlc(cpu.registers.A); }                 // 0xCB 07
void   CB_RRC_B_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.B); }                 // 0xCB 08
void   CB_RRC_C_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.C); }                 // 0xCB 09
void   CB_RRC_D_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.D); }                 // 0xCB 0A
void   CB_RRC_E_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.E); }                 // 0xCB 0B
void   CB_RRC_H_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.H); }                 // 0xCB 0C
void   CB_RRC_L_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.L); }                 // 0xCB 0D
void CB_RRC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.rrc(v);  memory.write_8(cpu.registers.HL, v);} // 0xCB 0E
void   CB_RRC_A_In::op(LR35902& cpu, Memory& memory) { cpu.rrc(cpu.registers.A); }                 // 0xCB 0F

// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================

void    CB_RL_B_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.B); }                 // 0xCB 10
void    CB_RL_C_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.C); }                 // 0xCB 11
void    CB_RL_D_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.D); }                 // 0xCB 12
void    CB_RL_E_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.E); }                 // 0xCB 13
void    CB_RL_H_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.H); }                 // 0xCB 14
void    CB_RL_L_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.L); }                 // 0xCB 15
void  CB_RL_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.rl(v);  memory.write_8(cpu.registers.HL, v);} // 0xCB 16
void    CB_RL_A_In::op(LR35902& cpu, Memory& memory) { cpu.rl(cpu.registers.A); }                 // 0xCB 17
void    CB_RR_B_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.B); }                 // 0xCB 18
void    CB_RR_C_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.C); }                 // 0xCB 19
void    CB_RR_D_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.D); }                 // 0xCB 1A
void    CB_RR_E_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.E); }                 // 0xCB 1B
void    CB_RR_H_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.H); }                 // 0xCB 1C
void    CB_RR_L_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.L); }                 // 0xCB 1D
void  CB_RR_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.rr(v); memory.write_8(cpu.registers.HL, v);} // 0xCB 1E
void    CB_RR_A_In::op(LR35902& cpu, Memory& memory) { cpu.rr(cpu.registers.A); }                 // 0xCB 1F

// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

void   CB_SLA_B_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.B); }                 // 0xCB 20
void   CB_SLA_C_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.C); }                 // 0xCB 21
void   CB_SLA_D_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.D); }                 // 0xCB 22
void   CB_SLA_E_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.E); }                 // 0xCB 23
void   CB_SLA_H_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.H); }                 // 0xCB 24
void   CB_SLA_L_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.L); }                 // 0xCB 25
void CB_SLA_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.sla(v); memory.write_8(cpu.registers.HL, v);} // 0xCB 26
void   CB_SLA_A_In::op(LR35902& cpu, Memory& memory) { cpu.sla(cpu.registers.A); }                 // 0xCB 27
void   CB_SRA_B_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.B); }                 // 0xCB 28
void   CB_SRA_C_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.C); }                 // 0xCB 29
void   CB_SRA_D_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.D); }                 // 0xCB 2A
void   CB_SRA_E_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.E); }                 // 0xCB 2B
void   CB_SRA_H_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.H); }                 // 0xCB 2C
void   CB_SRA_L_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.L); }                 // 0xCB 2D
void CB_SRA_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.sra(v); memory.write_8(cpu.registers.HL, v);} // 0xCB 2E
void   CB_SRA_A_In::op(LR35902& cpu, Memory& memory) { cpu.sra(cpu.registers.A); }                 // 0xCB 2F

// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

void   CB_SWAP_B_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.B); }                // 0xCB 30
void   CB_SWAP_C_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.C); }                // 0xCB 31
void   CB_SWAP_D_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.D); }                // 0xCB 32
void   CB_SWAP_E_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.E); }                // 0xCB 33
void   CB_SWAP_H_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.H); }                // 0xCB 34
void   CB_SWAP_L_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.L); }                // 0xCB 35
void CB_SWAP_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.swap(v); memory.write_8(cpu.registers.HL, v);} // 0xCB 36
void   CB_SWAP_A_In::op(LR35902& cpu, Memory& memory) { cpu.swap(cpu.registers.A); }                // 0xCB 37
void    CB_SRL_B_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.B); }                 // 0xCB 38
void    CB_SRL_C_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.C); }                 // 0xCB 39
void    CB_SRL_D_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.D); }                 // 0xCB 3A
void    CB_SRL_E_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.E); }                 // 0xCB 3B
void    CB_SRL_H_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.H); }                 // 0xCB 3C
void    CB_SRL_L_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.L); }                 // 0xCB 3D
void  CB_SRL_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.srl(v); memory.write_8(cpu.registers.HL, v);} // 0xCB 3E
void    CB_SRL_A_In::op(LR35902& cpu, Memory& memory) { cpu.srl(cpu.registers.A); }                 // 0xCB 3F