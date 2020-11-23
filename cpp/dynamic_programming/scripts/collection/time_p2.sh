#declare program arguments
sizes_2=(10000 ) #20000 30000 40000 50000 60000 70000 80000) #85000)
problems_2=("chainMatrixMultiplication" "mostCommonSubSequence")

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