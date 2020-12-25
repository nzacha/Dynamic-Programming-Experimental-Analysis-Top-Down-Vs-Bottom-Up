#include <stdlib.h>

#include "../helper/console.h"
#include "../helper/problem.h"

#include "liss.h"

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

        int recurse_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            args->array1D = (int*)initArray(DEFAULT_VALUE);
            int retVal = 1;
            for (int i=0; i<PROBLEM_SIZE; i++) retVal = max( retVal, recurse(args->array1D, args->data, i));
            //cout << "Array" << endl;
            //print1D(args->array, (int)(PROBLEM_SIZE));
            //cout << "Data" << endl;
            //print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int recurse(int* array, int* data, int curr){
            if(curr >= PROBLEM_SIZE) return 0;
            if(array[curr] > 0) return array[curr];

            int result = 1;            
            for (int i=0; i<curr; i++){
                if(data[curr] > data[i]) 
                    result = max(result, 1 + recurse(array, data, i));
            }
            array[curr] = result;
            return result;
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            LISS_Arguments* args = (LISS_Arguments*) args_generic;
            args->array1D = (int*)initArray(1);
            if(Console::ACTIVE){
                Console::create_progressbar(10);
            }
            int retVal = iterate(args->array1D, args->data);
            //cout << "Array" << endl;
            //print1D(args->array, PROBLEM_SIZE);
            //cout << "Data" << endl;
            //print1D(args->data, PROBLEM_SIZE);
            return retVal;
        }

        int iterate(int* array, int* data){
            //calculate increasing sequences
            for (int i = 1; i < PROBLEM_SIZE; i++ ){    
                if(Console::ACTIVE){
                    Console::clear_line();
                    Console::update_progressbar((int) (1.0*i*i/PROBLEM_SIZE), PROBLEM_SIZE);     
                }
                for (int j = 0; j < i; j++ ){ 
                    if ( data[i] > data[j] && array[i] < array[j] + 1)  
                        array[i] = array[j] + 1; 
                } 
            }           
            if(Console::ACTIVE){
                Console::clear_line();
            }
            
            //find max value
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
    //iterative 200000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
    //int problemWidth = stoi(argv[3]);
    int problemWidth = 1000;

    LISS* problem = new LISS(problemSize, problemWidth);
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