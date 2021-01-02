#declare program arguments
sizes_5=(20000 30000 40000 50000 60000 70000 80000) #10000
problems_5=("chainMatrixMultiplication")
methods=("iterative") #"recursive" 

ulimit -s unlimited

for problem in ${problems_5[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_5[@]}
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