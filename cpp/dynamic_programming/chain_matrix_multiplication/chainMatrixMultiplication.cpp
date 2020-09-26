#include "chainMatrixMultiplication.h"
#define DEBUG false
#define SOLO false

class Arguments : public Problem_Arguments{
    public:
        int** array;
        int* matrixSizes;
        Arguments(int** array, int* matrixSizes){
            this->array = array;
            this->matrixSizes = matrixSizes;            
        }
};

class ChainMatrixMultiplication : public Problem <int>{
    public: 
        ChainMatrixMultiplication(int problem_size){
            this->PROBLEM_SIZE = problem_size+1;
            this->PROBLEM_WIDTH = PROBLEM_SIZE;
            args = new Arguments((int**)initArray(0), (int*)generateData());
        }

        void* generateData(){  
            srand (time(NULL));

            int size = PROBLEM_SIZE;
            int* matrixSizes = new int[size];
            
            if(DEBUG) cout << "The values are: " << endl;
            for(int i=0; i<size; i++){
                matrixSizes[i] = rand() % (MAX_SIZE - MIN_SIZE +1) + MIN_SIZE;
                if(DEBUG) cout << "\t" << matrixSizes[i];
            }
            if(DEBUG) cout << endl << endl;
            return matrixSizes;
        }

        void* initArray(int defaultValue){
            int size = PROBLEM_SIZE+1;
            int** array = new int*[size];
            for(int i=0; i<size; i++){
                array[i] = new int[size];
            }

            for (int i = 0; i < size; i++)
                //for (int j = 0; j < size; j++) 
                array[i][i] = defaultValue; 

            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }

        void* writeData(string fileName){
            return NULL;
        }    
        
        int recurse_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            int* matrixSizes = args->matrixSizes;
            int** array = args->array;

            return recurse(array, matrixSizes, 0, PROBLEM_SIZE-2);
        }

        int recurse(int** array, int* matrixSizes, int indexStart, int indexEnd){
            if (indexStart == indexEnd)
                return 0;
            if(array[indexStart][indexEnd] != 0)
                return array[indexStart][indexEnd];

            int val1 = recurse(array, matrixSizes, indexStart+1, indexEnd) + matrixSizes[indexStart]*matrixSizes[indexStart+1]*matrixSizes[indexEnd+1];
            int val2 = recurse(array, matrixSizes, indexStart, indexEnd-1) + matrixSizes[indexStart]*matrixSizes[indexEnd]*matrixSizes[indexEnd+1];
            int retVal = min (val1, val2);

            array[indexStart][indexEnd] = retVal;
            return retVal;
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            int** array = args->array;
            int* matrixSizes = args->matrixSizes;
            return iterate(array, matrixSizes);
        }

        int iterate(int** array, int* matrixSizes){
            int indexStart, indexEnd, stepIterator, val1, val2;
            for(int step=1; step<PROBLEM_SIZE; step++){
                for(indexStart=0; indexStart<PROBLEM_SIZE-1; indexStart++){
                    indexEnd= indexStart + step;
                    if(indexEnd>PROBLEM_SIZE){
                        continue;
                    }

                    val1 = array[indexStart][indexEnd-1] + matrixSizes[indexStart]*matrixSizes[indexEnd]*matrixSizes[indexEnd+1];
                    val2 = array[indexStart+1][indexEnd] + matrixSizes[indexStart]*matrixSizes[indexStart+1]*matrixSizes[indexEnd+1];
                    array[indexStart][indexEnd] = min(val1, val2);
                }
            }
            return array[0][PROBLEM_SIZE-2];
        } 

        int** getSolution2D(){
            Arguments* casted_args = (Arguments*) args;
            return casted_args->array;
        }
};

int main() {
    int NUM_OF_ITEMS = 1000;

    ChainMatrixMultiplication* problem = new ChainMatrixMultiplication(NUM_OF_ITEMS);
    if(SOLO){
        long int timeTaken = problem->runTimeRecursive(problem->args);
        cout << "Recursive took: " << timeTaken <<" microseconds." << endl;
        //problem->printPath(problem->getSolution2D());

        long int timeTakenIterative = problem->runTimeIterative(problem->args);
        cout << "Iterative took: " << timeTakenIterative <<" microseconds." << endl;
        //problem->printPath(problem->getSolution2D());
    }else{
        bool val = problem->runCheck(problem->args);
        cout << "The values " << (string)(val ? "MATCH" : "DO NOT MATCH") << endl;
        cout << "Iterative found: " << problem->getResultIterative() << endl;
        cout << "Recursive found: " << problem->getResultRecursive() << endl;
    }
}