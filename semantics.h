
#ifndef ANNOTATED_AST_NODE
#define ANNOTATED_AST_NODE 1

#include "ast-node.h"
#include "symbol-table.h"

class AnnotatedAstNode {
private:
	const AstNode* ast_node;	
	AnnotatedAstNode* parent;
	AnnotatedAstNode* child;
	AnnotatedAstNode* sibling;
	SymbolTable* symbol_table;
	Type* type;
	const char* symbol;
public:
	inline AnnotatedAstNode(
		AstNode* n)
		: ast_node(n),
		symbol_table(NULL),
		child(NULL),
		sibling(NULL) {
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
		return symbol;
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

	inline void set_parent(AnnotatedAstNode* p)
	{
		parent = p;
	};

	inline void set_symbol_table(SymbolTable* st)
	{
		symbol_table = st;
	}

	inline void set_symbol(const char* s)
	{
		symbol = s;
	}

	inline SymbolTable* get_symbol_table(const char* symbol = NULL) const
	{
		SymbolTable* symtab = NULL;
		if (symbol_table != NULL) {
			symtab = symbol_table;
			if (symbol != NULL
				&& symtab->get_entry(symbol) == NULL) {
				symtab = parent->get_symbol_table(symbol);
			}
		} else if (parent != NULL) {
			symtab = parent->get_symbol_table(symbol);
		}
		return symtab;
	}

	inline Token* get_terminal() const
	{
		return ast_node->get_terminal();
	}

	inline void set_type(Type* const& t) {
		type = t;
	}

	inline Type* get_type() const {
		return type;
	}

	inline void add_child(AnnotatedAstNode* node)
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

	inline void add_children(AnnotatedAstNode** nodes, int count)
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
		string parent_prefix = "",
		string child_prefix = "") 
	{
		cout << parent_prefix
			 << "name="
			 << ast_form_string_reprs[(int)ast_node->get_name()]
			 << ",alt="
			 << ast_node_alt_string_reprs[(int)ast_node->get_alt()]
			 << endl;

		if (symbol_table) {
			symbol_table->print(child_prefix);
		}
		
		AnnotatedAstNode* node = child;
		for (; node; node = node->sibling) {
			if (node->sibling) {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "|    ";
				node->print(appended_p, appended_c);
			}
			else {
				string appended_p = child_prefix + "|____";
				string appended_c = child_prefix + "     ";
				node->print(appended_p, appended_c);
			}
		}
	}
};

#endif