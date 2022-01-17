
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
	// TODO: 
	// EACH NON-WHITE-SPACE CHARACTER THAT
	// CANNOT BE ONE OF THE ABOVE
};

enum Directives {
	IF,
	IFDEF,
	IFNDEF,
	ELIF,
	ELSE,
	ENDIF,
	INCLUDE,
	DEFINE,
	UNDEF,
	LINE,
	ERROR,
	PRAGMA
};

enum class PreprocessingTokenForm {
	/* Mark as no specific form */
	SIMPLE,
	/* HEADER_NAME */
	Q_HEADER,
	H_HEADER
};

class FileLocationDescriptor {
private:
	const char* filename;
	int line_number;
	int character_number;
public:
	inline FileLocationDescriptor()
		: filename(0),
		line_number(0),
		character_number(0) {
	}

	inline FileLocationDescriptor(
		const char* const& filen,
		const int& line,
		const int& character) :
		filename(filen),
		line_number(line),
		character_number(character) {
	}

	inline const char* get_filename() const {
		return filename;
	}

	inline int get_line() const {
		return line_number;
	}

	inline int get_character() const {
		return character_number;
	}
};

class PreprocessingToken {
private:
	const char* lexeme;
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
		form(PreprocessingTokenForm::SIMPLE) {
	};

	inline PreprocessingToken(
		const char* const& l,
		const PreprocessingTokenName  &n,
		const FileLocationDescriptor& const filedesc,
		const PreprocessingTokenForm& const f)
		: lexeme(l), 
		name(n), 
		file_descriptor(filedesc), 
		form(f) {
	};

	inline ~PreprocessingToken() {
		/* PreprocessingToken does not 'own' lexeme so no need to delete it. */
	};

	inline void print() {
		cout << "<PreprocessingToken={\""
			 << lexeme << "\"," 
			 << (int) name << "," 
			 << (int) form << "}>";
	}
};

#endif
