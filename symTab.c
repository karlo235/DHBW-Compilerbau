#include "symTab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

tableEntry actSymTable = NULL;

/**
 * @brief Function to add a new entry into the symbol table
 *
 * @param identifier Identifier
 * @param type Type
 * @param arity Arity
 * @return newly created table entry
 */
tableEntry addSymbolEntry(char identifier[], type type, int arity) {
    // Check if the symbol is already in the table
    if (getSymbolEntry(identifier) == NULL) {
        tableEntry new_tableEntry;
        new_tableEntry = (tableEntry) malloc(sizeof(struct tableEntry_struct));
        strcpy(new_tableEntry->identifier, identifier);
        new_tableEntry->type = type;
        new_tableEntry->arity = arity;
        new_tableEntry->next = NULL;

        // Check if a table already exists and initialize one if not
        if (actSymTable == NULL) {
            printf("SYM: Initializing symbol table\n");
            actSymTable = new_tableEntry;
        }
            // Append the entry to an existing table
        else {
            tableEntry temp = actSymTable;
            // Find the last entry
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_tableEntry;
            temp = NULL;
            // free(temp);
        }
        return new_tableEntry;
    } else {
        printf("SYM: Can't add symbol: ID already exists!\n");
        return NULL;
    }
}

/**
 * @brief  Function to find a symbol table entry based on an identifier
 * 
 * @param identifier Identifier
 * @return tableEntry of found entry or NULL if no entry is found
 */
tableEntry getSymbolEntry(char identifier[]) {
    tableEntry temp = actSymTable;
    while (temp != NULL) {
        if ((strcmp(temp->identifier, identifier) == 0))
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/**
 * @brief Function to check if a symbol table entry is of a given type
 * 
 * @param identifier
 * @return 0 if check unsuccessful or 1 if check successful
 */
int checkSymbol(char identifier[], type type) {

    tableEntry temp = getSymbolEntry(identifier);
    if (temp->type == type)
        return 1;
    else
        return 0;
}

/**
 * @brief Helper function for printing the symbol table, prints the given string repeatedly
 */
void printFor(char *str, int iter) {
    for (int i = 0; i < iter; ++i) {
        printf("%s", str);
    }
}

/**
 * @brief Helper function for printing the symbol table, centers and prints the given string
 */
void printText(const char *text, int cellWidth) {
    int rest = cellWidth - strlen(text);
    double whitespace = rest / 2;

    printf("|");
    printFor(" ", whitespace);
    printf("%s", text);

    if (rest % 2 == 1) { ++whitespace; }
    printFor(" ", whitespace);
}

/**
 * @brief Function to print the symbol table
 */
void printSymbolTable() {
    int cellWidth = 17;
    int lineWidth = cellWidth * 4 + 5;
    char const *types[] = {"Predicate", "Function", "Variable"};
    char buffer[100];

    // Print the outer border with headline
    printf("\n");
    printFor("-", lineWidth / 2 - 7);
    printf(" Symbol Table ");
    printFor("-", lineWidth / 2 - 6);
    printf("\n");

    // Print the head row of the table
    char *a = malloc(256);
    strcpy(a, "#");
    printText(a, cellWidth);
    strcpy(a, "ID");
    printText(a, cellWidth);
    strcpy(a, "Type");
    printText(a, cellWidth);
    strcpy(a, "Arity");
    printText(a, cellWidth);

    printf("|\n");
    printFor("-", lineWidth);
    printf("\n");

    int index = 1;
    tableEntry temp = actSymTable;

    // Iterate over the entries and print a row for each one
    while (temp != NULL) {
        sprintf(buffer, "%d", index);
        printText(buffer, cellWidth);
        printText(temp->identifier, cellWidth);
        printText(types[temp->type], cellWidth);
        sprintf(buffer, "%d", temp->arity);
        printText(buffer, cellWidth);
        printf("|");
        printf("\n");
        printFor("-", lineWidth);
        printf("\n");
        index++;
        temp = temp->next;
    }
    temp = NULL;
}