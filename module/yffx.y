%{

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


FILE *fi;  //指向输出文件的指针
extern int row_num, col_num;  //行数和列数
extern char *key;


int yylex();
int yyerror(char *s);

%}

%start Program
%token IDENTIFIER CONSTANT RELOP
%token COMMA SEMI DOT LPAREN RPAREN ASSIGN MINUS COLON
%token CONST VAR PROCEDURE _BEGIN_ END IF THEN ELSE ODD WHILE DO CALL READ WRITE CASE ENDCASE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%
Program     :subProg {
                  fprintf(fi, "Program -> subProg\n");
                  printf("\nCompile successfully!\n");
            }
            ;
subProg     :DeclarePart Statement {
                  fprintf(fi, "subProg -> DeclarePart Statement\n");
            
            }
            |Statement {
                  fprintf(fi, "subProg -> Statement\n");
      
            }
            ;
DeclarePart :ConstDec {
                  fprintf(fi, "DeclarePart -> ConstDec\n");
                 
            }
            |ConstDec VarDec {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec\n");
                  
            }
            |ConstDec ProceDec {
                  fprintf(fi, "DeclarePart -> ConstDec ProceDec\n");
                  
            }
            |ConstDec VarDec ProceDec {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec ProceDec\n");
                 
            }
            |VarDec ProceDec {
                  fprintf(fi, "DeclarePart -> VarDec ProceDec\n");
                 
            } 
            |VarDec {
                  fprintf(fi, "DeclarePart -> VarDec\n");
                 
            }
            |ProceDec {
                  fprintf(fi, "DeclarePart -> ProceDec\n");
                 
            }
            // | {fprintf(fi, "DeclarePart -> ε\n");}
            ;
ConstDec    :CONST ConstDef SEMI {
                  fprintf(fi, "ConstDec -> CONST ConstDef;\n");
                  
            }
            ; 
ConstDef    :ConstDef COMMA CDefine {
                  fprintf(fi, "ConstDef -> ConstDef, CDefine\n");
                 
            }
            |CDefine {
                  fprintf(fi, "ConstDef -> CDefine\n");
                  
            }
            ;
CDefine     :IDENTIFIER RELOP CONSTANT {
                  $1 = $3; fprintf(fi, "CDefine -> IDENTIFIER = CONSTANT\n");
                 
            }
            ;
VarDec      :VAR IdentiObj SEMI {
                  fprintf(fi, "VarDec -> VAR IdentiObj;\n");
                 
            }
            ;
IdentiObj   :IdentiObj COMMA IDENTIFIER {
                  fprintf(fi, "IdentiObj -> IdentiObj, IDENTIFIER\n");
                  
            }
            |IDENTIFIER {
                  fprintf(fi, "IdentiObj -> IDENTIFIER\n");
                  
            }
            ;
ProceDec    :ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceHead subProg ProceDec;\n");
                  
            }
            |ProceDec ProceHead subProg SEMI {
                  fprintf(fi, "ProceDec -> ProceDec ProceHead subProg;\n");
                  
            }
            // | {fprintf(fp, "ProceDec -> ε\n");}
            ;
ProceHead   :PROCEDURE IDENTIFIER SEMI  {
                  fprintf(fi, "ProceHead -> PROCEDURE IDENTIFIER;\n");
                 
            }
            ;
Statement   :AssignStm {
                  fprintf(fi, "Statement -> AssignStm\n");
                  
            }
            |ComplexStm {
                  fprintf(fi, "Statement -> ComplexStm\n");
                  
            }
            |CondStm {
                  fprintf(fi, "Statement -> CondStm\n");
                  
            }
            |WhilelpStm {
                  fprintf(fi, "Statement -> WhilelpStm\n");
                  
            }
            |CaseStm {
                  fprintf(fi, "Statement -> CaseStm\n");
                 
            }
            |CallStm {
                  fprintf(fi, "Statement -> CallStm\n");
                  
            }
            |ReadStm {
                  fprintf(fi, "Statement -> ReadStm\n");
                  
            }
            |WriteStm {
                  fprintf(fi, "Statement -> WriteStm\n");
                  
            }
            // | {fprintf(fp, "Statement -> ε\n");}
            ;
AssignStm   :IDENTIFIER ASSIGN Expr {
                  $1 = $3; fprintf(fi, "AssignStm -> IDENTIFIER := Expr\n");
                  
            }
            ;
ComplexStm  :_BEGIN_ Statemt END {
                  fprintf(fi, "ComplexStm -> _BEGIN_ Statemt Statement END\n");
                  
            }
            ;
Statemt     :Statement SEMI {
                  fprintf(fi, "Statemt -> Statement;\n");
                 
            }
            |Statemt Statement SEMI {
                  fprintf(fi, "Statemt -> Statemt Statement;\n");
                 
            }
            // | {fprintf(fp, "Statemt -> ε\n");}
            ;
CondStm     :IF Condition THEN Statement %prec LOWER_THAN_ELSE {
                  fprintf(fi, "CondStm -> IF Condition THEN Statement\n");
                  
            }
            |IF Condition THEN Statement ELSE Statement {
                  fprintf(fi, "Statement -> IF Condition THEN Statement ELSE Statement\n");
                 
            }
            ;
Condition   :Expr RELOP Expr {
                  fprintf(fi, "Condition -> Expr RELOP Expr\n");
                  
            }
            |ODD Expr {
                  fprintf(fi, "Condition -> ODD Expr\n");
                  
            }
            ;
Expr        :Expr PLUS Term {
                  $$ = $1 + $3; fprintf(fi, "Expr -> Expr + Term\n");
                  
            }
            |Expr MINUS Term {
                  $$ = $1 - $3; fprintf(fi, "Expr -> Expr - Term\n");
                 
            }
            |PLUS Term {
                  $$ = $2; fprintf(fi, "Expr -> +Term\n");
                  
            }
            |MINUS Term {
                  $$ = -$2; fprintf(fi, "Expr -> -Term\n");
                  
            }
            |Term {
                  $$ = $1; fprintf(fi, "Expr -> Term\n");
                 
            }
            ;
Term        :Term TIMES Factor {
                  $$ = $1 * $3; fprintf(fi, "Term -> Term * Factor\n");
                 
            }
            |Term DIVIDE Factor {
                  $$ = $1 / $3; fprintf(fi, "Term -> Term / Factor\n");
                  
            }
            |Factor {
                  $$ = $1; fprintf(fi, "Term -> Factor\n");
                  
            }
            ;
Factor      :IDENTIFIER {
                  $$ = $1; fprintf(fi, "Factor -> IDENTIFIER\n");
                  
            }
            |CONSTANT {
                  $$ = $1; fprintf(fi, "Factor -> CONSTANT\n");
                 
            }
            |LPAREN Expr RPAREN {
                  $$ = $2; fprintf(fi, "Factor -> (Expr)\n");
                  
            }
            ;
WhilelpStm  :WHILE Condition DO Statement {
                  fprintf(fi, "WhilelpStm -> WHILE Condition DO Statement\n");
                  
            }
            ;
CaseStm     :CaseHead CaseBody ENDCASE {
                  fprintf(fi, "CaseStm -> CaseHead CaseBody ENDCASE\n");

            }
            ;
CaseHead    :CASE IDENTIFIER COLON {
                  fprintf(fi, "CaseHead -> CASE IDENTIFIER COLON\n");
                  
            }
            ;
CaseBody    :CaseBody CONSTANT COLON Statemt {
                  fprintf(fi, "CaseBody -> CaseBody CONSTANT COLON Statemt\n");
                  
            }
            |CONSTANT COLON Statemt {
                  fprintf(fi, "CaseBody -> CONSTANT COLON Statemt\n");
                  
            }
            ;
CallStm     :CALL IDENTIFIER {
                  fprintf(fi, "CallStm -> CALL IDENTIFIER\n");
                  
            }
            ;
ReadStm     :READ LPAREN IdentiObj RPAREN {
                  fprintf(fi, "ReadStm -> READ(IdentiObj)\n");
                  
            }
            ;
WriteStm    :WRITE LPAREN ExprObj RPAREN {
                  fprintf(fi, "WriteStm -> WRITE(ExprObj)\n");
                 
            }
            ;
ExprObj     :ExprObj COMMA Expr {
                  fprintf(fi, "ExprObj -> ExprObj, Expr\n");
                  
            }
            |Expr {
                  fprintf(fi, "ExprObj -> Expr\n");
            }
            ;

%%
int main(){
    fi = fopen("D:\\Code\\Cpp\\compiler\\module\\yffx.txt", "w+");
    yyparse();
    return 1;
}
int yyerror(char *s){
     fprintf(fi,"%s! (%d,%d)\n", s, row_num, col_num);
    // fprintf(stderr,"%s\n",s);
    return 1;
}



