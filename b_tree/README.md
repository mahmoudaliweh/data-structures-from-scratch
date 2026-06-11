B-Tree

What problem does this data structure solve?
The B-Tree was designed to solve the "I/O bottleneck" inherent in systems that handle massive amounts of data—amounts so large they cannot fit entirely into primary memory (RAM) and must reside on secondary storage (like HDDs or SSDs).

Reading or writing data to a disk is orders of magnitude slower than accessing RAM. The B-Tree minimizes disk accesses by structuring data into large blocks that match the storage system's block size, allowing the system to read or write thousands of keys in a single disk I/O operation.

What is this data structure?
A B-Tree is a self-balancing, m-way search tree (where m represents the maximum number of children a node can have). Unlike binary trees, B-Tree nodes are "fat"—they contain dozens, hundreds, or thousands of keys and pointers arranged in sorted order within a single node.


What is this data structure?
A B-Tree is a self-balancing, m-way search tree (where $m$ represents the maximum number of children a node can have). Unlike binary trees, B-Tree nodes are "fat"—they contain dozens, hundreds, or thousands of keys and pointers arranged in sorted order within a single node.

Where is it used?
Database Storage Engines: SQLite, Oracle, and old versions of MySQL (InnoDB uses B+ Trees, a close variant).

File Systems: NTFS (Windows), HFS+ (macOS), and ext4 (Linux) use variants of B-Trees to index file directories and metadata blocks.

Why is it preferred?
Because the cost of spinning a disk platter or routing flash memory blocks dominates execution time. If an operation takes 1,000 CPU cycles but requires 1 disk access, reducing disk accesses by even one level saves massive amounts of time.
It prevents thrashing—a catastrophic state where a system spends more time moving memory pages back and forth between disk and RAM than it does executing actual application work.

Time Complexity: Logarithmic 