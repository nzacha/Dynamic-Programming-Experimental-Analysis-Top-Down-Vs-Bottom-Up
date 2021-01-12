#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
args_1=(5 50 500 5000)
problems_1=("dijkstra")
methods=("iterative" "recursive")  

ulimit -s unlimited

for problem in ${problems_1[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_1[@]}
		do
			for arg in ${args_1[@]}
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