CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)
GLIB_COMPILE_RESOURCES = $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)
GLIB_COMPILE_SCHEMAS = $(shell $(PKGCONFIG) --variable=glib_compile_schemas gio-2.0)

SRC = solardawnapp.c solardawnappwin.c solardawnappprefs.c solardawnappinit.c ../hardware/hardwaretest.o
BUILT_SRC = resources.c

OBJS = $(BUILT_SRC:.c=.o) $(SRC:.c=.o)

all: solardawnapp

org.gtk.solardawnapp.gschema.valid: org.gtk.solardawnapp.gschema.xml
	$(GLIB_COMPILE_SCHEMAS) --strict --dry-run --schema-file=$< && mkdir -p $(@D) && touch $@

gschemas.compiled: org.gtk.solardawnapp.gschema.valid
	$(GLIB_COMPILE_SCHEMAS) .

resources.c: solardawnapp.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=. --generate-dependencies solardawnapp.gresource.xml)
	$(GLIB_COMPILE_RESOURCES) solardawnapp.gresource.xml --target=$@ --sourcedir=. --generate-source

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

solardawnapp: $(OBJS) gschemas.compiled
	$(CC) -pthread -c -o $(@F) $(OBJS) $(LIBS)
