#include "mostCommonSubSequence.h"

#define DEBUG false

class Arguments : public Problem_Arguments{
    public:
        int** array;
        string seqA, seqB;

        Arguments(string seqA, string seqB){
            this->seqA = seqA;
            this->seqB = seqB;
        }
};

class MostCommonSubSequence : public Problem <int>{
    public:
        MostCommonSubSequence(string seqA, string seqB){
            this->PROBLEM_SIZE = seqA.length() +1;
            this->PROBLEM_WIDTH = seqB.length() +1;

            args = new Arguments(seqA, seqB);
        }

        void* generateData(){
            return NULL;
        }

        void* initArray(int defaultValue){ 	    
            int** array = new int*[PROBLEM_SIZE];            
            for (int i=0; i<PROBLEM_SIZE; i++){
                array[i] = new int[PROBLEM_WIDTH];
                for (int j=0; j<PROBLEM_WIDTH; j++){
                    array[i][j] = defaultValue;
                }
            }
            return array;
        }

        void* loadData(string fileName){
            return NULL;
        }

        void* writeData(string fileName){
            return NULL;
        }    
        
        int recurse_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;           
            args->array = (int**)initArray(-1); 
            int retVal = recurse(args->array, args->seqA, args->seqB, args->seqA.length()-1, args->seqB.length()-1);
            if(DEBUG) {
                cout << "Recursive table: " << endl;
                print2D<int>(getSolution2D(), PROBLEM_WIDTH, PROBLEM_SIZE);
            }
            return retVal;
        }

        int recurse(int** array, string seqA, string seqB, int a, int b){	
            if(a<0 || b<0)
                return 0;

            if(array[a+1][b+1] >= 0)
                return array[a+1][b+1];

            if(seqA[a] == seqB[b]){
                array[a+1][b+1] = (recurse(array, seqA, seqB, a-1, b-1) +1);
            }else{
                array[a+1][b+1] = max(recurse(array, seqA, seqB, a-1, b),recurse(array, seqA, seqB, a, b-1));
            }

            return array[a+1][b+1];
        }

        int iterate_init(Problem_Arguments* args_generic){
            Arguments* args = (Arguments*) args_generic;            
            args->array = (int**)initArray(0);
            int retVal = iterate(args->array, args->seqA, args->seqB);
            if(DEBUG) {
                cout << "Iterative table: " << endl;
                print2D<int>(getSolution2D(), PROBLEM_WIDTH, PROBLEM_SIZE);
            }
            return retVal;
        }

        int iterate(int** array, string seqA, string seqB){ 
            int height = seqA.length();
            int width = seqB.length();

            for(int i=1; i<=height; i++){
                for(int j=1; j<=width; j++){
                    /*if(DEBUG)
                        print2D(array, PROBLEM_SIZE, PROBLEM_WIDTH);*/

                    if(seqA[i-1] == seqB[j-1]){
                        array[i][j] = array[i-1][j-1] +1;
                        if(array[i][j]<array[i-1][j-1]){
                            printf("Int overflow detected!\n");
                            printf("Exiting...\n");
                            exit(0);
                        }
                    }else if(array[i][j-1] <= array[i-1][j]){
                        array[i][j] = array[i-1][j];
                    }else{
                        array[i][j] = array[i][j-1];
                    }
                }
            }
            return array[PROBLEM_SIZE-1][PROBLEM_WIDTH-1];
        } 

        int** getSolution2D(){
            return ((Arguments*) args)->array;
        }

};

int main(){
    MostCommonSubSequence* problem = new MostCommonSubSequence("ciawnciawocklwamoikfjoka\nmxokadwadwadwawdwanfaaaaokawmdkowajndoiawkmxkoplmoiawjcmoawmoc", ";lcmawpkljvioawklcmiwanfioawnicownamaaaaaiocniwoanciwajdiwajdijiwadjiawjiod");

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