#declare program arguments
sizes_6=(10000 20000 30000 40000 50000 60000 70000 80000 90000)
problems_6=("treeDiameter")

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