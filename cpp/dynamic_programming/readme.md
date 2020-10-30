to compile for production:
	g++ -std=c++11 -pthread runner.cpp -o executable.out

to run with valgrind:
	g++ -g -std=c++11 -pthread runner.cpp -o executable.out

to log process profile data into file: 
	top -b -p 'pid' > cpu.log
	
to run massif profiler
	valgrind --tool=massif --massif-out-file=massif.txt --stacks=yes ./executable.out

tp extract max heap usage
	cat massif.txt | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1 > massif_extract.txt	

to extract extra heap usage
	cat massif.txt | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1 >> massif_extract.txt;	

to etract stack usage
cat massif.txt | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1 >> massif_extract.txt;	
