all:
	gcc manip_chaines.c struct_user_channel.c server_functions.c server_multi_users.c -pthread -o ircServer
server:
	gcc manip_chaines.c struct_user_channel.c server_functions.c -pthread server_multi_users.c -o ircServer
clean:
	rm -f ircServerdbug
	rm -f ircServer
	rm -f *.o
