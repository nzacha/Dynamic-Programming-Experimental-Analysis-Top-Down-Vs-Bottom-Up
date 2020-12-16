#include <stdlib.h>

#include "../helper/problem.h"

class IndependentSetsTrees_Arguments : public Problem_Arguments{
    public:
        int *array, *data;

        IndependentSetsTrees_Arguments(int* data){
            this->data = data;
        }
};

class IndependentSetsTrees : public Problem <int>{

    public: 
        int DEFAULT_VALUE = -1;

        IndependentSetsTrees(int problemSize){
            this->PROBLEM_SIZE = problemSize;
            this->PROBLEM_WIDTH = 1;
            args = new IndependentSetsTrees_Arguments();
        }

        void* generateData(){
            return NULL;
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
        
        int recurse_init(Problem_Arguments* args_generic){
            IndependentSetsTrees_Arguments* args = (IndependentSetsTrees_Arguments*) args_generic;
            args->array = (int*)initArray(DEFAULT_VALUE);
            int retVal = recurse(args->array, args->data, 1, 1, args->data[1]);
            cout << "Array" << endl;
            print1D(args->array, PROBLEM_SIZE);
            cout << "Data" << endl;
            print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int recurse(int* array, int* data, int index, int step, int cost){

        }
        
        int iterate_init(Problem_Arguments* args_generic){
            IndependentSetsTrees_Arguments* args = (IndependentSetsTrees_Arguments*) args_generic;
            args->array = (int*)initArray(INT32_MAX);
            args->array[1] = args->data[1];
            int retVal = iterate(args->array, args->data);
            cout << "Array" << endl;
            print1D(args->array, PROBLEM_SIZE);
            cout << "Data" << endl;
            print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int iterate(int* array, int* data){
            return 0;
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    string method = "iterative"; //argv[1];
    //int problemSize = stoi(argv[2]);
     
    IndependentSetsTrees* problem = new IndependentSetsTrees(8);
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
}
#endif