const int NO_EDGE = 0, EDGE = 1;

int** generateGraph(int size, int min_neighbours, int max_neighbours){
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