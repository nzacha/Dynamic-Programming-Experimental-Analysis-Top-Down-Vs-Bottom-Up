#include <vector>

#include "allpairShortestPath.h"
#include "../helper/trees.h"

class Arguments : public Problem_Arguments{
    public:
        int** graph;
        GraphNode** listOfNodes;
        int** array;
        int** path;

        Arguments(int** graph, GraphNode** listOfNodes, int** path){
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
            GraphNode** listOfNodes = retval->second;
            int** path =  (int**)initArray(-1);            
            args = new Arguments(graph, listOfNodes, path);
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
            for (int i=0; i<PROBLEM_SIZE; i++){
                for (int j=0; j<PROBLEM_SIZE; j++){

                }    
            }
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
            Arguments* args = (Arguments*) args_generic;
            
            args->array = (int**)initArray(INT32_MAX);
            for(int i=0; i<PROBLEM_SIZE; i++){
                args->array[i][i] = 0;
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    if(args->graph[i][j] != NO_EDGE){
                        args->array[i][j] = args->graph[i][j];
                    }
                }
            }
            return recurse(args->array, args->listOfNodes, args->path, 0);
        }

        int recurse(int** array, GraphNode** listOfNodes, int** path, int nodeIndex){
            if(nodeIndex >= PROBLEM_SIZE) return 0;
            
            GraphNode* node = listOfNodes[nodeIndex];
            for(int i=0; i<PROBLEM_SIZE; i++){
                GraphNode* targetNode = listOfNodes[i];
                for(pair<GraphNode*, int> connection: node->connections){
                    GraphNode* pivotNode = connection.first;
                    if(array[nodeIndex][pivotNode->index] == INT32_MAX) continue;
                    if(array[pivotNode->index][targetNode->index] == INT32_MAX) continue;

                    int newVal = array[nodeIndex][pivotNode->index] + array[pivotNode->index][targetNode->index];
                    if(newVal < array[nodeIndex][targetNode->index]){
                        array[nodeIndex][targetNode->index] = newVal;
                        path[nodeIndex][targetNode->index] = pivotNode->index;
                    }
                }
            }
            return recurse(array, listOfNodes, path, nodeIndex+1);
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;

            args->array = (int**)initArray(INT32_MAX);
            for(int i=0; i<PROBLEM_SIZE; i++){
                args->array[i][i] = 0;
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    if(args->graph[i][j] != NO_EDGE){
                        args->array[i][j] = args->graph[i][j];
                    }
                }
            }
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
    int NUM_OF_ITEMS = 100;

    ShortestPath* problem = new ShortestPath(NUM_OF_ITEMS);
    
    /*
    problem->runTimeIterative(problem->args);
    problem->print2D(((Arguments*)problem->args)->array, problem->PROBLEM_SIZE, problem->PROBLEM_SIZE);
    problem->runTimeRecursive(problem->args);
    problem->print2D(((Arguments*)problem->args)->array, problem->PROBLEM_SIZE, problem->PROBLEM_SIZE);
    */
    problem->runCheck(problem->args);
    problem->writeData("out.txt");
}