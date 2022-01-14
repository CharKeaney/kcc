
#ifndef CODE_GEN_H
#define CODE_GEN_H 1

#include "semantics.h"

#define report_alloc(r) cout << "codegen.h:"				 \
							 << "reg_alloc:"				 \
						     << "allocating..."				 \
							 << x86_register_string_reprs[r] \
						     << endl;

#define report_gen(m) cout << "codegen.h:"					 \
					       << m								 \
					       << ": generating..."				 \
					       << endl

#define gen(s, r, i) gen_translation_unit(s, r, i)

enum class CodeGeneratorExitCode {
	SUCCESS,
	FAILURE
};

enum class x86_AssemblyInstructionMnemonic {
	ADD,
	SUB,
	INC,
	DEC,
	MULSS,
	DIV,
	PUSHQ,
	POPQ,
	CALL,
	RETQ,
	MOVSS,
	MOVQ,
	CMP,
	JE,
	JNE,
	JG,
	JGE,
	JL,
	JLE,
	JMP,
	SETE,
	SETNE,
	SETG,
	SETGE,
	SETL,
	SETLE,
	/* Literal constant types */
	LONG
};

static const char* x86_assembly_instruction_mnemonic_string_reprs[] {
	"add",
	"sub",
	"inc",
	"dec",
	"mulss",
	"div",
	"pushq",
	"popq",
	"call",
	"retq",
	"movss",
	"movq",
	"cmp",
	"je",
	"jne",
	"jg",
	"jge",
	"jl",
	"jle",
	"jmp",
	"sete",
	"setne",
	"setg",
	"setge",
	"setl",
	"setle",
	".long"
};

enum class x86_Register {
	RAX,
	RBX,
	RCX,
	RDX,
	RSI,
	RDI,
	RSP,
	RBP,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	XMM0,
	RIP
};

static const char* x86_register_string_reprs[] = {
	"rax",
	"rbx",
	"rcx",
	"rdx",
	"rsi",
	"rdi",
	"rsp",
	"rbp",
	"r8",
	"r9",
	"r10",
	"r11",
	"r12",
	"r13",
	"r14",
	"r15",
	"xmm0",
	"rip"
};

typedef uint32_t	x86_RegisterAllocMap;

typedef	uint8_t		byte_unsigned_integer;
typedef uint16_t	word_unsigned_integer;
typedef uint32_t	doubleword_unsigned_integer;
typedef uint64_t	quadword_unsigned_integer;
typedef int8_t		byte_signed_integer;
typedef int16_t		word_signed_integer;
typedef int32_t		doubleword_signed_integer;
typedef int64_t		quadword_signed_integer;
typedef int16_t		half_precision_floating_point;
typedef int32_t     single_precision_floating_point;
typedef int64_t     double_precision_floating_point;
typedef long double	double_extended_precision_floating_point;

typedef uint64_t	near_pointer;
typedef long double	far_pointer_with_64_bit_operand_size;
typedef uint64_t	far_pointer_with_32_bit_operand_size;

typedef struct register_and_offset {
	signed long offset;
	x86_Register reg;
} register_and_offset;

typedef struct label_and_register {
	const char* label;
	x86_Register reg;
} label_and_register;

enum class x86_AssemblyInstructionOperandType {
	X86_REGISTER_INDEX,
	X86_REGISTER_CONTAINING_ADDR,
	BYTE_UNSIGNED_INTEGER,
	WORD_UNSIGNED_INTEGER,
	DOUBLEWORD_UNSIGNED_INTEGER,
	QUADWORD_UNSIGNED_INTEGER, 
	BYTE_SIGNED_INTEGER,
	WORD_SIGNED_INTEGER,
	DOUBLEWORD_SIGNED_INTEGER,
	QUADWORD_SIGNED_INTEGER,
	HALF_PRECISION_FLOATING_POINT,
	SINGLE_PRECISION_FLOATING_POINT,
	DOUBLE_PRECISION_FLOATING_POINT,
	DOUBLE_EXTENDED_PRECISION_FLOATING_POINT,
	NEAR_POINTER,
	FAR_POINTER_WITH_64_BIT_OPERAND_SIZE,
	FAR_POINTER_WITH_32_BIT_OPERAND_SIZE,
	LABEL_AND_REGISTER,
	REGISTER_AND_OFFSET
};

typedef union x86_RegisterInstructionOperandVal {
	x86_Register reg_index;
	x86_Register reg_containing_addr;
	byte_unsigned_integer bui;
	word_unsigned_integer wui;
	doubleword_unsigned_integer dwui;
	quadword_unsigned_integer qwui;
	byte_signed_integer bsi;
	word_signed_integer wsi;
	doubleword_signed_integer dwsi;
	quadword_signed_integer qwsi;
	half_precision_floating_point hpfp;
	single_precision_floating_point spfp;
	double_precision_floating_point dpfp;
	double_extended_precision_floating_point depfp;
	near_pointer np;
	far_pointer_with_64_bit_operand_size fpw64bos;
	far_pointer_with_32_bit_operand_size fpw32bos;
	register_and_offset rao;
	label_and_register lar;
};

class x86_AssemblyInstructionOperand {
private:
	x86_AssemblyInstructionOperandType type;
	x86_RegisterInstructionOperandVal val;
	const char* lexeme;
public:
	x86_AssemblyInstructionOperand()
		: type(x86_AssemblyInstructionOperandType()), 
		  val(x86_RegisterInstructionOperandVal()) { }

	x86_AssemblyInstructionOperand(
		x86_AssemblyInstructionOperandType t,
		x86_RegisterInstructionOperandVal v)
		: type(t), val(v) { }

	inline void print() const {
		switch (type) {
			case x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX:
				cout << "%" 
					 << x86_register_string_reprs[(int)val.reg_index];
				break;
			case x86_AssemblyInstructionOperandType::X86_REGISTER_CONTAINING_ADDR:
				cout << "["
					 << x86_register_string_reprs[(int)val.reg_containing_addr]
					 << "]";
				break;
			case x86_AssemblyInstructionOperandType::BYTE_UNSIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::WORD_UNSIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::DOUBLEWORD_UNSIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::QUADWORD_UNSIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::BYTE_SIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::WORD_SIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::DOUBLEWORD_SIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::QUADWORD_SIGNED_INTEGER:
			case x86_AssemblyInstructionOperandType::HALF_PRECISION_FLOATING_POINT:
			case x86_AssemblyInstructionOperandType::SINGLE_PRECISION_FLOATING_POINT:
			case x86_AssemblyInstructionOperandType::DOUBLE_PRECISION_FLOATING_POINT:
			case x86_AssemblyInstructionOperandType::DOUBLE_EXTENDED_PRECISION_FLOATING_POINT:
				cout << (unsigned long long) val.dwui;
				break;
			case x86_AssemblyInstructionOperandType::NEAR_POINTER:
				cout << "[" 
					 << "0x"
					 << std::right
					 << std::hex
					 << std::setw(8)
					 << std::setfill('0')
					 << val.np
					 << "]";
				break;
			case x86_AssemblyInstructionOperandType::FAR_POINTER_WITH_64_BIT_OPERAND_SIZE:
			case x86_AssemblyInstructionOperandType::FAR_POINTER_WITH_32_BIT_OPERAND_SIZE:
				break;
			case x86_AssemblyInstructionOperandType::LABEL_AND_REGISTER:
				cout << val.lar.label
					 << "("
					 << "%" << x86_register_string_reprs[(int)val.lar.reg]
					 << ")";
				break;

			case x86_AssemblyInstructionOperandType::REGISTER_AND_OFFSET:
			{
				signed int offset = (int) val.rao.offset;
				cout << std::dec 
					 << offset 
					 << "("
					 << "%" << x86_register_string_reprs[(int)val.rao.reg]
					 << ")";
				break;
			}

			default:
				break;
		};
	}
};

enum class x86_AssemblyInstructionType {
	LABELED_INSTRUCTION,
	INSTRUCTION,
};

class x86_AssemblyInstruction {
private:	
	x86_AssemblyInstructionType type;
	const char* label;
	x86_AssemblyInstructionMnemonic mnemonic;
	const x86_AssemblyInstructionOperand* op1;
	const x86_AssemblyInstructionOperand* op2;
	const x86_AssemblyInstructionOperand* op3;

	inline void construct_x86_AssemblyInstruction_add(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_sub(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_inc(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_dec(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_mulss(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_div(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_pushq(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_pop(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3)
	{

	}

	inline void construct_x86_AssemblyInstruction_call(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_ret(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_movss(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_cmp(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_je(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jne(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jg(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jge(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jl(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jle(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_jmp(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_sete(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_setne(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_setg(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_setge(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_setl(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline void construct_x86_AssemblyInstruction_setle(
		x86_AssemblyInstructionOperand const& op1,
		x86_AssemblyInstructionOperand const& op2,
		x86_AssemblyInstructionOperand const& op3) 
	{

	}

	inline x86_AssemblyInstruction(
		x86_AssemblyInstructionType t,
		const char* l,
		x86_AssemblyInstructionMnemonic m,
		x86_AssemblyInstructionOperand* o1,
		x86_AssemblyInstructionOperand* o2,
		x86_AssemblyInstructionOperand* o3)
		: type(t),
		  mnemonic(m),
		  op1(o1),
		  op2(o2),
		  op3(o3) {
	}
public:
	inline x86_AssemblyInstruction() {};

	inline void set_label(const char* const& l) { label = l; };

	inline void set_type(x86_AssemblyInstructionType const& t) { type = t; };


	inline x86_AssemblyInstruction(
		x86_AssemblyInstructionMnemonic m)
	{
		switch (m) {

			case x86_AssemblyInstructionMnemonic::RETQ:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::RETQ;
				op1 = NULL;
				op2 = NULL;
				op3 = NULL;
				break;
			}
			
			default:
				break;
		}
		this->print();
	}

	inline x86_AssemblyInstruction(
		x86_AssemblyInstructionMnemonic m,
		const x86_AssemblyInstructionOperand* o1)
	{
		switch (m) {

			case x86_AssemblyInstructionMnemonic::LONG:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::LONG;
				op1 = o1;
				op2 = NULL;
				op3 = NULL;
				break;
			}

			case x86_AssemblyInstructionMnemonic::PUSHQ:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::PUSHQ;
				op1 = o1;
				op2 = NULL;
				op3 = NULL;
				break;
			}

			case x86_AssemblyInstructionMnemonic::POPQ:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::POPQ;
				op1 = o1;
				op2 = NULL;
				op3 = NULL;
				break;
			}

			default:
				break;
		}
		this->print();
	}

	inline x86_AssemblyInstruction(
		x86_AssemblyInstructionMnemonic m,
		const x86_AssemblyInstructionOperand* o1,
		const x86_AssemblyInstructionOperand* o2)
	{
		switch (m) {

			case x86_AssemblyInstructionMnemonic::ADD:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::SUB:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::INC:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::DEC:
			{
				break;
			}
			
			
			case x86_AssemblyInstructionMnemonic::DIV:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::PUSHQ:
			{
				break;
			}
			
			
			case x86_AssemblyInstructionMnemonic::CALL:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::RETQ:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::MOVSS:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::MOVSS;
				op1 = o1;
				op2 = o2;
				op3 = NULL;
				break;
			}

			case x86_AssemblyInstructionMnemonic::MOVQ:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::MOVQ;
				op1 = o1;
				op2 = o2;
				op3 = NULL;
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::CMP:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::JE:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::JNE:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::JG:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::JGE:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::JL:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::JLE:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::JMP:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::SETE:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::SETNE:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::SETG:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::SETGE:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::SETL:
			{
				break;
			}
			
			case x86_AssemblyInstructionMnemonic::SETLE:
			{
				break;
			}

			case x86_AssemblyInstructionMnemonic::MULSS:
			{
				type = x86_AssemblyInstructionType::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_AssemblyInstructionMnemonic::MULSS;
				op1 = o1;
				op2 = o2;
				op3 = NULL;
				break;
			}

			default: 
				break;
		}
		this->print();
	}

	inline void print() const {
		if (type == x86_AssemblyInstructionType::LABELED_INSTRUCTION) {
			cout << label;
			cout << ":" 
				 << endl;
		} 
		cout << "\t";	
		cout << x86_assembly_instruction_mnemonic_string_reprs[(int)mnemonic];
		
		cout << " ";
		if (op1) {
			op1->print();
		}			
		if (op2) {
			cout << ", ";
			op2->print();
		}
		if (op3) {			
			cout << ", ";
			op3->print();
		}
		cout << endl;
	}
};

static inline x86_Register reg_alloc(
	x86_RegisterAllocMap& map);

static inline CodeGeneratorExitCode gen_primary_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_postfix_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_unary_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_cast_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_multiplicative_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_additive_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_shift_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_relational_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_equality_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_and_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_exclusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_inclusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_logical_and_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_exlusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_logical_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_conditional_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_assignment_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand); 

static inline CodeGeneratorExitCode gen_constant_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register);

/* Declarations. */

static inline CodeGeneratorExitCode gen_declaration(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_declaration_specifiers(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register);

static inline CodeGeneratorExitCode gen_init_declarator_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_init_declarator(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_initializer(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_initializer_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register);

/* Statements. */

static inline CodeGeneratorExitCode gen_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_labeled_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_compound_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_block_item_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_block_item(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_expression_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand);

static inline CodeGeneratorExitCode gen_selection_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_iteration_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_jump_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

/* External definitions. */

static inline CodeGeneratorExitCode gen_translation_unit(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_external_declaration(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_function_definition(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs);

static inline CodeGeneratorExitCode gen_declaration_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register);

static inline x86_Register reg_alloc(
	x86_RegisterAllocMap& map)
{
	x86_RegisterAllocMap m = map;
	int i = 0;
	while ((m % 2) != 0) {
		m >>= 1;
		i++;
	}
	map += (1 << i);
	report_alloc(i);
	return (x86_Register) i;
}

static inline CodeGeneratorExitCode gen_symbol(
	StackDescriptor* const& stack,
	SymbolTableEntry* const& symbol_entry,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_AssemblyInstructionOperand& operand)
{
	report_gen("gen_identifier");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

 	switch (symbol_entry->scope) {

		case Scope::FUNCTION:
		{
			register_and_offset rao;
			rao.offset
				= symbol_entry->base_pointer_offset
				  - symbol_entry->function_frame_size;

			rao.reg
				= x86_Register::RBP;

			x86_RegisterInstructionOperandVal v;
			v.rao = rao;

			operand
				= x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::REGISTER_AND_OFFSET,
					v);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case Scope::GLOBAL:
		{
			//TODO;
			/*register_and_offset rao;
			rao.offset
				= sym_entry->base_pointer_offset;
			rao.reg
				= x86_Register::RSP;

			x86_RegisterInstructionOperandVal v;
			v.rao = rao;

			output_operand
				= x86_AssemblyInstructionOperand(
					x86_RegisterInstructionOperandType::REGISTER_AND_OFFSET,
					v);*/
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_literals(
	SymbolTable* const& symbol_table,
	x86_AssemblyInstruction*& instrs)
{
	report_gen("gen_literals");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;
	
	SymbolTableEntry* entries[1028] = { };
	symbol_table->get_entries(entries);
	/* for each entry in the symbol table */
	int literal_constant_ptr_i = 0;
	for (SymbolTableEntry** e = entries;
		 *e != NULL;
		 e++) {

		if ((*e)->is_literal) {
			char* label_str = new char[16]{ '.', 'L', 'C', 'P', '_' };
			_itoa_s(literal_constant_ptr_i++, label_str + 5, 11, 10);
			(*e)->literal_constant_ptr_label = label_str;
			x86_RegisterInstructionOperandVal v;
			v.dwui = (*e)->value;
			*instrs = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::LONG,
				new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::DOUBLEWORD_UNSIGNED_INTEGER,
					v));
			instrs->set_label(label_str);
			instrs->set_type(x86_AssemblyInstructionType::LABELED_INSTRUCTION);
			instrs++;
		}
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_primary_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_AssemblyInstructionOperand &operand)
{
	report_gen("gen_primary_expression");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;
	switch (node->get_alt()) {

		case AstNodeAlt::PRIMARY_EXPRESSION_1:
		{
			gen_symbol(
				stack,
				node->get_symbol_table()
				    ->get_entry(node->get_symbol()),
				instrs,
				alloc_map,
				operand);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_2:
		{
			exitcode = CodeGeneratorExitCode::SUCCESS;
			x86_RegisterAllocMap literal_alloc_map 
						= alloc_map;

			label_and_register lar;
			lar.label
				= node->get_child()
				      ->get_terminal()
				      ->get_lexeme();
			lar.reg
				= x86_Register::RIP;

			x86_RegisterInstructionOperandVal v;
			v.lar = lar;

			operand
				= x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::LABEL_AND_REGISTER,
					v);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_3:
			break;

		case AstNodeAlt::PRIMARY_EXPRESSION_4:
			break;

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_postfix_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_postfix_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::POSTFIX_EXPRESSION_1:
	{
		AnnotatedAstNode* primary_expression
			= node->get_child();
		if (gen_primary_expression(
			stack,
			primary_expression,
			instrs,
			alloc_map,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_2:
	{
		//	/* Loading AST data. */
		//	AnnotatedAstNode* postfix_expression 
		//		= node->get_child();
		//	AnnotatedAstNode* expression 
		//		= postfix_expression->get_sibling();
		//	
		//	/* Compute the array address */
		//	x86_RegisterAllocMap postfix_alloc_map
		//		= alloc_map;
		//	x86_Register postfix_register
		//		= reg_alloc(postfix_alloc_map);
		//	gen_postfix_expression(
		//		stack,
		//		postfix_expression,
		//		instrs, 
		//		postfix_alloc_map,
		//		postfix_register);
		//
		//	/* Compute the index */
		//	x86_RegisterAllocMap expression_alloc_map
		//		= alloc_map;
		//	x86_Register expression_register
		//		= reg_alloc(expression_alloc_map);
		//	if (gen_expression(
		//			stack,
		//			expression,
		//			instrs,
		//			expression_alloc_map,
		//			expression_register)
		//		== CodeGeneratorExitCode::SUCCESS) {
		//		exitcode = CodeGeneratorExitCode::FAILURE;
		//		break;
		//	}
		//
		//	/* Computing the offset */
		//	*instrs++ = construct_mov_instruction(
		//		r1,
		//		x86_Register::EAX
		//	);
		//
		//	/**instrs++ = construct_mul_instruction(
		//		size_of(postfix_expression->get_type())
		//	);*/
		//	/* Pop array address from stack */
		//	*instrs++ = construct_pop_instruction(
		//		postfix_register
		//	);
		//
		//	/* Computing the address of the indexed array. */
		//	*instrs++ = construct_add_instruction(
		//		postfix_register,
		//		x86_Register::EAX
		//	);
		//
		//	/* Dereference */
		//	*instrs++ = construct_mov_instruction(
		//		mem_t(postfix_register),
		//		postfix_register
		//	);
		//
		//	*instrs++ = construct_mov_instruction(
		//		postfix_register,
		//		result_register
		//	);
		//	break;
		//}
		//
		//case AstNodeAlt::POSTFIX_EXPRESSION_3:
		//{
		//	/* Loading AST data. */
		//	AnnotatedAstNode* unary_expression 
		//		= node->get_child();
		//
		//	/* Compute the array address */
		//	x86_Register unary_register;
		//	if (gen_postfix_expression(
		//			stack,
		//			unary_expression, 
		//			instrs, 
		//			unary_register)
		//		== CodeGeneratorExitCode::FAILURE) {
		//		exitcode = CodeGeneratorExitCode::FAILURE;
		//		break;
		//	}
		//
		//	*instrs++ = construct_inc_instruction(
		//		unary_register
		//	);		
		//	break;
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_4:
	{

		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_5:
	{
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_6:
	{
		///* Loading AST data. */
		//AnnotatedAstNode* postfix_expression
		//	= node->get_child();

		//if (gen_postfix_expression(
		//	stack,
		//	node,
		//	instrs,
		//	alloc_map,
		//	output_register)
		//	== CodeGeneratorExitCode::FAILURE) {
		//	exitcode = CodeGeneratorExitCode::FAILURE;
		//	break;
		//}

		//*instrs++ = construct_inc_instruction(
		//	output_register
		//);
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_7:
	{
		///* Loading AST data. */
		//AnnotatedAstNode* postfix_expression 
		//	= node->get_child();

		//if (gen_postfix_expression(
		//		stack,
		//		node, 
		//		instrs,
		//		alloc_map,
		//		output_register)
		//	== CodeGeneratorExitCode::FAILURE) {
		//	exitcode = CodeGeneratorExitCode::FAILURE;
		//	break;
		//}

		//*instrs++ = construct_dec_instruction(
		//	output_register
		//);
		break;
	}

	case AstNodeAlt::POSTFIX_EXPRESSION_8:
	{
		break;

	}

	case AstNodeAlt::POSTFIX_EXPRESSION_9:
	{
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_unary_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_unary_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::UNARY_EXPRESSION_1:
	{
		AnnotatedAstNode* postfix_expression
			= node->get_child();
		if (gen_postfix_expression(
			stack,
			postfix_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::UNARY_EXPRESSION_2:
		break;

	case AstNodeAlt::UNARY_EXPRESSION_3:
		break;

	case AstNodeAlt::UNARY_EXPRESSION_4:
		break;

	case AstNodeAlt::UNARY_EXPRESSION_5:
		break;

	case AstNodeAlt::UNARY_EXPRESSION_6:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_cast_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_cast_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::CAST_EXPRESSION_1:
	{
		AnnotatedAstNode* unary_expression
			= node->get_child();
		if (gen_unary_expression(
			stack,
			unary_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::CAST_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_multiplicative_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_multiplicative_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_1:
	{
		AnnotatedAstNode* cast_expression
			= node->get_child();
		if (gen_cast_expression(
			stack,
			cast_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2:
	{
		x86_RegisterAllocMap multicative_expression_2_alloc_map
			= alloc_map;

		AnnotatedAstNode* multiplicative_expression
			= node->get_child();
		AnnotatedAstNode* cast_expression
			= node->get_child()->get_sibling();

		x86_Register multiplicative_expression_register
			= reg_alloc(multicative_expression_2_alloc_map);

		x86_AssemblyInstructionOperand op1, op2;
		gen_multiplicative_expression(
			stack,
			multiplicative_expression,
			instrs,
			multicative_expression_2_alloc_map,
			multiplicative_expression_register,
			op1);

		x86_Register cast_register
			= reg_alloc(multicative_expression_2_alloc_map);

		gen_cast_expression(
			stack,
			cast_expression,
			instrs,
			multicative_expression_2_alloc_map,
			cast_register,
			op2);

		x86_RegisterInstructionOperandVal r1, r2;
		r1.reg_index = cast_register;
		r2.reg_index = multiplicative_expression_register;

		*instrs++ = x86_AssemblyInstruction(
			x86_AssemblyInstructionMnemonic::MULSS,
			new x86_AssemblyInstructionOperand(
				x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
				r1),
			new x86_AssemblyInstructionOperand(
				x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
				r2)
		);

		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3:
		break;

	case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_additive_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_additive_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::ADDITIVE_EXPRESSION_1:
	{
		AnnotatedAstNode* multiplicative_expression
			= node->get_child();
		if (gen_multiplicative_expression(
			stack,
			multiplicative_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::ADDITIVE_EXPRESSION_2:
		break;

	case AstNodeAlt::ADDITIVE_EXPRESSION_3:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_shift_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_shift_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::SHIFT_EXPRESSION_1:
	{
		AnnotatedAstNode* additive_expression
			= node->get_child();
		if (gen_additive_expression(
			stack,
			additive_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::SHIFT_EXPRESSION_2:
		break;

	case AstNodeAlt::SHIFT_EXPRESSION_3:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_relational_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_relational_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::RELATIONAL_EXPRESSION_1:
	{
		AnnotatedAstNode* shift_expression
			= node->get_child();
		if (gen_shift_expression(
			stack,
			shift_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::RELATIONAL_EXPRESSION_2:
		break;

	case AstNodeAlt::RELATIONAL_EXPRESSION_3:
		break;

	case AstNodeAlt::RELATIONAL_EXPRESSION_4:
		break;

	case AstNodeAlt::RELATIONAL_EXPRESSION_5:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_equality_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_equality_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::EQUALITY_EXPRESSION_1:
	{
		AnnotatedAstNode* relational_expression
			= node->get_child();
		if (gen_relational_expression(
			stack,
			relational_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::EQUALITY_EXPRESSION_2:
		break;

	case AstNodeAlt::EQUALITY_EXPRESSION_3:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_and_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_and_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::AND_EXPRESSION_1:
	{
		AnnotatedAstNode* equality_expression
			= node->get_child();
		if (gen_equality_expression(
			stack,
			equality_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}
	case AstNodeAlt::AND_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_exclusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_exclusive_or_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1:
	{
		AnnotatedAstNode* and_expression
			= node->get_child();
		if (gen_and_expression(
			stack,
			and_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_inclusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_inclusive_or_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_1:
	{
		AnnotatedAstNode* exclusive_or_expression
			= node->get_child();
		if (gen_exclusive_or_expression(
			stack,
			exclusive_or_expression,
			instrs,
			alloc_map,
			output_register,
			operand) 
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}
	case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_logical_and_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_logical_and_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::LOGICAL_AND_EXPRESSION_1:
	{
		AnnotatedAstNode* inclusive_or_expression
			= node->get_child();
		if (gen_inclusive_or_expression(
			stack,
			inclusive_or_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::LOGICAL_AND_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_exlusive_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_exlusive_or_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1:
		break;

	case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_logical_or_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_logical_or_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::LOGICAL_OR_EXPRESSION_1:
	{
		AnnotatedAstNode* logical_and_expression
			= node->get_child();
		if (gen_logical_and_expression(
			stack,
			logical_and_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::LOGICAL_OR_EXPRESSION_2:
		// TODO;
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_conditional_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_conditional_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::CONDITIONAL_EXPRESSION_1:
	{
		AnnotatedAstNode* logical_or_expression
			= node->get_child();
		if (gen_logical_or_expression(
			stack,
			logical_or_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::CONDITIONAL_EXPRESSION_2:
		// TODO;
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_assignment_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_assignment_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::ASSIGNMENT_EXPRESSION_1:
	{
		AnnotatedAstNode* conditional_expression
			= node->get_child();
		if (gen_conditional_expression(
			stack,
			conditional_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::ASSIGNMENT_EXPRESSION_2:
	{
		x86_RegisterAllocMap assignment_expression_2_alloc_map
			= alloc_map;

		AnnotatedAstNode* unary_expression =
			node->get_child();
		AnnotatedAstNode* assignment_operator =
			node->get_child()->get_sibling();
		AnnotatedAstNode* assignment_expression =
			node->get_child()->get_sibling()->get_sibling();

		//if (gen_unary_expression_as_lvalue(
		//		stack,
		//		unary_expression,
		//		instrs,
		//		assignment_expression_2_alloc_map,
		//		output_register)
		//	== CodeGeneratorExitCode::FAILURE) {
		//	break;
		//}

		switch (assignment_operator->get_alt()) {

		case AstNodeAlt::ASSIGNMENT_OPERATOR_1:
		{
			x86_Register assignment_expression_register
				= reg_alloc(assignment_expression_2_alloc_map);

			if (gen_assignment_expression(
				stack,
				assignment_expression,
				instrs,
				assignment_expression_2_alloc_map,
				assignment_expression_register,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_RegisterInstructionOperandVal v1;
			v1.reg_containing_addr = output_register;

			x86_RegisterInstructionOperandVal v2;
			v2.reg_index = assignment_expression_register;

			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::MOVSS,
				new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_CONTAINING_ADDR,
					v1),
				new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
					v2));

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ASSIGNMENT_OPERATOR_2:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_3:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_4:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_5:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_6:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_7:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_8:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_9:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_10:
			break;

		case AstNodeAlt::ASSIGNMENT_OPERATOR_11:
			break;

		default:
			break;
		}
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::EXPRESSION_1:
	{
		AnnotatedAstNode* assignment_expression
			= node->get_child();
		if (gen_assignment_expression(
			stack,
			assignment_expression,
			instrs,
			alloc_map,
			output_register,
			operand) 
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::EXPRESSION_2:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_constant_expression(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_constant_expression");

	switch (node->get_alt()) {

	case AstNodeAlt::CONSTANT_EXPRESSION_1:
		break;

	default:
		break;
	}
	return exitcode;
}

/* Declarations. */

static inline CodeGeneratorExitCode gen_declaration(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration");

	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_1:
	{
		AnnotatedAstNode* declaration_specifiers =
			node->get_child();
		AnnotatedAstNode* init_declarator_list =
			node->get_child()->get_sibling();
		if (init_declarator_list) {
			if (gen_init_declarator_list(
				stack,
				init_declarator_list,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_declaration_specifiers(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration_specifiers");

	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_SPECIFIERS_1:
	{
		AnnotatedAstNode* storage_class_specifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= node->get_child()->get_sibling();
		if (declaration_specifiers) {
			if (gen_declaration_specifiers(
				stack,
				declaration_specifiers,
				instrs,
				alloc_map,
				output_register)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::DECLARATION_SPECIFIERS_2:
	{
		AnnotatedAstNode* type_specifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= node->get_child()->get_sibling();
		if (declaration_specifiers) {
			if (gen_declaration_specifiers(
				stack,
				declaration_specifiers,
				instrs,
				alloc_map,
				output_register)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}
	case AstNodeAlt::DECLARATION_SPECIFIERS_3:
	{
		AnnotatedAstNode* type_qualifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= node->get_child()->get_sibling();
		if (declaration_specifiers) {
			if (gen_declaration_specifiers(
				stack,
				declaration_specifiers,
				instrs,
				alloc_map,
				output_register)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}
	case AstNodeAlt::DECLARATION_SPECIFIERS_4:
	{
		AnnotatedAstNode* function_specifier
			= node->get_child();
		AnnotatedAstNode* declaration_specifiers
			= node->get_child()->get_sibling();
		if (declaration_specifiers) {
			if (gen_declaration_specifiers(
				stack,
				declaration_specifiers,
				instrs,
				alloc_map,
				output_register)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_init_declarator_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_init_declarator_list");

	switch (node->get_alt()) {

	case AstNodeAlt::INIT_DECLARATOR_LIST_1:
	{
		AnnotatedAstNode* init_declarator
			= node->get_child();
		if (gen_init_declarator(
			stack,
			init_declarator,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::INIT_DECLARATOR_LIST_2:
	{
		AnnotatedAstNode* init_declarator_list
			= node->get_child();
		AnnotatedAstNode* init_declarator
			= node->get_child()->get_sibling();
		if (gen_init_declarator_list(
			stack,
			init_declarator_list,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		if (gen_init_declarator(
			stack,
			init_declarator,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_init_declarator(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_init_declarator");

	switch (node->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_1:
		{
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INIT_DECLARATOR_2:
		{
			AnnotatedAstNode* declarator
				= node->get_child();
			AnnotatedAstNode* initializer
				= node->get_child()->get_sibling();

			SymbolTable* st = declarator->get_symbol_table();
			SymbolTableEntry* ste = st->get_entry(declarator->get_symbol());

			x86_AssemblyInstructionOperand op1;
			if (gen_initializer(
				stack,
				initializer,
				instrs,
				x86_RegisterAllocMap(0),
				x86_Register::RAX,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_AssemblyInstructionOperand op2;
			if (gen_symbol(
				stack,
				declarator->get_symbol_table()->get_entry(declarator->get_symbol()),
				instrs,
				x86_RegisterAllocMap(0),
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::MOVSS,
				new x86_AssemblyInstructionOperand(op1),
				new x86_AssemblyInstructionOperand(op2));

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_initializer(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_initializer");

	switch (node->get_alt()) {

	case AstNodeAlt::INITIALIZER_1:
	{
		AnnotatedAstNode* assignment_expression
			= node->get_child();
		if (gen_assignment_expression(
			stack,
			assignment_expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::INITIALIZER_2:
	case AstNodeAlt::INITIALIZER_3:
	{
		AnnotatedAstNode* initializer_list
			= node->get_child();
		if (gen_initializer_list(
			stack,
			initializer_list,
			instrs,
			alloc_map,
			output_register)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_initializer_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_initializer_list");

	switch (node->get_alt()) {

	case AstNodeAlt::INITIALIZER_LIST_1:
	{
		/*AnnotatedAstNode* designation
			= node->get_child()->get_name() == AstNodeName::;
		gen_initializer(initializer, instrs);
		exitcode = CodeGeneratorExitCode::SUCCESS;*/
		break;
	}

	case AstNodeAlt::INITIALIZER_LIST_2:
	{
		/*	AnnotatedAstNode* initializer_list = node->get_child();
			gen_initializer_list(initializer_list, instrs);
			exitcode = CodeGeneratorExitCode::SUCCESS;*/
		break;
	}

	default:
		break;
	}
	return exitcode;
}

/* Statements. */

static inline CodeGeneratorExitCode gen_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_statement");

	switch (node->get_alt()) {

	case AstNodeAlt::STATEMENT_1:
	{
		AnnotatedAstNode* labeled_statement
			= node->get_child();
		if (gen_labeled_statement(
			stack,
			labeled_statement,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_2:
	{
		AnnotatedAstNode* compound_statement
			= node->get_child();
		if (gen_compound_statement(
				stack,
				compound_statement,
				instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_3:
	{
		AnnotatedAstNode* expression_statement
			= node->get_child();
		x86_AssemblyInstructionOperand *operand
			= new x86_AssemblyInstructionOperand();
		if (gen_expression_statement(
			stack,
			expression_statement,
			instrs,
			x86_RegisterAllocMap(0),
			x86_Register::RAX,
			*operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_4:
	{
		AnnotatedAstNode* selection_statement
			= node->get_child();
		if (gen_selection_statement(
			stack,
			selection_statement,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_5:
	{
		AnnotatedAstNode* iteration_statement
			= node->get_child();
		if (gen_iteration_statement(
			stack,
			iteration_statement,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::STATEMENT_6:
	{
		AnnotatedAstNode* jump_statement
			= node->get_child();
		if (gen_jump_statement(
			stack,
			jump_statement,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_labeled_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_labeled_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::LABELED_STATEMENT_1:
			break;

		case AstNodeAlt::LABELED_STATEMENT_2:
			break;

		case AstNodeAlt::LABELED_STATEMENT_3:
			break;

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_compound_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_compound_statement");

	switch (node->get_alt()) {

	case AstNodeAlt::COMPOUND_STATEMENT_1:
	{
		AnnotatedAstNode* block_item_list
			= node->get_child();
		if (gen_block_item_list(
			stack,
			block_item_list,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_block_item_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_block_item_list");

	switch (node->get_alt()) {

	case AstNodeAlt::BLOCK_ITEM_LIST_1:
	{
		AnnotatedAstNode* block_item
			= node->get_child();
		if (gen_block_item(
			stack,
			block_item,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::BLOCK_ITEM_LIST_2:
	{
		AnnotatedAstNode* block_item_list
			= node->get_child();
		AnnotatedAstNode* block_item
			= block_item_list->get_sibling();
		if (gen_block_item_list(
			stack,
			block_item_list,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		if (gen_block_item(
			stack,
			block_item,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_block_item(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_block_item");

	switch (node->get_alt()) {

	case AstNodeAlt::BLOCK_ITEM_1:
	{
		AnnotatedAstNode* declaration
			= node->get_child();
		if (gen_declaration(
			stack,
			declaration,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	case AstNodeAlt::BLOCK_ITEM_2:
	{
		AnnotatedAstNode* statement = node->get_child();
		if (gen_statement(
			stack,
			statement,
			instrs)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_expression_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register,
	x86_AssemblyInstructionOperand& operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_expression_statement");

	switch (node->get_alt()) {

	case AstNodeAlt::EXPRESSION_STATEMENT_1:
	{
		AnnotatedAstNode* expression
			= node->get_child();
		if (gen_expression(
			stack,
			expression,
			instrs,
			alloc_map,
			output_register,
			operand)
			== CodeGeneratorExitCode::FAILURE) {
			break;
		}
		exitcode = CodeGeneratorExitCode::SUCCESS;
		break;
	}

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_selection_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_selection_statement");

	switch (node->get_alt()) {

	case AstNodeAlt::SELECTION_STATEMENT_1:
		break;

	case AstNodeAlt::SELECTION_STATEMENT_2:
		break;

	case AstNodeAlt::SELECTION_STATEMENT_3:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_iteration_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_iteration_statement");

	switch (node->get_alt()) {

	case AstNodeAlt::ITERATION_STATEMENT_1:
		break;

	case AstNodeAlt::ITERATION_STATEMENT_2:
		break;

	case AstNodeAlt::ITERATION_STATEMENT_3:
		break;

	case AstNodeAlt::ITERATION_STATEMENT_4:
		break;

	default:
		break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_jump_statement(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_jump_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::JUMP_STATEMENT_1:
			break;

		case AstNodeAlt::JUMP_STATEMENT_2:
			break;

		case AstNodeAlt::JUMP_STATEMENT_3:
			break;

		case AstNodeAlt::JUMP_STATEMENT_4:
		{
			x86_AssemblyInstructionOperand *operand 
				= new x86_AssemblyInstructionOperand;
			AnnotatedAstNode* expression
				= node->get_child();
			gen_expression(
				stack,
				expression,
				instrs,
				x86_RegisterAllocMap(0),
				x86_Register::XMM0, 
				*operand);
			/* moving returned value to xmm0 */
			x86_AssemblyInstructionOperand* o1
				= new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
					{ x86_Register::XMM0 });
			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::MOVSS,
				operand,
				o1);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}
	
		default:
			break;
	
	}
	return exitcode;
}

/* External definitions. */

static inline CodeGeneratorExitCode gen_translation_unit(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_translation_unit");

	x86_RegisterAllocMap alloc_map = x86_RegisterAllocMap(0);

	gen_literals(node->get_symbol_table(), instrs);

	switch (node->get_alt()) {

		case AstNodeAlt::TRANSLATION_UNIT_1:
		{
			AnnotatedAstNode* external_declaration
				= node->get_child();
			if (gen_external_declaration(
					stack,
					external_declaration,
					instrs)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::TRANSLATION_UNIT_2:
		{
			AnnotatedAstNode* translation_unit
				= node->get_child();
			AnnotatedAstNode* external_declaration
				= translation_unit->get_sibling();
			if (gen_translation_unit(
				stack,
				node,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {

			}
			if (gen_external_declaration(
				stack,
				node,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_external_declaration(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_external_declaration");

	switch (node->get_alt()) {

		case AstNodeAlt::EXTERNAL_DECLARATION_1:
		{
			AnnotatedAstNode* function_definition
				= node->get_child();
			if (gen_function_definition(
				stack,
				function_definition,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXTERNAL_DECLARATION_2:
			//gen_declaration(node, instrs);
			break;

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_function_definition(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_function_definition");

	switch (node->get_alt()) {

		case AstNodeAlt::FUNCTION_DEFINITION_1:
		{
			AnnotatedAstNode* declaration_specifiers
				= node->get_child();
			AnnotatedAstNode* declarator
				= declaration_specifiers->get_sibling();
			
			AnnotatedAstNode* compound_statement
				= (declarator->get_sibling()->get_name()
					== AstNodeName::DECLARATION_LIST)
				  ? declarator->get_sibling()->get_sibling()
				  : declarator->get_sibling();

			x86_AssemblyInstructionOperand* o 
				= new x86_AssemblyInstructionOperand(
				x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
				{ x86_Register::RBP });
			*instrs = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::PUSHQ,
				o);

			instrs->set_label(declarator->get_symbol());
			instrs->set_type(x86_AssemblyInstructionType::LABELED_INSTRUCTION);
			instrs++;

			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::MOVQ,
				new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
					x86_RegisterInstructionOperandVal({ x86_Register::RSP })),
				new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
					x86_RegisterInstructionOperandVal({ x86_Register::RBP })));

			if (gen_compound_statement(
				stack,
				compound_statement,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {
				//break;
			}
			
			/* returning from function */
			x86_AssemblyInstructionOperand* o2
				= new x86_AssemblyInstructionOperand(
					x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
					{ x86_Register::RBP });
			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::POPQ,
				o2
			);
			*instrs++ = x86_AssemblyInstruction(
				x86_AssemblyInstructionMnemonic::RETQ
			);

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline CodeGeneratorExitCode gen_declaration_list(
	StackDescriptor* const& stack,
	AnnotatedAstNode* const& node,
	x86_AssemblyInstruction*& instrs,
	x86_RegisterAllocMap const& alloc_map,
	x86_Register const& output_register)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration_list");

	switch (node->get_alt()) {

	case AstNodeAlt::DECLARATION_LIST_1:
		break;

	case AstNodeAlt::DECLARATION_LIST_2:
		break;

	default:
		break;
	}
	return exitcode;
}

#endif