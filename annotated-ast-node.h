
#ifndef ANNOTATED_AST_NODE_H
#define ANNOTATED_AST_NODE_H 1

#include "semantics.h"
#include "symbol-table.h"
#include "ast-node.h"

struct Annotations {
	SymbolTable* symbol_table;
	const Type*  type;
	const char*  symbol;
	bool         constant_evaluation;
	uint64_t     constant_val;
};

class AnnotatedAstNode {
private:
	const AstNode*    ast_node;
	AnnotatedAstNode* parent;
	AnnotatedAstNode* child;
	AnnotatedAstNode* sibling;
	Annotations		  annotations;
public:
	inline AnnotatedAstNode(
		const AstNode* const& n)
		: ast_node(n),
		  parent(NULL),
		  child(NULL),
		  sibling(NULL),
		  annotations({ 0, 0, 0, 0, 0 }) {
	};

	inline ~AnnotatedAstNode() {
		AnnotatedAstNode* current_node = child;
		while (current_node != NULL) {
			/* Delete next */
			AnnotatedAstNode* next_node
				= current_node->get_sibling();
			delete current_node;
			current_node = next_node;
		}
	}

	inline const char* get_symbol() const
	{
		return annotations.symbol;
	};

	inline uint64_t get_constant_val() const
	{
		return annotations.constant_val;
	};

	inline AstNodeName get_name() const
	{
		return ast_node->get_name();
	};

	inline AstNodeAlt get_alt() const
	{
		return ast_node->get_alt();
	};

	inline AnnotatedAstNode* get_child() const
	{
		return child;
	};

	inline AnnotatedAstNode* get_sibling() const
	{
		return sibling;
	};

	inline AnnotatedAstNode* get_parent() {
		return parent;
	}

	inline void set_parent(
		AnnotatedAstNode* const& p)
	{
		parent = p;
	};

	inline void set_symbol_table(
		SymbolTable* const& st)
	{
		annotations.symbol_table = st;
	}

	inline void set_symbol(
		const char* s)
	{
		annotations.symbol = s;
	}

	inline void set_constant_val(
		uint64_t v)
	{
		annotations.constant_val = v;
	}

	inline SymbolTable* get_symbol_table(
		const char* const& symbol = NULL) const
	{
		SymbolTable* symtab = NULL;
		if (annotations.symbol_table != NULL) {
			symtab = annotations.symbol_table;
			if (symbol != NULL
				&& symtab->get_entry(symbol) == NULL) {
				symtab = parent->get_symbol_table(symbol);
			}
		} else if (parent != NULL) {
			symtab = parent->get_symbol_table(symbol);
		}
		return symtab;
	}

	inline const Token* get_terminal() const
	{
		return ast_node->get_terminal();
	}

	inline void set_type(
		const Type* const& t) 
	{
		annotations.type = t;
	}

	inline const Type* get_type() const {
		return annotations.type;
	}

	inline void add_child(
		AnnotatedAstNode* const& node)
	{
		if (child == NULL) {
			child = node;
		} else {
			AnnotatedAstNode* current = child;
			while (current->sibling != NULL) {
				current = current->sibling;
			}
			current->sibling = node;
		}
		node->set_parent(this);
	}

	inline void add_children(
		AnnotatedAstNode** const& nodes,
		int                const& count)
	{
		for (AnnotatedAstNode** n = nodes;
			 n < nodes + count;
			 n++) {
			add_child(*n);
			(*n)->set_parent(this);
		}
		/*print();*/
	}

	inline void print(
	    string const& parent_prefix = "",
		string const& child_prefix  = "")
	{
		const int name_i         = (int) ast_node->get_name();
		const int alt_i          = (int) ast_node->get_alt();
		const char* const name_s = ast_form_string_reprs[name_i];
		const char* const alt_s  = ast_node_alt_string_reprs[alt_i];

 		cout << parent_prefix
			 << "name="
		 	 << name_s
			 << ",alt="
			 << alt_s
		     << ",val="
			 << get_constant_val();
		if (annotations.type != NULL) {
			cout << ",type=";
			print_type(annotations.type);
		}
		cout << endl;

		if (annotations.symbol_table) {
			annotations.symbol_table->print(child_prefix);
		}

		AnnotatedAstNode* node = child;
		for (; node; node = node->sibling) {
			if (node->sibling) {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "|    ";
				node->print(appended_p, appended_c);
			} else {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "     ";
				node->print(appended_p, appended_c);
			}
		}
	}
};

#endif