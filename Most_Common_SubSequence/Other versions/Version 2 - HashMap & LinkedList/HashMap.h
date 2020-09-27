#include <stdio.h>
#include <stdlib.h>

struct node{
    unsigned short key;
    unsigned short val;
    struct node* next;
}__attribute__((packed));

struct table{
    int size;
    struct node** list;
}__attribute__((packed));

struct table* createHashMap(int size);

int hashCode(struct table* t, int key);

void insert(struct table* t, int row, int col, int val);

int lookup(struct table* t, int row, int col);

void printHashMap(struct table* t);

void destroyHashMap(struct table* t);