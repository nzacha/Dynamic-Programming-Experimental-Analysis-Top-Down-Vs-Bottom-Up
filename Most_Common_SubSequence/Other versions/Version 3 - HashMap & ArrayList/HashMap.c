#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "HashMap.h"
int growthOffset;

void* initArrayList(struct mapEntry** array, int size, int defKey, int defVal){
	for(int i=0; i<size; i++){
		array[i] = (struct mapEntry*) malloc(sizeof(struct mapEntry));
		array[i]->key = defKey;
		array[i]->val = defVal;		
	}
	return NULL;
}

/*
void* init_array(mapEntry* newArray, int intSize, mapEntry* oldArray, int oldSize){
	return NULL;
}
*/

void* init_arrayList(struct arrayList* list, int capacity){
	list->size = 0;
	list->capacity = growthOffset;
	list->array = (struct mapEntry**) malloc(list->capacity * sizeof(struct mapEntry*));
	list->level = 1;
	initArrayList(list->array, capacity, -1, -1);
	return NULL;
}

void* expandArrayList(struct arrayList* list, int growthOffset){	
	list->level++;
	short newCapacity = list->level * growthOffset;
	struct mapEntry** newArray = (struct mapEntry**) malloc(newCapacity * sizeof(struct mapEntry*));
	initArrayList(newArray, newCapacity, -1, -1);

	struct mapEntry* entry;
	for(int i=0; i < list->capacity; i++){
		entry = list->array[i];
		int key = hashCode(entry->key, newCapacity);		
		if(key >= 0){
			newArray[key]->key = entry->key;
			newArray[key]->val = entry->val;
		}
		free(entry);
	}

	struct mapEntry** temp = list->array;
	list->array = newArray;
	free(temp);

	list->capacity = newCapacity;
	return NULL;
}

struct table* createTable(int size){
	growthOffset = (int) (size * 1.0 / 2);
	if(!growthOffset)
		growthOffset++;

    struct table* t = (struct table*) malloc(sizeof(struct table));
    t->size = size;

    //create table list
    struct arrayList** tableList = (struct arrayList**) malloc(t->size * sizeof(struct arrayList*));

    //create 2nd dimension of table list
    struct arrayList* tempList;
    for(int i = 0; i < t->size; i++){
	    tempList = (struct arrayList*) malloc(size * sizeof(struct arrayList));
	    init_arrayList(tempList, growthOffset);
	    tableList[i] = tempList;
    }

    //initialize struct value
    t->list = tableList;

    return t;
}

int hashCode(int key, int listCapacity){
    return  key % listCapacity;
}

void* insert(struct table* t, int row, int col, int val){		
	struct arrayList* list = t->list[row];

    int pos = hashCode(col, list->capacity);
    while(list->array[pos]->val >= 0){    	
    	expandArrayList(list, growthOffset);
    	pos = hashCode(col, list->capacity);
    }

    list->array[pos]->key = col;
    list->array[pos]->val = val;
    list->size++;
    
    return NULL;
}

int lookup(struct table* t, int row, int col){
	if(row < 0 || col < 0)
		return 0;

	struct arrayList* list = t->list[row];
    int pos = hashCode(col, list->capacity);
    
    if(list->array[pos]->key == col)
    	return list->array[pos]->val;

    return INT_MIN;
}

void printHashMap(struct table* t){	
	int len;
	struct arrayList* list;
	for(int i=0; i<t->size; i++){
		len = 0;
		list = t->list[i];

		struct mapEntry* entry;
		printf("col: %d\n\t", i);
		for(int j=0; j<list->capacity; j++){
			entry = list->array[j];
			if(entry->val >= 0){
				printf("(%d, %d): %d,", i, entry->key, entry->val);
				len++;
			}
		}		
		printf("\n");
		printf("\tlength: %d\n\n", len);
	}
}

void destroyHashMap(struct table* t){
	for(int i=0; i < t->size; i++)	{
		struct arrayList* list = t->list[i];
		for(int j=0; j < list->capacity; j++){
			free(list->array[j]);
		}
		free(list->array);		
		free(list);
	}
	free(t->list);
	free(t);
}

#ifdef DEBUG_HASHMAP
int main(){
    struct table* t = createTable(8);
    printf("Table was created successfully?\n");
    insert(t, 1, 1, 1);
    insert(t, 1 ,2, 2);
    insert(t, 1 ,3, 3);
    insert(t, 1 ,4, 4);
    insert(t, 1 ,5, 5);    
    insert(t, 2, 1, 6);
    insert(t, 2 ,2, 7);
    insert(t, 2 ,3, 8);
    insert(t, 2 ,4, 9);
    insert(t, 2 ,5, 10);
  
    printHashMap(t);

    printf("%d\n", lookup(t, 1, 1));
    printf("%d\n", lookup(t, 2, 2));
    printf("%d\n", lookup(t, 3, 3));

    insert(t, 7, 7, 7);
    printf("%d\n", lookup(t, 7, 7));    
    printf("%d\n", lookup(t, 7, 6));    
    return 0;
}
#endif