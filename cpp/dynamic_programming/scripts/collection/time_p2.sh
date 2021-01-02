#declare program arguments
sizes_2=(15000 30000 45000 60000 75000 90000 105000 120000 135000)
problems_2=("knapsack")
methods=("iterative") #"recursive" 

ulimit -s unlimited

for problem in ${problems_2[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_2[@]}
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