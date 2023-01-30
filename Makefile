CC	= clang
CFLAGS	= -O0 -Wall -Wextra -Werror

all: header.o

%.o: %.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s
	-rm -rf *.dSYM

