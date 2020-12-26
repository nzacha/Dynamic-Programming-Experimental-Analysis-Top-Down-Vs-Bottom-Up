#declare program arguments
sizes_3=(20000000 40000000 60000000 80000000 100000000 120000000 140000000)
problems_3=("treeDiameter" "kTrees")

ulimit -s unlimited

#iterative for third problems
for problem in ${problems_3[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes_3[@]}
	do
		for attempt in {1..3}
		do
			echo "mem iterative ${problem} ${size} ${attempt}" > log.txt
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -iterative -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_hextra.txt
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_stack.txt
			
		done
	done
done

#recursive for third problems
for problem in ${problems_3[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes_3[@]}
	do
		for attempt in {1..3}
		do
			echo "mem recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -recursive -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_hextra.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_stack.txt
			
		done
	done
done