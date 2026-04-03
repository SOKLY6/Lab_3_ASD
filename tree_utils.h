#ifndef TREE_UTILS_h
#define TREE_UTILS_h

typedef union Value
{
    int operand;
    char operation;
} Value;

typedef struct TreeNode
{
    Value value;
    struct TreeNode *left;
    struct TreeNode *right;    
} TreeNode;

#endif
