CC	= clang
CFLAGS	= -O0 -Wall -Wextra -Werror

all: header.o lib

lib: libinit.o

header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libinit.o: libinit.c mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s
	-rm -rf *.dSYM

