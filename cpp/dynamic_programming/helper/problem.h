#include <iostream>
#include <stdlib.h>
#include <sys/time.h> 

using namespace std;

#define DEBUG false

class Problem_Arguments{};

template <class ResultType>  
class Problem{
    public:
        Problem_Arguments* args;
        ResultType res_iterative, res_recursive;
        long int time_iterative, time_recursive;
        int PROBLEM_SIZE, PROBLEM_WIDTH;

        virtual void* generateData()=0;
        virtual void* initArray(int defaultValue)=0;
        virtual void* writeData(string)=0;
        virtual void* loadData(string)=0;

        virtual ResultType iterate_init(Problem_Arguments*)=0;
        virtual ResultType recurse_init(Problem_Arguments*)=0;

        virtual ResultType** getSolution2D(){return NULL;};
        virtual ResultType* getSolution(){return NULL;};
        
        bool runCheck(Problem_Arguments* args){
            time_iterative = runTimeIterative(args);
            time_recursive = runTimeRecursive(args);

            return res_iterative == res_recursive;
        }

        long int runTimeIterative(Problem_Arguments* args){
            long int time_before = this->getClockTime();
            res_iterative = this->iterate_init(args);
            long int time_after = this->getClockTime();

            return time_iterative = time_after - time_before;
        }

        long int runTimeRecursive(Problem_Arguments* args){
            long int time_before = this->getClockTime();
            res_recursive = this->recurse_init(args);
            long int time_after = this->getClockTime();

            return time_recursive = time_after - time_before;
        }

        ResultType getResultRecursive(){
            return res_recursive;
        }
        
        ResultType getResultIterative(){
            return res_iterative;
        }

        long int getTimeIterative(){
            return time_iterative;
        }

        long int getTimeRecursive(){
            return time_recursive;
        }

        ResultType max(ResultType a, ResultType b){ return (a >= b) ? a : b;}

        ResultType min(ResultType a, ResultType b){ return (a <= b) ? a : b;}

        long int getClockTime(){
            struct timeval tp;
            gettimeofday(&tp, NULL);
            return tp.tv_usec;
        }

        template <typename type>
        void print2D(type** solution, int width, int height){
            //print array
            for (int i = 0; i < width; i++)
                cout << "\t" << i;
            cout << endl;
            for (int i = 0; i < height; i++) {
                cout << i << ":\t";
                for (int j = 0; j < width; j++){
                    cout << solution[i][j] << "\t";          
                }
                cout << endl;
            }
            cout << endl;
        }

        template <typename type>
        void print1D(type* solution, int height){
            //print array
            for (int i = 0; i < height; i++)
                cout << "\t" << i;
            cout << endl;
            cout << "table:\t";
            for (int i = 0; i < height; i++) {
                cout << solution[i] << "\t";
            }
            cout << endl << endl;;
        }
};