## Why B-Trees?

B-Tree is a specialized self-balancing m-way search tree designed to optimize data access on a secondary memory where large amount of data resides.

On a hard disk (HDD) or solid-state drive (SSD), hardware controllers do not read data byte-by-byte or row-by-row. Storage media is physically formatted into chunks called **sectors** or **blocks** (typically 4KB in size).

When you want to read just a single integer or a tiny 50-byte record from a file, the operating system is forced to load the **entire 4KB block** containing that record into RAM.

And so B-Tree optimizes data access by storing the keys in some way to minimize disk access as much as possible while defining some rules that the structure of the B-Tree must follow.

## What is a B-Tree?

A B-Tree is a self-balancing, **m-way search tree** (where $m$ represents the maximum number of children a node can have). Unlike binary trees, B-Tree nodes are "fat"—they contain dozens, hundreds, or thousands of keys and pointers arranged in sorted order within a single node.

it optimizes for **minimal page reads (disk I/O operations)**. By maximizing the branching factor (the number of children per node), it keeps the overall tree height remarkably flat.

## Properties of a B-Tree

1) All leaf nodes are at the same level, i.e. they have the same depth.
2) The keys of each node of a B-Tree should be stored in the ascending order.
3) All non-leaf nodes (except root node) should have at least `m/2` children.
4) All nodes (except root node) should have at least `m/2 - 1` keys.

## Where is it used?

- **Database Storage Engines:** SQLite, Oracle, and old versions of MySQL (InnoDB uses B+ Trees, a close variant).
    
- **File Systems:** NTFS (Windows), HFS+ (macOS), and ext4 (Linux) use variants of B-Trees to index file directories and metadata blocks.

## Why is it preferred?

Because the cost of spinning a disk platter or routing flash memory blocks dominates execution time. If an operation takes 1,000 CPU cycles but requires 1 disk access, reducing disk accesses by even one level saves massive amounts of time.

It prevents **thrashing**—a catastrophic state where a system spends more time moving memory pages back and forth between disk and RAM than it does executing actual application work.

## Time Complexity

| Operation    | Worst-Case Time | Average-Case Time | Space Impact              |
| :----------- | :-------------- | :---------------- | :------------------------ |
| **Search**   | $O(\log_m N)$   | $O(\log_m N)$     | $O(1)$ auxiliary          |
| **Insert**   | $O(m \log_m N)$ | $O(m \log_m N)$   | $O(\log_m N)$ stack space |
| **Delete**   | $O(m \log_m N)$ | $O(m \log_m N)$   | $O(\log_m N)$ stack space |
| **Update**   | $O(\log_m N)$   | $O(\log_m N)$     | $O(1)$ auxiliary          |
| **Traverse** | $O(N)$          | $O(N)$            | $O(\log_m N)$ stack space |

*Where **m** represents the order of the B-Tree (maximum number of children per node) and **N** represents the total number of keys currently stored in the tree.*

## Comments

#### Comment 1
The main reason for the existence of B-Trees is to better utilize the behavior of devices that read and write large chunks of data. Two properties are important to make the B-Tree better than binary trees when data has to be stored on disk:

- Access to disk is really slow (compared to memory or caches, random access to data on disk is orders of magnitude slower); and
- Every single read causes a whole sector to be loaded from the drive - assuming a sector size of 4K, this means 1000 integers, or tens of some larger objects you're storing.

Hence, we can use the pros of the second fact, while also minimizing the cons - i.e. number of disk accesses.

So, instead of just storing a single number in every node that tells us if we should continue to the left or to the right, we can create a bigger index that tells us if we should continue to the first 1/100, to the second or to the 99-th (imagine books in a library sorted by their first letter, then by the second, and so on). As long as all this data fits on a single sector, it will be loaded anyway, so we might as well use it completely.

This results in roughly logb N lookups, where N is the number of records. This number, while asymptotically the same as log2 N, is actually a few times smaller with large enough N and b - and since we're talking about storing data to disk for use in databases, etc., the amount of data is usually large enough to justify this.

#### Comment 2
RB trees are binary search trees. B trees can have more than two child nodes. In fact, the number of child nodes is variable.

So, you can vary the number of child nodes such that the size of a node is always a multiple of the filesystem block size. This reduces waste when reading: you cannot read less than one block anyway, you always have to read the full block, so you might just as well fill it up with useful data. Increasing the number of child nodes will also _decrease_ the depth of the tree, thus decreasing the average number of "hops" (i.e. disk reads), which again increases performance.

Remember: B trees are usually used to store data structures which are orders of magnitude _larger_ than memory, whereas RB trees are typically used to store data structures which are orders of magnitude _smaller_ than memory. In fact, B trees are specifically designed as an on-disk data structure as opposed to an in-memory data structure.

#### My Own Thoughts

So basically, when you have massive amount of data that can't fit in main memory and you are forced to store it on a secondary memory device where access costs are expensive keeping in mind that no matter how small the data is you need to access even if it's just one byte, you have to read the whole block/page from the secondary memory into the main memory, and you still want fast search/insertion/deletion, B-Tree shines.

So

