CC ?= gcc

SRC = hardwaretest.c
OBJS = $(SRC:.c=.o)

all: hardware

%.o: %.c
	$(CC) -c -o $(@F) $<

hardware: $(OBJS)
	$(CC) -c -o $(@F) $(OBJS)
