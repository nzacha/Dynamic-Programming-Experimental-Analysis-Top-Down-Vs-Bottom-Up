#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000 62500 65000 67500)
problems_1=("dijkstra" "independentSets" "knapsack")

sizes_2=(7500 15000 22500 30000 37500 45000 52500 60000 67500 75000 82500 85000 87500 90000)
problems_2=("allPairShortestPath" "chainMatrixMultiplication")

#iterative for first problems
for problem in ${problems_1[@]}
do
	rm i_${problem}.txt
	touch i_${problem}.txt

	for size in ${sizes_1[@]}
	do
		cat mem_results/${problem}/iterative/extract_${size}_heap.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
		cat mem_results/${problem}/iterative/extract_${size}_hextra.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
		cat mem_results/${problem}/iterative/extract_${size}_stack.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
	done
done

#recursive for first problems
for problem in ${problems_1[@]}
do
	rm r_${problem}.txt
	touch r_${problem}.txt
	
	for size in ${sizes_1[@]}
	do
		cat mem_results/${problem}/recursive/extract_${size}_heap.txt >> r_${problem}.txt
		echo "," >>  r_${problem}.txt
		cat mem_results/${problem}/recursive/extract_${size}_hextra.txt	>> r_${problem}.txt
		echo "," >>  r_${problem}.txt
		cat mem_results/${problem}/recursive/extract_${size}_stack.txt >> r_${problem}.txt
		echo "," >>  r_${problem}.txt
	done
done

#iterative for second problems
for problem in ${problems_2[@]}
do
	rm i_${problem}.txt
	touch i_${problem}.txt

	for size in ${sizes_1[@]}
	do
		cat mem_results/${problem}/iterative/extract_${size}_heap.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
		cat mem_results/${problem}/iterative/extract_${size}_hextra.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
		cat mem_results/${problem}/iterative/extract_${size}_stack.txt >> i_${problem}.txt
		echo "," >>  i_${problem}.txt
	done
done

#recursive for second problems
for problem in ${problems_2[@]}
do
	rm r_${problem}.txt
	touch r_${problem}.txt
	
	for size in ${sizes_1[@]}
	do
		cat mem_results/${problem}/recursive/extract_${size}_heap.txt >> r_${problem}.txt
		echo "," >>  r_${problem}.txt
		cat mem_results/${problem}/recursive/extract_${size}_hextra.txt	>> r_${problem}.txt
		echo "," >>  r_${problem}.txt
		cat mem_results/${problem}/recursive/extract_${size}_stack.txt >> r_${problem}.txt
		echo "," >>  r_${problem}.txt
	done
done

#time iterative first problems
for problem in ${problems_1[@]}
do				
	for size in ${sizes_1[@]}
	do
		cat time_results/iterative/
	done
done

#time recursive first problems
for problem in ${problems_1[@]}
do
	for size in ${sizes_1[@]}
	do
		cat time_results/${problem}/recursive		
	done
done

#time iterative second problems
for problem in ${problems_2[@]}
do
	for size in ${sizes_2[@]}
	do
		cat time_results/iterative/
	done
done

#time recursive second problems
for problem in ${problems_2[@]}
do
	for size in ${sizes_2[@]}
	do
		cat time_results/${problem}/recursive		
	done
done