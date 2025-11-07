
# Exercise 1

## a. 
int * (int pointer)
## b. 
int
## c. 
int (*)[10] (pointer to an array of 10 ints)  
## d. 
10
## e. 
10
## f. 
40
## g. 
60
## h. 
15
## i.
Writes memory to before the start of the array; undefined behaviour
## j.
element before p[0]; undefined behaviour
## k.
100
## l.
Memory after the end of the array; undefined behaviour


# Exercise 2

## a. 
int ** (pointer to pointer to int)

## b.

``M :``
	int**, pointer to pointer to int
	address of M[0]
``*M :`` 
	int*, pointer to int
	pointer to first integer array
``**M :``
	int, first element of first integer array
	value 0

## c.

`M[1][3] = 7`
`*(M[0]+1) = 1`
`*(*(M+1)+3) = 7`

## d.

No; as new int is called twice independently, the arrays are allocated in different places (in the heap?). Although it is possible that they might be next to each other, it is not guaranteed.



# Exercise 3

## a.

x determines the column, y determines the row.
## b.

14 x 6 = 84
## c.

Depends on whether row-major or column-major is used. 
In row-major, (1,3) and (1,4) are adjacent, in column major, (1,3) and (2,3) are adjacent.

## d.

It depends on the language and how the data is accessed.
in C and C++, row-major is the default, in FORTRAN it's column-major.

## e.

In row-major, the stride of the x-dimension is 1.

## f.

In row-major, the stride of the y-dimension is the row-length, 14.

## g.

index =  0 * 14 + 10 = 10
(0,10) is at A[10]
## h.

index = 3 * 14 + 0 = 42
(3,0) is at A[42]

## i.

Since y only goes up to 5, y =7 is out of bounds of the array.

