#clean results directory
mkdir mem_results

echo "Running Perecent Memory Routine"

#kTrees treeDiameter
#./scripts/collection/per_p3.sh

#mostCommonSubSequebce
./scripts/collection/per_p1.sh

#chainmatrixmultiplication
#./scripts/collection/per_p2.sh

echo "sending mail"
mail -s "Memory Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 