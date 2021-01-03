#clean results directory
mkdir mem_results

echo "Running Perecent Memory Routine"

#kTrees treeDiameter
./scripts/collection/per_p3.sh

#"dijkstra" "mostCommonSubSequence" "independentSets"
#./scripts/collection/per_p1.sh

#knapsack
#./scripts/collection/per_p4.sh

#chainmatrixmultiplication
#./scripts/collection/per_p2.sh

echo "sending mail"
mail -s "Percent Memory Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 