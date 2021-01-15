#declare program arguments
sizes_2=(135000 150000) #15000 30000 45000 60000 75000 90000 105000 120000 
args_2=(250 2500 25000)
problems_2=("knapsack")
methods=("recursive") #iterative

ulimit -s unlimited

for problem in ${problems_2[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_2[@]}
		do
			for arg in ${args_2[@]}
			do
				for attempt in {1..12}
				do
					echo "time ${method} ${problem} ${size} ${arg} ${attempt}" > log.txt
					echo "Running ${method} " ${problem} " size: ${size} arg: ${arg}, x${attempt}"
					./executable.out ${problem} ${size} ${arg} -${method} -q -o -dir $DIR/$method		
				done
			done
		done
	done
done