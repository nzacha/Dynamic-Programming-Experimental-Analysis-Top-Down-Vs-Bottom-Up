#include <vector>

#include "allpairShortestPath.h"
#include "../helper/trees.h"

class AllPair_Arguments : public Problem_Arguments{
    public:
        int** graph;
        GraphNode** listOfNodes;
        int** array;
        int** path;

        AllPair_Arguments(int** graph, GraphNode** listOfNodes, int** path){
            this->graph = graph;
            this->listOfNodes = listOfNodes;
            this->path = path;
        }
};

class ShortestPath : public Problem <int>{
    int max_neighbours, min_neighbours;
    int max_weight, min_weight;
    
    public: 
        ShortestPath(int problem_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = this->PROBLEM_SIZE;

            max_neighbours = PROBLEM_SIZE;
            min_neighbours = 0;
            max_weight = 10;
            min_weight = 1;

            pair <int**, GraphNode**>* retval = (pair <int**, GraphNode**>*) generateData();
            int** graph = retval->first;
            #ifdef DEBUG
                cout << "Graph: " << endl;
                print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
            #endif

            GraphNode** listOfNodes = retval->second;
            int** path =  (int**)initArray(-1); 
            for(int i=0; i<PROBLEM_SIZE; i++){
                path[i][i] = 0;
            }         
            args = new AllPair_Arguments(graph, listOfNodes, path);
        }

        bool biDirectional = true, isConnected = true;
        GraphNode** convertGraph(int** graph){
            GraphNode** listOfNodes = new GraphNode*[PROBLEM_SIZE];
            for (int i=0; i<PROBLEM_SIZE; i++){
                listOfNodes[i] = new GraphNode(i);
            }

            for (int i=0; i<PROBLEM_SIZE; i++){
                for (int j=0; j<PROBLEM_SIZE; j++){
                    if(graph[i][j] == NO_EDGE) continue;
                    listOfNodes[i]->addConnection(listOfNodes[j], graph[i][j]);
                }
            }
            return listOfNodes;
        }

        void* generateData(){ 
            pair <int**, GraphNode**>* retval =  new pair <int**, GraphNode**>();
            //return generateGraph(PROBLEM_SIZE, min_neighbours, max_neighbours, true);
            retval->first = generateWeighted(PROBLEM_SIZE, min_neighbours, max_neighbours, min_weight, max_weight, biDirectional, isConnected);
            retval->second = convertGraph(retval->first);
            return retval;
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

        int recurse_init(Problem_Arguments* args_generic){
            AllPair_Arguments* args = (AllPair_Arguments*) args_generic;
            
            args->array = (int**)initArray(INT32_MAX);    
            for(int i=0; i<PROBLEM_SIZE; i++){
                args->array[i][i] = 0;
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    if(args->graph[i][j] != NO_EDGE){
                        args->array[i][j] = args->graph[i][j];
                    }
                }
            }
            args->path =  (int**)initArray(-1);
            
            int retVal = recurse(args->array, args->listOfNodes, args->path, 0);
            #ifdef DEBUG
                cout << "Shortest Paths: " << endl;
                print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
                cout << "Intermediates: " << endl;
                print2D(args->path, PROBLEM_SIZE, PROBLEM_SIZE);
            #endif
            return retVal;
        }

        int recurse(int** array, GraphNode** listOfNodes, int** path, int nodeIndex){
            if(nodeIndex >= PROBLEM_SIZE) return 0;
            
            GraphNode* pivotNode = listOfNodes[nodeIndex];
            for(int i=0; i<PROBLEM_SIZE; i++){
                for(int j=0; j<PROBLEM_SIZE; j++){
                    if(array[i][pivotNode->index] == INT32_MAX) continue;
                    if(array[pivotNode->index][j] == INT32_MAX) continue;

                    int newVal = array[i][pivotNode->index] + array[pivotNode->index][j];
                    if(newVal < array[i][j] || newVal == 0){
                        array[i][j] = newVal;
                        path[i][j] = pivotNode->index;
                    }
                }
            }
            return recurse(array, listOfNodes, path, nodeIndex+1);
        }

        int iterate_init(Problem_Arguments* args_generic){
            AllPair_Arguments* args = (AllPair_Arguments*) args_generic;

            args->array = (int**)initArray(INT32_MAX);
            for(int i=0; i<PROBLEM_SIZE; i++){
                args->array[i][i] = 0;
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    if(args->graph[i][j] != NO_EDGE){
                        args->array[i][j] = args->graph[i][j];
                    }
                }
            }
            args->path =  (int**)initArray(-1); 
            #ifdef CONSOLE
                cout << "Running Bottom-up " << flush;
                Console::create_progressbar(10);
            #endif
            int retVal = iterate(args->array, args->path);
            #ifdef CONSOLE
                Console::clear_line();
            #endif
            #ifdef DEBUG
                cout << "Shortest Paths: " << endl;
                print2D(args->array, PROBLEM_SIZE, PROBLEM_SIZE);
                cout << "Intermediates: " << endl;
                print2D(args->path, PROBLEM_SIZE, PROBLEM_SIZE);
            #endif
            return retVal;
        }

        int iterate(int** array, int** path){
            for (int k=0; k<PROBLEM_SIZE; k++){
                for (int i=0; i<PROBLEM_SIZE; i++){
                    #ifdef CONSOLE
                        Console::clear_line();
                        cout << "Running Bottom-up " << flush;
                        Console::update_progressbar(k*PROBLEM_SIZE + i, PROBLEM_SIZE*PROBLEM_SIZE);
                    #endif    
                    for (int j=0; j<PROBLEM_SIZE; j++){
                        if(array[i][k] == INT32_MAX) continue;
                        if(array[k][j] == INT32_MAX) continue;
                        int newVal = (array[i][k] + array[k][j]); 
                        if(newVal < array[i][j] || newVal == 0){
                            array[i][j] = newVal;
                            path[i][j] = k;
                        }
                    }
                }
            }
            return 0;
        } 

        int** getSolution2D(){
            return ((AllPair_Arguments*) args)->array;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //recursive 80000
    //iterative 85000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
     
    ShortestPath* problem = new ShortestPath(problemSize);
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