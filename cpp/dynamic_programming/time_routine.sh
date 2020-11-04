#clean results directory
rm -rf time_results
mkdir time_results

#compile program
./compile.sh

#declare program arguments
sizes=(100 500 1000 5000 10000 50000 100000 500000 1000000)
problems=("allPairShortestPath" "chainMatrixMultiplication" "dijkstra" "independentSets" "knapsack" "mostCommonSubSequence")

for problem in ${problems[@]}
do
	mkdir time_results/
	mkdir time_results/iterative
				
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -iterative -q -o -dir time_results/iterative/
		done
	done
done

for problem in ${problems[@]}
do
	mkdir time_results/recursive			
	
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -recursive -q -o -dir time_results/${problem}/recursive		
		done
	done
done


#clean unwanted files
./scripts/clean.sh

#notify me via mail & sound
./scripts/notify.sh
