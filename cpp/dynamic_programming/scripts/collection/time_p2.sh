#declare program arguments
sizes_2=(15000 30000 45000 60000 75000 90000 105000 120000 135000)
problems_2=("knapsack")

ulimit -s unlimited

#time iterative second problems
for problem in ${problems_2[@]}
do				
	for size in ${sizes_2[@]}
	do
		for attempt in {1..12}
		do
			echo "time iterative ${problem} ${size} ${attempt}" > log.txt
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
			echo "time recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done
