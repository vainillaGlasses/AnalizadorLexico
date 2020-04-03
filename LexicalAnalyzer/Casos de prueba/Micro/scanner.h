#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>

/* character classification macros */
#include <ctype.h>
#include <string.h>

char token_buffer[200]; //Tamaño momentaneo, debe ser dinámico

// Tokens
typedef enum token_types { //Se agrego PIPE para el punto 10 de los ejercicios
	BEGIN, END, READ, WRITE, ID, INTLITERAL,
	LPAREN, RPAREN, PIPE, SEMICOLON, COMMA, ASSIGNOP,
	PLUSOP, MINUSOP, SCANEOF
} token;

// Punteros a archivos
FILE *source_file;
FILE *text_file;
FILE *data_file;

token scanner(void);
void lexical_error(int in_char);
token check_reserved(void);
void clear_buffer(void);
void buffer_char(int in_char);

#endif /* SCANNER_H */