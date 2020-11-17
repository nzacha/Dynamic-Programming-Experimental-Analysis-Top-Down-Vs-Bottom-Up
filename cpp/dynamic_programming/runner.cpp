#define runner_cpp

#include <thread>
#include <sys/stat.h>

#include "helper/problem.h"
#include "allpairShortestPath/allpairShortestPath.cpp"
#include "chainMatrixMultiplication/chainMatrixMultiplication.cpp"
#include "dijkstra/dijkstra.cpp"
#include "independendSets/independentSets.cpp"
#include "knapsack/knapsack.cpp"
#include "mostCommonSubSequence/mostCommonSubSequence.cpp"

void runAndWriteProblem(Problem<int>* problem, string outFile, bool recursive, bool iterative, bool writeOut){
    if(recursive && iterative)
        problem->runCheck(problem->args);
    else if(recursive)
        problem->runTimeRecursive(problem->args);
    else if(iterative)
        problem->runTimeIterative(problem->args);
    
    if(writeOut) problem->writeData(outFile);
}

void runAllPairShortestPath(int index, int num_of_items, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=> Thread " << index << " running \"all pair shortest path\" with " << num_of_items << endl; 
    ShortestPath* problem = new ShortestPath(num_of_items);
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

void runChainMatrixMultiplication(int index, int num_of_items, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=>Thread " << index << " running \"chain matrix multiplication\" with " << num_of_items << endl; 
    ChainMatrixMultiplication* problem = new ChainMatrixMultiplication(num_of_items);
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

void runDijkstra(int index, int num_of_items, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=> Thread " << index << " running \"dijkstra\" with " << num_of_items << endl; 
    Dijkstra* problem = new Dijkstra(num_of_items, 0, num_of_items-1);
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

void runIndependentSets(int index, int num_of_items, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=> Thread " << index << " running \"independent sets\" with " << num_of_items << endl; 
    IndependentSet* problem = new IndependentSet(num_of_items);
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

void runKnapsack(int index, int num_of_items, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=> Thread " << index << " running \"knapsack\" with " << num_of_items << endl; 
    Knapsack* problem = new Knapsack(num_of_items, num_of_items/5);
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

void runMCSS(int index, string fileName, string outFile, bool recursive, bool iterative, bool writeOut){
    cout << "\t=> Thread " << index << " running \"most common sub-sequence\" with " << fileName << endl; 
    string inputDir = "mostCommonSubSequence/Inputs/";
    string seqA_file = inputDir+ "sequenceA"+ fileName; 
    string seqB_file = inputDir+ "sequenceB"+ fileName; 
    MostCommonSubSequence* problem = new MostCommonSubSequence(getSequenceFromFile(seqA_file), getSequenceFromFile(seqB_file));
    
    runAndWriteProblem(problem, outFile, recursive, iterative, writeOut);
}

template <typename type, typename pred>
void runProblem(type arg, string dir_out, int numThreads, int perThreadReps, pred funct, bool recursive, bool iterative, bool writeOut){
    stringstream ss;
    ss << arg;
    
    for(int r=0; r<perThreadReps; r++){
        cout << "> Working on Item " << arg << " x " << r << endl; 

        if(numThreads > 1){
            cout << "numThreads > 1 : doing nothing" << endl;
            thread threads[numThreads];
            for(int i=0; i<numThreads; i++){
                threads[i] = thread(funct, i, arg, dir_out+ "time_item_"+ ss.str()+ "_thread_"+to_string(i)+ "rep_"+to_string(r)+".txt", recursive, iterative, writeOut);
                }   
            for(int i=0; i<numThreads; i++){
                threads[i].join();
            }
        }else{
            funct(0, arg, dir_out+ "time_item_"+ ss.str()+ "_rep_"+to_string(r)+".txt", recursive, iterative, writeOut);
        }
    }
}

enum Program {allPairShortestPath = 0, chainMatrixMultiplcation, dijkstra, independentSets, knapsack, mostCommonSubSequence, NUM_OF_PROBLEMS};
string ProgramNames[] = {"allPairShortestPath", "chainMatrixMultiplication", "dijkstra", "independentSets", "knapsack", "mostCommonSubSequence"};

void printHelpText(){
    cout << "> Program list: " << endl << "\t";
    for(int pid =0; pid<Program::NUM_OF_PROBLEMS; pid++)
        cout << "[ " << pid << " - \"" << ProgramNames[pid] << "\"] ";
    cout << endl << endl;

    cout << "> Commands: " << endl;
    cout << "\t[programn name] [argument] : to specify one of the programs" << endl << endl;
    cout << "\t-p [program index] [argument] : selects program by index" << endl << endl;
    cout << "\t-recursive : only recursive methods will be run" << endl << endl;
    cout << "\t-iterative : only iterative methods will be run" << endl << endl;
    cout << "\t-a -all : to run all programs with hardcoded parameters" << endl << endl;
    cout << "\t-r [amount] : to specify the number of repeatitions for each thread" << endl << endl;
    cout << "\t-t [amount] : to specify the number of threads" << endl << endl;
    cout << "\t-q -quiet : disables default output stream" << endl << endl;
    cout << "\t-clear : cleans output directory" << endl << endl;
    cout << "\t-h -help : shows this help menu" << endl;
}

int main (int argc, char** argv){
    string argument, out_dir = "results/";
    //The index of the program to run
    int program = -1;
    //The number of threads to be used per problem
    int numThreads = 1;
    //The number of repeatitions for each thread
    int perThreadReps = 1;
    bool run_all = false, quiet = false, clearOutputDir = false, writeOut=false;
    bool bothMethods = true, iterative = false, recursive = false;
    for(int i=0; i<argc; i++){
        string arg = (string)argv[i];
        if(arg == "-h" || arg == "-help"){
            printHelpText();
            return 0;
            
        } else if(arg == "-q" || arg == "-quiet"){
            quiet = true;

        } else if(arg == "-clear"){
            clearOutputDir = true;

        } else if(arg == "-recursive"){
            if(!bothMethods){
                cout << "Both iterative and recursive flags were set to true... Exiting..." << endl;
                return 1;
            }
            recursive = true;
            bothMethods = false;

        } else if(arg == "-iterative"){
            if(!bothMethods){
                cout << "Both iterative and recursive flags were set to true... Exiting..." << endl;
                return 1;
            }
            iterative = true;
            bothMethods = false;

        } else if(arg == "-dir"){
            if(i+1 >= argc){
                cout << "Please specify file name after \"-dir\" command... Exiting..." << endl;
                return 1;
            }
            out_dir = argv[++i];
            mkdir(out_dir.c_str(), S_IRWXU);
            out_dir += "/";

        } else if(arg == "-o"){
            writeOut = true;

        } else if(arg == "-r"){
            if(i+1 >= argc){
                cout << "Please specify number of repeatitions after \"-r\" command... Exiting..." << endl;
                return 1;
            }
            perThreadReps = stoi(argv[++i]);

        } else if(arg == "-t"){
            if(i+1 >= argc){
                cout << "Please specify number of threads to be used after \"-t\" command... Exiting..." << endl;
                return 1;
            }
            numThreads = stoi(argv[++i]);

        } else if(arg == "-all" || arg == "-a") {
            run_all = true;
        } else if(arg == "-p"){
            if(i+1 >= argc){
                cout << "Please specify program number after \"-p\" command... Exiting..." << endl;
                return 1;
            }

            program = stoi(argv[++i]);
            if (program >= Program::NUM_OF_PROBLEMS || program < 0){
                cout << "Invalid program number selected... Exiting..." << endl;
                return 1;
            }

            if(i+1 >= argc){
                cout << "Please specify argument value after program command... Exiting..." << endl;
                return 1;   
            }
            argument = argv[++i];

        } else {
            for(int j=0; j<Program::NUM_OF_PROBLEMS; j++){
                if(arg == ProgramNames[j]){
                    if(program != -1) {
                        cout << "More than 1 Program selected... Exiting..." << endl;
                        return 1;
                    }
                    program = j;

                    if(i+1 >= argc){
                        cout << "Please specify argument value after program command... Exiting..." << endl;
                        return 1;   
                    }
                    argument = argv[++i];
                    break;
                }
            }
        }
    }

    if(writeOut)
        mkdir(out_dir.c_str(), S_IRWXU);
    
    if(program == -1 && !run_all){
        cout << "No program was specified... Exiting..." << endl << endl;
        printHelpText();
        return 1;
    }

    //Disable output stream
    if(quiet)
        cout.setstate(ios_base::failbit);

    if(program!=-1) cout << "Running program " << ProgramNames[program] << " with: " << endl;
    else if(run_all)cout << "Running all programs with hardcoded arguments" << endl;
    //else cout << "Program not specified. Will run everything with hardcoded arguments" << endl;
    
    cout << endl;
    cout << "> Number of threads: " << numThreads << endl;
    cout << "> Repeatitons per thread: " << perThreadReps << endl;
    cout << endl;

    //Declare output directories
    unordered_map<string, string> fileNames = 
    {{ProgramNames[Program::allPairShortestPath], out_dir+ "allPairShortestPath/"}, 
    {ProgramNames[Program::chainMatrixMultiplcation], out_dir+ "chainMatrixMultiplication/"},
    {ProgramNames[Program::dijkstra], out_dir+ "dijkstra/"},
    {ProgramNames[Program::independentSets], out_dir+ "independendSets/"},
    {ProgramNames[Program::knapsack], out_dir+ "knapsack/"},
    {ProgramNames[Program::mostCommonSubSequence], out_dir+ "mostCommonSubSequence/"},
    };

    //Clear output directories
    for(pair<string, string> s: fileNames){
        if(clearOutputDir) 
            remove(s.second.c_str());
        if(run_all)
            mkdir(s.second.c_str(), S_IRWXU);
    }

    if(bothMethods){
        recursive = true;
        iterative = true;
    }

    //Run problems
    if(run_all){
        //Declare the problem arguments
        vector<int> allPairParams {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
        vector<int> chainMatrixParams {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
        vector<int> dijkstraParams {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
        vector<int> independentSetsParams {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
        vector<int> knapsackParams {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
        vector<string> mcssParams {"_26_10_1.txt", "_26_100_1.txt", "_26_1000_1.txt", "_26_10000_1.txt", "_26_20000_1.txt"};

        //Run the problems with specified arguments
        for(int i: allPairParams)
            runProblem(i, fileNames[ProgramNames[Program::allPairShortestPath]], numThreads, perThreadReps, runAllPairShortestPath, recursive, iterative, writeOut);
        
        for(int i: chainMatrixParams)
            runProblem(i, fileNames[ProgramNames[Program::chainMatrixMultiplcation]], numThreads, perThreadReps, runChainMatrixMultiplication, recursive, iterative, writeOut);
        
        for(int i: dijkstraParams)
            runProblem(i, fileNames[ProgramNames[Program::dijkstra]], numThreads, perThreadReps, runDijkstra, recursive, iterative, writeOut);
        
        for(int i: independentSetsParams)
            runProblem(i, fileNames[ProgramNames[Program::independentSets]], numThreads, perThreadReps, runIndependentSets, recursive, iterative, writeOut);
        
        for(int i: knapsackParams)
            runProblem(i, fileNames[ProgramNames[Program::knapsack]], numThreads, perThreadReps, runKnapsack, recursive, iterative, writeOut);
        
        for(string s: mcssParams)
            runProblem(s, fileNames[ProgramNames[Program::mostCommonSubSequence]], numThreads, perThreadReps, runMCSS, recursive, iterative, writeOut);
        
        //Enable output stream
        cout.clear();
        cout << "all routines done" << endl;
        return 0;
    }

    switch (program){
        case allPairShortestPath:
            mkdir(fileNames[ProgramNames[Program::allPairShortestPath]].c_str(), S_IRWXU);
            runProblem(stoi(argument), fileNames[ProgramNames[Program::allPairShortestPath]], numThreads, perThreadReps, runAllPairShortestPath, recursive, iterative, writeOut);
            break;
        case chainMatrixMultiplcation:
            mkdir(fileNames[ProgramNames[Program::chainMatrixMultiplcation]].c_str(), S_IRWXU);
            runProblem(stoi(argument), fileNames[ProgramNames[Program::chainMatrixMultiplcation]], numThreads, perThreadReps, runChainMatrixMultiplication, recursive, iterative, writeOut);
            break;
        case dijkstra:  
            mkdir(fileNames[ProgramNames[Program::dijkstra]].c_str(), S_IRWXU);
            runProblem(stoi(argument), fileNames[ProgramNames[Program::dijkstra]], numThreads, perThreadReps, runDijkstra, recursive, iterative, writeOut);
            break;
        case independentSets:
            mkdir(fileNames[ProgramNames[Program::independentSets]].c_str(), S_IRWXU);
            runProblem(stoi(argument), fileNames[ProgramNames[Program::independentSets]], numThreads, perThreadReps, runIndependentSets, recursive, iterative, writeOut);
            break;
        case knapsack:
            mkdir(fileNames[ProgramNames[Program::knapsack]].c_str(), S_IRWXU);
            runProblem(stoi(argument), fileNames[ProgramNames[Program::knapsack]], numThreads, perThreadReps, runKnapsack, recursive, iterative, writeOut);
            break;
        case mostCommonSubSequence:
            mkdir(fileNames[ProgramNames[Program::mostCommonSubSequence]].c_str(), S_IRWXU);
            runProblem(argument, fileNames[ProgramNames[Program::mostCommonSubSequence]], numThreads, perThreadReps, runMCSS, recursive, iterative, writeOut);
            break;
    }

    cout << endl << "Execution finished" << endl;
    return 0;
}