#include "dijkstra.h"

class Dijkstra_Arguments : public Problem_Arguments{
    public:
        int** graph;
        int* array, *path;
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

            max_neighbours = 5;
            min_neighbours = 3;
            max_weight = 20;
            min_weight = 1;

            int** graph = (int**)generateData(); 
            #ifdef DEBUG
                cout << "Start: " << start_point << endl;
                cout << "End: " << end_point << endl; 
                cout << "Graph:" << endl;
                print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
            #endif          
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
            args->path = (int*)initArray(-1);
            return recurse(args->graph, args->array, args->path, args->start_point, visited, args->end_point);
        }

        int recurse(int** graph, int* array, int* path, int index, bool* visited, int endPoint){
            if(index == -1) return array[endPoint];

            for(int j=0; j<PROBLEM_SIZE; j++){
                if (graph[index][j] != NO_EDGE){
                    if(array[j] > array[index] + graph[index][j]){
                        array[j] = array[index] + graph[index][j];
                        path[j] = index;
                    }
                }
            }
            visited[index] = true;

            int min = INT32_MAX, next = -1;
            //find not visited min vertex
            for(int j=0; j<PROBLEM_SIZE; j++){
                if(visited[j]) continue;
                if(array[j] < min) {
                    next = j;
                    min = array[j];;
                }
            }

            #ifdef DEBUG
                cout << "Solving for " << index << endl; 
                print1D(array, PROBLEM_SIZE);
                print1D(path, PROBLEM_SIZE);
            #endif
            return recurse(graph, array, path, next, visited, endPoint);
        }

        int iterate_init(Problem_Arguments* args_generic){
            Dijkstra_Arguments* args = (Dijkstra_Arguments*) args_generic;
            args->array = (int*)initArray(INT32_MAX);
            args->array[args->start_point] = 0;
            
            #ifdef CONSOLE
                cout << "Running Bottom-up " << flush;
                Console::create_progressbar(10);
            #endif
            for(int i=0; i<PROBLEM_SIZE; i++){
                if(i == args->start_point) continue;
                if(args->graph[args->start_point][i] != NO_EDGE){
                    args->array[i] = args->graph[args->start_point][i];
                }
            }
            args->path = (int*)initArray(-1);
            
            int retVal = iterate(args->graph, args->array, args->path, args->start_point, args->end_point);
            #ifdef CONSOLE
                Console::clear_line();
            #endif
            return retVal;
        }

        int iterate2(int** graph, int* array, int* path, int startPoint, int endPoint){
            list<int> Q;
            Q.push_front(startPoint);
            //add ancestors of startPoint
            for(int i=0; i<PROBLEM_SIZE; i++){
                if(i!=startPoint && graph[startPoint][i]){
                    Q.push_front(i);
                }
            }
            int min, index;
            while(Q.size > 1){
                min = INT32_MAX;
                index = -1;
                for(int i : Q){
                    if(array[i] < array[] + graph[][]){
                        min = array[i] + graph[][];
                        index = i;
                    }
                }
            }
        }

        int iterate(int** graph, int* array, int* path, int startPoint, int endPoint){
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            visited[startPoint] = true;

            int index, min;
            for(int i=0; i<PROBLEM_SIZE; i++){
                #ifdef CONSOLE
                    Console::clear_line();
                    cout << "Running Bottom-up " << flush;
                    Console::update_progressbar(i, PROBLEM_SIZE);
                #endif    
                
                if(i==0){
                    index = startPoint;
                    min = array[index];
                }else{
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
                }
                if(index == -1 ){
                    cout << "index -1 found... Graph is not connected...\nExiting..." << endl;
                    print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
                    exit(0);
                }

                for(int j=0; j<PROBLEM_SIZE; j++){
                    //cout << "index: " << index << " / " << "j: " << j << endl;
                    if (graph[index][j] != NO_EDGE){
                        if(array[j] > array[index] + graph[index][j]){
                            array[j] = array[index] + graph[index][j];
                            path[j] = index;
                        }
                    }
                }
                visited[index] = true;

                #ifdef DEBUG
                    cout << "Solving for " << index << endl;
                    print1D(array, PROBLEM_SIZE);
                    print1D(path, PROBLEM_SIZE);
                #endif
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
int main(int argc, char** argv) {
    //recursive 60000
    //iterative 60000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
     
    Dijkstra* problem = new Dijkstra(problemSize, 0, problemSize-1);
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