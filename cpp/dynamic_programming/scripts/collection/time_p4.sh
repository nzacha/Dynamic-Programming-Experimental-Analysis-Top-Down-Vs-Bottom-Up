#declare program arguments
sizes_4=(8000 16000 24000 32000 40000 48000 56000)
problems_5=( "longestIncreasingSubSequence1D" "longestIncreasingSubSequence2D")

#time iterative fourth problems
for problem in ${problems_4[@]}
do				
	for size in ${sizes_4[@]}
	do
		for attempt in {1..12}
		do
			echo "time iterative ${problem} ${size} ${attempt}" > log.txt
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -iterative -q -o -dir $DIR_ITERATIVE
		done
	done
done

#time recursive fourth problems
for problem in ${problems_4[@]}
do
	for size in ${sizes_4[@]}
	do
		for attempt in {1..12}
		do
			echo "time recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done