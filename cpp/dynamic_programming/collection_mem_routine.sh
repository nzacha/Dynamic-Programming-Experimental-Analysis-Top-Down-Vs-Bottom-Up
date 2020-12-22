#clean results directory
rm -rf mem_results
mkdir mem_results

echo "Running Memory Routine"

#dijkstra, independent sets
./scripts/collection/mem_p1.sh

#chainmatrixmultiplication
./scripts/collection/mem_p2.sh

#allpairshortestpath
#/scripts/collection/mem_p3.sh

#knapsack
./scripts/collection/mem_p4.sh

#treeDiameter
./scripts/collection/mem_p6.sh

#kTrees
./scripts/collection/mem_p7.sh

#longestCommonSubSequence
./scripts/collection/mem_p5.sh

echo "sending mail"
mail -s "Memory Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 