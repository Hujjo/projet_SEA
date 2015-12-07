all:
	gcc manip_chaines.c struct_user_channel.c server_functions.c server.c -o ircServer
server:
	gcc manip_chaines.c struct_user_channel.c server_functions.c server.c -o ircServer
clean:
	rm -f ircServer
	rm -f *.o
