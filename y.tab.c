#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "lab5.y"
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
#define	PARAM		21
#define	OPREAD		22
#define	OPWRITE		23
#define	IND			24
#define	INDEX		25
#define	CONTAPONT	26
#define	ATRIBPONT	27
#define CALLOP		28
#define EXITOP		29
#define RETURNOP	30

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
#define	FUNCOPND	9

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

char *nomeoperquad[31] = {"",
	"OR", "AND", "LT", "LE", "GT", "GE", "EQ", "NE", "MAIS",
	"MENOS", "MULT", "DIV", "RESTO", "MENUN", "NOT", "ATRIB",
	"OPENMOD", "NOP", "JUMP", "JF", "PARAM", "READ", "WRITE",
	"IND", "INDEX", "CONTAPONT", "ATRIBPONT", "CALLOP", "EXITOP",
	"RETURNOP"
};

/*
	Strings para tipos de operandos de quadruplas
 */

char *nometipoopndquad[10] = {"IDLE",
	"VAR", "INT", "REAL", "CARAC", "LOGIC", "CADEIA", "ROTULO", "MODULO", "FUNCAO"
};

/* Quadruplas */

typedef struct celquad celquad; 
typedef celquad *quadrupla; 

typedef struct celmodhead celmodhead;
typedef celmodhead *modhead; 

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
	modhead fhead;
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
quadrupla quadcorrente, quadaux, quadaux2;
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
#line 244 "lab5.y"
typedef union {
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
	int nargs;
} YYSTYPE;
#line 269 "y.tab.c"
#define CALL 257
#define CHAR 258
#define ELSE 259
#define FALSE 260
#define FLOAT 261
#define FOR 262
#define FUNCTION 263
#define IF 264
#define INT 265
#define LOGIC 266
#define PROCEDURE 267
#define PROGRAM 268
#define READ 269
#define REPEAT 270
#define RETURN 271
#define TRUE 272
#define VAR 273
#define WHILE 274
#define WRITE 275
#define ID 276
#define INTCT 277
#define CHARCT 278
#define FLOATCT 279
#define STRING 280
#define OR 281
#define AND 282
#define NOT 283
#define RELOP 284
#define ADOP 285
#define MULTOP 286
#define NEG 287
#define OPPAR 288
#define CLPAR 289
#define OPBRAK 290
#define CLBRAK 291
#define OPBRACE 292
#define CLBRACE 293
#define SCOLON 294
#define COMMA 295
#define ASSIGN 296
#define INVAL 297
#define LOWER_THAN_ELSE 298
#define YYERRCODE 256
short yylhs[] = {                                        -1,
   15,   17,   20,    0,   16,   22,   16,   21,   21,   23,
   24,   24,   24,   24,   25,   27,   25,   29,   26,   28,
   28,   30,   18,   18,   31,   32,   32,   35,   37,   33,
   36,   36,   39,   34,   40,   34,   38,   42,   38,   41,
   44,   19,   43,   43,   45,   45,   45,   45,   45,   45,
   45,   45,   45,   45,   45,   55,   56,   58,   46,   57,
   59,   57,   60,   61,   62,   47,   63,   64,   65,   48,
   66,   67,   68,   69,   70,   71,   49,   72,   73,   50,
   13,   74,   13,   75,   76,   51,   14,   77,   14,   10,
   10,   78,   53,   79,   53,   80,   54,   81,   54,   82,
   83,   84,   52,   12,   85,   12,    3,   86,    3,    4,
   87,    4,    5,   88,    5,    6,   89,    6,    7,   90,
    7,    8,   91,    8,    9,    9,    9,    9,    9,    9,
   92,    9,   93,    9,    9,   94,    1,   11,   11,   96,
   97,   95,   98,    2,   99,    2,
};
short yylen[] = {                                         2,
    0,    0,    0,    9,    0,    0,    3,    1,    2,    3,
    1,    1,    1,    1,    1,    0,    4,    0,    3,    0,
    2,    3,    0,    2,    3,    1,    1,    0,    0,    7,
    2,    3,    0,    6,    0,    7,    1,    0,    4,    2,
    0,    4,    0,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    0,    0,    0,    9,    0,
    0,    3,    0,    0,    0,    8,    0,    0,    0,   10,
    0,    0,    0,    0,    0,    0,   19,    0,    0,    7,
    1,    0,    4,    0,    0,    7,    1,    0,    4,    1,
    1,    0,    6,    0,    7,    0,    3,    0,    4,    0,
    0,    0,    7,    1,    0,    4,    1,    0,    4,    1,
    0,    4,    1,    0,    3,    1,    0,    4,    1,    0,
    4,    1,    0,    4,    1,    1,    1,    1,    1,    1,
    0,    3,    0,    4,    1,    0,    3,    0,    2,    0,
    0,    5,    0,    4,    0,    5,
};
short yydefred[] = {                                      1,
    0,    0,    0,    0,    2,    0,    6,   23,    0,    0,
   13,   12,   11,   14,    0,    8,    0,   28,    0,    0,
   24,    0,   26,   27,    9,   18,    0,   15,    0,    0,
   41,    4,    0,   20,   10,   16,    0,    0,   43,   25,
    0,    0,    0,    0,    0,    0,    0,   21,   17,   29,
    0,    0,    0,   37,    0,    0,    0,    0,   67,    0,
    0,    0,   42,   55,   45,   44,   46,   47,   48,   49,
   50,   51,   52,   53,   54,    0,    0,    0,   34,   40,
    0,   38,    0,   71,   56,   78,    0,    0,    0,   63,
   84,  136,    0,   22,    0,   30,    0,   36,    0,    0,
    0,    0,    0,    0,   97,  130,  129,    0,  126,  128,
  127,  114,  131,  133,  125,  135,    0,    0,  110,  113,
    0,    0,  122,    0,    0,  138,  101,   31,    0,   39,
    0,    0,    0,    0,   81,    0,    0,    0,    0,    0,
    0,  108,   99,  111,  117,  120,  123,    0,   90,    0,
   87,    0,    0,    0,   32,    0,    0,    0,   72,   57,
   82,    0,   68,    0,    0,  115,  132,    0,    0,    0,
    0,    0,    0,   64,   88,    0,  140,  139,    0,   93,
    0,  105,    0,    0,    0,    0,    0,  144,    0,  134,
    0,  112,    0,    0,  124,   65,    0,    0,    0,  102,
   95,    0,    0,   58,   83,   80,    0,  146,    0,   89,
   86,    0,  103,    0,   73,    0,    0,   66,  141,    0,
   61,   59,   69,  142,    0,    0,   70,   74,   62,    0,
    0,   75,    0,    0,   76,    0,   77,
};
short yydgoto[] = {                                       1,
  115,  116,  150,  118,  119,  120,  121,  122,  123,  151,
  153,  158,  136,  152,    2,    8,    6,   10,   65,   20,
   15,    9,   16,   52,   27,   28,   42,   41,   34,   48,
   21,   22,   23,   24,   29,   96,   78,   53,   44,   45,
   54,   99,   46,   39,   66,   67,   68,   69,   70,   71,
   72,   73,   74,   75,  102,  184,  222,  216,  226,  124,
  196,  209,   87,  187,  227,  101,  183,  220,  230,  233,
  236,  103,  162,  185,  125,  176,  197,  131,  132,   88,
   89,   76,  154,  213,  202,  169,  170,  139,  171,  172,
  173,  140,  141,  126,  178,  199,  224,  164,  165,
};
short yysindex[] = {                                      0,
    0, -258, -247, -246,    0, -202,    0,    0,   15, -255,
    0,    0,    0,    0,   15,    0, -203,    0, -191, -198,
    0, -202,    0,    0,    0,    0, -263,    0,   15, -212,
    0,    0, -198,    0,    0,    0, -158,    0,    0,    0,
 -159, -203, -189, -154,   15, -213, -135,    0,    0,    0,
 -150, -124, -282,    0, -115, -125, -123, -122,    0,    0,
 -107,  -90,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -92,  -91, -223,    0,    0,
  -83,    0,  -75,    0,    0,    0, -187,  -70,  -84,    0,
    0,    0,  -82,    0,  -67,    0, -200,    0,   15,    0,
  -92,  -84,  -92,  -49,    0,    0,    0,  -59,    0,    0,
    0,    0,    0,    0,    0,    0, -275,  -52,    0,    0,
 -216,  -50,    0,  -84, -105,    0,    0,    0,  -54,    0,
  -48,  -84,  -51, -217,    0,  -44,  -42,    0,  -71,  -71,
  -84,    0,    0,    0,    0,    0,    0, -177,    0,  -27,
    0,  -40,  -34,  -84,    0,  -36,  -27, -170,    0,    0,
    0,  -29,    0,  -28,  -84,    0,    0, -102,  -84,  -84,
  -71,  -71,  -71,    0,    0,  -23,    0,    0, -235,    0,
  -25,    0,  -84, -187,  -92,  -24,  -84,    0, -167,    0,
  -52,    0,   -3,  -50,    0,    0, -105,  -19,  -71,    0,
    0,  -84, -234,    0,    0,    0,  -79,    0, -187,    0,
    0, -129,    0,  -27,    0,   24,   -8,    0,    0,  -84,
    0,    0,    0,    0, -231, -187,    0,    0,    0,  -92,
   -9,    0,  -84,  -69,    0, -187,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0, -239,    0,    0,    0,   -4,
    0,    0,    0,    0, -237,    0,    0,    0,    0,    0,
    0,   -2,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -155,    0,    0,
  -98,    0,    0,    0,    0,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -186,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   13,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -140,
    0,    0,    0,    0,    0,    0,    0,  -47,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -104,    0,    0,
 -168,  -32,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    0, -119,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -144,
    0,    3,  -63,    0,    0,    0, -109,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   13,    0,    0,    0,    0,    0,    0,
  -10,    0, -165,  -17,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   13,    0,
    0,    0,    0,  -80,    0, -253,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   13,    0,
};
short yygindex[] = {                                      0,
  -76,    0,  -87,  124,  125,  155, -166,  126, -137,   99,
    0,  132,    0,    0,    0,  277,    0,    0,   32,    0,
    0,    0,  285,    5,    0,  259,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  224,    0,    0,
  204,    0,    0,    0,  -86,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 303
short yytable[] = {                                      93,
  104,  117,  167,   60,  193,  142,   81,   18,   60,    3,
   60,   19,   82,   17,  134,   60,   60,   60,  143,   17,
   60,   60,   60,    5,  133,    7,  135,    5,    4,    7,
   35,   36,  212,   37,   11,  195,  148,   12,   60,   60,
   60,   13,   14,   55,  157,  142,  142,    5,   56,  142,
   57,   32,    5,  168,    7,   58,   59,   60,  200,  215,
   61,   62,  228,  142,   40,   95,  179,  145,  146,   55,
    7,  160,   26,   98,   56,   38,   57,  157,   31,   63,
   64,   58,   59,   60,   30,   98,   61,   62,  129,   98,
   98,   98,   98,   31,   82,  203,   98,  204,   50,  207,
   98,   98,   35,  142,   31,   35,   64,   96,  205,   35,
   35,  174,  116,  116,  214,  118,  118,   43,  181,   94,
  116,  208,  218,  118,  182,  116,  116,  182,  118,  118,
   47,   94,  225,   33,   51,   94,   94,   94,   94,  229,
  145,   77,   94,   79,   91,  234,   94,   94,   92,  237,
   91,   80,  145,  231,  106,  146,  145,  145,  145,  145,
   83,  219,   84,  145,   85,   86,  107,  145,  145,  143,
  108,  109,  110,  111,  149,  106,  107,  112,  142,  104,
   90,  113,  114,   92,  107,  104,  190,  107,  106,  107,
  107,  108,  109,  110,  111,   19,   19,   91,  112,   94,
  107,  142,  113,  114,  108,  109,  110,  111,  106,  217,
   98,  142,  100,  127,  106,  113,  114,  137,  137,  235,
  137,  137,  137,  105,  137,  137,  128,  137,  138,  144,
  137,  137,  137,  136,  136,  147,  136,  136,  136,  155,
  156,  136,  136,  136,  159,  163,  136,  136,  119,  119,
  161,  119,  119,  142,  175,  177,  119,  180,  119,  186,
  188,  119,  119,  121,  121,  198,  121,  121,  201,  206,
  109,  121,   11,  121,  211,   12,  121,  121,  109,   13,
   14,  146,  221,  109,  109,  223,  232,    3,  100,    5,
   79,   85,  191,  166,  192,  210,  189,  194,   33,   25,
   49,   97,  130,
};
short yycheck[] = {                                      76,
   87,   89,  140,  257,  171,  281,  289,  263,  262,  268,
  264,  267,  295,    9,  102,  269,  270,  271,  294,   15,
  274,  275,  276,  263,  101,  263,  103,  267,  276,  267,
  294,  295,  199,   29,  258,  173,  124,  261,  292,  293,
  294,  265,  266,  257,  132,  281,  281,  294,  262,  281,
  264,   20,  292,  141,  292,  269,  270,  271,  294,  294,
  274,  275,  294,  281,   33,  289,  154,  284,  285,  257,
  273,  289,  276,  260,  262,  288,  264,  165,  292,  293,
  294,  269,  270,  271,  276,  272,  274,  275,  289,  276,
  277,  278,  279,  292,  295,  183,  283,  184,  288,  187,
  287,  288,  258,  281,  292,  261,  294,  294,  185,  265,
  266,  289,  281,  282,  202,  281,  282,  276,  289,  260,
  289,  289,  209,  289,  295,  294,  295,  295,  294,  295,
  290,  272,  220,  289,  289,  276,  277,  278,  279,  226,
  260,  277,  283,  294,  289,  233,  287,  288,  289,  236,
  295,  276,  272,  230,  260,  285,  276,  277,  278,  279,
  276,  291,  288,  283,  288,  288,  272,  287,  288,  289,
  276,  277,  278,  279,  280,  260,  281,  283,  281,  289,
  288,  287,  288,  276,  289,  295,  289,  272,  260,  294,
  295,  276,  277,  278,  279,  294,  295,  288,  283,  291,
  272,  281,  287,  288,  276,  277,  278,  279,  289,  289,
  294,  281,  288,  296,  295,  287,  288,  281,  282,  289,
  284,  285,  286,  294,  274,  289,  294,  291,  288,  282,
  294,  295,  296,  281,  282,  286,  284,  285,  286,  294,
  289,  289,  290,  291,  296,  288,  294,  295,  281,  282,
  295,  284,  285,  281,  295,  290,  289,  294,  291,  289,
  289,  294,  295,  281,  282,  289,  284,  285,  294,  294,
  281,  289,  258,  291,  294,  261,  294,  295,  289,  265,
  266,  285,  259,  294,  295,  294,  296,  292,  276,  292,
  289,  289,  169,  139,  170,  197,  165,  172,   22,   15,
   42,   78,   99,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 298
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CALL","CHAR","ELSE","FALSE",
"FLOAT","FOR","FUNCTION","IF","INT","LOGIC","PROCEDURE","PROGRAM","READ",
"REPEAT","RETURN","TRUE","VAR","WHILE","WRITE","ID","INTCT","CHARCT","FLOATCT",
"STRING","OR","AND","NOT","RELOP","ADOP","MULTOP","NEG","OPPAR","CLPAR",
"OPBRAK","CLBRAK","OPBRACE","CLBRACE","SCOLON","COMMA","ASSIGN","INVAL",
"LOWER_THAN_ELSE",
};
char *yyrule[] = {
"$accept : Prog",
"$$1 :",
"$$2 :",
"$$3 :",
"Prog : $$1 PROGRAM ID SCOLON $$2 Decls SubProgs $$3 CompStat",
"Decls :",
"$$4 :",
"Decls : VAR $$4 DeclList",
"DeclList : Declaration",
"DeclList : DeclList Declaration",
"Declaration : Type ElemList SCOLON",
"Type : INT",
"Type : FLOAT",
"Type : CHAR",
"Type : LOGIC",
"ElemList : Elem",
"$$5 :",
"ElemList : ElemList COMMA $$5 Elem",
"$$6 :",
"Elem : ID $$6 DimList",
"DimList :",
"DimList : DimList Dim",
"Dim : OPBRAK INTCT CLBRAK",
"SubProgs :",
"SubProgs : SubProgs SubProgDecl",
"SubProgDecl : Header Decls CompStat",
"Header : FuncHeader",
"Header : ProcHeader",
"$$7 :",
"$$8 :",
"FuncHeader : FUNCTION $$7 Type ID OPPAR $$8 FuncHeaderAux",
"FuncHeaderAux : CLPAR SCOLON",
"FuncHeaderAux : ParamList CLPAR SCOLON",
"$$9 :",
"ProcHeader : PROCEDURE ID OPPAR $$9 CLPAR SCOLON",
"$$10 :",
"ProcHeader : PROCEDURE ID OPPAR $$10 ParamList CLPAR SCOLON",
"ParamList : Parameter",
"$$11 :",
"ParamList : ParamList COMMA $$11 Parameter",
"Parameter : Type ID",
"$$12 :",
"CompStat : OPBRACE $$12 StatList CLBRACE",
"StatList :",
"StatList : StatList Statement",
"Statement : CompStat",
"Statement : IfStat",
"Statement : WhileStat",
"Statement : RepeatStat",
"Statement : ForStat",
"Statement : ReadStat",
"Statement : WriteStat",
"Statement : AssignStat",
"Statement : CallStat",
"Statement : ReturnStat",
"Statement : SCOLON",
"$$13 :",
"$$14 :",
"$$15 :",
"IfStat : IF OPPAR $$13 Expression CLPAR $$14 Statement $$15 ElseStat",
"ElseStat :",
"$$16 :",
"ElseStat : ELSE $$16 Statement",
"$$17 :",
"$$18 :",
"$$19 :",
"WhileStat : WHILE OPPAR $$17 Expression CLPAR $$18 $$19 Statement",
"$$20 :",
"$$21 :",
"$$22 :",
"RepeatStat : REPEAT $$20 Statement WHILE OPPAR $$21 Expression CLPAR SCOLON $$22",
"$$23 :",
"$$24 :",
"$$25 :",
"$$26 :",
"$$27 :",
"$$28 :",
"ForStat : FOR OPPAR $$23 Variable ASSIGN $$24 Expression SCOLON $$25 Expression SCOLON $$26 Variable ASSIGN $$27 Expression CLPAR $$28 Statement",
"$$29 :",
"$$30 :",
"ReadStat : READ OPPAR $$29 ReadList $$30 CLPAR SCOLON",
"ReadList : Variable",
"$$31 :",
"ReadList : ReadList COMMA $$31 Variable",
"$$32 :",
"$$33 :",
"WriteStat : WRITE OPPAR $$32 WriteList $$33 CLPAR SCOLON",
"WriteList : WriteElem",
"$$34 :",
"WriteList : WriteList COMMA $$34 WriteElem",
"WriteElem : STRING",
"WriteElem : Expression",
"$$35 :",
"CallStat : CALL ID OPPAR $$35 CLPAR SCOLON",
"$$36 :",
"CallStat : CALL ID OPPAR $$36 ExprList CLPAR SCOLON",
"$$37 :",
"ReturnStat : RETURN $$37 SCOLON",
"$$38 :",
"ReturnStat : RETURN $$38 Expression SCOLON",
"$$39 :",
"$$40 :",
"$$41 :",
"AssignStat : $$39 Variable ASSIGN $$40 Expression SCOLON $$41",
"ExprList : Expression",
"$$42 :",
"ExprList : ExprList COMMA $$42 Expression",
"Expression : AuxExpr1",
"$$43 :",
"Expression : Expression OR $$43 AuxExpr1",
"AuxExpr1 : AuxExpr2",
"$$44 :",
"AuxExpr1 : AuxExpr1 AND $$44 AuxExpr2",
"AuxExpr2 : AuxExpr3",
"$$45 :",
"AuxExpr2 : NOT $$45 AuxExpr3",
"AuxExpr3 : AuxExpr4",
"$$46 :",
"AuxExpr3 : AuxExpr4 RELOP $$46 AuxExpr4",
"AuxExpr4 : Term",
"$$47 :",
"AuxExpr4 : AuxExpr4 ADOP $$47 Term",
"Term : Factor",
"$$48 :",
"Term : Term MULTOP $$48 Factor",
"Factor : Variable",
"Factor : INTCT",
"Factor : FLOATCT",
"Factor : CHARCT",
"Factor : TRUE",
"Factor : FALSE",
"$$49 :",
"Factor : NEG $$49 Factor",
"$$50 :",
"Factor : OPPAR $$50 Expression CLPAR",
"Factor : FuncCall",
"$$51 :",
"Variable : ID $$51 SubscrList",
"SubscrList :",
"SubscrList : SubscrList Subscript",
"$$52 :",
"$$53 :",
"Subscript : OPBRAK $$52 AuxExpr4 CLBRAK $$53",
"$$54 :",
"FuncCall : ID OPPAR $$54 CLPAR",
"$$55 :",
"FuncCall : ID OPPAR $$55 ExprList CLPAR",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 1084 "lab5.y"
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
	s->fhead = modcorrente;
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
				case FUNCOPND:
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
				case FUNCOPND:
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
				case FUNCOPND:
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
#line 1079 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 307 "lab5.y"
{
					InicTabSimb (); InicCodIntermed (); numtemp = 0;
				}
break;
case 2:
#line 311 "lab5.y"
{
					InicTabSimb();
					listatipos = NULL;
					declparam = FALSO;
					printf("program %s;\n\n", yyvsp[-1].string);
					simb = escglobal = escopo = InsereSimb(yyvsp[-1].string, IDPROG, NAOVAR, NULL);
					InicCodIntermMod (simb);
					simb->fhead = modcorrente;
					opnd1.tipo = MODOPND;
					opnd1.atr.modulo = modcorrente;
					GeraQuadrupla (OPENMOD, opnd1, opndidle, opndidle);
				}
break;
case 3:
#line 324 "lab5.y"
{
					modcorrente = codintermed->prox;
					quadcorrente = modcorrente->listquad->prox;
					numquadcorrente = 1;
				}
break;
case 4:
#line 330 "lab5.y"
{
					GeraQuadrupla(EXITOP, opndidle, opndidle, opndidle);
					VerificaInicRef();
					ImprimeTabSimb();
					ImprimeQuadruplas();
				}
break;
case 6:
#line 338 "lab5.y"
{printf("var\n"); tab++; }
break;
case 7:
#line 338 "lab5.y"
{tab--;}
break;
case 10:
#line 343 "lab5.y"
{printf(";\n");}
break;
case 11:
#line 345 "lab5.y"
{tabular(); printf("int "); tipocorrente = INTEIRO;}
break;
case 12:
#line 346 "lab5.y"
{tabular(); printf("float "); tipocorrente = REAL;}
break;
case 13:
#line 347 "lab5.y"
{tabular(); printf("char "); tipocorrente = CARACTERE;}
break;
case 14:
#line 348 "lab5.y"
{tabular(); printf("logic ");  tipocorrente = LOGICO;}
break;
case 16:
#line 351 "lab5.y"
{printf(", ");}
break;
case 18:
#line 354 "lab5.y"
{
					printf("%s", yyvsp[0].string);
					if(ProcuraSimb(yyvsp[0].string, escopo) != NULL)
						DeclaracaoRepetida(yyvsp[0].string);
					else{
						simb = InsereSimb(yyvsp[0].string, IDVAR, tipocorrente, escopo);
						simb->array=FALSO;
						simb->ndims=0;
					}
				}
break;
case 21:
#line 366 "lab5.y"
{simb->array=VERDADE;}
break;
case 22:
#line 369 "lab5.y"
{
					printf("[%d]", yyvsp[-1].valint);
					if(yyvsp[-1].valint<=0)
						Esperado("Valor inteiro positivo");
					simb->ndims++;
					simb->dims[simb->ndims]=yyvsp[-1].valint;
				}
break;
case 25:
#line 381 "lab5.y"
{
					escopo = escopo->escopo;
					GeraQuadrupla(EXITOP, opndidle, opndidle, opndidle);
					if (escopo == NULL) printf("Erro, escopo voltou demais\n");
				}
break;
case 28:
#line 390 "lab5.y"
{tabular(); printf("function ");}
break;
case 29:
#line 391 "lab5.y"
{
					printf("%s(", yyvsp[-1].string);
					if (ProcuraSimb(yyvsp[-1].string, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb(yyvsp[-1].string, IDFUNC, tipocorrente, escopo);
					InicCodIntermMod (simb);
					simb->fhead = modcorrente;
					opnd1.tipo = MODOPND;
					opnd1.atr.modulo = modcorrente;
					GeraQuadrupla (OPENMOD, opnd1, opndidle, opndidle);
				}
break;
case 31:
#line 404 "lab5.y"
{printf(");\n");}
break;
case 32:
#line 405 "lab5.y"
{printf(");\n");}
break;
case 33:
#line 408 "lab5.y"
{
					tabular();
					printf("procedure %s(", yyvsp[-1].string);
					if (ProcuraSimb(yyvsp[-1].string, escopo) != NULL)
						DeclaracaoRepetida("Funcao com o mesmo nome que uma variavel global");
					escopo = simb = InsereSimb(yyvsp[-1].string, IDPROC, NAOVAR, escopo);
					InicCodIntermMod (simb);
					simb->fhead = modcorrente;
					opnd1.tipo = MODOPND;
					opnd1.atr.modulo = modcorrente;
					GeraQuadrupla (OPENMOD, opnd1, opndidle, opndidle);
				}
break;
case 34:
#line 420 "lab5.y"
{printf(");\n");}
break;
case 35:
#line 422 "lab5.y"
{
					tabular();
					printf("procedure %s(", yyvsp[-1].string);
					escopo = simb = InsereSimb(yyvsp[-1].string, IDPROC, NAOVAR, escopo);
					InicCodIntermMod (simb);
					simb->fhead = modcorrente;
					opnd1.tipo = MODOPND;
					opnd1.atr.modulo = modcorrente;
					GeraQuadrupla (OPENMOD, opnd1, opndidle, opndidle);
				}
break;
case 36:
#line 432 "lab5.y"
{printf(");\n");}
break;
case 38:
#line 435 "lab5.y"
{printf(", ");}
break;
case 40:
#line 438 "lab5.y"
{
					printf("%s", yyvsp[0].string);
					declparam = VERDADE;
					simbolo s = ProcuraSimb(yyvsp[0].string, escglobal);
					if (s != NULL && (s->tid == IDFUNC || s->tid == IDFUNC)){
						ErroLinguagem("Subprograma nao pode ser usado como parametro.");
					}
					InsereSimb(yyvsp[0].string, IDVAR, tipocorrente, escopo);
					declparam = FALSO;
				}
break;
case 41:
#line 450 "lab5.y"
{
					tabular();
					printf("\{\n");
					tab++;
				}
break;
case 42:
#line 456 "lab5.y"
{
					tab--;
					tabular();
					printf("}\n");
				}
break;
case 55:
#line 467 "lab5.y"
{printf(";\n");}
break;
case 56:
#line 469 "lab5.y"
{tabular(); printf("if("); tab++;}
break;
case 57:
#line 470 "lab5.y"
{
					printf(")\n");
					if(yyvsp[-1].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'if' deve ser logica");
					opndaux.tipo = ROTOPND;
					yyval.quad = GeraQuadrupla(OPJF, yyvsp[-1].infoexpr.opnd, opndidle, opndaux);
				}
break;
case 58:
#line 478 "lab5.y"
{
					tab--;
					yyval.quad = quadcorrente;
					yyvsp[-1].quad->result.atr.rotulo = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				}
break;
case 59:
#line 484 "lab5.y"
{
					if (yyvsp[-1].quad->prox != quadcorrente) {
						quadaux = yyvsp[-1].quad->prox;
						yyvsp[-1].quad->prox = quadaux->prox;
						quadaux->prox = yyvsp[-1].quad->prox->prox;
						yyvsp[-1].quad->prox->prox = quadaux;
						RenumQuadruplas (yyvsp[-1].quad, quadcorrente);
					}
				}
break;
case 61:
#line 496 "lab5.y"
{	
					tabular();
					printf("else\n");
					tab++;
					opndaux.tipo = ROTOPND;
					yyval.quad = GeraQuadrupla (OPJUMP, opndidle, opndidle, opndaux);

				}
break;
case 62:
#line 505 "lab5.y"
{
					tab--;
					yyvsp[-1].quad->result.atr.rotulo = GeraQuadrupla (NOP, opndidle, opndidle, opndidle);
				}
break;
case 63:
#line 511 "lab5.y"
{
					tabular(); 
					printf("while(");
					yyval.quad = GeraQuadrupla(NOP, opndidle,opndidle,opndidle);
				}
break;
case 64:
#line 516 "lab5.y"
{printf(")\n");}
break;
case 65:
#line 517 "lab5.y"
{
					if(yyvsp[-2].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'while' deve ser logica");
					opndaux.tipo = ROTOPND;
					yyval.quad = GeraQuadrupla(OPJF, yyvsp[-2].infoexpr.opnd, opndidle, opndaux);
				}
break;
case 66:
#line 524 "lab5.y"
{
					opndaux.tipo = ROTOPND;
					yyval.quad = GeraQuadrupla(OPJUMP, opndidle,opndidle,opndaux);
					yyval.quad->result.atr.rotulo = yyvsp[-5].quad;
					yyvsp[-1].quad->result.atr.rotulo = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				}
break;
case 67:
#line 532 "lab5.y"
{
					tabular();
					printf("repeat\n");
					yyval.quad = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				}
break;
case 68:
#line 538 "lab5.y"
{
					tabular();
					printf("while(");
				}
break;
case 69:
#line 542 "lab5.y"
{printf(");\n");}
break;
case 70:
#line 543 "lab5.y"
{
					if(yyvsp[-3].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Expressao do comando 'do repeat' deve ser logica");
					opndaux.tipo = ROTOPND;
					quadaux = GeraQuadrupla(OPJF, yyvsp[-3].infoexpr.opnd, opndidle, opndaux);
					opndaux.atr.rotulo = yyvsp[-8].quad;
					GeraQuadrupla(OPJUMP, opndidle, opndidle, opndaux);
					quadaux->result.atr.rotulo = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
				}
break;
case 71:
#line 553 "lab5.y"
{tabular(); printf("for(");}
break;
case 72:
#line 553 "lab5.y"
{printf(" = ");}
break;
case 73:
#line 554 "lab5.y"
{
					/* $$$$$$ 9 $$$$$$ */
					printf("; ");
					if (yyvsp[-4].infovar.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-4].infovar.simb->inic = VERDADE;
						if(yyvsp[-4].infovar.simb->tid!=IDVAR || (yyvsp[-4].infovar.simb->tvar!=INTEIRO && yyvsp[-4].infovar.simb->tvar!=CARACTERE) || yyvsp[-4].infovar.simb->array!=FALSO)
							Incompatibilidade("Variavel de inicializacao incompativel para o operador 'for'");
						VerificarCompatibilidade("assign", yyvsp[-4].infovar.simb->tvar, yyvsp[-1].infoexpr.tipo);
						GeraQuadrupla(OPATRIB,yyvsp[-1].infoexpr.opnd,opndidle,yyvsp[-4].infovar.opnd);
						
						/* quadrupla para verificacao da condicao */
						yyval.quad = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
					}
				}
break;
case 74:
#line 571 "lab5.y"
{printf("; ");}
break;
case 75:
#line 572 "lab5.y"
{
					/* $$$$$$ 15 $$$$$$ */
					printf(" = ");
					opndaux.tipo = ROTOPND;
					yyval.quad = GeraQuadrupla(OPJF, yyvsp[-4].infoexpr.opnd, opndidle, opndaux);
				}
break;
case 76:
#line 579 "lab5.y"
{
					/* $$$$$$ 18 $$$$$$ */
					printf(")\n");
					if (yyvsp[-13].infovar.simb == NULL || yyvsp[-4].infovar.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-4].infovar.simb->inic = VERDADE;
						if(strcmp(yyvsp[-13].infovar.simb->cadeia, yyvsp[-4].infovar.simb->cadeia))
							Incompatibilidade("Variavel de atualizacao deve ser a mesma de inicializacao");
						if((yyvsp[-10].infoexpr.tipo != INTEIRO && yyvsp[-10].infoexpr.tipo != CARACTERE) || (yyvsp[-1].infoexpr.tipo != INTEIRO && yyvsp[-1].infoexpr.tipo != CARACTERE) || yyvsp[-7].infoexpr.tipo!=LOGICO)
							Incompatibilidade("Expressoes de tipo inadequado");
						VerificarCompatibilidade("assign", yyvsp[-4].infovar.simb->tvar, yyvsp[-1].infoexpr.tipo);
						yyval.quad = GeraQuadrupla(OPATRIB,yyvsp[-1].infoexpr.opnd,opndidle,yyvsp[-4].infovar.opnd);
					}
				}
break;
case 77:
#line 596 "lab5.y"
{
					/* $$$$$$ 20 $$$$$$ */
					opndaux.tipo = ROTOPND;
					opndaux.atr.rotulo = yyvsp[-10].quad;
					yyval.quad = quadcorrente;
					GeraQuadrupla(OPJUMP, opndidle, opndidle,opndaux);
					
					quadaux = yyvsp[-4].quad->prox;
					yyvsp[-4].quad->prox = yyvsp[-1].quad->prox;
					yyval.quad->prox = quadaux;
					yyvsp[-1].quad->prox = quadcorrente;
					
					yyval.quad = GeraQuadrupla(NOP, opndidle, opndidle, opndidle);
					opndaux.atr.rotulo = yyval.quad;
					yyvsp[-4].quad->result = opndaux;
					
					RenumQuadruplas(yyvsp[-10].quad, quadcorrente);
					
					/* colocando expressao de atualizacao ao fim */
					
				}
break;
case 78:
#line 618 "lab5.y"
{tabular(); printf("read(");}
break;
case 79:
#line 619 "lab5.y"
{	
						if(yyvsp[0].nargs != 0){
							opnd1.tipo = INTOPND;
							opnd1.atr.valint = yyvsp[0].nargs;
							GeraQuadrupla(OPREAD, opnd1, opndidle, opndidle);
						}
					}
break;
case 80:
#line 626 "lab5.y"
{printf(");\n");}
break;
case 81:
#line 629 "lab5.y"
{
						if(yyvsp[0].infovar.simb->ndims == 0){
							yyval.nargs = 1;
							GeraQuadrupla(PARAM, yyvsp[0].infovar.opnd, opndidle,opndidle);
						}
						else{
							opnd2.tipo = VAROPND;
							opnd2.atr.simb = NovaTemp (yyvsp[0].infovar.opnd.tipo);
							GeraQuadrupla(PARAM, opnd2, opndidle, opndidle);
							opnd1.tipo = INTOPND;
							opnd1.atr.valint = 1;
							GeraQuadrupla(OPREAD, opnd1, opndidle, opndidle);
							GeraQuadrupla(ATRIBPONT, opnd2, opndidle, yyvsp[0].infovar.opnd);
							yyval.nargs = 0;
						}
					}
break;
case 82:
#line 645 "lab5.y"
{printf(", ");}
break;
case 83:
#line 646 "lab5.y"
{
						if(yyvsp[0].infovar.simb->ndims == 0){
							yyval.nargs = yyvsp[-3].nargs + 1;
							/* Guarda para quando aparecer um vetor */
							quadaux = GeraQuadrupla(PARAM, yyvsp[0].infovar.opnd, opndidle, opndidle);
						}
						else{
							opnd2.tipo = VAROPND;
							opnd2.atr.simb = NovaTemp (yyvsp[0].infovar.opnd.tipo);
							quadaux2 = GeraQuadrupla(PARAM, opnd2, opndidle, opndidle);
							opnd1.tipo = INTOPND;
							opnd1.atr.valint = yyvsp[-3].nargs;
							yyval.quad = GeraQuadrupla(OPREAD, opnd1, opndidle, opndidle);
							
							/* Read do vetor */
							opnd1.atr.valint = 1;
							GeraQuadrupla(OPREAD, opnd1, opndidle, opndidle);
							GeraQuadrupla(ATRIBPONT, opnd2, opndidle, yyvsp[0].infovar.opnd);
							
							/* Troca de referencias */
							quadaux2->prox = yyval.quad->prox;
							yyval.quad->prox = quadaux->prox;
							quadaux->prox = yyval.quad;
							RenumQuadruplas(quadaux, quadaux2->prox);
							
							/* atualizacao */
							yyval.nargs = 0;
						}
						
					}
break;
case 84:
#line 677 "lab5.y"
{tabular(); printf("write(");}
break;
case 85:
#line 678 "lab5.y"
{
						opnd1.tipo = INTOPND;
						opnd1.atr.valint = yyvsp[0].nargs;
						GeraQuadrupla (OPWRITE, opnd1, opndidle, opndidle);
					}
break;
case 86:
#line 683 "lab5.y"
{printf(");\n");}
break;
case 87:
#line 686 "lab5.y"
{
						yyval.nargs = 1;
						GeraQuadrupla (PARAM, yyvsp[0].infoexpr.opnd, opndidle, opndidle);
					}
break;
case 88:
#line 690 "lab5.y"
{printf(", ");}
break;
case 89:
#line 691 "lab5.y"
{
						yyval.nargs = yyvsp[-3].nargs + 1;
						GeraQuadrupla (PARAM, yyvsp[0].infoexpr.opnd, opndidle, opndidle);
					}
break;
case 90:
#line 697 "lab5.y"
{
						printf("\"%s\"", yyvsp[0].string);
						yyval.infoexpr.opnd.tipo = CADOPND;
						yyval.infoexpr.opnd.atr.valcad = malloc(strlen(yyvsp[0].string) + 1);
						strcpy(yyval.infoexpr.opnd.atr.valcad, yyvsp[0].string);
					}
break;
case 92:
#line 706 "lab5.y"
{
					tabular();
					printf("call %s();\n", yyvsp[-1].string);
					VerificarFuncao(yyvsp[-1].string, 0);
					simbolo simb = ProcuraSimb(yyvsp[-1].string, escglobal);
					opnd1.tipo = FUNCOPND; opnd1.atr.modulo = simb->fhead;
					GeraQuadrupla(CALLOP, opnd1, opndidle, opndidle);
				}
break;
case 94:
#line 716 "lab5.y"
{
					tabular();
					printf("call %s(", yyvsp[-1].string);
				}
break;
case 95:
#line 721 "lab5.y"
{
					printf(");\n");
					VerificarFuncao(yyvsp[-5].string, yyvsp[-2].nparams);
					simbolo simb = ProcuraSimb(yyvsp[-5].string, escglobal);
					opnd1.tipo = FUNCOPND; opnd1.atr.modulo = simb->fhead;
					opnd2.tipo = INTOPND; opnd2.atr.valint = yyvsp[-2].nparams;
					GeraQuadrupla(CALLOP, opnd1, opnd2, opndidle);
				}
break;
case 96:
#line 730 "lab5.y"
{tabular(); printf("return");}
break;
case 97:
#line 731 "lab5.y"
{
					printf(";\n");
					if (escopo->tid != IDPROG && escopo->tid != IDPROC)
						Incompatibilidade("Tipo de retorno nao deveria ser void");
					GeraQuadrupla(RETURNOP, opndidle, opndidle, opndidle);
				}
break;
case 98:
#line 737 "lab5.y"
{tabular(); printf("return ");}
break;
case 99:
#line 738 "lab5.y"
{
					printf(";\n");
					if (escopo->tid != IDFUNC)
						Incompatibilidade("Retorno de nao funcao nao deve ter tipo");
					VerificarCompatibilidade("return", escopo->tvar, yyvsp[-1].infoexpr.tipo);
					GeraQuadrupla(RETURNOP, yyvsp[-1].infoexpr.opnd, opndidle, opndidle);
				}
break;
case 100:
#line 746 "lab5.y"
{tabular();}
break;
case 101:
#line 746 "lab5.y"
{printf(" = ");}
break;
case 102:
#line 746 "lab5.y"
{printf(";\n");}
break;
case 103:
#line 747 "lab5.y"
{
					if (yyvsp[-5].infovar.simb == NULL) {
						ErroInterno("Variable null.");
					}
					else {
						yyvsp[-5].infovar.simb->inic = VERDADE;
						if(yyvsp[-5].infovar.simb->tvar == NAOVAR || yyvsp[-5].infovar.simb->tid != IDVAR)
							Esperado("Esperada uma variavel inteira, caractere, real ou logica para atribuicao.");
						VerificarCompatibilidade("assign", yyvsp[-5].infovar.simb->tvar, yyvsp[-2].infoexpr.tipo);
						if(yyvsp[-5].infovar.simb->ndims == 0)
							GeraQuadrupla(OPATRIB,yyvsp[-2].infoexpr.opnd,opndidle,yyvsp[-5].infovar.opnd);
						else
							GeraQuadrupla(ATRIBPONT, yyvsp[-2].infoexpr.opnd, opndidle, yyvsp[-5].infovar.opnd);
					}
				}
break;
case 104:
#line 764 "lab5.y"
{
					yyval.nparams=1;
					AdicionarListaTipo(yyvsp[0].infoexpr.tipo);
					GeraQuadrupla(PARAM, yyvsp[0].infoexpr.opnd, opndidle, opndidle);
				}
break;
case 105:
#line 769 "lab5.y"
{printf(", ");}
break;
case 106:
#line 770 "lab5.y"
{
					yyval.nparams=yyvsp[-3].nparams+1; 
					AdicionarListaTipo(yyvsp[0].infoexpr.tipo);
					GeraQuadrupla(PARAM, yyvsp[0].infoexpr.opnd, opndidle, opndidle);
				}
break;
case 108:
#line 777 "lab5.y"
{printf(" || ");}
break;
case 109:
#line 778 "lab5.y"
{
					if(yyvsp[-3].infoexpr.tipo!=LOGICO || yyvsp[0].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.infoexpr.tipo=LOGICO;
					yyval.infoexpr.opnd.tipo = VAROPND;  
					yyval.infoexpr.opnd.atr.simb = NovaTemp (yyval.infoexpr.tipo);
					GeraQuadrupla (OPOR, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd);
				}
break;
case 111:
#line 788 "lab5.y"
{printf(" && ");}
break;
case 112:
#line 789 "lab5.y"
{
					if(yyvsp[-3].infoexpr.tipo!=LOGICO || yyvsp[0].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.infoexpr.tipo=LOGICO;
					yyval.infoexpr.opnd.tipo = VAROPND;  
					yyval.infoexpr.opnd.atr.simb = NovaTemp (yyval.infoexpr.tipo);
					GeraQuadrupla (OPAND, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd);
				}
break;
case 114:
#line 799 "lab5.y"
{printf("!");}
break;
case 115:
#line 800 "lab5.y"
{
					if(yyvsp[0].infoexpr.tipo!=LOGICO)
						Incompatibilidade("Operando improprio para operador logico");
					yyval.infoexpr.tipo=LOGICO;
					yyval.infoexpr.opnd.tipo = VAROPND;  
					yyval.infoexpr.opnd.atr.simb = NovaTemp (yyval.infoexpr.tipo);
					GeraQuadrupla (OPNOT, yyvsp[0].infoexpr.opnd, opndidle, yyval.infoexpr.opnd);

				}
break;
case 117:
#line 812 "lab5.y"
{
					switch(yyvsp[0].atr){
						case LT: printf(" < "); break;
						case LE: printf(" <= "); break;
						case GT: printf(" > "); break;
						case GE: printf(" >= "); break;
						case EQ: printf(" == "); break;
						case NE: printf(" != "); break;
					}
				}
break;
case 118:
#line 823 "lab5.y"
{
					switch(yyvsp[-2].atr){
						case LT:
						case LE:
						case GT:
						case GE:
							if((yyvsp[-3].infoexpr.tipo!=INTEIRO && yyvsp[-3].infoexpr.tipo!=REAL && yyvsp[-3].infoexpr.tipo!=CARACTERE)
								|| (yyvsp[0].infoexpr.tipo!=INTEIRO && yyvsp[0].infoexpr.tipo!=REAL && yyvsp[0].infoexpr.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador relacional");
							break;
						case EQ:
						case NE:
							/*Se for logico, o outro operando também deve ser*/
							if(yyvsp[-3].infoexpr.tipo == LOGICO && yyvsp[0].infoexpr.tipo != LOGICO || yyvsp[-3].infoexpr.tipo != LOGICO && yyvsp[0].infoexpr.tipo == LOGICO)
								Incompatibilidade("Operador improprio para operador relacional");
							break;
						default:
							break;
					}
					yyval.infoexpr.tipo=LOGICO;
					/* criando quadrupla */
					yyval.infoexpr.opnd.tipo = VAROPND;  
					yyval.infoexpr.opnd.atr.simb = NovaTemp (yyval.infoexpr.tipo);
					switch(yyvsp[-2].atr){
						case LT: GeraQuadrupla(OPLT, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case LE: GeraQuadrupla(OPLE, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case GT: GeraQuadrupla(OPGT, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case GE: GeraQuadrupla(OPGE, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case EQ: GeraQuadrupla(OPEQ, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case NE: GeraQuadrupla(OPNE, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
					}

				}
break;
case 120:
#line 859 "lab5.y"
{
					switch(yyvsp[0].atr){
						case PL: printf(" + "); break;
						case MI: printf(" - "); break;
					}
				}
break;
case 121:
#line 866 "lab5.y"
{
					if((yyvsp[-3].infoexpr.tipo!=INTEIRO && yyvsp[-3].infoexpr.tipo!=REAL && yyvsp[-3].infoexpr.tipo!=CARACTERE)
						|| (yyvsp[0].infoexpr.tipo!=INTEIRO && yyvsp[0].infoexpr.tipo!=REAL && yyvsp[0].infoexpr.tipo!=CARACTERE))
						Incompatibilidade("Operando improprio para operador aritmetico");
					if(yyvsp[-3].infoexpr.tipo==REAL || yyvsp[0].infoexpr.tipo==REAL)
						yyval.infoexpr.tipo=REAL;
					else
						yyval.infoexpr.tipo=INTEIRO;
					yyval.infoexpr.opnd.tipo = VAROPND;
					yyval.infoexpr.opnd.atr.simb = NovaTemp(yyval.infoexpr.tipo);
					switch(yyvsp[-2].atr){
						case PL: GeraQuadrupla(OPMAIS, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
						case MI: GeraQuadrupla(OPMENOS, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd); break;
					}
				}
break;
case 123:
#line 884 "lab5.y"
{
					switch(yyvsp[0].atr){
						case MU: printf(" * "); break;
						case DI: printf(" / "); break;
						case RE: printf(" %% "); break;
					}
				}
break;
case 124:
#line 892 "lab5.y"
{
					switch(yyvsp[-2].atr){
						case MU:
						case DI:
							if((yyvsp[-3].infoexpr.tipo!=INTEIRO && yyvsp[-3].infoexpr.tipo!=REAL && yyvsp[-3].infoexpr.tipo!=CARACTERE)
								|| (yyvsp[0].infoexpr.tipo!=INTEIRO && yyvsp[0].infoexpr.tipo!=REAL && yyvsp[0].infoexpr.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador aritmetico");
							if(yyvsp[-3].infoexpr.tipo==REAL || yyvsp[0].infoexpr.tipo==REAL) yyval.infoexpr.tipo=REAL;
							else yyval.infoexpr.tipo=INTEIRO;
							yyval.infoexpr.opnd.tipo = VAROPND;
							yyval.infoexpr.opnd.atr.simb = NovaTemp(yyval.infoexpr.tipo);
							if(yyvsp[-2].atr == MU)
								GeraQuadrupla(OPMULTIP, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd);
							else
								GeraQuadrupla(OPDIV, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd);
							break;
						case RE:
							if((yyvsp[-3].infoexpr.tipo!=INTEIRO && yyvsp[-3].infoexpr.tipo!=CARACTERE) || (yyvsp[0].infoexpr.tipo!=INTEIRO && yyvsp[0].infoexpr.tipo!=CARACTERE))
								Incompatibilidade("Operando improprio para operador resto");
							yyval.infoexpr.tipo=INTEIRO;
							yyval.infoexpr.opnd.tipo = VAROPND;
							yyval.infoexpr.opnd.atr.simb = NovaTemp(yyval.infoexpr.tipo);
							GeraQuadrupla(OPRESTO, yyvsp[-3].infoexpr.opnd, yyvsp[0].infoexpr.opnd, yyval.infoexpr.opnd);
							break;
						default:
							break;
					}
				}
break;
case 125:
#line 922 "lab5.y"
{
					if(yyvsp[0].infovar.simb != NULL) {
						yyvsp[0].infovar.simb->ref = VERDADE;
						yyval.infoexpr.tipo = yyvsp[0].infovar.simb->tvar;
						yyval.infoexpr.opnd = yyvsp[0].infovar.opnd;
						if(yyvsp[0].infovar.simb->ndims != 0){
							result.atr.simb = NovaTemp(INTOPND);
							result.tipo = VAROPND;
							GeraQuadrupla(CONTAPONT, yyvsp[0].infovar.opnd, opndidle, result);
						}
					}
				}
break;
case 126:
#line 935 "lab5.y"
{
						printf("%d", yyvsp[0].valint); yyval.infoexpr.tipo = INTEIRO;
						yyval.infoexpr.opnd.tipo = INTOPND;
						yyval.infoexpr.opnd.atr.valint = yyvsp[0].valint;
					}
break;
case 127:
#line 941 "lab5.y"
{
						printf("%g", yyvsp[0].valreal); yyval.infoexpr.tipo = REAL;
						yyval.infoexpr.opnd.tipo = REALOPND;
						yyval.infoexpr.opnd.atr.valfloat = yyvsp[0].valreal;
					}
break;
case 128:
#line 947 "lab5.y"
{
						printf("\'%s\'", yyvsp[0].string);
						yyval.infoexpr.tipo = CARACTERE;
						yyval.infoexpr.opnd.tipo = CHAROPND;
						yyval.infoexpr.opnd.atr.valchar = yyvsp[0].string;
					}
break;
case 129:
#line 954 "lab5.y"
{
						printf("true");
						yyval.infoexpr.tipo = LOGICO;
						yyval.infoexpr.opnd.tipo = LOGICOPND;
						yyval.infoexpr.opnd.atr.vallogic = 1;
					}
break;
case 130:
#line 961 "lab5.y"
{
						printf("false"); 
						yyval.infoexpr.tipo = LOGICO;
						yyval.infoexpr.opnd.tipo = LOGICOPND;
						yyval.infoexpr.opnd.atr.vallogic = 0;
					}
break;
case 131:
#line 967 "lab5.y"
{printf("~");}
break;
case 132:
#line 968 "lab5.y"
{
					if(yyvsp[0].infoexpr.tipo != INTEIRO && yyvsp[0].infoexpr.tipo!= REAL && yyvsp[0].infoexpr.tipo!=CARACTERE)
						Incompatibilidade("Operando improprio para menos unario");
					if(yyvsp[0].infoexpr.tipo == REAL)
						yyval.infoexpr.tipo = REAL;
					else
						yyval.infoexpr.tipo = INTEIRO;
					yyval.infoexpr.opnd.tipo = VAROPND;
					yyval.infoexpr.opnd.atr.simb = NovaTemp(yyval.infoexpr.tipo);
					GeraQuadrupla  (OPMENUN, yyvsp[0].infoexpr.opnd, opndidle, yyval.infoexpr.opnd);
					

				}
break;
case 133:
#line 981 "lab5.y"
{printf("(");}
break;
case 134:
#line 982 "lab5.y"
{
						printf(")");
						yyval.infoexpr.tipo=yyvsp[-1].infoexpr.tipo;
						yyval.infoexpr.opnd = yyvsp[-1].infoexpr.opnd;
					}
break;
case 135:
#line 988 "lab5.y"
{
					if (yyvsp[0].infovar.simb != NULL) {
						yyval.infoexpr.tipo = yyvsp[0].infovar.simb->tvar;
					}
					yyval.infoexpr.opnd = yyvsp[0].infovar.opnd;
				}
break;
case 136:
#line 996 "lab5.y"
{
					printf("%s", yyvsp[0].string);
					simbolo escaux = escopo;
					simb = ProcuraSimb(yyvsp[0].string, escaux);
					while(escaux != NULL && simb == NULL) {
						escaux = escaux->escopo;
						if (escaux != NULL)
							simb = ProcuraSimb(yyvsp[0].string, escaux);
					}
					if(simb == NULL) 
						NaoDeclarado(yyvsp[0].string); 
					else if(simb->tid != IDVAR)
						TipoInadequado(yyvsp[0].string);
					yyval.simb = simb;
				}
break;
case 137:
#line 1012 "lab5.y"
{
					yyval.infovar.simb = yyvsp[-1].simb;
					if(yyval.infovar.simb != NULL) {
						if(yyval.infovar.simb->array == FALSO && yyvsp[0].nsubscr>0)
							NaoEsperado("Subscrito\(s)");
						else if(yyval.infovar.simb->array==VERDADE && yyvsp[0].nsubscr==0)
							Esperado("subscrito\(s)");
						else if(yyvsp[0].nsubscr!=yyval.infovar.simb->ndims)
							Incompatibilidade("Numero de subscritos incompativel com o declarado");
						yyval.infovar.opnd.tipo = VAROPND;
						if(yyvsp[0].nsubscr == 0)
							yyval.infovar.opnd.atr.simb = yyval.infovar.simb;
						else{
							/* Caso seja um vetor */
							yyval.infovar.opnd.tipo = VAROPND;
							yyval.infovar.opnd.atr.simb = NovaTemp(INTOPND);
							opnd1.tipo = VAROPND;
							opnd1.atr.simb = yyval.infovar.simb;
							opnd2.tipo = INTOPND;
							opnd2.atr.valint = yyvsp[0].nsubscr;
							GeraQuadrupla(INDEX, opnd1, opnd2, yyval.infovar.opnd);
						}
					}
				}
break;
case 138:
#line 1037 "lab5.y"
{yyval.nsubscr=0;}
break;
case 139:
#line 1038 "lab5.y"
{yyval.nsubscr=yyvsp[-1].nsubscr+1;}
break;
case 140:
#line 1040 "lab5.y"
{printf("[");}
break;
case 141:
#line 1040 "lab5.y"
{printf("]");}
break;
case 142:
#line 1041 "lab5.y"
{
					if(yyvsp[-2].infoexpr.tipo!=INTEIRO && yyvsp[-2].infoexpr.tipo!=CARACTERE)
						Incompatibilidade("Tipo inadequado para subscrito");
					/* Empilhando índices do vetor */
					GeraQuadrupla(IND, yyvsp[-2].infoexpr.opnd, opndidle, opndidle);
				}
break;
case 143:
#line 1048 "lab5.y"
{printf("%s()", yyvsp[-1].string);}
break;
case 144:
#line 1049 "lab5.y"
{
					VerificarFuncao(yyvsp[-3].string, 0);
					yyval.infovar.simb = ProcuraSimb(yyvsp[-3].string, escglobal);
					opnd1.tipo = FUNCOPND; opnd1.atr.modulo = yyval.infovar.simb->fhead;
					result = opndidle;
					if (yyval.infovar.simb != NULL) {
						if(yyval.infovar.simb->tvar == NAOVAR) result = opndidle;
						else {
							result.tipo = VAROPND;
							result.atr.simb = NovaTemp(yyval.infovar.simb->tvar);
						}
					}
					GeraQuadrupla(CALLOP, opnd1, opndidle, result);
					yyval.infovar.opnd = result;
				}
break;
case 145:
#line 1064 "lab5.y"
{printf("%s(", yyvsp[-1].string);}
break;
case 146:
#line 1065 "lab5.y"
{
					printf(")");
					VerificarFuncao(yyvsp[-4].string, yyvsp[-1].nparams);
					yyval.infovar.simb = ProcuraSimb(yyvsp[-4].string, escglobal);
					opnd1.tipo = FUNCOPND; opnd1.atr.modulo = yyval.infovar.simb->fhead;
					opnd2.tipo = INTOPND; opnd2.atr.valint = yyvsp[-1].nparams;
					result = opndidle;
					if (yyval.infovar.simb != NULL) {
						if(yyval.infovar.simb->tvar == NAOVAR) result = opndidle;
						else {
							result.tipo = VAROPND;
							result.atr.simb = NovaTemp(yyval.infovar.simb->tvar);
						}
					}
					GeraQuadrupla(CALLOP, opnd1, opnd2, result);
					yyval.infovar.opnd = result;
				}
break;
#line 2222 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
