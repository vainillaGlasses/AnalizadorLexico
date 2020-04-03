/*
 * Analizador Lexico: Presentacion Beamer 
 * Autor: Samantha Arburola
 * Modificado: 13mar2017, 17:12
 * */

// gcc show.c -o show
// ./show

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"

int main(){
	createLatex();
	//Table
	addTokensTable();
	//Code
	starCode("FileName.h");

	addType("int");
	addWhitespace(" ");
	addIdentifier("main");
	addPunctuator("(");
	addPunctuator(")");
	addPunctuator("{");
	addWhitespace("\n");
	addWhitespace("\t");
	addIdentifier("creatéLatex");
	addPunctuator("(");
	addPunctuator(")");
	addPunctuator(";");
	addWhitespace("\n");
	addWhitespace("\t");
	addType("int");
	addWhitespace(" ");
	addIdentifier("a");
	addWhitespace(" ");
	addOperator("+");
	addWhitespace(" ");
	addConstant("2");
	addPunctuator(";");
	addWhitespace("\n");
	addWhitespace("\t");
	addPunctuator("'");
	addStringlit("Im a String");
	addPunctuator("\""); ///// OJO ESTA ENTRADA
	addWhitespace("\n");
	addWhitespace("\t");
	addKeyword("return");
	addConstant("0");
	addPunctuator(";");
	addPunctuator("}");
	addWhitespace("\n");
	addWhitespace("\t");
	addEndOfFile("addEndOfFile");
	addWhitespace("\n");
	addError("File no close");
	
	endCode();
	// Histogram
	addHistogram(345,643,445,654,233,456,657,718,345,567);

	finishLatex();
	return 0;
}
void createLatex(void){
	//Create file
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "w");
	//Beamer Document
	fputs("\\documentclass[xcolor=table]{beamer}\n", myLatex);
	fputs("\\usetheme{JUB}\n", myLatex);
	//Library
	fputs("\\usepackage{pgfplots}", myLatex);
	fputs("\\pgfplotsset{width=6cm,compat=1.8}", myLatex);
	fputs("\\usepackage[utf8]{inputenc}\n", myLatex);
	fputs("\\usepackage{xcolor}\n", myLatex);
	fputs("\\usepackage[T1]{fontenc}\n", myLatex);
	fputs("\\usefonttheme{professionalfonts}\n", myLatex);
	fputs("\\usepackage{libertine}\n", myLatex);
	fputs("\\renewcommand{\\ttdefault}{cmtt}\n", myLatex);
	fputs("\\usepackage[scaled]{helvet}\n", myLatex);
	fputs("\\usepackage{hyperref}\n", myLatex);
	fputs("\\hypersetup{pdfpagemode=FullScreen}\n", myLatex);
	// Dinife color
	fputs("\\definecolor{Constant}{HTML}{3D9299}",myLatex);
	fputs("\\definecolor{EndOfFile}{HTML}{E8FF92}",myLatex);
	fputs("\\definecolor{Error}{HTML}{FF4C00}",myLatex);
	fputs("\\definecolor{Identifier}{HTML}{00FF85}",myLatex);
	fputs("\\definecolor{Keyword}{HTML}{FF404F}",myLatex);
	fputs("\\definecolor{Operator}{HTML}{FFEA40}",myLatex);
	fputs("\\definecolor{Punctuator}{HTML}{DA40FF}",myLatex);
	fputs("\\definecolor{Stringlit}{HTML}{14BDCC}",myLatex);
	fputs("\\definecolor{Type}{HTML}{CC147F}",myLatex);
	fputs("\\definecolor{Whitespace}{HTML}{B2FFF2}",myLatex);
	fputs("\\definecolor{backColor}{HTML}{37403C}",myLatex);
	fputs("\\pgfplotscreateplotcyclelist{mycolorlist}{{Constant},{EndOfFile},{Error},{Identifier},{Keyword},{Operator},{Punctuator},{Stringlit},{Type},{Whitespace},}\n", myLatex);

	//Portada
	fputs("\\title{Analizador Léxico}\n", myLatex);
	fputs("\\subtitle{Proyecto No 1}\n", myLatex);
	fputs("\\author{Kevin Lobo, Samantha Arburola, V\\'ictor Chaves}\n", myLatex);
	fputs("\\institute{Semestre I 2017 \\linebreak Compiladores e Int\\'erpretes\\linebreak Ingenier\\'ia en Compitaci\\'on}\n", myLatex);
	fputs("\\date{\\today}\n", myLatex);
	//Documento
	fputs("\\begin{document}\n", myLatex);
	fputs("\\begin{frame}[plain,t] \\titlepage \\end{frame}\n", myLatex);
	fclose(myLatex);
}

void addHistogram(int constant, int endoffile, int error, int identifier, int keyword, int operator, int punctuator, int stringlit, int mytype, int whitespace){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame}\\begin{tikzpicture}\\begin{axis}[axis background/.style={fill=backColor},ybar,ymin=0,x=0.43cm,bar width=4mm,enlargelimits=0.8,ylabel={Cantidad},xlabel={Tokens},symbolic x coords={Constant,EndOfFile,Error,Identifier,Keyword,Operator,Punctuator,Stringlit,Type,Whitespace},ticks=none, nodes near coords,nodes near coords align={vertical},ymajorgrids=true,grid style=dashed,legend style={font=\\tiny,at={(0.5,-0.15)},anchor=north,legend columns=5}]\n",myLatex);
	fputs("\\pgfplotsset{compat=1.10,width=6cm, cycle list name = mycolorlist};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Constant,",myLatex);
	fprintf(myLatex,"%d", constant);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(EndOfFile,",myLatex);
	fprintf(myLatex,"%d", endoffile);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Error,",myLatex);
	fprintf(myLatex,"%d", error);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Identifier,",myLatex);
	fprintf(myLatex,"%d", identifier);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Keyword,",myLatex);
	fprintf(myLatex,"%d", keyword);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Operator,",myLatex);
	fprintf(myLatex,"%d", operator);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Punctuator,",myLatex);
	fprintf(myLatex,"%d", punctuator);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Stringlit,",myLatex);
	fprintf(myLatex,"%d", stringlit);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Type,",myLatex);
	fprintf(myLatex,"%d", mytype);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Whitespace,",myLatex);
	fprintf(myLatex,"%d", whitespace);
	fputs(")};\n",myLatex);
    fputs("\\legend {Constant, EndOfFile, Error, Identifier, Keyword, Operator, Punctuator, Stringlit, Type, Whitespace}\\end{axis}\\end{tikzpicture}\\end{frame}\n",myLatex);
    fclose(myLatex);
}

void addTokensTable(void){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{Tokens}\n", myLatex);
	fputs("\\begin{table}[] \\centering \\begin{tabular}{lllll}\\multicolumn{5}{c}{\\cellcolor[HTML]{680100}{\\color[HTML]{68CBD0} {\\sc \\textbf{Tokens}}}}\\\\Keyword&Type&Identifier&Constant&Stringlit\\\\Operator&Punctuator&Whitespace&End of Line&Error\\end{tabular}\\end{table}", myLatex);
	fputs("\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void addFrameTitleSub(char* title, char* subtitle){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{", myLatex);
	fputs(title, myLatex);
	fputs("} \\framesubtitle{", myLatex);
	fputs(subtitle, myLatex);
	fputs("}\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void addFrameText(char* title, char* text){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{", myLatex);
	fputs(title, myLatex);
	fputs("}\n", myLatex);
	fputs(text, myLatex);
	fputs("\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void addFrameSubTitleText(char* title, char* subtitle, char* text){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{", myLatex);
	fputs(title, myLatex);
	fputs("} \\framesubtitle{", myLatex);
	fputs(subtitle, myLatex);
	fputs("}\n", myLatex);
	fputs(text, myLatex);
	fputs("\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void starCode(char* fileName){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{", myLatex);
	fputs(fileName, myLatex);
	fputs("}\n \\tiny \\tt \n", myLatex);
	fclose(myLatex);
}

void addCodeLine(char* line){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{tabbing} \\=linexx\\= 1\\+\\kill \n \\tt", myLatex);
	fputs(line, myLatex);
	fputs("\\>", myLatex);
	fclose(myLatex);
}

void addKeyword(char* lexema){
	if (lexema == "_Bool"){lexema = "\\_Bool";}
	if (lexema == "_Complex"){lexema = "\\_Complex";}
	if (lexema == "_Imaginary"){lexema = "\\_Imaginary";}
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{blue}\\colorbox[HTML]{FF404F}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addType(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{white}\\colorbox[HTML]{CC147F}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addIdentifier(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{violet}\\colorbox[HTML]{00FF85}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addConstant(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{white}\\colorbox[HTML]{3D9299}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addStringlit(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{yellow}\\colorbox[HTML]{14BDCC}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addOperator(char* lexema){
	if (lexema == "%%"){lexema = "\\%";}
	if (lexema == "&&"){lexema = "\\&\\&";}
	if (lexema == "&"){lexema = "\\&";}
	if (lexema == "^"){lexema = "\\textasciicircum";}
	if (lexema == "~"){lexema = "\\textasciitilde";}
	if (lexema == "^="){lexema = "\\textasciicircum=";}
	if (lexema == "&="){lexema = "\\&=";}
	if (lexema == "%="){lexema = "\\%=";}
	//if (lexema == "\""){lexema = "";}

	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{black}\\bf\\colorbox[HTML]{FFEA40}{\\tt ", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addPunctuator(char* lexema){
	if (lexema == "{"){lexema = "\\{";}
	if (lexema == "}"){lexema = "\\}";}
	if (lexema == "#"){lexema = "\\#";}
	if (lexema == "##"){lexema = "\\#\\#";}
	if (lexema == "$"){lexema = "\\textdollar";}
	if (lexema == "_"){lexema = "\\_";}
	if (lexema == "\\"){lexema = " \\textbackslash";}
	if (lexema == "%%>"){lexema = "\\%>";}
	if (lexema == "<%%"){lexema = "<\\%";}
	if (lexema == "%%:"){lexema = "\\%:";}
	if (lexema == "%%:%%:"){lexema = "\\%:\\%:";}

	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{blue}\\bf\\colorbox[HTML]{DA40FF}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addWhitespace(char* lexema){
	int myType;
	if(lexema == "\v"){lexema = "\\textbackslash v"; myType=1;}
	if(lexema == " "){lexema = "\\textvisiblespace"; myType=1;}
	if(lexema == "\t"){lexema = "\\textvisiblespace\\textvisiblespace\\textvisiblespace\\textvisiblespace"; myType=1;}
	
	if(lexema == "\f"){lexema = "\\textvisiblespace\\textvisiblespace\\textvisiblespace\\textvisiblespace"; myType=2;}
	if(lexema == "\n"){lexema = " "; myType=2;} 

	if(myType == 1){
		FILE *myLatex;
		myLatex = fopen("myLatex.tex", "a+");
		fputs("\\colorbox[HTML]{B2FFF2}{", myLatex);
		fputs(lexema, myLatex);
		fputs("}", myLatex);
		fclose(myLatex);
	}
	if(myType == 2){
		FILE *myLatex;
		myLatex = fopen("myLatex.tex", "a+");
		fputs("\\linebreak\n", myLatex);
		fputs("\\colorbox[HTML]{B2FFF2}{", myLatex);
		fputs(lexema, myLatex);
		fputs("}", myLatex);
		fclose(myLatex);
	}
}

void addEndOfFile(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{darkgray}\\colorbox[HTML]{E8FF92}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addError(char* lexema){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color[HTML]{19FFDF}\\bf\\colorbox[HTML]{FF4C00}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}\n", myLatex);
	fclose(myLatex);
}

void endCodeLine(void){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\end{tabbing}\n", myLatex);
	fclose(myLatex);
}

void endCode(void){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void finishLatex(void){
	// Finish document
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\end{document}\n", myLatex);
	fclose(myLatex);
	//Show Beamer
	system("pdflatex myLatex.tex");
	system("evince myLatex.pdf");
}
