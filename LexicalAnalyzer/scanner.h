/*
 * Victor Chaves
 */

#ifndef SCANNER_H
/*
 * Enumeración de tipos
 */
typedef enum {
    KEYWORD,
    TYPE,
    IDENTIFIER,
    CONSTANT,
    STRINGLIT,
    OPERATOR,
    PUNCTUATOR,
    WHITESPACE,
    ENDOFFILE,
    ERROR,
} tokens;

/*
 * Estructura para mantener los errores que se encuentren
 */
typedef struct node {
    int line;
    int col;
    struct node * next;
    char err_string[];
} error_node;


#endif /* SCANNER_H */

