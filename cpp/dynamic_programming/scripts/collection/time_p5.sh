#declare program arguments
sizes_5=(1000 2000 3000 4000 5000 6000)
args_5=(50 500 5000)
problems_5=("chainMatrixMultiplication")
methods=("iterative" "recursive") 

ulimit -s unlimited

for problem in ${problems_5[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_5[@]}
		do
			for arg in ${args_5[@]}
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