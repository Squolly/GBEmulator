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

#endif