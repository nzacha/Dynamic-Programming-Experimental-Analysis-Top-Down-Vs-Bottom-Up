#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("dijkstra" "independentSets" "mostCommonSubSequence")

ulimit -s unlimited

#time iterative first problems
for problem in ${problems_1[@]}
do		
	for size in ${sizes_1[@]}
	do
		for attempt in {1..12}
		do
			echo "time iterative ${problem} ${size} ${attempt}" > log.txt
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
			echo "time recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done
