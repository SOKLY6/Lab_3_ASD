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


int create_operation_tree_node(char operation);


int transformation_tree(Tree *tree)
{

}


void destroy_root(TreeNode *root) {
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