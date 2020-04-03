/*
 * Analizador Lexico: Presentacion Beamer 
 * Autor: Samantha Arburola
 * Modificado: 02abril2017, 23:49
 * */

// gcc show.c -o show
// ./show

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"

void createLatex(void){
	//Create file
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "w");
	//Beamer Document
	fputs("\\nonstopmode\n", myLatex);
	fputs("\\documentclass[tikz, xcolor=table]{beamer}\n", myLatex);
	fputs("\\usetheme{JUB}\n", myLatex);
	//Library
	fputs("\\usepackage{pgfplots, pgfplotstable}\n", myLatex);
	fputs("\\usepgfplotslibrary{ternary, units}\n", myLatex);
	fputs("\\usepackage{tikz}\n", myLatex);
	fputs("\\usepackage{pgf-pie}\n", myLatex);
	fputs("\\usetikzlibrary{positioning,shadows}\n", myLatex);
	fputs("\\pgfplotsset{width=6cm,compat=1.8}\n", myLatex);
	fputs("\\usepackage[utf8]{inputenc}\n", myLatex);
	fputs("\\usepackage{xcolor}\n", myLatex);
	fputs("\\usepackage{verbatim}\n", myLatex);
	fputs("\\usepackage{underscore}\n", myLatex);
	fputs("\\usepackage{url}\n", myLatex);
	fputs("\\usepackage[T1]{fontenc}\n", myLatex);
	fputs("\\usefonttheme{professionalfonts}\n", myLatex);
	fputs("\\usepackage{libertine}\n", myLatex);
	fputs("\\renewcommand{\\ttdefault}{cmtt}\n", myLatex);
	fputs("\\usepackage[scaled]{helvet}\n", myLatex);
	fputs("\\usepackage{hyperref}\n", myLatex);
	fputs("\\hypersetup{pdfpagemode=FullScreen}\n", myLatex);
	// Define color
	fputs("\\definecolor{colorConstant}{HTML}{3D9299}\n",myLatex);
	fputs("\\definecolor{colorEndOfFile}{HTML}{E8FF92}\n",myLatex);
	fputs("\\definecolor{colorError}{HTML}{FF4C00}\n",myLatex);
	fputs("\\definecolor{colorIdentifier}{HTML}{00FF85}\n",myLatex);
	fputs("\\definecolor{colorKeyword}{HTML}{FF404F}\n",myLatex);
	fputs("\\definecolor{colorOperator}{HTML}{FFEA40}\n",myLatex);
	fputs("\\definecolor{colorPunctuator}{HTML}{DA40FF}\n",myLatex);
	fputs("\\definecolor{colorStringLiteral}{HTML}{14BDCC}\n",myLatex);
	fputs("\\definecolor{colorType}{HTML}{CC147F}\n",myLatex);
	fputs("\\definecolor{colorWhitespace}{HTML}{B2FFF2}\n",myLatex);
	fputs("\\definecolor{backColor}{HTML}{37403C}\n",myLatex);
	fputs("\\pgfplotscreateplotcyclelist{mycolorlist}{{colorConstant},{colorError},{colorIdentifier},{colorKeyword},{colorOperator},{colorPunctuator},{colorStringLiteral},{colorType},}\n", myLatex);

	//Portada
	fputs("\\title{Lexical Analyzer}\n", myLatex);
	fputs("\\subtitle{Project No 1}\n", myLatex);
	fputs("\\author{Kevin Lobo, Samantha Arburola, V\\'ictor Chaves}\n", myLatex);
	fputs("\\institute{Semester I 2017 \\linebreak Compilers and Interpreters \\linebreak Computer Engineering}\n", myLatex);
	fputs("\\date{\\today}\n", myLatex);
	// Define key
	fputs("\\newif\\ifpienumberinlegend\n", myLatex);
	fputs("\\pgfkeys{/number in legend/.code=\n", myLatex);
    fputs("\\expandafter\\let\\expandafter\\ifpienumberinlegend\n", myLatex);
    fputs("\\csname if#1\\endcsname\n", myLatex);
    fputs("\\ifpienumberinlegend\n", myLatex);
    fputs("\\let\\legendbeforenumber\\beforenumber\n", myLatex);
    fputs("\\let\\legendafternumber\\afternumber\n", myLatex);
    fputs("\\def\\beforenumber##1\\afternumber{}\n", myLatex);
    fputs("\\fi,\n", myLatex);
    fputs("\\/numberLegend/.default=true\n}\n", myLatex);
	//Documento
	fputs("\\begin{document}\n", myLatex);
	fputs("\\begin{frame}[plain,t] \\titlepage \\end{frame}\n", myLatex);
	fclose(myLatex);
}

void addPieChart(int constant, int error, int identifier, int keyword, int operator, int punctuator, int stringlit, int mytype){
	int totalTokens;
	totalTokens = constant + error + identifier + keyword + operator + punctuator + stringlit + mytype;
	double dconstant, derror, didentifier, dkeyword, doperator, dpunctuator, dstringlit, dmytype;
	dconstant = (constant*100.0)/totalTokens;
	derror = (error*100.0)/totalTokens;
	didentifier = (identifier*100.0)/totalTokens;
	dkeyword = (keyword*100.0)/totalTokens;
	doperator = (operator*100.0)/totalTokens;
	dpunctuator = (punctuator*100.0)/totalTokens;
	dstringlit = (stringlit*100.0)/totalTokens;
	dmytype = (mytype*100.0)/totalTokens;

	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{Pie Chart} \\small \n \\begin{tikzpicture}[every legend entry/.append style={text width=0cm}]\n", myLatex);
	fputs("\\pie[text=legend, style=drop shadow, radius=2.5,color={colorConstant, colorError, colorIdentifier, colorKeyword, colorOperator, colorPunctuator, colorStringLiteral, colorType}]{", myLatex);
	fprintf(myLatex,"%.2lf", dconstant);
	fputs("/Constant, ", myLatex);
	fprintf(myLatex,"%.2lf", derror);
	fputs("/Error, ", myLatex);
	fprintf(myLatex,"%.2lf", didentifier);
	fputs("/Identifier, ", myLatex);
	fprintf(myLatex,"%.2lf", dkeyword);
	fputs("/Keyword, ", myLatex);
	fprintf(myLatex,"%.2lf", doperator);
	fputs("/Operator, ", myLatex);
	fprintf(myLatex,"%.2lf", dpunctuator);
	fputs("/Punctuator, ", myLatex);
	fprintf(myLatex,"%.2lf", dstringlit);
	fputs("/String Literal, ", myLatex);
	fprintf(myLatex,"%.2lf", dmytype);
	fputs("/Type}\n", myLatex);
	fputs("\\end{tikzpicture} \\end{frame}", myLatex);
	fclose(myLatex);
}

void addHistogram(int constant, int error, int identifier, int keyword, int operator, int punctuator, int stringlit, int mytype) {
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{Histogram} \\small \n\\begin{tikzpicture}\\begin{axis}[axis background/.style={fill=backColor}, ybar,x=0.43cm,bar width=4mm,enlargelimits=0.8,ylabel={Cantidad},xlabel={Tokens},xmajorticks=false,symbolic x coords={Constant,Error,Identifier,Keyword,Operator,Punctuator,StringLiteral,Type}, nodes near coords,nodes near coords align={vertical},ymajorgrids=true,grid style=dashed,legend style={font=\\tiny,at={(0.5,-0.15)},anchor=north,legend columns=5}]\n",myLatex);
	fputs("\\pgfplotsset{compat=1.10,width=6cm, cycle list name = mycolorlist};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Constant,",myLatex);
	fprintf(myLatex,"%d", constant);
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
	fputs("\\addplot+[fill] coordinates {(StringLiteral,",myLatex);
	fprintf(myLatex,"%d", stringlit);
	fputs(")};\n",myLatex);
	fputs("\\addplot+[fill] coordinates {(Type,",myLatex);
	fprintf(myLatex,"%d", mytype);
	fputs(")};\n",myLatex);
    fputs("\\legend {Constant, Error, Identifier, Keyword, Operator, Punctuator, StringLiteral, Type}\\end{axis}\\end{tikzpicture}\\end{frame}\n",myLatex);
    fclose(myLatex);
}

void addTokensTable(void){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{Tokens}\n", myLatex);
	fputs("\\small \\begin{table}[] \\centering \\begin{tabular}{llll}\\multicolumn{4}{c}{\\cellcolor[HTML]{680100}{\\color[HTML]{00FF3A} {\\normalsize \\sc \\textbf{Tokens}}}}\\\\\\color{blue}\\colorbox[HTML]{FF404F}{Keyword}&\\color{white}\\colorbox[HTML]{CC147F}{Type}&\\color{violet}\\colorbox[HTML]{00FF85}{Identifier}&\\color{white}\\colorbox[HTML]{3D9299}{Constant}\\\\\\color{black}{StringLiteral}&\\color{black}\\bf\\colorbox[HTML]{FFEA40}{\\tt Operator}&\\color{blue}\\bf\\colorbox[HTML]{DA40FF}{Punctuator}&\\color[HTML]{19FFDF}\\bf\\colorbox[HTML]{FF4C00}{Error}\\end{tabular}\\end{table}", myLatex);
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

void addExplain(void){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame} \\frametitle{Scanner} \\small \n", myLatex);
	fputs("The lexical analysis of a source code consists of reading said source code and converting the characters in it into a sequence of valid tokens for a specific language (previously defined). In the case of this project, this scanner will analyze programs written in the C programming language, specifically the C99 standard, and said scanner will make use of the tool flex for generating said scanner, as said tool allows to quickly define a scanner by making use of regular expressions to catch all possible valid combinations of strings that form valid tokens.", myLatex);
	fputs("\\end{frame}\n", myLatex);

	fputs("\\begin{frame} \\frametitle{Tokens} \\small \n", myLatex);	
	fputs("The tokens produced by the scanner are as follows: \\linebreak \\linebreak {\\bf + Keyword:} Reserved words that are specific of the C language and by themselves have a meaning. \\linebreak \\linebreak {\\bf + Type:} The type of data that will be used in the context, like in a variable declaration. These are by definition keywords, but are treated as a different token for ease of using a different color in the output.\\linebreak \\linebreak {\\bf + Identifier:} A valid name for denoting an object, such as variables, functions, members of structures, enumerations, user types, and others.\\linebreak \\linebreak {\\bf + Constant:} As its name implies, these are values which are constant, such as numbers (both integers and floats) to give an example.", myLatex);
	fputs("\\end{frame}\n", myLatex);

	fputs("\\begin{frame} \\frametitle{Tokens} \\small \n", myLatex);	
	fputs("{\\bf + StringLiteral:} A different type of constant, string literals are a sequence of characters (chars) of length zero or above, enclosed by double-quotes. \\linebreak \\linebreak {\\bf + Operator:} Specific punctuators that are used mostly in mathematical operations, such as the plus sign or the minus sign. As previously mentioned, these are still classified as punctuators, but for ease of coloring them differently, they are treated as their own classification.\\linebreak \\linebreak {\\bf + Punctuator:} Specific symbols or sequence of symbols which hold independent syntactic and semantic meaning, and completely dependent of context to mean something.\\linebreak \\linebreak {\\bf + Error:} A created token, this type is used to denote any sort of lexical error that may appear on the source code.", myLatex);
	fputs("\\end{frame}\n", myLatex);
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

void startCode(char* fileName){
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\begin{frame}[fragile] \\frametitle{", myLatex);
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
	fputs("\\color{black}{", myLatex);
	//fprintf(myLatex, "\\url{%s}", lexema);
	//fputs("\\{semiverbatim}", myLatex);
	//fputs("\n\\begin{verbatim}", myLatex);
	//fputs(lexema, myLatex);
	//fputs("\\end{verbatim}\n", myLatex);
	fprintf(myLatex, "\n\\verb|%s|\n", lexema);
	//fprintf(myLatex, "\\texttt{%s}", lexema);
	//fputs("\n\\end{semiverbatim}", myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
	/*FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{yellow}\\colorbox[HTML]{14BDCC}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);*/
}

void addOperator(char* lexema){
	if (!strcmp(lexema, "%")){lexema = "\\%";}
	if (!strcmp(lexema, "&&")){lexema = "\\&\\&";}
	if (!strcmp(lexema, "&")){lexema = "\\&";}
	if (!strcmp(lexema, "^")){lexema = "\\textasciicircum";}
	if (!strcmp(lexema, "~")){lexema = "\\textasciitilde";}
	if (!strcmp(lexema, "^=")){lexema = "\\textasciicircum=";}
	if (!strcmp(lexema, "&=")){lexema = "\\&=";}
	if (!strcmp(lexema, "%=")){lexema = "\\%=";}
	if (lexema == "\""){lexema = "\\textquotedbleft";} //tiene left falta right

	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{black}\\bf\\colorbox[HTML]{FFEA40}{\\tt ", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addPunctuator(char* lexema){
	if (!strcmp(lexema, "{")){lexema = "\\{";}
	if (!strcmp(lexema, "}")){lexema = "\\}";}
	if (!strcmp(lexema, "#")){lexema = "\\#";}
	if (!strcmp(lexema, "##")){lexema = "\\#\\#";}
	if (!strcmp(lexema, "$")){lexema = "\\textdollar";}
	if (!strcmp(lexema, "_")){lexema = "\\_";}
	if (!strcmp(lexema, "\\")){lexema = " \\textbackslash";}
	if (!strcmp(lexema, "%%>")){lexema = "\\%>";}
	if (!strcmp(lexema, "<%%")){lexema = "<\\%";}
	if (!strcmp(lexema, "%%:")){lexema = "\\%:";}
	if (!strcmp(lexema, "%%:%%:")){lexema = "\\%:\\%:";}

	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\color{blue}\\bf\\colorbox[HTML]{DA40FF}{", myLatex);
	fputs(lexema, myLatex);
	fputs("}", myLatex);
	fclose(myLatex);
}

void addWhitespace(char* lexema){
	int myType;
	if(!strcmp(lexema, "\v")){lexema = "\\textbackslash v"; myType=1;}
	if(!strcmp(lexema, " ")){lexema = "\\textvisiblespace"; myType=1;}
	if(!strcmp(lexema, "\t")){lexema = "\\textvisiblespace\\textvisiblespace\\textvisiblespace\\textvisiblespace"; myType=1;}
	
	if(!strcmp(lexema, "\f")){lexema = "\\textvisiblespace\\textvisiblespace\\textvisiblespace\\textvisiblespace"; myType=2;}
	if(!strcmp(lexema, "\n")){lexema = " "; myType=2;} 

	if(myType == 1){
		FILE *myLatex;
		myLatex = fopen("myLatex.tex", "a+");
		fputs("\\color{white}{", myLatex);
		fputs(lexema, myLatex);
		fputs("}", myLatex);
		fclose(myLatex);
	}
	if(myType == 2){
		FILE *myLatex;
		myLatex = fopen("myLatex.tex", "a+");
		fputs("\\linebreak\n\\color{white}{", myLatex);
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
	fputs("\n\\end{frame}\n", myLatex);
	fclose(myLatex);
}

void finishLatex(void){
	// Finish document
	FILE *myLatex;
	myLatex = fopen("myLatex.tex", "a+");
	fputs("\\end{document}\n", myLatex);
	fclose(myLatex);
	//Show Beamer
	system("pdflatex myLatex.tex > /dev/null");
	system("evince myLatex.pdf");
}
