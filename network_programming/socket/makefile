FLAGS=-std=c++0x
CC=g++
LIB_FILEs=Socket.h Socket.cpp
Server=Server.cpp
Client=Client.cpp

server:
	$(CC) $(LIB_FILEs) $(Server) $(FLAGS) -o server

client:
	$(CC) $(LIB_FILEs) $(Client) $(FLAGS) -o client

clean:
	rm server client *.h.gch

