This is a small program to analyze the running time of different sorting algorithms.
To open run the program :-

1. Open sort.cpp
2. You can change the program based on the reading the commented portions of the code.
   By default the program will analyze the performance of insertion sort, merge sort, quick sort, randomized quick sort and heap sort, mixed merge sort, mixed randomized quick sort. The size of input array is varied from 10 - 300 with leaps of 10. The array is filled with random integers for each sort round.
3. Compile the C++ program and then Run it.
4. Open gnuplot and type in the following lines -
   
   cd 'E:\Programs\Sorting\Sorting Analysis'
   (the path name must be inside the quotes)

   plot 'insertion.dat' u 1:2 with lines, 'quick.dat' u 1:2 with lines, 'merge.dat' u 1:2 with lines, 'randomquick.dat' u 1:2 with lines, 'heap.dat' u 1:2 with lines, 'mixedmerge.dat' u 1:2 with lines, 'mixedrandomquick.dat' u 1:2 with lines
   (add other sort .dat files if the code is changed)

5. A plot of running time of sorting will appear for you to analyze.
   The x axis represents the size of input data and the y axis represents the running time in microseconds.