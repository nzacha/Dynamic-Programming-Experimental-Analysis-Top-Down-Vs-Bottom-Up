#include <stack>
#include <fstream>
#include <iostream>
#include <sstream>

#include "mostCommonSubSequence.h"

class MCSS_Arguments : public Problem_Arguments{
    public:
        int** array;
        string seqA, seqB;

        MCSS_Arguments(string seqA, string seqB){
            this->seqA = seqA;
            this->seqB = seqB;
        }
};

string getSequenceFromFile(string filename){
    stringstream str;
    ifstream myfile(filename);
    string line;

    if(myfile.is_open()){
        while(getline(myfile, line)){
            str << line << endl;
        }
        myfile.close();
    }else{
        cout << "Unable to open file " << filename << endl;
        cout << "Exiting..." << endl;
        exit(0);
    }
    return str.str();
}

string generateSequence(int length){
    char sequence[length];
    
    for(int i=0; i<length; i++){
        int c = rand()%26;
        sequence[i] = (char) (c +'A');
    }
    string s = sequence;
    return s;
}

class MostCommonSubSequence : public Problem <int>{
    public:
        MostCommonSubSequence(bool isFile, string stringA, string stringB){
            string seqA,seqB;
            if(isFile){
                seqA = getSequenceFromFile(stringA);
                seqB = getSequenceFromFile(stringB);
            }else{
                seqA = stringA;
                seqB = stringB;
            }
            this->PROBLEM_SIZE = seqA.length() +1;
            this->PROBLEM_WIDTH = seqB.length() +1;

            args = new MCSS_Arguments(seqA, seqB);
        }

        MostCommonSubSequence(int lengthA, int lengthB){
            string seqA = generateSequence(lengthA);
            string seqB = generateSequence(lengthB);
            
            this->PROBLEM_SIZE = seqA.length() +1;
            this->PROBLEM_WIDTH = seqB.length() +1;

            srand(time(NULL));
            args = new MCSS_Arguments(seqA, seqB);
        }

        void* generateData(){
            return NULL;
        }

        void* loadData(string FILENAME){
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

        int recurse_init(Problem_Arguments* args_generic){
            MCSS_Arguments* args = (MCSS_Arguments*) args_generic;           
            args->array = (int**)initArray(-1); 
            int retVal = recurse(args->array, args->seqA, args->seqB, args->seqA.length()-1, args->seqB.length()-1);
            #ifdef DEBUG
                printSolution(args->array, args->seqA, args->seqB);
                print2D<int>(getSolution2D(), PROBLEM_WIDTH, PROBLEM_SIZE);
            #endif
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
                array[a+1][b+1] = max(recurse(array, seqA, seqB, a, b-1),recurse(array, seqA, seqB, a-1, b));
            }

            return array[a+1][b+1];
        }

        int iterate_init(Problem_Arguments* args_generic){
            MCSS_Arguments* args = (MCSS_Arguments*) args_generic;            
            args->array = (int**)initArray(0);
            if(Console::ACTIVE){
                Console::create_progressbar(10);
            }
            int retVal = iterate(args->array, args->seqA, args->seqB);
            if(Console::ACTIVE){
                Console::clear_line();
            }
            #ifdef DEBUG
                printSolution(args->array, args->seqA, args->seqB);
                print2D<int>(getSolution2D(), PROBLEM_WIDTH, PROBLEM_SIZE);
            #endif
            return retVal;
        }

        int iterate(int** array, string seqA, string seqB){ 
            int height = seqA.length();
            int width = seqB.length();

            for(int i=1; i<=height; i++){
                if(Console::ACTIVE){
                    Console::clear_line();
                    Console::update_progressbar(i, PROBLEM_SIZE);     
                }
                for(int j=1; j<=width; j++){
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

        void printSolution(int** array, string seqA, string seqB){
            int i = seqA.size(), j = seqB.size();
            int index = array[i][j];
            stack<char> word;
            while(i>=1 && j>=1){
                if((array[i-1][j-1] == index-1 || array[i-1][j-1] == -1) && (seqA[i-1]==seqB[j-1])  && (array[i-1][j] != index) && (array[i][j-1] != index)){
                    word.push(seqA.at(i-1));
                    i--;
                    j--;
                    index = array[i][j];
                }else if(array[i-1][j] == index){
                    i--;
                }else if(array[i][j-1] == index){
                    j--;
                }else {
                    break;
                }
                cout << i << "," << j << endl;
            }

            cout << ">The output is: ";
            while(!word.empty()){
                cout << word.top();
                word.pop();
            }
            cout << endl;
        }

        int** getSolution2D(){
            return ((MCSS_Arguments*) args)->array;
        }
};

#ifndef runner_cpp
int main(){
    string seqA = "PINEAPPLE";
    string seqB = "APPLES";
    MostCommonSubSequence* problem = new MostCommonSubSequence(false, seqA, seqB);
    problem->runCheck(problem->args);
}
#endif