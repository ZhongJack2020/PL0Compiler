%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXMEMBER 100

#define INTTYPE  0
#define REALTYPE 1

FILE *yyfx;  //指向输出文件的指针
FILE *yffx; //指向yffx.txt
extern int yylex();
extern FILE* yyin;

extern char key[20];
int VarCount=0;//变量个数

int NXQ=0; //指向下一个将要生成的四元式

int Entry(char *name);                        //如果符号表里没有放入符号表，主要是放标识符和常量
int NewTemp();                                 //产生Tx的随机变量并输入符号表
int Merge(int p,int q);                       //把两条链首合为一条，返回合并后的链首值
void BackPatch(int p,int t);               //回填
int GEN(char* op,int a1,int a2,int re);       //生成四元式    
void OutputQ();                               //输出四元式 

int FillType(int first,int type);             //符号表中first之后的类型都是type
int yyparse();								//调用语法分析程序
int yyerror(char *errstr);

struct QUATERLIST{
	char op[6];
	int arg1;
	int arg2;
	int result;
} QuaterList[MAXMEMBER];

struct VARLIST{
	char name[20];//名字
	int type;//类型
	int addr;//地址
} VarList[MAXMEMBER];

%}

%start    ProgDef

%union 
{
    int  Iv;//标识符值
    int CH;//next链
    int NO;//常数值
    struct { int TC,FC;} _BExpr;//truelist，falselist
    struct { int QUAD,CH;} _WBD;//while
    struct { int type,place;} _Expr;//bool
	
    char   _Rop[5];
    int      First;
    char   str[20];
}

%token    	Iden   300
%token    	IntNo	301
%token	  	RealNo    302
%token	  	Program  400

%token	  	Begin	401
%token	  	End	402
%token	  	Var	403

%token	  	Integer    404
%token	  	Real	405
%token	  	While	406
%token		If	407
%token		Then	408
%token		Else	409

%token		LE	500
%token		GE	501
%token		NE	502

/*priority*/
%left  '|'
%left  '&'
%right '!'
%nonassoc '<' '>' '=' LE GE NE //无结合
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS
//当使用了％Prec子句时，该产生式的优先级和结合性由％Prec子句决定

%type <CH> ProgDef    			//非终结符
%type <CH> SubProg
%type <CH> VarDef
%type <CH> VarDefList
%type <Iv> Type                          //类型
%type <First> VarList                   //储存一句var定义的类型
%type <CH> Statement
%type <CH> StateList
%type <CH> ComplexState         //这个语句的result
%type <_WBD> AsignState         //QUAD是语句地址，CH是NXQ-1
%type <CH> I_T_E				//if then else
%type <CH> I_T                  //if then 是布尔表达式的假链序号
%type <_WBD> Wd                      //QUAD是while四元式开始的NXQ，CH是布尔表达式的假链
%type <_Rop> RelationOp         //6种比较符
%type <_Expr> Expr 
%type <CH> W                           //while四元式开始的NXQ
%type <NO> Varable                 //变量的位置（符号表下标）
%type <NO> Asign_Varable      //变量的位置（符号表下标）
%type <_Expr> Const                //常量的类型和位置
%type <_BExpr>	BoolExpr      //真链和假链

%%
ProgDef:	SubProg
			{
				$$=0;
				fprintf(yffx, "Program ::= subProg\n");
				fprintf(yffx, "\nCompile successfully!\n");
			};

SubProg:   VarDef Begin StateList End
			{/*BackPatch($3,NXQ);*/
				GEN("Stop",0,0,0);
				fprintf(yffx, "SubProg ::= VarDef Begin StateList End\n");
			};
//变量声明部分的文法
VarDef:     VarDef Var VarDefList 
			{
				$$=0;
				fprintf(yffx, "VarDef ::= VarDef Var VarDefList\n");
			}
	|Var VarDefList 
			{
				$$=0;
				fprintf(yffx, "VarDef ::= Var VarDefList\n");
			};
VarDefList:  VarDefList VarList ';'{$$=0;fprintf(yffx, "VarDefList ::= VarDefList VarList\n");}
	|   VarList ';'{$$=0;fprintf(yffx, "VarDefList ::= VarList\n");}
	;
VarList	:  VarList ',' Varable
			{
				FillType($3,$1);
				fprintf(yffx, "VarList ::= VarList , Varable\n");
			}
	|  Type Varable
			{
				$$=$1;
				FillType($2,$$);
				fprintf(yffx, "VarList ::= Type Varable\n");
			}//声明变量类型
	|  VarList ',' Asign_Varable':''='Expr//声明变量类型并初始化
			{
				FillType($3,$1);
				fprintf(yffx, "VarList ::= VarList,Asign_Varable:=Expr\n");
				if(VarList[$3].type==$6.type)
					GEN(":=",$6.place,0,$3);
				else if($6.type==INTTYPE && VarList[$3].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",$6.place,0,T);//类型转换
					GEN(":=",T,0,$3);
				}
				else if($6.type==REALTYPE && VarList[$3].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$6.place,0,T);//类型转换
					GEN(":=",T,0,$3);
				}
			}
	|  Type  Asign_Varable':''='Expr
			{
				$$=$1;FillType($2,$$);
				fprintf(yffx, "Type Asign_Varable := Expr\n");
				if(VarList[$2].type==$5.type)
					GEN(":=",$5.place,0,$2);
				else if($5.type==INTTYPE && VarList[$2].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",$5.place,0,T);//类型转换
					GEN(":=",T,0,$2);
				}
				else if($5.type==REALTYPE && VarList[$2].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$5.place,0,T);//类型转换
					GEN(":=",T,0,$2);
				}
			}
	;
	
Type	:Integer
		{
			$$=INTTYPE;/*Type.lv=0*/
			fprintf(yffx, "Type ::= Integer\n");
		}
	|   Real
		{
			$$=REALTYPE;/*Type.lv=1*/
			fprintf(yffx, "Type ::= Real\n");
		}
	;
	

Asign_Varable:  Varable {$$=$1;fprintf(yffx, "Asign_Varable ::=Varable\n");}
	;
Varable:	Iden
			{ 
				$$=Entry(key);/*Varable.NO=VarCount*/
				fprintf(yffx, "Varable ::= Iden\n");
			}
	;
//赋值语句
AsignState:  Asign_Varable':''='Expr  
            {
				$$.QUAD=$1;$$.CH=NXQ-1;
				fprintf(yffx, "AsignState ::= Asign_Varable:=Expr\n");
				if(VarList[$1].type==$4.type)
					GEN(":=",$4.place,0,$1);
				else if($4.type==INTTYPE && VarList[$1].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",$4.place,0,T);//类型转换
					GEN(":=",T,0,$1);
				}
				else if($4.type==REALTYPE && VarList[$1].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$4.place,0,T);//类型转换
					GEN(":=",T,0,$1);
				}
			}
	;
//表达式
Expr	:   Expr'+'Expr
		{
			fprintf(yffx, "Expr ::= Expr+Expr\n");
			int T=NewTemp();
			if($1.type== INTTYPE && $3.type==INTTYPE)
			{
			GEN("Int+",$1.place,$3.place,T);
			VarList[T].type=$$.type=INTTYPE;
			}
			else if($1.type== REALTYPE && $3.type==REALTYPE)
			{
			GEN("Real+",$1.place,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
			}
			else if($1.type== INTTYPE)
			{
			int U=NewTemp();
			GEN("I->R",$1.place,0,U);//先将integer转换成real型
			GEN("Real+",U,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
			}
			else
			{
			int U=NewTemp();
			GEN("I->R",$3.place,0,U);
			GEN("Real+",$1.place,U,T);
			VarList[T].type=$$.type=REALTYPE;
			}
			$$.place=T;
		}
	|Expr'-'Expr
	{
		fprintf(yffx, "Expr ::= Expr-Expr\n");
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
		GEN("Int-",$1.place,$3.place,T);
		VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== REALTYPE && $3.type==REALTYPE)
		{
		GEN("Real-",$1.place,$3.place,T);
		VarList[T].type=$$.type=REALTYPE;
		}
		else if($1.type== INTTYPE)
		{
		int U=NewTemp();
		GEN("I->R",$1.place,0,U);
		GEN("Real-",U,$3.place,T);
		VarList[T].type=$$.type=REALTYPE;
		}
		else
		{
		int U=NewTemp();
		GEN("I->R",$3.place,0,U);
		GEN("R-",$1.place,U,T);
		VarList[T].type=$$.type=REALTYPE;
		}
		$$.place=T;
	}

	|Expr'*'Expr
	{
		fprintf(yffx, "Expr ::= Expr*Expr\n");
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
			GEN("Int*",$1.place,$3.place,T);
			VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== REALTYPE && $3.type==REALTYPE)
		{
			GEN("Real*",$1.place,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		else if($1.type== INTTYPE)
		{
			int U=NewTemp();
			GEN("I->R",$1.place,0,U);
			GEN("Real*",U,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		else
		{
			int U=NewTemp();
			GEN("I->R",$3.place,0,U);
			GEN("Real*",$1.place,U,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		$$.place=T;
	}
	|Expr'/'Expr
	{
		fprintf(yffx, "Expr ::= Expr/Expr\n");
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE){
			GEN("Int/",$1.place,$3.place,T);
			VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== REALTYPE && $3.type==REALTYPE)
		{
			GEN("Real/",$1.place,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		else if($1.type== INTTYPE)
		{
			int U=NewTemp();
			GEN("I->R",$1.place,0,U);
			GEN("Real/",U,$3.place,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		else{
			int U=NewTemp();
			GEN("I->R",$3.place,0,U);
			GEN("Real/",$1.place,U,T);
			VarList[T].type=$$.type=REALTYPE;
		}
		$$.place=T;
	}
	|Expr'%'Expr
    {
		fprintf(yffx, "Expr ::= Expr%%Expr\n");
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
			GEN("Int%",$1.place,$3.place,T);
			VarList[T].type=$$.type=INTTYPE;
			$$.place=T;
		}
	}
	|'('Expr')'
    {
		fprintf(yffx, "Expr ::= (Expr)\n");
		$$=$2;
	}
	|'-' Expr %prec UMINUS  
    {
		fprintf(yffx, "Expr ::= -Expr\n");
		int T=NewTemp();
		$$=$2;
		GEN("Minus",$2.place,0,T);
		$$.place=T;VarList[T].type=VarList[$2.place].type;
	}
	|Varable
	{
		fprintf(yffx, "Expr ::= Varable\n");
		$$.place=$1;
		$$.type=VarList[$1].type;

	}
	|Const
	{ 
		fprintf(yffx, "Expr ::= Const\n");
		$$=$1;
	}
	;

//语句串

StateList:	Statement
			{
				fprintf(yffx, "StateList ::= Statement\n");
				$$=$1;BackPatch($1,NXQ);
				fprintf(yffx, "Expr ::= Const\n");
			}
	|Statement   StateList
			{
				fprintf(yffx, "StateList ::= Statement StateList\n");
				$$=$1;BackPatch($1,NXQ);
			}
	;
Statement:   AsignState';'
			{
				$$=0;
				fprintf(yffx, "Statement ::= AsignState;\n");
			}//赋值语句
	|   I_T_E ComplexState
		{
			fprintf(yffx, "Statement ::= I_T_E ComplexState;\n");
			$$=Merge($1,$2);
		}//条件语句
	|   Wd ComplexState   
		{ //循环语句
			fprintf(yffx, "Statement ::= Wd ComplexState;\n");
			GEN("j",0,0,$1.QUAD);
			/*printf("\n\nQUAD%d\n",$1.QUAD;)*/
			BackPatch($2,$1.QUAD);
			$$=$1.CH;
		}

	;
//条件语句，循环语句的语义动作
I_T_E	:   I_T ComplexState Else
			{
				fprintf(yffx, "I_T_E ::= I_T ComplexState Else\n");
				int q=NXQ;GEN("j",0,0,0);BackPatch($1,NXQ);$$=Merge($2,q);
			}
	;
I_T	:   If '(' BoolExpr ')' Then 
		{
			fprintf(yffx, "I_T ::= If ( BoolExpr ) Then\n");
			BackPatch($3.TC,NXQ);$$=$3.FC;
		}
		|If '(' BoolExpr ')' 
		{
			fprintf(yffx, "I_T ::= If ( BoolExpr )\n");
			BackPatch($3.TC,NXQ);$$=$3.FC;
		}
	;
Wd	:   W '(' BoolExpr ')' 
		{
			fprintf(yffx, "Wd	::= W (BoolExpr) \n");
			BackPatch($3.TC,NXQ);$$.QUAD=$1;$$.CH=$3.FC;
		}
	;
W	:   While{$$=NXQ;fprintf(yffx, "W	::= While\n");}//将Expr第一四元式序号记录下来，以便在翻译完statement后产生一个跳转到此处的四元式。
		//翻译BoolExpr后使用当前NXQ（Statement的第一四元式序号）回填TC链，将FC属性传递给CH属性，方便后续合并和回填。
	;

ComplexState:	'[' StateList ']'  
				{	
					fprintf(yffx, "[StateList] \n");
					$$=$2;	
				}
	;
//布尔表达式
BoolExpr	: Expr RelationOp Expr
            {
				fprintf(yffx, "BoolExpr ::= Expr RelationOp Expr\n");
				$$.TC=NXQ;$$.FC=NXQ+1;
				GEN($2,$1.place,$3.place,0);//真链第NXQ个四元式，等待回填
				GEN("j",0,0,0);                       //假链四元式，等待回填
			}//短路处理
	| BoolExpr '&'  {BackPatch($1.TC,NXQ);}   BoolExpr
		{
			fprintf(yffx, "BoolExpr ::= BoolExpr & BoolExpr \n");
			$$.TC=$4.TC;$$.FC=Merge($1.FC,$4.FC);
		}
	| BoolExpr '|'{BackPatch($1.FC,NXQ);}  BoolExpr
		{
			fprintf(yffx, "BoolExpr ::= BoolExpr | BoolExpr \n");
			$$.FC=$4.FC;$$.TC=Merge($1.TC,$4.TC);
		}	//遇到且符号时，第一个布尔表达式的TC回填第二个布尔表达式的TC，将两个表达式的FC链合并，整个布尔表达式的TC链为第二个布尔表达式的TC，FC为合并的新链链首。
																								//遇到或符号时，第一个布尔表达式FC回填第二个布尔表达式的TC，两个表达式的TC链合并，作为整个表达式的TC，第二个布尔表达式的FC作为整个表达式的FC。

	|  '!' BoolExpr   
		{
			fprintf(yffx, "BoolExpr ::= !BoolExpr \n");
			$$.TC=$2.FC;$$.FC=$2.TC;
		}  //非的真假链是相反的
	|'(' BoolExpr ')'
		{
			fprintf(yffx, "BoolExpr ::= (BoolExpr)\n");
			$$=$2;
		}
	;
Const:IntNo
		{ 
			fprintf(yffx, "Const ::= IntNo\n");
			int i=Entry(key);
			$$.type=VarList[i].type=INTTYPE;
			$$.place=i;
		}
	|RealNo
		{ 
			fprintf(yffx, "Const ::= RealNo\n");
			int i=Entry(key);
			$$.type=VarList[i].type=REALTYPE;
			$$.place=i;
		}
	;
RelationOp:	'<'{strcpy($$,"j<");fprintf(yffx, "RelationOp ::= < \n");}
	|	'>'{strcpy($$,"j>");fprintf(yffx, "RelationOp ::= > \n");}
	|	'='{strcpy($$,"j=");fprintf(yffx, "RelationOp ::= = \n");}
	|	GE  {strcpy($$,"j>=");fprintf(yffx, "RelationOp ::= >= \n");}
	|	NE  {strcpy($$,"j!=");fprintf(yffx, "RelationOp ::= != \n");}
	|	LE  {strcpy($$,"j<=");fprintf(yffx, "RelationOp ::= <= \n");}
	;
%%

void OutputQ(void)
{
	int i;
	fprintf(yyfx,"\nQuarterList output:\n");
	for(i=0;i<NXQ;i++)
	{
		fprintf(yyfx,"%4d ( %8s, ",i,QuaterList[i].op);
		if(QuaterList[i].arg1)
			fprintf(yyfx,"%6s, ",VarList[QuaterList[i].arg1].name);
		else 
			fprintf(yyfx,"      , ");
		if(QuaterList[i].arg2)
			fprintf(yyfx,"%6s, ",VarList[QuaterList[i].arg2].name);
		else 
			fprintf(yyfx,"      , ");
		if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
			fprintf(yyfx,"%6d )\n",QuaterList[i].result);
		else if(QuaterList[i].result)
			fprintf(yyfx,"%6s )\n",VarList[QuaterList[i].result].name);
		else 
			fprintf(yyfx,"-\t )\n");
	}
	return;
}

int yyerror(char *errstr)
{
	fprintf(yffx,"%s\n",errstr);
	return 0;
}

int Entry(char *name)
{
	int i;
	for(i=1;i<=VarCount;i++) 
		if(!strcmp(name,VarList[i].name)) 
					return i;
	if(++VarCount>MAXMEMBER) 
	{
			fprintf(yffx,"Too many Variables!\n");exit(-1);
	}
	strcpy(VarList[VarCount].name,name);
	return VarCount;
}

int FillType(int first,int type)
{ 
    int i;
    for(i=first;i<=VarCount;i++)
		VarList[i].type=type;
    return i-1;
}

int Merge(int p,int q)
{
   int r;
   if(!q) 
        return p;
   else
   {
       r=q;
       while(QuaterList[r].result)
        r=QuaterList[r].result;
       QuaterList[r].result=p;
   }
   return q;
}

void BackPatch(int p,int t)
{
     int q=p;
     while(q)
     { 
           int q1=QuaterList[q].result;
           QuaterList[q].result=t;
           q=q1;
     } 
     return;
}

int GEN(char* op,int a1,int a2,int re)
{
	strcpy(QuaterList[NXQ].op,op);
	QuaterList[NXQ].arg1=a1;
	QuaterList[NXQ].arg2=a2;
	QuaterList[NXQ].result=re;
	NXQ++;
	return NXQ;
}

int NewTemp()
{
	static int no=0;
	char Tname[10];
	sprintf(Tname,"T%o",no++);
	return Entry(Tname);
}


int main(int argc, char *argv[])
{
	yyfx = fopen("D:\\Code\\Cpp\\compiler\\module\\yyfx.txt", "w+");
	yffx = fopen("D:\\Code\\Cpp\\compiler\\module\\yffx.txt", "w+");
	yyparse();
	OutputQ();
	getchar();
	return 1;
 }