#include "shortestPath.h"

class Arguments : public Problem_Arguments{
    public:

        Arguments(){
        }
};

class ShortestPath : public Problem <int>{
    public: 
        ShortestPath(int problem_size){
            this->PROBLEM_SIZE = problem_size;

            //args = new Arguments((Item**)generateData(), (int**)generateArray(-1));
        }

        void* generateData(){
            return NULL;
        }

        void* initArray(int defaultValue){   
            return NULL;
        }

        void* loadData(string fileName){
            return NULL;
        }

        void* writeData(string fileName){
            return NULL;
        }    
        
        int recurse_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;

            return recurse();
        }

        int recurse(){
            return 0;
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            
            return iterate();
        }

        int iterate(){
            return 0;
        } 

        int** getSolution(){
            //return ((Arguments*) args)->weights;
            return NULL;
        }
};

int main() {
    int NUM_OF_ITEMS = 30000;

    ShortestPath* problem = new ShortestPath(NUM_OF_ITEMS);

    /*
    long int timeTaken = problem->runTimeRecursive(problem->args);
    cout << "Recursive took: " << timeTaken <<" microseconds." << endl;
    //problem->printPath(problem->getSolution());
    */

    /*
    timeTaken = problem->runTimeIterative(problem->args);
    cout << "Iterative took: " << timeTaken <<" microseconds." << endl;
    //problem->printPath(problem->getSolution());
    */

    bool val = problem->runCheck(problem->args);
    cout << "The values " << (string)(val ? "MATCH" : "DO NOT MATCH") << endl;
    
    cout << "Iterative found: " << problem->getResultIterative() << endl;
    cout << "Recursive found: " << problem->getResultRecursive() << endl;
}