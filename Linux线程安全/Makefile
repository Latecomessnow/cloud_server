.PHONY:all
all:myThread GrabTicket
myThread:myThread.cc
	g++ -o $@ $^ -std=c++11 -lpthread
GrabTicket:grab_ticket.cc
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f myThread GrabTicket