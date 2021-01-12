#include <stdlib.h>

#include <vector>
#include <stack>

#include "../helper/problem.h"
#include "../helper/trees.h"

class TreeDiameter_Arguments : public Problem_Arguments{
    public:
        TreeNode* root;
        int** array;

        TreeDiameter_Arguments(TreeNode* root){
            this->root = root;
        }
};

class TreeDiameter : public Problem <int>{

    public: 
        int degree = 2;

        TreeDiameter(int problemSize, int degree){
            this->PROBLEM_SIZE = problemSize;
            this->degree = degree;
            TreeNode* root = (TreeNode*)generateData();
            args = new TreeDiameter_Arguments(root);

            #ifdef DEBUG
                showTree(root, PROBLEM_SIZE);
            #endif
        }

        void* generateData(){
            return generateConnectedTree(PROBLEM_SIZE, this->degree);
            //return generateConnectedTree(PROBLEM_SIZE, this->degree, 0.5);
            //return generatePerfectTree(PROBLEM_SIZE, this->degree);
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
        
        int *inc_array, *exc_array, diameter;
        int recurse_init(Problem_Arguments* args_generic){
            TreeDiameter_Arguments* args = (TreeDiameter_Arguments*) args_generic;
            inc_array = (int*)initArray(0);
            exc_array = (int*)initArray(0);

            //cout << "Showing tree before" << endl;
            //showTree(args->root, PROBLEM_SIZE);
            int retVal = recurse(args->root);
            //print1D(inc_array, PROBLEM_SIZE);
            //print1D(exc_array, PROBLEM_SIZE);
            //cout << "Diameter is: " << diameter << endl;
            return retVal;
        }

        int recurse(TreeNode* root){
            vector<int> fValues;

            //dfs
            for(auto v: root->children){
                recurse(v);
                //push chldrens' values of inc array into list
                fValues.push_back(inc_array[v->index]);
            }
            
            //find 2 max fvalues
            int max1=-1, max2=-1;
            for(int i=0; i<fValues.size(); i++){
                if(fValues[i] >= max1){
                    max2 = max1;
                    max1 = fValues[i];
                }else if(fValues[i] > max2){
                    max2 = fValues[i];
                }
            }
            
            inc_array[root->index] =1;
            if(max1 != -1)
               inc_array[root->index] += max1;
            
            if(max2 != -1){
                exc_array[root->index] = 1 + max1 + max2;
            }

            return diameter = max(diameter, max(inc_array[root->index], exc_array[root->index]));
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            TreeDiameter_Arguments* args = (TreeDiameter_Arguments*) args_generic;
            
            //generate stack of nodes
            bool* visited = new bool[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                visited[i] = false;
            }
            visited[args->root->index] = true;
            
            //put nodes into a queue
            stack<TreeNode*> nodes, s_sorted;
            nodes.push(args->root);
            visited[args->root->index] = true;
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

            //cout << "Showing tree before" << endl;
            //showTree(args->root, PROBLEM_SIZE);
            #ifdef CONSOLE
                if(Console::ACTIVE){
                    cout << "Running Bottom-up " << flush;
                    Console::create_progressbar(10);
                }
            #endif

            long* array = new long[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++)
                array[i] = (long)0;

            int retVal = iterate(array, args->root, s_sorted);
            //print1D(inc_array, PROBLEM_SIZE);
            //print1D(exc_array, PROBLEM_SIZE);
            //cout << "Diameter is: " << retVal << endl;
            return retVal;
        }

        int iterate(long* array, TreeNode* root, stack<TreeNode*> nodes){
            int computed = 0;  
            int maxVal=0;
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
                    array[node->index]= 1;  
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

                //calculate firstmax and secondmax of node
                int firstmax=0, secondmax=0;
                for(TreeNode* child: node->children){
                    if(child->value >= firstmax){
                        secondmax = firstmax;
                        firstmax = child->value;
                    }else if(child->value > secondmax){
                        secondmax = child->value;
                    }

                    //set the node value to the maximum of the 2 values
                }
                node->value = firstmax + 1;
                array[node->index]= 1 + firstmax + secondmax;
                maxVal = max(max(node->value, array[node->index]), maxVal);

                nodes.pop();
                computed++;
            }

            return maxVal;
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    //iterative 900000
    string method = argv[1];
    int problemSize = stoi(argv[2]);
     
    TreeDiameter* problem = new TreeDiameter(problemSize);
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