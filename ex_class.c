#include <stdio.h>

int main(void) {
	int x = 1;
	int *xPtr = &x;  // xPtr points to x

	printf("The memory address of x and the value of xPtr is %p.\n", xPtr);
	xPtr++;
	printf("After xPtr++: The  value of xPtr is %p.\n\n", xPtr);

	double *xPtrd = (double *)&x;	// without the cast, you get a warning
	printf("The memory address of x and the value of xPtrd is %p.\n", xPtrd);
	xPtrd++;
	printf("After xPtrd++: The value of xPtrd is %p.\n\n", xPtrd);

	char *xPtrc = (char *)&x;	// without the cast, you get a warning
	printf("The memory address of x and the value of xPtrc is %p.\n", xPtrc);
	xPtrc++;
	printf("After xPtrc++: The value of xPtrc is %p.\n\n", xPtrc);
		
	// Size of the variables/pointers
	printf("Size of int: %d\n", sizeof(int));
	printf("Size of int*: %d\n\n", sizeof(int*));
	printf("Size of double: %d\n", sizeof(double));
	printf("Size of double*: %d\n\n", sizeof(double*));
	printf("Size of char: %d\n", sizeof(char));
	printf("Size of char*: %d\n\n\n", sizeof(char*));
	
	return 0;
}
