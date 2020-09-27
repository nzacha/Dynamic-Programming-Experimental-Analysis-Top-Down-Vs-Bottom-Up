#include <stdio.h>
#include <stdlib.h>

struct mapEntry{
	short key;
	short val;
}__attribute__((packed));

struct arrayList{
	unsigned char level;
	short size;
	short capacity;
	struct mapEntry** array;
}__attribute__((packed));

struct table{
    short size;
    struct arrayList** list;
}__attribute__((packed));

void* initArrayList(struct mapEntry** array, int size, int defKey, int defVal);

void* init_arrayList(struct arrayList* list, int capacity);

void* expandArrayList(struct arrayList* list, int growthOffset);

struct table* createTable(int size);

int hashCode(int key, int listCapacity);

void* insert(struct table* t, int row, int col, int val);

int lookup(struct table* t, int row, int col);

void printHashMap(struct table* t);

void destroyHashMap(struct table* t);

