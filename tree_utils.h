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

typedef struct Tree
{
    TreeNode *root;
} Tree;


int init_tree(Tree *tree);
int create_operand_tree_node(TreeNode **node, int operand);
int create_operation_tree_node(TreeNode **node, char operation, TreeNode **left_operand, TreeNode **right_operand);
int transformation_tree(Tree *tree);
void print_tree(const TreeNode *root, int level);
void destroy_tree(Tree *tree);


#endif
