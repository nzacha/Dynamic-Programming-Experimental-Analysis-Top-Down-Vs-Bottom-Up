#declare program arguments
sizes_4=(8000 16000 24000 32000 40000 48000 56000)
args_4=(50 500 5000)
problems_4=("longestIncreasingSubSequence2D") #"longestIncreasingSubSequence1D" 
methods=("iterative" "recursive") 

ulimit -s unlimited

for problem in ${problems_4[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_4[@]}
		do
			for arg in ${args_4[@]}
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