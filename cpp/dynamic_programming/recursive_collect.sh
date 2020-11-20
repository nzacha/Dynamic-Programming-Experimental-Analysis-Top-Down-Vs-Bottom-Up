#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000 62500 65000 67500)
problems_1=("dijkstra" "independentSets" "knapsack")

sizes_2=(7500 15000 22500 30000 37500 45000 52500 60000 67500 75000 82500 85000 87500 90000)
problems_2=("allPairShortestPath" "chainMatrixMultiplication")


#recursive for first problems
for problem in ${problems_1[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes_1[@]}
	do
		for attempt in {1..3}
		do
			echo "Running recursive  ${problem}  size: ${size} x${attempt}"

			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_hextra.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_stack.txt
			
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
			echo "Running recursive  ${problem}  size: ${size} x${attempt}"

			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_heap.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_hextra.txt	
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_stack.txt
			
		done
	done
done