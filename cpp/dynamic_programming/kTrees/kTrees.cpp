#include <stdlib.h>
#include <stack>

#include "../helper/problem.h"
#include "../helper/trees.h"

class KTrees_Arguments : public Problem_Arguments{
    public:
        TreeNode* root;
        int* array;

        KTrees_Arguments(TreeNode* root){
            this->root = root; 
        }
};

class KTrees : public Problem <int>{

    public: 
        int DEFAULT_VALUE = 0;

        KTrees(int problemSize, int problemWidth){
            this->PROBLEM_SIZE = problemSize;
            this->PROBLEM_WIDTH = problemWidth;
            args = new KTrees_Arguments((TreeNode*)generateData());
        }

        void* generateData(){
            return generatePerfectTree(PROBLEM_SIZE, 2);
        }

        void* initArray(int defaultValue){ 
            int* array = new int[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i] = 0;
            }
            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }
              
        int recurse_init(Problem_Arguments* args_generic){
            KTrees_Arguments* args = (KTrees_Arguments*) args_generic;
            //showTree(args->root, PROBLEM_SIZE);
            args->array = (int*)initArray(0);
            int retVal = recurse(args->root, args->array, PROBLEM_WIDTH);
            //cout << "Array" << endl;
            //print1D(args->array, PROBLEM_SIZE);
            //cout << "Num of trees, of " << PROBLEM_WIDTH << " is: " << retVal << endl; 
            return retVal;
        }

        int recurse(TreeNode* node, int* array, int k){
            array[node->index] = 1;
            if(node->children.size() == 0 ) {
                return 1 == k;
            }

            int sum = 0;
            //dfs
            for(auto v: node->children){
                sum += recurse(v, array, k);
                array[node->index] += array[v->index];
            }
            return sum + (array[node->index] == k);
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            KTrees_Arguments* args = (KTrees_Arguments*) args_generic;
            //showTree(args->root, PROBLEM_SIZE);
            args->array = (int*)initArray(0);
            
            //generate stack of nodes
            bool visited[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }

            //put nodes into a queue
            stack <TreeNode*> s;
            queue<TreeNode*> nodes;
            TreeNode* node = args->root;
            nodes.push(node);
            s.push(node);
            while(s.size() > 0){
                node = s.top();
                s.pop();
                for(TreeNode* child : node->children){
                    if(!visited[child->index]){
                        visited[child->index] = true;
                        s.push(child);                        
                        nodes.push(child);
                    }
                }
            }

            #ifdef CONSOLE
                cout << "Running Bottom-up " << flush;
                Console::create_progressbar(10);
            #endif
            //cout << "Array" << endl;
            //print1D(args->array, PROBLEM_SIZE);
            int retVal = iterate(args->root, args->array, nodes, PROBLEM_WIDTH);
            //cout << "Array" << endl;
            //print1D(args->array, PROBLEM_SIZE);
            //cout << "Num of trees, of " << PROBLEM_WIDTH << " is: " << retVal << endl;                        
            return retVal;
        }

        int iterate(TreeNode* root, int* array, queue<TreeNode*> nodes, int k){
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
                //and if so, remove it from the queue
                if(node->children.size() == 0) {
                    node->value = (1==k);
                    array[node->index] = 1;
                    nodes.pop();                    
                    computed++;              
                    continue;
                }

                //check if node children have computed value
                //if theres a child without a value then set flag to false
                bool canCompute=true;
                for(TreeNode* child: node->children){
                    if(array[child->index] == 0){
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
                
                for(TreeNode* child: node->children){
                    array[node->index] += array[child->index];
                    node->value += child->value;
                }         
                array[node->index] += 1;       
                node->value += (k == array[node->index]);
                
                nodes.pop();
                computed++;
            }

            return root->value;
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //iterative 8000000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
    //int problemWidth = stoi(argv[3]);
    int problemWidth = 3;

    KTrees* problem = new KTrees(problemSize, problemWidth);
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
    //problem->runCheck(problem->args);
}
#endif