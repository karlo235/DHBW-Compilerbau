#include "symTab.h"
#include "synTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Function to create a node of type ALL
 *
 * @param var variable of the all node
 * @param formula_node formula of the all node
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
 * @param var variable of the exist node 
 * @param formula_node formula of the exist node
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
 * @param formula_left_node left node of and
 * @param formula_right_node right node of and
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
 * @param formula_left_node left node of or
 * @param formula_right_node right node of or
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
 * @param formula_left_node left node of implication
 * @param formula_right_node right node of implication
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
 * @param formula_left_node left node of equivalence
 * @param formula_right_node right node of equivalence
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
 * @param formula negated formula
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
 * @param SymTabEntry symbol table entry of the function
 * @param argumentList arguments of the function
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
 * @param SymTabEntry symbol table entry of the predicate
 * @param argumentList arguments of the predicate
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
 * @param SymTabEntry symbol table entry of the variable
 * @return created struct node*
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
 * @return created struct node*
 */
struct node *makeTrueNode() {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = true_node;
    return new_node;
}

/**
 * @brief Function to create a node of type FALSE
 *
 * @return created struct node*
 */
struct node *makeFalseNode() {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = false_node;
    return new_node;
}

/**
 * @brief Function to create a node of type ARGUMENT
 *
 * @param arg argument of the node
 * @return created struct node*
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
 * @param argument_left left argument of the node
 * @param argument_new argument to set as next
 * @return created struct node*
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
 * @param number number value
 * @return created struct node*
 */
struct node *makeNumberNode(int number) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->nodeType = number_t;
    new_node->number = number;
    return new_node;
}

/**
 * @brief Function to check if arity of node is equal to expected arity
 * 
 * @param node syntax tree node to check arity of
 * @param expectedArity expected arity of the node
 */
void checkArity(struct node *node, int expectedArity) {
    int actualArity = countArguments(node->function_struct.argument);
    if (actualArity != expectedArity) {
        fprintf(stderr, "Error: Invalid arity. Expected %d but got %d\n", expectedArity, actualArity);
        exit(1);
    }
}

/**
 * @brief Function to count the number of arguments of a syntax tree node
 * 
 * @param argList argument list of the syntax tree node
 */
int countArguments(struct node *argList) {
    int count = 0;
    struct node *current = argList;
    while (current != NULL) {
        count++;
        current = current->argument_struct.next;
    }
    return count;
}

/**
 * @brief Function to print the syntax tree
 *
 * @param node syntax tree node to print
 * @param level level of the node
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

/**
 * @brief Function to print the formula with brackets if they are needed
 * 
 * @param node syntax tree node to print
 * @param f output file
 * @param ignore_and if = 0 brackets will be printed, if = 1 brackets will not be printed
 */
void printFormulaWithBracketsIfNeeded(struct node* node, FILE *f, int ignore_and) {
    if ((node->nodeType == and && !ignore_and) ||
        node->nodeType == or ||
        node->nodeType == implication ||
        node->nodeType == equivalence) {
        fprintf(f, "(");
        printFormula(node, f);
        fprintf(f, ")");
    } else {
        printFormula(node, f);
    }
}


/**
 * @brief Function to print the formula to the output file
 * 
 * @param node syntax tree node to print
 * @param f output file
 */
void printFormula(struct node *node, FILE *f) {
    if (node != NULL) {
        switch (node->nodeType) {
            case all:
                fprintf(f, "ALL[");
                printFormula(node->quantor_struct.var, f);
                fprintf(f, "]");
                printFormulaWithBracketsIfNeeded(node->quantor_struct.formula, f, 0);
                break;
            case exist:
                fprintf(f, "EXIST[");
                printFormula(node->quantor_struct.var, f);
                fprintf(f, "]");
                printFormulaWithBracketsIfNeeded(node->quantor_struct.formula, f, 0);
                break;
            case and:
                printFormulaWithBracketsIfNeeded(node->binary_struct.formula_left, f, 1);
                fprintf(f, " & ");
                printFormulaWithBracketsIfNeeded(node->binary_struct.formula_right, f, 1);
                break;
            case or:
                printFormula(node->binary_struct.formula_left, f);
                fprintf(f, " | ");
                printFormula(node->binary_struct.formula_right, f);
                break;
            case implication:
                printFormula(node->binary_struct.formula_left, f);
                fprintf(f, " -> ");
                printFormula(node->binary_struct.formula_right, f);
                break;
            case equivalence:
                printFormula(node->binary_struct.formula_left, f);
                fprintf(f, " <-> ");
                printFormula(node->binary_struct.formula_right, f);
                break;
            case negation:
                if (node->unary_junctor.formula->nodeType == predicate) {
                    fprintf(f, "~");
                    printFormula(node->unary_junctor.formula, f);
                } else {
                    fprintf(f, "~(");
                    printFormula(node->unary_junctor.formula, f);
                    fprintf(f, ")");
                }
                break;
            case predicate:
                fprintf(f, "%s(", node->predicate_struct.tableEntry->identifier);
                printFormula(node->predicate_struct.argument, f);
                fprintf(f, ")");
                break;
            case function:
                if (node->function_struct.tableEntry->arity == 0) {
                    fprintf(f, "%s", node->function_struct.tableEntry->identifier);
                } else {
                    fprintf(f, "%s(", node->function_struct.tableEntry->identifier);
                    printFormula(node->function_struct.argument, f);
                    fprintf(f, ")");
                }
                break;
            case variable:
                fprintf(f, "%s", node->variable_struct.tableEntry->identifier);
                break;
            case true_node:
                fprintf(f, "TRUE");
                break;
            case false_node:
                fprintf(f, "FALSE");
                break;
            case number_t:
                fprintf(f, "%d", node->number);
                break;
            case argument_t:
                printFormula(node->argument_struct.argument, f);
                if (node->argument_struct.next != NULL) {
                    fprintf(f, ",");
                    printFormula(node->argument_struct.next, f);
                }
                break;
            default:
                printf("OUT: ERROR: Current nodeType = %d\n", node->nodeType);
                fprintf(f, "ERROR: Current node = %d\n", node->nodeType);
                exit(1);
        }
    }
}

/**
 * @brief Function to delete a (sub)tree of the syntax tree
 * 
 * @param node syntax tree node to delete
 */
void freeTree(struct node* node) {
	if (node != NULL) {
		switch (node->nodeType) {
			case all:
			case exist:
				freeTree(node->quantor_struct.formula);
				free(node);
				break;
			case and:
			case or:
			case implication:
			case equivalence:
				freeTree(node->binary_struct.formula_left);
				freeTree(node->binary_struct.formula_right);
				free(node);
				break;
			case negation:
				freeTree(node->unary_junctor.formula);
				free(node);
				break;
			case predicate:
				freeTree(node->predicate_struct.argument);
				free(node);
				break;
			case function:
				freeTree(node->function_struct.argument);
				free(node);
				break;
			case variable:
				free(node);
				break;
			case true_node:
				free(node);
				break;
			case false_node:
				free(node);
				break;
			case number_t:
				free(node);
				break;
			case argument_t:
				freeTree(node->argument_struct.argument);
				freeTree(node->argument_struct.next);
				free(node);
				break;
			default:
				printf("SYN: ERROR: Couldn't free node - nodeType = %d", node->nodeType);
				exit(1);
		}
	}
}

/**
 * @brief Function to copy a (sub)tree of the syntax tree
 * 
 * @param node syntax tree node to print
 */
struct node *copyTree(struct node* node) {
	struct node *copyNode = NULL;

    if (node != NULL) {
        switch (node->nodeType) {
            case all:
                copyNode = makeAllNode(copyTree(node->quantor_struct.var), copyTree(node->quantor_struct.formula));
                break;
            case exist:
                copyNode = makeExistNode(copyTree(node->quantor_struct.var), copyTree(node->quantor_struct.formula));
                break;
            case and:
                copyNode = makeConjunctionNode(copyTree(node->binary_struct.formula_left), copyTree(node->binary_struct.formula_right));
                break;
            case or:
                copyNode = makeDisjunctionNode(copyTree(node->binary_struct.formula_left), copyTree(node->binary_struct.formula_right));
                break;
            case implication:
                copyNode = makeImplicationNode(copyTree(node->binary_struct.formula_left), copyTree(node->binary_struct.formula_right));
                break;
            case equivalence:
                copyNode = makeEquivalenceNode(copyTree(node->binary_struct.formula_left), copyTree(node->binary_struct.formula_right));
                break;
            case negation:
                copyNode = makeNegationNode(copyTree(node->unary_junctor.formula));
                break;
            case predicate:
                copyNode = makePredicateNode(node->predicate_struct.tableEntry, copyTree(node->predicate_struct.argument));
                break;
            case function:
                copyNode = makeFunctionNode(node->function_struct.tableEntry, copyTree(node->function_struct.argument));
                break;
            case variable:
                copyNode = makeVariableNode(node->function_struct.tableEntry);
                break;
            case true_node:
                copyNode = makeTrueNode();
                break;
            case false_node:
                copyNode = makeFalseNode();
                break;
            case number_t:
                copyNode = makeNumberNode(node->number);
                break;
            case argument_t:
                copyNode = makeArgumentNode(copyTree(node->argument_struct.argument));
                copyNode->argument_struct.next = copyTree(node->argument_struct.next);
                break;
            default:
                printf("SYN: ERROR: Couldn't copy node - nodeType = %d", node->nodeType);
                exit(1);
        }
    }
    return copyNode;
}