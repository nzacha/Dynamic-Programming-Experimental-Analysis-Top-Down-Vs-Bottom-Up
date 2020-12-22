#include <list>

#ifndef graph_h
#define graph_h

#ifndef edge_const
#define edge_const
const int NO_EDGE = -1, EDGE = 1;
#endif

class GraphNode{
    public: 
        list< pair<GraphNode*, int>> connections;
        int index;

        GraphNode(int index){
            this->index = index;
        }

        void addConnection(GraphNode* node, int weight){
            connections.push_back( make_pair(node, weight));
        }
};

int** generateGraph(int size, int min_neighbours, int max_neighbours, bool twoSided){
    int** graph =  new int*[size];
    /* initialize random seed: */
    srand (time(NULL));
    //generate array
    for( int i=0; i< size; i++){
        graph[i] = new int[size];
        for(int j=0; j<size; j++){
            graph[i][j] = NO_EDGE;
        }
    }
    //populate array
    for( int nodeIndex=0; nodeIndex< size; nodeIndex++){
        int numberOfNeighbours = rand() % (max_neighbours - min_neighbours) + min_neighbours;
        //generate a connection for every neighbour of node
        int index, emptyCells;
        //cout << "Node: " << nodeIndex << ", Neighboors: " << numberOfNeighbours << endl;
        for( int connCount=0; connCount < numberOfNeighbours; connCount++){
            index = rand() % (numberOfNeighbours - connCount +1);
            emptyCells=0;
            //cout << "Node: " << nodeIndex << ", Neighboor Index: " << index << endl;
            for( int nodeIterator=0; nodeIterator<size; nodeIterator++){
                if(nodeIterator == nodeIndex){
                    emptyCells++;
                    continue;
                }

                if(emptyCells == index){
                    graph[nodeIndex][nodeIterator] = EDGE;
                    if(twoSided)
                        graph[nodeIterator][nodeIndex] = EDGE;
                    break;
                }

                if(graph[nodeIndex][nodeIterator] == NO_EDGE){
                    emptyCells++;
                }
            }
        }
    }
    return graph;
}


int** generateWeighted(int size, int min_neighbours, int max_neighbours, int min_weight, int max_weight, bool biDirectional, bool isConnected){
    if(!biDirectional){
        cout << "weighted graphs that are not bi-directional have not been implemented yet...\nExiting..." << endl;
        exit(0);
    }
    int** graph =  new int*[size];
    /* initialize random seed: */
    srand (time(NULL));
    //generate array
    for( int i=0; i< size; i++){
        graph[i] = new int[size];
        for(int j=0; j<size; j++){
            graph[i][j] = NO_EDGE;
        }
    }

    //populate array
    for( int nodeIndex=0; nodeIndex< size; nodeIndex++){
        int numberOfNeighbours = rand() % (max_neighbours - min_neighbours) + min_neighbours;
        if(isConnected) numberOfNeighbours++;
        //generate a connection for every neighbour of node
        for( int connCount=0; connCount < numberOfNeighbours; connCount++){
            int index = rand() % (size);
            while(index == nodeIndex)
                index = rand() % (size);
            graph[nodeIndex][index] = rand() % (max_weight - min_weight +1) + min_weight;
            if(biDirectional)
                graph[index][nodeIndex] = graph[nodeIndex][index];
        }
    }
    return graph;
}
#endif