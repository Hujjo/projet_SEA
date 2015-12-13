all:
	gcc manip_chaines.c struct_user_channel.c server_functions.c server.c -o ircServer
server:
	gcc manip_chaines.c struct_user_channel.c server_functions.c -pthread server.c -o ircServer
client:
	gcc client.c -o client
clean:
	rm -f ircServer
	rm -f *.o
