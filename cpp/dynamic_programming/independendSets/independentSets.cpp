#include "independentSets.h"
#include <bits/stdc++.h> 

class Arguments : public Problem_Arguments{
    public:
        int** graph;
        TreeNode* tree;

        Arguments(int** graph, int size, int noEdge){
            this->graph = graph;
            tree = rootGraph(graph, size, noEdge);
        }
        
        Arguments(TreeNode* tree){
            this->tree = tree;
        }

        TreeNode* rootGraph(int** graph, int size, int noEdge){
            TreeNode** nodes = new TreeNode*[size];
            for(int i=0; i<size; i++){  
                nodes[i] = new TreeNode(i);
            }

            TreeNode* root = nodes[0];
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    if(i==j) continue;
                    if(graph[i][j] != noEdge){
                        nodes[i]->appendChild(nodes[j]);
                    }
                }
            }
            return root;
        }
};

class IndependentSet : public Problem <int>{  
    int max_neighbours, min_neighbours;

    public: 
        IndependentSet(int problem_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = this->PROBLEM_SIZE;

            max_neighbours = PROBLEM_SIZE;
            min_neighbours = 0;

            //int** graph = (int**)generateData();   
            //args = new Arguments(graph, PROBLEM_SIZE, NO_EDGE);
            args = new Arguments(generateConnectedTree(PROBLEM_SIZE, 2));
            //args = new Arguments(generatePerfectTree(PROBLEM_SIZE,1));
        }

        void* generateData(){ 
            return generateGraph(PROBLEM_SIZE, min_neighbours, max_neighbours);
        }

        bool isConnected(TreeNode* tree){
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            
            stack <TreeNode*> s;
            TreeNode* node = tree;
            visited[node->index] = true;
            int count = 1;
            while(true){
                for(TreeNode* child : node->children){
                    if(!visited[child->index]){
                        count++;
                        visited[child->index] = true;
                        s.push(child);
                    }
                }
                if(s.size()<=0)
                    return (count == PROBLEM_SIZE);
                node = s.top();
                s.pop();
            }
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
            return recurse(args->tree);
        }

        int recurse(TreeNode* node){
            if(node == NULL)
                return 0;
            
            if(node->value)
                return node->value;

            if(node->children.size() == 0)
                return (node->value = 1);

            int value_excluding = 0;
            for(TreeNode* child: node->children){
                value_excluding += recurse(child);
            }

            int value_including = 1;
            for(TreeNode* child: node->children){
                if(child==NULL) continue;
                for(TreeNode* grandchild: child->children){
                    value_including += recurse(grandchild);
                }
            }
            return (node->value = max(value_including, value_excluding));
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;

            //generate stack of nodes
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            
            stack <TreeNode*> s;
            queue <TreeNode*> nodes;
            TreeNode* node = args->tree;
            visited[node->index] = true;
            nodes.push(node);
            while(true){
                for(TreeNode* child : node->children){
                    if(!visited[child->index]){
                        visited[child->index] = true;
                        s.push(child);
                        nodes.push(child);
                    }
                }
                if(s.size()<=0)
                    break;
                node = s.top();
                s.pop();
            }
            return iterate(args->tree, nodes);
        }

        int iterate(TreeNode* root, queue<TreeNode*> nodes){           
            bool visited[PROBLEM_SIZE];
            for (int i=0; i<PROBLEM_SIZE; i++)
                visited[i] = false;

            int computed = 0;
            TreeNode* node;
            while(nodes.size() > 0){
                node = nodes.front();
                
                //if node has no children (is a leaf) set leaf value
                if(node->children.size() == 0) {
                    node->value = 1;
                    nodes.pop();
                    computed++;
                    continue;
                }
                
                //check if node children have computed value
                bool canCompute = true;
                for(TreeNode* child: node->children){
                    if(child->value == 0){
                        canCompute = false;
                        break;
                    }
                }
                //if value can't be computed directly
                if(!canCompute) {
                    nodes.pop();
                    nodes.push(node);
                    continue;
                }
                
                //if node has children
                int val_including = 1;
                for(TreeNode* child: node->children){
                    for(TreeNode* grandchild: child->children){
                        val_including += grandchild->value;
                    }
                }
                int val_excluding = 0;
                for(TreeNode* child: node->children){
                    val_excluding += child->value;
                }
                
                node->value = max(val_including, val_excluding);
                nodes.pop();
                computed++;
            }
            return root->value;
        } 

        int** getSolution2D(){
            //return ((Arguments*) args)->weights;
            return NULL;
        }

        void showTree(TreeNode* root){
            bool visited[PROBLEM_SIZE];
            for(int i=0; i< PROBLEM_SIZE; i++)
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
                if(count==PROBLEM_SIZE)
                    break;

                node = nodes.front();
                nodes.pop();
            }
            cout << "Tree printed" << endl;
            cout << endl;
        }
};

int main() {
    int NUM_OF_ITEMS = 10000;

    IndependentSet* problem;
    bool connected = false;
    while(!connected){
        problem = new IndependentSet(NUM_OF_ITEMS);
        if (DEBUG) problem->print2D(((Arguments*)problem->args)->graph, problem->PROBLEM_SIZE, problem->PROBLEM_SIZE);

        connected = problem->isConnected(((Arguments*)problem->args)->tree);
    }
    if(DEBUG){
        cout << "Printing graph:" << endl;
        problem->print2D(((Arguments*)problem->args)->graph, problem->PROBLEM_SIZE, problem->PROBLEM_SIZE);

        problem->showTree(((Arguments*)problem->args)->tree);
    }
    bool val = problem->runCheck(problem->args);
    cout << "The values " << (string)(val ? "MATCH" : "DO NOT MATCH") << endl;
    cout << endl;
    
    cout << "Iterative found: " << problem->getResultIterative() << endl;
    cout << "Iterative took: " << problem->getTimeIterative() <<" microseconds." << endl;
    cout << endl;
    
    cout << "Recursive found: " << problem->getResultRecursive() << endl;
    cout << "Recursive took: " << problem->getTimeRecursive() <<" microseconds." << endl;
    cout << endl;    
}