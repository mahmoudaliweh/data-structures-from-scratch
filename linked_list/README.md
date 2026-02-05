# Linked list



A linked list is a sequence of nodes, where each node contains data and a reference to the next node.

The elements are connected via pointers and aren't necessary contagious physically in memory.



# Why linked list?



A linked list doesn't have a fixed size like arrays, it also offers O(1) constant time insertions/deletion at the begin.

Insertion/Deletion anywhere is O(1) assuming you already know the node address.

It prevents memory re-allocation since Its size isn't fixed internally.



# Disadvantages



No random access.

Extra memory for holding pointers.

Cache-unfriendly since elements aren't necessary contagious.



# Applications



Used to implement stack and queue data structures.

OS process scheduling as it uses queues that are basically linked lists thus you can add processes to the queue and remove them from the queue in O(1) time, unlike with arrays you might need to do some shifting. 



# Operations' Time Complexity



|Operation|Time Complexity|
|-|-|
|Insert/Delete (head)|O(1)|
|Insert/Delete (tail/middle)|O(n)|
|Access|O(n)|



