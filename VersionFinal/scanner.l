%{
    #include <stdio.h>
    #include "scanner.h"
    #include "show.h"
    
    int line_num = 1;
    int col_num = 1;
    
    int keyword_counter;
    int type_counter;
    int id_counter;
    int const_counter;
    int str_counter;
    int op_counter;
    int punc_counter;
    int err_counter;


    error_node *head = NULL;
    
    void count();
%}

%%

"auto"     { count(); return KEYWORD; }
"break"    { count(); return KEYWORD; }
"case"     { count(); return KEYWORD; }
"const"    { count(); return KEYWORD; }
"continue" { count(); return KEYWORD; }
"default"  { count(); return KEYWORD; }
"do"       { count(); return KEYWORD; }
"else"     { count(); return KEYWORD; }
"enum"     { count(); return KEYWORD; }
"extern"   { count(); return KEYWORD; }
"for"      { count(); return KEYWORD; }
"goto"     { count(); return KEYWORD; }
"if"       { count(); return KEYWORD; }
"inline"   { count(); return KEYWORD; }
"register" { count(); return KEYWORD; }
"restrict" { count(); return KEYWORD; }
"return"   { count(); return KEYWORD; }
"sizeof"   { count(); return KEYWORD; }
"static"   { count(); return KEYWORD; }
"struct"   { count(); return KEYWORD; }
"switch"   { count(); return KEYWORD; }
"typedef"  { count(); return KEYWORD; }
"union"    { count(); return KEYWORD; }
"volatile" { count(); return KEYWORD; }
"while"    { count(); return KEYWORD; }

"_Bool"      { count(); return TYPE; }
"char"       { count(); return TYPE; }
"_Complex"   { count(); return TYPE; }
"double"     { count(); return TYPE; }
"float"      { count(); return TYPE; }
"int"        { count(); return TYPE; }
"_Imaginary" { count(); return TYPE; }
"long"       { count(); return TYPE; }
"short"      { count(); return TYPE; }
"signed"     { count(); return TYPE; }
"unsigned"   { count(); return TYPE; }
"void"       { count(); return TYPE; }


[a-zA-Z_][a-zA-Z0-9_]* { count(); return IDENTIFIER; }


0[xX][a-fA-F0-9]+(u|U|l|L)*? { count(); return(CONSTANT); }
0[0-9]+(u|U|l|L)*?           { count(); return(CONSTANT); }
[0-9]+(u|U|l|L)*?            { count(); return(CONSTANT); }

[0-9]+[Ee][+-]?[0-9]+(f|F|l|L)?             { count(); return(CONSTANT); }
[0-9]*"."[0-9]+([Ee][+-]?[0-9]+)?(f|F|l|L)? { count(); return(CONSTANT); }
[0-9]+"."[0-9]*([Ee][+-]?[0-9]+)?(f|F|l|L)? { count(); return(CONSTANT); }

L?'(\\.|[^\\'])+'     { count(); return(CONSTANT); }
L?\"(\\.|[^\\"])*\"   { count(); return STRINGLIT; }

"="  { count(); return OPERATOR; } //
"+"  { count(); return OPERATOR; } //
"-"  { count(); return OPERATOR; } //
"*"  { count(); return OPERATOR; } //
"/"  { count(); return OPERATOR; } //
"%"  { count(); return OPERATOR; } //
"++" { count(); return OPERATOR; } //
"--" { count(); return OPERATOR; } //

"==" { count(); return OPERATOR; } //
"!=" { count(); return OPERATOR; } //
">"  { count(); return OPERATOR; } //
"<"  { count(); return OPERATOR; } //
">=" { count(); return OPERATOR; } //
"<=" { count(); return OPERATOR; } //
"&&" { count(); return OPERATOR; } //
"||" { count(); return OPERATOR; } //

"&"   { count(); return OPERATOR; } //
"|"   { count(); return OPERATOR; } //
"~"   { count(); return OPERATOR; } //
"!"   { count(); return OPERATOR; } //
"<<"  { count(); return OPERATOR; } //
">>"  { count(); return OPERATOR; } //
"^"   { count(); return OPERATOR; } //
"*="  { count(); return OPERATOR; } //
"/="  { count(); return OPERATOR; } //
"%="  { count(); return OPERATOR; } //
"+="  { count(); return OPERATOR; } //
"-="  { count(); return OPERATOR; } //
"<<=" { count(); return OPERATOR; } //
">>=" { count(); return OPERATOR; } //
"&="  { count(); return OPERATOR; } //
"^="  { count(); return OPERATOR; } //
"|="  { count(); return OPERATOR; } //

"["  { count(); return PUNCTUATOR; } //
"]"  { count(); return PUNCTUATOR; } //
"("  { count(); return PUNCTUATOR; } //
")"  { count(); return PUNCTUATOR; } //
"{"  { count(); return PUNCTUATOR; } //
"}"  { count(); return PUNCTUATOR; } //
"."  { count(); return PUNCTUATOR; } //
"->" { count(); return PUNCTUATOR; } //
";"  { count(); return PUNCTUATOR; } //
","  { count(); return PUNCTUATOR; } //

"<:" { count(); return PUNCTUATOR; } //
":>" { count(); return PUNCTUATOR; } //
"<%" { count(); return PUNCTUATOR; } //
"%>" { count(); return PUNCTUATOR; } //
"%:" { count(); return PUNCTUATOR; } //
"%:%:" { count(); return PUNCTUATOR; } //

"..." { count(); return PUNCTUATOR; } //
"?"   { count(); return PUNCTUATOR; } //
":"   { count(); return PUNCTUATOR; } //
"#"   { count(); return PUNCTUATOR; } //
"##"  { count(); return PUNCTUATOR; } //

[ \n\t\v\f] { count(); return WHITESPACE; }

<<EOF>> { return ENDOFFILE; }

. { return ERROR; }

%%

void count() {
    int i;
    
    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            line_num++, 
            col_num = 1;
        } else if (yytext[i] == '\t') {
            col_num += 8 - (col_num % 8);
        } else {
            col_num++;
        }
    }
}

error_node* push_error(error_node *err_head) {
    error_node *current = err_head;
    
    if (current == NULL) {
        err_head = (error_node*)malloc(sizeof(error_node));
        err_head->line = line_num;
        err_head->col = col_num;
        strcpy(err_head->err_string, yytext);
        err_head->next = NULL;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = (error_node*)malloc(sizeof(error_node));
        current->next->line = line_num;
        current->next->col = col_num;
        strcpy(current->next->err_string, yytext);
        current->next->next = NULL;
    }
    
    return err_head;
}

void print_errors(error_node *err_head) {
    error_node *current = err_head;
    while (current != NULL) {
        printf("LEXICAL ERROR FOUND ON LINE %d, COLUMN %d: %s\n", current->line, current->col, current->err_string);
        current = current->next;
    }
}


void free_errors() {
    error_node *next_err;
    while(head != NULL) {
        next_err = head->next;
        free(head);
        head = next_err;
    }
}

int main(int argc, char **argv) {
    int tok;
    if (argc != 2) {
        printf("Invalid arguments count\n"); 
        printf("Usage: ./scanner input_file\n");
        return 1;
    } else {
        char command[30];
        sprintf(command, "./preprocessor %s", argv[1]);
        int returnValue = system(command);
        yyin = fopen("output.c", "r+");
        if (!yyin || returnValue == -1){
        	printf("Unable to open %s. Please, verify that the file exists.\n", argv[1]);
        	return 1;
        }
        tok = yylex();

        createLatex();
        addExplain();
        addTokensTable();
        startCode(argv[1]);

        int change = 0;

        while(tok != ENDOFFILE){
            if (line_num % 10 == 0 && !change){
                //printf("CANTIDAD LINEAS: %d\n", line_num);
                endCode();
                startCode(argv[1]);
                change = 1;
            } else if (line_num % 10 != 0) {
                change = 0;
            }
            switch (tok){
                case KEYWORD:
                    //printf("KEYWORD: %s\n", yytext);
                    addKeyword(yytext);
                    keyword_counter++;
                    break;
                case TYPE:
                    //printf("TYPE: %s\n", yytext);
                    addType(yytext);
                    type_counter++;
                    break;
                case IDENTIFIER:
                    //printf("IDENTIFIER: %s\n", yytext);
                    addIdentifier(yytext);
                    id_counter++;
                    break;
                case CONSTANT:
                    //printf("CONSTANT: %s\n", yytext);
                    addConstant(yytext);
                    const_counter++;
                    break;
                case STRINGLIT:
                    //printf("STRINGLIT: %s\n", yytext);
                    addStringlit(yytext);
                    str_counter++;
                    break;
                case OPERATOR:
                    //printf("OPERATOR: %s\n", yytext);
                    addOperator(yytext);
                    op_counter++;
                    break;
                case PUNCTUATOR:
                    //printf("PUNCTUATOR: %s\n", yytext);
                    addPunctuator(yytext);
                    punc_counter++;
                    break;
                case WHITESPACE:
                    // El whitespace tambien se debería poner como está en el documento de salida
                    // Pero por si solo no hace nada
                    addWhitespace(yytext);
                    break;
                case ERROR:
                    head = push_error(head);
                    printf("LEXICAL ERROR: %s\n", yytext);
                    addError(yytext);
                    col_num++;
                    err_counter++;
                    break;
            }
            
            tok = yylex();
        }
        addEndOfFile("Finished");
        endCode();

        // Histogram
        addHistogram(
            const_counter,
            err_counter,
            id_counter,
            keyword_counter,
            op_counter,
            punc_counter,
            str_counter,
            type_counter
        );

	// PieChart
        addPieChart(
            const_counter,
            err_counter,
            id_counter,
            keyword_counter,
            op_counter,
            punc_counter,
            str_counter,
            type_counter
        );
        
        printf("Generating Beamer presentation. Please wait...\n");
        
        finishLatex();
        
        free_errors();
        remove("output.c");
        fclose(yyin);
    }
}