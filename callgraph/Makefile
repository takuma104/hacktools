CC=gcc
CFLAGS=-I/opt/local/include
LDFLAGS=-L/opt/local/lib

.PHONY: all
all: addr2name sample

addr2name: addr2name.o
	$(CC) $(LDFLAGS) -lbfd -liberty -lintl addr2name.o -o addr2name

addr2name.o: addr2name.c
	$(CC) $(CFLAGS) -c addr2name.c
	
sample: sample.o instrument.o
	$(CC) sample.o instrument.o -o sample

sample.o: sample.c
	$(CC) -finstrument-functions -c sample.c

instrument.o: instrument.c
	$(CC) -c instrument.c

.PHONY: clean
clean:
	rm -f *.o addr2name sample
