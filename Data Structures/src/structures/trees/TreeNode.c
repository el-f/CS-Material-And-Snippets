#include <stdio.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} tNode;

int main(int argc, char const *argv[])
{
    tNode *root;
    //empty tree declaration
    root = NULL;

    //one node
    root = (tNode *)malloc(sizeof(tNode));
    root->data = 5;
    root->left = NULL;
    root->right = NULL;

    return 0;
}