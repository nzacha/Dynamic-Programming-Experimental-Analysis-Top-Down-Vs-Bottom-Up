sizes=(10 100 200 500 1000 2000 5000 10000 20000 50000 80000 90000)
alphabets=(26 52)

for alphabet in ${alphabets[@]};
do
	for size in ${sizes[@]};
	do
		for attempt in {1..5};
		do
			touch Inputs/sequenceA_${alphabet}_${size}_${attempt}.txt
			touch Inputs/sequenceB_${alphabet}_${size}_${attempt}.txt
		done
	done
done