#include "symTab.h"
#include "synTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Function to create a node of type ALL
 *
 * @param var
 * @param formula_node
 * @return created struct node*
 */
struct node *makeAllNode(struct node *var, struct node *formula_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = all;
    new_node->quantor_struct.formula = formula_node;
    new_node->quantor_struct.var = var;
    return new_node;
}

/**
 * @brief Function to create a node of type EXIST
 *
 * @param var
 * @param formula_node
 * @return created struct node*
 */
struct node *makeExistNode(struct node *var, struct node *formula_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = exist;
    new_node->quantor_struct.formula = formula_node;
    new_node->quantor_struct.var = var;
    return new_node;
}

/**
 * @brief Function to create a node of type AND
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return created struct node*
 */
struct node *makeConjunctionNode(struct node *formula_left_node, struct node *formula_right_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = and;
    new_node->binary_struct.formula_left = formula_left_node;
    new_node->binary_struct.formula_right = formula_right_node;
    return new_node;
}

/**
 * @brief Function to create a node of type OR
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return created struct node*
 */
struct node *makeDisjunctionNode(struct node *formula_left_node, struct node *formula_right_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = or;
    new_node->binary_struct.formula_left = formula_left_node;
    new_node->binary_struct.formula_right = formula_right_node;
    return new_node;
}

/**
 * @brief Function to create a node of type IMPLICATION
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return created struct node*
 */
struct node *makeImplicationNode(struct node *formula_left_node, struct node *formula_right_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = implication;
    new_node->binary_struct.formula_left = formula_left_node;
    new_node->binary_struct.formula_right = formula_right_node;
    return new_node;
}

/**
 * @brief Function to create a node of type EQUIVALENT
 *
 * @param formula_left_node
 * @param formula_right_node
 * @return created struct node*
 */
struct node *makeEquivalenceNode(struct node *formula_left_node, struct node *formula_right_node) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = equivalence;
    new_node->binary_struct.formula_left = formula_left_node;
    new_node->binary_struct.formula_right = formula_right_node;
    return new_node;
}

/**
 * @brief Function to create a node of type NOT
 *
 * @param formula
 * @return created struct node*
 */
struct node *makeNegationNode(struct node *formula) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = negation;
    new_node->unary_junctor.formula = formula;
    return new_node;
}

/**
 * @brief Function to create a node of type FUNCTION
 *
 * @param SymTabEntry
 * @param argumentList
 * @return created struct node*
 */
struct node *makeFunctionNode(tableEntry SymTabEntry, struct node *argumentList) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = function;
    new_node->function_struct.tableEntry = SymTabEntry;
    new_node->function_struct.argument = argumentList;
    return new_node;
}

/**
 * @brief Function to create a node of type PREDICATE
 *
 * @param SymTabEntry
 * @param argumentList
 * @return created struct node*
 */
struct node *makePredicateNode(tableEntry SymTabEntry, struct node *argumentList) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = predicate;
    new_node->predicate_struct.tableEntry = SymTabEntry;
    new_node->predicate_struct.argument = argumentList;
    return new_node;
}

/**
 * @brief Function to create a node of type VARIABLE
 *
 * @param SymTabEntry
 * @return struct node*
 */
struct node *makeVariableNode(tableEntry SymTabEntry) {

    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = variable;
    new_node->variable_struct.tableEntry = SymTabEntry;
    return new_node;
}

/**
 * @brief Function to create a node of type TRUE
 *
 * @return struct node*
 */
struct node *makeTrueNode() {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = true_node;
    return new_node;
}

/**
 * @brief Function to create a node of type FALSE
 *
 * @return struct node*
 */
struct node *makeFalseNode() {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = false_node;
    return new_node;
}

/**
 * @brief Function to create a node of type ARGUMENT
 *
 * @return struct node*
 */
struct node *makeArgumentNode(struct node *arg) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = argument_t;
    new_node->argument_struct.argument = arg;
    new_node->argument_struct.next = NULL;
    return new_node;
}

/**
 * @brief Function to append an argument node
 *
 * @param argument_left
 * @param argument_new
 * @return struct node*
 */
struct node *appendArgumentNode(struct node *argument_left, struct node *argument_new) {
    struct node *temp = argument_left;
    while (temp->argument_struct.next != NULL) {
        temp = temp->argument_struct.next;
    }
    temp->argument_struct.next = argument_new;
    argument_new->argument_struct.next = NULL;
    return argument_left;
}

/**
 * @brief Function to create a node of type NUMBER
 *
 * @return struct node*
 */
struct node *makeNumberNode(int number) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = number_t;
    new_node->number = number;
    return new_node;
}

/**
 * @brief Function to print the syntax tree
 *
 * @param node
 * @param level
 */
void printTree(struct node *node, int level) {
    if (node != NULL) {
        if (node->nodeType != argument_t) {
            printf("SYN: ");
            for (int i = 0; i < level; i++) {
                printf(".");
            }
        }
        switch (node->nodeType) {
            case all:
                printf("ALL\n");
                printTree(node->quantor_struct.var, level + 1);
                printTree(node->quantor_struct.formula, level + 1);
                break;
            case exist:
                printf("EXIST\n");
                printTree(node->quantor_struct.var, level + 1);
                printTree(node->quantor_struct.formula, level + 1);
                break;
            case and:
                printf("AND\n");
                printTree(node->binary_struct.formula_left, level + 1);
                printTree(node->binary_struct.formula_right, level + 1);
                break;
            case or:
                printf("OR\n");
                printTree(node->binary_struct.formula_left, level + 1);
                printTree(node->binary_struct.formula_right, level + 1);
                break;
            case implication:
                printf("IMPLICATION\n");
                printTree(node->binary_struct.formula_left, level + 1);
                printTree(node->binary_struct.formula_right, level + 1);
                break;
            case equivalence:
                printf("EQUIVALENCE\n");
                printTree(node->binary_struct.formula_left, level + 1);
                printTree(node->binary_struct.formula_right, level + 1);
                break;
            case negation:
                printf("NEGATION\n");
                printTree(node->unary_junctor.formula, level + 1);
                break;
            case predicate:
                printf("PREDICATE: %s\n", node->predicate_struct.tableEntry->identifier);
                printTree(node->predicate_struct.argument, level + 1);
                break;
            case function:
                printf("FUNCTION: %s\n", node->function_struct.tableEntry->identifier);
                printTree(node->function_struct.argument, level + 1);
                break;
            case variable:
                printf("VARIABLE: %s\n", node->variable_struct.tableEntry->identifier);
                break;
            case true_node:
                printf("TRUE\n");
                break;
            case false_node:
                printf("FALSE\n");
                break;
            case number_t:
                printf("NUMBER %d\n", node->number);
                break;
            case argument_t:
                printTree(node->argument_struct.argument, level);
                if (node->argument_struct.next != NULL) {
                    printTree(node->argument_struct.next, level);
                }
                break;
            default:
                printf("SYN: ERROR: Unknown syntax tree node, aborting printing the tree\n");
                exit(1);
        }
    }
}