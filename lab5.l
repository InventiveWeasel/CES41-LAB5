delim		[ \t\n\r]
ws			{delim}+
digito		[0-9]
letra		[A-Za-z]
intct		{digito}+
floatct  	{digito}+((\.{digito}*)|((\.{digito}*)?([Ee][+-]?{digito}+)))
id			{letra}({letra}|{digito})*
carac1		\\.|[^\\']
charct		'{carac1}'
carac2		\\.|[^\\\"]
string		\"{carac2}*\"
%%
{ws}		{ ;}
"/*"		{comentario();}
call		{return CALL;}
char		{return CHAR;}
else		{return ELSE;}
false		{return FALSE;}
float		{return FLOAT;}
for			{return FOR;}
function	{return FUNCTION;}
if			{return IF;}
int			{return INT;}
logic		{return LOGIC;}
procedure	{return PROCEDURE;}
program		{return PROGRAM;}
read		{return READ;}
repeat		{return REPEAT;}
return		{return RETURN;}
true		{return TRUE;}
var			{return VAR;}
while		{return WHILE;}
write		{return WRITE;}
{id}		{strcpy (yylval.string, yytext); return ID;}
{floatct}	{yylval.valreal = atof(yytext); return FLOATCT;}
{intct}		{yylval.valint = atoi(yytext); return INTCT;}
{charct}	{strcpy (yylval.string, yytext+1); yylval.string[strlen(yylval.string)-1]='\0'; return CHARCT;}
{string}	{strcpy (yylval.string, yytext+1); yylval.string[strlen(yylval.string)-1]='\0'; return STRING;}
"||"		{return OR;}
"&&"		{return AND;}
"!"			{return NOT;}
"<"			{yylval.atr = LT; return RELOP;}
"<="		{yylval.atr = LE; return RELOP;}
">"			{yylval.atr = GT; return RELOP;}
">="		{yylval.atr = GE; return RELOP;}
"=="		{yylval.atr = EQ; return RELOP;}
"!="		{yylval.atr = NE; return RELOP;}
"+"			{yylval.atr = PL; return ADOP;}
"-"			{yylval.atr = MI; return ADOP;}
"*"			{yylval.atr = MU; return MULTOP;}
"/"			{yylval.atr = DI; return MULTOP;}
"%"			{yylval.atr = RE; return MULTOP;}
"~"			{return NEG;}
"("			{return OPPAR;}
")"			{return CLPAR;}
"["			{return OPBRAK;}
"]"			{return CLBRAK;}
"{"			{return OPBRACE;}
"}"			{return CLBRACE;}
";"			{return SCOLON;}
","			{return COMMA;}
"="			{return ASSIGN;}
.			{yylval.carac = yytext[0]; return INVAL;}
%%
void comentario()
{
	char c; 
	int estado = 1;
	while (estado != 3) {
		switch (estado) {
			case 1:
				c = input ();
				if (c == EOF) estado = 3;
				else if (c == '*') estado = 2;
				break;
			case 2:
				c = input ();
				if (c == EOF) estado = 3;
				else if (c == '/') estado = 3;
				else if (c == '*') estado = 2;
				else estado = 1;
				break;
			default:
				break;
		}
	}
}
char tratachar(char *s)
{
	if (s[1] != '\\') return s[1];
	else switch(s[2]) {
		case 'a': return 7;
		case 'b': return 8;
		case '\"': return 34;
		case 't': return 9;
		case '0': return 0;
		case 'v': return 11;
		case '\\': return 92;
		case 'r': return 13;
		case 'f': return 12;
		case 'n': return 10;
		case '\'': return 39;
		default: return s[2];
	}
	return s[2];
}
void tabular()
{
	int i;
	for(i=0; i<tab; i++) printf("    ");
}
