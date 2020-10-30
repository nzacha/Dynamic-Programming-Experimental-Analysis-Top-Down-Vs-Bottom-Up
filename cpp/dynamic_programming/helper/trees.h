#include <list>

#ifndef trees_h
#define trees_h

class TreeNode{
    public:
        int index, value = 0;
        bool visited = false;
        list<TreeNode*> children;

        TreeNode(int index){
            this->index = index;
        }

        void appendChild(TreeNode* node){
            children.push_back(node);
        }

        TreeNode* getChild(int index){
            list<TreeNode*>::iterator it = children.begin();
            advance(it, index);
            return *it;
        }
};

TreeNode* generateConnectedTree(int treeSize, int degree){
    srand (time(NULL));
    int generatedNodes = 0;
    TreeNode* root = new TreeNode(generatedNodes++);

    TreeNode** nodes = new TreeNode*[treeSize];
    for (int i=0; i<treeSize; i++) nodes[i] = NULL;
    nodes[generatedNodes++] = root;
    
    TreeNode* node;
    for(int i=generatedNodes; i<treeSize; i++){
        int index = rand() % (i-1);
        node = new TreeNode(i);
        while(nodes[index % treeSize] == NULL) index++;
        nodes[index]->appendChild(node);
        nodes[i] = NULL;

        nodes[i] = node;
    }
    return root;
}

TreeNode* generatePerfectTree(int treeSize, int degree){
    int generatedNodes =0, childrenIndex =0;
    list<TreeNode*> nodes;
    TreeNode* root = new TreeNode(generatedNodes++);
    TreeNode* child;
    TreeNode* node = root;
    for(;generatedNodes < treeSize;){
        //add children
        for(int j=0; j<degree && generatedNodes < treeSize; j++){
            child = new TreeNode(generatedNodes++);
            node->appendChild(child);
            nodes.push_back(child);
        }
        node = nodes.front();
        nodes.pop_front();
    }
    return root;
}

void destroyTree(TreeNode* node){
    for(TreeNode* child: node->children)
        destroyTree(child);
    delete(node);
}

void treeToGraph_recur(TreeNode* node, int** graph, int weight){
    for(TreeNode* child: node->children){
        graph[node->index][child->index] = weight;
        treeToGraph_recur(child, graph, weight);
    }
}

int** treeToGraph(TreeNode* root, int size, bool weighted){
    int** graph = new int*[size];
    for(int i=0; i<size; i++){
        graph[i] = new int[size];
        for(int j=0; j<size; j++)
            graph[i][j] = NO_EDGE;
    }
    if(!weighted)
        treeToGraph_recur(root, graph, EDGE);
    else
        cout << "tree 2 weighted graph not implemented yet" << endl; 
    
    return graph;
}
#endif