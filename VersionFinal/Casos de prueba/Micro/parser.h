#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "semantics.h"

token current_token;


void system_goal(void);
void program(void);
void statement_list(void);
void statement(void);
void id_list(void);
void expression(expr_rec target, expr_rec *result, int possible_cond, int from_cond, int can_assign);
void expr_list(void);
void add_op(op_rec *op);
void primary(expr_rec target, expr_rec *operand);
void syntax_error(token tok);
void match(token tok);
token next_token(void);



#endif /* PARSER_H */