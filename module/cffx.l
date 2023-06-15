%{
 FILE *fp;  //指向输出文件的指针 Constant [-]?([0-9])|([1-9][0-9]+[\.]?[0-9]*)
%}

KeyWord [iI][fF]|[tT][hH][eE][nN]|[wW][hH][iI][lL][eE]|[dD][oO]|[rR][eE][aA][dD]|[wW][rR][iI][tT][eE]|[cC][aA][lL][lL]|[bB][eE][gG][iI][nN]|[eE][nN][dD]|[cC][oO][nN][sS][tT]|[vV][aA][rR]|[pP][rR][oO][cC][eE][dD][uU][rR][eE]|[oO][dD][dD]|[cC][aA][sS][eE]|[eE][nN][dD][cC][aA][sS][eE]
Identifier [A-Za-z][A-Za-z0-9]*
Zero [0]
PossiInt ([+]?[1-9][0-9]*)
NegatiInt ([-]?[0-9]+)
Float {Zero}|{PossiInt}|{NegatiInt}(.[0-9]+)
Constant {PossiInt}|{NegatiInt}|{Zero}
Operator [\.\[\]\^\&\-\*\+\?\{\}\"\\\(\)\|\/\$\<\>]|:=
Delimiter  [\,\;\.]
Space (\ )
Tab (\t)
Other [^{KeyWord}{Identifier}{Constant}{Operator}{Delimiter}]
Annotation ("//".*)|("/*"[^("*/")]*"*/") 

%%



{KeyWord} {fprintf(fp, "Keyword : %s \n", yytext); }
{Identifier} {
	if(yyleng > 10){
		fprintf(fp, "Error!Expected a shorter IDENTIFIER!\n");
	}
	else{
		fprintf(fp, "Identifier : %s \n", yytext); 
	}
}  
{Constant} {
	if(yyleng > 14){
		fprintf(fp, "Error!Expected a shorter CONSTANT!\n");
	}
	else{
		fprintf(fp, "Constant : %s \n", yytext);
	}
}
{Operator} {fprintf(fp, "Operator : %s \n", yytext);}
{Delimiter} {fprintf(fp, "Delimiter : %s \n", yytext);}

\n {;}
{Space} {;}
{Tab} {;}
{Other} {fprintf(fp, "Error! %s\n", yytext); }
{Annotation} {fprintf(fp, "Annotation : %s \n", yytext);}

%%
int main(){
fp = fopen("D:\\Code\\Cpp\\compiler\\module\\cffx.txt", "w+");
yylex();

}
int yywrap(){
	return 1;
}