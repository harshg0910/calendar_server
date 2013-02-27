all: server_thread.o server_select.o server.o calendar.o
	g++ -g ./object/server_select.o ./object/calendar.o -o ./bin/server_select -Wall
	g++ -pthread -g ./object/server_thread.o ./object/calendar.o -o ./bin/server_thread -Wall
	g++ -g ./object/server.o ./object/calendar.o -o ./bin/server -Wall

server: server.o calendar.o
	g++ -g ./object/server.o ./object/calendar.o -o ./bin/server -Wall

server_thread: server_thread.o calendar.o
	g++ -g -pthread ./object/server_thread.o ./object/calendar.o -o ./bin/server_thread -Wall

server_select: server_select.o calendar.o
	g++ -g ./object/server_select.o ./object/calendar.o -o ./bin/server_select -Wall

server_thread.o: ./source/server_thread.cpp
	g++ -pthread -g -c ./source/server_thread.cpp -o ./object/server_thread.o -Wall

server_select.o: ./source/server_select.cpp
	g++ -g -c ./source/server_select.cpp -o ./object/server_select.o -Wall

server.o: ./source/server.cpp
	g++ -g -c ./source/server.cpp -o ./object/server.o -Wall

calendar.o: ./source/calendar.cpp
	g++ -g -c ./source/calendar.cpp -o ./object/calendar.o -Wall

clean:
	rm -rf ./bin/* ./object/*
