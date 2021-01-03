#clean results directory
rm -rf mem_results
mkdir mem_results

echo "Running Memory Routine"

#chainmatrixmultiplication
#./scripts/collection/mem_p5.sh

#knapsack
#./scripts/collection/mem_p2.sh

#treeDiameter kTrees
./scripts/collection/mem_p3.sh

#longestCommonSubSequence1D longestCommonSubSequence2D
#./scripts/collection/mem_p4.sh

#dijkstra, independent_sets mostCommonSubSequebce
#./scripts/collection/mem_p1.sh

echo "sending mail"
mail -s "Memory Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 