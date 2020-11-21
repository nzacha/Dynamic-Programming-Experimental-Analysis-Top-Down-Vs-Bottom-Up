#clean results directory
rm -rf time_results
mkdir time_results

echo "Running Time Routine"

#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("dijkstra" "independentSets")

sizes_2=(10000 20000 30000 40000 50000 60000 70000 80000) #85000)
problems_2=("chainMatrixMultiplication")

sizes_3=(2500 5000 7500 10000 12500 15000 17500)
problems_3=("allPairShortestPath")

sizes_4=(20000 40000 60000 80000 100000 120000 130000)
problems_4=("knapsack")

DIR="time_results"
DIR_ITERATIVE=$DIR"/iterative"
DIR_RECURSIVE=$DIR"/recursive"

mkdir $DIR
mkdir $DIR_ITERATIVE
mkdir $DIR_RECURSIVE

#time iterative first problems
for problem in ${problems_1[@]}
do		
	for size in ${sizes_1[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir $DIR_ITERATIVE
		done
	done
done

#time recursive first problems
for problem in ${problems_1[@]}
do		
	for size in ${sizes_1[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done

#time iterative second problems
for problem in ${problems_2[@]}
do				
	for size in ${sizes_2[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir $DIR_ITERATIVE
		done
	done
done

#time recursive second problems
for problem in ${problems_2[@]}
do
	for size in ${sizes_2[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done

#time iterative third problems
for problem in ${problems_3[@]}
do				
	for size in ${sizes_3[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir $DIR_ITERATIVE
		done
	done
done

#time recursive third problems
for problem in ${problems_3[@]}
do
	for size in ${sizes_3[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done

#time iterative fourth problems
for problem in ${problems_4[@]}
do				
	for size in ${sizes_4[@]}
	do
		for attempt in {1..12}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir $DIR_ITERATIVE
		done
	done
done

#time recursive fourth problems
for problem in ${problems_4[@]}
do
	for size in ${sizes_4[@]}
	do
		for attempt in {1..12}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done

echo "sending mail"
mail -s "Execution Time Collection Done" zicolas3@gmail.com <<< "Hello, execution has finished :)" 