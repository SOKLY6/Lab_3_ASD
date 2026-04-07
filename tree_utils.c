#include <stdio.h>
#include <stdlib.h>

#include "tree_utils.h"
#include "errors.h"


int init_tree(Tree *tree)
{
    if (tree == NULL)
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    tree->root = NULL;
    return 0;
}


int create_operand_tree_node(TreeNode **node, int operand)
{
    Value value;
    value.operand = operand;
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node == NULL)
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    *node = new_node;
    return 0;
}


int create_operation_tree_node(TreeNode **node, char operation,
    TreeNode **left_operand, TreeNode **right_operand)
{
    Value value;
    value.operation = operation;
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node == NULL)
    {
        return ALLOCATION_MEMORY_ERROR;
    }
    new_node->value = value;
    new_node->left = *left_operand;
    new_node->right = *right_operand;
    *node = new_node;
    return 0;
}


static void transformation_root(TreeNode *root, int minus_flag)
{
    if (root->left == NULL && root->right == NULL)
    {
        if (minus_flag != 0)
        {
            root->value.operand *= -1;
        }
        return;
    }
    char operation = root->value.operation;
    switch (operation)
    {
    case '-':
        root->value.operation = '+';
        transformation_root(root->left, minus_flag);
        transformation_root(root->right, !minus_flag);
        break;
    case '+':
        transformation_root(root->left, minus_flag);
        transformation_root(root->right, minus_flag);
        break;
    case '*':
    case '/':
    case '%':
        transformation_root(root->left, minus_flag);
        transformation_root(root->right, 0);
        break;
    default:
        break;
    }
}


int transformation_tree(Tree *tree)
{
    if (tree == NULL)
    {
        return TREE_NOT_INIT;
    }
    if (tree->root == NULL)
    {
        return TREE_IS_EMPTY;
    }
    transformation_root(tree->root, 0);
    return 0;
}


void print_tree(const TreeNode *root, int level)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->right, level + 1);
    printf("%*s", level * 4, "");
    if (root->left == NULL && root->right == NULL)
    {
        printf("%d\n", root->value.operand);
    }
    else
    {
        printf("%c\n", root->value.operation);
    }
    print_tree(root->left, level + 1);
}


static void destroy_root(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    destroy_root(root->left);
    destroy_root(root->right);

    free(root);
    return;
}

void destroy_tree(Tree *tree){
    if (tree == NULL) {
        return;
    }
    destroy_root(tree->root);
    return;
}
