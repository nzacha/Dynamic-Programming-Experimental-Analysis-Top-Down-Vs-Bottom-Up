#clean results directory
rm -rf time_results
mkdir time_results

#compile program
./compile.sh

echo "Running Time Routine"

#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000 62500 65000 67500)
problems_1=("dijkstra" "independentSets" "knapsack")

sizes_2=(7500 15000 22500 30000 37500 45000 52500 60000 67500 75000 82500 85000 87500 90000)
problems_2=("allPairShortestPath" "chainMatrixMultiplication")

#time iterative first problems
for problem in ${problems_1[@]}
do
	mkdir time_results/
	mkdir time_results/iterative
				
	for size in ${sizes_1[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir time_results/iterative/
		done
	done
done

#time recursive first problems
for problem in ${problems_1[@]}
do
	mkdir time_results/recursive			
	
	for size in ${sizes_1[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -recursive -q -o -dir time_results/recursive		
		done
	done
done

#time iterative second problems
for problem in ${problems_2[@]}
do
	mkdir time_results/
	mkdir time_results/iterative
				
	for size in ${sizes_2[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -iterative -q -o -dir time_results/iterative/
		done
	done
done

#time recursive second problems
for problem in ${problems_2[@]}
do
	mkdir time_results/recursive			
	
	for size in ${sizes_2[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -recursive -q -o -dir time_results/recursive		
		done
	done
done

echo "sending mail"
mail -s "Time Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 