#include<stdlib.h>
#include<stdio.h>

struct bin_tree {
    unsigned int data;
    struct bin_tree *right, *left;
};

typedef struct bin_tree node;

void insert(node** tree, int val);

void print_preorder(node* tree);

void print_inorder(node* tree);

void print_postorder(node* tree);

void deltree(node* tree);

node* search(node** tree, int val);
