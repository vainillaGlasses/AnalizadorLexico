/*
 * Analizador Lexico: Presentacion Beamer 
 * Autor: Samantha Arburola
 * Modificado: 13mar2017, 17:12
 * */
#ifndef SHOW_H
#define SHOW_H
void createLatex(void);
void addFrameTitleSub(char* title, char* subtitle);
void addFrameText(char* title, char* text);
void addFrameSubTitleText(char* title, char* subtitle, char* text);
void addTokensTable(void);
void addHistogram(int constant, int endoffile, int error, int identifier, int keyword, int operator, int punctuator, int stringlit, int type, int whitespace);
void starCode(char* fileName);
void addCodeLine(char* line);

void addKeyword(char* lexema);
void addType(char* lexema);
void addIdentifier(char* lexema);
void addConstant(char* lexema);
void addStringlit(char* lexema);
void addOperator(char* lexema);
void addPunctuator(char* lexema);
void addWhitespace(char* lexema);
void addEndOfFile(char* lexema);
void addError(char* lexema);

void endCodeLine(void);
void endCode(void);
void finishLatex(void);
#endif /* SHOW_H */
