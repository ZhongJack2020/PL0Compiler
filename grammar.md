# grammar

```
Program ::= subProg
SubProg ::= VarDef Begin StateList End
VarDef ::= VarDef Var VarDefList
VarDef ::= Var VarDefList
VarDefList ::= VarDefList VarList
VarDefList ::= VarList
VarList ::= VarList , Varable
VarList ::= Type Varable
VarList ::= VarList,Asign_Varable:=Expr
VarList ::= Type Asign_Varable:=Expr
Type ::= Integer
Type ::= Real
Asign_Varable ::= Varable
Varable ::= Iden
AsignState ::= Asign_Varable:=Expr
Expr ::= Expr+Expr | Expr-Expr | Expr*Expr | Expr/Expr | Expr%Expr | (Expr) | -Expr | Varable | Const
StateList ::= Statement
StateList ::= Statement StateList
Statement ::= AsignState;
Statement ::= I_T_E ComplexState;
Statement ::= Wd ComplexState;
I_T_E ::= I_T ComplexState Else
I_T ::= If ( BoolExpr ) Then
I_T ::= If ( BoolExpr )
Wd	::= W (BoolExpr)
W	::= While
ComplexState ::= [StateList]
BoolExpr ::= Expr RelationOp Expr
BoolExpr ::= BoolExpr & BoolExpr
BoolExpr ::= BoolExpr | BoolExpr 
BoolExpr ::= !BoolExpr
BoolExpr ::= (BoolExpr)
Const ::= IntNo
Const ::= RealNo
RelationOp ::= < | > | = | >= | != | <=
```



