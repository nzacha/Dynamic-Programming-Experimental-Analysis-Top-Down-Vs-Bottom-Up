#include <list>
#include <algorithm>
#include <queue>

#ifndef trees_h
#define trees_h

#ifndef edge_const
#define edge_const
const int NO_EDGE = -1, EDGE = 1;
#endif

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

void showTree(TreeNode* root, int size){
    bool visited[size];
    for(int i=0; i< size; i++)
        visited[i] = false;
        
    queue <TreeNode*> nodes;
    TreeNode* node = root;
    cout << "Printing tree:" << endl;
    //print root
    cout << "Root: " << node->index << "\t\t";
    visited[node->index] = true;
    for(TreeNode* child : node->children){
        cout << "Node: " << child->index << "\t";
        nodes.push(child);
    }
    cout << endl;
    int count=1;
    
    //pop next node
    node = nodes.front();
    nodes.pop();
    while(node){
        if(visited[node->index]){
            node = nodes.front();
            nodes.pop();
            continue;
        }

        cout << "Parent: " << node->index << "\t";
        visited[node->index] = true;
        
        if(node->children.size()>0){
            for(TreeNode* child: node->children){
                if(!visited[child->index]){
                    nodes.push(child);
                }
                cout << "Node: " << child->index << "\t";
            }
        }else{
            cout << "  --";
        }
        cout << endl;

        count++;
        if(count==size)
            break;

        node = nodes.front();
        nodes.pop();
    }
    cout << endl;
}

TreeNode* generateConnectedTree(int treeSize, int degree, int connectivity){
    srand (time(NULL));
    int generatedNodes = 0;
    TreeNode* root = new TreeNode(generatedNodes++);

    list<TreeNode*> toAdd;
    toAdd.push_back(root);

    TreeNode* node;
    list<TreeNode*>::iterator parent;
    for(int i=generatedNodes; i<treeSize; i++){
        int connections = (rand() % connectivity) +1;
        node = new TreeNode(generatedNodes++);
        for(int j=0; j<min(connections, (int)toAdd.size()); j++){
            int index;
            do{            
                //find a parent that doesnt contain the node
                index = rand() % (toAdd.size());
                parent = toAdd.begin();
                advance(parent, index);
            }while(find((*parent)->children.begin(), (*parent)->children.end(), node) != (*parent)->children.end());
            //push node into parent
            (*parent)->children.push_back(node);
            
            //if parent has reached degree limit erase him
            if((*parent)->children.size() >= degree){
                toAdd.erase(parent);
            }
            //add node in available nodes list
            toAdd.push_back(node);
        }
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