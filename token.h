
#ifndef TOKEN_H
#define TOKEN_H 1

#include <iostream>
#include "preprocessing-token.h"

using namespace std;

enum class TokenName {
	KEYWORD = 0,
	IDENTIFIER,
	CONSTANT,
	STRING_LITERAL,
	PUNCTUATOR,
	ERROR
};
#define NUM_TOKEN_NAMES 6

static const char* token_name_string_reprs[] {
	"KEYWORD",
	"IDENTIFIER",
	"CONSTANT",
	"STRING_LITERAL",
	"PUNCTUATOR",
	"ERROR"
};
#define token_name_string(p) \
		token_name_string_reprs[(int) p]


enum class TokenForm {
	/* Mark as no specific form */
	SIMPLE = 0,
	/* KEYWORD */
	AUTO,
	BREAK,
	CASE,
	CHAR,
	CONST,
	CONTINUE,
	DEFAULT,
	DO,
	DOUBLE,
	ELSE,
	ENUM,
	EXTERN,
	FLOAT,
	FOR,
	GOTO,
	IF,
	INLINE,
	INT,
	LONG,
	REGISTER,
	RESTRICT,
	RETURN,
	SHORT,
	SIGNED,
	SIZEOF,
	STATIC,
	STRUCT,
	SWITCH,
	TYPEDEF,
	UNION,
	UNSIGNED,
	WHILE,
	VOID,
	VOLATILE,
	_BOOL,
	_COMPLEX,
	_IMAGINARY,
	/* IDENTIFIER */
	/* CONSTANT */
	INTEGER_CONSTANT,
	FLOATING_CONSTANT,
	ENUMERATION_CONSTANT,
	CHARACTER_CONSTANT,
	STRING_LITERAL,
	/* PUNCTUATOR */
	OPEN_BRACKET,
	CLOSE_BRACKET,
	OPEN_PAREN,
	CLOSE_PAREN,
	OPEN_CURLY_BRACKET,
	CLOSE_CURLY_BRACKET,
	DOT,
	AMPERSAND,
	ASTERIX,
	PLUS,
	MINUS,
	TILDE,
	EXCLAMATION_MARK,
	FORWARD_SLASH,
	MODULO,
	INCREMENT,
	DECREMENT,
	RIGHT_ARROW,
	LEFT_SHIFT,
	LESS_THAN,
	GREATER_THAN,
	LESS_THAN_EQUAL,
	GREATER_THAN_EQUAL,

	EQUAL,
	NOT_EQUAL,
	XOR,
	OR,
	DOUBLE_AMPERSAND,
	DOUBLE_OR,
	QUESTION_MARK,
	COLON, SEMI_COLON,
	TRIPLE_DOT,
	ASSIGN,
	MULTIPLY_EQUAL,
	DIVIDE_EQUALS,
	MODULO_EQUALS,
	PLUS_EQUALS,
	MINUS_EQUALS,
	LEFT_SHIFT_EQUALS,
	RIGHT_SHIFT,
	RIGHT_SHIFT_EQUALS,
	AMPERSAND_EQUAL,
	XOR_EQUAL,
	OR_EQUAL,
	COMMA,
	HASHTAG,
	DOUBLE_HASHTAG,
	BIGRAPH_OPEN_BRACKET,
	BIGRAPH_CLOSE_BRACKET,
	BIGRAPH_OPEN_CURLY_BRACKET,
	BIGRAPH_CLOSE_CURLY_BRACKET,
	BIGRAPH_HASHTAG,
	BIGRAPH_DOUBLE_HASHTAG
};
#define NUM_TOKEN_FORMS 97

static const char* token_form_string_reprs[] {
	"SIMPLE",
	"AUTO",
	"BREAK",
	"CASE",
	"CHAR",
	"CONST",
	"CONTINUE",
	"DEFAULT",
	"DO",
	"DOUBLE",
	"ELSE",
	"ENUM",
	"EXTERN",
	"FLOAT",
	"FOR",
	"GOTO",
	"IF",
	"INLINE",
	"INT",
	"LONG",
	"REGISTER",
	"RESTRICT",
	"RETURN",
	"SHORT",
	"SIGNED",
	"SIZEOF",
	"STATIC",
	"STRUCT",
	"SWITCH",
	"TYPEDEF",
	"UNION",
	"UNSIGNED",
	"WHILE",
	"VOID",
	"VOLATILE",
	"_BOOL",
	"_COMPLEX",
	"_IMAGINARY",
	"INTEGER_CONSTANT",
	"FLOATING_CONSTANT",
	"ENUMERATION_CONSTANT",
	"CHARACTER_CONSTANT",
	"STRING_LITERAL",
	"OPEN_SQUARE_BRACKET",
	"CLOSE_SQUARE_BRACKET",
	"OPEN_PAREN",
	"CLOSE_PAREN",
	"OPEN_CURLY_BRACKET",
	"CLOSE_CURLY_BRACKET",
	"DOT",
	"AMPERSAND",
	"ASTERIX",
	"PLUS",
	"MINUS",
	"TILDE",
	"EXCLAMATION_MARK",
	"FORWARD_SLASH",
	"MODULO",
	"INCREMENT",
	"DECREMENT",
	"RIGHT_ARROW",
	"LEFT_SHIFT",
	"LESS_THAN",
	"GREATER_THAN",
	"LESS_THAN_EQUAL",
	"GREATER_THAN_EQUAL",
	"EQUAL",
	"NOT_EQUAL",
	"XOR",
	"OR",
	"DOUBLE_AMPERSAND",
	"DOUBLE_OR",
	"QUESTION_MARK",
	"COLON", 
	"SEMI_COLON",
	"TRIPLE_DOT",
	"ASSIGN",
	"MULTIPLY_EQUAL",
	"DIVIDE_EQUALS",
	"MODULO_EQUALS",
	"PLUS_EQUALS",
	"MINUS_EQUALS",
	"LEFT_SHIFT_EQUALS",
	"RIGHT_SHIFT",
	"RIGHT_SHIFT_EQUALS",
	"AMPERSAND_EQUAL",
	"XOR_EQUAL",
	"OR_EQUAL",
	"COMMA",
	"HASHTAG",
	"DOUBLE_HASHTAG",
	"ANTIQUATED_OPEN_SQUARE_BRACKET",
	"ANTIQUATED_CLOSE_SQUARE_BRACKET",
	"ANTIQUATED_OPEN_CURLY_BRACKET",
	"ANTIQUATED_CLOSE_CURLY_BRACKET",
	"ANTIQUATED_HASHTAG",
	"ANTIQUATED_DOUBLE_HASHTAG"
};
#define token_form_string(p) \
		token_form_string_reprs[(int) p]

typedef union TokenValue {
	float floatvalue;
	int   intvalue;
} TokenValue;

class Token {
private:
	TokenName              name;
	TokenForm              form;
	TokenValue             val;
	const char*            lexeme;
	FileLocationDescriptor file_descriptor;
	
public:
	inline Token() {
		name = TokenName::ERROR;
		form = TokenForm::SIMPLE;
		val = { };
		lexeme = NULL;
	};

	inline Token(
		TokenName              const& n,
		TokenForm              const& f,
		TokenValue             const& v,
		const char*            const& l,
		FileLocationDescriptor const& fld)
		: name(n), 
		  form(f), 
		  val(v), 
		  lexeme(l),
		  file_descriptor(fld) {
	}

	inline TokenName get_name() const {    
		return name;  
	}

	inline TokenForm get_form() const {     
		return form;  
	}

	inline const char* get_lexeme() const {
		return lexeme; 
	}

	inline TokenValue get_constant_val() const {    
		return val;	   
	}

	inline FileLocationDescriptor get_file_descriptor() const {
		return file_descriptor;
	}

	inline void print() const
	{
		const char* name_str
			= token_name_string(name);
		const char* form_str
			= token_form_string(form);
		cout << "<Token={"
			 << lexeme
			 << ","
			 << name_str
			 << ","
			 << form_str
			 << "}>";
	}
};

#endif