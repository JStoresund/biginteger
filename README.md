# BigInteger
Class made in order to be able to store virtually inifinitely high numbers.

The BigInt class store numbers in a string. As such, instead of the computer remembering the value of the stored number, it remembers the digits. Virtually all operators have been overloaded, in case anyone will actually use the class for anything. The class does not currently accept negative numbers, or decimal point numbers, but I might come back to this in the future.

In order to make a variable if the type, the syntax is (choose whichever you want):
- BigInt a{123};   //insert a long long (same as integer). Default value is 0
- BigInt a{"123"}; //insert a string. Necessary for values above 2^64-1
- BigInt b{a};     //insert another BigInt. 

It has to be noted that storing the digits instead of the actual number is an unconvenient way of storing a number; the first sometimes use more than double the amount of bytes than the latter (8*log(2) times more, with some slightly approximated math). 
I might come around to making a better class that optimizes storage. In that case using a vector<long long> would probably work, although I haven't thought through how all implementations would work. 
