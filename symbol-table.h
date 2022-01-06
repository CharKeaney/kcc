#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <string>

#include <iostream>
#include <iomanip>

using namespace std;

static int sizeof_map[] = {
	0,
	sizeof(char),
	sizeof(signed char),
	sizeof(unsigned char),
	sizeof(short),
	sizeof(unsigned short),
	sizeof(signed int),
	sizeof(unsigned int),
	sizeof(signed long),
	sizeof(unsigned long),
	sizeof(signed long long),
	sizeof(unsigned long long),
	sizeof(float),
	sizeof(double),
	sizeof(long double),
	sizeof(bool),
	sizeof(_complex)
};
#define size_of(i) size_of[i]

enum class BasicType {
	UNDEFINED = 0,
	VOID,
	CHAR,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SHORT,
	SIGNED_SHORT,
	UNSIGNED_SHORT,
	SIGNED_INT,
	UNSIGNED_INT,
	SIGNED_LONG,
	UNSIGNED_LONG,
	SIGNED_LONG_LONG,
	UNSIGNED_LONG_LONG,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	BOOL,
	COMPLEX,
};

static const char* basic_type_string_repr[] {
	"UNDEFINED",
	"VOID",
	"CHAR",
	"SIGNED_CHAR",
	"UNSIGNED_CHAR",
	"SHORT",
	"SIGNED_SHORT",
	"UNSIGNED_SHORT",
	"SIGNED_INT",
	"UNSIGNED_INT",
	"SIGNED_LONG",
	"UNSIGNED_LONG",
	"SIGNED_LONG_LONG",
	"UNSIGNED_LONG_LONG",
	"FLOAT",
	"DOUBLE",
	"LONG_DOUBLE",
	"BOOL",
	"COMPLEX",
};

enum class DerivedType {
	UNDEFINED = 0,
	ARRAY,
	STRUCTURE,
	UNION,
	FUNCTION,
	POINTER
};

static const char* derived_type_string_repr[] {
	"UNDEFINED",
	"ARRAY",
	"STRUCTURE",
	"UNION",
	"FUNCTION",
	"POINTER"
};

enum class DerivedOrBasic {
	DERIVED,
	BASIC
};

struct Type {
	DerivedOrBasic derived_or_basic;
	union {
		struct {
			DerivedType derived_type_name; 
			Type* t; 
		};	
		BasicType basic;
	};
};

inline void print_type(Type* t) 
{
	if (t == NULL) {
		cout << "";
	} else if (t->derived_or_basic == DerivedOrBasic::BASIC) {
		cout << basic_type_string_repr[(int)t->basic];
	} else {
		cout << derived_type_string_repr[(int)t->derived_type_name]
			 << " ";
		print_type(t->t);
	}
}

struct SymbolTableEntry {
	/* Key data */
	const char* symbol;
	SymbolTableEntry* next_entry;
	/* General Attributes */
	bool is_typedef;
	int address;
	int base_pointer_offset;
	Type *type;
	int number_formal_parameters;
	bool is_recursive;
};

inline SymbolTableEntry construct_symbol_table_entry(
	const char* symbol)
{
	SymbolTableEntry result = {
		symbol,
		NULL,
		0,
		0,
		false,
		NULL,
		0,
		0,
	};
	return result;
}

#define NUM_SYMBOL_TABLE_ENTRIES 6151

class SymbolTable {
private:
	SymbolTableEntry* entries[NUM_SYMBOL_TABLE_ENTRIES];

	unsigned int hash(const char* x) 
	{
		long long string_val = 0;
		for (const char* c = x; *c; c++) {
			string_val += 256 * *c;
		}
		unsigned int h = (string_val * 12289) % 6151;
		return h;
	}

public:
	inline SymbolTable() {
		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {
			*e = NULL;
		}
	}

	~SymbolTable() {
		delete[] entries;
	}

	inline SymbolTableEntry* get_entry(const char *symbol) 
	{
		unsigned int h = hash(symbol);
		SymbolTableEntry* entry = *(entries + h);
		if (entry != NULL) {
			while (entry != NULL) {
				if (strcmp(entry->symbol, symbol) != 0) {
					entry = entry->next_entry;
				} else {
					break;
				}
			}
		}
		return entry;
	}

	inline void get_entries(SymbolTableEntry** returned_entries) 
	{
		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			for (SymbolTableEntry* f = *e;
				f != NULL;
				f = f->next_entry) {

				*returned_entries++ = f;
			}
		}
		return;
	}

	inline void add_entry(
		const char* symbol) 
	{
		SymbolTableEntry* data = new SymbolTableEntry(
			construct_symbol_table_entry(symbol)
		);

		unsigned int h = hash(symbol);
		SymbolTableEntry** entry_addr = entries + h;
		if (*entry_addr != NULL) {
			SymbolTableEntry* old_entry = *entry_addr;
			*entry_addr = data;
			(*entry_addr)->next_entry = old_entry;
		} else {
			*entry_addr = data;
		}
	}

	inline void print(string prefix = "") 
	{
		cout << prefix;
		for (int i = 0; i < 16 * 7; i++) {
			cout << "-";
		}
		cout << endl;

		cout << prefix;
		cout <<": symbol       " 
			<< ": is_typedef   "
			<< ": address      "
			<< ": offset       " 
			<< ": num_params   " 
			<< ": recurses     " 
			<< ": type         " << endl;

		cout << prefix;
		for (int i = 0; i < 16 * 7; i++) {
			cout << "-";
		}
		cout << endl;

		for (SymbolTableEntry** e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			

			for (SymbolTableEntry* f = *e;
				f != NULL;
				f = f->next_entry) {

				cout << prefix;

				cout << ": "
					 << std::left
					 << std::setw(13)
					 << std::setfill(' ')
					 << f->symbol;

				cout << ": "
					<< std::left
					<< std::setw(13)
					<< std::setfill(' ')
					 << f->is_typedef;

				cout << ": "
					<< std::left
					<< std::setw(13)
					<< std::setfill(' ')
					 << f->address;

				cout << ": 0x"
					<< std::right
					<< std::hex
					<< std::setw(8)
					<< std::setfill('0')
					<< f->base_pointer_offset
					<< "   ";

				cout << ": "
					<< std::left
					<< std::setw(13)
					<< std::setfill(' ')
					 << f->number_formal_parameters;

				cout << ": "
					<< std::left
					<< std::setw(13)
					<< std::setfill(' ')
					 << f->is_recursive;

				cout << ": ";
				print_type(f->type);
				cout << endl;
			}		
		}

		cout << prefix;
		for (int i = 0; i < 16 * 7; i++) {
			cout << "-";
		}
		cout << endl;
	}
};

#endif