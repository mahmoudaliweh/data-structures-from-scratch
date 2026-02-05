# Dynamic Arrays



Dynamic arrays are just like static arrays except that they resize themselves automatically.



# Why Dynamic Arrays?



Append operation happens in O(1) amortized time.



# Advantages



Fast random access.

Cache-friendly.

Fast append.



# Disadvantages



Slow middle insertion/deletion

Resize spikes



# When to use?



When size is unknown or changes.

Append-heavy workload.



# Operations' Time Complexity Comparison



|Operation|Static Array|Dynamic Array|
|-|-|-|
|Random Access |O(1)|O(1)|
|Append|O(n)|O(1) amortized|
|Insert|O(n)|O(n)|
|Delete at end|O(1)|O(1)|
|Delete at begin/end|O(n)|O(n)|





