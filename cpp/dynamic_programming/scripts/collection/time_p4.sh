#declare program arguments
sizes_4=(20000 40000 60000 80000 100000 120000 130000)
problems_4=("knapsack")

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