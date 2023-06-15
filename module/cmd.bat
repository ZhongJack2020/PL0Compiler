@echo off
del cffx.exe
::del yffx.exe
del yyfx.exe

flex cffx.l
gcc lex.yy.c -o cffx

::bison yffx.y -d
::flex yffx.l
::gcc -o yffx.exe yffx.tab.c lex.yy.c

bison yyfx.y -d
flex yyfx.l
gcc -o yyfx.exe yyfx.tab.c lex.yy.c