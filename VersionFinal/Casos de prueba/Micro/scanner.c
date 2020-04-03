//Esto funciona hermosamente
#include "scanner.h"


/*DUDAS
	-Como detectar un ID que no inicia con letra

*/

/*TODO
	LISTO => clear_buffer();
	LISTO => buffer_char();
	LISTO => check_reserved();
	LISTO => lexical_error();
	LISTO => match();
	LISTO => next_token();
	LISTO => syntax_error();
	LISTO => generate();
	LISTO => extract();
	LISTO => lookup();
	LISTO => enter();
	Agregar semántica al parseador
	Puntos 8 y 10 de los ejercicios del capitulo;
	Generar codigo ensamblador ARM;
*/




token scanner(void){
	int in_char, c;
	clear_buffer();
	if (feof(source_file)) return SCANEOF;

	while ((in_char = getc(source_file)) != EOF) {
		if (isspace(in_char)) continue; //No hacer nada
		else if (isalpha(in_char)) {
			// ID ::= LETTER | ID LETTER | ID DIGIT | ID UNDERSCORE
			buffer_char(in_char);
			for (c = getc(source_file); isalnum(c) || c == '_'; c = getc(source_file)) buffer_char(c);
			ungetc(c, source_file);
			return check_reserved(); // Hay que hacer esta función
		} else if (isdigit(in_char)){
			//INTLITERAL ::= DIGIT | INTLITERAL DIGIT
			buffer_char(in_char);
			for (c = getc(source_file); isdigit(c); c = getc(source_file)) buffer_char(c);
			ungetc(c, source_file);
			return INTLITERAL;
		} else if (in_char == '(') return LPAREN;
		else if (in_char == ')') return RPAREN;
		else if (in_char == '|') return PIPE; //Soporte del punto 10
		else if (in_char == ';') return SEMICOLON;
		else if (in_char == ',') return COMMA;
		else if (in_char == '+') return PLUSOP;
		else if (in_char == ':') {
			//looking for ":="
			c = getc(source_file);
			if (c == '=') return ASSIGNOP;
			else {
				ungetc(c, source_file);
				lexical_error(in_char);
			}
		} else if (in_char == '-') {
			//Is it --, comment start
			c = getc(source_file);
			if (c == '-'){
				do
					in_char = getc(source_file);
				while (in_char != '\n');
			} else {
				ungetc(c, source_file);
				return MINUSOP;
			}
		} else lexical_error(in_char);
	}
}

void lexical_error(int in_char){
	printf("A lexical error has ocurred while scanning the char: %c \n", in_char);
}

token check_reserved(void){
	if (!strcmp(token_buffer, "begin")){
		return BEGIN;
	} else if (!strcmp(token_buffer, "end")){
		return END;
	} else if (!strcmp(token_buffer, "read")){
		return READ;
	} else if (!strcmp(token_buffer, "write")){
		return WRITE;
	} else return ID;
}

void clear_buffer(void){
	memset(&token_buffer[0], 0, sizeof(token_buffer));
}

void buffer_char(int in_char){
        // Creamos un "string" nuevo y lo concatenamos
        // Hacemos la conversión de int a char
	char concat_string[] = {(char) in_char, '\0'};
	strcat(token_buffer, concat_string);	
}