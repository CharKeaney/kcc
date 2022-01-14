
#ifndef TOKEN_H
#define TOKEN_H 1

#include <iostream>

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
	OPEN_SQUARE_BRACKET,
	CLOSE_SQUARE_BRACKET,
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
	ANTIQUATED_OPEN_SQUARE_BRACKET,
	ANTIQUATED_CLOSE_SQUARE_BRACKET,
	ANTIQUATED_OPEN_CURLY_BRACKET,
	ANTIQUATED_CLOSE_CURLY_BRACKET,
	ANTIQUATED_HASHTAG,
	ANTIQUATED_DOUBLE_HASHTAG
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

typedef union TokenValue {
	float floatvalue;
	int intvalue;
} TokenValue;

class Token {
private:
	TokenName name;
	TokenForm form;
	TokenValue val;
	const char* lexeme;
public:
	inline Token() {
		name = TokenName::ERROR;
		form = TokenForm::SIMPLE;
		val = { };
		lexeme = NULL;
	};

	inline Token(
		const TokenName& n,
		const TokenForm& f,
		const TokenValue& v,
		const char*& l)
		: name(n), form(f), val(v), lexeme(l) {
	}

	inline TokenName get_name() const { return name;	   }
	inline TokenForm get_form() const { return form;	   }
	inline const char* get_lexeme() const { return lexeme; }
	inline TokenValue get_val() const { return val;		   }

	inline void print() 
	{
		cout << "<Token={"
			 << lexeme
			 << ","
			 << token_name_string_reprs[(int) name]
			 << ","
			 << token_form_string_reprs[(int) form]
			 << "}>";
	}
};

#endif