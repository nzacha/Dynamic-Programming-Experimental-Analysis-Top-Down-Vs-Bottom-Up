#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SORTED

unsigned short** usol;
short** sol;

char* getSequenceFromFile(char* filename, int fileSize){
	FILE *fp;
    char str[fileSize];
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return NULL;
    }

    fgets(str, fileSize +1, fp);     
    //printf("%d - %s\n",fileSize, str);
    fclose(fp);

    char* sequence = (char*)calloc((strlen(str)+1), sizeof(char));
    strncpy(sequence, str, (size_t)(strlen(str)));

    return sequence;
}

void* initArray_signed(short*** table, int height, int width, int initVal){
	*table = (short**)calloc(height,sizeof(short*));

	for (int i=0; i<height; i++){
		(*table)[i] = (short*)calloc(width, sizeof(short));
	}

	for (int i=0; i<height; i++){
		for(int j=0; j<width; j++)
			(*table)[i][j] = initVal;
	}
	return NULL;
}

void* initArray_unsigned(unsigned short*** table, int height, int width, int initVal){
	*table = (unsigned short**)calloc(height,sizeof(unsigned short*));

	for (int i=0; i<height; i++){
		(*table)[i] = (unsigned short*)calloc(width, sizeof(unsigned short));
	}

	for (int i=0; i<height; i++){
		for(int j=0; j<width; j++)
			(*table)[i][j] = initVal;
	}
	return NULL;
}

void* printArray_unsigned(unsigned short** table, char* rows, char* columns){
	printf("\n");
	int height = strlen(rows)+1;
	int width = strlen(columns)+1;

	//Print Column Label
	printf("     ");
	for (int i=0; i<width; i++){
		printf("%c ",columns[i]);
	} 
	printf("\n");	

	printf("   ");
	for (int i=0; i<width; i++)
		printf("0 ");
	printf("\n");

	//Print Rows with Label
	for (int i=1; i<height; i++){
		printf("%c| ",rows[i-1]);
		printf("0 ");
		for (int j=1; j<width; j++){
			printf("%d ",table[i][j]);
		}
		printf("\n");
	} 
	return NULL;
}

void* printArray_signed(short** table, char* rows, char* columns){
	printf("\n");
	int height = strlen(rows)+1;
	int width = strlen(columns)+1;

	//Print Column Label
	printf("     ");
	for (int i=0; i<width; i++){
		printf("%c ",columns[i]);
	} 
	printf("\n");	

	printf("   ");
	for (int i=0; i<width; i++)
		printf("0 ");
	printf("\n");

	//Print Rows with Label
	for (int i=1; i<height; i++){
		printf("%c| ",rows[i-1]);
		printf("0 ");
		for (int j=1; j<width; j++){
			printf("%d ",table[i][j]);
		}
		printf("\n");
	} 
	return NULL;
}

void* destroyArray_signed(short** table, int height){
	for(int i=0; i<height; i++)
		free(table[i]);
	free(table);
	return NULL;
}

void* destroyArray_unsigned(unsigned short** table, int height){
	for(int i=0; i<height; i++)
		free(table[i]);
	free(table);
	return NULL;
}

void* findMCSS_iterative(unsigned short** table, char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);

	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			#ifdef DEBUG
				printArray_unsigned(table, seqA, seqB);
			#endif

			if(seqA[i-1] == seqB[j-1]){
				table[i][j] = table[i-1][j-1] +1;
				if(table[i][j]<table[i-1][j-1]){
					printf("Short overflow detected!\n");
					printf("Exiting...\n");
					exit(0);
				}
			}else if(table[i][j-1] <= table[i-1][j]){
				table[i][j] = table[i-1][j];
			}else{
				table[i][j] = table[i][j-1];
			}
		}
	}
	return NULL;
}

int max(int a, int b){
	if(a >= b)
		return a;
	return b;
}

int recur_findMCSS(short** table, char* seqA, char* seqB, int a, int b){	
	if(a<0 || b<0)
		return 0;

	if(table[a+1][b+1] >= 0)
		return table[a+1][b+1];

	if(seqA[a] == seqB[b]){
		table[a+1][b+1] = (recur_findMCSS(table, seqA, seqB, a-1, b-1) +1);
	}else{
		table[a+1][b+1] = max(recur_findMCSS(table, seqA, seqB, a-1, b),recur_findMCSS(table, seqA, seqB, a, b-1));
	}

	#ifdef DEBUG
		printArray_signed(table, seqA, seqB);
		//usleep(200000);
	#endif

	return table[a+1][b+1];
}

void* findMCSS_recursive(short** table, char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);
	recur_findMCSS(table, seqA, seqB, height-1, width-1);
	#ifdef DEBUG
		printArray_signed(table, seqA, seqB);
	#endif
	return NULL;
}

typedef struct __attribute__((packed)) node{
	struct node* next;
	struct node* parent;
	int heightA;
	int heightB;
	int value;
	int cost;
}node;

void node_print(struct node* n){
	if(!n)
		return;
	printf("value:%d\n", n->value);
	printf("cost:%d\n", n->cost);
	printf("height A:%d\n", n->heightA);
	printf("height B:%d\n", n->heightB);
}

void node_init(struct node** n, struct node* next, struct node* parent, int value, int cost, int heightA, int heightB){
	(*n) = (struct node*)malloc(sizeof(struct node));
	(*n)->next = next;
	(*n)->parent = parent;
	(*n)->value = value;
	(*n)->cost = cost;
	(*n)->heightA = heightA;
	(*n)->heightB = heightB;
}

void node_destroy(struct node** n){
	struct node* top = (*n);
	if(!top)
		return;
	free(top);
}

void node_destroy_chain(struct node** n){
	struct node* top = (*n);
	if(!top)
		return;

	struct node* temp;
	do{
	 	temp = top;		
	 	top = top->next;
	 	free(temp);
	}while(top);
}

void node_insert(struct node** root, struct node* newNode){
	if(!(*root)){
		(*root) = newNode;
		return;
	}
	
	newNode->next = *(root);
	(*root) = newNode;							
}

int stack_size(struct node* root){
	int count = 0;
	while(root){
		count++;
		node_print(root);
		root = root->next;
	}
	return count;
}

struct node* stack_pop(struct node** root){
	if(!(*root)){
		return NULL;
	}

	struct node* retNode = *root;	
	(*root) = (*root)->next;
	return retNode;
}

void node_insert_sorted(struct node** root, struct node* newNode){	
	//root is null
	if(!(*root)){
		(*root) = newNode;
		return;
	}

	struct node* tmp = (*root);
	//new node is more promising than root
	if(tmp->value - tmp->cost <= newNode->value - newNode->cost){
		newNode->next = tmp;		
		(*root) = newNode;		
		return;
	}

	do{		
		//new node position is at the end of the stack
		if(!(tmp->next)){
			tmp->next = newNode;			
			return;
		}
		if((tmp->next)->value - (tmp->next)->cost <= newNode->value - newNode->cost){
			newNode->next = tmp->next;
			tmp->next = newNode;
			return;
		}
		tmp = tmp->next;		
	}while(tmp);
}

struct node* findMCSS_recursive_optimised(short** table, char* seqA, char* seqB){
	int height = strlen(seqA);
	int width = strlen(seqB);	
	struct node* stack_top;
	node_init(&stack_top, NULL, NULL, 0, 0, height-1, width-1);	

	struct node* solution = NULL;	
	while(stack_top){
		struct node* currentNode = stack_pop(&stack_top);;
		if(!currentNode){
			printf("Error ocurred; Exiting\n");
			exit(0);
		}

		if(seqA[currentNode->heightA] == seqB[currentNode->heightB])
			currentNode->value++;	
		//skip if table value is not -1 and if its bigger than the current node's value
		if(table[currentNode->heightA +1][currentNode->heightB +1] != -1 && table[currentNode->heightA +1][currentNode->heightB +1] >= currentNode->value){
			#ifdef DEBUG
			printf("The current node is being skipped\n");
			#endif 
			continue;
		}

		#ifdef DEBUG
		printArray_signed(table, seqA, seqB);
		/*		
		printf("The current node is \n");
		node_print(currentNode);
		printf("The stack is:\n");
		printf("size: (%d)\n", stack_size(stack_top));
		*/
		#endif 

		//node reached end of sequence
		if(currentNode->heightA < 0 || currentNode->heightB < 0){
			if(!solution){
				solution = currentNode->parent;				
				//break;
			}else{
				if(solution->value < (currentNode->parent)->value){
					//node_destroy(&solution);
					solution = currentNode->parent;
				}else{
					//node_destroy(&currentNode);
				}
				//break;
			}
			continue;
		}
				
		struct node* newNode;
		//push new node into stack
		if(seqA[currentNode->heightA] == seqB[currentNode->heightB]){
			//if(table[currentNode->heightA][currentNode->heightB] <= currentNode->value){				
				#ifndef SORTED
					node_init(&newNode, stack_top, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA -1, currentNode->heightB -1);
					stack_top = newNode;			
				#else
					node_init(&newNode, NULL, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA -1, currentNode->heightB -1);
					node_insert_sorted(&stack_top, newNode);
				#endif				
			//}
		}else{			
			//if(table[currentNode->heightA][currentNode->heightB +1] < currentNode->value){
				#ifndef SORTED
					node_init(&newNode, stack_top, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA -1, currentNode->heightB);
					stack_top = newNode;
				#else
					node_init(&newNode, NULL, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA -1, currentNode->heightB);
					node_insert_sorted(&stack_top, newNode);
				#endif
			//}
			//if(table[currentNode->heightA +1][currentNode->heightB] < currentNode->value){
				#ifndef SORTED
					node_init(&newNode, stack_top, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA, currentNode->heightB -1);
					stack_top = newNode;
				#else
					node_init(&newNode, NULL, currentNode, currentNode->value, currentNode->cost +1, currentNode->heightA, currentNode->heightB -1);
					node_insert_sorted(&stack_top, newNode);
				#endif
			//}
		}

		table[currentNode->heightA +1][currentNode->heightB +1] = currentNode->value;			
		//usleep(400000);
	}

	//printArray_signed(table,seqA, seqB);
	return solution;
}

void* printSolution_iterative(unsigned short** table, char* seqA, char* seqB){
	#ifdef DEBUG
	printf("\nPrinting solution for \"%s\" and \"%s\"\n", seqA, seqB);
	#endif

	int height = strlen(seqA);
	int width = strlen(seqB);

	char path[height];
	int c = 0;

	int j=width;
	for(int i=height; i>0 && j>0;){
		for(; i>0 && j>0;){
			if(table[i-1][j-1] == table[i-1][j] && table[i-1][j-1] == table[i][j-1] && table[i-1][j-1] == (table[i][j]-1)){
				path[c++]=seqA[i-1];
				i--;
				j--;
			}else if (table[i][j] == table[i-1][j]){
				i--;
			}else{
				j--;
			}
		}
	}
	path[c++]='\0';

	char mcss[c];
	for(int i=0; i<c; i++)
		mcss[i]=path[c-i-2];

	#ifdef DEBUG
		printf("A Most Common SubSequence is: %s\n", mcss);
	#endif
	printf("Solution length is: %ld\n", strlen(mcss));

	return NULL;
}

void* printSolution_recursive(short** table, char* seqA, char* seqB){
	#ifdef DEBUG
	printf("\nPrinting solution for \"%s\" and \"%s\"\n", seqA, seqB);
	#endif

	int height = strlen(seqA);
	int width = strlen(seqB);

	char path[height];
	int c = 0;
	FIXME
	for(int i=height, j=width; i>0 && j>0;){
		if((table[i][j] != 0) && table[i-1][j-1] == (table[i][j]-1) && table[i][j-1] < table[i][j] && table[i-1][j] < table[i][j]){				
			path[c++]=seqA[i-1];
			printf("%c",seqA[i-1]);
			i--;
			j--;
		}else if (table[i][j] == table[i-1][j]){
			i--;
		}else{
			j--;
		}
	}
	printf("\n");
	path[c++]='\0';
	char mcss[c];
	for(int i=0; i<c; i++)
		mcss[i]=path[c-i-2];
	printf("(%d)%s\n",strlen(mcss),mcss);
	printf("(%d)%s\n",strlen(path),path);
	#ifdef DEBUG
		printf("A Most Common SubSequence is: %s\n", mcss);
	#endif	
	printf("Solution length is: %ld\n", strlen(mcss));
	return NULL;
}

void* printSolution_recursive_optimised(struct node* solution, char* seqA, char* seqB){
	#ifdef DEBUG
	printf("\nPrinting solution for \"%s\" and \"%s\"\n", seqA, seqB);	

	if(!solution){
		printf("%s\n", "no solution common sub-sequence found");
		return NULL;
	}

	struct node* tmp = solution;	
	printf("the sub-sequence is: ");
	while(tmp){
		if(!tmp->parent)
			break;		
		if((tmp->parent)->value < tmp->value){		
			printf("%c", seqA[(tmp)->heightA]);			
		}
		tmp = tmp->parent;
	}
	printf("\n");
	#endif

	printf("Solution length is: %d\n", solution->value);
	return NULL;
}

int main(int argc, char** argv){	
	if(argc != 5){
		printf("%s\n", "Correct Format: ./a.out [\"Sequence_A filename\"] [\"Sequence_B filename\"] ['iterative: 1' or 'recursive: 2'] ['File Size']\n");
		return 1;
	}

	char* seqA = getSequenceFromFile(argv[1], atoi(argv[4]));
	char* seqB = getSequenceFromFile(argv[2], atoi(argv[4]));
	if(!seqA || !seqB){
		printf("Unable to read Sequences from Files\n");
		return 1;
	}

	int method = atoi(argv[3]);

	#ifdef DEBUG
		printf("Running \"%s\" with %d arguments \n", argv[0], argc);
		printf("Sequence A: %s (%ld)\n", seqA, strlen(seqA));
		printf("Sequence B: %s (%ld)\n", seqB, strlen(seqB));
	#else
		printf("Sequence_A:%ld\n", strlen(seqA));
		printf("Sequence_B:%ld\n", strlen(seqB));
	#endif
	

	//time starts
	clock_t time;

	if(method == 1){
		initArray_unsigned(&usol, strlen(seqA)+1, strlen(seqB)+1, 0);

		#ifdef DEBUG
			printf("Using Iterative (Bottom-Up) approach\n");
			printArray_unsigned(usol, seqA, seqB);
		#endif

		time = clock();
		findMCSS_iterative(usol, seqA, seqB);
		time = clock() - time;

		#ifdef DEBUG
			printArray_unsigned(usol, seqA, seqB);
		#endif
		printSolution_iterative(usol, seqA, seqB);

		destroyArray_unsigned(usol, strlen(seqA)+1);	
	}else if(method == 2){
		initArray_signed(&sol, strlen(seqA)+1, strlen(seqB)+1, -1);

		#ifdef DEBUG
			printf("Using Recursive (Top-Down) approach\n");
		#endif

		time = clock();
		findMCSS_recursive(sol, seqA, seqB);		
		time = clock() - time;

		#ifdef DEBUG
			printArray_signed(sol, seqA, seqB);
		#endif
		printSolution_recursive(sol,seqA, seqB);

		destroyArray_signed(sol, strlen(seqA)+1);
	}else if(method == 3){
		initArray_signed(&sol, strlen(seqA)+1, strlen(seqB)+1, -1);	

		#ifdef DEBUG
			printf("Using Recursive (Top-Down) approach - OPTIMISED\n");
			#ifdef SORTED
				printf("Using sorted stack\n");
			#endif
		#endif

		time = clock();
		struct node* solution = findMCSS_recursive_optimised(sol, seqA, seqB);		
		time = clock() - time;
		
		printSolution_recursive_optimised(solution, seqA, seqB);		

		destroyArray_signed(sol, strlen(seqA)+1);
	}else{
		printf("Invalid method number!\n");
		return 1;
	}
	
	free(seqA);
	free(seqB);
	
	double time_taken = ((double)time)/CLOCKS_PER_SEC; // calculate the elapsed time
	#ifdef DEBUG
		printf("\nThe program took %f seconds to execute\n", time_taken);	
	#else
		printf("Time_taken:%f\n", time_taken);	
	#endif

	return 0;
}
	