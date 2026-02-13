# Red-Back Tree Insertion/Deletion Fixes



### Red-Black Tree Properties 



1. There are no adjacent red nodes.
2. The number of black nodes from the root to every leaf node is the same.



### We always insert/delete at the leaf therefore:



1. Insertion might break property 1.

2\. Deletion might break the property 2.

We choose the color of the node to be inserted to be red because fixing property 1 is easier than fixing property 2.



### Insertion Fixes:



The objective of the fix is to somehow separate the two adjacent red nodes while maintaining property 2 using rotations.

as you know rotations preserve the BST property of the tree so we shouldn't worry about that.



Case 1:

Node is the root node, just color it black.



Case 2:

Node's parent is black, no fixes needed



Case 3:

Node's parent is red, which implies that grandparent exists and it is black and if uncle exists it must be red otherwise property 2 was violated before insertion which isn't allowed to happen.



If uncle doesn't even exist, this means the node is red, its parent is red, its grandparent is black. We can manipulate the subtree using rotations and recoloring (its current root is the grandparent) to somehow separate the adjacent red nodes while keeping the root of the subtree black to not violate property 2.



If uncle exists, we know that its color is red, we could color the grandparent red and its children black and by that we didn't break property 2 and we fixed the tree but the thing is coloring the grandparent red might break a property, so we recursively apply the fix algorithm on the grandparent.



### Deletion Fixes:



The objective of the fix is to somehow increase the number of black nodes in the path where we deleted the node to be deleted using rotations and re-coloring.



Base Cases:



If either parent, or uncle, or uncle's right child, or uncle's left child is a red node, we could somehow manipulate the tree to bring one of the nodes to the path where a black node is needed, and color it to black.



The recursive case:



All nodes are already black so we will decrease the number of black nodes on the opposite side of the path to be fixed, and propagate the break upwards (parent node) then re-check cases.



The point of this document is to remind myself of the big picture and the objective of fixes rather than trying to memorize cases so that if i forget some case I can still determine how to fix the tree.



