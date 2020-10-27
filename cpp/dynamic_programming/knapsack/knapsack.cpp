#include "knapsack.h"

class Arguments : public Problem_Arguments{
    public:
        Item** items;
        int** weights;

        Arguments(Item** items){
            this->items = items;
        }
};

class Knapsack : public Problem <int>{
    public: 
        Knapsack(int problem_size, int sack_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = sack_size;

            args = new Arguments((Item**)generateData());
        }

        void* generateData(){
            Item** items = new Item*[PROBLEM_SIZE];

            /* initialize random seed: */
            srand (time(NULL));
            /* initialize items */
            for( int i=0; i< PROBLEM_SIZE; i++){
                /* generate a randomized item: */
                int weight = rand() % (MAX_WEIGHT - MIN_WEIGHT +1) + MIN_WEIGHT;
                int value = rand() % (MAX_VALUE - MIN_VALUE +1) + MIN_VALUE;
                //item->name = "Item: "+ to_string(i);
                items[i] = new Item(weight, value);
            }

            //items.sort(ItemComparator());
            //cout << "Printing sorted items list: " << endl;
            if(DEBUG){
                for (int i=0; i<PROBLEM_SIZE; i++){
                    cout << "Item "+ to_string(i) << endl;
                    cout << string(*items[i]) << endl;
                }
            }

        return items;
        }

        void* initArray(int defaultValue){   
            int** sacks = new int*[PROBLEM_SIZE+1](); 
            //init problem array
            for (int i = 0; i <= PROBLEM_SIZE; i++) {
                sacks[i] = new int[PROBLEM_WIDTH+1](); 
                for (int j = 0; j <= PROBLEM_WIDTH; j++) 
                    sacks[i][j] = defaultValue;
            }
            return sacks;
        }

        void* loadData(string fileName){
            return NULL;
        }

        void* writeData(string fileName){
            return NULL;
        }    
        
        int recurse_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            args->weights = (int**)initArray(-1);
            int itemIndex = PROBLEM_SIZE;
            int weightIndex = PROBLEM_WIDTH;
            return recurse(args->items, args->weights, itemIndex, weightIndex);
        }

        int recurse(Item** items, int** weights, int itemIndex, int weightIndex){
            if(itemIndex == 0){
                return 0;
            }
            if (weights[itemIndex][weightIndex] != -1) {
                return weights[itemIndex][weightIndex];
            }

            Item* item = items[itemIndex-1];
            if(weightIndex < item->weight){
                return weights[itemIndex][weightIndex] = recurse(items, weights, itemIndex-1, weightIndex);
            }else{
                weights[itemIndex][weightIndex] = max(recurse(items, weights, itemIndex-1, weightIndex), recurse(items, weights, itemIndex-1, weightIndex - item->weight) + item->value);
                return  weights[itemIndex][weightIndex];
            }
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            args->weights = (int**)initArray(-1);
            return iterate(args->items, args->weights);
        }

        int iterate(Item** items, int** weights){ 
            int itemIndex, weightIndex; 

            // Build table K[][] in bottom up manner 
            for (itemIndex = 0; itemIndex <= PROBLEM_SIZE; itemIndex++) { 
                for (weightIndex = 0; weightIndex <= PROBLEM_WIDTH; weightIndex++) { 
                    Item* item = items[itemIndex-1];
                    if (itemIndex == 0 || weightIndex == 0) 
                        weights[itemIndex][weightIndex] = 0; 
                    else if (item->weight <= weightIndex) 
                        weights[itemIndex][weightIndex] = max(item->value + weights[itemIndex-1][weightIndex - item->weight], weights[itemIndex - 1][weightIndex]); 
                    else
                        weights[itemIndex][weightIndex] = weights[itemIndex - 1][weightIndex]; 
                } 
            } 
            
            return weights[PROBLEM_SIZE][PROBLEM_WIDTH]; 
        } 

        int** getSolution2D(){
            return ((Arguments*) args)->weights;
        }
};

int main() {
    int NUM_OF_ITEMS = 20, SACK_SIZE = 50;

    Knapsack* problem = new Knapsack(NUM_OF_ITEMS, SACK_SIZE);
    problem->runCheck(problem->args);
}