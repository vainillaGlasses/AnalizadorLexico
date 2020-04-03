#include "parser.h"

token *temp_next_token = NULL;

void system_goal(void){
	//Production: <system goal> ::= <program> SCANEOF
	program();
	match(SCANEOF);
}

void program(void){
	//Production: <program> ::= BEGIN <statement list> END
	start();
	match(BEGIN);
	statement_list();
	match(END);
	finish();
}

void statement_list(void){
	//Production: <statement list> ::= <statement> {<statement>}
	statement();
	while (1){
		switch (next_token()){
			case ID:
			case READ:
			case WRITE:
				statement();
				break;
			default:
				return;
		}
	}
}

void statement(void){
	token tok = next_token();

	switch(tok){
		case ID:
			//<statement> ::= ID := <expression>;
			match(ID);
			expr_rec target = process_id();
			expr_rec src;
			match(ASSIGNOP);
			expression(target, &src, 0, 0, 0);
                        if (src.kind != VOIDEXPR) {
                            assign(target, src);
                        }
                        match(SEMICOLON);
			break;
		case READ:
			//<statement> ::= READ (<id list>);
			match(READ);
			match(LPAREN);
			id_list();
			match(RPAREN);
			match(SEMICOLON);
			break;
		case WRITE:
			//<statement> ::= WRITE (<expr list>);
			match(WRITE);
			match(LPAREN);
			expr_list();
			match(RPAREN);
			match(SEMICOLON);
			break;
		default:
			syntax_error(tok);
			break;
	}
}

void id_list(void){
	//<id list> ::= ID {, ID}
	match(ID);
	expr_rec id = process_id();
	read_id(id);

	while (next_token() == COMMA){
		match(COMMA);
		match(ID);
		expr_rec id = process_id();
		read_id(id);
	}
}

void expression(expr_rec target, expr_rec *result, int possible_cond, int from_cond, int can_assign){
	expr_rec left_operand, center_operand, right_operand;
	op_rec op;

	primary(target, & left_operand);

	while (next_token() == PLUSOP || next_token() == MINUSOP){
		add_op(& op);
		primary(target, & right_operand);
		left_operand = gen_infix(left_operand, op, right_operand);
	}

	// Si estamos dentro de una recursión, tenemos que asignar o si no se pierden los valores
	if (target.kind != VOIDEXPR && can_assign) {
	    assign(target, left_operand);	
	}
	
	// Código para revisar si es una condicional
	if (next_token() == PIPE && !from_cond){
		if (possible_cond){
			
			// Tengo que generar dos labels
			string label_zero;
			string label_no_zero;

			strcpy(label_zero, get_jump_label());
			strcpy(label_no_zero, get_jump_label());


			add_op(&op);
			write_zero_label(label_zero, left_operand);
			expression(target, &center_operand, 0, 1, 1);

			if (next_token() == PIPE){
				add_op(&op);
				write_no_zero_jump(label_zero, label_no_zero);
				expression(target, &right_operand, 0, 0, 1);
				write_label(label_no_zero);

				// Generamos un nuevo left_operand
                                left_operand.kind = VOIDEXPR;
                                strcpy(left_operand.name, target.name);
			} else {
				syntax_error(next_token());
			}
		} else {
			syntax_error(next_token());
		}
	}


		
	*result = left_operand;
}

void expr_list(void){
	//<expr list> ::= <expression> {, <expression>}
	expr_rec target;
    target.kind = VOIDEXPR;
    expr_rec record;
	expression(target, &record, 0, 0, 0);
	write_expr(record);
	while (next_token() == COMMA){
		match(COMMA);
		expression(target, &record, 0, 0, 0);
		write_expr(record);
	}
}


void add_op(op_rec *op){
	token tok = next_token();

	//<addop> ::= PLUSOP | MINUSOP | PIPE
	if (tok == PLUSOP || tok == MINUSOP || tok == PIPE) {
		match(tok);
		*op = process_op();
	}
	else syntax_error(tok);
}

void primary(expr_rec target, expr_rec *operand){
	token tok = next_token();

	switch(tok){
		case LPAREN:
			//<primary> ::= (expression)
			match(LPAREN);
			expression(target, operand, 1, 0, 0);
			match(RPAREN);
			break;
		case ID:
			//<primary> ::= ID
			match(ID);
			*operand = process_id(); 
			break;
		case INTLITERAL:
			//<primary> ::= INTLITERAL
			match(INTLITERAL);
			*operand = process_literal();
			break;
		default:
			syntax_error(tok);
			break;
	}
}


void syntax_error(token tok) {
    printf("A syntax error has ocurred\n");
}


//Rutina para hacer match de un token
void match(token t){
	if (temp_next_token == NULL){
		if (scanner() == t){
			current_token = t;
		} else {
			syntax_error(t);
		}
	} else {
		if (*temp_next_token == t){
			current_token = t;
			free(temp_next_token);
			temp_next_token = NULL;
		} else {
			syntax_error(t);
		}
	}
	
}

//Rutina para obtener el siguiente token
token next_token(){
	token tok;
	if (temp_next_token == NULL){
		tok = scanner();
		temp_next_token = malloc(sizeof(tok));
		*temp_next_token = tok;
	} else {
		tok = *temp_next_token;
	}
	return tok;
}