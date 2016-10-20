#ifndef __INSTRUCTION_SET_HPP__
#define __INSTRUCTION_SET_HPP__

#include "Instruction.hpp"
#include <vector> 
#include <memory> 
const bool VERBOSE_FLAG = false; 

// consider to remove LR35902 and Memory from Parameters and add them as members of Instruction class 

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

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

struct LD_B_B_In : public Instruction { LD_B_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x40 LD B, B
struct LD_B_C_In : public Instruction { LD_B_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x41 LD B, C
struct LD_B_D_In : public Instruction { LD_B_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x42 LD B, D
struct LD_B_E_In : public Instruction { LD_B_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x43 LD B, E
struct LD_B_H_In : public Instruction { LD_B_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x44 LD B, H
struct LD_B_L_In : public Instruction { LD_B_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x45 LD B, L
struct LD_B_mHL_In : public Instruction { LD_B_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x46 LD B, (HL)
struct LD_B_A_In : public Instruction { LD_B_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x47 LD B, A
struct LD_C_B_In : public Instruction { LD_C_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x48 LD C, B
struct LD_C_C_In : public Instruction { LD_C_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x49 LD C, C
struct LD_C_D_In : public Instruction { LD_C_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x4A LD C, D
struct LD_C_E_In : public Instruction { LD_C_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x4B LD C, E
struct LD_C_H_In : public Instruction { LD_C_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x4C LD C, H
struct LD_C_L_In : public Instruction { LD_C_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x4D LD C, L
struct LD_C_mHL_In : public Instruction { LD_C_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x4E LD C, (HL)
struct LD_C_A_In : public Instruction { LD_C_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x4F LD C, A

// =================================================================================================          
// OpCodes 0x50 - 0x5F
// =================================================================================================

struct LD_D_B_In : public Instruction { LD_D_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x50 LD D, B
struct LD_D_C_In : public Instruction { LD_D_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x51 LD D, C
struct LD_D_D_In : public Instruction { LD_D_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x52 LD D, D
struct LD_D_E_In : public Instruction { LD_D_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x53 LD D, E
struct LD_D_H_In : public Instruction { LD_D_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x54 LD D, H
struct LD_D_L_In : public Instruction { LD_D_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x55 LD D, L
struct LD_D_mHL_In : public Instruction { LD_D_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x56 LD D, (HL)
struct LD_D_A_In : public Instruction { LD_D_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x57 LD D, A
struct LD_E_B_In : public Instruction { LD_E_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x58 LD E, B
struct LD_E_C_In : public Instruction { LD_E_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x59 LD E, C
struct LD_E_D_In : public Instruction { LD_E_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x5A LD E, D
struct LD_E_E_In : public Instruction { LD_E_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x5B LD E, E
struct LD_E_H_In : public Instruction { LD_E_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x5C LD E, H
struct LD_E_L_In : public Instruction { LD_E_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x5D LD E, L
struct LD_E_mHL_In : public Instruction { LD_E_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x5E LD E, (HL)
struct LD_E_A_In : public Instruction { LD_E_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x5F LD E, A

// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

struct LD_H_B_In : public Instruction { LD_H_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x60 LD H, B
struct LD_H_C_In : public Instruction { LD_H_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x61 LD H, C
struct LD_H_D_In : public Instruction { LD_H_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x62 LD H, D
struct LD_H_E_In : public Instruction { LD_H_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x63 LD H, E
struct LD_H_H_In : public Instruction { LD_H_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x64 LD H, H
struct LD_H_L_In : public Instruction { LD_H_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x65 LD H, L
struct LD_H_mHL_In : public Instruction { LD_H_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x66 LD H, (HL)
struct LD_H_A_In : public Instruction { LD_H_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x67 LD H, A
struct LD_L_B_In : public Instruction { LD_L_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x68 LD L, B
struct LD_L_C_In : public Instruction { LD_L_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x69 LD L, C
struct LD_L_D_In : public Instruction { LD_L_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x6A LD L, D
struct LD_L_E_In : public Instruction { LD_L_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x6B LD L, E
struct LD_L_H_In : public Instruction { LD_L_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x6C LD L, H
struct LD_L_L_In : public Instruction { LD_L_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x6D LD L, L
struct LD_L_mHL_In : public Instruction { LD_L_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x6E LD L, (HL)
struct LD_L_A_In : public Instruction { LD_L_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x6F LD L, A

// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

struct LD_mHL_B_In : public Instruction { LD_mHL_B_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x70 LD (HL), B
struct LD_mHL_C_In : public Instruction { LD_mHL_C_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x71 LD (HL), C
struct LD_mHL_D_In : public Instruction { LD_mHL_D_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x72 LD (HL), D
struct LD_mHL_E_In : public Instruction { LD_mHL_E_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x73 LD (HL), E
struct LD_mHL_H_In : public Instruction { LD_mHL_H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x74 LD (HL), H
struct LD_mHL_L_In : public Instruction { LD_mHL_L_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x75 LD (HL), L
struct HALT_In : public Instruction { HALT_In(); virtual void op(LR35902& cpu, Memory& memory); };               // 0x76 HALT
struct LD_mHL_A_In : public Instruction { LD_mHL_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x77 LD (HL), A
struct LD_A_B_In : public Instruction { LD_A_B_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x78 LD A, B
struct LD_A_C_In : public Instruction { LD_A_C_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x79 LD A, C
struct LD_A_D_In : public Instruction { LD_A_D_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x7A LD A, D
struct LD_A_E_In : public Instruction { LD_A_E_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x7B LD A, E
struct LD_A_H_In : public Instruction { LD_A_H_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x7C LD A, H
struct LD_A_L_In : public Instruction { LD_A_L_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x7D LD A, L
struct LD_A_mHL_In : public Instruction { LD_A_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x7E LD A, (HL)
struct LD_A_A_In : public Instruction { LD_A_A_In(); virtual void op(LR35902& cpu, Memory& memory); };           // 0x7F LD A, A

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

struct ADD_A_B_In   : public Instruction {   ADD_A_B_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x80 ADD A, B
struct ADD_A_C_In   : public Instruction {   ADD_A_C_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x81 ADD A, C
struct ADD_A_D_In   : public Instruction {   ADD_A_D_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x82 ADD A, D
struct ADD_A_E_In   : public Instruction {   ADD_A_E_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x83 ADD A, E
struct ADD_A_H_In   : public Instruction {   ADD_A_H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x84 ADD A, H
struct ADD_A_L_In   : public Instruction {   ADD_A_L_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x85 ADD A, L
struct ADD_A_mHL_In : public Instruction { ADD_A_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x86 ADD A, (HL)
struct ADD_A_A_In   : public Instruction {   ADD_A_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x87 ADD A, A
struct ADC_A_B_In   : public Instruction {   ADC_A_B_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x88 ADC A, B
struct ADC_A_C_In   : public Instruction {   ADC_A_C_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x89 ADC A, C
struct ADC_A_D_In   : public Instruction {   ADC_A_D_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8A ADC A, D
struct ADC_A_E_In   : public Instruction {   ADC_A_E_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8B ADC A, E
struct ADC_A_H_In   : public Instruction {   ADC_A_H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8C ADC A, H
struct ADC_A_L_In   : public Instruction {   ADC_A_L_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8D ADC A, L
struct ADC_A_mHL_In : public Instruction { ADC_A_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8E ADC A, (HL)
struct ADC_A_A_In   : public Instruction {   ADC_A_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x8F ADC A, A

// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

struct SUB_B_In     : public Instruction {   SUB_B_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x90 SUB B
struct SUB_C_In     : public Instruction {   SUB_C_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x91 SUB C
struct SUB_D_In     : public Instruction {   SUB_D_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x92 SUB D
struct SUB_E_In     : public Instruction {   SUB_E_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x93 SUB E
struct SUB_H_In     : public Instruction {   SUB_H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x94 SUB H
struct SUB_L_In     : public Instruction {   SUB_L_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x95 SUB L
struct SUB_mHL_In   : public Instruction { SUB_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x96 SUB (HL)
struct SUB_A_In     : public Instruction {   SUB_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x97 SUB A
struct SBC_B_In     : public Instruction {   SBC_B_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x98 SBC B
struct SBC_C_In     : public Instruction {   SBC_C_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x99 SBC C
struct SBC_D_In     : public Instruction {   SBC_D_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9A SBC D
struct SBC_E_In     : public Instruction {   SBC_E_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9B SBC E
struct SBC_H_In     : public Instruction {   SBC_H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9C SBC H
struct SBC_L_In     : public Instruction {   SBC_L_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9D SBC L
struct SBC_mHL_In   : public Instruction { SBC_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9E SBC (HL)
struct SBC_A_In     : public Instruction {   SBC_A_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0x9F SBC A

// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

struct AND_B_In     : public Instruction {   AND_B_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA0
struct AND_C_In     : public Instruction {   AND_C_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA1
struct AND_D_In     : public Instruction {   AND_D_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA2
struct AND_E_In     : public Instruction {   AND_E_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA3
struct AND_H_In     : public Instruction {   AND_H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA4
struct AND_L_In     : public Instruction {   AND_L_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA5
struct AND_mHL_In   : public Instruction { AND_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA6
struct AND_A_In     : public Instruction {   AND_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA7
struct XOR_B_In     : public Instruction {   XOR_B_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA8
struct XOR_C_In     : public Instruction {   XOR_C_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xA9
struct XOR_D_In     : public Instruction {   XOR_D_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAA
struct XOR_E_In     : public Instruction {   XOR_E_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAB
struct XOR_H_In     : public Instruction {   XOR_H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAC
struct XOR_L_In     : public Instruction {   XOR_L_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAD
struct XOR_mHL_In   : public Instruction { XOR_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAE
struct XOR_A_In     : public Instruction {   XOR_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xAF

// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

struct OR_B_In     : public Instruction {   OR_B_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB0
struct OR_C_In     : public Instruction {   OR_C_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB1
struct OR_D_In     : public Instruction {   OR_D_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB2
struct OR_E_In     : public Instruction {   OR_E_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB3
struct OR_H_In     : public Instruction {   OR_H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB4
struct OR_L_In     : public Instruction {   OR_L_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB5
struct OR_mHL_In   : public Instruction { OR_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB6
struct OR_A_In     : public Instruction {   OR_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB7
struct CP_B_In     : public Instruction {   CP_B_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB8
struct CP_C_In     : public Instruction {   CP_C_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xB9
struct CP_D_In     : public Instruction {   CP_D_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBA
struct CP_E_In     : public Instruction {   CP_E_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBB
struct CP_H_In     : public Instruction {   CP_H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBC
struct CP_L_In     : public Instruction {   CP_L_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBD
struct CP_mHL_In   : public Instruction { CP_mHL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBE
struct CP_A_In     : public Instruction {   CP_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xBF

// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

struct RET_NZ_In      : public Instruction {      RET_NZ_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC0
struct POP_BC_In      : public Instruction {      POP_BC_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC1
struct JP_NZ_a16_In   : public Instruction {   JP_NZ_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC2
struct JP_a16_In      : public Instruction {      JP_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC3
struct CALL_NZ_a16_In : public Instruction { CALL_NZ_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC4
struct PUSH_BC_In     : public Instruction {     PUSH_BC_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC5
struct ADD_A_d8_In    : public Instruction {    ADD_A_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC6
struct RST_00H_In     : public Instruction {     RST_00H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC7
struct RET_Z_In       : public Instruction {       RET_Z_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC8
struct RET_In         : public Instruction {         RET_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xC9
struct JP_Z_a16_In    : public Instruction {    JP_Z_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xCA
struct PREFIX_CB_In   : public Instruction {   PREFIX_CB_In(); ~PREFIX_CB_In(); virtual void execute(LR35902& cpu, Memory& memory); virtual void op(LR35902& cpu, Memory& memory); std::vector<std::unique_ptr<Instruction> > _cb_instructions; };  // 0xCB
struct CALL_Z_a16_In  : public Instruction {  CALL_Z_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xCC
struct CALL_a16_In    : public Instruction {    CALL_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xCD
struct ADC_A_d8_In    : public Instruction {    ADC_A_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xCE
struct RST_08H_In     : public Instruction {     RST_08H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xCF

// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

struct RET_NC_In      : public Instruction {   RET_NC_In(); virtual void op(LR35902& cpu, Memory& memory); };     // 0xD0
struct POP_DE_In      : public Instruction {   POP_DE_In(); virtual void op(LR35902& cpu, Memory& memory); };     // 0xD1
struct JP_NC_a16_In   : public Instruction { JP_NC_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };    // 0xD2
// 0xD3: no operation for this opcode in LR35902
struct CALL_NC_a16_In : public Instruction { CALL_NC_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD4
struct PUSH_DE_In     : public Instruction {     PUSH_DE_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD5
struct SUB_d8_In      : public Instruction {      SUB_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD6
struct RST_10H_In     : public Instruction {     RST_10H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD7
struct RET_C_In       : public Instruction {       RET_C_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD8
struct RETI_In        : public Instruction {        RETI_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xD9
struct JP_C_a16_In    : public Instruction {    JP_C_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xDA
// 0xDB: no operation for this opcode in LR35902
struct  CALL_C_a16_In : public Instruction {  CALL_C_a16_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xDC
// 0xDD: no operation for this opcode in LR35902
struct SBC_A_d8_In    : public Instruction {    SBC_A_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xDE
struct RST_18H_In     : public Instruction {     RST_18H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xDF

// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

struct LDH_a8_A_In : public Instruction {   LDH_a8_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE0
struct   POP_HL_In : public Instruction {     POP_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE1
struct  LD_mC_A_In : public Instruction {    LD_mC_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE2
// 0xE3: no operation for this opcode in LR35902
// 0xE4: no operation for this opcode in LR35902
struct  PUSH_HL_In : public Instruction {  PUSH_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE5
struct   AND_d8_In : public Instruction {   AND_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE6
struct RST_20H_In  : public Instruction {  RST_20H_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE7
struct ADD_SP_r8_In: public Instruction {ADD_SP_r8_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE8
struct   JP_HL_In : public Instruction {   JP_HL_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xE9
struct LD_a16_A_In : public Instruction { LD_a16_A_In(); virtual void op(LR35902& cpu, Memory& memory); };  // 0xEA
// 0xEB: no operation for this opcode in LR35902
// 0xEC: no operation for this opcode in LR35902
// 0xED: no operation for this opcode in LR35902
struct   XOR_d8_In : public Instruction {   XOR_d8_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0xEE
struct  RST_28H_In : public Instruction {  RST_28H_In(); virtual void op(LR35902& cpu, Memory& memory); };       // 0xEF

// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

struct LDH_A_a8_In   : public Instruction { LDH_A_a8_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF0
struct POP_AF_In     : public Instruction {   POP_AF_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF1
struct  LD_A_mC_In   : public Instruction {  LD_A_mC_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF2
struct         DI_In : public Instruction {       DI_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF3
// 0xF4: no operation for this opcode in LR35902
struct    PUSH_AF_In : public Instruction {  PUSH_AF_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF5
struct      OR_d8_In : public Instruction {    OR_d8_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF6
struct   RST_30H_In  : public Instruction {  RST_30H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF7
struct LD_HL_SP_r8_In: public Instruction {  LD_HL_SP_r8_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF8
struct   LD_SP_HL_In : public Instruction { LD_SP_HL_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xF9
struct   LD_A_a16_In : public Instruction { LD_A_a16_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xFA
struct         EI_In : public Instruction {       EI_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xFB
// 0xFC: no operation for this opcode in LR35902
// 0xFD: no operation for this opcode in LR35902
struct      CP_d8_In : public Instruction {    CP_d8_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xFE
struct    RST_38H_In : public Instruction {  RST_38H_In(); virtual void op(LR35902& cpu, Memory& memory); }; // 0xFF

#endif
