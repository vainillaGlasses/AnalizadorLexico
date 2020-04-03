#ifndef SEMANTICS_H
#define SEMANTICS_H

#define MAXIDLEN 33
#define MAXVARIABLES 100

#include "scanner.h"

typedef char string[MAXIDLEN];

char lookup_table[MAXVARIABLES][MAXIDLEN];



//for operators
typedef struct {
	enum op { PLUS, MINUS, PIPEOP } operator;
} op_rec;

//expression types
enum expr {IDEXPR, LITERALEXPR, TEMPEXPR, VOIDEXPR};

//for <primary> and <expression>
typedef struct expression{
	enum expr kind;
	union {
		string name; //for IDEXPR, TEMPEXPR
		int val; //for LITERALEXPR
	};	
} expr_rec;


int lookup(string s);
void enter(string s);
void start(void);
void finish(void);
void assign(expr_rec target, expr_rec source);
op_rec process_op(void);
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);
void read_id(expr_rec in_var);
expr_rec process_id(void);
expr_rec process_literal(void);
void write_expr(expr_rec out_expr);
void generate(string op_code, string param_one, string param_two, string param_three);
void generate_text(char *string);
void generate_data(char *string);
void append_files(void);
void check_id(string s);
char *extract(expr_rec source);
char *extract_op(op_rec source);
char *get_temp(void);
char *get_label(void);
char *get_jump_label(void);
void write_zero_label(string label, expr_rec operation);
void write_no_zero_jump(string label_zero, string label_no_zero);
void write_label(string label);

#endif /* SEMANTICS_H */