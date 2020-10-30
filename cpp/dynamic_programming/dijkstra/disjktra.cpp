#include "dijkstra.h"

#define DEBUG false

class Dijkstra_Arguments : public Problem_Arguments{
    public:
        int** graph;
        int* array;
        int start_point, end_point;

        Dijkstra_Arguments(int** graph, int start_point, int end_point){
            this->graph = graph;
            this->start_point = start_point;
            this->end_point = end_point;
        }
};

class Dijkstra : public Problem <int>{
    int max_neighbours, min_neighbours;
    int max_weight, min_weight;

    public: 
        Dijkstra(int problem_size, int start_point, int end_point){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = this->PROBLEM_SIZE;

            max_neighbours = 10;
            min_neighbours = 0;
            max_weight = 10;
            min_weight = 5;

            int** graph = (int**)generateData();           
            args = new Dijkstra_Arguments(graph, start_point, end_point);
        }

        void* generateData(){ 
            return generateWeighted(PROBLEM_SIZE, min_neighbours, max_neighbours, min_weight, max_weight, true, true);
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
            Dijkstra_Arguments* args = (Dijkstra_Arguments*) args_generic;
            args->array = (int*)initArray(INT32_MAX);
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            args->array[args->start_point] = 0;
            return recurse(args->graph, args->array, args->start_point, visited, args->end_point);
        }

        int recurse(int** graph, int* array, int index, bool* visited, int endPoint){
            if(index == -1) return array[endPoint];;

            for(int j=0; j<PROBLEM_SIZE; j++){
                if (graph[index][j] != NO_EDGE){
                    if(array[j] > array[index] + graph[index][j])
                        array[j] = array[index] + graph[index][j];
                }
            }
            visited[index] = true;

            int min = INT32_MAX, next = -1;
            //find not visited min vertex
            for(int j=0; j<PROBLEM_SIZE; j++){
                if(visited[j]) continue;
                if(array[j] < min) {
                    next = j;
                    min = array[j];
                }
            }

            if (DEBUG) {
                cout << "chose index: " << index << endl;
                print1D(array, PROBLEM_SIZE);
            }
            return recurse(graph, array, next, visited, endPoint);
        }

        int iterate_init(Problem_Arguments* args_generic){
            Dijkstra_Arguments* args = (Dijkstra_Arguments*) args_generic;
            args->array = (int*)initArray(INT32_MAX);
            args->array[args->start_point] = 0;
            
            for(int i=0; i<PROBLEM_SIZE; i++){
                if(i == args->start_point) continue;
                if(args->graph[args->start_point][i] != NO_EDGE){
                    args->array[i] = args->graph[args->start_point][i];
                }
            }

            return iterate(args->graph, args->array, args->start_point, args->end_point);
        }

        int iterate(int** graph, int* array, int startPoint, int endPoint){
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            visited[startPoint] = true;

            if (DEBUG) {
                cout << "Starting from: " << startPoint << endl;
                print1D(array, PROBLEM_SIZE);
            }

            int index, min;
            for(int i=0; i<PROBLEM_SIZE-1; i++){
                min = INT32_MAX;
                index = -1;
                //find not visited min vertex
                for(int j=0; j<PROBLEM_SIZE; j++){
                    if(visited[j]) continue;
                    if(array[j] < min) {
                        index = j;
                        min = array[j];
                    }
                }
                if(index == -1 ){
                    cout << "index -1 found...]nGraph is not connected...\nExiting..." << endl;
                    print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
                    exit(0);
                }

                if (DEBUG) cout << "Choosing index: " << index << endl;
                for(int j=0; j<PROBLEM_SIZE; j++){
                    //cout << "index: " << index << " / " << "j: " << j << endl;
                    if (graph[index][j] != NO_EDGE){
                        if(array[j] > array[index] + graph[index][j])
                            array[j] = array[index] + graph[index][j];
                    }
                }
                visited[index] = true;

                if (DEBUG) print1D(array, PROBLEM_SIZE);
            }

            for (int i=0; i<PROBLEM_SIZE; i++){
                if (array[i] == INT32_MAX) array[i] = NO_EDGE;
            }
            return array[endPoint];
        } 

        int* getSolution1D(){
            return ((Dijkstra_Arguments*) args)->array;
        }
};

#ifndef runner_cpp
int main() {
    int NUM_OF_ITEMS = 20000;

    Dijkstra* problem = new Dijkstra(NUM_OF_ITEMS, 0, NUM_OF_ITEMS-1);
    if(!problem->runCheck(problem->args)){
        cout << endl;
        cout << "Printing graph:" << endl;
        problem->print2D(((Dijkstra_Arguments*)problem->args)->graph, problem->PROBLEM_SIZE, problem->PROBLEM_SIZE);

        cout << "Printing array:" << endl;
        problem->print1D(((Dijkstra_Arguments*)problem->args)->array, problem->PROBLEM_SIZE);
    }
}
#endif