# Algorithm
##### 1. Arbitrarily group the elements in pairs.
##### 2. Perform pairwise compairons, one for each pair and pick the larger element.
##### 3. Recursively sort the the (n/2) larger elements using merge-insertion.
##### 4. Insert at the start of the sequence S, the element that was paired with the first and smallest element of S.
##### 5. Insert the remaining (n/2) - 1 elements using binary search, with a specific ordering described below.

# Method
### pair-chain
Each element contains a pointer to another it is paired with, and the length of the pair-chain grows exponentially with powers of two, pair-chain-lookup is a procedure used to look through this pair-chain and find the pairing on any recursive depth. On depth 0 the length is R=1 and on 1 it is 2, 4 on 2 etc.. therefore lookup on a given depth will require R dereferences.
(insert pair-chain pic)
### binary insertion
Let C ( n ) be the function that returns the number of comparisons in the worst case when inserting into a sequence of n elements.
We have the relation
(insert binary-search relation pic)
### Insertion ordering
We use the observation above to minimize the number of comparisons needed for each insertion, consider the configuration
(insert configuration pic)
Left to right insertion gives us C ( 2 ) + C ( 4 ) = 2 + 3 = 5
(insert LTR insertion pic)
We can make C ( n ) the same for both b2 and b3, because
C ( 3 ) <==> C ( 3 ).
b2 and b3 are collectively called a group, groups are inserted in reverse order so that C ( n ) is uniform across the entire group.
(insert correct insertion pic)
[Knuth](https://warwick.ac.uk/fac/sci/dcs/teaching/material-archive/cs341/fj.pdf "Knuth") found a formula which takes the current group k and outputs the main chain start index
(insert knuth formula)
### M -> S mapping
M is the main chain array, while S is the sorted sequence, in the beginning M and S are equivalent, but insertion into S destroys the equivalence. To keep this equivalence, a tracker variable p is used for each element, if insertion happened before the element, its p is incremented by 1, and this p is added to the original index of the element in M, to find its current index in S.
(insert M->S mapping pic)