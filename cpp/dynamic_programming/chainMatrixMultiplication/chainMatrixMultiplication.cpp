#include "chainMatrixMultiplication.h"
#define DEBUG false

class ChainMatrix_Arguments : public Problem_Arguments{
    public:
        int** array;
        int* matrixSizes;
        ChainMatrix_Arguments(int* matrixSizes){
            this->matrixSizes = matrixSizes;            
        }
};

class ChainMatrixMultiplication : public Problem <int>{
    public: 
        ChainMatrixMultiplication(int problem_size){
            this->PROBLEM_SIZE = problem_size+1;
            this->PROBLEM_WIDTH = PROBLEM_SIZE;
            args = new ChainMatrix_Arguments((int*)generateData());
            //print1D(((ChainMatrix_Arguments*)args)->matrixSizes, PROBLEM_SIZE);
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
        
        int recurse_init(Problem_Arguments* args_generic){
            ChainMatrix_Arguments* args = (ChainMatrix_Arguments*) args_generic;
            args->array = (int**)initArray(0);
            int retVal = recurse(args->array, args->matrixSizes, 0, PROBLEM_SIZE-2);
            //print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
            return retVal;
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
            ChainMatrix_Arguments* args = (ChainMatrix_Arguments*) args_generic;
            args->array = (int**)initArray(0);
            int retVal = iterate(args->array, args->matrixSizes);
            //print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
            return retVal;
        }

        int iterate(int** array, int* matrixSizes){
            int indexStart, indexEnd, stepIterator, val1, val2;
            for(int step=1; step<PROBLEM_SIZE; step++){
                for(indexStart=0; indexStart<PROBLEM_SIZE - step -1; indexStart++){
                    indexEnd = indexStart + step;

                    val1 = array[indexStart][indexEnd-1] + matrixSizes[indexStart]*matrixSizes[indexEnd]*matrixSizes[indexEnd+1];
                    val2 = array[indexStart+1][indexEnd] + matrixSizes[indexStart]*matrixSizes[indexStart+1]*matrixSizes[indexEnd+1];
                    array[indexStart][indexEnd] = min(val1, val2);
                }
            }

            return array[0][PROBLEM_SIZE-2];
        } 

        int** getSolution2D(){
            return ((ChainMatrix_Arguments*) args)->array;
        }
};

#ifndef runner_cpp
int main() {
    int NUM_OF_ITEMS = 5;//30000;

    ChainMatrixMultiplication* problem = new ChainMatrixMultiplication(NUM_OF_ITEMS);
    problem->runCheck(problem->args);
}
#endif