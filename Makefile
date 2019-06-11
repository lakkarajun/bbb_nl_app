INCS = $(shell pkg-config --cflags libmnl)
LIBS = $(shell pkg-config --libs libmnl)
CFLAGS = -ggdb
CC = /home/raju/Projects/BBBcode/buildroot/output/host/bin/arm-linux-gnueabihf-gcc
LDFLAGS = 

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(INCS) $<

nl-app: nl-app.o
	$(CC) -o $@ $< $(LIBS)

clean:
	/bin/rm -f *.o
	/bin/rm -f nl-app
