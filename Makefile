CC	= clang
CFLAGS	= -O0 -Wall -Wextra -Werror
CFLAGS	+= -fPIC
SOFLAGS	= -shared

AR	= ar
ARFLAGS	= -r

all: header.o libmuk.a libmuk.so libmukompi.so libmukmpich.so

libmuk.a: libinit.o wrapmpich.o wrapompi.o
	$(AR) $(ARFLAGS) $@ $^

libmuk.so: libinit.o
	$(CC) $(SOFLAGS) $^ -o $@

libmukompi.so: wrapompi.o
	$(CC) $(SOFLAGS) $^ -o $@

libmukmpich.so: wrapmpich.o
	$(CC) $(SOFLAGS) $^ -o $@

header.o: header.c mpi.h
	$(CC) $(CFLAGS) -c $< -o $@

libinit.o: libinit.c mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapmpich.o: wrapmpich.c mpich.h mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

wrapompi.o: wrapompi.c ompi.h mpi.h muk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.x *.s *.a *.so
	-rm -rf *.dSYM

