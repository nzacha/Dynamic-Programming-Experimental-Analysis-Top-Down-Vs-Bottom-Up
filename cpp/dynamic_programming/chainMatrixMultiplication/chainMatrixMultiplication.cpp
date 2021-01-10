#include "chainMatrixMultiplication.h"

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
        int MAX_SIZE = 20;
        int MIN_SIZE = 1;
        ChainMatrixMultiplication(int problem_size, int max_size){
            this->PROBLEM_SIZE = problem_size+1;
            this->PROBLEM_WIDTH = PROBLEM_SIZE;
            MAX_SIZE = max_size;
            args = new ChainMatrix_Arguments((int*)generateData());
            #ifdef DEBUG
                print1D(((ChainMatrix_Arguments*)args)->matrixSizes, PROBLEM_SIZE);
            #endif        
        }

        ChainMatrixMultiplication(int* matrices, int problem_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = PROBLEM_SIZE;
            args = new ChainMatrix_Arguments(matrices);
            #ifdef DEBUG
                print1D(((ChainMatrix_Arguments*)args)->matrixSizes, PROBLEM_SIZE);
            #endif
        }

        void* generateData(){  
            srand (time(NULL));

            int size = PROBLEM_SIZE;
            int* matrixSizes = new int[size];
            
            for(int i=0; i<size; i++){
                matrixSizes[i] = rand() % (MAX_SIZE - MIN_SIZE +1) + MIN_SIZE;
            }
            return matrixSizes;
        }

        void* initArray(int defaultValue){
            int size = PROBLEM_SIZE+1;
            int** array = new int*[size];
            for(int i=0; i<size; i++){
                array[i] = new int[size];
                for (int j = 0; j < size; j++)
                    array[i][j] = defaultValue; 
            }

            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }

        int recurse_init(Problem_Arguments* args_generic){
            ChainMatrix_Arguments* args = (ChainMatrix_Arguments*) args_generic;
            args->array = (int**)initArray(0);
            int retVal = recurse(args->array, args->matrixSizes, 0, PROBLEM_SIZE-2);
            #ifdef DEBUG
                print2D(args->array, PROBLEM_SIZE-1, PROBLEM_SIZE-2);
            #endif
            return retVal;
        }

        int recurse(int** array, int* matrixSizes, int indexStart, int indexEnd){
            if (indexStart == indexEnd)
                return 0;
            if(array[indexStart][indexEnd] != 0)
                return array[indexStart][indexEnd];

            int min = INT32_MAX;
            for(int k=indexStart; k<indexEnd; k++){
                int val = recurse(array, matrixSizes, indexStart, k) + recurse(array, matrixSizes, k+1, indexEnd) + matrixSizes[indexStart]*matrixSizes[k+1]*matrixSizes[indexEnd+1];
                if(val < min)
                    min = val;
            }
            int retVal = min;
            array[indexStart][indexEnd] = retVal;
            return retVal;
        }

        int iterate_init(Problem_Arguments* args_generic){
            ChainMatrix_Arguments* args = (ChainMatrix_Arguments*) args_generic;
            args->array = (int**)initArray(0);
            #ifdef CONSOLE
                if(Console::ACTIVE){
                    cout << "Running Bottom-up " << flush;
                    Console::create_progressbar(10);
                }
            #endif
            int retVal = iterate(args->array, args->matrixSizes);
            #ifdef CONSOLE
                if(Console::ACTIVE)
                    Console::clear_line();
            #endif
            #ifdef DEBUG
                print2D(args->array, PROBLEM_SIZE-1, PROBLEM_SIZE-2);
            #endif
            return retVal;
        }

        int iterate(int** array, int* matrixSizes){
            int indexStart, indexEnd, val;
            for(int step=1; step<PROBLEM_SIZE; step++){
                #ifdef CONSOLE
                    if(Console::ACTIVE){
                        Console::clear_line();
                        cout << "Running Bottom-up " << flush;
                        Console::update_progressbar(step, PROBLEM_SIZE);
                    }
                #endif
                for(indexStart=0; indexStart<PROBLEM_SIZE - step -1; indexStart++){
                    indexEnd = indexStart + step;
                    int min = INT32_MAX;
                    for(int k=indexStart; k<indexEnd; k++){
                        val = array[indexStart][k] + array[k+1][indexEnd] + matrixSizes[indexStart]*matrixSizes[k+1]*matrixSizes[indexEnd+1];
                        if(val < min){
                            min = val;
                        }
                    }
                    array[indexStart][indexEnd] = min;
                }
            }

            return array[0][PROBLEM_SIZE-2];
        } 

        int** getSolution2D(){
            return ((ChainMatrix_Arguments*) args)->array;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //recursive 80000
    //iterative 85000
    int matrices[] = {30,35,15,5,10,20,25};
    ChainMatrixMultiplication* problem = new ChainMatrixMultiplication(matrices, 7);
    problem->runCheck(problem->args);
    /*string method = argv[1];
    int problemSize = stoi(argv[2]);
     
    ChainMatrixMultiplication* problem = new ChainMatrixMultiplication(stoi(argv[2]));
    long long int time_taken;
    if (method=="iterative"){
        time_taken = problem->runTimeIterative(problem->args);
    }else if (method == "recursive"){
        time_taken = problem->runTimeRecursive(problem->args);
    } else {
        cout << "Method not recognized" << endl;
        return 1;
    }
    cout <<  "time taken: " << time_taken << endl;
    */
}
#endif