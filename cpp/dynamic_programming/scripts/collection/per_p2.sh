#declare program arguments
sizes_2=(10000 20000 30000 40000 50000 60000 70000 80000)
problems_2=("chainMatrixMultiplication")
methods=("recursive" "iterative")

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
			for attempt in {1..3}
			do
				echo "per ${method} ${problem} ${size} ${attempt}" > log.txt
				echo "Running ${method} " ${problem} " size: ${size} x${attempt}"

				./executable.out ${problem} ${size} -${method} -q &
				pid=$!

				top -d 0.1 -bp ${pid} >> tmp.txt &
				top_pid=$!

				#wait for program end
				tail --pid=${pid} -f /dev/null
				#kill top_pid

				cat tmp.txt | grep ${pid} | tr -s ' ' | cut -d ' ' -f11 > mem_results/${problem}/${method}/per_${size}_${attempt}.txt

				rm tmp.txt
			done
		done
	done
done