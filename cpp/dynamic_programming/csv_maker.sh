#!/bin/bash

#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
args_1=(5 50 500 5000)
problems_1=("dijkstra")

sizes_2=(15000 30000 45000 60000 75000 90000 105000 120000 135000 150000)
args_2=(250 2500 25000)
problems_2=("knapsack")

sizes_3=(20000000 40000000 60000000 80000000 100000000 120000000 140000000)
args_3=(10 100 1000 10000)
problems_3=("treeDiameter" "independentSets" "kTrees")

sizes_4=(8000 16000 24000 32000 40000 48000 56000)
args_4=(50 500 5000 50000 500000)
problems_4=("longestIncreasingSubSequence2D") #"longestIncreasingSubSequence1D" 

sizes_5=(1000 2000 3000 4000 5000 6000)
args_5=(50 500 5000 50000)
problems_5=("chainMatrixMultiplication")

sizes_6=(500 1000 1500 2000 2500 3000)
args_6=(1 2 6 11 16 21 26)
problems_6=("mostCommonSubSequence")

#sizes_6=(2500 5000 7500 10000 12500 15000 17500)
#problems_6=("allPairShortestPath")

rm -rf data
mkdir data

mkdir data/per
mkdir data/mem
mkdir data/time

M_ATTEMPTS=3
T_ATTEMPTS=12
ITERATIVE="iterative"
RECURSIVE="recursive"

function printAttempts {
	printf "Attempt," >> $1
	for (( i=1; i<=$2; i++))
	do
		printf "$i," >> $1
	done
	echo >> $1
}

function printHeap {
	printf "Heap," >> $1
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/$2/$3/extract_${4}_${5}_heap.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printExtraHeap {
	printf "Extra Heap," >> $1
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/$2/$3/extract_${4}_${5}_hextra.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printStack {
	printf "Stack," >> $1
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/$2/$3/extract_${4}_${5}_stack.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printTime {
	printf "${4}," >> $1
	for (( i=1; i<=$T_ATTEMPTS; i++))
	do
		cat time_results/$2/$3/time_item_${4}_arg_${5}.txt | grep "$2 time taken: " | tr -d "{$2} time taken: " | rev | cut -c 3- | rev | cut -d ' ' -f 1 | head -$i | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printPerMem {
	printf "${4}," >> $1	
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/${2}/${3}/per_${4}_${5}_${i}.txt | tr , . | sort -n | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

#iterative for first problems
for problem in ${problems_1[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
	printAttempts
	for arg in ${args_1[@]}
	do	
		for size in ${sizes_1[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#create attempts tables
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg 

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for first problems
for problem in ${problems_1[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS

	for arg in ${args_1[@]}
	do			
		for size in ${sizes_1[@]}
		do
			#append size
			echo "Size,$size" >> $file

			#create mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done

#iterative for second problems
for problem in ${problems_2[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_2[@]}
	do
		for size in ${sizes_2[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for second problems
for problem in ${problems_2[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
			
	for arg in ${args_1[@]}
	do
		for size in ${sizes_2[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done

#iterative for third problems
for problem in ${problems_3[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_3[@]}
	do
		for size in ${sizes_3[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for second problems
for problem in ${problems_3[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_3[@]}
	do
		for size in ${sizes_3[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done

#iterative for fourth problems
for problem in ${problems_4[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
			
	for arg in ${args_4[@]}
	do
		for size in ${sizes_4[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for fourth problems
for problem in ${problems_4[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_4[@]}
	do
		for size in ${sizes_4[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done

#iterative for fifth problems
for problem in ${problems_5[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_5[@]}
	do	
		for size in ${sizes_5[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for fifth problems
for problem in ${problems_5[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	rintAttempts $t_file $T_ATTEMPTS
		
		
	for arg in ${args_5[@]}
	do
		for size in ${sizes_5[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done

#iterative for sixth problems
for problem in ${problems_6[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	p_file=data/per/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_6[@]}
	do
		for size in ${sizes_6[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $ITERATIVE $size $arg
			printExtraHeap $file $problem $ITERATIVE $size $arg
			printStack $file $problem $ITERATIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $ITERATIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $ITERATIVE $size $arg
		done
	done
done

#recursive for sixth problems
for problem in ${problems_6[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	p_file=data/per/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for arg in ${args_6[@]}
	do
		for size in ${sizes_6[@]}
		do
			#print size
			echo "Size,$size" >> $file

			#append mem file
			printAttempts $file $M_ATTEMPTS
			printHeap $file $problem $RECURSIVE $size $arg
			printExtraHeap $file $problem $RECURSIVE $size $arg
			printStack $file $problem $RECURSIVE $size $arg
			echo >> $file

			#append time file
			printTime $t_file $RECURSIVE $problem $size $arg

			#print mem %
			printPerMem $p_file $problem $RECURSIVE $size $arg
		done
	done
done