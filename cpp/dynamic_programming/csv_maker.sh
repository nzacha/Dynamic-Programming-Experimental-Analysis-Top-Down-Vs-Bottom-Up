#!/bin/bash

#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("dijkstra" "independentSets")

sizes_2=(10000 20000 30000 40000 50000 60000 70000 80000)
problems_2=("chainMatrixMultiplication" "mostCommonSubSequence")

#sizes_3=(2500 5000 7500 10000 12500 15000 17500)
problems_3=("allPairShortestPath")

sizes_4=(20000 40000 60000 80000 100000 120000 130000)
problems_4=("knapsack")

sizes_5=(20000 40000 60000 80000 100000 120000 140000 160000 180000 200000)
problems_5=("longestIncreasingSubSequence")

sizes_6=(10000 20000 30000 40000 50000 60000 70000 80000 90000)
problems_6=("treeDiameter")

sizes_7=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000)
problems_7=("kTrees")


rm -rf data
mkdir data

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
		cat mem_results/$2/$3/extract_${4}_heap.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printExtraHeap {
	printf "Extra Heap," >> $1
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/$2/$3/extract_${4}_hextra.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printStack {
	printf "Stack," >> $1
	for (( i=1; i<=$M_ATTEMPTS; i++))
	do
		cat mem_results/$2/$3/extract_${4}_stack.txt | head -1 | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

function printTime {
	printf "Time," >> $1
	for (( i=1; i<=$T_ATTEMPTS; i++))
	do
		cat time_results/$2/$3/time_item_${4}_rep_0.txt | grep "$2 time taken: " | tr -d "{$2} time taken: " | rev | cut -c 3- | rev | cut -d ' ' -f 1 | head -$i | tail -1 | tr -d '\n' >> $1
		printf "," >> $1
	done
	echo >> $1
}

#iterative for first problems
for problem in ${problems_1[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_1[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#create attempts tables
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for first problems
for problem in ${problems_1[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_1[@]}
	do
		#append size
		echo "Size,$size" >> $file

		#create mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for second problems
for problem in ${problems_2[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_2[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size

	done
done

#recursive for second problems
for problem in ${problems_2[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_2[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for third problems
for problem in ${problems_3[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_3[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for second problems
for problem in ${problems_3[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_3[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for fourth problems
for problem in ${problems_4[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_4[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for fourth problems
for problem in ${problems_4[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_4[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for fifth problems
for problem in ${problems_5[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_5[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for fifth problems
for problem in ${problems_5[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_5[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for sixth problems
for problem in ${problems_6[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_6[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for sixth problems
for problem in ${problems_6[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_6[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done

#iterative for seventh problems
for problem in ${problems_7[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_7[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size
		echo >> $file

		#append time file
		printTime $t_file $ITERATIVE $problem $size
	done
done

#recursive for seventh problems
for problem in ${problems_7[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	printAttempts $t_file $T_ATTEMPTS
		
	for size in ${sizes_7[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#append mem file
		printAttempts $file $M_ATTEMPTS
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size
		echo >> $file

		#append time file
		printTime $t_file $RECURSIVE $problem $size
	done
done