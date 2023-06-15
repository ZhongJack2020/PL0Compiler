%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define    	Iden    	300
#define    	IntNo	301
#define	  	RealNo  	302
/*keywords:*/
#define	  	Program 	400
#define	  	Begin	401
#define	  	End	402
#define	  	Var	403
#define	  	Integer 	404
#define	  	Real	405
#define	  	While	406
#define		If	407
#define		Then	408
#define		Else	409

/*bijiao yunsuanfu: */
#define		LE	500
#define		GE	501
#define		NE	502
#define		ERRORCHAR	600

#define MAXSTR 20

int row_num = 1, col_num = 1;

/* This array is used for determin if a identier is keyword */

char key[20]; /* this array is used to store the string of identifier or 
		  integer/real number.When one of them are abtained in yytext, 
		  copy it to key. key will be used in YACC source file
		  (YSP file filename.y) */
int id_or_keyword(char *name);/* to check out if the name is a keyword*/
int countCharacter(const char* str, char ch);
%}
letter      		[A-Za-z]
alnum		[A-Za-z0-9]
d		[0-9]
white		[\t\040]
Annotation ("//".*)|("/*"[^("*/")]*"*/") 
%start		COMMENT
%%

\{			{ECHO;BEGIN COMMENT;} /*ECHO:存入yyout*/
<COMMENT>\}		{ECHO;BEGIN 0;}
<COMMENT>\n		{ECHO;++row_num; col_num = 1;}
<COMMENT>[^\}]+ 	{ECHO;} /*去注释:{...}*/

\n {row_num += 1; col_num = 1;}

[Bb][eE][Gg][iI][Nn]			{ECHO;col_num += yyleng;return Begin;}
[eE][Nn][Dd]			{ECHO;col_num += yyleng;return End;}
[Pp][Rr][oO][Gg][Rr][Aa][Mm]		{ECHO;col_num += yyleng;return Program;}
[Vv][Aa][Rr]			{ECHO;col_num += yyleng;return Var;}
[Ii][nN][Tt][eE][Gg][eE][Rr]		{ECHO;col_num += yyleng;return Integer;}
[Rr][eE][Aa][lL]			{ECHO;col_num += yyleng;return Real;}
[Ww][Hh][Ii][Ll][Ee]			{ECHO;col_num += yyleng;return While;}
[iI][Ff]				{ECHO;col_num += yyleng;return If;}
[Tt][Hh][Ee][Nn]			{ECHO;col_num += yyleng;return Then;}
[Ee][Ll][Ss][Ee]			{ECHO;col_num += yyleng;return Else;}


({d}+(\.{d}*)?[Ee]([+-])?{d}+)|({d}*\.{d}+[Ee]([+-])?{d}+)	{ECHO;strcpy(key,yytext);return RealNo;col_num += yyleng;}
{d}+\.{d}*|{d}*\.{d}+					{ECHO;strcpy(key,yytext);return RealNo;col_num += yyleng;}
{d}+						{ECHO;strcpy(key,yytext);return IntNo;col_num += yyleng;}


"("			{ECHO;return '(';col_num += yyleng;}
")"			{ECHO;return ')';col_num += yyleng;}
"["			{ECHO;return '[';col_num += yyleng;}
"]"			{ECHO;return ']';col_num += yyleng;}
">"			{ECHO;return '>';col_num += yyleng;}
"<"			{ECHO;return '<';col_num += yyleng;}
"="			{ECHO;return '=';col_num += yyleng;}
"<="			{ECHO;return LE;col_num += yyleng;}
">="			{ECHO;return GE;col_num += yyleng;}
"!="			{ECHO;return NE;col_num += yyleng;}
":"			{ECHO;return ':';col_num += yyleng;}
";"			{ECHO;return ';';col_num += yyleng;}
"\."			{ECHO;return '.';col_num += yyleng;}
"*"			{ECHO;return '*';col_num += yyleng;}
"+"			{ECHO;return '+';col_num += yyleng;}
"-"			{ECHO;return '-';col_num += yyleng;}
"/"			{ECHO;return '/';col_num += yyleng;}
"%"			{ECHO;return '%';col_num += yyleng;}
","			{ECHO;return ',';col_num += yyleng;} 
"&"                     		{ECHO;return '&';col_num += yyleng;}
"|"                     		{ECHO;return '|';col_num += yyleng;}
"!"                     		{ECHO;return '!';col_num += yyleng;} 

{letter}{alnum}*		{ ECHO;strcpy(key,yytext);return Iden;col_num += yyleng;} /*标识符*/
{white}+			{ECHO;col_num += yyleng;}
.			{
				printf("Invalid char %s\n",yytext);
				col_num += yyleng;
			 	return ERRORCHAR;
			}
{Annotation} 	{
				row_num += countCharacter(yytext,'\n');col_num = 1;
				}


%%

int countCharacter(const char* str, char ch) {
    int count = 0;
    
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    
    return count;
}

#ifndef yywrap
 int yywrap(){
	return 1;
}
#endif