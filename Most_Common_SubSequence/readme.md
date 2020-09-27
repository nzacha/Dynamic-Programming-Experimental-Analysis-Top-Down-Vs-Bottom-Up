// TO USE VALGRIND MEMCHECK TOOL
valgrind ./a.out sequenceA_10.txt sequenceB_10.txt 1

// TO USE VALGRIND MEMCHECK TOOL WITH EXTRA CHECKS
valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./a.out sequenceA_10.txt sequenceB_10.txt 1

// TO VEIW DEBUG INFO
gcc -D DEBUG main.c

// TO PROFILE HEAP AND STACK USE:
valgrind --tool=massif --stacks=yes ./a.out Inputs/sequenceA_1_1000.txt Inputs/sequenceB_1_1000.txt 2

// TO EXTRACT HEAP USAGE:
ms_print massif.out.15918 | grep "(*B)" | cut -d " " -f2 | grep B | tr -d "(" | tr -d ")" | tr -d "B" | tr -d "," | sort -r | head -1
 
// TO EXTRACT MOST HEAP USAGE:
ms_print massif.out.16598 | grep '      ' |  tr -s " " | cut -d " " -f4 | grep -v time | tr -d "," | grep -o '[0-9]*' | sort -n -r | head -1

// TO EXTRACT MOST STACK USAGE:
ms_print massif.out.16598 | grep '      ' |  tr -s " " | cut -d " " -f7 | grep -v time | tr -d "," | grep -o '[0-9]*' | sort -n -r | head -1

//compile with debug
make CFLAGS=-DDEBUG

//to get heap
cat massif.out.8398 | grep mem_heap_B | tr -d "mem_heap_B=" | sort -n -r | head -1


//to get extra heap
cat massif.out.8398 | grep mem_heap_extra_B | tr -d "mem_heap_extra_B=" | sort -n -r | head -1

//to get max stack
cat massif.out.8398 | grep mem_stacks_B | tr -d "mem_stacks_B=" | sort -n -r | head -1

//example run
./a.out ../Inputs/sequenceA_0_100.txt ../Inputs/sequenceB_0_100.txt 1

Change Log
V_1: 
	> Top-Down and Bottom-Up approaches functional	
	1 - see below) >Data type used for Bottom-Up approach must be re-eximined (not optimal)
	2 - see below) >Data structure used for Top-Down must be re-examined (wasteful)

	Remarks:	As expected, a noticable speed advantage was detected in the Bottom-Up approach due to the recursive nature of the Top-Down algoritm. However, the difference in memory usage between the two algorithms is surpising, since the Bottom-Up approach requires O(NxN)b bytes of memory to store the solution where as the Top-Down approach requires much less.

	Considering optimizations for Bottom-Up approach: Store only two levels of the solution per stage. 

	1)	Array Type:
		-The array is of type Integer. Integers are 4 bytes long (up to 2^32 = 4,294,967,295).
		This means that for a problem of size A:60,000 and B:60,000, a total of 60,000 x 60,000 x 4 Bytes is allocated for the array containing the solution, which adds up to 13.411 GB of data. This may not be optimal since the solution may not require this big data types.

		-The array can be made of Chars to save space for a more optimized solution, this means the solution cant exceed 2^8 (255) which is not optimal since problems can reach such lengths relatively easy. 
	
		-If Short data type is used, solutions can be up to 2^16 letters long (65535) which seems optimal but may still not be enough. If we aim to 'max out' a 16 GB machine with a NxN array in regards to different data types:
			>for Integer: N must be about 65536
				in this example we observe that the numberical MAX of an Integer variable is 4,294,967,296
				which is far beyond the problem size (solution length CAN'T exceed the legnth of sequence A or B)
			>for Short: N must be about 92682
				in this example we observe that the numberical MAX of a Short variable is 65535 which is less than N, which may hint of a possibility for overflow if the solution length exceeds the limits of a Short variable
			>for Byte: N must be about 131072
				in this example we observe that the numberical MAX of a Byte/Char which is 255 is far below the Problem size, which will most likely hint to overflow, thus should be avoided.
		In conclusion: To increase efficiency the algorithm will be made capable of using smaller data types. More specificaly, The Solution will be held in a Short array but some checks will be necsessary to detect any overflows.

	2)	Top-Down Data Structure:
		-In this version of the algorithm, the Top-Down solution uses the same Data Structure as the Bottom-Up solution. This means that the NxN array is used to hold the values found during the recursive steps of the algorithm. As a result, the same memory allocation is required for both approaches. However during some preliminary tests it was discovered that this solution is very wasteful, since the Recursive solution only solves a fraction of the sub-problems solved by the Iterative approach. Thus a new Data Structure must be proposed to better fit the needs of the Recursive algorithm.

V_2:
	> Changed iterative array data type to Short
	> Added HashMap to recursive algorithm (instead of NxN array like in the iterative algotihm)

	Remarks:	The HashMap (array of linked list) is much less space efficient than the array, since every node requires 12 bytes of memory where as the array cell requires 2. Maybe an implementation of HashMap with array of arrays will be more benefitial

v_3:
	> 