***********************************************
UCSD Extension 2022Fall

167113: Data Structures and Algorithms in C/C++
Implementation 2.1 Singly Linked List 

Cheng Fei
***********************************************



Linked Lists:

Introduction:
One of the most fundamental data structures is Elements linked together in a specific order 
Advantages vs. arrays
o O(1) inserts (arrays have O(n))
o O(1) deletes (arrays have O(n))
o Dynamically sized (arrays require # elems to be known before array created)
o Do not require contiguous memory
Disadvantages vs. arrays
o O(n) random access (arrays have O(1))
o Uses additional memory linking each element to next

Definition:
Head: Pointer to first element in list 
Tail: Pointer to last element in list 
Singly-linked lists:
o Each element links to next element
o Can be traversed forward only 
Doubly-linked lists:
o Each element links to next and previous element
o Can be traversed forward and backward 
Circular lists:
o List that wraps around on itself
o Has no beginning or end
o Can be implemented using a singly-linked or doubly-linked list