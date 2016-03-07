#ifndef __INSTRUCTION_SET_PREFIX_CB_HPP__
#define __INSTRUCTION_SET_PREFIX_CB_HPP__

#include "Instruction.hpp" 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

struct CB_RLC_B_In   : public Instruction {   CB_RLC_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 00
struct CB_RLC_C_In   : public Instruction {   CB_RLC_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 01
struct CB_RLC_D_In   : public Instruction {   CB_RLC_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 02
struct CB_RLC_E_In   : public Instruction {   CB_RLC_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 03
struct CB_RLC_H_In   : public Instruction {   CB_RLC_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 04
struct CB_RLC_L_In   : public Instruction {   CB_RLC_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 05
struct CB_RLC_mHL_In : public Instruction { CB_RLC_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 06
struct CB_RLC_A_In   : public Instruction {   CB_RLC_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 07
struct CB_RRC_B_In   : public Instruction {   CB_RRC_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 08
struct CB_RRC_C_In   : public Instruction {   CB_RRC_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 09
struct CB_RRC_D_In   : public Instruction {   CB_RRC_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0A
struct CB_RRC_E_In   : public Instruction {   CB_RRC_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0B
struct CB_RRC_H_In   : public Instruction {   CB_RRC_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0C
struct CB_RRC_L_In   : public Instruction {   CB_RRC_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0D
struct CB_RRC_mHL_In : public Instruction { CB_RRC_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0E
struct CB_RRC_A_In   : public Instruction {   CB_RRC_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 0F

// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================

struct CB_RL_B_In   : public Instruction {     CB_RL_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 10
struct CB_RL_C_In   : public Instruction {     CB_RL_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 11
struct CB_RL_D_In   : public Instruction {     CB_RL_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 12
struct CB_RL_E_In   : public Instruction {     CB_RL_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 13
struct CB_RL_H_In   : public Instruction {     CB_RL_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 14
struct CB_RL_L_In   : public Instruction {     CB_RL_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 15
struct CB_RL_mHL_In : public Instruction {   CB_RL_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 16
struct CB_RL_A_In   : public Instruction {     CB_RL_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 17
struct CB_RR_B_In   : public Instruction {     CB_RR_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 18
struct CB_RR_C_In   : public Instruction {     CB_RR_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 19
struct CB_RR_D_In   : public Instruction {     CB_RR_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1A
struct CB_RR_E_In   : public Instruction {     CB_RR_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1B
struct CB_RR_H_In   : public Instruction {     CB_RR_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1C
struct CB_RR_L_In   : public Instruction {     CB_RR_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1D
struct CB_RR_mHL_In : public Instruction {   CB_RR_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1E
struct CB_RR_A_In   : public Instruction {     CB_RR_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 1F

// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

struct CB_SLA_B_In  : public Instruction {    CB_SLA_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 20
struct CB_SLA_C_In  : public Instruction {    CB_SLA_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 21
struct CB_SLA_D_In  : public Instruction {    CB_SLA_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 22
struct CB_SLA_E_In  : public Instruction {    CB_SLA_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 23
struct CB_SLA_H_In  : public Instruction {    CB_SLA_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 24
struct CB_SLA_L_In  : public Instruction {    CB_SLA_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 25
struct CB_SLA_mHL_In: public Instruction {  CB_SLA_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 26
struct CB_SLA_A_In  : public Instruction {    CB_SLA_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 27
struct CB_SRA_B_In  : public Instruction {    CB_SRA_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 28
struct CB_SRA_C_In  : public Instruction {    CB_SRA_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 29
struct CB_SRA_D_In  : public Instruction {    CB_SRA_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2A
struct CB_SRA_E_In  : public Instruction {    CB_SRA_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2B
struct CB_SRA_H_In  : public Instruction {    CB_SRA_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2C
struct CB_SRA_L_In  : public Instruction {    CB_SRA_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2D
struct CB_SRA_mHL_In: public Instruction {  CB_SRA_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2E
struct CB_SRA_A_In  : public Instruction {    CB_SRA_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 2F

// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

struct CB_SWAP_B_In  : public Instruction {  CB_SWAP_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 30
struct CB_SWAP_C_In  : public Instruction {  CB_SWAP_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 31
struct CB_SWAP_D_In  : public Instruction {  CB_SWAP_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 32
struct CB_SWAP_E_In  : public Instruction {  CB_SWAP_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 33
struct CB_SWAP_H_In  : public Instruction {  CB_SWAP_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 34
struct CB_SWAP_L_In  : public Instruction {  CB_SWAP_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 35
struct CB_SWAP_mHL_In: public Instruction {CB_SWAP_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 36
struct CB_SWAP_A_In  : public Instruction {  CB_SWAP_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 37
struct CB_SRL_B_In   : public Instruction {   CB_SRL_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 38
struct CB_SRL_C_In   : public Instruction {   CB_SRL_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 39
struct CB_SRL_D_In   : public Instruction {   CB_SRL_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3A
struct CB_SRL_E_In   : public Instruction {   CB_SRL_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3B
struct CB_SRL_H_In   : public Instruction {   CB_SRL_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3C
struct CB_SRL_L_In   : public Instruction {   CB_SRL_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3D
struct CB_SRL_mHL_In : public Instruction { CB_SRL_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3E
struct CB_SRL_A_In   : public Instruction {   CB_SRL_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 3F

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

struct BIT_0_B_In   : public Instruction {  BIT_0_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 40
struct BIT_0_C_In   : public Instruction {  BIT_0_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 41
struct BIT_0_D_In   : public Instruction {  BIT_0_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 42
struct BIT_0_E_In   : public Instruction {  BIT_0_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 43
struct BIT_0_H_In   : public Instruction {  BIT_0_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 44
struct BIT_0_L_In   : public Instruction {  BIT_0_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 45
struct BIT_0_mHL_In : public Instruction {BIT_0_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 46
struct BIT_0_A_In   : public Instruction {  BIT_0_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 47
struct BIT_1_B_In   : public Instruction {  BIT_1_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 48
struct BIT_1_C_In   : public Instruction {  BIT_1_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 49
struct BIT_1_D_In   : public Instruction {  BIT_1_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4A
struct BIT_1_E_In   : public Instruction {  BIT_1_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4B
struct BIT_1_H_In   : public Instruction {  BIT_1_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4C
struct BIT_1_L_In   : public Instruction {  BIT_1_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4D
struct BIT_1_mHL_In : public Instruction {BIT_1_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4E
struct BIT_1_A_In   : public Instruction {  BIT_1_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 4F

// =================================================================================================
// OpCodes 0x50 - 0x5F
// =================================================================================================

struct BIT_2_B_In   : public Instruction {  BIT_2_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 50
struct BIT_2_C_In   : public Instruction {  BIT_2_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 51
struct BIT_2_D_In   : public Instruction {  BIT_2_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 52
struct BIT_2_E_In   : public Instruction {  BIT_2_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 53
struct BIT_2_H_In   : public Instruction {  BIT_2_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 54
struct BIT_2_L_In   : public Instruction {  BIT_2_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 55
struct BIT_2_mHL_In : public Instruction {BIT_2_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 56
struct BIT_2_A_In   : public Instruction {  BIT_2_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 57
struct BIT_3_B_In   : public Instruction {  BIT_3_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 58
struct BIT_3_C_In   : public Instruction {  BIT_3_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 59
struct BIT_3_D_In   : public Instruction {  BIT_3_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5A
struct BIT_3_E_In   : public Instruction {  BIT_3_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5B
struct BIT_3_H_In   : public Instruction {  BIT_3_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5C
struct BIT_3_L_In   : public Instruction {  BIT_3_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5D
struct BIT_3_mHL_In : public Instruction {BIT_3_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5E
struct BIT_3_A_In   : public Instruction {  BIT_3_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 5F

// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

struct BIT_4_B_In   : public Instruction {  BIT_4_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 60
struct BIT_4_C_In   : public Instruction {  BIT_4_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 61
struct BIT_4_D_In   : public Instruction {  BIT_4_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 62
struct BIT_4_E_In   : public Instruction {  BIT_4_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 63
struct BIT_4_H_In   : public Instruction {  BIT_4_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 64
struct BIT_4_L_In   : public Instruction {  BIT_4_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 65
struct BIT_4_mHL_In : public Instruction {BIT_4_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 66
struct BIT_4_A_In   : public Instruction {  BIT_4_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 67
struct BIT_5_B_In   : public Instruction {  BIT_5_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 68
struct BIT_5_C_In   : public Instruction {  BIT_5_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 69
struct BIT_5_D_In   : public Instruction {  BIT_5_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6A
struct BIT_5_E_In   : public Instruction {  BIT_5_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6B
struct BIT_5_H_In   : public Instruction {  BIT_5_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6C
struct BIT_5_L_In   : public Instruction {  BIT_5_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6D
struct BIT_5_mHL_In : public Instruction {BIT_5_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6E
struct BIT_5_A_In   : public Instruction {  BIT_5_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 6F

// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

struct BIT_6_B_In   : public Instruction {  BIT_6_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 70
struct BIT_6_C_In   : public Instruction {  BIT_6_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 71
struct BIT_6_D_In   : public Instruction {  BIT_6_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 72
struct BIT_6_E_In   : public Instruction {  BIT_6_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 73
struct BIT_6_H_In   : public Instruction {  BIT_6_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 74
struct BIT_6_L_In   : public Instruction {  BIT_6_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 75
struct BIT_6_mHL_In : public Instruction {BIT_6_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 76
struct BIT_6_A_In   : public Instruction {  BIT_6_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 77
struct BIT_7_B_In   : public Instruction {  BIT_7_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 78
struct BIT_7_C_In   : public Instruction {  BIT_7_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 79
struct BIT_7_D_In   : public Instruction {  BIT_7_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7A
struct BIT_7_E_In   : public Instruction {  BIT_7_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7B
struct BIT_7_H_In   : public Instruction {  BIT_7_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7C
struct BIT_7_L_In   : public Instruction {  BIT_7_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7D
struct BIT_7_mHL_In : public Instruction {BIT_7_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7E
struct BIT_7_A_In   : public Instruction {  BIT_7_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 7F

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

struct RES_0_B_In   : public Instruction {  RES_0_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 80
struct RES_0_C_In   : public Instruction {  RES_0_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 81
struct RES_0_D_In   : public Instruction {  RES_0_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 82
struct RES_0_E_In   : public Instruction {  RES_0_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 83
struct RES_0_H_In   : public Instruction {  RES_0_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 84
struct RES_0_L_In   : public Instruction {  RES_0_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 85
struct RES_0_mHL_In : public Instruction {RES_0_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 86
struct RES_0_A_In   : public Instruction {  RES_0_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 87
struct RES_1_B_In   : public Instruction {  RES_1_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 88
struct RES_1_C_In   : public Instruction {  RES_1_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 89
struct RES_1_D_In   : public Instruction {  RES_1_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8A
struct RES_1_E_In   : public Instruction {  RES_1_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8B
struct RES_1_H_In   : public Instruction {  RES_1_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8C
struct RES_1_L_In   : public Instruction {  RES_1_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8D
struct RES_1_mHL_In : public Instruction {RES_1_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8E
struct RES_1_A_In   : public Instruction {  RES_1_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 8F

// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

struct RES_2_B_In   : public Instruction {  RES_2_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 90
struct RES_2_C_In   : public Instruction {  RES_2_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 91
struct RES_2_D_In   : public Instruction {  RES_2_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 92
struct RES_2_E_In   : public Instruction {  RES_2_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 93
struct RES_2_H_In   : public Instruction {  RES_2_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 94
struct RES_2_L_In   : public Instruction {  RES_2_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 95
struct RES_2_mHL_In : public Instruction {RES_2_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 96
struct RES_2_A_In   : public Instruction {  RES_2_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 97
struct RES_3_B_In   : public Instruction {  RES_3_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 98
struct RES_3_C_In   : public Instruction {  RES_3_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 99
struct RES_3_D_In   : public Instruction {  RES_3_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9A
struct RES_3_E_In   : public Instruction {  RES_3_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9B
struct RES_3_H_In   : public Instruction {  RES_3_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9C
struct RES_3_L_In   : public Instruction {  RES_3_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9D
struct RES_3_mHL_In : public Instruction {RES_3_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9E
struct RES_3_A_In   : public Instruction {  RES_3_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB 9F

// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

struct RES_4_B_In   : public Instruction {  RES_4_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A0
struct RES_4_C_In   : public Instruction {  RES_4_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A1
struct RES_4_D_In   : public Instruction {  RES_4_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A2
struct RES_4_E_In   : public Instruction {  RES_4_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A3
struct RES_4_H_In   : public Instruction {  RES_4_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A4
struct RES_4_L_In   : public Instruction {  RES_4_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A5
struct RES_4_mHL_In : public Instruction {RES_4_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A6
struct RES_4_A_In   : public Instruction {  RES_4_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A7
struct RES_5_B_In   : public Instruction {  RES_5_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A8
struct RES_5_C_In   : public Instruction {  RES_5_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB A9
struct RES_5_D_In   : public Instruction {  RES_5_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AA
struct RES_5_E_In   : public Instruction {  RES_5_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AB
struct RES_5_H_In   : public Instruction {  RES_5_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AC
struct RES_5_L_In   : public Instruction {  RES_5_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AD
struct RES_5_mHL_In : public Instruction {RES_5_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AE
struct RES_5_A_In   : public Instruction {  RES_5_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB AF

// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

struct RES_6_B_In   : public Instruction {  RES_6_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B0
struct RES_6_C_In   : public Instruction {  RES_6_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B1
struct RES_6_D_In   : public Instruction {  RES_6_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B2
struct RES_6_E_In   : public Instruction {  RES_6_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B3
struct RES_6_H_In   : public Instruction {  RES_6_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B4
struct RES_6_L_In   : public Instruction {  RES_6_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B5
struct RES_6_mHL_In : public Instruction {RES_6_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B6
struct RES_6_A_In   : public Instruction {  RES_6_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B7
struct RES_7_B_In   : public Instruction {  RES_7_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B8
struct RES_7_C_In   : public Instruction {  RES_7_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB B9
struct RES_7_D_In   : public Instruction {  RES_7_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BA
struct RES_7_E_In   : public Instruction {  RES_7_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BB
struct RES_7_H_In   : public Instruction {  RES_7_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BC
struct RES_7_L_In   : public Instruction {  RES_7_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BD
struct RES_7_mHL_In : public Instruction {RES_7_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BE
struct RES_7_A_In   : public Instruction {  RES_7_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB BF

// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

struct SET_0_B_In   : public Instruction {  SET_0_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C0
struct SET_0_C_In   : public Instruction {  SET_0_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C1
struct SET_0_D_In   : public Instruction {  SET_0_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C2
struct SET_0_E_In   : public Instruction {  SET_0_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C3
struct SET_0_H_In   : public Instruction {  SET_0_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C4
struct SET_0_L_In   : public Instruction {  SET_0_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C5
struct SET_0_mHL_In : public Instruction {SET_0_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C6
struct SET_0_A_In   : public Instruction {  SET_0_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C7
struct SET_1_B_In   : public Instruction {  SET_1_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C8
struct SET_1_C_In   : public Instruction {  SET_1_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB C9
struct SET_1_D_In   : public Instruction {  SET_1_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CA
struct SET_1_E_In   : public Instruction {  SET_1_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CB
struct SET_1_H_In   : public Instruction {  SET_1_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CC
struct SET_1_L_In   : public Instruction {  SET_1_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CD
struct SET_1_mHL_In : public Instruction {SET_1_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CE
struct SET_1_A_In   : public Instruction {  SET_1_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB CF

// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

struct SET_2_B_In   : public Instruction {  SET_2_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D0
struct SET_2_C_In   : public Instruction {  SET_2_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D1
struct SET_2_D_In   : public Instruction {  SET_2_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D2
struct SET_2_E_In   : public Instruction {  SET_2_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D3
struct SET_2_H_In   : public Instruction {  SET_2_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D4
struct SET_2_L_In   : public Instruction {  SET_2_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D5
struct SET_2_mHL_In : public Instruction {SET_2_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D6
struct SET_2_A_In   : public Instruction {  SET_2_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D7
struct SET_3_B_In   : public Instruction {  SET_3_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D8
struct SET_3_C_In   : public Instruction {  SET_3_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB D9
struct SET_3_D_In   : public Instruction {  SET_3_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DA
struct SET_3_E_In   : public Instruction {  SET_3_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DB
struct SET_3_H_In   : public Instruction {  SET_3_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DC
struct SET_3_L_In   : public Instruction {  SET_3_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DD
struct SET_3_mHL_In : public Instruction {SET_3_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DE
struct SET_3_A_In   : public Instruction {  SET_3_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB DF

// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

struct SET_4_B_In   : public Instruction {  SET_4_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E0
struct SET_4_C_In   : public Instruction {  SET_4_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E1
struct SET_4_D_In   : public Instruction {  SET_4_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E2
struct SET_4_E_In   : public Instruction {  SET_4_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E3
struct SET_4_H_In   : public Instruction {  SET_4_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E4
struct SET_4_L_In   : public Instruction {  SET_4_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E5
struct SET_4_mHL_In : public Instruction {SET_4_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E6
struct SET_4_A_In   : public Instruction {  SET_4_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E7
struct SET_5_B_In   : public Instruction {  SET_5_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E8
struct SET_5_C_In   : public Instruction {  SET_5_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB E9
struct SET_5_D_In   : public Instruction {  SET_5_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB EA
struct SET_5_E_In   : public Instruction {  SET_5_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB EB
struct SET_5_H_In   : public Instruction {  SET_5_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB EC
struct SET_5_L_In   : public Instruction {  SET_5_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB ED
struct SET_5_mHL_In : public Instruction {SET_5_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB EE
struct SET_5_A_In   : public Instruction {  SET_5_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB EF

// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

struct SET_6_B_In   : public Instruction {  SET_6_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F0
struct SET_6_C_In   : public Instruction {  SET_6_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F1
struct SET_6_D_In   : public Instruction {  SET_6_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F2
struct SET_6_E_In   : public Instruction {  SET_6_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F3
struct SET_6_H_In   : public Instruction {  SET_6_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F4
struct SET_6_L_In   : public Instruction {  SET_6_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F5
struct SET_6_mHL_In : public Instruction {SET_6_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F6
struct SET_6_A_In   : public Instruction {  SET_6_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F7
struct SET_7_B_In   : public Instruction {  SET_7_B_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F8
struct SET_7_C_In   : public Instruction {  SET_7_C_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB F9
struct SET_7_D_In   : public Instruction {  SET_7_D_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FA
struct SET_7_E_In   : public Instruction {  SET_7_E_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FB
struct SET_7_H_In   : public Instruction {  SET_7_H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FC
struct SET_7_L_In   : public Instruction {  SET_7_L_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FD
struct SET_7_mHL_In : public Instruction {SET_7_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FE
struct SET_7_A_In   : public Instruction {  SET_7_A_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xCB FF

#endif