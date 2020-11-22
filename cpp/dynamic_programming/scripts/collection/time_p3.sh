#declare program arguments
sizes_3=(2500 5000 7500 10000 12500 15000 17500)
problems_3=("allPairShortestPath")

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