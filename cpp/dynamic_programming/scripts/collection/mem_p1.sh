#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("mostCommonSubSequence") # "dijkstra" "independentSets"

ulimit -s unlimited

#iterative for first problems
for problem in ${problems_1[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes_1[@]}
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

#recursive for first problems
for problem in ${problems_1[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes_1[@]}
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
