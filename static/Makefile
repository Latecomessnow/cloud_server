libcal.a: sub.o add.o
	ar -rc libcal.a sub.o add.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
add.o:add.c
	gcc -c add.c -o add.o

.PHONY:output
output:
	mkdir -p mathlib/lib
	mkdir -p mathlib/include
	cp -rf *.h mathlib/include
	cp -rf *.a mathlib/lib

.PHONY:clean
clean:
	rm -rf *.o *.a *.so

