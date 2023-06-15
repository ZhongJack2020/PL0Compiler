# grammar

```
Program ::= subProg
SubProg ::= VarDef Begin StateList End
VarDef ::= VarDef Var VarDefList | Var VarDefList
VarDefList ::= VarDefList VarList | VarList
VarList ::= VarList , Varable | Type Varable | VarList,Asign_Varable:=Expr | Type Asign_Varable:=Expr
Type ::= Integer | Real
Asign_Varable ::= Varable
Varable ::= Iden
AsignState ::= Asign_Varable:=Expr
Expr ::= Expr+Expr | Expr-Expr | Expr*Expr | Expr/Expr | Expr%Expr | (Expr) | -Expr | Varable | Const
StateList ::= Statement | Statement StateList
Statement ::= AsignState; | I_T_E ComplexState; | Wd ComplexState;
I_T_E ::= I_T ComplexState Else
I_T ::= If ( BoolExpr ) Then | If ( BoolExpr )
Wd	::= W (BoolExpr)
W	::= While
ComplexState ::= [StateList]
BoolExpr ::= Expr RelationOp Expr
BoolExpr ::= BoolExpr & BoolExpr
BoolExpr ::= BoolExpr | BoolExpr 
BoolExpr ::= !BoolExpr |(BoolExpr)
Const ::= IntNo | RealNo
RelationOp ::= < | > | = | >= | != | <=
```



