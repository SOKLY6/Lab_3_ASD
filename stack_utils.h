#ifndef STACK_UTILS_h
#define STACK_UTILS_h

#include "tree_utils.h"


typedef struct OperandNode
{
    TreeNode *operand;
    struct OperandNode *next;
    
} OperandNode;

typedef struct OperandStack
{
    OperandNode *head;
} OperandStack;


int init_operand_stack(OperandStack *stack);
int insert_operand_stack(OperandStack *stack, TreeNode *operand);
int pop_operand_stack(OperandStack *stack, TreeNode **pop_operand);
int pick_operand_stack(OperandStack *stack, TreeNode **pick_operand);
void destroy_operand_stack(OperandStack *stack);


typedef struct OperationNode
{
    char operation;
    struct OperationNode *next;
} OperationNode;

typedef struct OperationStack
{
    OperationNode *head;
} OperationStack;


int init_operation_stack(OperationStack *stack);
int insert_operation_stack(OperationStack *stack, char operation);
int pop_operation_stack(OperationStack *stack, char *operation);
int pick_operation_stack(OperationStack *stack, char *operation);
void destroy_operation_stack(OperationStack *stack);


#endif