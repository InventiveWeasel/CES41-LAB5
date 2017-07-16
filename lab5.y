%{
#include 	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
void comentario (void);
#define LT 			1
#define LE 			2
#define	GT			3
#define	GE			4
#define	EQ			5
#define	NE			6
#define PL			1
#define MI			2
#define MU			1
#define DI			2
#define RE			3

/* Definicao dos tipos de identificadores */
#define IDVOID		0
#define IDPROG		1
#define IDVAR		2
#define	IDFUNC		3
#define	IDPROC		4

/* Definicao dos tipos de passagem de parametros*/
#define PARAMVAL	1
#define PARAMREF	2

/* Definicao dos tipos de variaveis */
#define	NAOVAR		0
#define	INTEIRO		1
#define	LOGICO		2
#define	REAL		3
#define	CARACTERE	4
#define VOID		5

/* Definicao dos operadores de quadruplas */
#define	OPOR		1
#define	OPAND		2
#define OPLT 		3
#define OPLE 		4
#define	OPGT	   	5
#define	OPGE		6
#define	OPEQ		7
#define	OPNE		8
#define	OPMAIS		9
#define	OPMENOS		10
#define	OPMULTIP	11
#define	OPDIV		12
#define	OPRESTO		13
#define	OPMENUN		14
#define	OPNOT		15
#define	OPATRIB		16
#define	OPENMOD		17
#define	NOP			18
#define	OPJUMP		19
#define	OPJF		20

/* Definicoes de constantes para os tipos dos operandos */
#define	IDLEOPND	0
#define	VAROPND		1
#define	INTOPND		2
#define	REALOPND	3
#define	CHAROPND	4
#define	LOGICOPND	5
#define	CADOPND		6
#define	ROTOPND		7
#define	MODOPND		8




/* Definicao de outras constantes */
#define	NCLASSHASH	23
#define	VERDADE		1
#define	FALSO		0
#define MAXDIMS		10

/* Strings para nomes dos tipos de identificadores*/
char *nometipid[5] = {" ", "IDPROG", "IDVAR", "IDFUNC", "IDPROC"};

/* Strings para nomes dos tipos de variaveis */
char *nometipvar[6]={"NAOVAR", "INTEIRO", "LOGICO", "REAL", "CARACTERE", "VOID"};

/* Strings para operadores de quadruplas */

char *nomeoperquad[21] = {"",
	"OR", "AND", "LT", "LE", "GT", "GE", "EQ", "NE", "MAIS",
	"MENOS", "MULT", "DIV", "RESTO", "MENUN", "NOT", "ATRIB",
	"OPENMOD", "NOP", "JUMP", "JF"
};

/*
	Strings para tipos de operandos de quadruplas
 */

char *nometipoopndquad[9] = {"IDLE",
	"VAR", "INT", "REAL", "CARAC", "LOGIC", "CADEIA", "ROTULO", "MODULO"
};

/* Declaracoes para a tabela de simbolos */
typedef struct celsimb celsimb;
typedef celsimb *simbolo;
typedef struct elemlistsimb elemlistsimb;
typedef elemlistsimb *listsimb;
struct celsimb {
	char *cadeia;
	int tid, tvar, tparam, ndims, dims[MAXDIMS+1], nparams;
	char inic, ref, array, param;
	simbolo escopo, prox;
	listsimb listvar, listparam, listfunc;
};
struct elemlistsimb {
	simbolo simb;
	listsimb prox;
};

/* Lista de tipos */
typedef struct celtiponoh celtiponoh;
typedef celtiponoh *tiponoh;
struct celtiponoh{
	int tipo;
	tiponoh prox;
};
tiponoh listatipos;

typedef struct celquad celquad; 
typedef celquad *quadrupla; 

typedef struct celmodhead celmodhead;
typedef celmodhead *modhead; 

/* Union para atributo de um operando */
typedef union atribopnd atribopnd; 
union atribopnd {
	simbolo simb; 
	int valint; 
	float valfloat;
	char valchar;
	char vallogic;
	char *valcad;
	quadrupla rotulo; 
	modhead modulo;
};

/* Struct de um operando */
typedef struct operando operando; 
struct operando{
	int tipo;
	atribopnd atr;
};

/* Struct de uma quadrupla */
struct celquad{
	int num;
	int oper;
	operando opnd1, opnd2, result;
	quadrupla prox;
};


/* Struct de um cabecalho de modulo */
struct celmodhead {
	simbolo modname; modhead prox;
	int modtip;
	quadrupla listquad;
};

/* Declaracoes para atributos de expressoes e variaveis */
typedef struct infoexpressao infoexpressao;
struct infoexpressao { 
	int tipo;
	operando opnd; 
};

typedef struct infovariavel infovariavel;
struct infovariavel {
	simbolo simb;
	operando opnd; 
};

/* Variaveis globais para a tabela de simbolos e analise semantica */
simbolo tabsimb[NCLASSHASH];
simbolo simb;
simbolo escopo, escglobal;
int tipocorrente;
int declparam;

/* Variaveis globais para o manuseio das quadruplas */
quadrupla quadcorrente, quadaux;
modhead codintermed, modcorrente;
int oper, numquadcorrente;
operando opnd1, opnd2, result, opndaux;
int numtemp;
const operando opndidle = {IDLEOPND, 0};


/* Prototipos das funcoes para a tabela de simbolos e analise semantica */
void InicTabSimb(void);
void ImprimeTabSimb(void);
simbolo InsereSimb(char *,int,int,simbolo);
int hash(char *);
simbolo ProcuraSimb(char *,simbolo);
void DeclaracaoRepetida(char *);
void TipoInadequado(char *);
void NaoDeclarado(char *);
void VerificaInicRef(void);
void Incompatibilidade(char *);
void Esperado(char *);
void NaoEsperado(char *);
void ErroLinguagem(char *);
void ErroInterno(char *);
void AdicionarListaTipo(int);
void LimparListaTipos(void);
void VerificarParams(listsimb);
void VerificarCompatibilidade(const char *, int, int);
void VerificarFuncao(char *, int);

/* Prototipos das funcoes para o codigo intermediario */
void InicCodIntermed (void);
void InicCodIntermMod (simbolo);
quadrupla GeraQuadrupla (int, operando, operando, 	operando);
simbolo NovaTemp (int);
void ImprimeQuadruplas (void);
void RenumQuadruplas (quadrupla, quadrupla);


int tab = 0;
void tabular (void);
%}
%union {
	char string[50];
	int atr, valint;
	float valreal;
	char carac;
	infoexpressao infoexpr;
	infovariavel infovar;
	simbolo simb;
	int tipoexpr;
	int nsubscr;
	int nparams;
	quadrupla quad;
}
%type	<infovar>	Variable
%type	<infoexpr>	Expression  AuxExpr1  AuxExpr2  AuxExpr3  AuxExpr4  Term  Factor
%type	<nsubscr>	SubscrList
%type	<nparams>	ExprList
%type 	<tipoexpr>	FuncCall
%token 				CALL
%token 				CHAR
%Token 				ELSE
%token				FALSE
%token 				FLOAT
%token 				FOR
%token 				FUNCTION
%token 				IF
%token 				INT
%token 				LOGIC
%token 				PROCEDURE
%token 				PROGRAM
%token 				READ
%token 				REPEAT
%token 				RETURN
%token 				TRUE
%token 				VAR
%token 				WHILE
%token 				WRITE
%token	<string>	ID
%token	<valint>	INTCT
%token	<string>	CHARCT
%token	<valreal>	FLOATCT
%token	<string>	STRING
%token				OR
%token				AND
%token				NOT
%token	<atr>		RELOP
%token	<atr>		ADOP
%token	<atr>		MULTOP
%token				NEG
%token				OPPAR
%token				CLPAR
%token				OPBRAK
%token				CLBRAK
%token				OPBRACE
%token				CLBRACE
%token				SCOLON 
%token				COMMA
%token				ASSIGN
%token	<carac>		INVAL
%nonassoc 			LOWER_THAN_ELSE
%nonassoc 			ELSE
%%
Prog			:  {
					InicTabSimb (); InicCodIntermed (); numtemp = 0;
				}
					PROGRAM ID SCOLON
				{
					InicTabSimb();
					listatipos = NULL;
					declparam = FALSO;
					printf("program %s;\n\n", $3);
					simb = escglobal = escopo = InsereSimb($3, IDPROG, NAOVAR, NULL);
					InicCodIntermMod (simb);
					opnd1.tipo = MODOPND;
					opnd1.atr.modulo = modcorrente;
					GeraQuadrupla (OPENMOD, opnd1, opndidle, opndidle);

				}
				   Decls  SubProgs  CompStat
				{
					VerificaInicRef();
					ImprimeTabSimb();
					ImprimeQuadruplas ();
				}
				;
Decls 			:	
				|  VAR {printf("var\n"); tab++; } DeclList {tab--;}
				;
DeclList		:  Declaration
				|  DeclList  Declaration
				;
Declaration 	:  Type ElemList SCOLON {printf(";\n");} 
				;
Type			:  INT {tabular(); printf("int "); tipocorrente = INTEIRO;}
				|  FLOAT {tabular(); printf("float "); tipocorrente = REAL;}
				|  CHAR {tabular(); printf("char "); tipocorrente = CARACTERE;}
				|  LOGIC {tabular(); printf("logic ");  tipocorrente = LOGICO;}
				;
ElemList    	:  Elem
				|  ElemList COMMA {printf(", ");} Elem
				;
Elem        	:  ID 
				{
					printf("%s", $1);
					if(ProcuraSimb($1, escopo) != NULL)
						DeclaracaoRepetida($1);
					else{
						simb = InsereSimb($1, IDVAR, tipocorrente, escopo);
						simb->array=FALSO;
						simb->ndims=0;
					}
				}  DimList
				;
DimList	    	: 
				|  DimList  Dim  {simb->array=VERDADE;}
				;
Dim				:  OPBRAK INTCT CLBRAK 
				{
					printf("[%d]", $2);
					if($2<=0)
						Esperado("Valor inteiro positivo");
					simb->ndims++;
					simb->dims[simb->ndims]=$2;
				}
				;
SubProgs	    :
				|  SubProgs  SubProgDecl
				;
SubProgDecl   	:  Header  Decls  CompStat
				{
					escopo = escopo->escopo;
					if (escopo == NULL) printf("Erro, escopo voltou demais\n");
				}
				;
Header   		:  FuncHeader
				|  ProcHeader
				;
FuncHeader		:  FUNCTION {tabular(); printf("function ");} Type ID OPPAR
				{
					printf("%s(", $4);
					if (ProcuraSimb($4, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb($4, IDFUNC, tipocorrente, escopo);
				}
				   FuncHeaderAux
				;
FuncHeaderAux	:  CLPAR  SCOLON {printf(");\n");}
				|  ParamList  CLPAR  SCOLON {printf(");\n");}
				;
ProcHeader  	:  PROCEDURE ID OPPAR 
				{
					tabular();
					printf("procedure %s(", $2);
					if (ProcuraSimb($2, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb($2, IDPROC, NAOVAR, escopo);
				}
				   CLPAR SCOLON {printf(");\n");}
				|  PROCEDURE ID OPPAR
				{
					tabular();
					printf("procedure %s(", $2);
					escopo = simb = InsereSimb($2, IDPROC, NAOVAR, escopo);
				}
				   ParamList CLPAR SCOLON {printf(");\n");}
				;
ParamList   	:  Parameter
				|  ParamList  COMMA {printf(", ");} Parameter
				;
Parameter   	:  Type ID
				{
					printf("%s", $2);
					declparam = VERDADE;
					simbolo s = ProcuraSimb($2, escglobal);
					if (s != NULL && (s->tid == IDFUNC || s->tid == IDFUNC)){
						ErroLinguagem("Subprograma nao pode ser usado como parametro.");
					}
					InsereSimb($2, IDVAR, tipocorrente, escopo);
					declparam = FALSO;
				}
				;
CompStat		:  OPBRACE
				{
					tabular();
					printf("\{\n");
					tab++;
				}
				   StatList  CLBRACE
				{
					tab--;
					tabular();
					printf("}\n");
				}
				;
StatList		:
				|  StatList  Statement
				;
Statement   	:  CompStat  |  IfStat  |  WhileStat  |  RepeatStat
            	|  ForStat  |  ReadStat  |  WriteStat  |  AssignStat
            	|  CallStat  |  ReturnStat  |  SCOLON {printf(";\n");}
				;
IfStat			:  IF OPPAR {tabular(); printf("if("); tab++;} Expression  CLPAR
				{
					printf(")\n");
					if($4.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'if' deve ser logica");
					opndaux.tipo = ROTOPND;
					$<quad>$ = GeraQuadrupla(OPJF, $4.opnd, opndidle, opndaux);
				}
					Statement 
				{
					tab--;
					$<quad>$ = quadcorrente;
					$<quad>6->result.atr.rotulo = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				} 
					ElseStat
				{
					if ($<quad>8->prox != quadcorrente) {
						quadaux = $<quad>8->prox;
						$<quad>8->prox = quadaux->prox;
						quadaux->prox = $<quad>8->prox->prox;
						$<quad>8->prox->prox = quadaux;
						RenumQuadruplas ($<quad>8, quadcorrente);
					}
				}
				;
ElseStat		:  
				|  	ELSE 
				{	
					tabular();
					printf("else\n");
					tab++;
					opndaux.tipo = ROTOPND;
					$<quad>$ = GeraQuadrupla (OPJUMP, opndidle, opndidle, opndaux);

				} 
					Statement 
				{
					tab--;
					$<quad>2->result.atr.rotulo = GeraQuadrupla (NOP, opndidle, opndidle, opndidle);
				}
				;
WhileStat   	:  WHILE OPPAR 
				{
					tabular(); 
					printf("while(");
					$<quad>$ = GeraQuadrupla(NOP, opndidle,opndidle,opndidle);
				} 
					Expression CLPAR {printf(")\n");} 
				{
					if($4.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'while' deve ser logica");
					opndaux.tipo = ROTOPND;
					$<quad>$ = GeraQuadrupla(OPJF, opndidle, opndidle, opndaux);
				}
					Statement
				{
					opndaux.tipo = ROTOPND;
					$<quad>$ = GeraQuadrupla(OPJUMP, opndidle,opndidle,opndaux);
					$<quad>$->result.atr.rotulo = $<quad>3;
					$<quad>7->result.atr.rotulo = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				}
				;
RepeatStat  	:  REPEAT {tabular(); printf("repeat\n");} Statement  WHILE OPPAR {tabular(); printf("while(");} Expression CLPAR SCOLON {printf(");\n");}
				{
					if($7.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'do repeat' deve ser logica");
				}
				;
ForStat	    	:  FOR OPPAR {tabular(); printf("for(");} Variable ASSIGN {printf(" = ");} Expression SCOLON 
				{
					printf("; ");
					if ($4.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						$4.simb->inic = VERDADE;
						if($4.simb->tid!=IDVAR || ($4.simb->tvar!=INTEIRO && $4.simb->tvar!=CARACTERE) || $4.simb->array!=FALSO)
							Incompatibilidade("Variavel de inicializacao incompativel para o operador 'for'");
					}
				}
					Expression SCOLON {printf("; ");} Variable ASSIGN {printf(" = ");} Expression  CLPAR
				{
					printf(")\n");
					if ($4.simb == NULL || $13.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						$13.simb->inic = VERDADE;
						if(strcmp($4.simb->cadeia, $13.simb->cadeia))
							Incompatibilidade("Variavel de atualizacao deve ser a mesma de inicializacao");
						if(($7.tipo != INTEIRO && $7.tipo != CARACTERE) || ($16.tipo != INTEIRO && $16.tipo != CARACTERE) || $10.tipo!=LOGICO)
							Incompatibilidade("Expressoes de tipo inadequado");
					}
				} Statement
				;
ReadStat   		:  READ OPPAR {tabular(); printf("read(");} ReadList CLPAR SCOLON {printf(");\n");}
				;
ReadList		:  Variable
				|  ReadList COMMA {printf(", ");} Variable
				;
WriteStat   	:  WRITE OPPAR {tabular(); printf("write(");} WriteList CLPAR SCOLON {printf(");\n");}
				;
WriteList		:  WriteElem
				|  WriteList COMMA {printf(", ");} WriteElem
				;
WriteElem		:  STRING {printf("\"%s\"", $1);}
				|  Expression  
				;
CallStat    	:  CALL ID OPPAR {tabular(); printf("call %s();\n", $2); VerificarFuncao($2, 0);} CLPAR SCOLON
				|  CALL ID OPPAR
				{
					tabular();
					printf("call %s(", $2);
				}
				   ExprList CLPAR SCOLON {printf(");\n"); VerificarFuncao($2, $5);}
				;
ReturnStat  	:  RETURN {tabular(); printf("return");} SCOLON
				{
					printf(";\n");
					if (escopo->tid != IDPROG && escopo->tid != IDPROC)
						Incompatibilidade("Tipo de retorno nao deveria ser void");
				}
				|  RETURN {tabular(); printf("return ");} Expression SCOLON
				{
					printf(";\n");
					if (escopo->tid != IDFUNC)
						Incompatibilidade("Retorno de nao funcao nao deve ter tipo");
					VerificarCompatibilidade("return", escopo->tvar, $3.tipo);
				}
				;
AssignStat  	: {tabular();} Variable ASSIGN {printf(" = ");} Expression SCOLON {printf(";\n");}
				{
					if ($2.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						$2.simb->inic = VERDADE;
						if($2.simb->tvar == NAOVAR || $2.simb->tid != IDVAR)
							Esperado("Esperada uma variavel inteira, caractere, real ou logica para atribuicao.");
						VerificarCompatibilidade("assign", $2.simb->tvar, $5.tipo);
						GeraQuadrupla(OPATRIB,$5.opnd,opndidle,$2.opnd);
					}
				}
				;
ExprList		:  Expression {$$=1; AdicionarListaTipo($1.tipo);}
				|  ExprList COMMA {printf(", ");} Expression {$$=$1+1;  AdicionarListaTipo($4.tipo);}
				;
Expression  	:  AuxExpr1
				|  Expression OR {printf(" || ");} AuxExpr1
				{
					if($1.tipo!=LOGICO || $4.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$.tipo=LOGICO;
					$$.opnd.tipo = VAROPND;  
					$$.opnd.atr.simb = NovaTemp ($$.tipo);
					GeraQuadrupla (OPOR, $1.opnd, $4.opnd, $$.opnd);
				}
				;
AuxExpr1    	:  AuxExpr2
				|  AuxExpr1 AND {printf(" && ");} AuxExpr2
				{
					if($1.tipo!=LOGICO || $4.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$.tipo=LOGICO;
					$$.opnd.tipo = VAROPND;  
					$$.opnd.atr.simb = NovaTemp ($$.tipo);
					GeraQuadrupla (OPAND, $1.opnd, $4.opnd, $$.opnd);
				}
				;
AuxExpr2    	:  AuxExpr3
				|  NOT {printf("!");} AuxExpr3
				{
					if($3.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					$$.tipo=LOGICO;
					$$.opnd.tipo = VAROPND;  
					$$.opnd.atr.simb = NovaTemp ($$.tipo);
					GeraQuadrupla (OPNOT, $3.opnd, opndidle, $$.opnd);

				}
				;
AuxExpr3    	:  AuxExpr4	
				|  AuxExpr4  RELOP
				{
					switch($2){
						case LT: printf(" < "); break;
						case LE: printf(" <= "); break;
						case GT: printf(" > "); break;
						case GE: printf(" >= "); break;
						case EQ: printf(" == "); break;
						case NE: printf(" != "); break;
					}
				}
				AuxExpr4
				{
					switch($2){
						case LT:
						case LE:
						case GT:
						case GE:
							if(($1.tipo!=INTEIRO && $1.tipo!=REAL && $1.tipo!=CARACTERE)
								|| ($4.tipo!=INTEIRO && $4.tipo!=REAL && $4.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador relacional");
							break;
						case EQ:
						case NE:
							//Se for logico, o outro operando também deve ser
							if($1.tipo == LOGICO && $4.tipo != LOGICO || $1.tipo != LOGICO && $4.tipo == LOGICO)
								Incompatibilidade("Operador improprio para operador relacional");
							break;
						default:
							break;
					}
					$$.tipo=LOGICO;
					/* criando quadrupla */
					$$.opnd.tipo = VAROPND;  
					$$.opnd.atr.simb = NovaTemp ($$.tipo);
					switch($2){
						case LT: GeraQuadrupla(OPLT, $1.opnd, $4.opnd, $$.opnd); break;
						case LE: GeraQuadrupla(OPLE, $1.opnd, $4.opnd, $$.opnd); break;
						case GT: GeraQuadrupla(OPGT, $1.opnd, $4.opnd, $$.opnd); break;
						case GE: GeraQuadrupla(OPGE, $1.opnd, $4.opnd, $$.opnd); break;
						case EQ: GeraQuadrupla(OPEQ, $1.opnd, $4.opnd, $$.opnd); break;
						case NE: GeraQuadrupla(OPNE, $1.opnd, $4.opnd, $$.opnd); break;
					}

				}
				;
AuxExpr4    	:  Term
				|  AuxExpr4  ADOP
				{
					switch($2){
						case PL: printf(" + "); break;
						case MI: printf(" - "); break;
					}
				}
				Term
				{
					if(($1.tipo!=INTEIRO && $1.tipo!=REAL && $1.tipo!=CARACTERE)
						|| ($4.tipo!=INTEIRO && $4.tipo!=REAL && $4.tipo!=CARACTERE))
						Incompatibilidade("Operando improprio para operador aritmetico");
					if($1.tipo==REAL || $4.tipo==REAL)
						$$.tipo=REAL;
					else
						$$.tipo=INTEIRO;
					$$.opnd.tipo = VAROPND;
					$$.opnd.atr.simb = NovaTemp($$.tipo);
					switch($2){
						case PL: GeraQuadrupla(OPMAIS, $1.opnd, $4.opnd, $$.opnd); break;
						case MI: GeraQuadrupla(OPMENOS, $1.opnd, $4.opnd, $$.opnd); break;
					}
				}
				;
Term  	    	:  Factor
				|  Term  MULTOP 
				{
					switch($2){
						case MU: printf(" * "); break;
						case DI: printf(" / "); break;
						case RE: printf(" %% "); break;
					}
				}
				Factor
				{
					switch($2){
						case MU:
						case DI:
							if(($1.tipo!=INTEIRO && $1.tipo!=REAL && $1.tipo!=CARACTERE)
								|| ($4.tipo!=INTEIRO && $4.tipo!=REAL && $4.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador aritmetico");
							if($1.tipo==REAL || $4.tipo==REAL) $$.tipo=REAL;
							else $$.tipo=INTEIRO;
							$$.opnd.tipo = VAROPND;
							$$.opnd.atr.simb = NovaTemp($$.tipo);
							if($2 == MU)
								GeraQuadrupla(OPMULTIP, $1.opnd, $4.opnd, $$.opnd);
							else
								GeraQuadrupla(OPDIV, $1.opnd, $4.opnd, $$.opnd);
							break;
						case RE:
							if(($1.tipo!=INTEIRO && $1.tipo!=CARACTERE) || ($4.tipo!=INTEIRO && $4.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador resto");
							$$.tipo=INTEIRO;
							$$.opnd.tipo = VAROPND;
							$$.opnd.atr.simb = NovaTemp($$.tipo);
							GeraQuadrupla(OPRESTO, $1.opnd, $4.opnd, $$.opnd);
							break;
						default:
							break;
					}
				}
				;
Factor			:  Variable
				{
					if($1.simb != NULL) {
						$1.simb->ref = VERDADE;
						$$.tipo = $1.simb->tvar;
						$$.opnd = $1.opnd;
					}
				}
				|  INTCT 
					{
						printf("%d", $1); $$.tipo = INTEIRO;
						$$.opnd.tipo = INTOPND;
						$$.opnd.atr.valint = $1;
					}
				|  FLOATCT 
					{
						printf("%g", $1); $$.tipo = REAL;
						$$.opnd.tipo = REALOPND;
						$$.opnd.atr.valfloat = $1;
					}
				|  CHARCT 
					{
						printf("\'%s\'", $1);
						$$.tipo = CARACTERE;
						$$.opnd.tipo = CHAROPND;
						$$.opnd.atr.valchar = $1;
					}
            	|  TRUE 
					{
						printf("true");
						$$.tipo = LOGICO;
						$$.opnd.tipo = LOGICOPND;
						$$.opnd.atr.vallogic = 1;
					}
				|  FALSE 
					{
						printf("false"); 
						$$.tipo = LOGICO;
						$$.opnd.tipo = LOGICOPND;
						$$.opnd.atr.vallogic = 0;
					}
				|  NEG {printf("~");} Factor 
				{
					if($3.tipo != INTEIRO && $3.tipo!= REAL && $3.tipo!=CARACTERE)
						Incompatibilidade("Operando improprio para menos unario");
					if($3.tipo == REAL)
						$$.tipo = REAL;
					else
						$$.tipo = INTEIRO;
					$$.opnd.tipo = VAROPND;
					$$.opnd.atr.simb = NovaTemp($$.tipo);
					GeraQuadrupla  (OPMENUN, $3.opnd, opndidle, $$.opnd);
					

				}
            	|  OPPAR {printf("(");} Expression  CLPAR
					{
						printf(")");
						$$.tipo=$3.tipo;
						$$.opnd = $3.opnd;
					}
				|  FuncCall {$$.tipo = $1;}
				;
Variable		:  ID
				{
					printf("%s", $1);
					simbolo escaux = escopo;
					simb = ProcuraSimb($1, escaux);
					while(escaux != NULL && simb == NULL) {
						escaux = escaux->escopo;
						if (escaux != NULL)
							simb = ProcuraSimb($1, escaux);
					}
					if(simb == NULL) 
						NaoDeclarado($1); 
					else if(simb->tid != IDVAR)
						TipoInadequado($1);
					$<simb>$ = simb;
				} 
				   SubscrList 
				{
					$$.simb = $<simb>2;
					if($$.simb != NULL) {
						if($$.simb->array == FALSO && $3>0)
							NaoEsperado("Subscrito\(s)");
						else if($$.simb->array==VERDADE && $3==0)
							Esperado("subscrito\(s)");
						else if($3!=$$.simb->ndims)
							Incompatibilidade("Numero de subscritos incompativel com o declarado");
						$$.opnd.tipo = VAROPND;
						if($3 == 0)
							$$.opnd.atr.simb = $$.simb;
					}
				}  
				;
SubscrList  	:  {$$=0;}
				|  SubscrList  Subscript  {$$=$1+1;}
				;
Subscript		:  OPBRAK {printf("[");} AuxExpr4  CLBRAK {printf("]");}
				{
					if($3.tipo!=INTEIRO && $3.tipo!=CARACTERE)
						Incompatibilidade("Tipo inadequado para subscrito");
				}
				;
FuncCall    	:  ID OPPAR {printf("%s()", $1);} CLPAR
				{
					simbolo s = ProcuraSimb($1, escglobal);
					VerificarFuncao($1, 0);
					if (s == NULL)
						$$ = NAOVAR;
					else $$ = s->tvar;
				}
				|  ID OPPAR {printf("%s(", $1);} ExprList CLPAR
				{
					printf(")");
					VerificarFuncao($1, $4);
					simbolo s = ProcuraSimb($1, escglobal);
					if (s == NULL)
						$$ = NAOVAR;
					else $$ = s->tvar;
				}
				;
%%
#include "lex.yy.c"

/* Inicializa a tabela de simbolos */
void InicTabSimb(){
	int i;
	for(i=0;i<NCLASSHASH;i++)
		tabsimb[i] = NULL;
}

/*
	ProcuraSimb(cadeia, escopo): Procura cadeia e escopo na tabela de simbolos;
	Caso ela ali esteja, retorna um ponteiro para a sua celula;
	Caso contrário, retorna NULL.

*/
simbolo ProcuraSimb (char *cadeia, simbolo escopo) {
	simbolo s; int i;
	i = hash (cadeia);
	for (s = tabsimb[i]; (s != NULL) && (strcmp(cadeia, s->cadeia) != 0 || (escopo != s->escopo)); s = s->prox);
	return s;
}

/*
	InsereListSimb(simbolo, listsimb*): Insere
	simbolo numa lista de simbolos
 */
 
void InsereListSimb(simbolo simb, listsimb *lista) {
	listsimb l = (listsimb) malloc (sizeof (elemlistsimb));
	l->simb = simb;
	l->prox = *lista;
	*lista = l;
}

/*
	InsereSimb (cadeia, tid, tvar, escopo): Insere cadeia na tabela de
	simbolos, com tid como tipo de identificador, com tvar como
	tipo de variavel e com escopo como escopo; Retorna um ponteiro para a celula inserida
 */

simbolo InsereSimb (char *cadeia, int tid, int tvar, simbolo escopo) {
	int i; simbolo aux, s;
	i = hash (cadeia); aux = tabsimb[i];
	s = tabsimb[i] = (simbolo) malloc (sizeof (celsimb));
	s->cadeia = (char*) malloc ((strlen(cadeia)+1) * sizeof(char));
	strcpy (s->cadeia, cadeia);
	s->tid = tid;		s->tvar = tvar;
	s->nparams = s->ndims = 0;
	s->listfunc = s->listparam = s->listvar = NULL;
	s->escopo = escopo;
	s->prox = aux;
	if (declparam) {
		s->inic = s->ref = s->param = VERDADE;
		if (s->tid == IDVAR)
			InsereListSimb(s, &escopo->listparam);
		s->escopo->nparams++;
	}
	else {
		s->inic = s->ref = s->param = FALSO;
		if (s->tid == IDVAR)
			InsereListSimb(s, &escopo->listvar);
	}
	if (tid == IDFUNC || tid == IDPROC) {
		InsereListSimb(s, &escopo->listfunc);
	}
	return s;
}

/*
	hash (cadeia): funcao que determina e retorna a classe
	de cadeia na tabela de simbolos implementada por hashing
 */

int hash (char *cadeia) {
	int i, h;
	for (h = i = 0; cadeia[i]; i++) {h += cadeia[i];}
	h = h % NCLASSHASH;
	return h;
}

/* ImprimeTabSimb: Imprime todo o conteudo da tabela de simbolos  */

void ImprimeTabSimb () {
	int i, j; simbolo s;
	printf ("\n\n   TABELA  DE  SIMBOLOS:\n\n");
	for (i = 0; i < NCLASSHASH; i++)
		if (tabsimb[i]) {
			printf ("Classe %d:\n", i);
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				printf ("  %s(%s %s), escopo: ", s->cadeia,  nometipid[s->tid],  nometipvar[s->tvar]);
				if (s->escopo == NULL) printf("null\n");
				else printf("%s\n", s->escopo->cadeia);
				if (s->listparam != NULL) {
					printf("\tParametros (%d): ", s->nparams);
					listsimb l = s->listparam;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->listfunc != NULL) {
					printf("\tFuncoes: ");
					listsimb l = s->listfunc;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->listvar != NULL) {
					printf("\tVariaveis: ");
					listsimb l = s->listvar;
					while(l != NULL) {
						printf(" %s(%s)", l->simb->cadeia, nometipvar[l->simb->tvar]);
						l = l->prox;
					}
					printf("\n");
				}
				if (s->tid == IDVAR){
					printf ("\tInicializado: %d, Referenciado: %d\n", s->inic, s->ref);
					if(s->array == VERDADE){
						printf("\tArray: (%d dimensoes):", s->ndims);
						for(j=1; j <= s->ndims; j++)
							printf(" %d", s->dims[j]);
						printf("\n");
					}
				}
				printf("\n");
			}
		}
}

void VerificaInicRef(){
	int i;
	simbolo s;
	for (i = 0; i < NCLASSHASH; i++) {
		if (tabsimb[i]) {
			for (s = tabsimb[i]; s!=NULL; s = s->prox){
				if(s->tid == IDVAR){
					if(s->ref == FALSO)
						printf("%s do escopo %s nao referenciado\n", s->cadeia, s->escopo->cadeia);
					if(s->inic == FALSO)
						printf("%s do escopo %s nao inicializado\n", s->cadeia, s->escopo->cadeia);
				}
			}
		}
	}
	
}

void AdicionarListaTipo(int tipo) {
	tiponoh n = (tiponoh) malloc (sizeof (celtiponoh));
	n->tipo = tipo;
	n->prox = listatipos;
	listatipos = n;
}

void LimparListaTipos(){
	tiponoh n;
	while(listatipos != NULL) {
		n = listatipos;
		listatipos = listatipos->prox;
		free(n);
	}
}

void VerificarCompatibilidade(const char *mensagem, int tipo1, int tipo2) {
	char buffer[200];
	buffer[0] = 0;
	if(tipo1==INTEIRO && (tipo2!=INTEIRO && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de inteiro: esperado inteiro ou caractere.", mensagem);
	else if(tipo1==REAL && (tipo2!=INTEIRO && tipo2!=REAL && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de real: esperado real, inteiro ou caractere.", mensagem);
	else if(tipo1==CARACTERE && (tipo2!=INTEIRO && tipo2!= CARACTERE))
		sprintf(buffer, "[%s] Compatibilidade de caractere: esperado inteiro ou caractere.", mensagem);
	else if(tipo1==LOGICO && tipo2!=LOGICO)
		sprintf(buffer, "[%s] Compatibilidade de logico: esperado logico.", mensagem);
	if (buffer[0] != 0)
		Incompatibilidade(buffer);
}

void VerificarParams(listsimb p) {
	tiponoh q = listatipos;
	while(q != NULL && p != NULL){
		VerificarCompatibilidade("param", p->simb->tvar, q->tipo);
		q = q->prox;
		p = p->prox;
	}
	if (p != NULL || q != NULL)
		ErroInterno("Erro interno de logica do compilador.");
}

void VerificarFuncao(char * id, int nparams) {
	simbolo s = ProcuraSimb(id, escglobal);
	if (s == NULL) {
		NaoDeclarado("Funcao ou procedimento nao declarado.");
		return;
	}
	simbolo escaux = escopo;
	while(escaux != NULL) {
		if (strcmp(escaux->cadeia, id) == 0)
			ErroLinguagem("Proibida recursividade.");
		escaux = escaux->escopo;
	}
	if(s->tid != IDFUNC && s->tid != IDPROC){
		NaoEsperado("Esperava identificador de funcao.");
	}
	else if(s->nparams != nparams) {
		Incompatibilidade("Quantidade de parametros nao compativel.");
	}
	else {
		VerificarParams(s->listparam);
	}
	LimparListaTipos();
}

/* Funcoes do codigo intermediario */

/* Inicia o modulo lider de todo o programa */
void InicCodIntermed () {
	codintermed = malloc (sizeof (celmodhead));
	modcorrente = codintermed;
   	modcorrente->listquad = NULL;
	modcorrente->prox = NULL;
}

/* Cria um modulo de codigo intermediario (processo, funcao ou programa) */
void InicCodIntermMod (simbolo simb) {
	modcorrente->prox = malloc (sizeof (celmodhead));
	modcorrente = modcorrente->prox;
	modcorrente->prox = NULL;
	modcorrente->modname = simb;
	modcorrente->modtip = simb->tid;
	modcorrente->listquad = malloc (sizeof (celquad));
	quadcorrente = modcorrente->listquad;
	quadcorrente->prox = NULL;
	numquadcorrente = 0;
	quadcorrente->num = numquadcorrente;
}

quadrupla GeraQuadrupla (int oper, operando opnd1, operando opnd2, operando result) {
	quadcorrente->prox = malloc (sizeof (celquad));
	quadcorrente = quadcorrente->prox;
	quadcorrente->oper = oper;
	quadcorrente->opnd1 = opnd1;
	quadcorrente->opnd2 = opnd2;
	quadcorrente->result = result;
	quadcorrente->prox = NULL;
	numquadcorrente ++;
   	quadcorrente->num = numquadcorrente;
   	return quadcorrente;
}

/* ###### Verificar insercao de simbolo temporario ###### */
/* Gera um nome para uma nova variavel temporaria ##XX */
simbolo NovaTemp (int tip) {
	simbolo simb; int temp, i, j;
	char nometemp[10] = "##", s[10] = {0};
	numtemp ++; temp = numtemp;
	for (i = 0; temp > 0; temp /= 10, i++)
		s[i] = temp % 10 + '0';
	i --;
	for (j = 0; j <= i; j++)
		nometemp[2+i-j] = s[j];
	simb = InsereSimb (nometemp, IDVAR, tip, escopo);
	simb->inic = simb->ref = VERDADE;
	simb->array = FALSO; return simb;
}

void ImprimeQuadruplas () {
	modhead p;
	quadrupla q;
	for (p = codintermed->prox; p != NULL; p = p->prox) {
		printf ("\n\nQuadruplas do modulo %s:\n", p->modname->cadeia);
		for (q = p->listquad->prox; q != NULL; q = q->prox) {
			printf ("\n\t%4d) %s", q->num, nomeoperquad[q->oper]);
			printf (", (%s", nometipoopndquad[q->opnd1.tipo]);
			switch (q->opnd1.tipo) {
				case IDLEOPND: break;
				case VAROPND: printf (", %s", q->opnd1.atr.simb->cadeia); break;
				case INTOPND: printf (", %d", q->opnd1.atr.valint); break;
				case REALOPND: printf (", %g", q->opnd1.atr.valfloat); break;
				case CHAROPND: printf (", %c", q->opnd1.atr.valchar); break;
				case LOGICOPND: printf (", %d", q->opnd1.atr.vallogic); break;
				case CADOPND: printf (", %s", q->opnd1.atr.valcad); break;
				case ROTOPND: printf (", %d", q->opnd1.atr.rotulo->num); break;
				case MODOPND: printf(", %s", q->opnd1.atr.modulo->modname->cadeia);
					break;
			}
			printf (")");
			printf (", (%s", nometipoopndquad[q->opnd2.tipo]);
			switch (q->opnd2.tipo) {
				case IDLEOPND: break;
				case VAROPND: printf (", %s", q->opnd2.atr.simb->cadeia); break;
				case INTOPND: printf (", %d", q->opnd2.atr.valint); break;
				case REALOPND: printf (", %g", q->opnd2.atr.valfloat); break;
				case CHAROPND: printf (", %c", q->opnd2.atr.valchar); break;
				case LOGICOPND: printf (", %d", q->opnd2.atr.vallogic); break;
				case CADOPND: printf (", %s", q->opnd2.atr.valcad); break;
				case ROTOPND: printf (", %d", q->opnd2.atr.rotulo->num); break;
				case MODOPND: printf(", %s", q->opnd2.atr.modulo->modname->cadeia);
					break;
			}
			printf (")");
			printf (", (%s", nometipoopndquad[q->result.tipo]);
			switch (q->result.tipo) {
				case IDLEOPND: break;
				case VAROPND: printf (", %s", q->result.atr.simb->cadeia); break;
				case INTOPND: printf (", %d", q->result.atr.valint); break;
				case REALOPND: printf (", %g", q->result.atr.valfloat); break;
				case CHAROPND: printf (", %c", q->result.atr.valchar); break;
				case LOGICOPND: printf (", %d", q->result.atr.vallogic); break;
				case CADOPND: printf (", %s", q->result.atr.valcad); break;
				case ROTOPND: printf (", %d", q->result.atr.rotulo->num); break;
				case MODOPND: printf(", %s", q->result.atr.modulo->modname->cadeia);
					break;
			}
			printf (")");
		}
	}
   printf ("\n");
}

void RenumQuadruplas (quadrupla quad1, quadrupla quad2) {
	quadrupla q; int nquad;
	for (q = quad1->prox, nquad = quad1->num; q != quad2; q = q->prox) {
      nquad++;
		q->num = nquad;
	}
}


/*  Mensagens de erros semanticos  */

void DeclaracaoRepetida (char *s) {
	printf ("\n\n***** Declaracao Repetida: %s *****\n\n", s);
}

void NaoDeclarado (char *s) {
	printf ("\n\n***** Identificador Nao Declarado: %s *****\n\n", s);
}

void TipoInadequado (char *s) {
	printf ("\n\n***** Identificador de Tipo Inadequado: %s *****\n\n", s);
}

void Incompatibilidade(char *s){
	printf ("\n\n***** Incompatibilidade: %s *****\n\n", s);
}

void Esperado (char *s) {
	printf ("\n\n***** Esperado: %s *****\n\n", s);
}

void NaoEsperado (char *s) {
	printf ("\n\n***** Nao Esperado: %s *****\n\n", s);
}

void ErroLinguagem(char *s) {
	printf ("\n\n***** Erro de linguagem: %s *****\n\n", s);
}

void ErroInterno(char *s) {
	printf ("\n\n***** Erro interno: %s *****\n\n", s);
}
