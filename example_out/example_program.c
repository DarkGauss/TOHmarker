// C Program for Iterative Tower of Hanoi
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_DISKS 2
#define NUM_TOP_DISK_ERRORS 0
#define NUM_BIG_DEST_ERRORS 0

//stores the actual number of disks moved
int numMovesActual = 0;

// A structure to represent a stack
struct Stack
{
	unsigned maxSize;	//max size of stack
	int top;	//top of stack
	int * array;	//array to store values in stack
};

// function to create a stack of given maxSize.
struct Stack *createStack(unsigned maxSize)
{
	struct Stack *stack =
		(struct Stack *)malloc(sizeof(struct Stack));
	stack->maxSize = maxSize;
	stack->top = -1;
	stack->array =
		(int *)malloc(stack->maxSize * sizeof(int));
	return stack;
}

// Stack is full, when the top = maxindex
int isFull(struct Stack *stack)
{
	return (stack->top == stack->maxSize - 1);
}

// Stack is empty, when top is equal to -1
int isEmpty(struct Stack *stack)
{
	return (stack->top == -1);
}

// Function to add an item to stack. It increases
// top by 1
void push(struct Stack *stack, int item)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = item;
}

// Function to remove an item from stack. It
// decreases top by 1
int pop(struct Stack *stack)
{
	if (isEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

//Shows when a disk is moved
void moveDisk(char fromPeg, char toPeg, int disk)
{
	printf("Move %d from %c to %c\n",
		   disk, fromPeg, toPeg);
	numMovesActual++;
}

// Function to implement legal movement between
// two poles
void moveDisksSrcToDst(struct Stack *src,
							  struct Stack *dest, char s, char d)
{
	//number of errors where the top wasn't removed
	static int topDiskErrLeft = NUM_TOP_DISK_ERRORS;
	//number of errors where the moved disk was Bigger the top on dst
	static int bigDstErrLeft = NUM_BIG_DEST_ERRORS;
	int srcTopDisk = pop(src);
	int dstTopDisk = pop(dest);

	// When dst is empty
	if (srcTopDisk == INT_MIN)
	{
		push(src, dstTopDisk);
		moveDisk(d, s, dstTopDisk);
	}

	// When src  is empty
	else if (dstTopDisk == INT_MIN)
	{
		push(dest, srcTopDisk);
		moveDisk(s, d, srcTopDisk);
	}

	// When top disk of src > top disk of dst
	else if (srcTopDisk > dstTopDisk)
	{
		
		push(src, srcTopDisk);
		push(src, dstTopDisk);
		moveDisk(d, s, dstTopDisk);
	}

	// When top disk of src < top disk of dst
	else
	{
		push(dest, dstTopDisk);
		push(dest, srcTopDisk);
		moveDisk(s, d, srcTopDisk);
	}
}

//Main Function to implement toh
int tohSolve(int numDisks, struct Stack *src, struct Stack *aux,
				  struct Stack *dest)
{
	int i, numMoves;
	char s = 'S', d = 'D', a = 'A';

	//we know the amount of moved need by formula 2^k-1
	numMoves = (int)powf(2, numDisks) - 1;

	//If number of disks is even, then interchange
	//destination pole and auxiliary pole

	//solution when even
	if(numDisks % 2 == 0)
	{
		//Larger disks will be pushed first
		for (i = numDisks; i >= 1; i--)
			push(src, i);

		for (i = 1; i <= numMoves; i++)
		{
			if (i % 3 == 1)
				moveDisksSrcToDst(src, aux, s, a);

			else if (i % 3 == 2)
				moveDisksSrcToDst(src, dest, s, d);

			else if (i % 3 == 0)
				moveDisksSrcToDst(dest, aux, d, a);
		}
	}
	//solution when odd
	else
	{
		//Larger disks will be pushed first
		for (i = numDisks; i >= 1; i--)
			push(src, i);

		for (i = 1; i <= numMoves; i++)
		{
			if (i % 3 == 1)
				moveDisksSrcToDst(src, dest, s, d);

			else if (i % 3 == 2)
				moveDisksSrcToDst(src, aux, s, a);

			else if (i % 3 == 0)
				moveDisksSrcToDst(aux, dest, a, d);
		}
	}
	
	


	return numMoves; //return expected number of moves without errors
}

// Driver Program
int main()
{
	// Input: number of disks, this is k
	unsigned numDisks = NUM_DISKS;

	struct Stack *src, *dest, *aux;

	// Create three stacks of size 'numDisks'
	// to hold the disks
	src = createStack(numDisks);
	aux = createStack(numDisks);
	dest = createStack(numDisks);
	printf("k = %d\n", numDisks);
	tohSolve(numDisks, src, aux, dest);
	printf("Moves = %d\n", numMovesActual);
	return 0;
}
