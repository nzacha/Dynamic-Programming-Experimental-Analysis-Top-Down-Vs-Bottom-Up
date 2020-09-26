#include "allpairShortestPath.h"

class Arguments : public Problem_Arguments{
    public:
        int** graph;
        int** array;
        int** path;

        Arguments(int** graph, int** array, int** path){
            this->graph = graph;
            this->array = array;
            this->path = path;
        }
};

class ShortestPath : public Problem <int>{
    int max_neighbours, min_neighbours;
    int max_weight, min_weight;
    const int NO_EDGE = -1;
    public: 
        ShortestPath(int problem_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = this->PROBLEM_SIZE;

            max_neighbours = PROBLEM_SIZE;
            min_neighbours = 0;
            max_weight = 10;
            min_weight = 1;

            int** graph = (int**)generateData();
            
            int** array =  (int**)initArray(INT32_MAX);
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i][i] = 0;
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    if(graph[i][j] != NO_EDGE){
                        array[i][j] = graph[i][j];
                    }
                }
            }
            
            int** path =  (int**)initArray(INT32_MAX);
            
            args = new Arguments(graph, array, path);
        }

        void* generateData(){ 
            int defaultValue = NO_EDGE;

            int** graph =  new int*[PROBLEM_SIZE];
            /* initialize random seed: */
            srand (time(NULL));
            //generate array
            for( int i=0; i< PROBLEM_SIZE; i++){
                graph[i] = new int[PROBLEM_SIZE];
                for(int j=0; j<PROBLEM_SIZE; j++){
                    graph[i][j] = defaultValue;
                }
            }
            //populate array
            for( int nodeIndex=0; nodeIndex< PROBLEM_SIZE; nodeIndex++){
                int numberOfNeighbours = rand() % (max_neighbours - min_neighbours) + min_neighbours;
                //generate a connection for every neighbour of node
                int index, emptyCells;
                //cout << "Node: " << nodeIndex << ", Neighboors: " << numberOfNeighbours << endl;
                for( int connCount=0; connCount<numberOfNeighbours; connCount++){
                    index = rand() % (numberOfNeighbours - connCount +1);
                    emptyCells=0;
                    //cout << "Node: " << nodeIndex << ", Neighboor Index: " << index << endl;
                    for( int nodeIterator=0; nodeIterator<PROBLEM_SIZE; nodeIterator++){
                        if(nodeIterator == nodeIndex){
                            emptyCells++;
                            continue;
                        }

                        if(emptyCells == index){
                            graph[nodeIndex][nodeIterator] = rand() % (max_weight - min_weight +1) + min_weight;
                            graph[nodeIterator][nodeIndex] = graph[nodeIndex][nodeIterator];
                            break;
                        }

                        if(graph[nodeIndex][nodeIterator] == defaultValue){
                            emptyCells++;
                        }
                    }
                }
            }
            return graph;
        }

        void* initArray(int defaultValue){ 
            int** array = new int*[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i] = new int[PROBLEM_WIDTH];
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    array[i][j]=defaultValue;
                }
            }
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
            return recurse(args->array, args->path, 0, 0, 0);
        }

        int recurse(int** array, int** path, int k, int i, int j){
            return 0;
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;
            return iterate(args->array, args->path);
        }

        int iterate(int** array, int** path){
            for (int k=0; k<PROBLEM_SIZE; k++){
                for (int i=0; i<PROBLEM_SIZE; i++){
                    for (int j=0; j<PROBLEM_SIZE; j++){
                        if(array[i][k] == INT32_MAX) continue;
                        if(array[k][j] == INT32_MAX) continue;
                        int newVal = (array[i][k] + array[k][j]); 
                        if(newVal < array[i][j]){
                            array[i][j] = newVal;
                            path[i][j] = k;
                        }
                    }
                }
            }
            return 0;
        } 

        int** getSolution2D(){
            return ((Arguments*) args)->array;
        }
};

int main() {
    int NUM_OF_ITEMS = 5;

    ShortestPath* problem = new ShortestPath(NUM_OF_ITEMS);

    /*
    cout << "BEFORE" << endl << endl;
    cout << "Graph: " << endl;
    problem->print2D<int>(((Arguments*)problem->args)->graph, NUM_OF_ITEMS, NUM_OF_ITEMS);
    cout << "Array: " << endl;
    problem->print2D<int>(((Arguments*)problem->args)->array, NUM_OF_ITEMS, NUM_OF_ITEMS);
    cout << "Path: "<< endl;
    problem->print2D<int>(((Arguments*)problem->args)->path, NUM_OF_ITEMS, NUM_OF_ITEMS);
    */

    /*
    long int recursiveTimeTaken = problem->runTimeRecursive(problem->args);
    cout << "Recursive took: " << recursiveTimeTaken <<" microseconds." << endl;
    //problem->printPath(problem->getSolution());
    */
   
    long int iterativeTimeTaken = problem->runTimeIterative(problem->args);
    cout << "Iterative took: " << iterativeTimeTaken <<" microseconds." << endl;
    //problem->print2D(problem->getSolution2D(), problem->PROBLEM_SIZE, problem->PROBLEM_WIDTH);


    //cout << "AFTER" << endl << endl;
    cout << "Graph: " << endl;
    problem->print2D<int>(((Arguments*)problem->args)->graph, NUM_OF_ITEMS, NUM_OF_ITEMS);
    cout << "Array: " << endl;
    problem->print2D<int>(((Arguments*)problem->args)->array, NUM_OF_ITEMS, NUM_OF_ITEMS);
    cout << "Path: "<< endl;
    problem->print2D<int>(((Arguments*)problem->args)->path, NUM_OF_ITEMS, NUM_OF_ITEMS);
    

    /*
    bool val = problem->runCheck(problem->args);
    cout << "The values " << (string)(val ? "MATCH" : "DO NOT MATCH") << endl;
    
    cout << "Iterative found: " << problem->getResultIterative() << endl;
    cout << "Recursive found: " << problem->getResultRecursive() << endl;
    */
}