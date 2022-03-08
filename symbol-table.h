#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H 1

#include <string>

#include <iostream>
#include <iomanip>

#include "semantics.h"

#define DEBUG_TYPE_SHOW_NULL_DUPLICATION 0

using namespace std;

struct SymbolTableEntry {
	/*     Key data.          */
	const char*          symbol;
	SymbolTableEntry*    next_entry;
	/*   General Attributes.           */
	IdentifierClassifier identifier_type;
	bool                 is_literal;
	int                  value;
	int                  base_pointer_offset;
	const Type*          type;
	int                  number_formal_parameters;
	SymbolTableEntry*    function_ptr;
	int                  function_frame_size;
	Scope                scope;		
	/* Attributes added during code generation.*/
	const char*          literal_constant_ptr_label;
};

static inline SymbolTableEntry construct_symbol_table_entry(
	const char* const& symbol)
{
	SymbolTableEntry result = {
		symbol,
		NULL,
		IdentifierClassifier::UNDEFINED,
		0,
		0,
		false,
		NULL,
		0,
		0,
		NULL 
	};
	return result;
}

#define ST_PRINT_SYMBOL_WIDTH
#define ST_PRINT_IDENTIFIER_TYPE_WIDTH
#define ST_PRINT_IS_LITERAL_WIDTH
#define ST_PRINT_IS_VALUE
#define ST_PRINT_IS_OFFSET
#define ST_PRINT_FUNCTION_PTR
#define ST_PRINT_NUM_PARAMS
#define ST_PRINT_SCOPE_TYPE
#define ST_PRINT_FRAME_SIZE
#define ST_PRINT_TYPE

static inline void print_symbol_table_entry_header()
{
	cout << ": symbol       "
		 << ": identifier type "
		 << ": is literal? "
		 << ": value      "
		 << ": offset     "
		 << ": function ptr "
		 << ": num_params "		
		 << ": scope type "
		 << ": frame size "
		 << ": type         ";
}

static inline void print_symbol_table_entry_content(
	const SymbolTableEntry* const& entry)
{
	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << entry->symbol;

	cout << ": "
		 << std::left
		 << std::setw(16)
		 << std::setfill(' ')
		 << identifier_classifier_string_repr[(int)entry->identifier_type];

	cout << ": "
		 << std::left
		 << std::setw(12)
		 << std::setfill(' ')
		 << (entry->is_literal 
			? "true" 
			: "false");

	cout << ": 0x"
		 << std::right
		 << std::hex
		 << std::setw(8)
		 << std::setfill('0')
		 << entry->value
		 << " ";

	cout << ": 0x"
		 << std::right
		 << std::hex
		 << std::setw(8)
		 << std::setfill('0')
		 << entry->base_pointer_offset
		 << " ";

	const char* id = entry->function_ptr 
					 ? entry->function_ptr->symbol 
					 : "N/A";
	cout << ": "
		 << std::left
		 << std::setw(13)
		 << std::setfill(' ')
		 << id;

	cout << ": "
		 << std::left
		 << std::setw(11)
		 << std::setfill(' ')
		 << entry->number_formal_parameters;

	cout << ": "
		 << std::left
		 << std::setw(11)
		 << std::setfill(' ')
		 << scope_string_repr[(int)entry->scope];

	cout << ": "
		 << std::left
		 << std::setw(11)
		 << std::setfill(' ')
		 << entry->function_frame_size;

	cout << ": ";
	if (entry->type != NULL) {
		print_type(entry->type);
	} else {
		cout << "N/A";
	}
}
#define NUM_SYMBOL_TABLE_ENTRIES 6151

class SymbolTable {
private:
	SymbolTableEntry* entries[NUM_SYMBOL_TABLE_ENTRIES] = { };

	unsigned int hash(const char* const& x) const
	{
		long long string_val = 0;
		for (const char* c = x; *c; c++) {
			string_val += 256 * *c;
		}
		const unsigned int h = (string_val * 12289) % 6151;
		return h;
	}

public:
	inline SymbolTable() { }

	~SymbolTable() {
		delete[] entries;
	}

	inline SymbolTableEntry* get_entry(
		const char* const& symbol) const
	{
		const unsigned int h 
			= hash(symbol);
		SymbolTableEntry* entry 
			= *(entries + h);
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

	inline void get_entries(
		SymbolTableEntry** returned_entries) const
	{
		for (SymbolTableEntry *const * e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			for (SymbolTableEntry * f = *e;
				f != NULL;
				f = f->next_entry) {

				*returned_entries++ = f;
			}
		}
		return;
	}

	inline void add_entry(
		const char* const& symbol) 
	{
		SymbolTableEntry* data = new SymbolTableEntry(
			construct_symbol_table_entry(symbol));

		unsigned int h = hash(symbol);
		SymbolTableEntry** entry_addr 
			= entries + h;
		if (*entry_addr != NULL) {
			SymbolTableEntry* old_entry = *entry_addr;
			*entry_addr = data;
			(*entry_addr)->next_entry = old_entry;
		} else {
			*entry_addr = data;
		}
	}

	inline void print(
		string const& prefix = "") const
	{
		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;

		cout << prefix;
		print_symbol_table_entry_header();
		cout << endl;

		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;

		for (const SymbolTableEntry *const * e = entries;
			e < entries + NUM_SYMBOL_TABLE_ENTRIES;
			e++) {

			for (const SymbolTableEntry* f = *e;
				f != NULL;
				f = f->next_entry) {

				cout << prefix;
				print_symbol_table_entry_content(f);
				cout << endl;
			}		
		}

		cout << prefix;
		for (int i = 0; i < 16 * 9; i++) {
			cout << "-";
		}
		cout << endl;
	}
};

#endif