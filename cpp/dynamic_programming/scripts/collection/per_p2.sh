#declare program arguments
sizes_2=(15000 30000 45000 60000 75000 90000 105000 120000 135000 150000)
args_2=(250 2500 25000)
problems_2=("knapsack")
methods=("iterative" "recursive")

ulimit -s unlimited

rm -f tmp.txt	

for problem in ${problems_2[@]}
do
	for method in ${methods[@]}
	do
	
		mkdir mem_results/${problem}
		mkdir mem_results/${problem}/${method}
					
		for size in ${sizes_2[@]}
		do
			for arg in ${args_2[@]}
			do
				for attempt in {1..3}
				do
					echo "per ${method} ${problem} ${size} ${arg} ${attempt}" > log.txt
					echo "Running ${method} " ${problem} " size: ${size} arg: ${arg} x${attempt}"

					./executable.out ${problem} ${size} ${arg} -${method} -q &
					pid=$!

					top -d 0.1 -bp ${pid} >> tmp.txt &
					top_pid=$!

					#wait for program end
					tail --pid=${pid} -f /dev/null
					#kill top_pid

					cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${problem}/${method}/per_${size}_${arg}_${attempt}.txt

					rm tmp.txt
				done
			done
		done
	done
done