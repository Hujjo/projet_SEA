all:
	gcc manip_chaines.c struct_user_channel.c server_functions.c server.c -o ircServer
server:
	gcc manip_chaines.c struct_user_channel.c server_functions.c -pthread server_multi_users.c -o ircServer
serverdbug:
	gcc -g manip_chaines.c struct_user_channel.c server_functions.c -pthread server_multi_users.c -o ircServerdbug

client:
	gcc client.c -o client
clean:
	rm -f ircServerdbug
	rm -f ircServer
	rm -f *.o
