
#ifndef PREPROCESSING_TOKEN_H
#define PREPROCESSING_TOKEN_H 1

#include <iostream>

using namespace std;

enum class PreprocessingTokenName {
	ERROR,
	HEADER_NAME,
	IDENTIFIER,
	PP_NUMBER,
	CHARACTER_CONSTANT,
	STRING_LITERAL,
	PUNCTUATOR,
	END_OF_FILE,
	// TODO: 
	// EACH NON-WHITE-SPACE CHARACTER THAT
	// CANNOT BE ONE OF THE ABOVE
};

static const char* preprocessing_token_name_string_repr[] {
	"ERROR",
	"HEADER_NAME",
	"IDENTIFIER",
	"PP_NUMBER",
	"CHARACTER_CONSTANT",
	"STRING_LITERAL",
	"PUNCTUATOR",
	"EOF"
};

enum class PreprocessingTokenForm {
	/* Mark as no specific form */
	UNDEFINED,
	/* HEADER_NAME */	
	HEADER_NAME_1,
	HEADER_NAME_2,
	/* IDENTIFIER */
	IDENTIFIER_1,
	IDENTIFIER_2,
	IDENTIFIER_3,
	/* PP_NUMBER */
	PP_NUMBER_1,
	PP_NUMBER_2,
	PP_NUMBER_3,
	PP_NUMBER_4,
	PP_NUMBER_5,
	PP_NUMBER_6,
	PP_NUMBER_7,
	PP_NUMBER_8,
	PP_NUMBER_9,
	/* CHARACTER_CONSTANT */
	CHARACTER_CONSTANT_1,
	CHARACTER_CONSTANT_2,
	/* STRING_LITERAL */
	STRING_LITERAL_1, 
	STRING_LITERAL_2,
	/* PUNCTUATORS */
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

static const char* preprocessing_token_form_string_repr[]{
	"UNDEFINED",
	"HEADER_NAME_1",
	"HEADER_NAME_2",
	"IDENTIFIER_1",
	"IDENTIFIER_2",
	"IDENTIFIER_3",
	"PP_NUMBER_1",
	"PP_NUMBER_2",
	"PP_NUMBER_3",
	"PP_NUMBER_4",
	"PP_NUMBER_5",
	"PP_NUMBER_6",
	"PP_NUMBER_7",
	"PP_NUMBER_8",
	"PP_NUMBER_9",
	"CHARACTER_CONSTANT_1",
	"CHARACTER_CONSTANT_2",
	"STRING_LITERAL_1", 
	"STRING_LITERAL_2",
	"OPEN_BRACKET",
	"CLOSE_BRACKET",
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
	"BIGRAPH_OPEN_BRACKET",
	"BIGRAPH_CLOSE_BRACKET",
	"BIGRAPH_OPEN_CURLY_BRACKET",
	"BIGRAPH_CLOSE_CURLY_BRACKET",
	"BIGRAPH_HASHTAG",
	"BIGRAPH_DOUBLE_HASHTAG"
};

struct FileLocationDescriptor {
	const char*  filename;
	unsigned int line_number;
	unsigned int character_number;
	unsigned int lexeme_length;
};

static inline FileLocationDescriptor construct_file_location_descriptor() 
{
	FileLocationDescriptor fld = {
		NULL,
		0,
		0,
		0
	};
	return fld;
}

static inline FileLocationDescriptor construct_file_location_descriptor(
	const char* const& filen,
	int         const& line,
	int         const& character,
	int         const& lexeme_len) 
{
	FileLocationDescriptor fld = {
		filen,
		line,
		character,
		lexeme_len
	};
	return fld;
}

static inline void print_file_location_descriptor(
	FileLocationDescriptor const& fld) 
{
	cout << "<FileLocationDescriptor={"
		 << fld.filename
		 << ","
		 << fld.line_number
		 << ","
		 << fld.character_number
		 << "}>";
}

class PreprocessingToken {
private:
	const char*            lexeme;
	PreprocessingTokenName name;
	FileLocationDescriptor file_descriptor;
	PreprocessingTokenForm form;
public:
	const char* get_lexeme() const { return lexeme; }

	inline PreprocessingTokenName get_name() const {
		return name;
	}

	inline FileLocationDescriptor get_file_descriptor() const {
		return file_descriptor;
	}

	inline PreprocessingTokenForm get_form() const {
		return form;
	}

	inline PreprocessingToken()
		: lexeme(0),
		  name(PreprocessingTokenName::ERROR),
		  file_descriptor(FileLocationDescriptor()),
		  form(PreprocessingTokenForm::UNDEFINED) {
	};

	inline PreprocessingToken(
		const char*            const& l,
		PreprocessingTokenName const& n,
		FileLocationDescriptor const& filedesc,
		PreprocessingTokenForm const& f)
		: lexeme(l), 
		name(n), 
		file_descriptor(filedesc), 
		form(f) {
	};

	inline ~PreprocessingToken() {
		/* PreprocessingToken does not 'own' lexeme 
		   so no need to delete it. */
	};

	inline void print() {
		cout << "<PreprocessingToken={\""
			 << lexeme << "\"," 
			 << preprocessing_token_name_string_repr[(int) name] << "," 
			 << preprocessing_token_form_string_repr[(int) form] << "}>";
	}
};

#define PPT_TABLE_ENTRY_LEXEME_WIDTH 32
#define PPT_TABLE_ENTRY_NAME_WIDTH   13
#define PPT_TABLE_ENTRY_FORM_WIDTH   20
#define PPT_TABLE_ENTRY_FILE_WIDTH   13
#define PPT_TABLE_ENTRY_LINE_WIDTH   6
#define PPT_TABLE_ENTRY_CHAR_WIDTH   6
#define PPT_TABLE_ENTRY_LEN_WIDTH    6

#include <iomanip>

static inline void print_preprocessing_token_table_entry(
	const PreprocessingToken* const& ppt) 
{
	const int name_i         
		= (int) ppt->get_name();
	const int form_i         
		= (int) ppt->get_form(); 
	const char* const name_s
		= preprocessing_token_name_string_repr[name_i];
	const char* const form_s 
		= preprocessing_token_form_string_repr[form_i];
	const FileLocationDescriptor fld 
		= ppt->get_file_descriptor();
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LEXEME_WIDTH)
         << std::setfill(' ')
		 << ppt->get_lexeme() ;
	cout << std::left
         << std::setw(PPT_TABLE_ENTRY_NAME_WIDTH)
		 << std::setfill(' ')
		 << name_s;
	cout << std::left
		<< std::setw(PPT_TABLE_ENTRY_FORM_WIDTH)
		<< std::setfill(' ')
		<< form_s;
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_FILE_WIDTH)
		 << std::setfill(' ')
		 << fld.filename;
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LINE_WIDTH)
		 << std::setfill(' ')
		 << fld.line_number;
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_CHAR_WIDTH)
		 << std::setfill(' ')
		 << fld.character_number;
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LEN_WIDTH)
		 << std::setfill(' ')
		 << fld.lexeme_length
		 << endl;
}

static inline void print_preprocessing_token_table(
	const PreprocessingToken* const& ppts,
	int						  const& count) 
{	
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LEXEME_WIDTH) 
         << std::setfill(' ')
		 << "Lexeme" ;
	cout  << std::left
		 << std::setw(PPT_TABLE_ENTRY_NAME_WIDTH)   
		 << std::setfill(' ')
		 << "Name";
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_FORM_WIDTH)  
		 << std::setfill(' ')
		 << "Form";
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_FILE_WIDTH)   
		 << std::setfill(' ')
		 << "File";
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LINE_WIDTH)   
		 << std::setfill(' ') 
		 << "Line";
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_CHAR_WIDTH)
		 << std::setfill(' ')
		 << "Char";
	cout << std::left
		 << std::setw(PPT_TABLE_ENTRY_LEN_WIDTH)
		 << std::setfill(' ')
		 << "Len"
		 << endl;
	for (const PreprocessingToken* p = ppts; 
		 p < ppts + count; 
		 p++) {
		print_preprocessing_token_table_entry(p);
	}
}
#endif
