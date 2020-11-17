#include "independentSets.h"
#include <bits/stdc++.h> 

class IndendentSets_Arguments : public Problem_Arguments{
    public:
        int** graph;
        TreeNode* tree;

        IndendentSets_Arguments(int** graph){
            this->graph = graph;
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

        void cleanTree(TreeNode* root){
            root->value = 0;
            for (TreeNode* child: root->children)
                cleanTree(child);
        }
};

class IndependentSet : public Problem <int>{  
    int max_neighbours, min_neighbours;

    public: 
        IndependentSet(int problem_size){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = problem_size;

            max_neighbours = problem_size;
            min_neighbours = 1;

            TreeNode* tree = generateConnectedTree(problem_size, 2, 1);
            #ifdef DEBUG
                showTree(tree);
            #endif
            int** graph = treeToGraph(tree, problem_size, false);
            #ifdef DEBUG
                cout << "Graph: " << endl;
                print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
            #endif
            destroyTree(tree);
            
            //int** graph = generateGraph(problem_size, min_neighbours, max_neighbours, true);
            
            args = new IndendentSets_Arguments(graph);
        }

        void* generateData(){ 
            return generateGraph(PROBLEM_SIZE, min_neighbours, max_neighbours, true);
        }

        bool isConnected(TreeNode* tree){
            if(tree==NULL) return false;

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
            return 0;
        }

        void* loadData(string fileName){
            return NULL;
        }
        
        int recurse_init(Problem_Arguments* args_generic){
            IndendentSets_Arguments* args = (IndendentSets_Arguments*) args_generic;
            args->tree = args->rootGraph(args->graph, PROBLEM_SIZE, NO_EDGE);
            int retVal = recurse(args->tree);
            
            return retVal;
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
            IndendentSets_Arguments* args = (IndendentSets_Arguments*) args_generic;
            args->tree = args->rootGraph(args->graph, PROBLEM_SIZE, NO_EDGE);

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
            #ifdef CONSOLE
                cout << "Running Bottom-up " << flush;
                Console::create_progressbar(10);
            #endif
            int retVal = iterate(args->tree, nodes);
            #ifdef CONSOLE
                Console::clear_line();
            #endif
            return retVal;
        }

        int iterate(TreeNode* root, queue<TreeNode*> nodes){           
            bool visited[PROBLEM_SIZE];
            for (int i=0; i<PROBLEM_SIZE; i++)
                visited[i] = false;

            int computed = 0;
            TreeNode* node;
            while(nodes.size() > 0){
                #ifdef CONSOLE
                    Console::clear_line();
                    cout << "Running Bottom-up " << flush;
                    Console::update_progressbar(computed, PROBLEM_SIZE);
                #endif    
                
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
            cout << endl;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //recursive 60000
    //iterative 60000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
     
    IndependentSet* problem = new IndependentSet(problemSize);
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