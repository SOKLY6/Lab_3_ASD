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
            create_operand_tree_node(node, operand);
            insert_operand_stack(&operands, node);
        }
        if (c == '\n' || c == 'EOF')
        {
            break;
        }
        if (isspace(c))
        {
            continue;
        }
        if (is_operation(c))
        {
            insert_operation_stack(&operations, c);
        }
        if (isalnum(c))
        {
            *nb = c;
            nb++;
            number_key = 1;
        }
    }
}