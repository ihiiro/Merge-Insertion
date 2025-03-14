# Algorithm
##### 1. Arbitrarily group the elements in pairs.
##### 2. Perform pairwise compairons, one for each pair and pick the larger element.
##### 3. Recursively sort the the (n/2) larger elements using merge-insertion.
##### 4. Insert at the start of the sequence S, the element that was paired with the first and smallest element of S.
##### 5. Insert the remaining (n/2) - 1 elements using binary search, with a specific ordering described below.

# Method
### pair-chain
Each element contains a pointer to another it is paired with, and the length of the pair-chain grows exponentially with powers of two, pair-chain-lookup is a procedure used to look through this pair-chain and find the pairing on any recursive depth. On depth 0 the length is R=1 and on 1 it is 2, 4 on 2 etc.. therefore lookup on a given depth will require R dereferences.
![pair chain](https://github.com/ihiiro/Merge-Insertion/blob/master/pair_chain.png "pair chain")
### binary insertion
Let C ( n ) be the function that returns the number of comparisons in the worst case when inserting into a sequence of n elements.
We have the relation
![binary search relation](https://github.com/ihiiro/Merge-Insertion/blob/master/equivalence.png "binary search relation")
### Insertion ordering
We use the observation above to minimize the number of comparisons needed for each insertion, consider the configuration
![Configuration](https://github.com/ihiiro/Merge-Insertion/blob/master/configuration.png "configuration")
Left to right insertion gives us C ( 2 ) + C ( 4 ) = 2 + 3 = 5
![wrong insertion](https://github.com/ihiiro/Merge-Insertion/blob/master/wrong_insertion.png "wrong insertion")
We can make C ( n ) the same for both b2 and b3, because
C ( 3 ) <==> C ( 3 ).
b2 and b3 are collectively called a group, groups are inserted in reverse order so that C ( n ) is uniform across the entire group.
![correct insertion](https://github.com/ihiiro/Merge-Insertion/blob/master/correct_insertion.png "correct insertion")
[Knuth](https://warwick.ac.uk/fac/sci/dcs/teaching/material-archive/cs341/fj.pdf "Knuth") found a formula which takes the current group k and outputs the main chain start index, inserting an element from group k into S will require at most k comparisons, provided insertion starts at index Tk in the main chain and continues backwards toward the group's end.
![knuth's formula](https://github.com/ihiiro/Merge-Insertion/blob/master/formula.png "knuth's formula")
### M -> S mapping
M is the main chain array while S is the sorted sequence, in the beginning of a recursive depth M and S are equivalent, but insertion into S destroys the equivalence. To keep this equivalence, a tracker variable p is used for each element, if insertion happened before the element, its p is incremented by 1 in M, and this p is added to the original index of the element in M to find its current index in S.
This is necessary so that binary search happens up to but not including "an".
![M->S mapping](https://github.com/ihiiro/Merge-Insertion/blob/master/mapping.png "M->S mapping")