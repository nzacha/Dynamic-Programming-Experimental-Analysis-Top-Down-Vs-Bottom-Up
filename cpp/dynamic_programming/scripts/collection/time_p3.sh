#declare program arguments
sizes_3=(20000000 40000000 60000000 80000000 100000000 120000000 140000000)
args_3=(1 10 100 1000 10000)
problems_3=("treeDiameter" "independentSets" "kTrees")
methods=("iterative" "recursive")

ulimit -s unlimited

for problem in ${problems_3[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_3[@]}
		do
			for arg in ${args_3[@]}
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