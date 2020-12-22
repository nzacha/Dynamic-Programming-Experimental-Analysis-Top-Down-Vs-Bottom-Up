#declare program arguments
sizes_7=(100000 200000 300000 400000 500000 600000 700000 800000)
problems_7=("kTrees")

#time iterative fourth problems
for problem in ${problems_7[@]}
do				
	for size in ${sizes_7[@]}
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
for problem in ${problems_7[@]}
do
	for size in ${sizes_7[@]}
	do
		for attempt in {1..12}
		do
			echo "time recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"
			./executable.out ${problem} ${size} -recursive -q -o -dir $DIR_RECURSIVE		
		done
	done
done