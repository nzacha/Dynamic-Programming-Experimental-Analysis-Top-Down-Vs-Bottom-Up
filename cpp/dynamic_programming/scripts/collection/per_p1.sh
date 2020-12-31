#declare program arguments
sizes_1=(7500 15000 22500 30000 37500 45000 52500 60000)
problems_1=("mostCommonSubSequence")

ulimit -s unlimited

rm -f tmp.txt	

#iterative for first problems
: '
for problem in ${problems_1[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/iterative
				
	for size in ${sizes_1[@]}
	do
		for attempt in {1..3}
		do
			echo "per iterative ${problem} ${size} ${attempt}" > log.txt
			echo "Running iterative " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -iterative -q &
			pid=$!

			top -d 0.1 -bp ${pid} >> tmp.txt &
			top_pid=$!

			#wait for program end
			tail --pid=${pid} -f /dev/null
			#kill top_pid

			cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${probem}/iterative/per_${attemp}.txt

			rm tmp.txt
		done
	done
done
'

#recursive for first problems
for problem in ${problems_1[@]}
do
	mkdir mem_results/${problem}
	mkdir mem_results/${problem}/recursive			
	
	for size in ${sizes_1[@]}
	do
		for attempt in {1..3}
		do
			echo "per recursive ${problem} ${size} ${attempt}" > log.txt
			echo "Running recursive " ${problem} " size: ${size} x${attempt}"

			./executable.out ${problem} ${size} -recursive -q &
			pid=$!

			top -d 0.1 -bp ${pid} >> tmp.txt &
			top_pid=$!

			#wait for program end
			tail --pid=${pid} -f /dev/null
			#kill top_pid

			cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${problem}/recursive/per_${size}_${attempt}.txt

			rm tmp.txt
		done
	done
done