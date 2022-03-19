/* Authored by Charlie Keaney                */
/* error.h - Responsible for defining error
			 codes.                          */

#ifndef ERROR_H
#define ERROR_H

#include <cstddef>

#include "preprocessing-token.h"

#define ERR_COLOUR_START    "\x1B[31m"
#define ERR_COLOUR_FINISHED "\033[0m"

#define WARN_COLOUR_START    "\x1B[32m"
#define WARN_COLOUR_FINISHED "\033[0m"

#define MSG_COLOUR_START    "\x1B[33m"
#define MSG_COLOUR_FINISHED "\033[0m"

/*****************************************************//**
*                      Declarations                      *
/********************************************************/

/* Error messages consist of format : err-solutions */
static
const char* err_messages[] = {
	"Could not recognise this token (). Did you mispell it?"
	"Could not recognise this identifier ()."
	"Did you forget to declare it or mispell it?",
	"Expected a semicolon here. Did you forget to put it in?",
};

enum class ErrorCode {
	UNDEFINED,
	ERR_UNRECOGNISED_IDENTIFIER,
	ERR_MISSING_SEMICOLON,
	/* Preprocessor Errors */
	ERR_PP_INVALID_HEADER,
	ERR_PP_INVALID_IDENTIFIER,
	ERR_PP_INVALID_PP_NUMBER,
	ERR_PP_INVALID_PUNCTUATOR,
	ERR_PP_INVALID_CONSTANT,
	ERR_PP_INVALID_STRING_LITERAL,
	/* Lexer Errors. */
	ERR_INVALID_CONSTANT,
	ERR_INVALID_IDENTIFIER,
	ERR_INVALID_STRING_LITERAL,
	ERR_INVALID_PUNCTUATOR,
	/* Parser Errors. */
	ERR_PARSER_INVALID_TRANSLATION_UNIT,
};

struct Error {
	ErrorCode              error_code;
	const char*            error_message;
	FileLocationDescriptor fld;
	Error*                 next_error;
};

enum class WarningCode {
	UNDEFINED
};

struct Warning {
	WarningCode            warning_code;
	const char*            warning_message;
	FileLocationDescriptor fld;
	Warning*               next_warning;
};

enum class MessageCode {
	UNDEFINED
};

struct Message {
	MessageCode            message_code;
	const char*            message;
	FileLocationDescriptor fld;
	Message*               next_message;
};

Error* construct_error_book(
	ErrorCode              const& error_code,
	const char*            const& error_message,
	FileLocationDescriptor const& fld);

static inline
const char* construct_invalid_constant_error_message(
	const char* const& error_lexeme);

static inline
void display_pointer_to_input_position(
	FileLocationDescriptor const& fld,
	const char*            const& input);

static inline
void print_error_book(
	Error*      const& error_book,
	const char* const& input);

static inline
void print_warning_book(
	Warning*    const& warning_book,
	const char* const& input);

static inline
void print_message_book(
	Message*    const& message_book,
	const char* const& input);

class AlertList {
private:
	Error* error;
	Warning* warning;
	Message* message;
public:
	inline void add_error(
		Error* const& new_error)
	{
		if (error == NULL) {
			error = new_error;
		}
		else {
			Error* last_error = error;
			while (last_error->next_error != NULL) {
				last_error = last_error->next_error;
			}
			last_error->next_error = new_error;
		}
	}

	/* The messages reference the input, so we will need the input to be passed in too.*/
	inline void print(const char* input)
	{
		print_error_book(error, input);
		print_warning_book(warning, input);
		print_message_book(message, input);
	}
};

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

Error* construct_error_book(
	ErrorCode              const& error_code,
	const char*            const& error_message,
	FileLocationDescriptor const& fld)
{
	Error* error
		= new Error({
			error_code,
			error_message,
			fld,
			NULL
			});
	return error;
}

static inline
const char* construct_invalid_constant_error_message(
	const char* const& error_lexeme)
{
	return NULL;
}

static inline
void display_pointer_to_input_position(
	FileLocationDescriptor const& fld,
	const char*            const& input)
{
	int r = 0;
	int c = 0;
	const char* input_ptr = input;
	/* Move pointer to start of error line. */
	while (r < fld.line_number) {
		while (*input_ptr++ != '\n') { }
		r++;
	}
	/* Print error line. */
	while (*input_ptr != '\n') {
		cout << *input_ptr++;
	}
	cout << *input_ptr++;
	cout << ERR_COLOUR_START;
	/* Now print space before pointer. */
	for (int i = 0; 
		 i < fld.character_number; 
		 i++) {
		cout << " ";
	}
	/* Now print pointer with tail. */
	cout << "^";
	for (int i = 0; 
			i < fld.lexeme_length - 1; 
			i++) {
		cout << "~";
	}
	cout << ERR_COLOUR_FINISHED
		 << endl;
}

static inline
void print_error_book(
	Error*      const& error_book,
	const char* const& input)
{
	Error* e = error_book;
	while (e != NULL) {
		/* Print out the message. */
		cout << ERR_COLOUR_START
			 << "kcc"                        << ":"
			 << "error"                      << ":"
			 << "err" << (int) e->error_code << ":"
			 << e->fld.filename              << ":"
			 << e->fld.line_number           << ":"
			 << e->fld.character_number      << ":"
			 << e->error_message
			 << ERR_COLOUR_FINISHED
			 << endl;
		/* Show where the input went wrong. */
		display_pointer_to_input_position(e->fld, input);
		/* Move onto next error. */
		e = e->next_error;
	}
}

static inline
void print_warning_book(
	Warning*    const& warning_book,
	const char* const& input)
{
	Warning* e = warning_book;
	while (e != NULL) {
		/* Print out the message. */
		cout << WARN_COLOUR_START
			 << "kcc"                                     << ":"
			 << "error"                                   << ":"
			 << "err" << (int) warning_book->warning_code << ":"
			 << warning_book->fld.filename                << ":"
			 << warning_book->fld.line_number             << ":"
			 << warning_book->fld.character_number        << ":"
			 << warning_book->warning_message
			 << WARN_COLOUR_FINISHED;
		/* Show where the input went wrong. */
		display_pointer_to_input_position(warning_book->fld, input);
		/* Move onto next error. */
		e = e->next_warning;
	}
}


static inline
void print_message_book(
	Message*    const& message_book,
	const char* const& input)
{
	Message* e = message_book;
	while (e != NULL) {
		/* Print out the message. */
		cout << MSG_COLOUR_START
			 << "kcc"                                     << ":"
			 << "error"                                   << ":"
			 << "err" << (int) message_book->message_code << ":"
			 << message_book->fld.filename                << ":"
			 << message_book->fld.line_number             << ":"
			 << message_book->fld.character_number        << ":"
			 << message_book->message
			 << MSG_COLOUR_FINISHED;
		/* Show where the input went wrong. */
		display_pointer_to_input_position(message_book->fld, input);
		/* Move onto next error. */
		e = e->next_message;
	}
}

#endif