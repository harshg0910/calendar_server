a.out: server.o calendar.o
	g++ -g server.o calendar.o -o server

server.o: server.cpp
	g++ -g -c server.cpp -o server.o

calendar.o: calendar.cpp
	g++ -g -c calendar.cpp -o calendar.o

clean:
	rm -rf *.o server
