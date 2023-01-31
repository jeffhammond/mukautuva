CC	= clang
CFLAGS	= -O0 -Wall -Wextra -Werror

all: header.o lib

lib: libinit.o wrapmpich.o wrapompi.o

header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libinit.o: libinit.c mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapmpich.o: wrapmpich.c mpich.h mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapompi.o: wrapompi.c ompi.h mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s
	-rm -rf *.dSYM

