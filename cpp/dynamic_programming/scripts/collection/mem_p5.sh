#declare program arguments
sizes_5=(500 1000 1500 2000 2500 3000)
args_5=(50 500 5000 50000)
problems_5=("chainMatrixMultiplication")
methods=("iterative" "recursive")  

ulimit -s unlimited

for problem in ${problems_5[@]}
do
	for method in ${methods[@]}
	do
		mkdir mem_results/${problem}
		mkdir mem_results/${problem}/${method}
					
		for size in ${sizes_5[@]}
		do
			for arg in ${args_5[@]}
			do
				for attempt in {1..3}
				do
					echo "mem ${method} ${problem} ${size} ${arg} ${attempt}" > log.txt
					echo "Running ${method} " ${problem} " size: ${size} arg: ${arg} x${attempt}"

					valgrind --tool=massif --massif-out-file=mem_results/${problem}/massif${size}_${arg}_${attempt}.txt --stacks=yes ./executable.out ${problem} ${size} ${arg} -${method} -q
					
					cat mem_results/${problem}/massif${size}_${arg}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 >> mem_results/${problem}/${method}/extract_${size}_${arg}_heap.txt	
					cat mem_results/${problem}/massif${size}_${arg}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> mem_results/${problem}/${method}/extract_${size}_${arg}_hextra.txt
					cat mem_results/${problem}/massif${size}_${arg}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> mem_results/${problem}/${method}/extract_${size}_${arg}_stack.txt
				done	
			done
		done
	done
done