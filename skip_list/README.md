# Skip List



Skip list is a dynamic probabilistic data structure that allows for fast search, insertion and deletion on average.

It's a probabilistic alternative to balanced binary search trees that is easier to implement as it doesn't require rotations.



# Why Skip List?



O(log n) expected time all operations without complex rebalancing like balanced trees.

It solves the problem of maintaining a sorted dynamic set efficiently.



Balanced trees (AVL, Red-Black) solve this but:

Hard to implement

Many rotations

Complex invariants



Skip lists achieve similar performance using randomization instead of strict rebalancing.



# Advantages



Much simpler than AVL / Red-Black

No rotations

Predictable average performance

Easy to implement correctly



# Disadvantages



Worse worst-case than balanced trees

More memory than BST (extra pointers)

Performance depends on randomness



# Time Complexity



|Operation|Excepted Time|Worst Time|
|-|-|-|
|Search|O(log n)|O(n)|
|Insert|O(log n)|O(n)|
|Delete|O(log n)|O(n)|



