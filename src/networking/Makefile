CC = gcc
DEBUG_FLAGS = -g -O0 -DDEBUG -pthread
CFLAGS = $(DEBUG_FLAGS) -Wall

all: watcher

watcher: watcher.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

peer: peer.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o watcher peer
