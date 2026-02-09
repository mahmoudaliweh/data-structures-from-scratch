# AVL Trees



AVL tree is a self-balancing binary search tree where the difference between heights of left and right subtrees for any node can't be more than one.



# Why AVL Trees?



A normal BST can degrade into a linked list, AVL Trees  guarantee logarithmic height so operations stay fast.

AVL trees maintain tree balance by doing rotations after insertions/deletions to guarantee overall worst case time complexity O(log(n)). 



# Advantages



Strict height guarantee

Fast worst-case lookups

Great for read-heavy systems



# Disadvantages



Although faster in lookups than Red-Black Trees, AVL Trees might incur slightly more overhead on insertions and deletions due to stricter balancing requirements. As a result, Red-Black Trees are more common in standard libraries like TreeMap or TreeSet in Java or map in C++ STL.

More complex implementation

Slightly slower inserts/deletes



# When to use AVL



Lookup-heavy workloads

Ordered data required

Predictability > raw insertion speed



# AVL Tree Operations' Time Complexity



|Operation|Time complexity|
|-|-|
|Insert/Delete/Search|O(log(n))|



