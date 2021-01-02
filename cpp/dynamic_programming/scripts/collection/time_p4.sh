#declare program arguments
sizes_4=(8000 16000 24000 32000 40000 48000 56000)
problems_4=("longestIncreasingSubSequence2D") #"longestIncreasingSubSequence1D" 
methods=("iterative") #"recursive" 

ulimit -s unlimited

for problem in ${problems_4[@]}
do
	for method in ${methods[@]}
	do
		for size in ${sizes_4[@]}
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