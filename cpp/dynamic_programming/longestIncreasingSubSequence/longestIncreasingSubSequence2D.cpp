#include <stdlib.h>

#include "../helper/console.h"
#include "../helper/problem.h"

#include "liss.h"

class LISS2D : public Problem <int>{

    public: 
        int DEFAULT_VALUE = -1, MAX_VAL = 20;

        LISS2D(int problemSize, int max_value){
            this->PROBLEM_SIZE = problemSize;
            this->PROBLEM_WIDTH = problemSize;
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
            int** array = new int*[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i] = new int[PROBLEM_SIZE];
                for(int j=0; j<PROBLEM_SIZE; j++){
                    array[i][j] = defaultValue;
                }
            }
            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }

        int recurse_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            args->array2D = (int**)initArray(DEFAULT_VALUE);
            int retVal =0;
            for(int i=0; i<PROBLEM_SIZE-retVal; i++){
                for(int j=i+1; j<PROBLEM_SIZE-retVal; j++){
                    if(args->data[i] < args->data[j])
                        retVal = max(retVal, recurse(args->array2D, args->data, i, j));   
                }
            }                
            //cout << "Array" << endl;
            //print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
            //cout << "Data" << endl;
            //print1D(args->data, PROBLEM_SIZE);
            return retVal+1;
        }

        int recurse(int** array, int* data, int prev, int curr){
            if(curr >= PROBLEM_SIZE) return 0;
            //memoization
            if(array[prev][curr] >= 0) return array[prev][curr];
            //curr value is bigger so we skip
            if(data[prev] >= data[curr]){                
                return recurse(array, data, prev, curr+1);
            }
            //otherwise: curr value is not bigger
            array[prev][curr] = max(recurse(array, data, prev, curr+1), 1 + recurse(array, data, curr, curr+1));
            return array[prev][curr];
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            args->array2D = (int**)initArray(0);
            if(Console::ACTIVE){
                Console::create_progressbar(10);
            }
            int retVal = iterate(args->array2D, args->data);
            //cout << "Array" << endl;
            //print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
            //cout << "Data" << endl;
            //print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int iterate(int** array, int* data){
            //cache contains the previous best of each index
            int cache[PROBLEM_SIZE] = {0};
            for(int i=0; i<PROBLEM_SIZE; i++){
                if(Console::ACTIVE){
                    Console::clear_line();
                    Console::update_progressbar(i, PROBLEM_SIZE);     
                }
                for(int j=i+1; j<PROBLEM_SIZE; j++){
                    if(data[i]<data[j]) {
                        array[i][j] = cache[i]+1;
                        if(cache[j]<array[i][j]) cache[j]=array[i][j];
                    }
                }
            }
            if(Console::ACTIVE){
                Console::clear_line();
            }
            //print1D(cache, PROBLEM_SIZE);
            int retVal = 0;
            for(int i=0; i<PROBLEM_SIZE; i++)
                retVal = max(retVal, cache[i]);
            return retVal+1;
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //iterative 200000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
    //int problemWidth = stoi(argv[3]);
    int problemWidth = 1000;

    LISS2D* problem = new LISS2D(problemSize, problemWidth);
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
    //problem->runCheck(problem->args);
}
#endif