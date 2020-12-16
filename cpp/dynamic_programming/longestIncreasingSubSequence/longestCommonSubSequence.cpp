#include <stdlib.h>

#include "../helper/problem.h"

class LISS_Arguments : public Problem_Arguments{
    public:
        int *array, *data;

        LISS_Arguments(int* data){
            this->data = data;
        }
};

class LISS : public Problem <int>{

    public: 
        int DEFAULT_VALUE = -1, MAX_VAL = 20;

        LISS(int problemSize, int max_value){
            this->PROBLEM_SIZE = problemSize;
            this->PROBLEM_WIDTH = 1;
            this->MAX_VAL = max_value;
            args = new LISS_Arguments((int*)generateData());
        }

        void* generateData(){
            srand(time(NULL));
            int* data = new int[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                data[i] = rand() % MAX_VAL;
            }
            return data;
        }

        void* initArray(int defaultValue){ 
            int* array = new int[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i] = defaultValue;
            }
            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }
        
        int** initArray2(int defaultValue){
            int** array = new int*[PROBLEM_SIZE+1];
            for(int i=0; i<=PROBLEM_SIZE; i++){
                array[i] = new int[PROBLEM_SIZE+1];
                for(int j=0; j<=PROBLEM_SIZE; j++){
                    array[i][j] = defaultValue;
                }
            }
            return array;
        }

        int recurse_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            int* array = (int*)initArray(DEFAULT_VALUE);
            int retVal = recurse(array, args->data, INT32_MIN, 0);
            cout << "Array" << endl;
            print1D(array, (int)(PROBLEM_SIZE));
            cout << "Data" << endl;
            print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int recurse(int* array, int* data, int prev, int curr){
            // Base case: nothing is remaining
            if (curr == PROBLEM_SIZE)
                return 0;
        
            // case 1: exclude the current element and process the
            // remaining elements
            int excl = recurse(array, data, prev, curr + 1);
        
            // case 2: include the current element if it is greater
            // than previous element in LIS
            int incl = 0;
            if (data[curr] > prev)
                incl = 1 + recurse(array, data, data[curr], curr + 1);
        
            array[curr] = max(incl, excl);
            // return maximum of above two choices
            return array[curr];
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            args->array = (int*)initArray(1);
            int retVal = iterate(args->array, args->data);
            cout << "Array" << endl;
            print1D(args->array, PROBLEM_SIZE);
            cout << "Data" << endl;
            print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int iterate(int* array, int* data){
            for (int i = 1; i < PROBLEM_SIZE; i++ ){ 
                for (int j = 0; j < i; j++ ){ 
                    if ( data[i] > data[j] && array[i] < array[j] + 1)  
                        array[i] = array[j] + 1; 
                } 
            } 
            
            int max =INT32_MIN, index=-1;
            for(int i=0; i<PROBLEM_SIZE; i++){
                if(array[i] > max){
                    max = array[i];
                    index = i;
                }
            }
            return array[index];
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    string method = "iterative"; //argv[1];
    //int problemSize = stoi(argv[2]);
     
    LISS* problem = new LISS(20, 100);
    problem->runCheck(problem->args);
    long long int time_taken;
    /*
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