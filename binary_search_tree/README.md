# Binary Search Trees



A Binary Search Tree (BST) is a hierarchical data structure where each node has at most two children. For every node, all values in the left subtree are smaller than the node’s value, and all values in the right subtree are greater.



# Why Binary Search Trees?



Binary Search Trees enable searching and inserting elements in O(log n) time on average. Self-balancing variants such as AVL Trees and Red-Black Trees guarantee O(log n) time in the worst case by maintaining balance.



One might ask why BSTs are needed when binary search on a sorted array also achieves O(log n) search time. While binary search is efficient, inserting or deleting elements in a sorted array requires shifting elements to maintain order, resulting in O(n) time complexity.



Linked lists avoid shifting costs but do not support binary search due to the lack of random access, requiring O(n) time to search.



A Binary Search Tree addresses these limitations by maintaining ordered data while supporting efficient search, insertion, and deletion.



# Binary Search Tree Time Complexity



|Operation|Average Case|Worst Case|
|-|-|-|
|Search|O(log(n))|O(n)|
|Insert|O(log(n))|O(n)|
|Delete|O(log(n))|O(n)|



