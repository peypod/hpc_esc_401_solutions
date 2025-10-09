cpi : cpi.o get_time.o
	gcc -o cpi cpi.o get_time.o
cpi.o : cpi.c get_time.h
	gcc -O3 -ffast-math -mavx2 -c -o cpi.o cpi.c
get_time.o : get_time.c get_time.h
	gcc -O3 -ffast-math -mavx2 -c -o get_time.o get_time.c
clean:
	rm -f cpi cpi.o get_time.o
all:
	gcc -O3 cpi get_time
cpi_mpi : cpi_mpi.o get_time.o
	mpicc -o cpi_mpi cpi_mpi.o get_time.o
cpi_mpi.o : get_time.h 
	mpicc -O3 -c -o cpi_mpi.o cpi_mpi.c


