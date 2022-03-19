
/* Authored by Charlie Keaney                */
/* lexema-pool.h - Responsible for defining the lexema pool,
*                  a structure used to efficiently store and
*                  manage lexema in an input program.        */

#ifndef LEXEMA_POOL_H
#define LEXEMA_POOL_H 1

#include <cstddef>
#include <string.h>
#include <iostream>

#define LEXEMA_POOL_SZ (1 << 16)

using namespace std;

/*****************************************************//**
*                      Declarations                      *
/********************************************************/

/** 
* Represents an entry in the LexemaPool 
**/
struct LexemaEntry {
	const char*  lexeme;
	LexemaEntry* next_entry;
};

/** 
* Represents a pool in which lexema
* can be stored efficiently and easily
* managed.
**/
struct LexemaPool {
	LexemaEntry* data[LEXEMA_POOL_SZ];
};

/**
* Hashes a lexeme for insertion into 
* the lexema table.
* 
* @param lexeme The lexeme to hash.
* @return Returns the hash of the lexeme.
**/
static inline 
size_t hash_lexeme(
	const char* const& lexeme);

/**
* Prints out a lexema pool.
* 
* @param pool The pool to print out.
**/
static inline 
void print_lexema_pool(
	LexemaPool const& pool);

/**
* Looksup a lexeme in the given lexema pool,
* returning the entry found or NULL if no such
* entry exists.
* 
* @param pool The given pool to lookup the lexeme in.
* @param lexeme The given lexeme.
**/
static inline 
LexemaEntry* lookup_lexeme_in_pool(
	LexemaPool  const& pool,
	const char* const& lexeme);

/**
* Inserts the given lexeme into the given 
* lexema pool.
* 
* @param pool The given pool.
* @param lexeme The given lexeme.
* @return Returns true if insertion was successful, 
*         false, otherwise.
**/
static inline 
bool insert_lexeme_into_pool(
	LexemaPool       & pool,
	const char* const& lexeme);

/*****************************************************//**
*                         Definitions                    *
/********************************************************/

static inline 
size_t hash_lexeme(
	const char* const& lexeme)
{
	size_t h = 0;
	for (const char* c = lexeme; *c; c++) {
		h *= 128;
		h += *c;
	}
	return (h * 36) % LEXEMA_POOL_SZ;
}

static inline 
void print_lexema_pool(
	LexemaPool const& pool)
{
	cout << "---- Lexema Pool ----"
	     << endl;
	int i = 0;
	/* For each bucket. */
	for (const LexemaEntry* const* bucket = pool.data;
		bucket < (pool.data + (1 << 16));
		bucket++) {
		/* For each entry within that bucket. */
		for (const LexemaEntry* entry = *bucket;
			entry;
			entry = entry->next_entry) {
			/* Print out that lexeme. */
			cout << i++ 
				 << " : " 
				 << entry->lexeme 
				 << endl;
		}
	}
}

static inline 
LexemaEntry* lookup_lexeme_in_pool(
	LexemaPool  const& pool,
	const char* const& lexeme)
{
	size_t h = hash_lexeme(lexeme);
	LexemaEntry* e = (pool.data)[h];
	while (
		(e != NULL)
		&& (strcmp(lexeme, e->lexeme) != 0)) {
		e = e->next_entry;
	}
	return e;
}

static inline 
bool insert_lexeme_into_pool(
	LexemaPool       & pool,
	const char* const& lexeme)
{
	LexemaEntry* new_entry = new LexemaEntry;
	new_entry->lexeme = lexeme;	
	new_entry->next_entry = NULL;

	size_t h = hash_lexeme(lexeme);
	LexemaEntry* e = (pool.data)[h];
	if (e == NULL) {
		(pool.data)[h] = new_entry;
	} else {
		do {
			if (e->next_entry == NULL) {
				e->next_entry = new_entry;
				break;
			} else {
				e = e->next_entry;
			}
		} while (true);
	}
	return true;
}

#endif