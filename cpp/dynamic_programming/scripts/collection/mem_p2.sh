#declare program arguments
sizes_2=(10000 20000 30000 40000 50000 60000 70000 80000)
problems_2=("chainMatrixMultiplication")

#iterative for second problems
for problem in ${problems_2[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes_2[@]}
	do
		for attempt in {1..3}
		do
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -iterative -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_hextra.txt
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_stack.txt
			
		done
	done
done

#recursive for second problems
for problem in ${problems_2[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes_2[@]}
	do
		for attempt in {1..3}
		do
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -recursive -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_hextra.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_stack.txt
			
		done
	done
done
