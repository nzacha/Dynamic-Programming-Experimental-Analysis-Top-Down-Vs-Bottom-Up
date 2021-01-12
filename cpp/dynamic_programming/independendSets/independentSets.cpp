#include "independentSets.h"
#include <bits/stdc++.h> 

class IndendentSets_Arguments : public Problem_Arguments{
    public:
        int** graph;
        TreeNode* tree;

        IndendentSets_Arguments(int** graph){
            this->graph = graph;
        }

        IndendentSets_Arguments(TreeNode* tree){
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

        void cleanTree(TreeNode* root){
            root->value = 0;
            for (TreeNode* child: root->children)
                cleanTree(child);
        }
};

class IndependentSet : public Problem <int>{  
    int max_neighbours, min_neighbours;

    public: 
        IndependentSet(int problem_size, int degree){
            this->PROBLEM_SIZE = problem_size;
            this->PROBLEM_WIDTH = problem_size;

            max_neighbours = problem_size;
            min_neighbours = 1;

            TreeNode* tree = generateConnectedTree(problem_size, degree);
            #ifdef DEBUG
                showTree(tree, PROBLEM_SIZE);
            #endif
            /*
            * int** graph = treeToGraph(tree, problem_size, false);
            * #ifdef DEBUG
            *     cout << "Graph: " << endl;
            *     print2D(graph, PROBLEM_SIZE, PROBLEM_SIZE);
            * #endif
            * destroyTree(tree);
            */
            //int** graph = generateGraph(problem_size, min_neighbours, max_neighbours, true);
            
            args = new IndendentSets_Arguments(tree);
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
            //args->tree = args->rootGraph(args->graph, PROBLEM_SIZE, NO_EDGE);
            int retVal = recurse(args->tree);
            
            return retVal;
        }

        int recurse(TreeNode* node){
            //node doesnt exist
            if(node == NULL)
                return 0;
            
            //if leaf value has already neem calculated
            if(node->value)
                return node->value;

            //if its a leaf set value
            if(node->children.size() == 0)
                return (node->value = 1);

            //value when node is excluded
            int value_excluding = 0;
            for(TreeNode* child: node->children){
                value_excluding += recurse(child);
            }

            //value when node is included
            int value_including = 1;
            for(TreeNode* child: node->children){
                if(child==NULL) continue;
                for(TreeNode* grandchild: child->children){
                    value_including += recurse(grandchild);
                }
            }

            //return maximum of the 2
            return (node->value = max(value_including, value_excluding));
        }

        int iterate_init(Problem_Arguments* args_generic){
            IndendentSets_Arguments* args = (IndendentSets_Arguments*) args_generic;
            //args->tree = args->rootGraph(args->graph, PROBLEM_SIZE, NO_EDGE);

            bool* visited = new bool[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            visited[args->tree->index] = true;
            
            //put nodes into a queue
            stack<TreeNode*> nodes, s_sorted;
            nodes.push(args->tree);
            visited[args->tree->index] = true;
            TreeNode* node;
            while(nodes.size()>0){
                node = nodes.top();
                s_sorted.push(node);
                nodes.pop();
                for(TreeNode* child : node->children){
                    if(!visited[child->index]){
                        visited[child->index] = true;
                        nodes.push(child);
                    }
                }
            }
            delete visited;

            #ifdef CONSOLE
                if(Console::ACTIVE){                
                    cout << "Running Bottom-up " << flush;
                    Console::create_progressbar(10);
                }
            #endif
            int retVal = iterate(args->tree, s_sorted);
            #ifdef CONSOLE
                if(Console::ACTIVE)                   
                    Console::clear_line();
            #endif
            return retVal;
        }

        int iterate(TreeNode* root, stack<TreeNode*> nodes){           
            int computed = 0;
            TreeNode* node;
            while(nodes.size() > 0){
                #ifdef CONSOLE
                    if(Console::ACTIVE){                
                        Console::clear_line();
                        cout << "Running Bottom-up " << flush;
                        Console::update_progressbar(computed, PROBLEM_SIZE);
                    }
                #endif    
                
                node = nodes.top();
                
                //if node has no children (is a leaf) set leaf value 
                //and if so, remove it from the queue
                if(node->children.size() == 0) {
                    node->value = 1;
                    nodes.pop();
                    computed++;
                    continue;
                }
                
                //check if node children have computed value
                //if theres a child without a value then set flag to false
                bool canCompute = true;
                for(TreeNode* child: node->children){
                    if(child->value == 0){
                        canCompute = false;
                        break;
                    }
                }

                //if value can't be computed directly (flag is false)
                //put node back into the back of the queue
                //and continue to the next node
                if(!canCompute) {
                    nodes.pop();
                    nodes.push(node);
                    continue;
                }
                //the value can be computed

                //calculate value including the current node
                int val_including = 1;
                for(TreeNode* child: node->children){
                    for(TreeNode* grandchild: child->children){
                        val_including += grandchild->value;
                    }
                }
                //calculate value excluding the current node
                int val_excluding = 0;
                for(TreeNode* child: node->children){
                    val_excluding += child->value;
                }
                
                //set the node value to the maximum of the 2 values
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