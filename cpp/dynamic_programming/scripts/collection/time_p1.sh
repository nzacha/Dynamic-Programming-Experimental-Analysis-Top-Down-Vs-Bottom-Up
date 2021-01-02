#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("mostCommonSubSequence") #"dijkstra" "independentSets" 
methods=("iterative") #"recursive" 

ulimit -s unlimited

for problem in ${problems_1[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_1[@]}
		do
			for attempt in {1..12}
			do
				echo "time ${method} ${problem} ${size} ${attempt}" > log.txt
				echo "Running ${method} " ${problem} " size: ${size} x${attempt}"
				./executable.out ${problem} ${size} -${method} -q -o -dir $DIR_RECURSIVE		
			done
		done
	done
done