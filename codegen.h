/* Authored by Charlie Keaney        */
/* ast-node.h - Responsible for code 
				generation from an 
				annotated abstract 
				syntax tree.         */

#ifndef CODE_GEN_H
#define CODE_GEN_H 1

#include "semantics.h"
#include "symbol-table.h"
#include "annotated-ast-node.h"

#define DEBUG_CODEGEN_SHOW_INSTR_GEN 0
#define DEBUG_CODEGEN_SHOW_REG_ALLOC 0

#define report_alloc(r)						 \
	if (DEBUG_CODEGEN_SHOW_REG_ALLOC) {		 \
		cout << "codegen.h:"				 \
			 << "reg_alloc:"				 \
			 << "allocating..."				 \
			 << x86_register_string_reprs[r] \
			 << endl; 						 \
	}

#define report_gen(m)						 \
	if (DEBUG_CODEGEN_SHOW_INSTR_GEN) {		 \
		cout << "codegen.h:"				 \
			 << m							 \
			 << ": generating..."			 \
			 << endl;						 \
	}

#define gen(a, r, i) gen_translation_unit(a, r, i)

/*****************************************************//**
*                      Declarations                      *
/********************************************************/

enum class CodeGeneratorExitCode {
	SUCCESS,
	FAILURE_CONVERSION_ERROR,
	FAILURE
};

enum class x86_Asm_IR_Mnemonic {
	ADD,
	ADDSS,
	AND,
	SUB,
	SUBSS,
	INC,
	CMP,
	CMOVZ,
	CMOVNZ,
	DEC,
	MULSS,
	DIV,
	DIVSS,
	IDIV,
	IMUL,
	PUSHQ,
	POPQ,
	CALL,
	RETQ,	
	MOV,
	MOVSS,
	MOVQ,
	MOVD,
	MUL,
	JE,
	JNE,
	JG,
	JGE,
	JL,
	JLE,
	JMP,
	JZ,
	NEG,
	OR,
	SETE,
	SETNE,
	SETG,
	SETGE,
	SETL,
	SETLE,
	SHL,
	SHR,
	XOR,
	/* Literal constant types */
	LONG
};

static 
const char* x86_asm_ir_mnemonic_string_reprs[] {
	"add",
	"addss",
	"and",
	"sub",
	"subss",
	"inc",
	"cmp",
	"cmovz",
	"cmovnz",
	"dec",
	"mulss",
	"div",
	"divss",
	"idiv",
	"imul",
	"pushq",
	"popq",
	"call",
	"retq",
	"mov",
	"movss",
	"movq",
	"movd",
	"mul",
	"je",
	"jne",
	"jg",
	"jge",
	"jl",
	"jle",
	"jmp",
	"jz",
	"neg",
	"or",
	"sete",
	"setne",
	"setq",
	"setge",
	"setl",
	"setle",
	"shl",
	"shr",
	"xor",
	".long"
};

enum class x86_RegisterName {
	UNDEFINED,
	/* Accumulator */
	RAX,
	EAX,
	AX,
	AH,
	AL,
	/* Counter */
	RCX,
	ECX,
	CX,
	CH,
	CL,
	/* Data */
	RDX,
	EDX,
	DX,
	DH,
	DL,
	/* Base */
	RBX,
	EBX,
	BX,
	BH,
	BL,
	/* Stack Pointer */
	RSP,
	ESP,
	SP,
	SPL,
	/* Stack Base Pointer */
	RBP,
	EBP,
	BP,
	BPL,
	/* Source */
	RSI,
	ESI,
	SI,
	SIL,
	/* Destination */
	RDI,
	EDI,
	DI,
	DIL,
	/* Other General Purpose */
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	RIP,
	EFLAGS,
	/* XMM Registers */
	XMM0, 
	XMM1,
	XMM2,
	XMM3,
	XMM4,
	XMM5,
	XMM6,
	XMM7,
};

static 
const char* x86_register_string_reprs[] = {	
	"undefined",
	"rax",
	"eax",
	"ax",
	"ah",
	"al",
	"rcx",
	"ecx",
	"cx",
	"ch",
	"cl",
	"rdx",
	"edx",
	"dx",
	"dh",
	"dl",
	"rbx",
	"ebx",
	"bx",
	"bh",
	"bl",
	"rsp",
	"esp",
	"sp",
	"spl",
	"rbp",
	"ebp",
	"bp",
	"bpl",
	"rsi",
	"esi",
	"si",
	"sil",
	"rdi",
	"edi",
	"di",
	"dil",
	"r8",
	"r9",
	"r10",
	"r11",
	"r12",
	"r13",
	"r14",
	"r15",
	"rip",
	"eflags",
	"xmm0",
	"xmm1",
	"xmm2",
	"xmm3",
	"xmm4",
	"xmm5",
	"xmm6",
	"xmm7",
};

enum class x86_RegisterType {
	UNDEFINED,
	FLOAT_64,
	FLOAT_32,
	INT_64,
	INT_32,
	INT_16,
	INT_8
};

typedef struct x86_RegisterAllocMap {
	/* XMM Registers         */
	bool xmm0 : 1;
	bool xmm1 : 1;
	bool xmm2 : 1;
	bool xmm3 : 1;
	bool xmm4 : 1;
	bool xmm5 : 1;
	bool xmm6 : 1;
	bool xmm7 : 1; 
	/* Accumulator           */
	bool rax  : 1;
	bool eax  : 1;
	bool ax   : 1;
	bool ah   : 1;
	bool al   : 1;
	/* Counter               */
	bool rcx  : 1;
	bool ecx  : 1;
	bool cx   : 1;
	bool ch   : 1;
	bool cl   : 1;
	/* Data	                 */
	bool rdx  : 1;
	bool edx  : 1;
	bool dx   : 1;
	bool dh   : 1;
	bool dl   : 1;
	/* Base                  */
	bool rbx  : 1;
	bool ebx  : 1;
	bool bx   : 1;
	bool bh   : 1;
	bool bl   : 1;
	/* Stack Pointer         */
	bool rsp  : 1;
	bool esp  : 1;
	bool sp   : 1;
	bool spl  : 1;
	/* Stack Base Pointer    */
	bool rbp  : 1;
	bool ebp  : 1;
	bool bp   : 1;
	bool bpl  : 1;
	/* Source                */
	bool rsi  : 1;
	bool esi  : 1;
	bool si   : 1;
	bool sil  : 1;
	/* Destination           */
	bool rdi  : 1;
	bool edi  : 1;
	bool di   : 1;
	bool dil  : 1;
	/* Other General Purpose */
	bool r8   : 1;
	bool r9   : 1;
	bool r10  : 1;
	bool r11  : 1;
	bool r12  : 1;
	bool r13  : 1;
	bool r14  : 1;
	bool r15  : 1;
	bool rip  : 1;
};

typedef uint32_t	doubleword_unsigned_integer;

typedef uint64_t	near_pointer;
typedef long double	far_pointer_with_64_bit_operand_size;
typedef uint64_t	far_pointer_with_32_bit_operand_size;

typedef struct register_and_offset {
	signed long      offset;
	x86_RegisterName reg;
} register_and_offset;

typedef struct label_and_register {
	const char*      label;
	x86_RegisterName reg;
} label_and_register;

enum class x86_Asm_IR_OperandType {
	LITERAL,
	IDENTIFIER,
	X86_REGISTER_INDEX,
	X86_REGISTER_CONTAINING_ADDR,
	DOUBLEWORD_UNSIGNED_INTEGER,
	NEAR_POINTER,
	LABEL_AND_REGISTER,
	REGISTER_AND_OFFSET,
	LABEL
};

typedef union x86_Asm_IR_OperandVal {
	x86_RegisterName                     reg_index;
	x86_RegisterName                     reg_containing_addr;
	doubleword_unsigned_integer          dwui;
	near_pointer                         np;
	far_pointer_with_64_bit_operand_size fpw64bos;
	far_pointer_with_32_bit_operand_size fpw32bos;
	register_and_offset                  rao;
	label_and_register                   lar;
	const char*                          label;
};

class x86_Asm_IR_Operand {
private:
	x86_Asm_IR_OperandType type;
	x86_Asm_IR_OperandVal  val;
	const char*            lexeme;
public:
	x86_Asm_IR_Operand()
		: type(x86_Asm_IR_OperandType()), 
		  val(x86_Asm_IR_OperandVal()) { }

	x86_Asm_IR_Operand(
		x86_Asm_IR_OperandType base_type,
		x86_Asm_IR_OperandVal v)
		: type(base_type), 
		  val(v) { }

	inline void print() const {

		switch (type) {

			case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
				cout // TODO; AT&T syntax << "%"
					 << x86_register_string_reprs[(int)val.reg_index];
				break;
			
			case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
				cout <<  "["
					 << x86_register_string_reprs[(int)val.reg_containing_addr]
					 << "]";
				break;
			
			case x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER:
				cout // TODO AT&T Syntax << "$" 
					<< std::dec 
					<< val.dwui;
				break;
			
			case x86_Asm_IR_OperandType::NEAR_POINTER:
				cout << "["
					 << "0x"
					 << std::right
					 << std::hex
					 << std::setw(8)
					 << std::setfill('0')
					 << val.np
					 << "]";
				break;

			case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
			{
				cout << val.lar.label
					 << "("
					 //<< "%" 
					 << x86_register_string_reprs[(int)val.lar.reg]
					 << ")";
				break;
			}

			case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
			{
				signed int offset = (int) val.rao.offset;
				//if (offset < 0) cout << "-";				
				if (offset != 0) {
					cout << std::dec
						<< offset; //< 0 ? -1 * offset : offset
				}
				cout << "("
					 // TODO; AT&T SYNTAX << "%" 
					 << x86_register_string_reprs[(int)val.rao.reg]
					 << ")";
				break;
			}
			
			default:
				break;
		};
	}

	inline x86_Asm_IR_OperandType get_type() const {
		return type;
	}

	inline x86_Asm_IR_OperandVal get_constant_val() const {
		return val;
	}
};

enum class x86_Asm_IR_Type {
	LABELED_INSTRUCTION,
	INSTRUCTION,
};

class x86_Asm_IR {
private:	
	x86_Asm_IR_Type     type;
	const char*         label;
	x86_Asm_IR_Mnemonic mnemonic;
	int                 num_operands;
	x86_Asm_IR_Operand  op1;
	x86_Asm_IR_Operand  op2;
	x86_Asm_IR_Operand  op3;

	inline x86_Asm_IR(
		x86_Asm_IR_Type     const& base_type,
		const char*         const& l,
		x86_Asm_IR_Mnemonic const& m,
		x86_Asm_IR_Operand  const& o1,
		x86_Asm_IR_Operand  const& o2,
		x86_Asm_IR_Operand  const& o3)
		: type(base_type),
		  mnemonic(m),
		  op1(o1),
		  op2(o2),
		  op3(o3) {
	}
public:
	inline x86_Asm_IR() {};

	inline void set_label(
		const char* const& l) { 
		label = l; 
	};

	inline void set_type(
		x86_Asm_IR_Type const& base_type) { 
		type = base_type; 
	};

	inline x86_Asm_IR(
		x86_Asm_IR_Mnemonic const& m)
	{
		switch (m) {

			case x86_Asm_IR_Mnemonic::RETQ:
			{
				type = x86_Asm_IR_Type::INSTRUCTION;
				const char* label = NULL;
				mnemonic = x86_Asm_IR_Mnemonic::RETQ;
				break;
			}
			
			default:
				break;
		}
		num_operands = 0;
		if (DEBUG_CODEGEN_SHOW_INSTR_GEN) {
			this->print();
		}
	}

	inline x86_Asm_IR(
		x86_Asm_IR_Mnemonic const& m,
		x86_Asm_IR_Operand  const& o1)
	{
		switch (m) {

			case x86_Asm_IR_Mnemonic::LONG:
			case x86_Asm_IR_Mnemonic::JMP:
			case x86_Asm_IR_Mnemonic::PUSHQ:
			case x86_Asm_IR_Mnemonic::POPQ:
			case x86_Asm_IR_Mnemonic::NEG:
			{
				type = x86_Asm_IR_Type::INSTRUCTION;
				const char* label = NULL;
				mnemonic = m;
				op1 = o1;
				break;
			}

			default:
				break;

		}
		num_operands = 1;
		if (DEBUG_CODEGEN_SHOW_INSTR_GEN) {
			this->print();
		}
	}

	inline x86_Asm_IR(
		x86_Asm_IR_Mnemonic const& m,
		x86_Asm_IR_Operand  const& o1,
		x86_Asm_IR_Operand  const& o2)
	{
		switch (m) {

			case x86_Asm_IR_Mnemonic::ADD:
			case x86_Asm_IR_Mnemonic::SUB:
			case x86_Asm_IR_Mnemonic::SUBSS:
			case x86_Asm_IR_Mnemonic::INC:
			case x86_Asm_IR_Mnemonic::DEC:
			case x86_Asm_IR_Mnemonic::DIVSS:
			case x86_Asm_IR_Mnemonic::IDIV:
			case x86_Asm_IR_Mnemonic::DIV:
			case x86_Asm_IR_Mnemonic::PUSHQ:
			case x86_Asm_IR_Mnemonic::CALL:
			case x86_Asm_IR_Mnemonic::RETQ:
			case x86_Asm_IR_Mnemonic::MOV:
			case x86_Asm_IR_Mnemonic::MOVD:
			case x86_Asm_IR_Mnemonic::MOVSS:
			case x86_Asm_IR_Mnemonic::MOVQ:
			case x86_Asm_IR_Mnemonic::CMP:
			case x86_Asm_IR_Mnemonic::JE:
			case x86_Asm_IR_Mnemonic::JNE:
			case x86_Asm_IR_Mnemonic::JG:
			case x86_Asm_IR_Mnemonic::JGE:
			case x86_Asm_IR_Mnemonic::JL:
			case x86_Asm_IR_Mnemonic::JLE:
			case x86_Asm_IR_Mnemonic::JMP:
			case x86_Asm_IR_Mnemonic::SETE:
			case x86_Asm_IR_Mnemonic::SETNE:
			case x86_Asm_IR_Mnemonic::SETG:
			case x86_Asm_IR_Mnemonic::SETGE:
			case x86_Asm_IR_Mnemonic::SETL:
			case x86_Asm_IR_Mnemonic::SETLE:
			case x86_Asm_IR_Mnemonic::SHL:
			case x86_Asm_IR_Mnemonic::SHR:			
			case x86_Asm_IR_Mnemonic::IMUL:		
			case x86_Asm_IR_Mnemonic::MULSS:
			case x86_Asm_IR_Mnemonic::MUL:
			{
				type = x86_Asm_IR_Type::INSTRUCTION;
				const char* label = NULL;
				mnemonic = m;
				op1 = o1;
				op2 = o2;
				num_operands = 2;
				break;
			}

			default: 
				break;

		}
		if (DEBUG_CODEGEN_SHOW_INSTR_GEN) {
			this->print();
		}
	}

	inline void print() const {
		if (type == x86_Asm_IR_Type::LABELED_INSTRUCTION) {
			cout << label 
				 << ":" 
				 << endl;
		} 

		cout << "\t"
			 << std::left
			 << setw(5)
			 << setfill(' ')
		     << x86_asm_ir_mnemonic_string_reprs[(int) mnemonic]
		     << " ";
		if (num_operands > 0) {
			op1.print();
		}			
		if (num_operands > 1) {
			cout << ", ";
			op2.print();

		}
		if (num_operands > 2) {
			cout << ", ";
			op3.print();
		}
		cout << endl;
	}
};

/**
* @param operand
* @param op1_t
* @param converted_operand
* @param op2_t
**/
static inline
CodeGeneratorExitCode convert_operand_to_correct_type(
	const Type*            const& c_type,
	x86_Asm_IR_Operand     const& operand,
	x86_Asm_IR_OperandType const& op1_t,
	x86_Asm_IR_Operand          & converted_operand,
	x86_Asm_IR_OperandType const& op2_t,
	x86_Asm_IR*                 & instrs,
	x86_RegisterAllocMap        & alloc_map);

/**
* @param op1_t
* @param op1
* @param op2_t
* @param op2
* @param instrs
**/
static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_multiply(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs) ;

/**
* @param op1_t
* @param op1
* @param op2_t
* @param op2
* @param instrs
**/
static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_divide(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs);

/**
* @param dest_t
* @param dest
* @param source_t
* @param source
* @ param instrs
**/
static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_move(
	const Type*        const& dest_t,
	x86_Asm_IR_Operand const& dest,
	const Type*        const& source_t,
	x86_Asm_IR_Operand const& source,
	x86_Asm_IR*             & instrs);

/**
* @param op1_t
* @param op1
* @param op2_t
* @param op2
* @param instrs
**/
static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_add(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs);

/**
* @param op1_t
* @param op1
* @param op2_t
* @param op2
* @param instrs
**/
static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_subtract(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs);

/**
* @param type
**/
static inline
x86_RegisterType get_register_type_from_ast_type(
	const Type* const& type);

/** 
* @param map
**/
static inline
bool accumulator_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool counter_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool data_is_free(
	x86_RegisterAllocMap const& map);

/** 
* @param map
**/
static inline
bool base_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool stack_pointer_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool stack_base_pointer_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool source_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
**/
static inline
bool destination_is_free(
	x86_RegisterAllocMap const& map);

/**
* @param map
* @param name
**/
static inline
void allocate_given_register(
	x86_RegisterAllocMap      & map,
	x86_RegisterName     const& name);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_accumulator_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_counter_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_data_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_base_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_stack_pointer_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_stack_base_pointer_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_source_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_destination_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param map
* @param register_size
**/
static inline
x86_RegisterName allocate_register(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size);

/**
* @param symbol_entry
* @param instrs
* @param operand
* @param map
**/
static inline
CodeGeneratorExitCode gen_symbol(
	const SymbolTableEntry* const& symbol_entry,
	x86_Asm_IR*                  & instrs,
	x86_Asm_IR_Operand           & operand,
	x86_RegisterAllocMap    const& map);

/**
* @param label_prefix
* @param num_labels_used
**/
static inline
const char* construct_label(
	const char*   label_prefix,
	int         & num_labels_used)	;

/**
* @param num_labels_used
* @param symbol_table
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_literals(
	int               & num_labels_used,
	SymbolTable* const& symbol_table,
	x86_Asm_IR*       & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_primary_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_postfix_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_unary_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_cast_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_multiplicative_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_additive_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
*/
static inline
CodeGeneratorExitCode gen_shift_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used 
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_relational_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_equality_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_and_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_exclusive_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_inclusive_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
*/
static inline
CodeGeneratorExitCode gen_logical_and_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_exclusive_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_logical_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_conditional_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_assignment_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param output_register
**/
static inline
CodeGeneratorExitCode gen_constant_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_RegisterName        const& output_register);

/* Declarations. */

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_declaration(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param output_register
**/
static inline
CodeGeneratorExitCode gen_declaration_specifiers(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_RegisterName        const& output_register);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_init_declarator_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_init_declarator(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_initializer(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_initializer_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/* Statements. */

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_labeled_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_compound_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_block_item(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
**/
static inline
CodeGeneratorExitCode gen_block_item_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param operand
**/
static inline
CodeGeneratorExitCode gen_expression_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_selection_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_iteration_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_jump_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/* External definitions. */

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_translation_unit(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_external_declaration(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
**/
static inline
CodeGeneratorExitCode gen_function_definition(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs);

/**
* @param num_labels_used
* @param node
* @param instrs
* @param alloc_map
* @param output_register
**/
static inline
CodeGeneratorExitCode gen_declaration_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map);

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

static inline
CodeGeneratorExitCode convert_operand_to_correct_type(
	const Type*            const& c_type,
	x86_Asm_IR_Operand     const& operand,
	x86_Asm_IR_OperandType const& op1_t,
	x86_Asm_IR_Operand          & converted_operand,
	x86_Asm_IR_OperandType const& op2_t,
	x86_Asm_IR*                 & instrs,
	x86_RegisterAllocMap        & alloc_map)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;
	switch (op1_t) {

		case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
			
			switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					break;

				case x86_Asm_IR_OperandType::LABEL:
					break;

				default:
					break;
			}
			break;

		case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:

			switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
					break;

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					break;

				case x86_Asm_IR_OperandType::LABEL:
					break;

				default:
					break;
			}
			break;

		case x86_Asm_IR_OperandType::NEAR_POINTER:
			
			 switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
					break;

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					break;

				case x86_Asm_IR_OperandType::LABEL:
					break;

				default:
					break;

			}
			break; 

		case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:

			switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
				{
					x86_RegisterName reg
						= allocate_register(
							alloc_map,
							get_register_type_from_ast_type(c_type));
					converted_operand
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal({ reg }));
					construct_x86_AssemblyInstruction_move(
						c_type,
						converted_operand,
						c_type,
						operand,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					break;
				
				case x86_Asm_IR_OperandType::LABEL:
					break;
				
				default:
					break;
			}
			break;

		case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:

			switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
				{
					x86_RegisterName reg
						= allocate_register(
							alloc_map,
							get_register_type_from_ast_type(c_type));
					converted_operand
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal({ reg }));
					construct_x86_AssemblyInstruction_move(
						c_type,
						converted_operand,
						c_type,
						operand,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case x86_Asm_IR_OperandType::LABEL:
					break;

				default:
					break;

			}
			break; 
		
		case x86_Asm_IR_OperandType::LABEL:

			switch (op2_t) {

				case x86_Asm_IR_OperandType::X86_REGISTER_INDEX:
					break;

				case x86_Asm_IR_OperandType::X86_REGISTER_CONTAINING_ADDR:
					break;

				case x86_Asm_IR_OperandType::NEAR_POINTER:
					break;

				case x86_Asm_IR_OperandType::LABEL_AND_REGISTER:
					break;

				case x86_Asm_IR_OperandType::REGISTER_AND_OFFSET:
					break;

				case x86_Asm_IR_OperandType::LABEL:
					converted_operand = operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_multiply(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs) 
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;
	if (op1_t->classifier    == TypeClassifier::OBJECT
	    && op2_t->classifier == TypeClassifier::OBJECT) {

		if (is_real_floating_type(op1_t) 
			&& is_real_floating_type(op2_t)) {
			*instrs++ 
				= x86_Asm_IR(
					x86_Asm_IR_Mnemonic::MULSS,
					op1,
					op2); 
			exitcode = CodeGeneratorExitCode::SUCCESS;

		} else if (is_signed_integer_type(op1_t)
			       && is_signed_integer_type(op2_t)) {
			*instrs++ 
				= x86_Asm_IR(
					x86_Asm_IR_Mnemonic::IMUL,
					op1,
					op2);
			exitcode = CodeGeneratorExitCode::SUCCESS;

		} else if (is_unsigned_integer_type(op1_t)   
			       && is_unsigned_integer_type(op2_t)) {
			*instrs++ 
				= x86_Asm_IR(
					x86_Asm_IR_Mnemonic::MUL,
					op1,
					op2);
			exitcode = CodeGeneratorExitCode::SUCCESS;

		} else {

		}

	} else {

	}
	if (exitcode == CodeGeneratorExitCode::FAILURE) {
		/*	
		report_codegen_conversion_failure(
			"construct_x86_AssemblyInstruction_multiply:",
			op1_t,
			op2_t);*/
		cout << "\x1B[31m"
			 << "construct_x86_AssemblyInstruction_multiply:"
			 << " failed to convert type ";
		print_type(op1_t);
		cout << " to type ";
		print_type(op2_t);
		cout << "."
			 << "\033[0m"
			 << endl;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_divide(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	if (is_real_floating_type(op1_t)
		&& is_real_floating_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::DIVSS,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else if (is_signed_integer_type(op1_t)
		       && is_signed_integer_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::IDIV,
			op1,
			op2);			
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else if (is_unsigned_integer_type(op1_t)
		       && is_unsigned_integer_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::DIV,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else {

	}

	if (exitcode == CodeGeneratorExitCode::FAILURE) {
		cout << "\x1B[31m"
			 << "construct_x86_AssemblyInstruction_divide:"
			 << " failed to convert type ";
		print_type(op1_t);
		cout << " to type ";
		print_type(op2_t);
		cout << "." << "\033[0m"
			 << endl;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_move(
	const Type*        const& dest_t,
	x86_Asm_IR_Operand const& dest,
	const Type*        const& source_t,
	x86_Asm_IR_Operand const& source,
	x86_Asm_IR*             & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE_CONVERSION_ERROR;

	if (is_real_floating_type(dest_t) 
		&& is_real_floating_type(source_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::MOVSS,
			dest,
			source);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else if (is_integer_type(dest_t) 
		       && is_integer_type(source_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::MOV,
			dest,
			source);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else if (is_pointer_type(dest_t)
		       && types_are_equivalent(
				      dereference_type(dest_t), 
				      source_t)) {
		x86_Asm_IR_OperandVal v;
		v.rao.reg = dest.get_constant_val().reg_index;
		v.rao.offset = 0;

		x86_Asm_IR_Operand new_op1 
		    = x86_Asm_IR_Operand(
			      x86_Asm_IR_OperandType::REGISTER_AND_OFFSET,
				  v);
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::MOV,
			source,
			new_op1);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else {

	}

	if (exitcode == CodeGeneratorExitCode::FAILURE_CONVERSION_ERROR) {
		cout << "\x1B[31m"
			 << "construct_x86_AssemblyInstruction_mov:"
			 << " failed to convert type ";
		print_type(dest_t);
		cout << " to type ";
		print_type(source_t);
		cout << "." 
			 << "\033[0m"
			 << endl;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_add(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	if (is_real_floating_type(op1_t)
		&& is_real_floating_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::ADDSS,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;
		
	} else if (is_integer_type(op1_t) 
			   && is_integer_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::ADD,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else {

	}

	if (exitcode == CodeGeneratorExitCode::FAILURE) {
		cout << "\x1B[31m";

		cout << "construct_x86_AssemblyInstruction_add:"
			 << " failed to convert type ";
		print_type(op1_t);
		cout << " to type ";
		print_type(op2_t);
		cout << "." 
			 << "\033[0m"
			 << endl;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode construct_x86_AssemblyInstruction_subtract(
	const Type*        const& op1_t,
	x86_Asm_IR_Operand const& op1,
	const Type*        const& op2_t,
	x86_Asm_IR_Operand const& op2,
	x86_Asm_IR*             & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	if (is_real_floating_type(op1_t)
		&& is_real_floating_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::SUBSS,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else if (is_integer_type(op1_t)
		       && is_integer_type(op2_t)) {
		*instrs++ = x86_Asm_IR(
			x86_Asm_IR_Mnemonic::SUB,
			op1,
			op2);
		exitcode = CodeGeneratorExitCode::SUCCESS;

	} else {

	}

	if (exitcode == CodeGeneratorExitCode::FAILURE) {
		cout << "\x1B[31m";
		cout << "construct_x86_AssemblyInstruction_sub:"
			 << " failed to convert type ";
		print_type(op1_t);
		cout << " to type ";
		print_type(op2_t);
		cout << "." 
			 << "\033[0m"
			 << endl;
	}
	return exitcode;
}

static x86_RegisterAllocMap construct_blank_alloc_map() {
	const x86_RegisterAllocMap retval
		= x86_RegisterAllocMap({ });
	return retval;
}

static inline
x86_RegisterType get_register_type_from_ast_type(
	const Type* const& type)
{
	x86_RegisterType reg_type = x86_RegisterType::UNDEFINED;
	if (is_integer_type(type)) {
		const int sz = get_sizeof_type(type);
		switch (sz) {
			case 8: reg_type = x86_RegisterType::INT_64; break;
			case 4: reg_type = x86_RegisterType::INT_32; break;
			case 2: reg_type = x86_RegisterType::INT_16; break;
			case 1: reg_type = x86_RegisterType::INT_8;  break;
			default: break;
		}

	} else if (is_real_floating_type(type)) {
		const int sz = get_sizeof_type(type);
		switch (sz) {
			case 8: reg_type = x86_RegisterType::FLOAT_64; break;
			case 4: reg_type = x86_RegisterType::FLOAT_32; break;
			default: break;
		}

	} else {

	}
	return reg_type;
}

static inline
bool accumulator_is_free(
	x86_RegisterAllocMap const& map) 
{
	const bool retval 
		=  map.rax    == false
		   && map.eax == false
		   && map.ax  == false
		   && map.ah  == false
		   && map.al  == false;
	return retval; 
}

static inline
bool counter_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rcx    == false
		  && map.ecx == false
		  && map.cx  == false
		  && map.ch  == false
	  	  && map.cl  == false;
	return retval; 
}

static inline
bool data_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rdx    == false
		  && map.edx == false
		  && map.dx  == false
		  && map.dh  == false
		  && map.dl  == false;
	return retval;
}

static inline
bool base_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rbx    == false
		  && map.ebx == false
		  && map.bx  == false
		  && map.bh  == false
		  && map.bl  == false;
	return retval;
}

static inline
bool stack_pointer_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rsp    == false
		  && map.esp == false
		  && map.sp  == false
		  && map.spl == false;
	return retval;
}

static inline
bool stack_base_pointer_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rbp    == false
		  && map.ebp == false
		  && map.bp  == false
		  && map.bpl == false;
	return retval;
}

static inline
bool source_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rsi    == false
		  && map.esi == false
		  && map.si  == false
		  && map.sil == false;
	return retval;
}

static inline
bool destination_is_free(
	x86_RegisterAllocMap const& map)
{
	const bool retval
		= map.rdi    == false
		  && map.edi == false
		  && map.di  == false
		  && map.dil == false;
	return retval;
}

static inline
void allocate_given_register(
	x86_RegisterAllocMap      & map,
	x86_RegisterName     const& name)
{
	switch (name) {
		case x86_RegisterName::XMM0: map.xmm0 = true; break;
		case x86_RegisterName::XMM1: map.xmm1 = true; break;
		case x86_RegisterName::XMM2: map.xmm2 = true; break;
		case x86_RegisterName::XMM3: map.xmm3 = true; break;
		case x86_RegisterName::XMM4: map.xmm4 = true; break;
		case x86_RegisterName::XMM5: map.xmm5 = true; break;
		case x86_RegisterName::XMM6: map.xmm6 = true; break;
		case x86_RegisterName::XMM7: map.xmm7 = true; break;
		case x86_RegisterName::RAX : map.rax  = true; break;
		case x86_RegisterName::EAX : map.eax  = true; break;
		case x86_RegisterName::AX  : map.ax   = true; break;
		case x86_RegisterName::AH  : map.ah   = true; break;
		case x86_RegisterName::AL  : map.al   = true; break;
		case x86_RegisterName::RCX : map.rcx  = true; break;
		case x86_RegisterName::ECX : map.ecx  = true; break;
		case x86_RegisterName::CX  : map.cx   = true; break;
		case x86_RegisterName::CH  : map.ch   = true; break;
		case x86_RegisterName::CL  : map.cl   = true; break;
		case x86_RegisterName::RDX : map.rdx  = true; break;
		case x86_RegisterName::EDX : map.edx  = true; break;
		case x86_RegisterName::DX  : map.dx   = true; break;
		case x86_RegisterName::DH  : map.dh   = true; break;
		case x86_RegisterName::DL  : map.dl   = true; break;
		case x86_RegisterName::RBX : map.rbx  = true; break;
		case x86_RegisterName::EBX : map.ebx  = true; break;
		case x86_RegisterName::BX  : map.bx   = true; break;
		case x86_RegisterName::BH  : map.bh   = true; break;
		case x86_RegisterName::BL  : map.bl   = true; break;
		case x86_RegisterName::RSP : map.rsp  = true; break;
		case x86_RegisterName::ESP :  map.esp  = true; break;
		case x86_RegisterName::SP  :   map.sp   = true; break;
		case x86_RegisterName::SPL :  map.spl  = true; break;
		case x86_RegisterName::RBP :  map.rbp  = true; break;
		case x86_RegisterName::EBP :  map.ebp  = true; break;
		case x86_RegisterName::BP  :   map.bp   = true; break;
		case x86_RegisterName::BPL:  map.bpl  = true; break;
		case x86_RegisterName::RSI:  map.rsi  = true; break;
		case x86_RegisterName::ESI:  map.esi  = true; break;
		case x86_RegisterName::SI :   map.si   = true; break;
		case x86_RegisterName::SIL:  map.sil  = true; break;
		case x86_RegisterName::RDI:  map.rdi  = true; break;
		case x86_RegisterName::EDI:  map.edi  = true; break;
		case x86_RegisterName::DI :   map.di   = true; break;
		case x86_RegisterName::DIL:  map.dil  = true; break;
		case x86_RegisterName::R8 :   map.r8   = true; break;
		case x86_RegisterName::R9 :   map.r9   = true; break;
		case x86_RegisterName::R10:  map.r10  = true; break;
		case x86_RegisterName::R11:  map.r11  = true; break;
		case x86_RegisterName::R12:  map.r12  = true; break;
		case x86_RegisterName::R13:  map.r13  = true; break;
		case x86_RegisterName::R14:  map.r14  = true; break;
		case x86_RegisterName::R15:  map.r15  = true; break;
		case x86_RegisterName::RIP:  map.rip  = true; break;
		default: break;
	}
}

static inline
x86_RegisterName allocate_accumulator_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rax     = true;
			alloced_reg = x86_RegisterName::RAX;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.eax     = true;
			alloced_reg = x86_RegisterName::EAX;
			break;

		case x86_RegisterType::INT_16:
			map.ax      = true;
			alloced_reg = x86_RegisterName::AX;
			break;

		case x86_RegisterType::INT_8:
			map.ah      = true;
			alloced_reg = x86_RegisterName::AH;
			break;
		*/

		default:
			break;
	
	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_counter_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rcx     = true;
			alloced_reg = x86_RegisterName::RCX;
			break;

		/*case x86_RegisterType::INT_32:
			map.ecx     = true;
			alloced_reg = x86_RegisterName::ECX;
			break;

		case x86_RegisterType::INT_16:
			map.cx      = true;
			alloced_reg = x86_RegisterName::CX;
			break;

		case x86_RegisterType::INT_8:
			map.ch      = true;
			alloced_reg = x86_RegisterName::CH;
			break;*/

		default:
			break;
	
	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_data_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rdx     = true;
			alloced_reg = x86_RegisterName::RDX;
			break;

		/*case x86_RegisterType::INT_32:
			map.edx     = true;
			alloced_reg = x86_RegisterName::EDX;
			break;

		case x86_RegisterType::INT_16:
			map.dx       = true;
			alloced_reg = x86_RegisterName::DX;
			break;

		case x86_RegisterType::INT_8:
			map.dl      = true;
			alloced_reg = x86_RegisterName::DL;
			break;*/

		default:
			break;
	
	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_base_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rbx     = true;
			alloced_reg = x86_RegisterName::RBX;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.ebx     = true;
			alloced_reg = x86_RegisterName::EBX;
			break;

		case x86_RegisterType::INT_16:
			map.bx       = true;
			alloced_reg = x86_RegisterName::BX;
			break;

		case x86_RegisterType::INT_8:
			map.bl      = true;
			alloced_reg = x86_RegisterName::BL;
			break;
		*/

		default:
			break;
	
	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_stack_pointer_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rsp     = true;
			alloced_reg = x86_RegisterName::RSP;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.esp = true;
			alloced_reg = x86_RegisterName::ESP;
			break;

		case x86_RegisterType::INT_16:
			map.sp = true;
			alloced_reg = x86_RegisterName::SP;
			break;

		case x86_RegisterType::INT_8:
			map.spl = true;
			alloced_reg = x86_RegisterName::SPL;
			break;*/

		default:
			break;

	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_stack_base_pointer_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rbp     = true;
			alloced_reg = x86_RegisterName::RBP;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.ebp     = true;
			alloced_reg = x86_RegisterName::EBP;
			break;

		case x86_RegisterType::INT_16:
			map.bp      = true;
			alloced_reg = x86_RegisterName::BP;
			break;

		case x86_RegisterType::INT_8:
			map.bpl     = true;
			alloced_reg = x86_RegisterName::BPL;
			break;
		*/

		default:
			break;

	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_source_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rsi     = true;
			alloced_reg = x86_RegisterName::RSI;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.esi     = true;
			alloced_reg = x86_RegisterName::ESI;
			break;

		case x86_RegisterType::INT_16:
			map.si      = true;
			alloced_reg = x86_RegisterName::SI;
			break;

		case x86_RegisterType::INT_8:
			map.sil     = true;
			alloced_reg = x86_RegisterName::SIL;
			break;
		*/

		default:
			break;

	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_destination_of_size(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName alloced_reg;
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
			map.rdi     = true;
			alloced_reg = x86_RegisterName::RDI;
			break;

		/*
		case x86_RegisterType::INT_32:
			map.edi     = true;
			alloced_reg = x86_RegisterName::EDI;
			break;

		case x86_RegisterType::INT_16:
			map.di      = true;
			alloced_reg = x86_RegisterName::DI;
			break;

		case x86_RegisterType::INT_8:
			map.dil     = true;
			alloced_reg = x86_RegisterName::DIL;
			break;
		*/

		default:
			break;

	}
	return alloced_reg;
}

static inline
x86_RegisterName allocate_register(
	x86_RegisterAllocMap      & map,
	x86_RegisterType     const& register_size)
{
	x86_RegisterName allocated_register;
	
	switch (register_size) {

		case x86_RegisterType::INT_64:
		case x86_RegisterType::INT_32:
		case x86_RegisterType::INT_16:
		case x86_RegisterType::INT_8:
		{
			if (accumulator_is_free(map)) {
				allocated_register 
					= allocate_accumulator_of_size(
						map,
						register_size);

			} else if (counter_is_free(map)) {
				allocated_register
					= allocate_counter_of_size(
						map,
						register_size);

			} else if (data_is_free(map)) {
				allocated_register 
					= allocate_data_of_size(
						map, 
						register_size);

			} else if (base_is_free(map)) {
				allocated_register 
					= allocate_base_of_size(
						map, 
						register_size);

			} else if (stack_pointer_is_free(map)) {
				allocated_register
					= allocate_stack_pointer_of_size(
						map, 
						register_size);

			} else if (stack_base_pointer_is_free(map)) {
				allocated_register 
					= allocate_stack_base_pointer_of_size(
						map, 
						register_size);

			} else if (source_is_free(map)) {
				allocated_register 
					= allocate_source_of_size(
						map, 
						register_size);

			} else if (destination_is_free(map)) {
				allocated_register
					= allocate_destination_of_size(
						map, 
						register_size);

			} else {
				cout << "alloc_fail";
			}
			break;
		}

		case x86_RegisterType::FLOAT_64:
		case x86_RegisterType::FLOAT_32:
		{
			if (map.xmm0 == false) {
				allocated_register 
					= x86_RegisterName::XMM0;
				map.xmm0 
					= true;

			} else if (map.xmm1 == false) {
				allocated_register 
					= x86_RegisterName::XMM1;
				map.xmm1 
					= true;

			} else if (map.xmm2 == false) {
				allocated_register 
					= x86_RegisterName::XMM2;
				map.xmm2 
					= true;

			} else if (map.xmm3 == false) {
				allocated_register 
					= x86_RegisterName::XMM3;
				map.xmm3 
					= true;

			} else if (map.xmm4 == false) {
				allocated_register 
					= x86_RegisterName::XMM4;
				map.xmm4 
					= true;

			} else if (map.xmm5 == false) {
				allocated_register 
					= x86_RegisterName::XMM5;
				map.xmm5 
					= true;

			} else if (map.xmm6 == false) {
				allocated_register 
					= x86_RegisterName::XMM6;
				map.xmm6 
					= true;

			} else if (map.xmm7 == false) {
				allocated_register 
					= x86_RegisterName::XMM7;
				map.xmm7 
					= true;

			} else {
				cout << "alloc_fail";
			}
			break;
		}

		default:
			cout << "alloc_fail";
			break;

	}
	return allocated_register;
}

static inline
CodeGeneratorExitCode gen_symbol(
	const SymbolTableEntry* const& symbol_entry,
	x86_Asm_IR*                  & instrs,
	x86_Asm_IR_Operand           & operand,
	x86_RegisterAllocMap    const& map)
{
	report_gen("gen_symbol");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

 	switch (symbol_entry->scope) {

		case Scope::BLOCK:
		case Scope::FUNCTION:
		{
			x86_RegisterAllocMap alloc_map
				= construct_blank_alloc_map();

			register_and_offset rao;
			rao.offset
				= symbol_entry->base_pointer_offset
				  - symbol_entry->function_ptr->function_frame_size;
			rao.reg = x86_RegisterName::RBP;
			x86_Asm_IR_OperandVal v;
			v.rao = rao;
			operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::REGISTER_AND_OFFSET,
					v);

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case Scope::FILE:
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

static inline
const char* construct_label(
	const char*   label_prefix,
	int         & num_labels_used)	
{
	char* const label_str = new char[16];

	int i = 0;
	do {
		label_str[i] = label_prefix[i];
		i++;
	} while (label_prefix[i] != '\0');

	char* const label_substr_start 
		= label_str + i;
	const int label_substr_len
		= 16 - i;

	_itoa_s(
		num_labels_used++, 
		label_substr_start,
		label_substr_len,
		10);

	return label_str;;
}

static inline
CodeGeneratorExitCode gen_literals(
	int               & num_labels_used,
	SymbolTable* const& symbol_table,
	x86_Asm_IR*       & instrs)
{
	report_gen("gen_literals");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;
	
	SymbolTableEntry*  entries [1028]  = { };
	symbol_table->get_entries(entries);
	/* for each entry in the symbol table */
	int literal_constant_ptr_i = 0;
	for (SymbolTableEntry** e = entries;
		 *e != NULL;
		 e++) {

		if ((*e)->is_literal
			&& ((*e)->type->classifier == TypeClassifier::OBJECT
			    && !is_integer_type((*e)->type))) {

			(*e)->literal_constant_ptr_label 
				= construct_label(
					".LCP_", 
					num_labels_used);
			
			x86_Asm_IR_OperandVal v;
			v.dwui = (*e)->value;
			
			*instrs = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::LONG,
				x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
					v));
			
			instrs->set_label(
				(*e)->literal_constant_ptr_label);
			instrs->set_type(
				x86_Asm_IR_Type::LABELED_INSTRUCTION);
			instrs++;
		}
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_primary_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	report_gen("gen_primary_expression");
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;
	switch (node->get_alt()) {

		case AstNodeAlt::PRIMARY_EXPRESSION_1:
		{
			const char* const symbol 
				= node->get_symbol();
			const SymbolTable* const symtab
				= node->get_symbol_table(symbol);
			const SymbolTableEntry* const symtab_entry
				= symtab->get_entry(symbol);

			if (symbol == NULL) {
				cout << "codegen.h:gen_primary_expression:"
						"error on unrecognised identifier.\n";
			}
			gen_symbol(
				symtab_entry,
				instrs,
				operand,
				alloc_map);

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_2:
		{
			exitcode = CodeGeneratorExitCode::SUCCESS;
			x86_RegisterAllocMap literal_alloc_map
				= alloc_map;

			const char* const symbol 
				= node->get_symbol();
			const SymbolTable* const symtab
				= node->get_symbol_table(symbol);
			const SymbolTableEntry* const symtab_entry
				= symtab->get_entry(symbol);
			const Type* const type
				= symtab_entry->type;

			/* See if this will be inlined (made immediate) */
			if (is_integer_type(type)) {
				
				x86_Asm_IR_OperandVal v;
				v.dwui  
					= symtab_entry->value;
				operand 
					= x86_Asm_IR_Operand(
					      x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
						  v);

			} else {
				/* Else load literal from memory. */
				label_and_register lar;
				lar.label
					= symtab_entry
					  ->literal_constant_ptr_label;
				lar.reg
					= x86_RegisterName::RIP;

				x86_Asm_IR_OperandVal v;
				v.lar = lar;

				operand
					= x86_Asm_IR_Operand(
						x86_Asm_IR_OperandType::LABEL_AND_REGISTER,
						v);

			}

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_3:
		{
			// TODO; String literal.
			break;
		}

		case AstNodeAlt::PRIMARY_EXPRESSION_4:
		{
			const AnnotatedAstNode* const expression
				= node->get_child();
			if (gen_expression(
				num_labels_used,
				expression,
				instrs,
				alloc_map,
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

static inline
CodeGeneratorExitCode gen_postfix_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_postfix_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::POSTFIX_EXPRESSION_1:
		{
			const AnnotatedAstNode* const primary_expression
				= node->get_child();
			if (gen_primary_expression(
				num_labels_used,
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
			x86_RegisterAllocMap expression_alloc_map
				= alloc_map;

			/* Loading AST data. */
			const AnnotatedAstNode* const postfix_expression 
				= node->get_child();
			const AnnotatedAstNode* const expression 
				= postfix_expression->get_sibling();
			
			const Type* const postfix_expression_type
				= postfix_expression->get_type();
				
			/* Compute the array address */
			x86_RegisterAllocMap postfix_alloc_map
				= alloc_map;
			const x86_RegisterType register_type
				= get_register_type_from_ast_type(
				      postfix_expression_type);
			x86_RegisterName postfix_register
				= allocate_register(
					postfix_alloc_map,
					register_type);

			/* Computing the base */
			x86_Asm_IR_Operand op1;
			if (gen_postfix_expression(
				num_labels_used,
				postfix_expression,
				instrs,
				expression_alloc_map,
				op1) 
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const x86_RegisterName base_register_name
				= allocate_register(
				      postfix_alloc_map,
					  register_type);

			const x86_Asm_IR_Operand base_register_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					{ base_register_name });
			
			construct_x86_AssemblyInstruction_move(
				postfix_expression_type,
				base_register_operand,
				postfix_expression_type,
				op1,
				instrs);

			/* Compute the offset */
			x86_Asm_IR_Operand offset;
			if (gen_expression(
					num_labels_used,
					expression,
					instrs,
					expression_alloc_map,
					offset)
				== CodeGeneratorExitCode::SUCCESS) {
				exitcode = CodeGeneratorExitCode::FAILURE;
				break;
			}
			x86_Asm_IR_OperandVal size_imm;

			const Type* const element_type
				= get_element_type(
					postfix_expression_type);
			const int element_size
				= get_sizeof_type(
					element_type);
			size_imm.dwui
				= element_size;

			const x86_Asm_IR_Operand size_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
					size_imm);

			construct_x86_AssemblyInstruction_multiply(
				postfix_expression_type,
				offset,
				postfix_expression_type,
				size_operand,
				instrs);

			/* Computing the address of the array plus offset */
			construct_x86_AssemblyInstruction_add(
				postfix_expression_type,
				base_register_operand,
				postfix_expression_type,
				offset,
				instrs);

			/* Dereference */
			x86_Asm_IR_OperandVal derefed_postfix_register_val;
			derefed_postfix_register_val.reg_containing_addr 
				= postfix_register;

			x86_Asm_IR_Operand derefed_postfix_register
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::REGISTER_AND_OFFSET,
					derefed_postfix_register_val);

			x86_Asm_IR_Operand postfix_register_op
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					derefed_postfix_register_val);

			construct_x86_AssemblyInstruction_move(
				postfix_expression_type,
				postfix_register_op,
				postfix_expression_type,
				derefed_postfix_register,
				instrs);

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}
			
		case AstNodeAlt::POSTFIX_EXPRESSION_3:
		{
			/* TODO; FUNCTION CALLING ROUTINE. */
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_4:
		{
			/* TODO; . */
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_5:
		{
			/* TODO; -> */
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_6:
		case AstNodeAlt::POSTFIX_EXPRESSION_7:
		{
			x86_RegisterAllocMap expression_alloc_map
				= alloc_map;

			/* Loading AST data. */
			AnnotatedAstNode* postfix_expression
				= node->get_child();

			x86_Asm_IR_Operand postfix_expression_operand;
			if (gen_postfix_expression(
				num_labels_used,
				postfix_expression,
				instrs,
				expression_alloc_map,
				postfix_expression_operand)
				== CodeGeneratorExitCode::FAILURE) {
				exitcode = CodeGeneratorExitCode::FAILURE;
				break;
			}

			x86_Asm_IR_OperandVal reg_pre_side_effect;
			reg_pre_side_effect.reg_index 
				= allocate_register(
					expression_alloc_map, 
					get_register_type_from_ast_type(postfix_expression->get_type()));

			const Type* const postfix_expression_type
				= postfix_expression->get_type();

			const x86_Asm_IR_Operand reg_pre_side_effect_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					reg_pre_side_effect);

			construct_x86_AssemblyInstruction_move(
				postfix_expression_type,
				postfix_expression_operand,
				postfix_expression_type,
				reg_pre_side_effect_operand,
				instrs);

			switch (node->get_alt()) {

				case AstNodeAlt::POSTFIX_EXPRESSION_6:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::INC,
						postfix_expression_operand);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case AstNodeAlt::POSTFIX_EXPRESSION_7:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::DEC,
						postfix_expression_operand);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				default:
					break;
			}
			
			operand = x86_Asm_IR_Operand(
				x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
				reg_pre_side_effect);
			break;
		}

		case AstNodeAlt::POSTFIX_EXPRESSION_8:
		case AstNodeAlt::POSTFIX_EXPRESSION_9:
		{
			AnnotatedAstNode* type_name 
				= node->get_child();
			AnnotatedAstNode* initializer_list 
				= type_name->get_child();
			
			if (gen_initializer_list(
				num_labels_used,
				initializer_list,
				instrs,
				alloc_map) == CodeGeneratorExitCode::FAILURE) {
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

static inline
CodeGeneratorExitCode gen_unary_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_unary_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::UNARY_EXPRESSION_1:
		{
			const AnnotatedAstNode* const postfix_expression
				= node->get_child();
			if (gen_postfix_expression(
				num_labels_used,
				postfix_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_2:
		{
			const AnnotatedAstNode* const unary_expression
				= node->get_child();
			if (gen_unary_expression(
				num_labels_used,
				unary_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::INC,
				operand);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_3:
		{
			const AnnotatedAstNode* const unary_expression
				= node->get_child();
			
			x86_Asm_IR_Operand unary_expression_operand;

			if (gen_unary_expression(
				num_labels_used,
				unary_expression,
				instrs,
				alloc_map,
				unary_expression_operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::DEC,
				unary_expression_operand);
			
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_4:
		{
			const AnnotatedAstNode* const unary_operator
				= node->get_child();
			const AnnotatedAstNode* const cast_expression
				= unary_operator->get_sibling();

			x86_Asm_IR_Operand cast_expression_output_operand
				= x86_Asm_IR_Operand();

			if (gen_cast_expression(
				num_labels_used,
				cast_expression,
				instrs,
				alloc_map,
				cast_expression_output_operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			switch (unary_operator->get_alt()) {

				case AstNodeAlt::UNARY_OPERATOR_1:
				{
					x86_RegisterAllocMap unary_expression_alloc_map
						= alloc_map;

					const char* const cast_expression_symbol
						= cast_expression->get_symbol();
					const SymbolTable* const cast_expression_scope
						= node->get_symbol_table(
							cast_expression_symbol);
					const SymbolTableEntry* const cast_expression_entry
						= cast_expression_scope->get_entry(
							cast_expression_symbol);

					const Type* const cast_expression_type
						= cast_expression->get_type();
					const x86_RegisterType cast_expression_reg_type
						= get_register_type_from_ast_type(
							cast_expression_type);
					const x86_RegisterName cast_expression_register
						= allocate_register(
							unary_expression_alloc_map,
							cast_expression_reg_type);

					const x86_Asm_IR_Operand 
						reference_to_cast_expression_reg
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal(
								{ cast_expression_register }));

					x86_Asm_IR_OperandVal cast_expression_imm_val;
					cast_expression_imm_val.dwui 
						= cast_expression_entry->base_pointer_offset;

					x86_Asm_IR_Operand reference_to_cast_expression_imm
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
							cast_expression_imm_val);

					x86_Asm_IR_Operand rbp_reg
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal(
								{ x86_RegisterName::RBP }));

					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::MOV,
						reference_to_cast_expression_reg,
						rbp_reg);

					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::ADD,
						reference_to_cast_expression_reg,
						reference_to_cast_expression_imm);

					operand = reference_to_cast_expression_reg;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::UNARY_OPERATOR_2:
				{
					x86_Asm_IR_OperandVal v;

					v.reg_index 
						= cast_expression_output_operand.get_constant_val().reg_index;

					x86_Asm_IR_Operand op1_dereferenced
						= x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							v);

					const Type* const cast_expression_type
						= cast_expression->get_type();
					const Type* const dereferenced_cast_expression_type
						= dereference_type(
							cast_expression_type);

					construct_x86_AssemblyInstruction_move(
						cast_expression_type,
						cast_expression_output_operand,
						dereferenced_cast_expression_type,
						op1_dereferenced,
						instrs);

					operand = cast_expression_output_operand;
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}

				case AstNodeAlt::UNARY_OPERATOR_3:
				{
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::UNARY_OPERATOR_4:
				{
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::NEG,
						cast_expression_output_operand);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::UNARY_OPERATOR_5:
				{
					break;
				}
				
				case AstNodeAlt::UNARY_OPERATOR_6:
				{
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::NEG,
						cast_expression_output_operand);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				default:
					break;
			}
			break;
		}

		case AstNodeAlt::UNARY_EXPRESSION_5:
		{
			const AnnotatedAstNode* const type_name
				= node->get_child();

			const Type* const type_name_type
				= type_name->get_type();
			const int sizeof_type_name
				= get_sizeof_type(type_name_type);

			x86_Asm_IR_OperandVal v;
			v.dwui = sizeof_type_name;

			x86_Asm_IR_Operand op
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
					v);
			operand = op;

			exitcode = CodeGeneratorExitCode::SUCCESS;
		}

		case AstNodeAlt::UNARY_EXPRESSION_6:
		{
			const AnnotatedAstNode* const type_name 
				= node->get_child();

			const Type* const type_name_type
				= type_name->get_type();
			const int sizeof_type_name
				= get_sizeof_type(type_name_type);

			x86_Asm_IR_OperandVal v;
			v.dwui = sizeof_type_name;

			x86_Asm_IR_Operand op
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
					v);
			operand = op;

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_cast_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_cast_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::CAST_EXPRESSION_1:
		{
			const AnnotatedAstNode* const unary_expression
				= node->get_child();
			if (gen_unary_expression(
				num_labels_used,
				unary_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::CAST_EXPRESSION_2:
		{
			const AnnotatedAstNode* const type_name
				= node->get_child();
			const AnnotatedAstNode* const cast_expression
				= type_name->get_sibling();

			if (gen_cast_expression(
				num_labels_used,
				cast_expression,
				instrs,
				alloc_map,
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

static inline
CodeGeneratorExitCode gen_multiplicative_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
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
				num_labels_used,
				cast_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2:		
		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3:
		case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4:
		{
			x86_RegisterAllocMap multicative_expression_2_alloc_map
				= alloc_map;

			const AnnotatedAstNode* const multiplicative_expression
				= node->get_child();
			const AnnotatedAstNode* const cast_expression
				= multiplicative_expression->get_sibling();

			x86_Asm_IR_Operand op1;
			x86_Asm_IR_Operand op2;

			if (gen_multiplicative_expression(
				num_labels_used,
				multiplicative_expression,
				instrs,
				multicative_expression_2_alloc_map,
				op1) == CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const multiplicative_expression_type
				= multiplicative_expression->get_type();
			const x86_RegisterType multiplicative_expression_reg_type
				= get_register_type_from_ast_type(
					multiplicative_expression_type);

			x86_RegisterName temp 
				= allocate_register(
				      multicative_expression_2_alloc_map,
					  multiplicative_expression_reg_type);

			construct_x86_AssemblyInstruction_move(
				multiplicative_expression_type,
				x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					x86_Asm_IR_OperandVal(
						{ temp })),
				multiplicative_expression_type,
				op1,
				instrs);

			if (gen_cast_expression(
				num_labels_used,
				cast_expression,
				instrs,
				multicative_expression_2_alloc_map,
				op2) == CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const cast_expression_type
				= cast_expression->get_type();

			x86_Asm_IR_Operand new_cast_expression_operand;
			convert_operand_to_correct_type(
				cast_expression_type,
				op2,
				op2.get_type(),
				new_cast_expression_operand,
				x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
				instrs,
				multicative_expression_2_alloc_map);
			
			bool valid_typing 
				= true;

			x86_Asm_IR_Operand multiplicative_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					x86_Asm_IR_OperandVal(
						{ temp }));

			switch (node->get_alt()) {

				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_2:
				{
					// TODO; swap type.
					construct_x86_AssemblyInstruction_multiply(
						multiplicative_expression_type,
						multiplicative_operand,
						cast_expression_type,
						new_cast_expression_operand,
						instrs);
					break;
				}
				
				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_3:
				{
					construct_x86_AssemblyInstruction_divide(
						multiplicative_expression_type,
						multiplicative_operand,
						cast_expression_type,
						new_cast_expression_operand,
						instrs);
					break;
				}

				case AstNodeAlt::MULTIPLICATIVE_EXPRESSION_4:
				{
					/*construct_x86_AssemblyInstruction_modulo(
						multiplicative_expression->get_type(),
						x86_AssemblyInstructionOperand(
							x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
							x86_AssemblyInstructionOperandVal({ temp })),
						cast_expression->get_type(),
						op2,
						instrs);*/
					break;
				}

				/*
				*instrs++ = x86_AssemblyInstruction(
					x86_AssemblyInstructionMnemonic::IDIV,
					x86_AssemblyInstructionOperand(
						x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
						x86_AssemblyInstructionOperandVal({ temp })),
					op2);
				*instrs++ = x86_AssemblyInstruction(
					x86_AssemblyInstructionMnemonic::MOVSS,
					x86_AssemblyInstructionOperand(
						x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
						x86_AssemblyInstructionOperandVal({ x86_Register::RDX})),
					x86_AssemblyInstructionOperand(
						x86_AssemblyInstructionOperandType::X86_REGISTER_INDEX,
						x86_AssemblyInstructionOperandVal({ temp })));
				*/
					 					
				default:
					valid_typing = false;
					break;

			}
			if (valid_typing) {
					operand = x86_Asm_IR_Operand(
						x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
						x86_Asm_IR_OperandVal({ temp }));
					exitcode = CodeGeneratorExitCode::SUCCESS;
			}
			break;

		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_additive_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_additive_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::ADDITIVE_EXPRESSION_1:
		{
			const AnnotatedAstNode* const multiplicative_expression
				= node->get_child();
			if (gen_multiplicative_expression(
				num_labels_used,
				multiplicative_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::ADDITIVE_EXPRESSION_2:
		case AstNodeAlt::ADDITIVE_EXPRESSION_3:
		{
			const AnnotatedAstNode* const additive_expression
				= node->get_child();
			const AnnotatedAstNode* const multiplicative_expression
				= additive_expression->get_sibling();

			x86_RegisterAllocMap additive_expression_alloc_map
				= alloc_map;

			x86_Asm_IR_Operand additive_expression_reg;

			if (gen_additive_expression(
				num_labels_used,
				additive_expression,
				instrs,
				additive_expression_alloc_map,
				additive_expression_reg)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const additive_expression_type
				= additive_expression->get_type();
			const Type* const multiplicative_expression_type
				= multiplicative_expression->get_type();

			const x86_RegisterType additive_expression_register_type
				= get_register_type_from_ast_type(
					additive_expression_type);

			const x86_RegisterName additive_expression_register
				= allocate_register(
					additive_expression_alloc_map,
					additive_expression_register_type);

			x86_Asm_IR_Operand output
				= x86_Asm_IR_Operand(
				    x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					{ additive_expression_register });

			construct_x86_AssemblyInstruction_move(
				additive_expression_type,
				output,
				additive_expression_type,
				additive_expression_reg,
				instrs);

			x86_Asm_IR_Operand multiplicative_expression_reg;

			if (gen_multiplicative_expression(
				num_labels_used,
				multiplicative_expression,
				instrs,
				additive_expression_alloc_map,
				multiplicative_expression_reg)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}


			bool valid_typing = true;
			switch (node->get_alt()) {

				case AstNodeAlt::ADDITIVE_EXPRESSION_2:
					construct_x86_AssemblyInstruction_add(
						additive_expression_type,
						output,
						multiplicative_expression_type,
						multiplicative_expression_reg,
						instrs);
					break;
				
				case AstNodeAlt::ADDITIVE_EXPRESSION_3:
					construct_x86_AssemblyInstruction_subtract(
						additive_expression_type,
						output,
						multiplicative_expression_type,
						multiplicative_expression_reg,
						instrs);
					break; 

				default:
					valid_typing = false;
					break;
			}
			if (valid_typing) {
				operand = output;
				exitcode = CodeGeneratorExitCode::SUCCESS;
			}
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_shift_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_shift_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::SHIFT_EXPRESSION_1:
		{
			const AnnotatedAstNode* const additive_expression
				= node->get_child();
			if (gen_additive_expression(
				num_labels_used,
				additive_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::SHIFT_EXPRESSION_2:
		case AstNodeAlt::SHIFT_EXPRESSION_3:
		{
			const AnnotatedAstNode* const shift_expression
				= node->get_child();
			const AnnotatedAstNode* const additive_expression
				= shift_expression->get_sibling();

			x86_RegisterAllocMap shift_expression_alloc_map
				= alloc_map;

			x86_Asm_IR_Operand op1;
			x86_Asm_IR_Operand op2;

			if (gen_shift_expression(
				num_labels_used,
				shift_expression,
				instrs,
				shift_expression_alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const shift_expression_type
				= shift_expression->get_type();

			const x86_RegisterType shift_expression_register_type
				= get_register_type_from_ast_type(
					shift_expression_type);

			const x86_RegisterName shift_expression_register
				= allocate_register(
					shift_expression_alloc_map,
					shift_expression_register_type);

			x86_Asm_IR_Operand output
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					{ shift_expression_register });

			const Type* const additive_expression_type
				= additive_expression->get_type();

			construct_x86_AssemblyInstruction_move(
				shift_expression_type,
				output,
				additive_expression_type,
				op1,
				instrs);

			if (gen_additive_expression(
				num_labels_used,
				additive_expression,
				instrs,
				shift_expression_alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			switch (node->get_alt()) {

				case AstNodeAlt::SHIFT_EXPRESSION_2:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SHL,
						output,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case AstNodeAlt::SHIFT_EXPRESSION_3:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SHR,
						output,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				default:
					break;

			}
			operand = op1;
			break;
		}

		default:
			break;
	}

	return exitcode;
}

static inline
CodeGeneratorExitCode gen_relational_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_relational_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::RELATIONAL_EXPRESSION_1:
		{
			const AnnotatedAstNode* const shift_expression
				= node->get_child();
			if (gen_shift_expression(
					num_labels_used,
					shift_expression,
					instrs,
					alloc_map,
					operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::RELATIONAL_EXPRESSION_2:
		case AstNodeAlt::RELATIONAL_EXPRESSION_3:
		case AstNodeAlt::RELATIONAL_EXPRESSION_4:
		case AstNodeAlt::RELATIONAL_EXPRESSION_5:
		{
			const AnnotatedAstNode* const relational_expression
				= node->get_child();
			const AnnotatedAstNode* const shift_expression
				= relational_expression->get_sibling();

			x86_Asm_IR_Operand op1;

			if (gen_relational_expression(
				num_labels_used,
				relational_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_shift_expression(
				num_labels_used,
				shift_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ 
				= x86_Asm_IR(
					x86_Asm_IR_Mnemonic::CMP,
					op1,
					op2);

			switch (node->get_alt()) {

				case AstNodeAlt::RELATIONAL_EXPRESSION_2:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETL,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case AstNodeAlt::RELATIONAL_EXPRESSION_3:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETG,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				

				case AstNodeAlt::RELATIONAL_EXPRESSION_4:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETLE,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case AstNodeAlt::RELATIONAL_EXPRESSION_5:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETGE,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				default:
					break;

			}
			operand = op1;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_equality_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_equality_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::EQUALITY_EXPRESSION_1:
		{
			const AnnotatedAstNode* const relational_expression
				= node->get_child();
			if (gen_relational_expression(
				num_labels_used,
				relational_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EQUALITY_EXPRESSION_2:
		case AstNodeAlt::EQUALITY_EXPRESSION_3:
		{
			const AnnotatedAstNode* const equality_expression
				= node->get_child();
			const AnnotatedAstNode* const relational_expression
				= equality_expression->get_sibling();

			x86_Asm_IR_Operand op1;

			if (gen_equality_expression(
				num_labels_used,
				equality_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_relational_expression(
				num_labels_used,
				relational_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::CMP,
				op1,
				op2);

			switch (node->get_alt()) {

				case AstNodeAlt::EQUALITY_EXPRESSION_2:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETE,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				case AstNodeAlt::EQUALITY_EXPRESSION_3:
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SETNE,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;

				default:
					break;

			}
			operand = op1;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_and_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_and_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::AND_EXPRESSION_1:
		{
			const AnnotatedAstNode* const equality_expression
				= node->get_child();
			if (gen_equality_expression(
				num_labels_used,
				equality_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::AND_EXPRESSION_2:
		{
			const AnnotatedAstNode* const and_expression
				= node->get_child();
			const AnnotatedAstNode* const equality_expression
				= and_expression->get_sibling();

			x86_Asm_IR_Operand op1;

			if (gen_and_expression(
				num_labels_used,
				and_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_equality_expression(
				num_labels_used,
				equality_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::AND,
				op1,
				op2);

			operand = op1;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_exclusive_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_exclusive_or_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_1:
		{
			const AnnotatedAstNode* const and_expression
				= node->get_child();
			if (gen_and_expression(
				num_labels_used,
				and_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXCLUSIVE_OR_EXPRESSION_2:
		{
			const AnnotatedAstNode* const exclusive_or_expression
				= node->get_child();
			const AnnotatedAstNode* const and_expression
				= exclusive_or_expression->get_sibling();

			x86_Asm_IR_Operand op1;

			if (gen_exclusive_or_expression(
				num_labels_used,
				exclusive_or_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_and_expression(
				num_labels_used,
				and_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::XOR,
				op1,
				op2);

			operand = op1;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_inclusive_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_inclusive_or_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_1:
		{
			const AnnotatedAstNode* const exclusive_or_expression
				= node->get_child();
			if (gen_exclusive_or_expression(
				num_labels_used,
				exclusive_or_expression,
				instrs,
				alloc_map,
				operand) 
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INCLUSIVE_OR_EXPRESSION_2:
		{
			const AnnotatedAstNode* const inclusive_or_expression
				= node->get_child();
			const AnnotatedAstNode* const exclusive_or_expression
				= inclusive_or_expression->get_sibling();

			x86_Asm_IR_Operand op1;
			if (gen_inclusive_or_expression(
				num_labels_used,
				inclusive_or_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;
			if (gen_exclusive_or_expression(
				num_labels_used,
				exclusive_or_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::OR,
				op1,
				op2);

			operand = op1;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}


static inline
CodeGeneratorExitCode gen_logical_and_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_logical_and_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_1:
		{
			const AnnotatedAstNode* const inclusive_or_expression
				= node->get_child();
			if (gen_inclusive_or_expression(
				num_labels_used,
				inclusive_or_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LOGICAL_AND_EXPRESSION_2:
		{
			const AnnotatedAstNode* const logical_or_expression
				= node->get_child();
			const AnnotatedAstNode* const logical_and_expression
				= logical_or_expression->get_sibling();

			x86_Asm_IR_Operand op1;
			if (gen_logical_or_expression(
				num_labels_used,
				logical_or_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;
			if (gen_logical_and_expression(
				num_labels_used,
				logical_and_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ 
				= x86_Asm_IR(
					x86_Asm_IR_Mnemonic::OR,
					op1,
					op2);

			operand = op1;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_logical_or_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_logical_or_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::LOGICAL_OR_EXPRESSION_1:
		{
			const AnnotatedAstNode* const logical_and_expression
				= node->get_child();
			if (gen_logical_and_expression(
				num_labels_used,
				logical_and_expression, 
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LOGICAL_OR_EXPRESSION_2:
		{
			const AnnotatedAstNode* const logical_or_expression
				= node->get_child();
			const AnnotatedAstNode* const logical_and_expression
				= logical_or_expression->get_sibling();

			x86_Asm_IR_Operand op1;
			if (gen_logical_or_expression(
				num_labels_used,
				logical_or_expression,
				instrs,
				alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_logical_and_expression(
				num_labels_used,
				logical_and_expression,
				instrs,
				alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::OR,
				op1,
				op2);

			operand = op1;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_conditional_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_conditional_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::CONDITIONAL_EXPRESSION_1:
		{
			const AnnotatedAstNode* const logical_or_expression
				= node->get_child();
			if (gen_logical_or_expression(
				num_labels_used,
				logical_or_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::CONDITIONAL_EXPRESSION_2:
		{
			/* 
			val = cond ? a : b 
			// translates to 
			if (cond) {
			    val = a
			} else {
			    val = b;
			}
			*/

			const AnnotatedAstNode* const logical_or_expression
				= node->get_child();
			const AnnotatedAstNode* const expression
				= logical_or_expression->get_sibling();
			const AnnotatedAstNode* const conditional_expression
				= expression->get_sibling();
			
			const char* const skip_expression_label 
				= construct_label(
					".LBB0_", 
					num_labels_used);
			const char* const evaluation_finished_label 
				= construct_label(
					".LBB0_", 
					num_labels_used);

			x86_RegisterAllocMap cond_expr
				= alloc_map;

			const Type* const conditional_expression_type
				= conditional_expression->get_type();

			const x86_RegisterType conditional_expression_register_type
				= get_register_type_from_ast_type(
					conditional_expression_type);

			const x86_RegisterName conditional_expression_register
				= allocate_register(
					cond_expr,
					conditional_expression_register_type);

			x86_Asm_IR_Operand output
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					{ conditional_expression_register });

			/* if (cond) { */
			x86_Asm_IR_Operand op1
				= x86_Asm_IR_Operand();
			if (gen_logical_or_expression(
				num_labels_used,
				logical_or_expression,
				instrs,
				cond_expr,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_OperandVal skip_expression_label_val;
			skip_expression_label_val.label 
				= { skip_expression_label };

			const x86_Asm_IR_Operand skip_expression_label_op
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::LABEL,
					skip_expression_label_val);

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::JZ,
				op1,
				skip_expression_label_op);

			x86_Asm_IR_Operand op2
				= x86_Asm_IR_Operand();
			if (gen_expression(
				num_labels_used,
				expression,
				instrs,
				cond_expr,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const expression_type
				= expression->get_type();

			construct_x86_AssemblyInstruction_move(
				conditional_expression_type,
				output,
				expression_type,
				op2,
				instrs);

			x86_Asm_IR_OperandVal evaluation_finished_label_val;
			evaluation_finished_label_val.label 
				= evaluation_finished_label;
			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::JMP,
				x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::LABEL,
					evaluation_finished_label_val));

			/* } else { */
			x86_Asm_IR_Operand op3
				= x86_Asm_IR_Operand();
			if (gen_conditional_expression(
				num_labels_used,
				conditional_expression,
				instrs,
				cond_expr,
				op3)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			construct_x86_AssemblyInstruction_move(
				conditional_expression_type,
				output,
				conditional_expression_type,
				op3,
				instrs);

			/* } */
			operand = output;
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;

	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_assignment_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_assignment_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::ASSIGNMENT_EXPRESSION_1:
		{
			const AnnotatedAstNode* const conditional_expression
				= node->get_child();
			if (gen_conditional_expression(
				num_labels_used,
				conditional_expression,
				instrs,
				alloc_map,
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

			const AnnotatedAstNode* const unary_expression 
				= node->get_child();
			const AnnotatedAstNode* const assignment_operator 
				= unary_expression->get_sibling();
			const AnnotatedAstNode* const assignment_expression 
				= assignment_operator->get_sibling();

			x86_Asm_IR_Operand op1;

			if (gen_assignment_expression(
				num_labels_used,
				assignment_expression,
				instrs,
				assignment_expression_2_alloc_map,
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;

			if (gen_unary_expression(
				num_labels_used,
				unary_expression,
				instrs,
				assignment_expression_2_alloc_map,
				op2)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			switch (assignment_operator->get_alt()) {

				case AstNodeAlt::ASSIGNMENT_OPERATOR_1:
				{
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type
						= assignment_expression->get_type();
					construct_x86_AssemblyInstruction_move(
						unary_expression_type,
						op2,
						assignment_expression_type,
						op1,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_2:
				{
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type
						= assignment_expression->get_type();
					construct_x86_AssemblyInstruction_multiply(
						assignment_expression_type,
						op1,
						unary_expression_type,
						op2,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_3:
				{
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type
						= assignment_expression->get_type();
					construct_x86_AssemblyInstruction_divide(
						assignment_expression_type,
						op1,
						unary_expression_type,
						op2,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_4:
				{
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type						
						= assignment_expression->get_type();

					x86_Asm_IR_OperandVal v;
					v.dwui = 0;
					
					construct_x86_AssemblyInstruction_move(
						assignment_expression_type,
						x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal({x86_RegisterName::RDX})),
						unary_expression_type,
						x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::DOUBLEWORD_UNSIGNED_INTEGER,
							v),
						instrs);
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::IDIV,
						op1,
						op2);
					construct_x86_AssemblyInstruction_multiply(
						assignment_expression_type,
						op1,
						assignment_expression_type,
						x86_Asm_IR_Operand(
							x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
							x86_Asm_IR_OperandVal({ x86_RegisterName::RDX })),
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_5:
				{	
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type
						= assignment_expression->get_type();

					construct_x86_AssemblyInstruction_add(
						assignment_expression_type,
						op1,
						unary_expression_type,
						op2,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_6:
				{
					const Type* const unary_expression_type
						= unary_expression->get_type();
					const Type* const assignment_expression_type
						= assignment_expression->get_type();

					construct_x86_AssemblyInstruction_subtract(
						assignment_expression_type,
						op1,
						unary_expression_type,
						op2,
						instrs);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_7:
				{
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SHL,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}
				
				case AstNodeAlt::ASSIGNMENT_OPERATOR_8:
				{	
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::SHR,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}
				
				case AstNodeAlt::ASSIGNMENT_OPERATOR_9:
				{	
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::AND,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;
				}

				case AstNodeAlt::ASSIGNMENT_OPERATOR_10:
				{	
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::XOR,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}
				
				case AstNodeAlt::ASSIGNMENT_OPERATOR_11:
				{	
					*instrs++ = x86_Asm_IR(
						x86_Asm_IR_Mnemonic::NEG,
						op1,
						op2);
					exitcode = CodeGeneratorExitCode::SUCCESS;
					break;				
				}
			
				default:
					break;
			}
			operand = op1;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_1:
		{
			const AnnotatedAstNode* const assignment_expression
				= node->get_child();
			if (gen_assignment_expression(
				num_labels_used,
				assignment_expression,
				instrs,
				alloc_map,
				operand) 
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXPRESSION_2:
		{
			const AnnotatedAstNode* const expression
				= node->get_child();
			const AnnotatedAstNode* const assignment_expression
				= expression->get_sibling();

			if (gen_expression(
				num_labels_used,
				expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			if (gen_assignment_expression(
				num_labels_used,
				assignment_expression,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_constant_expression(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_constant_expression");

	switch (node->get_alt()) {

		case AstNodeAlt::CONSTANT_EXPRESSION_1:
		{
			if (gen_conditional_expression(
				num_labels_used,
				node,
				instrs,
				alloc_map,
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

/* Declarations. */

static inline
CodeGeneratorExitCode gen_declaration(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_1:
		{
			const AnnotatedAstNode* const declaration_specifiers =
				node->get_child();
			const AnnotatedAstNode* const init_declarator_list =
				declaration_specifiers->get_sibling();
			if (init_declarator_list) {
				if (gen_init_declarator_list(
					num_labels_used,
					init_declarator_list,
					instrs,
					alloc_map)
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

static inline
CodeGeneratorExitCode gen_declaration_specifiers(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_RegisterName        const& output_register)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration_specifiers");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_SPECIFIERS_1:
		{
			const AnnotatedAstNode* const storage_class_specifier
				= node->get_child();
			const AnnotatedAstNode* const declaration_specifiers
				= storage_class_specifier->get_sibling();
			if (declaration_specifiers) {
				if (gen_declaration_specifiers(
					num_labels_used,
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
			const AnnotatedAstNode* const type_specifier
				= node->get_child();
			const AnnotatedAstNode* const declaration_specifiers
				= type_specifier->get_sibling();
			if (declaration_specifiers) {
				if (gen_declaration_specifiers(
					num_labels_used,
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
			const AnnotatedAstNode* const type_qualifier
				= node->get_child();
			const AnnotatedAstNode* const declaration_specifiers
				= type_qualifier->get_sibling();
			if (declaration_specifiers) {
				if (gen_declaration_specifiers(
					num_labels_used,
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
			const AnnotatedAstNode* const function_specifier
				= node->get_child();
			const AnnotatedAstNode* const declaration_specifiers
				= function_specifier->get_sibling();
			if (declaration_specifiers) {
				if (gen_declaration_specifiers(
					num_labels_used,
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

static inline
CodeGeneratorExitCode gen_init_declarator_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_init_declarator_list");

	switch (node->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_LIST_1:
		{
			const AnnotatedAstNode* const init_declarator
				= node->get_child();
			if (gen_init_declarator(
				num_labels_used,
				init_declarator,
				instrs,
				alloc_map)
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
				= init_declarator_list->get_sibling();
			if (gen_init_declarator_list(
				num_labels_used,
				init_declarator_list,
				instrs,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			if (gen_init_declarator(
				num_labels_used,
				init_declarator,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_init_declarator(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_init_declarator");

	switch (node->get_alt()) {

		case AstNodeAlt::INIT_DECLARATOR_1:
		{
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::INIT_DECLARATOR_2:
		{
			const AnnotatedAstNode* const declarator
				= node->get_child();
			const AnnotatedAstNode* const initializer
				= declarator->get_sibling();

			const SymbolTable* const symtab
				= declarator->get_symbol_table();
			const char* const declarator_symbol
				= declarator->get_symbol();
			const SymbolTableEntry* const symtab_entry 
				= symtab->get_entry(declarator_symbol);

			x86_Asm_IR_Operand op1;
			if (gen_initializer(
				num_labels_used,
				initializer,
				instrs,
				construct_blank_alloc_map(),
				op1)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			x86_Asm_IR_Operand op2;
			if (gen_symbol(
				symtab_entry,
				instrs,
				op2,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			const Type* const initializer_type
				= initializer->get_type();

			const Type* const symtab_entry_type
				= symtab_entry->type;

			construct_x86_AssemblyInstruction_move(
				symtab_entry_type,
				op2,
				initializer_type,
				op1,
				instrs);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_initializer(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_initializer");

	switch (node->get_alt()) {

		case AstNodeAlt::INITIALIZER_1:
		{
			const AnnotatedAstNode* const assignment_expression
				= node->get_child();
			if (gen_assignment_expression(
				num_labels_used,
				assignment_expression,
				instrs,
				alloc_map,
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
			const AnnotatedAstNode* const initializer_list
				= node->get_child();
			if (gen_initializer_list(
				num_labels_used,
				initializer_list,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_designator_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_designation");

	switch (node->get_alt()) {

		case AstNodeAlt::DESIGNATION_1:
		{
			const AnnotatedAstNode* const designator 
				= node->get_child();
			const AnnotatedAstNode* const designator_list
				= node->get_sibling();

			if (gen_designator_list(
				num_labels_used,
				designator_list,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_designation(
	int                       & num_labels_used,
	AnnotatedAstNode*    const& node,
	x86_Asm_IR*               & instrs,
	x86_RegisterAllocMap const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_designation");

	switch (node->get_alt()) {

		case AstNodeAlt::DESIGNATION_1:
		{
			const AnnotatedAstNode* const designator_list
				= node->get_sibling();

			if (gen_designator_list(
				num_labels_used,
				designator_list,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_initializer_list(
	int                          &num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_initializer_list");

	switch (node->get_alt()) {

		//case AstNodeAlt::INITIALIZER_LIST_1:
		//{
		//	AnnotatedAstNode* designation
		//		= node->get_child()->get_name() == AstNodeName::DESIGNATION
		//		  ? node->get_child()
		//		  : NULL;
		//	AnnotatedAstNode* initializer
		//		= designation
		//		  ? designation->get_sibling()
		//		  : node->get_sibling();
		//	if (designation) {
		//		x86_AssemblyInstructionOperand op1;
		//			num_labels_used,
		//			designation,
		//			instrs,
		//			alloc_map);
		//	}
		//	gen_initializer(
		//		num_labels_used,
		//		node,
		//		instrs,
		//		alloc_map, 
		//		op);
		//	*instrs++ = x86_AssemblyInstruction(
		//		x86_AssemblyInstructionMnemonic::MOVSS,
		//		op1,
		//		op2);*/
		//	//TODO;
		//	break;
		//}

		//case AstNodeAlt::INITIALIZER_LIST_2:
		//{
		//	/*	AnnotatedAstNode* initializer_list = node->get_child();
		//		gen_initializer_list(initializer_list, instrs);
		//		exitcode = CodeGeneratorExitCode::SUCCESS;*/
		//	break;
		//}

		default:
			break;

	}
	return exitcode;
}

/* Statements. */

static inline
CodeGeneratorExitCode gen_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::STATEMENT_1:
		{
			const AnnotatedAstNode* const labeled_statement
				= node->get_child();
			if (gen_labeled_statement(
				num_labels_used,
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
			const AnnotatedAstNode* const compound_statement
				= node->get_child();
			if (gen_compound_statement(
					num_labels_used,
					compound_statement,
					instrs,
				    alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_3:
		{
			const AnnotatedAstNode* const expression_statement
				= node->get_child();
			x86_Asm_IR_Operand operand
				= x86_Asm_IR_Operand();
			if (gen_expression_statement(
				num_labels_used,
				expression_statement,
				instrs,
				alloc_map,
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::STATEMENT_4:
		{
			const AnnotatedAstNode* const selection_statement
				= node->get_child();
			if (gen_selection_statement(
				num_labels_used,
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
			const AnnotatedAstNode* const iteration_statement
				= node->get_child();
			if (gen_iteration_statement(
				num_labels_used,
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
			const AnnotatedAstNode* const jump_statement
				= node->get_child();
			if (gen_jump_statement(
				num_labels_used,
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

static inline
CodeGeneratorExitCode gen_labeled_statement(
	int                          &num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_labeled_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::LABELED_STATEMENT_1:
		{
			const AnnotatedAstNode* const identifier 
				= node->get_child();
			const AnnotatedAstNode* const statement 
				= identifier->get_sibling();

			x86_Asm_IR* statement_start = instrs;
			if (gen_statement(				num_labels_used,
				node,
				instrs,
				construct_blank_alloc_map())
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			statement_start->set_type(
				x86_Asm_IR_Type::LABELED_INSTRUCTION);
			const char* const label_s 
				= construct_label("LSS_", num_labels_used);
			statement_start->set_label(
				label_s);

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::LABELED_STATEMENT_2:
		{
			const AnnotatedAstNode* const constant_expression
				= node->get_child();
			const AnnotatedAstNode* const statement
				= constant_expression->get_sibling();
			break;
		}

		case AstNodeAlt::LABELED_STATEMENT_3:
		{
			const AnnotatedAstNode* const statement
				= node->get_child();
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_compound_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_compound_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::COMPOUND_STATEMENT_1:
		{
			const AnnotatedAstNode* const block_item_list
				= node->get_child();

			if (gen_block_item_list(
				num_labels_used,
				block_item_list,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_block_item_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_block_item_list");

	switch (node->get_alt()) {

		case AstNodeAlt::BLOCK_ITEM_LIST_1:
		{
			const AnnotatedAstNode* const block_item
				= node->get_child();

			if (gen_block_item(
				num_labels_used,
				block_item,
				instrs,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}

			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::BLOCK_ITEM_LIST_2:
		{
			const AnnotatedAstNode* const block_item_list
				= node->get_child();
			const AnnotatedAstNode* const block_item
				= block_item_list->get_sibling();

			if (gen_block_item_list(
				num_labels_used,
				block_item_list,
				instrs,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			if (gen_block_item(
				num_labels_used,
				block_item,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_block_item(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_block_item");

	switch (node->get_alt()) {

		case AstNodeAlt::BLOCK_ITEM_1:
		{
			const AnnotatedAstNode* const declaration
				= node->get_child();
			if (gen_declaration(
				num_labels_used,
				declaration,
				instrs,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::BLOCK_ITEM_2:
		{
			const AnnotatedAstNode* const statement 
				= node->get_child();
			if (gen_statement(
				num_labels_used,
				statement,
				instrs,
				alloc_map)
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

static inline
CodeGeneratorExitCode gen_expression_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map,
	x86_Asm_IR_Operand           & operand)
{
	CodeGeneratorExitCode exitcode = CodeGeneratorExitCode::FAILURE;

	report_gen("gen_expression_statement");

	switch (node->get_alt()) {

		case AstNodeAlt::EXPRESSION_STATEMENT_1:
		{
			const AnnotatedAstNode* const expression
				= node->get_child();
			if (gen_expression(
				num_labels_used,
				expression,
				instrs,
				alloc_map,
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

static inline
CodeGeneratorExitCode gen_selection_statement(
	int                           & num_labels_used,
	const AnnotatedAstNode*  const& node,
	x86_Asm_IR*                   & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

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

static inline
CodeGeneratorExitCode gen_iteration_statement(
	int                           & num_labels_used,
	const AnnotatedAstNode*  const& node,
	x86_Asm_IR*                   & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

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

static inline
CodeGeneratorExitCode gen_jump_statement(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

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
			x86_Asm_IR_Operand operand;
			const AnnotatedAstNode* const expression
				= node->get_child();
			if (gen_expression(
				num_labels_used,
				expression,
				instrs,
				construct_blank_alloc_map(),
				operand)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			/* moving returned value to xmm0 */
			x86_Asm_IR_Operand o1
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					{ x86_RegisterName::XMM0 });

			const Type* const expression_type
				= expression->get_type();

			construct_x86_AssemblyInstruction_move(
				expression_type,
				o1,
				expression_type,
				operand,
				instrs);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}
	
		default:
			break;
	
	}
	return exitcode;
}

/* External definitions. */

static inline
CodeGeneratorExitCode gen_translation_unit(
	int                    & num_labels_used,
	AnnotatedAstNode* const& node,
	x86_Asm_IR*            & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_translation_unit");

	x86_RegisterAllocMap alloc_map = construct_blank_alloc_map();

	gen_literals(num_labels_used, node->get_symbol_table(), instrs);

	switch (node->get_alt()) {

		case AstNodeAlt::TRANSLATION_UNIT_1:
		{
			const AnnotatedAstNode* const external_declaration
				= node->get_child();
			if (gen_external_declaration(
					num_labels_used,
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
			const AnnotatedAstNode* const translation_unit
				= node->get_child();
			const AnnotatedAstNode* const external_declaration
				= translation_unit->get_sibling();
			if (gen_translation_unit(
				num_labels_used,
				node,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {

			}
			if (gen_external_declaration(
				num_labels_used,
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

static inline
CodeGeneratorExitCode gen_external_declaration(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_external_declaration");

	switch (node->get_alt()) {

		case AstNodeAlt::EXTERNAL_DECLARATION_1:
		{
			const AnnotatedAstNode* const function_definition
				= node->get_child();
			if (gen_function_definition(
				num_labels_used,
				function_definition,
				instrs)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::EXTERNAL_DECLARATION_2:
		{
			const AnnotatedAstNode* const declaration
				= node->get_child();
			if (gen_declaration(
				num_labels_used,
				declaration,
				instrs,
				construct_blank_alloc_map())
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

static inline
CodeGeneratorExitCode gen_function_definition(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_function_definition");

	switch (node->get_alt()) {

		case AstNodeAlt::FUNCTION_DEFINITION_1:
		{
			const AnnotatedAstNode* const declaration_specifiers
				= node->get_child();
			const AnnotatedAstNode* const declarator
				= declaration_specifiers->get_sibling();
			const AnnotatedAstNode* const declarator_sibling
				= declarator->get_sibling();
			const AnnotatedAstNode* const compound_statement
				= (declarator_sibling->get_name()
					== AstNodeName::DECLARATION_LIST)
				  ? declarator_sibling->get_sibling()
				  : declarator_sibling;

			const x86_Asm_IR_Operand rbp_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					x86_Asm_IR_OperandVal(
						{ x86_RegisterName::RBP }));

			*instrs = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::PUSHQ,
				rbp_operand);

			const char* const declarator_symbol
				= declarator->get_symbol();

			instrs->set_label(
				declarator_symbol);
			instrs->set_type(
				x86_Asm_IR_Type::LABELED_INSTRUCTION);
			instrs++;

			const x86_Asm_IR_Operand rsp_operand
				= x86_Asm_IR_Operand(
					x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
					x86_Asm_IR_OperandVal(
						{ x86_RegisterName::RSP }));
			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::MOVQ,
				rbp_operand,
				rsp_operand);

			/* for each argument */
			SymbolTable* const func_sym_tab 
				= node->get_symbol_table();

			SymbolTableEntry* arguments[1028] = { };
			func_sym_tab->get_entries(arguments);
			for (SymbolTableEntry** e = arguments;
				 *e != NULL;
				 e++) {
				x86_Asm_IR_Operand op2;

				x86_RegisterAllocMap alloc_map 
					= construct_blank_alloc_map();

				gen_symbol(
					*e, 
					instrs, 
					op2, 
					alloc_map);

				x86_Asm_IR_Operand xmm1_operand
					= x86_Asm_IR_Operand(
						x86_Asm_IR_OperandType::X86_REGISTER_INDEX,
						x86_Asm_IR_OperandVal(
							{ x86_RegisterName::XMM1 }));
				*instrs++ = x86_Asm_IR(
					x86_Asm_IR_Mnemonic::MOVSS,
					op2,
					xmm1_operand);
				// TODO; stub.
			}

			if (gen_compound_statement(
				num_labels_used,
				compound_statement,
				instrs,
				construct_blank_alloc_map())
				== CodeGeneratorExitCode::FAILURE) {
				//break;
			}
			
			/* returning from function */
			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::POPQ,
				rbp_operand);

			*instrs++ = x86_Asm_IR(
				x86_Asm_IR_Mnemonic::RETQ);
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		default:
			break;
	}
	return exitcode;
}

static inline
CodeGeneratorExitCode gen_declaration_list(
	int                          & num_labels_used,
	const AnnotatedAstNode* const& node,
	x86_Asm_IR*                  & instrs,
	x86_RegisterAllocMap    const& alloc_map)
{
	CodeGeneratorExitCode exitcode 
		= CodeGeneratorExitCode::FAILURE;

	report_gen("gen_declaration_list");

	switch (node->get_alt()) {

		case AstNodeAlt::DECLARATION_LIST_1:
		{
			const AnnotatedAstNode* const declaration
				= node->get_child();
			if (gen_declaration(
				num_labels_used,
				declaration,
				instrs,
				alloc_map)
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			exitcode = CodeGeneratorExitCode::SUCCESS;
			break;
		}

		case AstNodeAlt::DECLARATION_LIST_2:
		{
			const AnnotatedAstNode* const declaration
				= node->get_child();
			const AnnotatedAstNode* const declaration_list				
				= declaration->get_sibling();
			if (gen_declaration_list(
				num_labels_used,
				declaration_list,
				instrs,
				alloc_map) 
				== CodeGeneratorExitCode::FAILURE) {
				break;
			}
			if (gen_declaration(
				num_labels_used,
				declaration,
				instrs,
				alloc_map)
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

#endif