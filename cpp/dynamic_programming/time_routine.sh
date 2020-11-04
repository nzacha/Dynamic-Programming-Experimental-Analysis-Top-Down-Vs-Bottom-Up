#clean results directory
rm -rf mem_results
mkdir mem_results

#compile program
./compile.sh

#declare program arguments
sizes=(100 500 1000 5000 10000 50000 100000 500000 1000000)
problems=("allPairShortestPath" "chainMatrixMultiplication" "dijkstra" "independentSets" "knapsack" "mostCommonSubSequence")

for problem in ${problems[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running iterative size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -iterative -q -o -dir time_results/
		done
	done
done

for problem in ${problems[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running recursive size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -recursive -q -o -dir time_results/		
		done
	done
done


#clean unwanted files
./scripts/clean.sh

#notify me via mail & sound
./scripts/notify.sh
