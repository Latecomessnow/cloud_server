.PHONY:all
all:client server 
client:client.c
	gcc -o $@ $^ 
serve:r server.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f server client
