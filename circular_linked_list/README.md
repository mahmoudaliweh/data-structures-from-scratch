# Circular linked list



It's like singly linked list except that the last node points to the first node, and for doubly linked list the last node's next pointer points to the first node and the first node's previous pointer points to the last node.



# Why circular linked list?



Useful for tasks that require continuous cycling through elements without restarting traversal

Insertion at beginning or end is O(1)



# Applications



Media players (looped playlists)

Games (turn management)



# Operations' Time Complexity



|Operation|Time complexity|
|-|-|
|Insertion/Deletion at head/tail|O(1)|
|Search|O(n)|
|Delete by value|O(n)|
|Rotate|O(1)|
|Insert at tail (if no tail pointer)|O(n)|



