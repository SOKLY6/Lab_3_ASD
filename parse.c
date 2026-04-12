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
    default:
        return -1;
    }
}


static int push_number_operand(OperandStack *operands, char *number, char **nb)
{
    **nb = '\0';
    if (strlen(number) != 1 && number[0] == '0')
    {
        return INCORRECT_VALUE_ERROR;
    }
    int operand = atoi(number);
    *nb = number;
    TreeNode *node;
    if (create_operand_tree_node(&node, operand))
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    if (insert_operand_stack(operands, node))
    {
        free(node);
        return ALLOCATION_MEMORY_ERROR;
    }
    return 0;
}


static int make_operation_node(OperandStack *operands, OperationStack *operations)
{
    char operation;
    TreeNode *right;
    TreeNode *left;
    if (pop_operand_stack(operands, &right) || pop_operand_stack(operands, &left)
        || pop_operation_stack(operations, &operation))
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
    if (insert_operand_stack(operands, new_node))
    {
        free(right);
        free(left);
        return ALLOCATION_MEMORY_ERROR;
    }
    return 0;
}


static int process_operation(OperandStack *operands, OperationStack *operations, char current_operation)
{
    char operation;
    while (!peek_operation_stack(operations, &operation) && operation != '('
        && (operation_priority(operation) >= operation_priority(current_operation)))
    {
        int res = make_operation_node(operands, operations);
        if (res)
        {
            return res;
        }
    }
    if (insert_operation_stack(operations, current_operation))
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    return 0;
}


static int process_closing_bracket(OperandStack *operands, OperationStack *operations)
{
    char operation;
    while (!peek_operation_stack(operations, &operation) && operation != '(')
    {
        int res = make_operation_node(operands, operations);
        if (res)
        {
            return res;
        }
    }
    if (pop_operation_stack(operations, &operation))
    {
        return INCORRECT_VALUE_ERROR;
    }
    return 0;
}


static int finish_parse(Tree *tree, OperandStack *operands, OperationStack *operations, int number_key, char *number, char **nb)
{
    if (number_key)
    {
        int res = push_number_operand(operands, number, nb);
        if (res)
        {
            return res;
        }
    }

    while (!is_empty_operation_stack(operations))
    {
        char operation;
        if (!peek_operation_stack(operations, &operation) && operation == '(')
        {
            return INCORRECT_VALUE_ERROR;
        }
        int res = make_operation_node(operands, operations);
        if (res)
        {
            return res;
        }
    }

    TreeNode *root;
    if (pop_operand_stack(operands, &root))
    {
        return STACK_IS_EMPTY;
    }

    if (!is_empty_operand_stack(operands))
    {
        return INCORRECT_VALUE_ERROR;
    }

    tree->root = root;
    return 0;
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
    int c;
    
    while((c = getchar()) != EOF)
    {
        if (!isalnum(c) && number_key)
        {
            int res = push_number_operand(&operands, number, &nb);
            if (res)
            {
                destroy_operation_stack(&operations);
                destroy_operand_stack(&operands);
                return res;
            }
            number_key = !number_key;
        }
        if (c == '\n')
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
                destroy_operation_stack(&operations);
                destroy_operand_stack(&operands);
                return ALLOCATION_MEMORY_ERROR;
            }
            continue;
        }
        if (is_operation(c))
        {
            int res = process_operation(&operands, &operations, c);
            if (res)
            {
                destroy_operation_stack(&operations);
                destroy_operand_stack(&operands);
                return res;
            }
            continue;
        }
        if (c == ')')
        {
            int res = process_closing_bracket(&operands, &operations);
            if (res)
            {
                destroy_operation_stack(&operations);
                destroy_operand_stack(&operands);
                return res;
            }
            continue;
        }
        if (isalnum(c))
        {
            *nb = c;
            nb++;
            number_key = 1;
            continue;
        }
        destroy_operation_stack(&operations);
        destroy_operand_stack(&operands);
        return INCORRECT_VALUE_ERROR;
    }

    int res = finish_parse(tree, &operands, &operations, number_key, number, &nb);
    if (res)
    {
        destroy_operation_stack(&operations);
        destroy_operand_stack(&operands);
    }
    return res;
}
