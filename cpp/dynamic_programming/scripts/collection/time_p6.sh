#declare program arguments
sizes_6=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000)
problems_6=("treeDiameter" "kTrees")

ulimit -s unlimited

#time iterative fourth problems
for problem in ${problems_6[@]}
do				
	for size in ${sizes_6[@]}
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
for problem in ${problems_6[@]}
do
	for size in ${sizes_6[@]}
	do
		for attempt in {1..12}
		do
			echo "time recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done