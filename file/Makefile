.PHONY:all
all:mytest test
mytest:file.c
	gcc -o $@ $^
test:test.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf mytest
