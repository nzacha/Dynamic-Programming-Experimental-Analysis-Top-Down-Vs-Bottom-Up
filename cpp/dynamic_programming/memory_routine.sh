#clean results directory
rm -rf mem_results
mkdir mem_results

#compile program
./compile.sh

#declare program arguments
sizes=(100) #500 1000 5000 10000 50000 100000 500000 1000000)
problems=("allPairShortestPath" "chainMatrixMultiplication" "dijkstra" "independentSets" "knapsack" "mostCommonSubSequence")

for problem in ${problems[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running iterative size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -iterative -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 > mem_results/${problem}/iterative/extract_${size}_${attempt}.txt	
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_${attempt}.txt
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/iterative/extract_${size}_${attempt}.txt
			
		done
	done
done

for problem in ${problems[@]}
do
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes[@]}
	do
		for attempt in {1..7}
		do
			echo "Running recursive size: ${size} x${attempt}"

			valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} -recursive -q
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_${attempt}.txt	
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_${attempt}.txt
			
			cat mem_results/${problem}/massif${size}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/recursive/extract_${size}_${attempt}.txt
			
		done
	done
done


#clean unwanted files
./scripts/clean.sh

#notify me via mail & sound
./scripts/notify.sh