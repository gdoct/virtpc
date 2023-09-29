#ifndef OPCODES_H
#define OPCODES_H

#include "numbers.h"

enum Opcodes : Byte {
	BRK = 0x00,
	ORA_X_IND = 0x01,
	ORA_ZP = 0x05,
	ASL_ZP = 0x06,
	PHP = 0x08,
	ORA_IMM = 0x09,
	ASL_A = 0x0A,
	ORA_ABS = 0x0D,
	ASL_ABS = 0x0E,
	BPL_REL = 0x10,
	ORA_IND_Y = 0x11,
	ORA_ZP_X = 0x15,
	ASL_ZP_X = 0x16,
	CLC = 0x18,
	ORA_ABS_Y = 0x19,
	ORA_ABS_X = 0x1D,
	ASL_ABS_X = 0x1E,
	JSR_ABS = 0x20,
	AND_X_IND = 0x21,
	BIT_ZP = 0x24,
	AND_ZP = 0x25,
	ROL_ZP = 0x26,
	PLP = 0x28,
	AND_IMM = 0x29,
	ROL_A = 0x2A,
	BIT_ABS = 0x2C,
	AND_ABS = 0x2D,
	ROL_ABS = 0x2E,
	BMI_REL = 0x30,
	AND_IND_Y = 0x31,
	AND_ZP_X = 0x35,
	ROL_ZP_X = 0x36,
	SEC = 0x38,
	AND_ABS_Y = 0x39,
	AND_ABS_X = 0x3D,
	ROL_ABS_X = 0x3E,
	RTI_IMP = 0x40,
	EOR_X_IND = 0x41,
	EOR_ZP = 0x45,
	LSR_ZP = 0x46,
	PHA_IMP = 0x48,
	EOR_IMM = 0x49,
	LSR_A = 0x4A,
	JMP_ABS = 0x4C,
	EOR_ABS = 0x4D,
	LSR_ABS = 0x4E,
	BVC_REL = 0x50,
	EOR_IND_Y = 0x51,
	EOR_ZP_X = 0x55,
	LSR_ZP_X = 0x56,
	CLI = 0x58,
	EOR_ABS_Y = 0x59,
	EOR_ABS_X = 0x5D,
	LSR_ABS_X = 0x5E,
	RTS_IMP = 0x60,
	ADC_X_IND = 0x61,
	ADC_ZP = 0x65,
	ROR_ZP = 0x66,
	PLA_IMP = 0x68,
	ADC_IMM = 0x69,
	ROR_A = 0x6A,
	JMP_IND = 0x6C,
	ADC_ABS = 0x6D,
	ROR_ABS = 0x6E,
	BVS_REL = 0x70,
	ADC_IND_Y = 0x71,
	ADC_ZP_X = 0x75,
	ROR_ZP_X = 0x76,
	SEI = 0x78,
	ADC_ABS_Y = 0x79,
	ADC_ABS_X = 0x7D,
	ROR_ABS_X = 0x7E,
	STA_X_IND = 0x81,
	STY_ZP = 0x84,
	STA_ZP = 0x85,
	STX_ZP = 0x86,
	DEY_IMP = 0x88,
	TXA_IMP = 0x8A,
	STY_ABS = 0x8C,
	STA_ABS = 0x8D,
	STX_ABS = 0x8E,
	BCC_REL = 0x90,
	STA_IND_Y = 0x91,
	STY_ZP_X = 0x94,
	STA_ZP_X = 0x95,
	STX_ZP_Y = 0x96,
	TYA_IMP = 0x98,
	STA_ABS_Y = 0x99,
	TXS_IMP = 0x9A,
	STA_ABS_X = 0x9D,
	LDY_IMM = 0xA0,
	LDA_X_IND = 0xA1,
	LDY_ZP = 0xA4,
	LDA_ZP = 0xA5,
	LDX_ZP = 0xA6,
	TAY_IMP = 0xA8,
	LDA_IMM = 0xA9,
	TAX_IMP = 0xAA,
	LDY_ABS = 0xAC,
	LDA_ABS = 0xAD,
	LDX_ABS = 0xAE,
	BCS_REL = 0xB0,
	LDA_IND_Y = 0xB1,
	LDY_ZP_X = 0xB4,
	LDA_ZP_X = 0xB5,
	LDX_ZP_Y = 0xB6,
	CLV_IMP = 0xB8,
	LDA_ABS_Y = 0xB9,
	TSX_IMP = 0xBA,
	LDY_ABS_X = 0xBC,
	LDA_ABS_X = 0xBD,
	LDX_ABS_Y = 0xBE,
	CPY_IMM = 0xC0,
	CMP_X_IND = 0xC1,
	CPY_ZP = 0xC4,
	CMP_ZP = 0xC5,
	DEC_ZP = 0xC6,
	INY_IMP = 0xC8,
	CMP_IMM = 0xC9,
	DEX_IMP = 0xCA,
	CMP_ABS = 0xCD,
	DEC_ABS = 0xCE,
	BNE_REL = 0xD0,
	CMP_IND_Y = 0xD1,
	CMP_ZP_X = 0xD5,
	DEC_ZP_X = 0xD6,
	CLD_IMP = 0xD8,
	CMP_ABS_Y = 0xD9,
	CMP_ABS_X = 0xDD,
	DEC_ABS_X = 0xDE,
	CPX_IMM = 0xE0,
	SBC_X_IND = 0xE1,
	CPX_ZP = 0xE4,
	SBC_ZP = 0xE5,
	INC_ZP = 0xE6,
	INX_IMP = 0xE8,
	SBC_IMM = 0xE9,
	NOP_IMP = 0xEA,
	CPX_ABS = 0xEC,
	SBC_ABS = 0xED,
	INC_ABS = 0xEE,
	BEQ_REL = 0xF0,
	SBC_IND_Y = 0xF1,
	SBC_ZP_X = 0xF5,
	INC_ZP_X = 0xF6,
	SED_IMP = 0xF8,
	SBC_ABS_Y = 0xF9,
	SBC_ABS_X = 0xFD,
	INC_ABS_X = 0xFE,
};

static Opcodes opcode_parse(Byte data) {
	switch (data) {
	case Opcodes::BRK:
	case Opcodes::ORA_X_IND:
	case Opcodes::ORA_ZP:
	case Opcodes::ASL_ZP:
	case Opcodes::PHP:
	case Opcodes::ORA_IMM:
	case Opcodes::ASL_A:
	case Opcodes::ORA_ABS:
	case Opcodes::ASL_ABS:
	case Opcodes::BPL_REL:
	case Opcodes::ORA_IND_Y:
	case Opcodes::ORA_ZP_X:
	case Opcodes::ASL_ZP_X:
	case Opcodes::CLC:
	case Opcodes::ORA_ABS_Y:
	case Opcodes::ORA_ABS_X:
	case Opcodes::ASL_ABS_X:
	case Opcodes::JSR_ABS:
	case Opcodes::AND_X_IND:
	case Opcodes::BIT_ZP:
	case Opcodes::AND_ZP:
	case Opcodes::ROL_ZP:
	case Opcodes::PLP:
	case Opcodes::AND_IMM:
	case Opcodes::ROL_A:
	case Opcodes::BIT_ABS:
	case Opcodes::AND_ABS:
	case Opcodes::ROL_ABS:
	case Opcodes::BMI_REL:
	case Opcodes::AND_IND_Y:
	case Opcodes::AND_ZP_X:
	case Opcodes::ROL_ZP_X:
	case Opcodes::SEC:
	case Opcodes::AND_ABS_Y:
	case Opcodes::AND_ABS_X:
	case Opcodes::ROL_ABS_X:
	case Opcodes::RTI_IMP:
	case Opcodes::EOR_X_IND:
	case Opcodes::EOR_ZP:
	case Opcodes::LSR_ZP:
	case Opcodes::PHA_IMP:
	case Opcodes::EOR_IMM:
	case Opcodes::LSR_A:
	case Opcodes::JMP_ABS:
	case Opcodes::EOR_ABS:
	case Opcodes::LSR_ABS:
	case Opcodes::BVC_REL:
	case Opcodes::EOR_IND_Y:
	case Opcodes::EOR_ZP_X:
	case Opcodes::LSR_ZP_X:
	case Opcodes::CLI:
	case Opcodes::EOR_ABS_Y:
	case Opcodes::EOR_ABS_X:
	case Opcodes::LSR_ABS_X:
	case Opcodes::RTS_IMP:
	case Opcodes::ADC_X_IND:
	case Opcodes::ADC_ZP:
	case Opcodes::ROR_ZP:
	case Opcodes::PLA_IMP:
	case Opcodes::ADC_IMM:
	case Opcodes::ROR_A:
	case Opcodes::JMP_IND:
	case Opcodes::ADC_ABS:
	case Opcodes::ROR_ABS:
	case Opcodes::BVS_REL:
	case Opcodes::ADC_IND_Y:
	case Opcodes::ADC_ZP_X:
	case Opcodes::ROR_ZP_X:
	case Opcodes::SEI:
	case Opcodes::ADC_ABS_Y:
	case Opcodes::ADC_ABS_X:
	case Opcodes::ROR_ABS_X:
	case Opcodes::STA_X_IND:
	case Opcodes::STY_ZP:
	case Opcodes::STA_ZP:
	case Opcodes::STX_ZP:
	case Opcodes::DEY_IMP:
	case Opcodes::TXA_IMP:
	case Opcodes::STY_ABS:
	case Opcodes::STA_ABS:
	case Opcodes::STX_ABS:
	case Opcodes::BCC_REL:
	case Opcodes::STA_IND_Y:
	case Opcodes::STY_ZP_X:
	case Opcodes::STA_ZP_X:
	case Opcodes::STX_ZP_Y:
	case Opcodes::TYA_IMP:
	case Opcodes::STA_ABS_Y:
	case Opcodes::TXS_IMP:
	case Opcodes::STA_ABS_X:
	case Opcodes::LDY_IMM:
	case Opcodes::LDA_X_IND:
	case Opcodes::LDY_ZP:
	case Opcodes::LDA_ZP:
	case Opcodes::LDX_ZP:
	case Opcodes::TAY_IMP:
	case Opcodes::LDA_IMM:
	case Opcodes::TAX_IMP:
	case Opcodes::LDY_ABS:
	case Opcodes::LDA_ABS:
	case Opcodes::LDX_ABS:
	case Opcodes::BCS_REL:
	case Opcodes::LDA_IND_Y:
	case Opcodes::LDY_ZP_X:
	case Opcodes::LDA_ZP_X:
	case Opcodes::LDX_ZP_Y:
	case Opcodes::CLV_IMP:
	case Opcodes::LDA_ABS_Y:
	case Opcodes::TSX_IMP:
	case Opcodes::LDY_ABS_X:
	case Opcodes::LDA_ABS_X:
	case Opcodes::LDX_ABS_Y:
	case Opcodes::CPY_IMM:
	case Opcodes::CMP_X_IND:
	case Opcodes::CPY_ZP:
	case Opcodes::CMP_ZP:
	case Opcodes::DEC_ZP:
	case Opcodes::INY_IMP:
	case Opcodes::CMP_IMM:
	case Opcodes::DEX_IMP:
	case Opcodes::CMP_ABS:
	case Opcodes::DEC_ABS:
	case Opcodes::BNE_REL:
	case Opcodes::CMP_IND_Y:
	case Opcodes::CMP_ZP_X:
	case Opcodes::DEC_ZP_X:
	case Opcodes::CLD_IMP:
	case Opcodes::CMP_ABS_Y:
	case Opcodes::CMP_ABS_X:
	case Opcodes::DEC_ABS_X:
	case Opcodes::CPX_IMM:
	case Opcodes::SBC_X_IND:
	case Opcodes::CPX_ZP:
	case Opcodes::SBC_ZP:
	case Opcodes::INC_ZP:
	case Opcodes::INX_IMP:
	case Opcodes::SBC_IMM:
	case Opcodes::NOP_IMP:
	case Opcodes::CPX_ABS:
	case Opcodes::SBC_ABS:
	case Opcodes::INC_ABS:
	case Opcodes::BEQ_REL:
	case Opcodes::SBC_IND_Y:
	case Opcodes::SBC_ZP_X:
	case Opcodes::INC_ZP_X:
	case Opcodes::SED_IMP:
	case Opcodes::SBC_ABS_Y:
	case Opcodes::SBC_ABS_X:
	case Opcodes::INC_ABS_X:
		return (Opcodes)data;
	default:
		return Opcodes::NOP_IMP;
	}
}
#endif