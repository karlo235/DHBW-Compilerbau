#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "synTree.h"
#include <stdio.h>

struct node *rmDoubleNeg(struct node *node);

struct node *shiftNeg(struct node *node);

struct node *simplifyFormula(struct node *node);

struct node *removeBooleans(struct node *node);

struct node *optimizeFormula(struct node *node);

#endif