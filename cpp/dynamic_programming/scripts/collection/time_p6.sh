#declare program arguments
sizes_6=(500 1000 1500 2000 2500 3000)
args_6=(1 2 6 11 16 21 26)
problems_6=("mostCommonSubSequence")
methods=("iterative" "recursive")  

ulimit -s unlimited

for problem in ${problems_6[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_6[@]}
		do
			for arg in ${args_6[@]}
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