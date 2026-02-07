# Hash Table



A hash table's primary objective is to be able search/insert in O(1) constant time, it achieves this by mapping keys to indices in an array (Hash table) using a hash function that its primary goal is to uniquely map every unique key to a unique index to minimize collisions as much as possible.

A collision happens when two different keys map to the same index.

A good hash function shouldn't map two different keys to the same index, it also shouldn't have high time complexity, because the only reason we are hashing is to minimize search/insert time complexity.

A collision is likely to happen if there are lots of keys stored relatively to the total number of keys that can be stored, we will call that the load factor. For example if your array can store 100 keys, the more keys you insert, the closer you get to 100, the more likely a collision will occur unless your hashing function is perfect.

So a way to minimize collision is to maintain a small load factor.



# Why Hash Tables?



Hash Tables provide constant time search, insert and delete operations on average.



# Key Properties of Hash Functions



Deterministic: A hash function must consistently produce the same output (index) for the same input (key)

Efficiency: A hash function should be able to process input quickly

Uniformity: A hash function should distribute the hash values uniformly across the output space to avoid clustering

Collision Resistance: It should be difficult to find two different inputs that produce the same output (hash value)

Avalanche Effect: A small change in the input should produce a significantly different hash value



# Collision Resolution Techniques



## Open Addressing:



All the elements are stored in the hash table itself.

Collisions are handles by looking for the next empty space in the table.

There are various ways to use this approach, including double hashing, linear probing and quadratic probing.

Linear probing handles collisions by finding the next empty slot. 

Disadvantage of linear probing is primary clustering where long chains of occupied slots build up causing long lookup time.



## Separate Channing:



Collisions are handled by making each cell in the hash table points to a linked list of records that have the same hash value, chaining is simple but requires additional memory outside the table



## Rehashing:



Rehashing is the process of increasing the size of the hash table and redistributing the elements based on their new hash value, it's done to prevent collisions by a high load factor.

Rehashing is done by checking the load factor every time a new entry is inserted into the hash table, if the load factor becomes greater than the pre-defined value then rehash.

For rehash, make a new array of double the previous size and make it the new array, then traverse the elements in the old array to insert them into the new array.



# Types of Hash Functions



## Division Method

The division method involves dividing the key by a prime number and using the remainder as the hash value.



##### Advantages:

Simple to implement

Works well when you divide by a prime number



##### Disadvantages:

Poor distribution if the prime number isn't chosen wisely



## Multiplication Method

A constant between 0 and 1 is multiplied by the key, the fractional part of the product is then multiplied by a number to get the hash value.



##### Advantages:

Less sensitive to the chosen multiplication number 



##### Disadvantages:

More complex than division method



## Mid-Square Method

The key is squared and the middle digits of the result are taken as the hash value



##### Advantages:

Produces good distribution of hash values



##### Disadvantages:

May require more computational effort



## Folding Method

Divide the key into equal parts, sum the parts then take the modulo with respect to some number m.



##### Advantages:

Simple and easy to implement



##### Disadvantages:

Depends on the choice of the partitioning scheme



## Cryptographic Hash Functions

They are designed to be secure and are used in cryptography. Examples include MD5, SHA-1, and SHA-256



##### Characteristics:

Pre-image resistance

Second pre-image resistance

Collision resistance



##### Advantages:

High Security



##### Disadvantages:

Computationally intensive.



## Perfect Hashing



## Universal Hashing



Pre-image resistance is not being able to know the key using the hash value, this is important if for example you are storing passwords, and the password is the key.





# Advantages of Hash Tables



Extremely fast lookups



# Disadvantages of Hash Tables



No ordering

Worst-case O(n)

Memory overhead

Hash function quality matters



# When to use it?



Lookup-heavy workloads

Indexing

Counting / grouping



# When not to use it?



Ordered traversal required

Range queries

Memory-constrained environments



# Applications



Database indexes

Caches





















