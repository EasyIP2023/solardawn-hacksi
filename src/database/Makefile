CC ?= gcc

SRC = solardawndb.c
OBJS = $(SRC:.c=.o)

all: database

%.o: %.c
	$(CC) -c -o $(@F) $<

database: $(OBJS)
	$(CC) -c -o $(@F) $(OBJS) -lsqlite3
