make

rm -rf Results
mkdir Results
mkdir Results/Time
mkdir Results/Memory

alphabets=(26 52)
sizes=(10 100 200 500 1000 2000 5000 10000 20000 50000 80000 90000)


for alphabet in ${alphabets[@]};
do
	for size in ${sizes[@]};
	do
		for method in {1..2};
		do	
			for attempt in 2;
			do
				echo "Running size: ${size} for alphabet: ${alphabet} and for method: ${method} x${attempt}"		
				#run massif profiler
				valgrind --tool=massif --massif-out-file=Results/res_massif_${alphabet}_${size}_${method}_${attempt}.txt --stacks=yes ./a.out ../Inputs/sequenceA_${alphabet}_${size}_${attempt}.txt ../Inputs/sequenceB_${alphabet}_${size}_${attempt}.txt $method ${size} > Results/res_${alphabet}_${size}_${method}_${attempt}.txt 2>&1;
				#heap usage
				cat Results/res_massif_${alphabet}_${size}_${method}_${attempt}.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 > Results/Memory/mem_heap_${alphabet}_${size}_${method}.txt;	
				#extra heap usage
				cat Results/res_massif_${alphabet}_${size}_${method}_${attempt}.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 > Results/Memory/mem_heap_extra_${alphabet}_${size}_${method}.txt;	
				#stack usage
				cat Results/res_massif_${alphabet}_${size}_${method}_${attempt}.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 > Results/Memory/mem_stack_${alphabet}_${size}_${method}.txt;	
				#grep exeecute time
				cat Results/res_${alphabet}_${size}_${method}_${attempt}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${alphabet}_${size}_${method}_${attempt}.txt;	
			done
		done
	done
done


for alphabet in ${alphabets[@]};
do
	for size in ${sizes[@]};
	do
		for method in {1..2};
		do	
			for attempt in 1;
			do
				echo "Running size: ${size} for alphabet: ${alphabet} and for method: ${method} x${attempt}"		
				#run valgrind profiler
				valgrind ./a.out ../Inputs/sequenceA_${alphabet}_${size}_${attempt}.txt ../Inputs/sequenceB_${alphabet}_${size}_${attempt}.txt $method ${size} > Results/res_${alphabet}_${size}_${method}_${attempt}.txt 2>&1;
				#grep heap allocation
				cat Results/res_${alphabet}_${size}_${method}_${attempt}.txt | grep "bytes allocated" | cut -d ' ' -f 11 > Results/Memory/mem_${alphabet}_${size}_${method}.txt;	
				#grep execute time
				cat Results/res_${alphabet}_${size}_${method}_${attempt}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${alphabet}_${size}_${method}_${attempt}.txt;	
			done
		done
	done
done


for alphabet in ${alphabets[@]};
do
	for size in ${sizes[@]};
	do
		for method in {1..2};
		do	
			for attempt in {3..5};
			do
				echo "Running size: ${size} for alphabet: ${alphabet} and for method: ${method} x${attempt}"		
				./a.out ../Inputs/sequenceA_${alphabet}_${size}_${attempt}.txt ../Inputs/sequenceB_${alphabet}_${size}_${attempt}.txt $method ${size} > Results/res_${alphabet}_${size}_${method}_${attempt}.txt 2>&1;				
				cat Results/res_${alphabet}_${size}_${method}_${attempt}.txt | grep "Time_taken" | cut -d ':' -f2 > Results/Time/time_${alphabet}_${size}_${method}_${attempt}.txt;	
			done
		done
	done
done