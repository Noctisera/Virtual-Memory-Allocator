# README Virtual Memory Allocator

## Description
This is a small simulator written in 'C' that mimics (more or less) how memory allocation works on computers.


## What does it do?
It has multiple commands that the user can use to simulate a virtual allocator.

1.	ALLOC_ARENA <size_of_arena> : Creates the space where all the memory will be alocated.
2.	DEALLOC_ARENA : Frees the arena and all memory allocated in it.
3.	ALLOC_BLOCK <arena_address> <size_of_arena> : Allocates a block at the chosen address with the chosen size. Inside each block are 1 or more miniblocks where the data will be written. If 2 blocks are right next to eachother, they merge and the their miniblocks will be in the same new block.
4.	FREE_BLOCK <arena_address> : Frees the miniblock with the chosen starting address.
6.	WRITE <arena_address> <size_of_write> <data_to_write> : Writes data at the chosen address. The introduced data must have its length equal to the size introduced before it.
5.	READ <arena_address> <size_of_read> : Reads the data starting from the chosen address and prints it in the console. The printed data will have its size equal to the the size introduced.
7.	PMAP : Prints information about the arena and all the blocks allocated in it.
8.	MPROTECT <arena_address> <permissions_to_give> : Changes the permission of a miniblock. When a miniblock is alloced, it will automatically gain permission to read and write. Instead of <permissions>, put one or more of the following inputs: PROT_NONE | PROT_READ | PROT_WRITE | PROT_EXEC. To write or read in a miniblock, all the miniblocks from his block must have their respective permissions valid.

## Code structure and implementation
Linked lists were used to implement the memory allocator. The arena is a big struct that stores information about it's contents like 'the number of blocks'/'the number of miniblocks'/'remaining data'/etc and has a pointer to the list of blocks.

The blocks are always in the order of their starting address and each points to their respective list of miniblocks.

The miniblocks can store data inside their buffer and start with rw- permissions when they are first allocated.

Adding or removing a miniblock also changes the block it is located in. The starting/end addresses and the 'head' pointer (the one that points to the list of miniblocks) in the block must be changed accordingly. If a miniblocks located in the middle of a list of miniblocks is removed, then one more block is created and the 2 split lists become the head of their respective blocks.

Writing data in a miniblock allocs it's full size in rw_buffer (instead of the necesarry size for the text) to make writing multiple texts in different zones of the same miniblock easier for the poor programmer to implement. The used zones in rw_buffer will have their respective text. The other unusued zones will have the ASCII value 0 (NULL) by using calloc.

Reading data in a miniblock will only read zones in rw_buffer with written text in them and stop otherwise if it meets the ASCII value 0.

## Errors
Whenever something wrong happens in the program, an error will appear with a suggestive name that indicates what the problem was.

### What could have been done better
Using a double linked list instead of a simple linked list to help improve on time in alloc_block by a bit.

Implementing a get_miniblock() function to make the code look cleaner in some parts.



Note: ALWAYS START THE PROGRAM WITH ALLOC_ARENA AND END IT WITH DEALLOC_ARENA. DOING OTHERWISE WILL MOST LIKELY RESULT IN A CRASH/SEGMENTATION FAULT.
