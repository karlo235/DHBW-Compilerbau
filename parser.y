%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "symTab.h"
    #include "synTree.h"
    #include "optimizer.h"
    extern int yyerror(char *err);
    extern int yylex(void);
    extern FILE *yyin;
    FILE *outputFile;
%}

%union {
    char val[101];
    int number;
    struct node *node;
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
            printSymbolTable();
            printTree($<node>2, 0);
            $<node>2 = optimizeFormula($<node>2);
            printDeclarations(outputFile);
            fprintf(outputFile, "\n");
            printFormula($<node>2, outputFile);
            fprintf(outputFile, " ;\n");
          };

declarations:
          | declarations declaration
          ;

declaration:  
          DECLARE PREDICATE ID DD DIGIT {
            printf("PAR: Declaration: Predicate -%s- Arity: %d\n", $<val>3, $<number>5);
            addSymbolEntry($<val>3, Predicate, $<number>5);
          }
          | DECLARE FUNCTION ID DD DIGIT {
            printf("PAR: Declaration: Function -%s- Arity: %d\n", $<val>3, $<number>5);
            addSymbolEntry($<val>3, Function, $<number>5);
          }
          | DECLARE VARIABLE ID DD INT {
            printf("PAR: Declaration: Variable -%s- Type: %s\n", $<val>3, $<val>5);
            addSymbolEntry($<val>3, Variable, 0);
          }
          ;

formula:  ALL OPENSQUARE ID CLOSESQUARE formula {
            printf("PAR: QUANTOR: ALL %s\n", $<val>3);
            if (checkSymbol($<val>3, Variable)) {
              tableEntry t = getSymbolEntry($<val>3);
              if(t->arity == 0) {
                struct node *var = makeVariableNode(t);
                $<node>$ = makeAllNode(var, $<node>5);
              } else {
                printf("PAR: ERROR: %s ARITY IST NOT 0\n", $<val>3);
                exit(1);  
              }
            } else {
              printf("PAR: ERROR: %s IS NOT A VARIABLE\n", $<val>3);
              exit(1);
            }
          }
          | EXIST OPENSQUARE ID CLOSESQUARE formula {
            printf("PAR: QUANTOR: EXIST %s\n", $<val>3);
            if (checkSymbol($<val>3, Variable)) {
              tableEntry t = getSymbolEntry($<val>3);
              struct node *var = makeVariableNode(t);
              $<node>$ = makeExistNode(var, $<node>5);
            } else if (checkSymbol($<val>3, Function)) {
              tableEntry t = getSymbolEntry($<val>3);
              struct node *var = makeFunctionNode(t, $<node>5);
              $<node>$ = makeExistNode(var, $<node>5);
            } else {
              printf("PAR: ERROR: %s IS NOT A VARIABLE OR A FUNCTION\n", $<val>3);
              exit(1);
            }
          }
          | ID OPENPAR args CLOSEPAR {
            printf("PAR: ATOM: %s()\n", $<val>1);
            if (checkSymbol($<val>1, Predicate)) {
              tableEntry t = getSymbolEntry($<val>1);
              struct node *predicateNode = makePredicateNode(t, $<node>3);
              checkArity(predicateNode, t->arity); 
              $<node>$ = predicateNode;
            } else {
              printf("PAR: ERROR: %s IS NOT A PREDICATE\n", $<val>1);
              exit(1);
            }
          }
          | NOT formula {
            printf("PAR: JUNCTOR: NEGATION\n");
            $<node>$ = makeNegationNode($<node>2);
          }
          | OPENPAR formula CLOSEPAR {
            $<node>$ = $<node>2;
          }
          | formula AND formula {
            printf("PAR: JUNCTOR: AND\n");
            $<node>$ = makeConjunctionNode($<node>1, $<node>3);
          }
          | formula OR formula {
            printf("PAR: JUNCTOR: OR\n");
            $<node>$ = makeDisjunctionNode($<node>1, $<node>3);
          }
          | formula IMPLICATION formula {
            printf("PAR: JUNCTOR: IMPLICATION\n");
            $<node>$ = makeImplicationNode($<node>1, $<node>3);
          }
          | formula EQUIVALENT formula {
            printf("PAR: JUNCTOR: EQUIVILENCE\n");
            $<node>$ = makeEquivalenceNode($<node>1, $<node>3);
          }
          | FALSE {
            $<node>$ = makeFalseNode();
          }
          | TRUE {
            $<node>$ = makeTrueNode();
          }
          ;

args:     {
            printf("PAR: kein Argument\n");
            $<node>$ = NULL;
          }
          | ID {
            printf("PAR: TERM: Variable/Constant %s\n", $<val>1);
            if (checkSymbol($<val>1, Function)) {
              tableEntry t = getSymbolEntry($<val>1);
              struct node *node = makeFunctionNode(t, NULL);
              $<node>$ = makeArgumentNode(node);
            } else if (checkSymbol($<val>1, Variable)) {
              tableEntry t = getSymbolEntry($<val>1);
              struct node *node = makeVariableNode(t);
              $<node>$ = makeArgumentNode(node);
            } else {
              printf("PAR: ERROR: %s IS NOT A VARIABLE OR A FUNCTION\n", $<val>1);
              exit(1);
            }
          }
          | DIGIT {
            printf("PAR: TERM: Variable/Constant %d\n", $<number>1);
            struct node *num = makeNumberNode($<number>1);
            $<node>$ = makeArgumentNode(num);
          }
          | ID OPENPAR args CLOSEPAR {
            if (checkSymbol($<val>1, Function)) {
                tableEntry t = getSymbolEntry($<val>1);
                struct node *functionNode = makeFunctionNode(t, $<node>3);
                checkArity(functionNode, t->arity);
                $<node>$ = makeArgumentNode(functionNode);
            } else {
                printf("PAR: ERROR: %s IS NOT A FUNCTION\n", $<val>1);
                exit(1);
            }
          }
          | args COMMA args {
            $<node>$ = appendArgumentNode($<node>1, $<node>3);
          }
          ;
%%

int yyerror(char *err) {
    printf("Error: %s\n", err);
}
void main(int argc, char *argv[]) {
    ++argv, --argc;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    if (argc > 1)
        outputFile = fopen(argv[1], "w");
    else
        outputFile = fopen("output.pl1", "w");
    yyparse();
}