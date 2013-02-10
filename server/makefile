a.out: server.o calendar.o
	g++ -g server.o calendar.o -o server -Wall

server.o: server.cpp
	g++ -g -c server.cpp -o server.o -Wall

calendar.o: calendar.cpp
	g++ -g -c calendar.cpp -o calendar.o -Wall

clean:
	rm -rf *.o server
