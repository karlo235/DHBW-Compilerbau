#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

// Possible types in Predicate Logic 1
enum type {
    Predicate, Function, Variable
};
typedef enum type type;

// Datatype of a symbol table entry
struct tableEntry_struct {
    // Entry identifier
    char identifier[101];
    // Entry type
    type type;
    // Number of arguments
    int arity;
    // Pointer on the next element
    struct tableEntry_struct *next;
};

typedef struct tableEntry_struct *tableEntry;

tableEntry addSymbolEntry(char identifier[], type type, int arity);

tableEntry getSymbolEntry(char *identifier);

int checkSymbol(char identifier[], type type);

void printSymbolTable();

void printDeclarations(FILE *f);

#endif