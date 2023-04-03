%{
  #include <stdio.h>
  #include "parser.tab.h"
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
  return DECLARE;
}
"PREDICATE" {
  printf( "LEX: KEY: PREDICATE\n");
  return PREDICATE;
}
"FUNCTION" {
  printf("LEX: KEY: FUNCTION\n");
  return FUNCTION;
}
"VARIABLE" {
  printf("LEX: KEY: VARIABLE\n");
  return VARIABLE;
}
"TRUE" {
  printf("LEX: KEY: TRUE\n");
  return TRUE;
}
"FALSE" {
  printf("LEX: KEY: FALSE\n");
  return FALSE;
}
"int" {
  printf("LEX: KEY: int\n");
  return INT;
}
\: {
  printf("LEX: KEY: Colon\n");
  return DD;
}
\; {
  printf("LEX: KEY: Semicolon\n");
  return SEMICOLON;
}
\, {
  printf("LEX: KEY: Comma\n");
  return COMMA;
}
\( {
  printf("LEX: KEY: Bracket Open\n");
  return OPENPAR;
}
\) {
  printf("LEX: KEY: Bracket Close\n");
  return CLOSEPAR;
}
\[ {
  printf("LEX: KEY: Square Open\n");
  return OPENSQUARE;
}
\] {
  printf("LEX: KEY: Square Close\n");
  return CLOSESQUARE;
}
\& {
  printf("LEX: KEY: AND\n");
  return AND;
}
\| {
  printf("LEX: KEY: OR\n");
  return OR;
}
\~ {
  printf("LEX: KEY: NOT\n");
  return NOT;
}
"->" {
  printf("LEX: KEY: IMPLICATION\n");
  return IMPLICATION;
}
"<->" {
  printf("LEX: KEY: EQUIVALENT\n");
  return EQUIVALENT;
}
"ALL" {
  printf("LEX: KEY: ALL\n");
  return ALL;
}
"EXIST" {
  printf("LEX: KEY: EXIST\n");
  return EXIST;
}
{ID} {
  printf("LEX: IDENTIFIER: %s\n", yytext);
  strcpy(yylval.val,yytext);
  return ID;
}  
{DIGIT}+ {
  printf("LEX: NUMBER: %s\n", yytext);
  yylval.number = atoi(yytext);
  return DIGIT;
}
[ \t\n\r] {
  // Skip over tab, new line, etc.
}
. {
  printf("LEX: Error: %s\n", yytext );
}

%%