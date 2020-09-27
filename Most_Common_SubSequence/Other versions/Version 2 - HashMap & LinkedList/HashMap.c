#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "HashMap.h"


struct table* createHashMap(int size){
    struct table* t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(size * sizeof(struct node*));
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}

int hashCode(struct table* t, int key){
    return key%t->size;
}

/*
int getKey(int col, int tableSize){
	return col;
}*/

void insert(struct table* t, int row, int col, int val){		
	//int key = getKey(row, col, t->size);
    int pos = hashCode(t, col);

    struct node* list = t->list[pos];
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    	
    struct node* temp = list;

    while(temp){
        if(temp->key == row){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }

    newNode->key = row;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}

int lookup(struct table* t, int row, int col){
	//int key = getKey(row, col, t->size);
    int pos = hashCode(t, col);
    if(pos < 0)
        return INT_MIN;
    
    struct node* list = t->list[pos];
    struct node* temp = list;

    while(temp){
        if(temp->key == row){
            return temp->val;
        }
        temp = temp->next;
    }

    return INT_MIN;
}

void printHashMap(struct table* t){
	struct node* temp;
	for(int i=0; i<t->size; i++){
		temp = t->list[i];
		printf("col: %d\n\t", i);
		while(temp){
			printf("(%d, %d): %d", i, temp->key, temp->val);
			temp=temp->next;
			if(temp)
				printf(", ");
		}
		printf("\n");
	}
}

void destroyHashMap(struct table* t){
    for(int i=0; i < t->size; i++){
        struct node* node = t->list[i];
        struct node* prev = NULL;
        while(node){
            prev = node;
            node = node->next;
            if(prev)
                free(prev);
        }   
    }
    free(t->list);
    free(t);
}

/*
int main(){
    struct table *t = createTable(5);
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
    return 0;
}
*/