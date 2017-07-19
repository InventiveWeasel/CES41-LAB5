flex %1.l
yacc -v %1.y
gcc y.tab.c main.c yyerror.c -o %1 -lfl -Wimplicit-function-declaration
%1 < %2 > %3