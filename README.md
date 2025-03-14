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
