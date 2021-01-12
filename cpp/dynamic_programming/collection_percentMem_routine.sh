#clean results directory
mkdir mem_results

echo "Running Perecent Memory Routine"

#dijkstra, independent_sets
#./scripts/collection/per_p1.sh

#knapsack
#./scripts/collection/per_p2.sh

#treeDiameter kTrees
./scripts/collection/per_p3.sh

#longestCommonSubSequence1D longestCommonSubSequence2D
./scripts/collection/per_p4.sh

#chainmatrixmultiplication
./scripts/collection/per_p5.sh

#mostCommonSubSequebce
#./scripts/collection/per_p6.sh

echo "sending mail"
mail -s "Percent Memory Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 