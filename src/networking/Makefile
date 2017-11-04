CC = gcc
DEBUG_FLAGS = -g -O0 -DDEBUG -pthread -lm
CFLAGS = $(DEBUG_FLAGS) -Wall
RM = rm -f

all: watcher peer

watcher: watcher.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

peer: peer.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	$(RM) *.o watcher peer
