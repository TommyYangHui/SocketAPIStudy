all:server client open
server:server.o bank.o
	cc server.o bank.o -o server
server.o:server.c
	cc -c server.c
bank.o:bank.c
	cc -c bank.c
client:client.o bank.o
	cc client.o bank.o -o client
client.o:client.c
	cc -c client.c
open:open.o dao.o bank.o
	cc open.o dao.o bank.o -o open
open.o:open.c
	cc -c open.c
dao.o:dao.c
	cc -c dao.c
clean:
	rm *.o *.gch *.dat server client open
