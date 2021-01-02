#declare program arguments
sizes_3=(20000000 40000000 60000000 80000000 100000000 120000000 140000000)
problems_3=("treeDiameter" "kTrees")
methods=("iterative") #"recursive" 

ulimit -s unlimited

for problem in ${problems_3[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_3[@]}
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