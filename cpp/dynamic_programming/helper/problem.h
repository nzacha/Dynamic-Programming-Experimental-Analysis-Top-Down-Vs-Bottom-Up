#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h> 
#include <chrono>

using namespace std;

#define DEBUG false

class Problem_Arguments{};

template <class ResultType>  
class Problem{
    public:
        Problem_Arguments* args;
        ResultType res_iterative, res_recursive;
        uint64_t time_iterative, time_recursive;
        long long PROBLEM_SIZE, PROBLEM_WIDTH;

        virtual void* generateData()=0;
        virtual void* initArray(int defaultValue)=0;
        
        //Writes a file with specified name and content
        void writeFile(string fileName, string content){
            ofstream myfile (fileName);
            myfile << content;
            myfile.close();
        }

        virtual void* writeData(string fileName){
            stringstream ss;
            ss.precision(4);
            ss << fixed << "recursive time taken: " << time_recursive * 1.0 / 1000000 << " s." << endl;
            ss << "recursive result: " << res_recursive << endl;
            ss << fixed << "iterative time taken: " << time_iterative * 1.0 / 1000000<< " s."<< endl; 
            ss << "iterative result: " << res_iterative << endl;
            writeFile(fileName, ss.str());
        }

        virtual void* loadData(string fileName)=0;

        virtual ResultType iterate_init(Problem_Arguments*)=0;
        virtual ResultType recurse_init(Problem_Arguments*)=0;

        virtual ResultType** getSolution2D(){return NULL;};
        virtual ResultType* getSolution(){return NULL;};
        
        bool runCheck(Problem_Arguments* args){
            cout << "Running check" << endl;
            uint64_t time_iterative = runTimeIterative(args);
            uint64_t time_recursive = runTimeRecursive(args);
            cout << endl;
            
            bool retVal = res_iterative == res_recursive;
            
            cout << "The values " << (string)(retVal ? "MATCH" : "DO NOT MATCH") << endl;
            cout << endl;
            
            cout << "Iterative found: " << getResultIterative() << endl;
            cout << "Iterative took: ";
            printf("%.4Lf s.", ((long double) getTimeIterative()) / 1000000);
            cout << endl;
            cout << endl;
        
            cout << "Recursive found: " << getResultRecursive() << endl;
            cout << "Recursive took: ";
            printf("%.4Lf s.", ((long double) getTimeRecursive()) / 1000000);
            cout << endl;

            return retVal;
        }

        uint64_t runTimeIterative(Problem_Arguments* args){
            cout << "Running iterative method" << endl;
            uint64_t time_before = this->getClockTime();
            res_iterative = this->iterate_init(args);
            uint64_t time_after = this->getClockTime();

            return time_iterative = (time_after - time_before);
        }

        uint64_t runTimeRecursive(Problem_Arguments* args){
            cout << "Running recursive method" << endl;
            uint64_t time_before = this->getClockTime();
            res_recursive = this->recurse_init(args);
            uint64_t time_after = this->getClockTime();

            return time_recursive = (time_after - time_before);
        }

        ResultType getResultRecursive(){
            return res_recursive;
        }
        
        ResultType getResultIterative(){
            return res_iterative;
        }

        uint64_t getTimeIterative(){
            return time_iterative;
        }

        uint64_t getTimeRecursive(){
            return time_recursive;
        }

        ResultType max(ResultType a, ResultType b){ return (a >= b) ? a : b;}

        ResultType min(ResultType a, ResultType b){ return (a <= b) ? a : b;}

        uint64_t getClockTime(){
            return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
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