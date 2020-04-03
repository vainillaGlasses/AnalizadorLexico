#include "semantics.h"
#include "parser.h"

int curr_lookup_table_index = 0;


/*Seccion de rutinas para la tabla de simbolos
*La tabla de simbolos indica que "variables" hemos usado.
*De esta manera, sabemos cuando pedir memoria en ensamblador y cuando no
*/


/*
 * TODO: Hay que generar el ensamblador y revisar que funcione bien hermoso y sexy
 * Funciones que usan generate:
 *  finish
 *  assign
 *  gen_infix
 *  read_id
 *  write_expr
 *  check_id
 *  write_zero_label
 *  write_no_zero_jump
 *  write_label
 */

// Ya existe un ID con este nombre?
int lookup(string s) {
    for (int i = 0; i < curr_lookup_table_index; i++) {
        // Si es cero, son iguales
        if (!strcmp(s, lookup_table[i])) {
            return 1;
        }
    }
    
    return 0;
}

// Metemos un ID a la tabla
void enter(string s) {
    if (curr_lookup_table_index >= MAXVARIABLES) {
        printf("Variable limit exceeded for this program. Closing...\n");
        exit(1);
    }
    strcpy(lookup_table[curr_lookup_table_index], s);
    curr_lookup_table_index++;
}



//Inicio de las respectivas rutinas semanticas
void start(void){
	//
	generate_data(".data");
	generate_text(".text");
	generate_text(".balign 4");
	generate_text(".global main");
	generate_text("main:");
}


void finish(void){
	//Genera código ARM para finalizar el programa
    // Cargamos un código de salida 0
    generate("ldr", "r0", "=0", ""); //bx lr hace esto automaticamente
        
    // Salimos del main
	generate("bx", "lr", "", "");

	// Y llamamos a la rutina que unirá .data con .text
	append_files();
}

/*
 * Hay que revisar casos:
 *   Source es literal -> Target es ID o temp => Ambos contemplados
 *   Source es id -> Target es ID o temp
 *   Source es temp -> Target es ID o temp
 *   Otros casos son errores que no deberían de cumplirse
 */
void assign(expr_rec target, expr_rec source){
	//Genera código para asignación
	string source_str;
    string target_str;                
	sprintf(source_str, "=%s", extract(source));
    sprintf(target_str, "=%s", extract(target)); 
	if (source.kind == LITERALEXPR){		       
        generate("ldr", "r0", target_str, "");
		generate("ldr", "r1", source_str, "");
		generate("str", "r1", "[r0]", "");       
                
	} else {
        generate("ldr", "r0", source_str, "");
        generate("ldr", "r0", "[r0]", "");
        generate("ldr", "r1", target_str, "");		
		generate("str", "r0", "[r1]", "");
    }
}

op_rec process_op(void){
	//Produce operator descriptor
	op_rec o;

	if (current_token == PLUSOP) o.operator = PLUS;
	else if (current_token == MINUSOP) o.operator = MINUS;
	else o.operator = PIPEOP;
	return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
	expr_rec e_rec;
	int result;
	if (e1.kind == LITERALEXPR && e2.kind == LITERALEXPR){
		if (op.operator == PLUS){
			result = e1.val + e2.val;
		} else {
			result = e1.val - e2.val;
		}
		
		e_rec.kind = LITERALEXPR;
		e_rec.val = result;
		return e_rec;
	} 
	//An exp_rec with temp variant set
	e_rec.kind = TEMPEXPR;
	/*Genera código para una operación infix.
	*Obtiene el resultado en un temp y setea un semantic record
	*para el resultado
	*/
        
	strcpy(e_rec.name, get_temp());
                
        // TODO: REVISAR QUE ESTE CÓDIGO FUNCIONE BIEN BIEN SEXY
	// Generamos el código de suma/resta

	// Cargamos en r1 o el valor o el puntero a la variable en e1
        string expr_1;
        sprintf(expr_1, "=%s", extract(e1));
        generate("ldr", "r1", expr_1, "");
        
        
	if (e1.kind != LITERALEXPR) {
            generate("ldr", "r1", "[r1]", "");
        }

	// Hay que tambien revisar si e2 es literal o variable
	string expr_2;
        sprintf(expr_2, "=%s", extract(e2));
        generate("ldr", "r2", expr_2, "");
        
        
	if (e2.kind != LITERALEXPR) {
            generate("ldr", "r2", "[r2]", "");
        }
	

	// Y hacemos la operacion
	generate(extract_op(op), "r0", "r1", "r2");
	
        // Y guardamos el valor en el temp que creamos
	// TODO: REVISAR ESTE ENSAMBLADOR, TOMADO DEL CAP #3 DE LA GUIA DE THINKINGEEK
	string expr_3;
	sprintf(expr_3, "=%s", e_rec.name);
    generate("ldr", "r4", expr_3, "");
    generate("str", "r0", "[r4]", "");
        
	return e_rec;
}

void read_id(expr_rec in_var){
	static int first = 1;
    if (first){
    	generate_data(".balign 4");
    	generate_data("scanmsj: .asciz \"%d\"");
    	check_id("return");
    	generate_text(".extern scanf");
    	generate("ldr", "r1", "=return", "");
		generate("str", "lr", "[r1]", "");
    	first = 0;
    }	
	generate("ldr", "r0", "=scanmsj", "");
	if (in_var.kind == LITERALEXPR){
		syntax_error(current_token); //Podrían haber errores aquí
	} else {
		string expr;
		sprintf(expr, "=%s", in_var.name);
		generate("ldr", "r1", expr, "");
	}
	generate("bl", "scanf", "", "");
	generate("ldr", "lr", "=return", "");
	generate("ldr", "lr", "[lr]", "");
}

expr_rec process_id(void){
	expr_rec t;
	//Declarar un ID y construir el semantic record correspondiente
	check_id(token_buffer);
	t.kind = IDEXPR;
	strcpy(t.name, token_buffer);
	return t;
}

expr_rec process_literal(void){
	expr_rec t;
	//Convierte un literal a la representación numérica y construye un semantic record
	t.kind = LITERALEXPR;
	(void) sscanf(token_buffer, "%d", & t.val);
	return t;
}

void write_expr(expr_rec out_expr){
    // TODO: Igual que en el read_id
    static int first = 1;
    if (first){
    	generate_data(".balign 4");
    	generate_data("msj: .asciz \"%d\\n\"");
    	check_id("return");
    	generate_text(".extern printf");
    	generate("ldr", "r1", "=return", "");
		generate("str", "lr", "[r1]", "");
    	first = 0;
    }	
	generate("ldr", "r0", "=msj", "");
	if (out_expr.kind == LITERALEXPR){
		generate("ldr", "r1", extract(out_expr), ""); //Podrían haber errores aquí
	} else {
		string expr;
		sprintf(expr, "=%s", out_expr.name);
		generate("ldr", "r1", expr, "");
		generate("ldr", "r1", "[r1]", "");
	}
	generate("bl", "printf", "", "");
	generate("ldr", "lr", "=return", "");
	generate("ldr", "lr", "[lr]", "");
}

// Esta función escribe el código al archivo final
void generate(string op_code, string param_one, string param_two, string param_three) {
    // TODO: Este generate solo sirve para la parte de texto
    // NOTA: por definición de este ensamblador, el op_code NO puede ser en blanco
    //printf("Instruccion %s %s %s %s\n", op_code, param_one, param_two, param_three);
    fprintf(text_file, "%s", op_code);
    
    if (strcmp(param_one, "")) {
        fprintf(text_file, " %s", param_one);
    }
    
    if (strcmp(param_two, "")) {
        fprintf(text_file, ", %s", param_two);
    }
    
    if (strcmp(param_three, "")) {
        fprintf(text_file, ", %s", param_three);
    }
    fprintf(text_file, "\n");
}

void generate_text(char *string){
	fprintf(text_file, "%s\n", string);
}

void generate_data(char *string){
	fprintf(data_file, "%s\n", string);
}

void append_files(void){
	char ch;
	rewind(text_file);

	while ((ch = fgetc(text_file)) != EOF){
		fputc(ch, data_file);
	}

}

void check_id(string s){
    if (!lookup(s)){
        enter(s);
        char var[42];
        sprintf(var, "%s: .word 0", s);
        generate_data(".balign 4");
        generate_data(var);
    }
}



//Rutina para extraer la información de una expresión
char *extract(expr_rec source){
	char *rec_data;
	if (source.kind == IDEXPR || source.kind == TEMPEXPR || source.kind == VOIDEXPR){
		rec_data = source.name;
	} else {
		rec_data = malloc(sizeof(int));
		sprintf(rec_data, "%d", source.val);
	}
	return rec_data;
}

char *extract_op(op_rec source){
	char *operation;
	if (source.operator == PLUS){
		operation = "add"; 
	} else {
		operation = "sub";
	}
	return operation;
}


//Rutina para asignar temporales
char *get_temp(void){
	//Max temporales asignados hasta el momento
	static int max_temp = 0;
	static char tempname[MAXIDLEN];

	max_temp++;
	sprintf(tempname, "temp_%d", max_temp);
	check_id(tempname);
	return tempname;
}

// Rutina para asignar labels de salto
char *get_jump_label(void) {
	//Max temporales asignados hasta el momento
	static int max_jump_label = 0;
	static char jump_label_name[MAXIDLEN];

	max_jump_label++;
	sprintf(jump_label_name, "jump_label_%d", max_jump_label);
	return jump_label_name;
}

void write_zero_label(string label, expr_rec operation) {
        // Generamos el r0 que contiene 0
        // Usamos r1 para la comparación
        generate("ldr", "r0", "=0", "");
        if (operation.kind == LITERALEXPR) {
            // Si es un literal, hay que sacar el valor
            string value;
            sprintf(value, "=%d", operation.val);
            generate("ldr", "r1", value, "");
        } else {
        	string value;
            sprintf(value, "=%s", operation.name);
            generate("ldr", "r1", value, "");
            generate("ldr", "r1", "[r1]", "");         
        }
        
    generate("cmp", "r1", "r0", "");
	generate("beq", label, "", "");
}

void write_no_zero_jump(string label_zero, string label_no_zero) {
	generate("b", label_no_zero, "", "");
	write_label(label_zero);
}

void write_label(string label) {
        sprintf(label, "%s:", label);
	generate(label, "", "", "");
}