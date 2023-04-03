%{
  #include <stdio.h>
%}

%option noyywrap

DIGIT [0-9]
ID [a-zA-Z][a-zA-Z0-9_]*

%%
"/*".*"*/" {
  printf("LEX: COMMENT: %s\n", yytext );
}
"DECLARE" {
  printf("LEX: KEY: DECLARE\n");
}
"PREDICATE" {
  printf( "LEX: KEY: PREDICATE\n");
}
"FUNCTION" {
  printf("LEX: KEY: FUNCTION\n");
}
"VARIABLE" {
  printf("LEX: KEY: VARIABLE\n");
}
"TRUE" {
  printf("LEX: KEY: TRUE\n");
}
"FALSE" {
  printf("LEX: KEY: FALSE\n");
}
"int" {
  printf("LEX: KEY: int\n");
}
\: {
  printf("LEX: KEY: Colon\n");
}
\; {
  printf("LEX: KEY: Semicolon\n");
}
\, {
  printf("LEX: KEY: Comma\n");
}
\( {
  printf("LEX: KEY: Bracket Open\n");
}
\) {
  printf("LEX: KEY: Bracket Close\n");
}
\[ {
  printf("LEX: KEY: Square Open\n");
}
\] {
  printf("LEX: KEY: Square Close\n");
}
\& {
  printf("LEX: KEY: AND\n");
}
\| {
  printf("LEX: KEY: OR\n");
}
\~ {
  printf("LEX: KEY: NOT\n");
}
"->" {
  printf("LEX: KEY: IMPLICATION\n");
}
"<->" {
  printf("LEX: KEY: EQUIVALENT\n");
}
"ALL" {
  printf("LEX: KEY: ALL\n");
}
"EXIST" {
  printf("LEX: KEY: EXIST\n");
}
{ID} {
  printf("LEX: IDENTIFIER: %s\n", yytext);
}  
{DIGIT}+ {
  printf("LEX: NUMBER: %s\n", yytext);
}
[ \t\n\r] {
  // Skip over tab, new line, etc.
}
. {
  printf("LEX: Error: %s\n", yytext );
}

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
  yylex();
}