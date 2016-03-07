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
   CB_RRC_B_In::CB_RRC_B_In()        : Instruction("RRC",   "RRC B", "Z00C", 0x08, 2,  8, VERBOSE_FLAG) { } // 0xCB 08
   CB_RRC_C_In::CB_RRC_C_In()        : Instruction("RRC",   "RRC C", "Z00C", 0x09, 2,  8, VERBOSE_FLAG) { } // 0xCB 09
   CB_RRC_D_In::CB_RRC_D_In()        : Instruction("RRC",   "RRC D", "Z00C", 0x0A, 2,  8, VERBOSE_FLAG) { } // 0xCB 0A
   CB_RRC_E_In::CB_RRC_E_In()        : Instruction("RRC",   "RRC E", "Z00C", 0x0B, 2,  8, VERBOSE_FLAG) { } // 0xCB 0B
   CB_RRC_H_In::CB_RRC_H_In()        : Instruction("RRC",   "RRC H", "Z00C", 0x0C, 2,  8, VERBOSE_FLAG) { } // 0xCB 0C
   CB_RRC_L_In::CB_RRC_L_In()        : Instruction("RRC",   "RRC L", "Z00C", 0x0D, 2,  8, VERBOSE_FLAG) { } // 0xCB 0D
 CB_RRC_mHL_In::CB_RRC_mHL_In()      : Instruction("RRC","RRC (HL)", "Z00C", 0x0E, 2, 16, VERBOSE_FLAG) { } // 0xCB 0E
   CB_RRC_A_In::CB_RRC_A_In()        : Instruction("RRC",   "RRC A", "Z00C", 0x0F, 2,  8, VERBOSE_FLAG) { } // 0xCB 0F

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
   CB_RR_B_In::CB_RR_B_In()         : Instruction(  "RR",   "RR B", "Z00C", 0x18, 2,  8, VERBOSE_FLAG) { } // 0xCB 18
   CB_RR_C_In::CB_RR_C_In()         : Instruction(  "RR",   "RR C", "Z00C", 0x19, 2,  8, VERBOSE_FLAG) { } // 0xCB 19
   CB_RR_D_In::CB_RR_D_In()         : Instruction(  "RR",   "RR D", "Z00C", 0x1A, 2,  8, VERBOSE_FLAG) { } // 0xCB 1A
   CB_RR_E_In::CB_RR_E_In()         : Instruction(  "RR",   "RR E", "Z00C", 0x1B, 2,  8, VERBOSE_FLAG) { } // 0xCB 1B
   CB_RR_H_In::CB_RR_H_In()         : Instruction(  "RR",   "RR H", "Z00C", 0x1C, 2,  8, VERBOSE_FLAG) { } // 0xCB 1C
   CB_RR_L_In::CB_RR_L_In()         : Instruction(  "RR",   "RR L", "Z00C", 0x1D, 2,  8, VERBOSE_FLAG) { } // 0xCB 1D
 CB_RR_mHL_In::CB_RR_mHL_In()       : Instruction(  "RR","RR (HL)", "Z00C", 0x1E, 2, 16, VERBOSE_FLAG) { } // 0xCB 1E
   CB_RR_A_In::CB_RR_A_In()         : Instruction(  "RR",   "RR A", "Z00C", 0x1F, 2,  8, VERBOSE_FLAG) { } // 0xCB 1F
   
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

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

   BIT_0_B_In::BIT_0_B_In()         : Instruction( "BIT",   "BIT 0, B", "Z01-", 0x40, 2,  8, VERBOSE_FLAG) { } // 0xCB 40
   BIT_0_C_In::BIT_0_C_In()         : Instruction( "BIT",   "BIT 0, C", "Z01-", 0x41, 2,  8, VERBOSE_FLAG) { } // 0xCB 41
   BIT_0_D_In::BIT_0_D_In()         : Instruction( "BIT",   "BIT 0, D", "Z01-", 0x42, 2,  8, VERBOSE_FLAG) { } // 0xCB 42
   BIT_0_E_In::BIT_0_E_In()         : Instruction( "BIT",   "BIT 0, E", "Z01-", 0x43, 2,  8, VERBOSE_FLAG) { } // 0xCB 43
   BIT_0_H_In::BIT_0_H_In()         : Instruction( "BIT",   "BIT 0, H", "Z01-", 0x44, 2,  8, VERBOSE_FLAG) { } // 0xCB 44
   BIT_0_L_In::BIT_0_L_In()         : Instruction( "BIT",   "BIT 0, L", "Z01-", 0x45, 2,  8, VERBOSE_FLAG) { } // 0xCB 45
 BIT_0_mHL_In::BIT_0_mHL_In()       : Instruction( "BIT","BIT 0, (HL)", "Z01-", 0x46, 2, 16, VERBOSE_FLAG) { } // 0xCB 46
   BIT_0_A_In::BIT_0_A_In()         : Instruction( "BIT",   "BIT 0, A", "Z01-", 0x47, 2,  8, VERBOSE_FLAG) { } // 0xCB 47
   BIT_1_B_In::BIT_1_B_In()         : Instruction( "BIT",   "BIT 1, B", "Z01-", 0x48, 2,  8, VERBOSE_FLAG) { } // 0xCB 48
   BIT_1_C_In::BIT_1_C_In()         : Instruction( "BIT",   "BIT 1, C", "Z01-", 0x49, 2,  8, VERBOSE_FLAG) { } // 0xCB 49
   BIT_1_D_In::BIT_1_D_In()         : Instruction( "BIT",   "BIT 1, D", "Z01-", 0x4A, 2,  8, VERBOSE_FLAG) { } // 0xCB 4A
   BIT_1_E_In::BIT_1_E_In()         : Instruction( "BIT",   "BIT 1, E", "Z01-", 0x4B, 2,  8, VERBOSE_FLAG) { } // 0xCB 4B
   BIT_1_H_In::BIT_1_H_In()         : Instruction( "BIT",   "BIT 1, H", "Z01-", 0x4C, 2,  8, VERBOSE_FLAG) { } // 0xCB 4C
   BIT_1_L_In::BIT_1_L_In()         : Instruction( "BIT",   "BIT 1, L", "Z01-", 0x4D, 2,  8, VERBOSE_FLAG) { } // 0xCB 4D
 BIT_1_mHL_In::BIT_1_mHL_In()       : Instruction( "BIT","BIT 1, (HL)", "Z01-", 0x4E, 2, 16, VERBOSE_FLAG) { } // 0xCB 4E
   BIT_1_A_In::BIT_1_A_In()         : Instruction( "BIT",   "BIT 1, A", "Z01-", 0x4F, 2,  8, VERBOSE_FLAG) { } // 0xCB 4F
   
// =================================================================================================
// OpCodes 0x50 - 0x5F
// =================================================================================================

   BIT_2_B_In::BIT_2_B_In()         : Instruction(  "BIT",   "BIT 2,B", "Z01-", 0x50, 2,  8, VERBOSE_FLAG) { } // 0xCB 50
   BIT_2_C_In::BIT_2_C_In()         : Instruction(  "BIT",   "BIT 2,C", "Z01-", 0x51, 2,  8, VERBOSE_FLAG) { } // 0xCB 51
   BIT_2_D_In::BIT_2_D_In()         : Instruction(  "BIT",   "BIT 2,D", "Z01-", 0x52, 2,  8, VERBOSE_FLAG) { } // 0xCB 52
   BIT_2_E_In::BIT_2_E_In()         : Instruction(  "BIT",   "BIT 2,E", "Z01-", 0x53, 2,  8, VERBOSE_FLAG) { } // 0xCB 53
   BIT_2_H_In::BIT_2_H_In()         : Instruction(  "BIT",   "BIT 2,H", "Z01-", 0x54, 2,  8, VERBOSE_FLAG) { } // 0xCB 54
   BIT_2_L_In::BIT_2_L_In()         : Instruction(  "BIT",   "BIT 2,L", "Z01-", 0x55, 2,  8, VERBOSE_FLAG) { } // 0xCB 55
 BIT_2_mHL_In::BIT_2_mHL_In()       : Instruction(  "BIT","BIT 2,(HL)", "Z01-", 0x56, 2, 16, VERBOSE_FLAG) { } // 0xCB 56
   BIT_2_A_In::BIT_2_A_In()         : Instruction(  "BIT",   "BIT 2,A", "Z01-", 0x57, 2,  8, VERBOSE_FLAG) { } // 0xCB 57
   BIT_3_B_In::BIT_3_B_In()         : Instruction(  "BIT",   "BIT 3,B", "Z01-", 0x58, 2,  8, VERBOSE_FLAG) { } // 0xCB 58
   BIT_3_C_In::BIT_3_C_In()         : Instruction(  "BIT",   "BIT 3,C", "Z01-", 0x59, 2,  8, VERBOSE_FLAG) { } // 0xCB 59
   BIT_3_D_In::BIT_3_D_In()         : Instruction(  "BIT",   "BIT 3,D", "Z01-", 0x5A, 2,  8, VERBOSE_FLAG) { } // 0xCB 5A
   BIT_3_E_In::BIT_3_E_In()         : Instruction(  "BIT",   "BIT 3,E", "Z01-", 0x5B, 2,  8, VERBOSE_FLAG) { } // 0xCB 5B
   BIT_3_H_In::BIT_3_H_In()         : Instruction(  "BIT",   "BIT 3,H", "Z01-", 0x5C, 2,  8, VERBOSE_FLAG) { } // 0xCB 5C
   BIT_3_L_In::BIT_3_L_In()         : Instruction(  "BIT",   "BIT 3,L", "Z01-", 0x5D, 2,  8, VERBOSE_FLAG) { } // 0xCB 5D
 BIT_3_mHL_In::BIT_3_mHL_In()       : Instruction(  "BIT","BIT 3,(HL)", "Z01-", 0x5E, 2, 16, VERBOSE_FLAG) { } // 0xCB 5E
   BIT_3_A_In::BIT_3_A_In()         : Instruction(  "BIT",   "BIT 3,A", "Z01-", 0x5F, 2,  8, VERBOSE_FLAG) { } // 0xCB 5F
   
// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

   BIT_4_B_In::BIT_4_B_In()         : Instruction( "BIT",   "BIT 4, B", "Z01-", 0x60, 2,  8, VERBOSE_FLAG) { } // 0xCB 60
   BIT_4_C_In::BIT_4_C_In()         : Instruction( "BIT",   "BIT 4, C", "Z01-", 0x61, 2,  8, VERBOSE_FLAG) { } // 0xCB 61
   BIT_4_D_In::BIT_4_D_In()         : Instruction( "BIT",   "BIT 4, D", "Z01-", 0x62, 2,  8, VERBOSE_FLAG) { } // 0xCB 62
   BIT_4_E_In::BIT_4_E_In()         : Instruction( "BIT",   "BIT 4, E", "Z01-", 0x63, 2,  8, VERBOSE_FLAG) { } // 0xCB 63
   BIT_4_H_In::BIT_4_H_In()         : Instruction( "BIT",   "BIT 4, H", "Z01-", 0x64, 2,  8, VERBOSE_FLAG) { } // 0xCB 64
   BIT_4_L_In::BIT_4_L_In()         : Instruction( "BIT",   "BIT 4, L", "Z01-", 0x65, 2,  8, VERBOSE_FLAG) { } // 0xCB 65
 BIT_4_mHL_In::BIT_4_mHL_In()       : Instruction( "BIT","BIT 4, (HL)", "Z01-", 0x66, 2, 16, VERBOSE_FLAG) { } // 0xCB 66
   BIT_4_A_In::BIT_4_A_In()         : Instruction( "BIT",   "BIT 4, A", "Z01-", 0x67, 2,  8, VERBOSE_FLAG) { } // 0xCB 67
   BIT_5_B_In::BIT_5_B_In()         : Instruction( "BIT",   "BIT 5, B", "Z01-", 0x68, 2,  8, VERBOSE_FLAG) { } // 0xCB 68
   BIT_5_C_In::BIT_5_C_In()         : Instruction( "BIT",   "BIT 5, C", "Z01-", 0x69, 2,  8, VERBOSE_FLAG) { } // 0xCB 69
   BIT_5_D_In::BIT_5_D_In()         : Instruction( "BIT",   "BIT 5, D", "Z01-", 0x6A, 2,  8, VERBOSE_FLAG) { } // 0xCB 6A
   BIT_5_E_In::BIT_5_E_In()         : Instruction( "BIT",   "BIT 5, E", "Z01-", 0x6B, 2,  8, VERBOSE_FLAG) { } // 0xCB 6B
   BIT_5_H_In::BIT_5_H_In()         : Instruction( "BIT",   "BIT 5, H", "Z01-", 0x6C, 2,  8, VERBOSE_FLAG) { } // 0xCB 6C
   BIT_5_L_In::BIT_5_L_In()         : Instruction( "BIT",   "BIT 5, L", "Z01-", 0x6D, 2,  8, VERBOSE_FLAG) { } // 0xCB 6D
 BIT_5_mHL_In::BIT_5_mHL_In()       : Instruction( "BIT","BIT 5, (HL)", "Z01-", 0x6E, 2, 16, VERBOSE_FLAG) { } // 0xCB 6E
   BIT_5_A_In::BIT_5_A_In()         : Instruction( "BIT",   "BIT 5, A", "Z01-", 0x6F, 2,  8, VERBOSE_FLAG) { } // 0xCB 6F
   
// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

   BIT_6_B_In::BIT_6_B_In()         : Instruction( "BIT",   "BIT 6, B", "Z01-", 0x70, 2,  8, VERBOSE_FLAG) { } // 0xCB 70
   BIT_6_C_In::BIT_6_C_In()         : Instruction( "BIT",   "BIT 6, C", "Z01-", 0x71, 2,  8, VERBOSE_FLAG) { } // 0xCB 71
   BIT_6_D_In::BIT_6_D_In()         : Instruction( "BIT",   "BIT 6, D", "Z01-", 0x72, 2,  8, VERBOSE_FLAG) { } // 0xCB 72
   BIT_6_E_In::BIT_6_E_In()         : Instruction( "BIT",   "BIT 6, E", "Z01-", 0x73, 2,  8, VERBOSE_FLAG) { } // 0xCB 73
   BIT_6_H_In::BIT_6_H_In()         : Instruction( "BIT",   "BIT 6, H", "Z01-", 0x74, 2,  8, VERBOSE_FLAG) { } // 0xCB 74
   BIT_6_L_In::BIT_6_L_In()         : Instruction( "BIT",   "BIT 6, L", "Z01-", 0x75, 2,  8, VERBOSE_FLAG) { } // 0xCB 75
 BIT_6_mHL_In::BIT_6_mHL_In()       : Instruction( "BIT","BIT 6, (HL)", "Z01-", 0x76, 2, 16, VERBOSE_FLAG) { } // 0xCB 76
   BIT_6_A_In::BIT_6_A_In()         : Instruction( "BIT",   "BIT 6, A", "Z01-", 0x77, 2,  8, VERBOSE_FLAG) { } // 0xCB 77
   BIT_7_B_In::BIT_7_B_In()         : Instruction( "BIT",   "BIT 7, B", "Z01-", 0x78, 2,  8, VERBOSE_FLAG) { } // 0xCB 78
   BIT_7_C_In::BIT_7_C_In()         : Instruction( "BIT",   "BIT 7, C", "Z01-", 0x79, 2,  8, VERBOSE_FLAG) { } // 0xCB 79
   BIT_7_D_In::BIT_7_D_In()         : Instruction( "BIT",   "BIT 7, D", "Z01-", 0x7A, 2,  8, VERBOSE_FLAG) { } // 0xCB 7A
   BIT_7_E_In::BIT_7_E_In()         : Instruction( "BIT",   "BIT 7, E", "Z01-", 0x7B, 2,  8, VERBOSE_FLAG) { } // 0xCB 7B
   BIT_7_H_In::BIT_7_H_In()         : Instruction( "BIT",   "BIT 7, H", "Z01-", 0x7C, 2,  8, VERBOSE_FLAG) { } // 0xCB 7C
   BIT_7_L_In::BIT_7_L_In()         : Instruction( "BIT",   "BIT 7, L", "Z01-", 0x7D, 2,  8, VERBOSE_FLAG) { } // 0xCB 7D
 BIT_7_mHL_In::BIT_7_mHL_In()       : Instruction( "BIT","BIT 7, (HL)", "Z01-", 0x7E, 2, 16, VERBOSE_FLAG) { } // 0xCB 7E
   BIT_7_A_In::BIT_7_A_In()         : Instruction( "BIT",   "BIT 7, A", "Z01-", 0x7F, 2,  8, VERBOSE_FLAG) { } // 0xCB 7F

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

   RES_0_B_In::RES_0_B_In()         : Instruction( "RES",   "RES 0, B", "----", 0x80, 2,  8, VERBOSE_FLAG) { } // 0xCB 80
   RES_0_C_In::RES_0_C_In()         : Instruction( "RES",   "RES 0, C", "----", 0x81, 2,  8, VERBOSE_FLAG) { } // 0xCB 81
   RES_0_D_In::RES_0_D_In()         : Instruction( "RES",   "RES 0, D", "----", 0x82, 2,  8, VERBOSE_FLAG) { } // 0xCB 82
   RES_0_E_In::RES_0_E_In()         : Instruction( "RES",   "RES 0, E", "----", 0x83, 2,  8, VERBOSE_FLAG) { } // 0xCB 83
   RES_0_H_In::RES_0_H_In()         : Instruction( "RES",   "RES 0, H", "----", 0x84, 2,  8, VERBOSE_FLAG) { } // 0xCB 84
   RES_0_L_In::RES_0_L_In()         : Instruction( "RES",   "RES 0, L", "----", 0x85, 2,  8, VERBOSE_FLAG) { } // 0xCB 85
 RES_0_mHL_In::RES_0_mHL_In()       : Instruction( "RES","RES 0, (HL)", "----", 0x86, 2, 16, VERBOSE_FLAG) { } // 0xCB 86
   RES_0_A_In::RES_0_A_In()         : Instruction( "RES",   "RES 0, A", "----", 0x87, 2,  8, VERBOSE_FLAG) { } // 0xCB 87
   RES_1_B_In::RES_1_B_In()         : Instruction( "RES",   "RES 1, B", "----", 0x88, 2,  8, VERBOSE_FLAG) { } // 0xCB 88
   RES_1_C_In::RES_1_C_In()         : Instruction( "RES",   "RES 1, C", "----", 0x89, 2,  8, VERBOSE_FLAG) { } // 0xCB 89
   RES_1_D_In::RES_1_D_In()         : Instruction( "RES",   "RES 1, D", "----", 0x8A, 2,  8, VERBOSE_FLAG) { } // 0xCB 8A
   RES_1_E_In::RES_1_E_In()         : Instruction( "RES",   "RES 1, E", "----", 0x8B, 2,  8, VERBOSE_FLAG) { } // 0xCB 8B
   RES_1_H_In::RES_1_H_In()         : Instruction( "RES",   "RES 1, H", "----", 0x8C, 2,  8, VERBOSE_FLAG) { } // 0xCB 8C
   RES_1_L_In::RES_1_L_In()         : Instruction( "RES",   "RES 1, L", "----", 0x8D, 2,  8, VERBOSE_FLAG) { } // 0xCB 8D
 RES_1_mHL_In::RES_1_mHL_In()       : Instruction( "RES","RES 1, (HL)", "----", 0x8E, 2, 16, VERBOSE_FLAG) { } // 0xCB 8E
   RES_1_A_In::RES_1_A_In()         : Instruction( "RES",   "RES 1, A", "----", 0x8F, 2,  8, VERBOSE_FLAG) { } // 0xCB 8F
   
// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

   RES_2_B_In::RES_2_B_In()         : Instruction(  "RES",   "RES 2,B", "----", 0x90, 2,  8, VERBOSE_FLAG) { } // 0xCB 90
   RES_2_C_In::RES_2_C_In()         : Instruction(  "RES",   "RES 2,C", "----", 0x91, 2,  8, VERBOSE_FLAG) { } // 0xCB 91
   RES_2_D_In::RES_2_D_In()         : Instruction(  "RES",   "RES 2,D", "----", 0x92, 2,  8, VERBOSE_FLAG) { } // 0xCB 92
   RES_2_E_In::RES_2_E_In()         : Instruction(  "RES",   "RES 2,E", "----", 0x93, 2,  8, VERBOSE_FLAG) { } // 0xCB 93
   RES_2_H_In::RES_2_H_In()         : Instruction(  "RES",   "RES 2,H", "----", 0x94, 2,  8, VERBOSE_FLAG) { } // 0xCB 94
   RES_2_L_In::RES_2_L_In()         : Instruction(  "RES",   "RES 2,L", "----", 0x95, 2,  8, VERBOSE_FLAG) { } // 0xCB 95
 RES_2_mHL_In::RES_2_mHL_In()       : Instruction(  "RES","RES 2,(HL)", "----", 0x96, 2, 16, VERBOSE_FLAG) { } // 0xCB 96
   RES_2_A_In::RES_2_A_In()         : Instruction(  "RES",   "RES 2,A", "----", 0x97, 2,  8, VERBOSE_FLAG) { } // 0xCB 97
   RES_3_B_In::RES_3_B_In()         : Instruction(  "RES",   "RES 3,B", "----", 0x98, 2,  8, VERBOSE_FLAG) { } // 0xCB 98
   RES_3_C_In::RES_3_C_In()         : Instruction(  "RES",   "RES 3,C", "----", 0x99, 2,  8, VERBOSE_FLAG) { } // 0xCB 99
   RES_3_D_In::RES_3_D_In()         : Instruction(  "RES",   "RES 3,D", "----", 0x9A, 2,  8, VERBOSE_FLAG) { } // 0xCB 9A
   RES_3_E_In::RES_3_E_In()         : Instruction(  "RES",   "RES 3,E", "----", 0x9B, 2,  8, VERBOSE_FLAG) { } // 0xCB 9B
   RES_3_H_In::RES_3_H_In()         : Instruction(  "RES",   "RES 3,H", "----", 0x9C, 2,  8, VERBOSE_FLAG) { } // 0xCB 9C
   RES_3_L_In::RES_3_L_In()         : Instruction(  "RES",   "RES 3,L", "----", 0x9D, 2,  8, VERBOSE_FLAG) { } // 0xCB 9D
 RES_3_mHL_In::RES_3_mHL_In()       : Instruction(  "RES","RES 3,(HL)", "----", 0x9E, 2, 16, VERBOSE_FLAG) { } // 0xCB 9E
   RES_3_A_In::RES_3_A_In()         : Instruction(  "RES",   "RES 3,A", "----", 0x9F, 2,  8, VERBOSE_FLAG) { } // 0xCB 9F
   
// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

   RES_4_B_In::RES_4_B_In()         : Instruction( "RES",   "RES 4, B", "----", 0xA0, 2,  8, VERBOSE_FLAG) { } // 0xCB A0
   RES_4_C_In::RES_4_C_In()         : Instruction( "RES",   "RES 4, C", "----", 0xA1, 2,  8, VERBOSE_FLAG) { } // 0xCB A1
   RES_4_D_In::RES_4_D_In()         : Instruction( "RES",   "RES 4, D", "----", 0xA2, 2,  8, VERBOSE_FLAG) { } // 0xCB A2
   RES_4_E_In::RES_4_E_In()         : Instruction( "RES",   "RES 4, E", "----", 0xA3, 2,  8, VERBOSE_FLAG) { } // 0xCB A3
   RES_4_H_In::RES_4_H_In()         : Instruction( "RES",   "RES 4, H", "----", 0xA4, 2,  8, VERBOSE_FLAG) { } // 0xCB A4
   RES_4_L_In::RES_4_L_In()         : Instruction( "RES",   "RES 4, L", "----", 0xA5, 2,  8, VERBOSE_FLAG) { } // 0xCB A5
 RES_4_mHL_In::RES_4_mHL_In()       : Instruction( "RES","RES 4, (HL)", "----", 0xA6, 2, 16, VERBOSE_FLAG) { } // 0xCB A6
   RES_4_A_In::RES_4_A_In()         : Instruction( "RES",   "RES 4, A", "----", 0xA7, 2,  8, VERBOSE_FLAG) { } // 0xCB A7
   RES_5_B_In::RES_5_B_In()         : Instruction( "RES",   "RES 5, B", "----", 0xA8, 2,  8, VERBOSE_FLAG) { } // 0xCB A8
   RES_5_C_In::RES_5_C_In()         : Instruction( "RES",   "RES 5, C", "----", 0xA9, 2,  8, VERBOSE_FLAG) { } // 0xCB A9
   RES_5_D_In::RES_5_D_In()         : Instruction( "RES",   "RES 5, D", "----", 0xAA, 2,  8, VERBOSE_FLAG) { } // 0xCB AA
   RES_5_E_In::RES_5_E_In()         : Instruction( "RES",   "RES 5, E", "----", 0xAB, 2,  8, VERBOSE_FLAG) { } // 0xCB AB
   RES_5_H_In::RES_5_H_In()         : Instruction( "RES",   "RES 5, H", "----", 0xAC, 2,  8, VERBOSE_FLAG) { } // 0xCB AC
   RES_5_L_In::RES_5_L_In()         : Instruction( "RES",   "RES 5, L", "----", 0xAD, 2,  8, VERBOSE_FLAG) { } // 0xCB AD
 RES_5_mHL_In::RES_5_mHL_In()       : Instruction( "RES","RES 5, (HL)", "----", 0xAE, 2, 16, VERBOSE_FLAG) { } // 0xCB AE
   RES_5_A_In::RES_5_A_In()         : Instruction( "RES",   "RES 5, A", "----", 0xAF, 2,  8, VERBOSE_FLAG) { } // 0xCB AF
   
// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

   RES_6_B_In::RES_6_B_In()         : Instruction( "RES",   "RES 6, B", "----", 0xB0, 2,  8, VERBOSE_FLAG) { } // 0xCB B0
   RES_6_C_In::RES_6_C_In()         : Instruction( "RES",   "RES 6, C", "----", 0xB1, 2,  8, VERBOSE_FLAG) { } // 0xCB B1
   RES_6_D_In::RES_6_D_In()         : Instruction( "RES",   "RES 6, D", "----", 0xB2, 2,  8, VERBOSE_FLAG) { } // 0xCB B2
   RES_6_E_In::RES_6_E_In()         : Instruction( "RES",   "RES 6, E", "----", 0xB3, 2,  8, VERBOSE_FLAG) { } // 0xCB B3
   RES_6_H_In::RES_6_H_In()         : Instruction( "RES",   "RES 6, H", "----", 0xB4, 2,  8, VERBOSE_FLAG) { } // 0xCB B4
   RES_6_L_In::RES_6_L_In()         : Instruction( "RES",   "RES 6, L", "----", 0xB5, 2,  8, VERBOSE_FLAG) { } // 0xCB B5
 RES_6_mHL_In::RES_6_mHL_In()       : Instruction( "RES","RES 6, (HL)", "----", 0xB6, 2, 16, VERBOSE_FLAG) { } // 0xCB B6
   RES_6_A_In::RES_6_A_In()         : Instruction( "RES",   "RES 6, A", "----", 0xB7, 2,  8, VERBOSE_FLAG) { } // 0xCB B7
   RES_7_B_In::RES_7_B_In()         : Instruction( "RES",   "RES 7, B", "----", 0xB8, 2,  8, VERBOSE_FLAG) { } // 0xCB B8
   RES_7_C_In::RES_7_C_In()         : Instruction( "RES",   "RES 7, C", "----", 0xB9, 2,  8, VERBOSE_FLAG) { } // 0xCB B9
   RES_7_D_In::RES_7_D_In()         : Instruction( "RES",   "RES 7, D", "----", 0xBA, 2,  8, VERBOSE_FLAG) { } // 0xCB BA
   RES_7_E_In::RES_7_E_In()         : Instruction( "RES",   "RES 7, E", "----", 0xBB, 2,  8, VERBOSE_FLAG) { } // 0xCB BB
   RES_7_H_In::RES_7_H_In()         : Instruction( "RES",   "RES 7, H", "----", 0xBC, 2,  8, VERBOSE_FLAG) { } // 0xCB BC
   RES_7_L_In::RES_7_L_In()         : Instruction( "RES",   "RES 7, L", "----", 0xBD, 2,  8, VERBOSE_FLAG) { } // 0xCB BD
 RES_7_mHL_In::RES_7_mHL_In()       : Instruction( "RES","RES 7, (HL)", "----", 0xBE, 2, 16, VERBOSE_FLAG) { } // 0xCB BE
   RES_7_A_In::RES_7_A_In()         : Instruction( "RES",   "RES 7, A", "----", 0xBF, 2,  8, VERBOSE_FLAG) { } // 0xCB BF

// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

   SET_0_B_In::SET_0_B_In()         : Instruction( "SET",   "SET 0, B", "----", 0xC0, 2,  8, VERBOSE_FLAG) { } // 0xCB C0
   SET_0_C_In::SET_0_C_In()         : Instruction( "SET",   "SET 0, C", "----", 0xC1, 2,  8, VERBOSE_FLAG) { } // 0xCB C1
   SET_0_D_In::SET_0_D_In()         : Instruction( "SET",   "SET 0, D", "----", 0xC2, 2,  8, VERBOSE_FLAG) { } // 0xCB C2
   SET_0_E_In::SET_0_E_In()         : Instruction( "SET",   "SET 0, E", "----", 0xC3, 2,  8, VERBOSE_FLAG) { } // 0xCB C3
   SET_0_H_In::SET_0_H_In()         : Instruction( "SET",   "SET 0, H", "----", 0xC4, 2,  8, VERBOSE_FLAG) { } // 0xCB C4
   SET_0_L_In::SET_0_L_In()         : Instruction( "SET",   "SET 0, L", "----", 0xC5, 2,  8, VERBOSE_FLAG) { } // 0xCB C5
 SET_0_mHL_In::SET_0_mHL_In()       : Instruction( "SET","SET 0, (HL)", "----", 0xC6, 2, 16, VERBOSE_FLAG) { } // 0xCB C6
   SET_0_A_In::SET_0_A_In()         : Instruction( "SET",   "SET 0, A", "----", 0xC7, 2,  8, VERBOSE_FLAG) { } // 0xCB C7
   SET_1_B_In::SET_1_B_In()         : Instruction( "SET",   "SET 1, B", "----", 0xC8, 2,  8, VERBOSE_FLAG) { } // 0xCB C8
   SET_1_C_In::SET_1_C_In()         : Instruction( "SET",   "SET 1, C", "----", 0xC9, 2,  8, VERBOSE_FLAG) { } // 0xCB C9
   SET_1_D_In::SET_1_D_In()         : Instruction( "SET",   "SET 1, D", "----", 0xCA, 2,  8, VERBOSE_FLAG) { } // 0xCB CA
   SET_1_E_In::SET_1_E_In()         : Instruction( "SET",   "SET 1, E", "----", 0xCB, 2,  8, VERBOSE_FLAG) { } // 0xCB CB
   SET_1_H_In::SET_1_H_In()         : Instruction( "SET",   "SET 1, H", "----", 0xCC, 2,  8, VERBOSE_FLAG) { } // 0xCB CC
   SET_1_L_In::SET_1_L_In()         : Instruction( "SET",   "SET 1, L", "----", 0xCD, 2,  8, VERBOSE_FLAG) { } // 0xCB CD
 SET_1_mHL_In::SET_1_mHL_In()       : Instruction( "SET","SET 1, (HL)", "----", 0xCE, 2, 16, VERBOSE_FLAG) { } // 0xCB CE
   SET_1_A_In::SET_1_A_In()         : Instruction( "SET",   "SET 1, A", "----", 0xCF, 2,  8, VERBOSE_FLAG) { } // 0xCB CF
   
// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

   SET_2_B_In::SET_2_B_In()         : Instruction(  "SET",   "SET 2,B", "----", 0xD0, 2,  8, VERBOSE_FLAG) { } // 0xCB D0
   SET_2_C_In::SET_2_C_In()         : Instruction(  "SET",   "SET 2,C", "----", 0xD1, 2,  8, VERBOSE_FLAG) { } // 0xCB D1
   SET_2_D_In::SET_2_D_In()         : Instruction(  "SET",   "SET 2,D", "----", 0xD2, 2,  8, VERBOSE_FLAG) { } // 0xCB D2
   SET_2_E_In::SET_2_E_In()         : Instruction(  "SET",   "SET 2,E", "----", 0xD3, 2,  8, VERBOSE_FLAG) { } // 0xCB D3
   SET_2_H_In::SET_2_H_In()         : Instruction(  "SET",   "SET 2,H", "----", 0xD4, 2,  8, VERBOSE_FLAG) { } // 0xCB D4
   SET_2_L_In::SET_2_L_In()         : Instruction(  "SET",   "SET 2,L", "----", 0xD5, 2,  8, VERBOSE_FLAG) { } // 0xCB D5
 SET_2_mHL_In::SET_2_mHL_In()       : Instruction(  "SET","SET 2,(HL)", "----", 0xD6, 2, 16, VERBOSE_FLAG) { } // 0xCB D6
   SET_2_A_In::SET_2_A_In()         : Instruction(  "SET",   "SET 2,A", "----", 0xD7, 2,  8, VERBOSE_FLAG) { } // 0xCB D7
   SET_3_B_In::SET_3_B_In()         : Instruction(  "SET",   "SET 3,B", "----", 0xD8, 2,  8, VERBOSE_FLAG) { } // 0xCB D8
   SET_3_C_In::SET_3_C_In()         : Instruction(  "SET",   "SET 3,C", "----", 0xD9, 2,  8, VERBOSE_FLAG) { } // 0xCB D9
   SET_3_D_In::SET_3_D_In()         : Instruction(  "SET",   "SET 3,D", "----", 0xDA, 2,  8, VERBOSE_FLAG) { } // 0xCB DA
   SET_3_E_In::SET_3_E_In()         : Instruction(  "SET",   "SET 3,E", "----", 0xDB, 2,  8, VERBOSE_FLAG) { } // 0xCB DB
   SET_3_H_In::SET_3_H_In()         : Instruction(  "SET",   "SET 3,H", "----", 0xDC, 2,  8, VERBOSE_FLAG) { } // 0xCB DC
   SET_3_L_In::SET_3_L_In()         : Instruction(  "SET",   "SET 3,L", "----", 0xDD, 2,  8, VERBOSE_FLAG) { } // 0xCB DD
 SET_3_mHL_In::SET_3_mHL_In()       : Instruction(  "SET","SET 3,(HL)", "----", 0xDE, 2, 16, VERBOSE_FLAG) { } // 0xCB DE
   SET_3_A_In::SET_3_A_In()         : Instruction(  "SET",   "SET 3,A", "----", 0xDF, 2,  8, VERBOSE_FLAG) { } // 0xCB DF
   
// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

   SET_4_B_In::SET_4_B_In()         : Instruction( "SET",   "SET 4, B", "----", 0xE0, 2,  8, VERBOSE_FLAG) { } // 0xCB E0
   SET_4_C_In::SET_4_C_In()         : Instruction( "SET",   "SET 4, C", "----", 0xE1, 2,  8, VERBOSE_FLAG) { } // 0xCB E1
   SET_4_D_In::SET_4_D_In()         : Instruction( "SET",   "SET 4, D", "----", 0xE2, 2,  8, VERBOSE_FLAG) { } // 0xCB E2
   SET_4_E_In::SET_4_E_In()         : Instruction( "SET",   "SET 4, E", "----", 0xE3, 2,  8, VERBOSE_FLAG) { } // 0xCB E3
   SET_4_H_In::SET_4_H_In()         : Instruction( "SET",   "SET 4, H", "----", 0xE4, 2,  8, VERBOSE_FLAG) { } // 0xCB E4
   SET_4_L_In::SET_4_L_In()         : Instruction( "SET",   "SET 4, L", "----", 0xE5, 2,  8, VERBOSE_FLAG) { } // 0xCB E5
 SET_4_mHL_In::SET_4_mHL_In()       : Instruction( "SET","SET 4, (HL)", "----", 0xE6, 2, 16, VERBOSE_FLAG) { } // 0xCB E6
   SET_4_A_In::SET_4_A_In()         : Instruction( "SET",   "SET 4, A", "----", 0xE7, 2,  8, VERBOSE_FLAG) { } // 0xCB E7
   SET_5_B_In::SET_5_B_In()         : Instruction( "SET",   "SET 5, B", "----", 0xE8, 2,  8, VERBOSE_FLAG) { } // 0xCB E8
   SET_5_C_In::SET_5_C_In()         : Instruction( "SET",   "SET 5, C", "----", 0xE9, 2,  8, VERBOSE_FLAG) { } // 0xCB E9
   SET_5_D_In::SET_5_D_In()         : Instruction( "SET",   "SET 5, D", "----", 0xEA, 2,  8, VERBOSE_FLAG) { } // 0xCB EA
   SET_5_E_In::SET_5_E_In()         : Instruction( "SET",   "SET 5, E", "----", 0xEB, 2,  8, VERBOSE_FLAG) { } // 0xCB EB
   SET_5_H_In::SET_5_H_In()         : Instruction( "SET",   "SET 5, H", "----", 0xEC, 2,  8, VERBOSE_FLAG) { } // 0xCB EC
   SET_5_L_In::SET_5_L_In()         : Instruction( "SET",   "SET 5, L", "----", 0xED, 2,  8, VERBOSE_FLAG) { } // 0xCB ED
 SET_5_mHL_In::SET_5_mHL_In()       : Instruction( "SET","SET 5, (HL)", "----", 0xEE, 2, 16, VERBOSE_FLAG) { } // 0xCB EE
   SET_5_A_In::SET_5_A_In()         : Instruction( "SET",   "SET 5, A", "----", 0xEF, 2,  8, VERBOSE_FLAG) { } // 0xCB EF
   
// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

   SET_6_B_In::SET_6_B_In()         : Instruction( "SET",   "SET 6, B", "----", 0xF0, 2,  8, VERBOSE_FLAG) { } // 0xCB F0
   SET_6_C_In::SET_6_C_In()         : Instruction( "SET",   "SET 6, C", "----", 0xF1, 2,  8, VERBOSE_FLAG) { } // 0xCB F1
   SET_6_D_In::SET_6_D_In()         : Instruction( "SET",   "SET 6, D", "----", 0xF2, 2,  8, VERBOSE_FLAG) { } // 0xCB F2
   SET_6_E_In::SET_6_E_In()         : Instruction( "SET",   "SET 6, E", "----", 0xF3, 2,  8, VERBOSE_FLAG) { } // 0xCB F3
   SET_6_H_In::SET_6_H_In()         : Instruction( "SET",   "SET 6, H", "----", 0xF4, 2,  8, VERBOSE_FLAG) { } // 0xCB F4
   SET_6_L_In::SET_6_L_In()         : Instruction( "SET",   "SET 6, L", "----", 0xF5, 2,  8, VERBOSE_FLAG) { } // 0xCB F5
 SET_6_mHL_In::SET_6_mHL_In()       : Instruction( "SET","SET 6, (HL)", "----", 0xF6, 2, 16, VERBOSE_FLAG) { } // 0xCB F6
   SET_6_A_In::SET_6_A_In()         : Instruction( "SET",   "SET 6, A", "----", 0xF7, 2,  8, VERBOSE_FLAG) { } // 0xCB F7
   SET_7_B_In::SET_7_B_In()         : Instruction( "SET",   "SET 7, B", "----", 0xF8, 2,  8, VERBOSE_FLAG) { } // 0xCB F8
   SET_7_C_In::SET_7_C_In()         : Instruction( "SET",   "SET 7, C", "----", 0xF9, 2,  8, VERBOSE_FLAG) { } // 0xCB F9
   SET_7_D_In::SET_7_D_In()         : Instruction( "SET",   "SET 7, D", "----", 0xFA, 2,  8, VERBOSE_FLAG) { } // 0xCB FA
   SET_7_E_In::SET_7_E_In()         : Instruction( "SET",   "SET 7, E", "----", 0xFB, 2,  8, VERBOSE_FLAG) { } // 0xCB FB
   SET_7_H_In::SET_7_H_In()         : Instruction( "SET",   "SET 7, H", "----", 0xFC, 2,  8, VERBOSE_FLAG) { } // 0xCB FC
   SET_7_L_In::SET_7_L_In()         : Instruction( "SET",   "SET 7, L", "----", 0xFD, 2,  8, VERBOSE_FLAG) { } // 0xCB FD
 SET_7_mHL_In::SET_7_mHL_In()       : Instruction( "SET","SET 7, (HL)", "----", 0xFE, 2, 16, VERBOSE_FLAG) { } // 0xCB FE
   SET_7_A_In::SET_7_A_In()         : Instruction( "SET",   "SET 7, A", "----", 0xFF, 2,  8, VERBOSE_FLAG) { } // 0xCB FF
   
   
   
   
   

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

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

void   BIT_0_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.B); }                // 0xCB 40
void   BIT_0_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.C); }                // 0xCB 41
void   BIT_0_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.D); }                // 0xCB 42
void   BIT_0_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.E); }                // 0xCB 43
void   BIT_0_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.H); }                // 0xCB 44
void   BIT_0_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.L); }                // 0xCB 45
void BIT_0_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(0, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 46
void   BIT_0_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(0, cpu.registers.A); }                // 0xCB 47
void    BIT_1_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.B); }                 // 0xCB 48
void    BIT_1_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.C); }                 // 0xCB 49
void    BIT_1_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.D); }                 // 0xCB 4A
void    BIT_1_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.E); }                 // 0xCB 4B
void    BIT_1_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.H); }                 // 0xCB 4C
void    BIT_1_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.L); }                 // 0xCB 4D
void  BIT_1_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(1, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 4E
void    BIT_1_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(1, cpu.registers.A); }                 // 0xCB 4F

// =================================================================================================
// OpCodes 0x50 - 0x5F
// =================================================================================================

void   BIT_2_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.B); }                // 0xCB 50
void   BIT_2_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.C); }                // 0xCB 51
void   BIT_2_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.D); }                // 0xCB 52
void   BIT_2_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.E); }                // 0xCB 53
void   BIT_2_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.H); }                // 0xCB 54
void   BIT_2_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.L); }                // 0xCB 55
void BIT_2_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(2, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 56
void   BIT_2_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(2, cpu.registers.A); }                // 0xCB 57
void    BIT_3_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.B); }                 // 0xCB 58
void    BIT_3_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.C); }                 // 0xCB 59
void    BIT_3_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.D); }                 // 0xCB 5A
void    BIT_3_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.E); }                 // 0xCB 5B
void    BIT_3_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.H); }                 // 0xCB 5C
void    BIT_3_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.L); }                 // 0xCB 5D
void  BIT_3_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(3, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 5E
void    BIT_3_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(3, cpu.registers.A); }                 // 0xCB 5F

// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

void   BIT_4_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.B); }                // 0xCB 60
void   BIT_4_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.C); }                // 0xCB 61
void   BIT_4_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.D); }                // 0xCB 62
void   BIT_4_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.E); }                // 0xCB 63
void   BIT_4_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.H); }                // 0xCB 64
void   BIT_4_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.L); }                // 0xCB 65
void BIT_4_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(4, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 66
void   BIT_4_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(4, cpu.registers.A); }                // 0xCB 67
void    BIT_5_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.B); }                 // 0xCB 68
void    BIT_5_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.C); }                 // 0xCB 69
void    BIT_5_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.D); }                 // 0xCB 6A
void    BIT_5_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.E); }                 // 0xCB 6B
void    BIT_5_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.H); }                 // 0xCB 6C
void    BIT_5_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.L); }                 // 0xCB 6D
void  BIT_5_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(5, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 6E
void    BIT_5_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(5, cpu.registers.A); }                 // 0xCB 6F

// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

void   BIT_6_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.B); }                // 0xCB 70
void   BIT_6_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.C); }                // 0xCB 71
void   BIT_6_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.D); }                // 0xCB 72
void   BIT_6_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.E); }                // 0xCB 73
void   BIT_6_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.H); }                // 0xCB 74
void   BIT_6_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.L); }                // 0xCB 75
void BIT_6_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(6, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 76
void   BIT_6_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(6, cpu.registers.A); }                // 0xCB 77
void    BIT_7_B_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.B); }                 // 0xCB 78
void    BIT_7_C_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.C); }                 // 0xCB 79
void    BIT_7_D_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.D); }                 // 0xCB 7A
void    BIT_7_E_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.E); }                 // 0xCB 7B
void    BIT_7_H_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.H); }                 // 0xCB 7C
void    BIT_7_L_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.L); }                 // 0xCB 7D
void  BIT_7_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.bit(7, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 7E
void    BIT_7_A_In::op(LR35902& cpu, Memory& memory) { cpu.bit(7, cpu.registers.A); }                 // 0xCB 7F

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

void   RES_0_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.B); }                // 0xCB 80
void   RES_0_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.C); }                // 0xCB 81
void   RES_0_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.D); }                // 0xCB 82
void   RES_0_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.E); }                // 0xCB 83
void   RES_0_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.H); }                // 0xCB 84
void   RES_0_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.L); }                // 0xCB 85
void RES_0_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(0, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 86
void   RES_0_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(0, cpu.registers.A); }                // 0xCB 87
void    RES_1_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.B); }                 // 0xCB 88
void    RES_1_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.C); }                 // 0xCB 89
void    RES_1_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.D); }                 // 0xCB 8A
void    RES_1_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.E); }                 // 0xCB 8B
void    RES_1_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.H); }                 // 0xCB 8C
void    RES_1_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.L); }                 // 0xCB 8D
void  RES_1_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(1, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 8E
void    RES_1_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(1, cpu.registers.A); }                 // 0xCB 8F

// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

void   RES_2_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.B); }                // 0xCB 90
void   RES_2_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.C); }                // 0xCB 91
void   RES_2_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.D); }                // 0xCB 92
void   RES_2_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.E); }                // 0xCB 93
void   RES_2_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.H); }                // 0xCB 94
void   RES_2_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.L); }                // 0xCB 95
void RES_2_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(2, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 96
void   RES_2_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(2, cpu.registers.A); }                // 0xCB 97
void    RES_3_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.B); }                 // 0xCB 98
void    RES_3_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.C); }                 // 0xCB 99
void    RES_3_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.D); }                 // 0xCB 9A
void    RES_3_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.E); }                 // 0xCB 9B
void    RES_3_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.H); }                 // 0xCB 9C
void    RES_3_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.L); }                 // 0xCB 9D
void  RES_3_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(3, v); memory.write_8(cpu.registers.HL, v);} // 0xCB 9E
void    RES_3_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(3, cpu.registers.A); }                 // 0xCB 9F

// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

void   RES_4_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.B); }                // 0xCB A0
void   RES_4_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.C); }                // 0xCB A1
void   RES_4_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.D); }                // 0xCB A2
void   RES_4_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.E); }                // 0xCB A3
void   RES_4_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.H); }                // 0xCB A4
void   RES_4_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.L); }                // 0xCB A5
void RES_4_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(4, v); memory.write_8(cpu.registers.HL, v);} // 0xCB A6
void   RES_4_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(4, cpu.registers.A); }                // 0xCB A7
void    RES_5_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.B); }                 // 0xCB A8
void    RES_5_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.C); }                 // 0xCB A9
void    RES_5_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.D); }                 // 0xCB AA
void    RES_5_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.E); }                 // 0xCB AB
void    RES_5_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.H); }                 // 0xCB AC
void    RES_5_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.L); }                 // 0xCB AD
void  RES_5_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(5, v); memory.write_8(cpu.registers.HL, v);} // 0xCB AE
void    RES_5_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(5, cpu.registers.A); }                 // 0xCB AF

// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

void   RES_6_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.B); }                // 0xCB B0
void   RES_6_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.C); }                // 0xCB B1
void   RES_6_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.D); }                // 0xCB B2
void   RES_6_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.E); }                // 0xCB B3
void   RES_6_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.H); }                // 0xCB B4
void   RES_6_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.L); }                // 0xCB B5
void RES_6_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(6, v); memory.write_8(cpu.registers.HL, v);} // 0xCB B6
void   RES_6_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(6, cpu.registers.A); }                // 0xCB B7
void    RES_7_B_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.B); }                 // 0xCB B8
void    RES_7_C_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.C); }                 // 0xCB B9
void    RES_7_D_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.D); }                 // 0xCB BA
void    RES_7_E_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.E); }                 // 0xCB BB
void    RES_7_H_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.H); }                 // 0xCB BC
void    RES_7_L_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.L); }                 // 0xCB BD
void  RES_7_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.res(7, v); memory.write_8(cpu.registers.HL, v);} // 0xCB BE
void    RES_7_A_In::op(LR35902& cpu, Memory& memory) { cpu.res(7, cpu.registers.A); }                 // 0xCB BF

// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

void   SET_0_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.B); }                // 0xCB C0
void   SET_0_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.C); }                // 0xCB C1
void   SET_0_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.D); }                // 0xCB C2
void   SET_0_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.E); }                // 0xCB C3
void   SET_0_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.H); }                // 0xCB C4
void   SET_0_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.L); }                // 0xCB C5
void SET_0_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(0, v); memory.write_8(cpu.registers.HL, v);} // 0xCB C6
void   SET_0_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(0, cpu.registers.A); }                // 0xCB C7
void    SET_1_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.B); }                 // 0xCB C8
void    SET_1_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.C); }                 // 0xCB C9
void    SET_1_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.D); }                 // 0xCB CA
void    SET_1_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.E); }                 // 0xCB CB
void    SET_1_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.H); }                 // 0xCB CC
void    SET_1_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.L); }                 // 0xCB CD
void  SET_1_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(1, v); memory.write_8(cpu.registers.HL, v);} // 0xCB CE
void    SET_1_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(1, cpu.registers.A); }                 // 0xCB CF

// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

void   SET_2_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.B); }                // 0xCB D0
void   SET_2_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.C); }                // 0xCB D1
void   SET_2_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.D); }                // 0xCB D2
void   SET_2_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.E); }                // 0xCB D3
void   SET_2_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.H); }                // 0xCB D4
void   SET_2_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.L); }                // 0xCB D5
void SET_2_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(2, v); memory.write_8(cpu.registers.HL, v);} // 0xCB D6
void   SET_2_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(2, cpu.registers.A); }                // 0xCB D7
void    SET_3_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.B); }                 // 0xCB D8
void    SET_3_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.C); }                 // 0xCB D9
void    SET_3_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.D); }                 // 0xCB DA
void    SET_3_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.E); }                 // 0xCB DB
void    SET_3_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.H); }                 // 0xCB DC
void    SET_3_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.L); }                 // 0xCB DD
void  SET_3_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(3, v); memory.write_8(cpu.registers.HL, v);} // 0xCB DE
void    SET_3_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(3, cpu.registers.A); }                 // 0xCB DF

// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

void   SET_4_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.B); }                // 0xCB E0
void   SET_4_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.C); }                // 0xCB E1
void   SET_4_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.D); }                // 0xCB E2
void   SET_4_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.E); }                // 0xCB E3
void   SET_4_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.H); }                // 0xCB E4
void   SET_4_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.L); }                // 0xCB E5
void SET_4_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(4, v); memory.write_8(cpu.registers.HL, v);} // 0xCB E6
void   SET_4_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(4, cpu.registers.A); }                // 0xCB E7
void    SET_5_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.B); }                 // 0xCB E8
void    SET_5_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.C); }                 // 0xCB E9
void    SET_5_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.D); }                 // 0xCB EA
void    SET_5_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.E); }                 // 0xCB EB
void    SET_5_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.H); }                 // 0xCB EC
void    SET_5_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.L); }                 // 0xCB ED
void  SET_5_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(5, v); memory.write_8(cpu.registers.HL, v);} // 0xCB EE
void    SET_5_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(5, cpu.registers.A); }                 // 0xCB EF

// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

void   SET_6_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.B); }                // 0xCB F0
void   SET_6_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.C); }                // 0xCB F1
void   SET_6_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.D); }                // 0xCB F2
void   SET_6_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.E); }                // 0xCB F3
void   SET_6_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.H); }                // 0xCB F4
void   SET_6_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.L); }                // 0xCB F5
void SET_6_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(6, v); memory.write_8(cpu.registers.HL, v);} // 0xCB F6
void   SET_6_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(6, cpu.registers.A); }                // 0xCB F7
void    SET_7_B_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.B); }                 // 0xCB F8
void    SET_7_C_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.C); }                 // 0xCB F9
void    SET_7_D_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.D); }                 // 0xCB FA
void    SET_7_E_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.E); }                 // 0xCB FB
void    SET_7_H_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.H); }                 // 0xCB FC
void    SET_7_L_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.L); }                 // 0xCB FD
void  SET_7_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 v = memory.read_8(cpu.registers.HL); cpu.set(7, v); memory.write_8(cpu.registers.HL, v);} // 0xCB FE
void    SET_7_A_In::op(LR35902& cpu, Memory& memory) { cpu.set(7, cpu.registers.A); }                 // 0xCB FF