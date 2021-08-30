all:server client

server:server.c
	gcc server.c -o $@

client:client.c
	gcc $< -o $@

.PTHONY:clean
	clean:
	rm -f server
	rm -f client

