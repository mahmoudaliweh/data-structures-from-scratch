# Heap



Heap is a complete binary tree where every node's key is less than its parent's key for max heap and the opposite for min heap.



# Why Heap?



Why Heap if AVL Tree exists?



It allows you to peek min/max key in O(1).

Extract min/max key in O(log(n)).

It has a simpler structure than AVL since it's stored in an array.

Cache-locaility as it's implemented as an array so the memory cells are contagious.

Heap has better constants than AVL since it doesn't perform rotations.

Heap is specialized for extracting min/max keys where AVL is for search.

Heap is implemented as an array as it is a complete binary tree.



# When to use Heap?



If your workload is finding the most important thing next.



# Applications



Graph Algorithms

Priority Queue Implementation

Heapsort in O(n log n)

Job scheduling in OS

Lossless Compression Algorithms such as Huffman coding .

# 

# Time Complexity



|Operation|Heap|AVL Tree|
|-|-|-|
|Peek min/max|O(1)|O(log n)|
|Insert|O(log n)|O(log n)|
|Delete min/max|O(log n)|O(log n)|
|Search|O(n)|O(log n)|

# 



Notes



“Better constants” means:

Fewer instructions and simpler operations inside O(log n).



“Better cache locality” means:

Data stored contiguously → fewer cache misses → faster.



A binary heap is almost always:

Implemented as an array.

No explicit nodes.

No pointer-based tree.





