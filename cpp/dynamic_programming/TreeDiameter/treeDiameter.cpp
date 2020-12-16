#include <stdlib.h>

#include <vector>

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
        TreeDiameter(int problemSize){
            this->PROBLEM_SIZE = problemSize;
            args = new TreeDiameter_Arguments((TreeNode*)generateData());
        }

        void* generateData(){
            return generatePerfectTree(PROBLEM_SIZE, 2);
        }

        void* initArray(int defaultValue){ 
            int** array = new int*[PROBLEM_SIZE];
            for(int i=0; i<PROBLEM_SIZE; i++){
                array[i] = new int[PROBLEM_WIDTH];
                for(int j=0; j<PROBLEM_WIDTH; j++){
                    array[i][j] = defaultValue;
                }
            }
            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }
        
        int *inc_array, *exc_array, diameter;
        int recurse_init(Problem_Arguments* args_generic){
            TreeDiameter_Arguments* args = (TreeDiameter_Arguments*) args_generic;
            inc_array = new int[PROBLEM_SIZE];
            exc_array = new int[PROBLEM_SIZE];

            cout << "Showing tree before" << endl;
            showTree(args->root, PROBLEM_SIZE);
            int retVal = recurse(args->root);
            print1D(inc_array, PROBLEM_SIZE);
            print1D(exc_array, PROBLEM_SIZE);
            cout << "Diameter is: " << diameter << endl;
            return retVal;
        }

        int recurse(TreeNode* root){
            vector<int> fValues;

            //dfs
            for(auto v: root->children){
                recurse(v);
                fValues.push_back(inc_array[v->index]);
            }
            
            //find 2 max fvalues
            int max1=-1, max2=-1;
            for(int i=0; i<fValues.size(); i++){
                if(fValues[i] > max2){
                    max2 = fValues[i];
                }else if(fValues[i] > max1){
                    max1 = fValues[i];
                }
            }
            
            inc_array[root->index] =1;
            if(max1 != -1)
               inc_array[root->index] += max1;
            
            if(max2 != -1){
                exc_array[root->index] = 2 + max1 + max2;
            }

            diameter = max(diameter, max(inc_array[root->index], exc_array[root->index]));
            return 0;
        }
        
        int iterate_init(Problem_Arguments* args_generic){
            /*IndependentSetsTrees_Arguments* args = (IndependentSetsTrees_Arguments*) args_generic;
            args->array = (int*)initArray(INT32_MAX);
            args->array[1] = args->data[1];
            int retVal = iterate(args->array, args->data);
            cout << "Array" << endl;
            print1D(args->array, PROBLEM_SIZE);
            cout << "Data" << endl;
            print1D(args->data, PROBLEM_SIZE);
            return retVal;
            */
            return 0;
        }

        int iterate(int* array, int* data){
            return 0;
        }

        int* getSolution1D(){
            return NULL;
        }
};

#ifndef runner_cpp
int main(int argc, char** argv) {
    string method = "recursive"; //argv[1];
    //int problemSize = stoi(argv[2]);
     
    TreeDiameter* problem = new TreeDiameter(10);
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