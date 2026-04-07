#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "tree_utils.h"
#include "stack_utils.h"
#include "errors.h"


int is_operation(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
        return 1;
    default:
        return 0;
    }
}


int operation_priority(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
    case '%':
        return 1;
    case '^':
        return 2;
    }
}


int parse(Tree *tree)
{
    OperationStack operations;
    init_operation_stack(&operations);
    OperandStack operands;
    init_operand_stack(&operands);

    int number_key = 0;
    char number[BUFSIZ];
    char *nb = number;
    char c;
    
    while(c = getchar())
    {
        if (!isalnum(c) && number_key)
        {
            if (number[0] == '0')
            {
                return INCORRECT_VALUE_ERROR;
            }
            nb = '\0';
            int operand = atoi(number);
            nb = number;
            TreeNode *node;
            if (create_operand_tree_node(node, operand))
            {
                return ALLOCATION_MEMORY_ERROR;
            }
            if (insert_operand_stack(&operands, node))
            {
                free(node);
                return ALLOCATION_MEMORY_ERROR;
            }
            continue;
        }
        if (c == '\n' || c == 'EOF')
        {
            break;
        }
        if (isspace(c))
        {
            continue;
        }
        if (c == '(')
        {
            if (insert_operation_stack(&operations, c))
            {
                return ALLOCATION_MEMORY_ERROR;
            }
        }
        if (is_operation(c))
        {
            char operation;
            while (!peek_operation_stack(&operations, &operation) && (operation_priority(operation) <= operation_priority(c)))
            {
                TreeNode *right;
                TreeNode *left;
                if (pop_operand_stack(&operands, &right) || pop_operand_stack(&operands, &left)
                    || pop_operation_stack(&operations, &operation))
                {
                    return STACK_IS_EMPTY;
                }
                TreeNode *new_node;
                if (create_operation_tree_node(&new_node, operation, &left, &right))
                {
                    free(right);
                    free(left);
                    return ALLOCATION_MEMORY_ERROR;
                }
                if (insert_operand_stack(&operands, new_node))
                {
                    free(right);
                    free(left);
                    return ALLOCATION_MEMORY_ERROR;
                }
            }
            if (insert_operation_stack(&operations, c))
            {
                return ALLOCATION_MEMORY_ERROR;
            }
        }
        if (c == ')')
        {
            char operation;
            while (!peek_operation_stack(&operations, &operation) && operation != '(')
            {
                TreeNode *right;
                TreeNode *left;
                if (pop_operand_stack(&operands, &right) || pop_operand_stack(&operands, &left)
                    || pop_operation_stack(&operations, &operation))
                {
                    return STACK_IS_EMPTY;
                }
                TreeNode *new_node;
                if (create_operation_tree_node(&new_node, operation, &left, &right))
                {
                    free(right);
                    free(left);
                    return ALLOCATION_MEMORY_ERROR;
                }
                if (insert_operand_stack(&operands, new_node))
                {
                    free(right);
                    free(left);
                    return ALLOCATION_MEMORY_ERROR;
                }
            }
            if (pop_operation_stack(&operations, &operation))
            {
                return INCORRECT_VALUE_ERROR;
            }
        }
        if (isalnum(c))
        {
            *nb = c;
            nb++;
            number_key = 1;
        }
    }
}