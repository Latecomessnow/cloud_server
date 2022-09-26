.PHONY:all
all:test exec

test:test.c
	gcc -o $@ $^

exec:exec.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf exec test
