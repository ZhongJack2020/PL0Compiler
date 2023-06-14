%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXMEMBER 100

#define INTTYPE  0
#define REALTYPE 1

FILE *yyfx;  //ָ������ļ���ָ��
FILE *yffx; //ָ��yffx.txt
extern int yylex();
extern FILE* yyin;

extern char key[20];
int VarCount=0;//��������

int NXQ=0; //ָ����һ����Ҫ���ɵ���Ԫʽ

int Entry(char *name);                        //������ű���û�з�����ű���Ҫ�Ƿű�ʶ���ͳ���
int NewTemp();                                 //����Tx�����������������ű�
int Merge(int p,int q);                       //���������׺�Ϊһ�������غϲ��������ֵ
void BackPatch(int p,int t);               //����
int GEN(char* op,int a1,int a2,int re);       //������Ԫʽ    
void OutputQ();                               //�����Ԫʽ 

int FillType(int first,int type);             //���ű���first֮������Ͷ���type
int yyparse();								//�����﷨��������
int yyerror(char *errstr);

struct QUATERLIST{
	char op[6];
	int arg1;
	int arg2;
	int result;
} QuaterList[MAXMEMBER];

struct VARLIST{
	char name[20];//����
	int type;//����
	int addr;//��ַ
} VarList[MAXMEMBER];

%}

%start    ProgDef

%union 
{
    int  Iv;//��ʶ��ֵ
    int CH;//next��
    int NO;//����ֵ
    struct { int TC,FC;} _BExpr;//truelist��falselist
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
%nonassoc '<' '>' '=' LE GE NE //�޽��
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS
//��ʹ���ˣ�Prec�Ӿ�ʱ���ò���ʽ�����ȼ��ͽ�����ɣ�Prec�Ӿ����

%type <CH> ProgDef    			//���ս��
%type <CH> SubProg
%type <CH> VarDef
%type <CH> VarDefList
%type <Iv> Type                          //����
%type <First> VarList                   //����һ��var���������
%type <CH> Statement
%type <CH> StateList
%type <CH> ComplexState         //�������result
%type <_WBD> AsignState         //QUAD������ַ��CH��NXQ-1
%type <CH> I_T_E				//if then else
%type <CH> I_T                  //if then �ǲ������ʽ�ļ������
%type <_WBD> Wd                      //QUAD��while��Ԫʽ��ʼ��NXQ��CH�ǲ������ʽ�ļ���
%type <_Rop> RelationOp         //6�ֱȽϷ�
%type <_Expr> Expr 
%type <CH> W                           //while��Ԫʽ��ʼ��NXQ
%type <NO> Varable                 //������λ�ã����ű��±꣩
%type <NO> Asign_Varable      //������λ�ã����ű��±꣩
%type <_Expr> Const                //���������ͺ�λ��
%type <_BExpr>	BoolExpr      //�����ͼ���

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
//�����������ֵ��ķ�
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
			}//������������
	|  VarList ',' Asign_Varable':''='Expr//�����������Ͳ���ʼ��
			{
				FillType($3,$1);
				fprintf(yffx, "VarList ::= VarList,Asign_Varable:=Expr\n");
				if(VarList[$3].type==$6.type)
					GEN(":=",$6.place,0,$3);
				else if($6.type==INTTYPE && VarList[$3].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",$6.place,0,T);//����ת��
					GEN(":=",T,0,$3);
				}
				else if($6.type==REALTYPE && VarList[$3].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$6.place,0,T);//����ת��
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
					GEN("I->R",$5.place,0,T);//����ת��
					GEN(":=",T,0,$2);
				}
				else if($5.type==REALTYPE && VarList[$2].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$5.place,0,T);//����ת��
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
//��ֵ���
AsignState:  Asign_Varable':''='Expr  
            {
				$$.QUAD=$1;$$.CH=NXQ-1;
				fprintf(yffx, "AsignState ::= Asign_Varable:=Expr\n");
				if(VarList[$1].type==$4.type)
					GEN(":=",$4.place,0,$1);
				else if($4.type==INTTYPE && VarList[$1].type==REALTYPE)
				{
					int T=NewTemp();
					GEN("I->R",$4.place,0,T);//����ת��
					GEN(":=",T,0,$1);
				}
				else if($4.type==REALTYPE && VarList[$1].type==INTTYPE)
				{
					int T=NewTemp();
					GEN("R->I",$4.place,0,T);//����ת��
					GEN(":=",T,0,$1);
				}
			}
	;
//���ʽ
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
			GEN("I->R",$1.place,0,U);//�Ƚ�integerת����real��
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

//��䴮

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
			}//��ֵ���
	|   I_T_E ComplexState
		{
			fprintf(yffx, "Statement ::= I_T_E ComplexState;\n");
			$$=Merge($1,$2);
		}//�������
	|   Wd ComplexState   
		{ //ѭ�����
			fprintf(yffx, "Statement ::= Wd ComplexState;\n");
			GEN("j",0,0,$1.QUAD);
			/*printf("\n\nQUAD%d\n",$1.QUAD;)*/
			BackPatch($2,$1.QUAD);
			$$=$1.CH;
		}

	;
//������䣬ѭ���������嶯��
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
W	:   While{$$=NXQ;fprintf(yffx, "W	::= While\n");}//��Expr��һ��Ԫʽ��ż�¼�������Ա��ڷ�����statement�����һ����ת���˴�����Ԫʽ��
		//����BoolExpr��ʹ�õ�ǰNXQ��Statement�ĵ�һ��Ԫʽ��ţ�����TC������FC���Դ��ݸ�CH���ԣ���������ϲ��ͻ��
	;

ComplexState:	'[' StateList ']'  
				{	
					fprintf(yffx, "[StateList] \n");
					$$=$2;	
				}
	;
//�������ʽ
BoolExpr	: Expr RelationOp Expr
            {
				fprintf(yffx, "BoolExpr ::= Expr RelationOp Expr\n");
				$$.TC=NXQ;$$.FC=NXQ+1;
				GEN($2,$1.place,$3.place,0);//������NXQ����Ԫʽ���ȴ�����
				GEN("j",0,0,0);                       //������Ԫʽ���ȴ�����
			}//��·����
	| BoolExpr '&'  {BackPatch($1.TC,NXQ);}   BoolExpr
		{
			fprintf(yffx, "BoolExpr ::= BoolExpr & BoolExpr \n");
			$$.TC=$4.TC;$$.FC=Merge($1.FC,$4.FC);
		}
	| BoolExpr '|'{BackPatch($1.FC,NXQ);}  BoolExpr
		{
			fprintf(yffx, "BoolExpr ::= BoolExpr | BoolExpr \n");
			$$.FC=$4.FC;$$.TC=Merge($1.TC,$4.TC);
		}	//�����ҷ���ʱ����һ���������ʽ��TC����ڶ����������ʽ��TC�����������ʽ��FC���ϲ��������������ʽ��TC��Ϊ�ڶ����������ʽ��TC��FCΪ�ϲ����������ס�
																								//���������ʱ����һ���������ʽFC����ڶ����������ʽ��TC���������ʽ��TC���ϲ�����Ϊ�������ʽ��TC���ڶ����������ʽ��FC��Ϊ�������ʽ��FC��

	|  '!' BoolExpr   
		{
			fprintf(yffx, "BoolExpr ::= !BoolExpr \n");
			$$.TC=$2.FC;$$.FC=$2.TC;
		}  //�ǵ���������෴��
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