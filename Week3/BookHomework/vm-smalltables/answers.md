### Q1

still only one register to store the root page directory, no matter how many levels of table

### Q2

Lets take the example of seed 0, virtual address 611c:

611c = 11000 01000 11100

* 1st memory reference: 11000 (24) in the page directory (108), which results in a1 (10100001)  
* this means the page is valid (1), and it is located in 0100001 = 33  
* 2nd memory reference: 01000 (8) in page 33, which results in b5 (10110101)  
* this means the page is valid (1), and it is located in 0110101 = 53  
* 3rd memory reference: 11100 (28) in page 53, which results in 08 (00001000)