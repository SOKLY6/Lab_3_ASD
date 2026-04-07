#include <stdio.h>

#include "parse.h"
#include "tree_utils.h"
#include "errors.h"


static void print_error_message(int res)
{
    switch (res)
    {
    case ALLOCATION_MEMORY_ERROR:
        printf("allocation memory error\n");
        break;
    case REALLOCATION_MEMORY_ERROR:
        printf("reallocation memory error\n");
        break;
    case PTR_NULL:
        printf("ptr null\n");
        break;
    case STACK_IS_EMPTY:
        printf("stack is empty\n");
        break;
    case STACK_NOT_INIT:
        printf("stack not init\n");
        break;
    case TREE_NOT_INIT:
        printf("tree not init\n");
        break;
    case TREE_IS_EMPTY:
        printf("tree is empty\n");
        break;
    case INCORRECT_VALUE_ERROR:
        printf("incorrect value error\n");
        break;
    case OPENING_FILE_ERROR:
        printf("opening file error\n");
        break;
    case VALUE_ERROR:
        printf("value error\n");
        break;
    case INCORRECT_DATA_FORMAT:
        printf("incorrect data format\n");
        break;
    case INCORRECT_KEY_VALUE_FORMAT:
        printf("incorrect key value format\n");
        break;
    default:
        printf("unknown error\n");
        break;
    }
}


int main(void)
{
    Tree tree;
    int res = init_tree(&tree);
    if (res)
    {
        print_error_message(res);
        return res;
    }

    res = parse(&tree);
    if (res)
    {
        print_error_message(res);
        return res;
    }

    printf("before\n");
    print_tree(tree.root, 0);

    res = transformation_tree(&tree);
    if (res)
    {
        print_error_message(res);
        destroy_tree(&tree);
        return res;
    }

    printf("\nafter\n");
    print_tree(tree.root, 0);

    destroy_tree(&tree);
    return 0;
}
