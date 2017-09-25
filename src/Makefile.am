INCLUDES = -I$(top_srcdir) -I$(includedir) $(GNOME_INCLUDEDIR) \
-DG_LOG_DOMAIN=\"SolarDawn\" -DGNOMELOCALEDIR=\""$(datadir)/locale"\" \
-I../intl -I$(top_srcdir)/intl
bin_PROGRAMS = solardawn
gnome_solardawn_SOURCES =         \
solardawn.c           \
solardawn.h
gnome_solardawn_LDADD = $(GNOMEUI_LIBS) $(GNOME_LIBDIR) $(INTLLIBS)
