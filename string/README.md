# Strings



String is basically an array of characters stored contiguously in memory except that it's dynamic and offers common operations.



# Why Strings?



Strings are aware of their length and encoding while arrays aren't, they also offer common operations like searching and concatenating.

Strings are dynamic, you can change their size and manipulate them.

Strings do bound checking while arrays don't.



# Char Array Problems



A scan operation on your char array stops when it encounters the null character '\\0', so whenever you initialize a char array using an initializer list, you should remember to end it with a null character like that:

char myText\[] = {'a', 'b', '\\0'};

otherwise a memory overread occurs as it will keep reading from the memory until it encounters a null character.



Char arrays aren't aware of their length nor encoding, they don't know if you initialized them with UTF-8 or ASCI characters, they always assume it's ASCI.



Char arrays have buffer overflow problem as they don't know when to stop reading from the user.



# Immutable String Operations' Time Complexity



|Operation|Time Complexity|Explanation|
|-|-|-|
|length|O(1)|Strings store their length|
|Index|O(1) or O(n)|O(1) if every character takes the same number of bytes.<br />O(n) if it's a variable length world like UTF-8 as it uses variables bytes for characters (1-4 bytes).  |
|Traverse|O(n)||
|Compare|O(n)||
|Insert/Delete|O(n)||
|Search|O(n \* m)||
|Substring|O(n)||





.

# Mutable String Operations' Time Complexity



|Operation|Time Complexity|Explanation|
|-|-|-|
|length|O(1)|Strings store their length|
|Index|O(1)|This is byte-level indexing|
|Traverse|O(n)||
|Compare|O(n)||
|Append character|Amortized O(1)|Same concept as dynamic arrays|
|Search|O(n \* m)|Can optimize to O(n + m)|
|Substring|O(n)||
|Append string|Amortized O(m)||
|Delete|O(1) at end, O(n) at middle or beginning||







