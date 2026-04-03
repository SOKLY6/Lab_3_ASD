#ifndef STACK_UTILS_h
#define STACK_UTILS_h

#include "tree_utils.h"

typedef struct OperandNode
{
    TreeNode *operand;
    struct OperandNode *prev;
    struct OperandNode *next;
    
} OperandNode;

typedef struct OperandStack
{
    OperandNode *head;
} OperandStack;


typedef struct OperationNode
{
    char operation;
    struct OperationNode *prev;
    struct OperationNode *next;
    
} OperationNode;

typedef struct OperationStack
{
    OperationNode *head;
} OperationStack;

#endif