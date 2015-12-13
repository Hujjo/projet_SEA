all:
	gcc server.c -o server
	gcc client.c -o client
server:
	gcc manip_chaines.c struct_user_channel.c -pthread server.c -o server
client:
	gcc client.c -o client
clean:
	rm -f server client
