# Matrix-Multiplication
Implementation of 4 different Matrix-multiplication algorithms, 
>>>schoolbook/divide_and_conquer/strassen/optimized strassen<<<

![graph](https://user-images.githubusercontent.com/61370901/80899513-e4dd6680-8d4b-11ea-98c6-3b47c23e93bf.png)

Schoolbook, divide_and_conquer, strassen are implemented the way textbook requires.

This is how I optimized strassen algorithm. 

<Implementation + Optimization>
I thought dividing matrix into size 1 was inefficient since the overhead is big in the Strassen algorithm. I thought the operation of the matrix would be faster with the Schoolbook algorithm when the matrix was divided into small enough matrix. Accordingly, the conditional statement if(size==1) was replaced with if(size<=32). The array size below 32 was not called recursively but was calculated and returned immediately. 

The matrix size 32 was determined through the test run. I put 4, 16, 32, 64 as a candidate for the number to be x in the statement if(size<=x). I found out that the processing time was reduced at 32 and then increased back again from 64. In my environment, 32 was the best value for multiplication rather than a recursive call. 

The O(n3) operation from size 32 was also optimized. The schoolbook algorithm’s matrix multiplication is done by IJK method. For each operation, matrix B accesses the elements of the next row. This occurs cache miss since the array is stored in the order of row0, row1, row2 in memory. So I chose KIJ method which accesses the elements in the order of columns. Cache hit rate can be increased and performance is expected to be improved.
