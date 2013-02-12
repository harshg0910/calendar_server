all: server_thread.o server_select.o server.o calendar.o
	g++ -g server_select.o calendar.o -o server_select -Wall
	g++ -pthread -g server_thread.o calendar.o -o server_thread -Wall
	g++ -g server.o calendar.o -o server -Wall

server: server.o calendar.o
	g++ -g server.o calendar.o -o server -Wall

server_thread: server_thread.o calendar.o
	g++ -g -pthread server_thread.o calendar.o -o server_thread -Wall

server_select: server_select.o calendar.o
	g++ -g server_select.o calendar.o -o server_select -Wall

server_thread.o: server_thread.cpp
	g++ -pthread -g -c server_thread.cpp -o server_thread.o -Wall

server_select.o: server_select.cpp
	g++ -g -c server_select.cpp -o server_select.o -Wall

server.o: server.cpp
	g++ -g -c server.cpp -o server.o -Wall

calendar.o: calendar.cpp
	g++ -g -c calendar.cpp -o calendar.o -Wall

clean:
	rm -rf *.o server server_select server_thread
