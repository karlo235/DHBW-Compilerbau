%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    extern int yyerror(char* err);
    extern int yylex(void);
    extern FILE *yyin;
%}

%union {
    char val [101];
	  int number;
}

%left   EQUIVALENT
%left   IMPLICATION
%left   OR
%left   AND
%left   NOT
%left   ALL EXIST OPENSQUARE CLOSESQUARE
%left   COMMA
%left   TRUE FALSE
%token  OPENPAR CLOSEPAR
%token  SEMICOLON
%token  ID
%token  DIGIT
%token  DECLARE PREDICATE FUNCTION VARIABLE DD INT

%%
input: declarations formula SEMICOLON {
            printf("PAR: Formula completed with Semicolon.");
          };

declarations:
          | declarations declaration
          ;

declaration:  
          DECLARE PREDICATE ID DD DIGIT {
            printf("PAR: Declaration: Predicate -%s- Arity: %d\n", $<val>3, $<number>5);
          }
          | DECLARE FUNCTION ID DD DIGIT {
            printf("PAR: Declaration: Function -%s- Arity: %d\n", $<val>3, $<number>5);
          }
          | DECLARE VARIABLE ID DD INT {
            printf("PAR: Declaration: Variable -%s- Type: %s\n", $<val>3, $<val>5);
          }
          ;

formula:  ALL OPENSQUARE ID CLOSESQUARE formula {
            printf("PAR: QUANTOR: ALL %s\n", $<val>3);
          }
          | EXIST OPENSQUARE ID CLOSESQUARE formula {
            printf("PAR: QUANTOR: EXIST %s\n", $<val>3);
          }
          | ID OPENPAR args CLOSEPAR {
            printf("PAR: ATOM: %s()\n", $<val>1);
          }
          | NOT formula {
            printf("PAR: JUNCTOR: NEGATION\n");
          }
          | OPENPAR formula CLOSEPAR
          | formula AND formula {
            printf("PAR: JUNCTOR: AND\n");
          }
          | formula OR formula {
            printf("PAR: JUNCTOR: OR\n");
          }
          | formula IMPLICATION formula {
            printf("PAR: JUNCTOR: IMPLICATION\n");
          }
          | formula EQUIVALENT formula {
            printf("PAR: JUNCTOR: EQUIVILENCE\n");
          }
          | FALSE
          | formula FALSE
          | formula FALSE formula
          | TRUE
          | formula TRUE
          | formula TRUE formula
          ;

args:
          | arg_list
          ;

arg_list:
          | ID {
            printf("PAR: TERM: Variable/Constant %s\n", $<val>1);
          }
          | DIGIT {
            printf("PAR: TERM: Variable/Constant %d\n", $<number>1);
          }
          | ID OPENPAR arg_list CLOSEPAR {
          }
          | arg_list COMMA arg_list
          ;
%%

int yyerror(char* err)
{
  printf("Error: %s\n",err);
}
void main(int argc, char* argv[])
{
  ++argv, --argc;
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  yyparse();
}