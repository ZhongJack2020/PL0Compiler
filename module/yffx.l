%{

#include <string.h>
#include <stdlib.h>
#include "yffx.tab.h"


int row_num = 1, col_num = 1;  //行数和列数
char *key;

%}


KeyWord [iI][fF]|[tT][hH][eE][nN]|[eE][lL][sS][eE]|[wW][hH][iI][lL][eE]|[dD][oO]|[rR][eE][aA][dD]|[wW][rR][iI][tT][eE]|[cC][aA][lL][lL]|[bB][eE][gG][iI][nN]|[eE][nN][dD]|[cC][oO][nN][sS][tT]|[vV][aA][rR]|[pP][rR][oO][cC][eE][dD][uU][rR][eE]|[oO][dD][dD]|[cC][aA][sS][eE]|[eE][nN][dD][cC][aA][sS][eE]
Identifier [A-Za-z][A-Za-z0-9]*
Zero [0]
PossiInt ([+]?[1-9][0-9]*)
NegatiInt ([-]?[0-9]+)
Float {Zero}|{PossiInt}|{NegatiInt}(.[0-9]+)
Constant {PossiInt}|{NegatiInt}|{Zero}
Operator [\[\]\^\&\-\*\+\?\{\}\"\\\(\)\|\/\$\<\>\#\=]|:=
Delimiter  [\,\;\.\:]
Space (\ )
Tab (\t)
Other [^{KeyWord}{Identifier}{Constant}{Operator}{Delimiter}]

%%

	//这部分注释要有前导空格，否则lex编译出错

{KeyWord} {
	// fprintf(fp, "%s : K, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "CONST")){
		key = "CONST";
		 
		return CONST;
	}
	if(!strcmpi(yytext, "VAR")){
		key = "VAR";
		return VAR;
	}
	if(!strcmpi(yytext, "PROCEDURE")){
		key = "PROCEDURE";
		 
		return PROCEDURE;
	}
	if(!strcmpi(yytext, "BEGIN")){
		key = "BEGIN";
		 
		return _BEGIN_;
	}
	if(!strcmpi(yytext, "END")){
		key = "END";
		 
		return END;
	}
	if(!strcmpi(yytext, "IF")){
		key = "IF";
		 
		return IF;
	}
	if(!strcmpi(yytext, "THEN")){
		key = "THEN";
		 
		return THEN;
	}
	if(!strcmpi(yytext, "ELSE")){
		key = "ELSE";
		 
		return ELSE;
	}
	if(!strcmpi(yytext, "ODD")){
		key = "ODD";
		 
		return ODD;
	}
	if(!strcmpi(yytext, "WHILE")){
		key = "WHILE";
		 
		return WHILE;
	}
	if(!strcmpi(yytext, "DO")){
		key = "DO";
		 
		return DO;
	}
	if(!strcmpi(yytext, "CALL")){
		key = "CALL";
		 
		return CALL;
	}
	if(!strcmpi(yytext, "READ")){
		key = "CONST";
		 
		return READ;
	}
	if(!strcmpi(yytext, "WRITE")){
		key = "WRITE";
		 
		return WRITE;
	}
	if(!strcmpi(yytext, "CASE")){
		key = "CASE";
		 
		return CASE;
	}
	if(!strcmpi(yytext, "ENDCASE")){
		key = "ENDCASE";
		 
		return ENDCASE;
	}
	col_num += yyleng;
	// return KeyWord;
}
{Identifier} {
	if(yyleng > 10){
		// fprintf(fp, "Error!Expected a shorter IDENTIFIER!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		// fprintf(fp, "%s : I, (%d, %d)\n", yytext, row_num, col_num); col_num += yyleng;
	}
	// printf("--%s--\n", yytext);
	key = "IDENTIFIER";
	 
	return IDENTIFIER;
}  
{Constant} {
	if(yyleng > 14){
		// fprintf(fp, "Error!Expected a shorter CONSTANT!(%d, %d)\n", row_num, col_num);
		col_num += yyleng;
	}
	else{
		// fprintf(fp, "%s : C, (%d, %d)\n", yytext, row_num, col_num);
		col_num += yyleng;
	}
	key = "CONSTANT";
	 
	return CONSTANT;
}
{Operator} {
	// fprintf(fp, "%s : O, (%d, %d)\n", yytext, row_num, col_num);
	if(!strcmpi(yytext, "=")||!strcmpi(yytext, "#")||!strcmpi(yytext, "<")||!strcmpi(yytext, "<=")||!strcmpi(yytext, ">")||!strcmpi(yytext, ">=")){
		key = "RELOP";
		 
		return RELOP;
	}
	if(!strcmpi(yytext, "(")){
		key = "LPAREN";
		 
		return LPAREN;
	}
	if(!strcmpi(yytext, ")")){
		key = "RPAREN";
		 
		return RPAREN;
	}
	if(!strcmpi(yytext, ":=")){
		key = "CONST";
		 
		return ASSIGN;
	}
	if(!strcmpi(yytext, "-")){
		key = "MINUS";
		 
		return MINUS;
	}
	if(!strcmpi(yytext, "+")){
		key = "PLUS";
		 
		return PLUS;
	}
	if(!strcmpi(yytext, "*")){
		key = "TIMES";
		 
		return TIMES;
	}
	if(!strcmpi(yytext, "/")){
		key = "DIVIDE";
		 
		return DIVIDE;
	}
	col_num += yyleng;
	// return Operator;
}
{Delimiter} {
	// fprintf(fp, "%s : D, (%d, %d)\n", yytext, row_num, col_num);
	++col_num;
	if(!strcmpi(yytext, ",")){
		key = "COMMA";
		 
		return COMMA;
	}
	if(!strcmpi(yytext, ";")){
		key = "SEMI";
		 
		return SEMI;
	}
	if(!strcmpi(yytext, ".")){
		key = "DOT";
		 
		return DOT;
	}
	if(!strcmpi(yytext, ":")){
		key = "COLON";
		 
		return COLON;
	}
}
\n {++row_num; col_num = 1;}  //换行符计数
{Space} {;}
{Tab} {;}
{Other} {
	// fprintf(fp, "%s : T, (%d, %d)\n", yytext, row_num, col_num);
	col_num += yyleng;
}

%%
// int main(){
// 	// fp = fopen("E:/.../.../Compiling Principle/Lab2/WordOutput.txt", "w+");
// 	yylex();
// }
int yywrap(){
	return 1;
}



