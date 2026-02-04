Array is a fundamental linear data structure that stores elements of the same data type contiguously and since elements are of the same data type you have fast random access in O(1) constant time as you know the size of the data type and you have the starting address of the array so with simple calculation you can calculate the address of the i-th element. For example if the starting address is 0000 and the data type size is 2 bytes, and you want to access the 5th element, you can calculate its address by 0000 + (4 \* 2 bytes) = 0008.



Advantages:



Fast access to elements

Memory efficient

Cache-friendly traversal.

CPU loads memory in cache lines (e.g., 64 bytes at a time).

When you access arr\[0], the CPU often loads arr\[0] … arr\[15] into cache in one go (if int = 4 bytes, that’s 16 elements).

Then accessing arr\[1], arr\[2]… is already in cache → extremely fast.





Disadvantages:



Fixed size

Insertion/Deletion in O(n) time. Since it's static and fixed you won't be able to insert into it directly, you will need to create new array and move elements or shift elements.





Applications:



Used to implement other data structures like vectors which are basically dynamic arrays, stacks and queues.

Matrix/Grid representations

Buffers in real-time systems



When to use arrays?



You need fast random access.

You know or can approximate size in advance.



When not to use it?



You want fast insertion/deletion

Variable size



Operations' time complexity:



Access O(1)

Search (unsorted) O(n)

Search (sorted) O(log(n))

Insertion at end O(1) (if there is space), O(n) (if full)

Insertion at middle/beginning O(n)

Deletion at end O(1)

Deletion at middle/start O(n)

Traversal O(n) 



