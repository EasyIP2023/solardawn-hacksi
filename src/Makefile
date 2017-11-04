CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

MAIN = main.c
UI_OBJ = ui/solardawnapp.o ui/solardawnappinit.o ui/solardawnappwin.o ui/solardawnappenterinfo.o ui/solardawnappbuypower.o ui/resources.o
HARDWARE_OBJ = hardware/hardwaretest.o
DATABASE_OBJ = database/solardawndb.o

OBJS =  $(UI_OBJ) $(HARDWARE_OBJ) $(DATABASE_OBJ)

all: solardawnneeds solardawn

solardawnneeds:
	+$(MAKE) -C hardware/
	+$(MAKE) -C database/
	+$(MAKE) -C ui/

solardawn: $(OBJS)
	$(CC) -o $(@F) $(MAIN) $(OBJS) $(LIBS) $(CFLAGS)  -lsqlite3

clean:
	rm -f ui/resources.c
	rm -f ui/*.o
	rm -f hardware/*.o
	rm -f database/*.o
	rm -f solardawn
