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

/* This array is used for determin if a identier is keyword */

char key[20]; /* this array is used to store the string of identifier or 
		  integer/real number.When one of them are abtained in yytext, 
		  copy it to key. key will be used in YACC source file
		  (YSP file filename.y) */
int id_or_keyword(char *name);/* to check out if the name is a keyword*/
%}
letter      		[A-Za-z]
alnum		[A-Za-z0-9]
d		[0-9]
white		[\t\n\040]
Annotation ("//".*)|("/*"[^("*/")]*"*/") 
%start		COMMENT
%%

\{			{ECHO;BEGIN COMMENT;} /*ECHO:存入yyout*/
<COMMENT>\}		{ECHO;BEGIN 0;}
<COMMENT>\n		{ECHO;}
<COMMENT>[^\}]+ 	{ECHO;} /*去注释*/

[Bb][eE][Gg][iI][Nn]			{ECHO;return Begin;}
[eE][Nn][Dd]			{ECHO;return End;}
[Pp][Rr][oO][Gg][Rr][Aa][Mm]		{ECHO;return Program;}
[Vv][Aa][Rr]			{ECHO;return Var;}
[Ii][nN][Tt][eE][Gg][eE][Rr]		{ECHO;return Integer;}
[Rr][eE][Aa][lL]			{ECHO;return Real;}
[Ww][Hh][Ii][Ll][Ee]			{ECHO;return While;}
[iI][Ff]				{ECHO;return If;}
[Tt][Hh][Ee][Nn]			{ECHO;return Then;}
[Ee][Ll][Ss][Ee]			{ECHO;return Else;}


({d}+(\.{d}*)?[Ee]([+-])?{d}+)|({d}*\.{d}+[Ee]([+-])?{d}+)	{ECHO;strcpy(key,yytext);return RealNo;}
{d}+\.{d}*|{d}*\.{d}+					{ECHO;strcpy(key,yytext);return RealNo;}
{d}+						{ECHO;strcpy(key,yytext);return IntNo;}


"("			{ECHO;return '(';}
")"			{ECHO;return ')';}
"["			{ECHO;return '[';}
"]"			{ECHO;return ']';}
">"			{ECHO;return '>';}
"<"			{ECHO;return '<';}
"="			{ECHO;return '=';}
"<="			{ECHO;return LE;}
">="			{ECHO;return GE;}
"!="			{ECHO;return NE;}
":"			{ECHO;return ':';}
";"			{ECHO;return ';';}
"\."			{ECHO;return '.';}
"*"			{ECHO;return '*';}
"+"			{ECHO;return '+';}
"-"			{ECHO;return '-';}
"/"			{ECHO;return '/';}
"%"			{ECHO;return '%';}
","			{ECHO;return ',';} 
"&"                     		{ECHO;return '&';}
"|"                     		{ECHO;return '|';}
"!"                     		{ECHO;return '!';} 

{letter}{alnum}*		{ ECHO;strcpy(key,yytext);return Iden;} /*标识符*/
{white}+			{ECHO;}
.			{printf("Invalid char %s\n",yytext);
			 return ERRORCHAR;
			}
{Annotation} {;}
%%


#ifndef yywrap
 int yywrap(){
	return 1;
}
#endif