CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC_OBJ = main.c ui/solardawnapp.o ui/solardawnappinit.o ui/solardawnappwin.o ui/solardawnappprefs.o ui/resources.o hardware/hardwaretest.o

all: solardawnneeds solardawn

solardawnneeds:
	+$(MAKE) -C hardware/
	+$(MAKE) -C ui/

solardawn: $(SRC_OBJ)
	$(CC) -o $(@F) $(SRC_OBJ) $(LIBS) $(CFLAGS)

clean:
	rm -f ui/org.gtk.solardawnapp.gschema.valid
	rm -f ui/gschemas.compiled
	rm -f ui/resources.c
	rm -f ui/*.o
	rm -f hardware/*.o
	rm -f solardawn
