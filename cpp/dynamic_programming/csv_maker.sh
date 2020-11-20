#!/bin/bash

#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000 62500 65000 67500)
problems_1=("dijkstra" "independentSets" "knapsack")

sizes_2=(7500 15000 22500 30000 37500 45000 52500 60000 67500 75000 82500 85000 87500 90000)
problems_2=("allPairShortestPath" "chainMatrixMultiplication")

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
	for (( i=1; i<=$M_ATTEMPTS; i++))
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

function printTime{
	printf "Time," >> $1
	for (( i=1; i<=$T_ATTEMPTS; i++))
	do
		printf "," >> $1
	done
	echo >> $1
}

#iterative for first problems
for problem in ${problems_1[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv

	for size in ${sizes_1[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#create attempts tables
		printAttempts $file
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size

		echo >> $file
	done
done

#recursive for first problems
for problem in ${problems_2[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv

	for size in ${sizes_2[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#create attempts tables
		printAttempts $file
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size

		echo >> $file
	done
done


#iterative for second problems
for problem in ${problems_1[@]}
do
	file=data/mem/i_${problem}.csv
	t_file=data/time/i_${problem}.csv
	
	for size in ${sizes_1[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#create attempts tables
		printAttempts $file
		printHeap $file $problem $ITERATIVE $size
		printExtraHeap $file $problem $ITERATIVE $size
		printStack $file $problem $ITERATIVE $size

		echo >> $file
	done
done

#recursive for second problems
for problem in ${problems_2[@]}
do
	file=data/mem/r_${problem}.csv
	t_file=data/time/r_${problem}.csv
	
	for size in ${sizes_2[@]}
	do
		#print size
		echo "Size,$size" >> $file

		#create attempts tables
		printAttempts $file
		printHeap $file $problem $RECURSIVE $size
		printExtraHeap $file $problem $RECURSIVE $size
		printStack $file $problem $RECURSIVE $size

		echo >> $file
	done
done