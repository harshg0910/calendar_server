all: client.o
	g++ -g ./object/client.o -o ./bin/calendar -Wall

client.o: ./source/client.cpp
	g++ -g -c ./source/client.cpp -o ./object/client.o -Wall

clean:
	rm -rf ./bin/* ./object/*
