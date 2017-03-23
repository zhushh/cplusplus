FLAGS=-std=c++0x
CC=g++
LIB_FILEs=Socket.h Socket.cpp
Server=Server.cpp
Client=Client.cpp
# selectclient=selectclient.cpp
# selectserver=selectserver.cpp

server:
	$(CC) $(LIB_FILEs) $(Server) $(FLAGS) -o server

client:
	$(CC) $(LIB_FILEs) $(Client) $(FLAGS) -o client

# selectclient:
# 	$(CC) $(LIB_FILEs) $(selectclient) $(FLAGS) -o selectclient

# selectserver:
# 	$(CC) $(LIB_FILEs) $(selectserver) $(FLAGS) -o selectserver

clean:
	rm server client # selectclient selectserver

