#ifndef PATCHDOL_H
#define PATCHDOL_H

typedef enum {
	_ADDI = 14,
	_ADDIS = 15,
	_BRANCH = 18,
	_BCCTR = 19,
	_MTSPR = 31
} OPCODES;

typedef enum {
	_XER = 1,
	_LR = 8,
	_CTR = 9
} SPR;

// Big Endian
typedef struct {
	union {
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			int LI : 24; // Immediate field (23 bit + sign)
			unsigned AA : 1; // Absolute Address
			unsigned LK : 1; // update LinK
		} I; // Immediate
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned BO : 5; // Branch Option
			unsigned BI : 5; // Branch If
			unsigned BD : 14; // Branch Displacement (13 bits + sign)
			unsigned AA : 1; // Absolute Address
			unsigned LK : 1; // update LinK
		} B; // Branch
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned _r : 14; // Reserved
			unsigned LEVI : 7; // Level
			unsigned _r2 : 3; // Reserved 
			unsigned one : 1; // constant 1
			unsigned _r3 : 1; // Reserved
		} SC; // Supervisor Call
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned RT : 5; // Target
			unsigned RA : 5; // Source or Target
			unsigned D : 16; // Data | SI: Signed Integer			
		} D;
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned RT : 5; // Target
			unsigned RA : 5; // Source or Target
			unsigned DS : 14; // Signed immediate concatenated with 0x0B00
			unsigned XO : 2; // eXtended Opcode			
		} DS; // Data Sign?
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned RT : 5; // Target
			unsigned RA : 5; // Source or Target
			unsigned RB : 5; // Source or Target
			unsigned XO : 10; // eXtended Opcode
			unsigned _r : 1; // Reserved
		} X;
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned BO : 5; // Target
			unsigned BI : 5; // Source or Target
			unsigned _r2 : 3; // Source or Target
			unsigned BH : 2; // Source or Target
			unsigned XO : 10; // eXtended Opcode
			unsigned LK : 1; // Reserved or Rc or 1
		} XL;
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned RT : 5; // Target/Source
			unsigned spr : 10; // Source or Target
			unsigned XO : 10; // eXtended Opcode
			unsigned _reserved : 1; // Reserved
		} XFX;
		struct {
			// 32
			unsigned OPCD : 6; // OPCoDe
			unsigned _r1 : 1; // Reserved
			unsigned FLM : 8; // FLoating Mask
			unsigned _r2 : 1; // Reserved
			unsigned FRB : 5; // Source FPR
			unsigned XO : 10; // eXtended Opcode
			unsigned Rc : 1; // Record
		} XFL;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned RS : 5; // Source
			unsigned RA : 5; // Arg

			unsigned sh : 5; // shift
			unsigned XO : 9; // eXtended Opcode
			unsigned sh2 : 1; // shift
			unsigned Rc : 1; // Record
		} XS;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned RT : 5; // Target
			unsigned RA : 5; // Arg
			unsigned RB : 5; // shift
			unsigned OE : 1; // Overflow Enable
			unsigned XO : 9; // eXtended Opcode
			unsigned Rc : 1; // Record
		} XO;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned FRT : 5; // Target
			unsigned FRA : 5; // Arg
			unsigned FRB : 5; // shift
			unsigned FRC : 5; // Overflow Enable
			unsigned XO : 5; // eXtended Opcode
			unsigned Rc : 1; // Record
		} A;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned RS : 5; // Source
			unsigned RA : 5; // Arg A
			unsigned RB : 5; // Arg B
			unsigned MB : 5; // Mask Begin
			unsigned ME : 5; // Mask End
			unsigned Rc : 1; // Record
		} M;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned RS : 5; // Source
			unsigned RA : 5; // Arg A
			unsigned sh : 5; // Arg B
			unsigned XO : 3; // eXtended Opcode
			unsigned MB : 6; // Mask Begin
			unsigned sh2 : 1; // Mask End
			unsigned Rc : 1; // Record
		} MD;
		struct {
			unsigned OPCD : 6; // OPCoDe
			unsigned RS : 5; // Source
			unsigned RA : 5; // Arg A
			unsigned RB : 5; // Arg B
			unsigned MBE : 3; // Mask Begin/End
			unsigned XO : 1; // Mask End
			unsigned Rc : 1; // Record
		} MDS;
	};
} __attribute__((packed)) ppc_instruction;

#define PPCI(form, opc, ...) (ppc_instruction){form = {.OPCD = opc, __VA_ARGS__}}

#define ADDIS(target, a, i) PPCI(.D,   _ADDIS, .RT = target, .RA = a, .D = (i >> 16) + !!(i & 0x8000))
#define ADDI(target, a, i)  PPCI(.D,   _ADDI,  .RT = target, .RA = a, .D = i & 0xFFFF)
#define MTCTR(x)            PPCI(.XFX, _MTSPR, .RT = x, .spr = _CTR, .XO = 467);
#define BCTRL				PPCI(.XL,  _BCCTR, .BO = 0x14, .BI = 0, .BH = 0, .XO = 528, .LK = 1)
#define BL(off)             PPCI(.I, _BRANCH, .LI = off, .AA = 0, .LK = 1);
#define B(off)              PPCI(.I, _BRANCH, .LI = off, .AA = 0, .LK = 0);

#endif /* PATCHDOL_H */