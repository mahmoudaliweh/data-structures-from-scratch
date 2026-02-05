# Doubly linked list



It's just like singly linked list except that each node contains a pointer to its previous node, in linked list each node contains a pointer to the next node only.



# Why doubly linked list?



It solves efficient insertion and deletion as it makes insertion/deletion at both ends and any known position happens in O(1) constant time unlike with singly linked list, you can only insert at the begin.

It allows for forward and backward traversal.



# Disadvantages



Extra memory (2 pointers per node)

Cache-unfriendly since nodes aren't contagious physically in memory.



# Operations' Time Complexity



|Operation|Time complexity |
|-|-|
|Insert (head/tail/known position)|O(1)|
|Delete (known node position)|O(1)|
|Search|O(n)|
|Access (Sequential)|O(n)|



