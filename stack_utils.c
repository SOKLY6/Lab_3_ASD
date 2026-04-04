#include <stdlib.h>

#include "stack_utils.h"
#include "errors.h"


int init_operand_stack(OperandStack *stack)
{
    if (stack == NULL) 
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    stack->head = NULL;
    return 0;
}


int insert_operand_stack(OperandStack *stack, TreeNode *operand)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }
    OperandNode *node = (OperandNode *)malloc(sizeof(OperandNode));
    if (node == NULL)
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    node->operand = operand;
    node->next = stack->head;
    stack->head = node;
    return 0;
}


int pop_operand_stack(OperandStack *stack, TreeNode **pop_operand)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }
    if (stack->head == NULL)
    {
        return STACK_IS_EMPTY;
    }
    OperandNode *node = stack->head;
    *pop_operand = node->operand;
    stack->head = node->next;
    free(node);
    return 0;
}


int pick_operand_stack(OperandStack *stack, TreeNode **pick_operand)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }
    if (stack->head == NULL)
    {
        return STACK_IS_EMPTY;
    }
    *pick_operand = stack->head->operand;
    return 0;
}


void destroy_operand_stack(OperandStack *stack)
{
    if (stack == NULL) 
    {
        return;
    }
    while(stack->head != NULL)
    {
        OperandNode *node = stack->head;
        stack->head = stack->head->next;
        free(node);
    }
    return;
}


int init_operation_stack(OperationStack *stack)
{
    if (stack == NULL) 
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    stack->head = NULL;
    return 0;
}


int insert_operation_stack(OperationStack *stack, char operation)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }

    OperationNode *node = (OperationNode *)malloc(sizeof(OperationNode));
    if (node == NULL)
    {
        return ALLOCATION_MEMORY_ERROR;
    }

    node->operation = operation;
    node->next = stack->head;
    stack->head = node;
    return 0;
}


int pop_operation_stack(OperationStack *stack, char *operation)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }
    if (stack->head == NULL)
    {
        return STACK_IS_EMPTY;
    }
    OperationNode *node = stack->head;
    *operation = node->operation;
    stack->head = node->next;
    free(node);
    return 0;
}


int pick_operation_stack(OperationStack *stack, char *operation)
{
    if (stack == NULL) 
    {
        return STACK_NOT_INIT;
    }
    if (stack->head == NULL)
    {
        return STACK_IS_EMPTY;
    }
    *operation = stack->head->operation;
    return 0;
}


void destroy_operation_stack(OperationStack *stack)
{
    if (stack == NULL) 
    {
        return;
    }
    while (stack->head != NULL)
    {
        OperationNode *node = stack->head;
        stack->head = stack->head->next;
        free(node);
    }
    return;
}