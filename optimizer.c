#include "synTree.h"
#include "optimizer.h"
#include <stdlib.h>

/**
 * @brief Function to remove double negations in formula
 * 
 * @param node start node of which to remove the double negations from
 * @return new start node
 */
struct node *rmDoubleNeg(struct node *node) {
    struct node *newStartNode;
    struct node *left;
    struct node *right;

    switch (node->nodeType) {
        case negation:
            if (node->unary_junctor.formula->nodeType == negation) {
                newStartNode = rmDoubleNeg(node->unary_junctor.formula->unary_junctor.formula);
                free(node->unary_junctor.formula);
                free(node);
            } else {
                newStartNode = rmDoubleNeg(node->unary_junctor.formula);
                newStartNode = node;
            }
            break;
        case all:
        case exist:
            newStartNode = rmDoubleNeg(node->quantor_struct.formula);
            node->quantor_struct.formula = newStartNode;
            newStartNode = node;
            break;
        case and:
        case or:
        case implication:
        case equivalence:
            left = rmDoubleNeg(node->binary_struct.formula_left);
            right = rmDoubleNeg(node->binary_struct.formula_right);
            node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
            newStartNode = node;
            break;
        default:
            newStartNode = node;
    }
    return newStartNode;
}

/**
 * @brief Function to shift negations before predicate in formula
 * 
 * @param node start node of which to shift the double negations from
 * @return new start node
 */
struct node *shiftNeg(struct node *node) {
    struct node *newStartNode;
    struct node *newLeft;
    struct node *newRight;
    struct node *newNegationNode;
    struct node *left;
    struct node *right;

    switch (node->nodeType) {
        case negation:
            switch (node->unary_junctor.formula->nodeType) {
                case and:
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    newRight = shiftNeg(newRight);
                    newLeft = shiftNeg(newLeft);
                    newStartNode = makeDisjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                case or:
                    newLeft = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_left);
                    newRight = makeNegationNode(node->unary_junctor.formula->binary_struct.formula_right);
                    newRight = shiftNeg(newRight);
                    newLeft = shiftNeg(newLeft);
                    newStartNode = makeConjunctionNode(newLeft, newRight);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                case exist:
                    newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
                    newNegationNode = shiftNeg(newNegationNode);
                    newStartNode = makeAllNode(node->unary_junctor.formula->quantor_struct.var, newNegationNode);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                case all:
                    newNegationNode = makeNegationNode(node->unary_junctor.formula->quantor_struct.formula);
                    newNegationNode = shiftNeg(newNegationNode);
                    newStartNode = makeExistNode(node->unary_junctor.formula->quantor_struct.var, newNegationNode);
                    free(node->unary_junctor.formula);
                    free(node);
                    break;
                default:
                    newStartNode = node;
                    break;
            }
            break;
        case all:
        case exist:
            newStartNode = shiftNeg(node->quantor_struct.formula);
            node->quantor_struct.formula = newStartNode;
            newStartNode = node;
            break;
        case and:
        case or:
        case implication:
        case equivalence:
            left = shiftNeg(node->binary_struct.formula_left);
            right = shiftNeg(node->binary_struct.formula_right);
            node->binary_struct.formula_left = left;
            node->binary_struct.formula_right = right;
            newStartNode = node;
            break;
        default:
            newStartNode = node;
    }
    return newStartNode;
}

/**
 * @brief Function to simplify unary and binary junctors in formula
 * 
 * @param node start node from which to simplify the formula
 * @return new start node
 */
struct node *simplifyFormula(struct node *node) {
    struct node *newStartNode;
    struct node *left;
    struct node *right;

    switch (node->nodeType) {
        case and:
        case or:
            node->binary_struct.formula_left = simplifyFormula(node->binary_struct.formula_left);
            node->binary_struct.formula_right = simplifyFormula(node->binary_struct.formula_right);
            newStartNode = node;
            break;
        case negation:
            node->unary_junctor.formula = simplifyFormula(node->unary_junctor.formula);
            newStartNode = node;
            break;
        case all:
        case exist:
            newStartNode = simplifyFormula(node->quantor_struct.formula);
            node->quantor_struct.formula = newStartNode;
            newStartNode = node;
            break;
        case equivalence:
            node->binary_struct.formula_left = simplifyFormula(node->binary_struct.formula_left);
            node->binary_struct.formula_right = simplifyFormula(node->binary_struct.formula_right);
            left = makeConjunctionNode(node->binary_struct.formula_left, node->binary_struct.formula_right);
            struct node *rightNegLeft = makeNegationNode(copyTree(node->binary_struct.formula_left));
            struct node *rightNegRight = makeNegationNode(copyTree(node->binary_struct.formula_right));
            right = makeConjunctionNode(rightNegLeft, rightNegRight);
            newStartNode = makeDisjunctionNode(left, right);
            free(node);
            break;
        case implication:
            node->binary_struct.formula_left = simplifyFormula(node->binary_struct.formula_left);
            node->binary_struct.formula_right = simplifyFormula(node->binary_struct.formula_right);
            left = makeNegationNode(node->binary_struct.formula_left);
            right = node->binary_struct.formula_right;
            newStartNode = makeDisjunctionNode(left, right);
            free(node);
            break;
        default:
            newStartNode = node;
    }
    return newStartNode;
}

/**
 * @brief Function to remove unneccessary TRUE/FALSE booleans in formula
 * 
 * @param node start node from which to remove the booleans from 
 * @return new start node
 */
struct node *removeBooleans(struct node *node) {
    struct node *newStartNode;
    
    switch (node->nodeType) {
        case and:
            node->binary_struct.formula_left = removeBooleans(node->binary_struct.formula_left);
            node->binary_struct.formula_right = removeBooleans(node->binary_struct.formula_right);
            if (node->binary_struct.formula_left->nodeType == true_node) {
                newStartNode = node->binary_struct.formula_right;
                freeTree(node->binary_struct.formula_left);
                free(node);
            } else if (node->binary_struct.formula_right->nodeType == true_node) {
                newStartNode = node->binary_struct.formula_left;
                freeTree(node->binary_struct.formula_right);
                free(node);
            } else if (node->binary_struct.formula_left->nodeType == false_node ||
                       node->binary_struct.formula_right->nodeType == false_node) {
                newStartNode = makeFalseNode();
                freeTree(node->binary_struct.formula_left);
                freeTree(node->binary_struct.formula_right);
                free(node);
            } else {
                newStartNode = node;
            }
            break;
        case or:
            node->binary_struct.formula_left = removeBooleans(node->binary_struct.formula_left);
            node->binary_struct.formula_right = removeBooleans(node->binary_struct.formula_right);

            if (node->binary_struct.formula_left->nodeType == true_node ||
                node->binary_struct.formula_right->nodeType == true_node) {
                newStartNode = makeTrueNode();
                freeTree(node->binary_struct.formula_left);
                freeTree(node->binary_struct.formula_right);
                free(node);
            } else if (node->binary_struct.formula_left->nodeType == false_node) {
                newStartNode = node->binary_struct.formula_right;
                freeTree(node->binary_struct.formula_left);
                free(node);
            } else if (node->binary_struct.formula_right->nodeType == false_node) {
                newStartNode = node->binary_struct.formula_left;
                freeTree(node->binary_struct.formula_right);
                free(node);
            } else {
                newStartNode = node;
            }
            break;
        case negation:
            node->unary_junctor.formula = removeBooleans(node->unary_junctor.formula);
            if (node->unary_junctor.formula->nodeType == true_node) {
                newStartNode = makeFalseNode();
                free(node->unary_junctor.formula);
                free(node);
            } else if (node->unary_junctor.formula->nodeType == false_node) {
                newStartNode = makeTrueNode();
                free(node->unary_junctor.formula);
                free(node);
            } else {
                newStartNode = node;
            }
            break;
        case equivalence:
        case implication:
            node->binary_struct.formula_left = removeBooleans(node->binary_struct.formula_left);
            node->binary_struct.formula_right = removeBooleans(node->binary_struct.formula_right);
            newStartNode = node;
            break;
        case all:
        case exist:
            newStartNode = removeBooleans(node->quantor_struct.formula);
            node->quantor_struct.formula = newStartNode;
            newStartNode = node;
            break;
        default:
            newStartNode = node;
    }
    return newStartNode;
}

/**
 * @brief Function to perform all optimization steps
 * 
 * @param node start node from which to optimize the formula
 * @return start node of the optimized formula
 */
struct node *optimizeFormula(struct node *node) {
    node = simplifyFormula(node);
    node = shiftNeg(node);
    node = rmDoubleNeg(node);
    node = removeBooleans(node);

    return node;
}