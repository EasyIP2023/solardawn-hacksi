gnome_solardawn_helpdir = $(datadir)/gnome/help/solardawn/C

gnome_solardawn_help_DATA = \
				gnome-solardawn.html \
				topic.dat
SGML_FILES = gnome-solardawn.sgml
EXTRA_DIST = \
	topic.dat \
	$(SGML_FILES)

all:
gnome-solardawn.html: gnome-solardawn/gnome-solardawn.html
-cp gnome-solardawn/gnome-solardawn.html .
gnome-solardawn/gnome-solardawn.html: $(SGML_FILES)
-db2html gnome-solardawn.sgml
## when we make dist, we include the generated HTML so people don’t
## have to have the docbook tools
dist-hook:
mkdir $(distdir)/gnome-solardawn
-cp gnome-solardawn/*.html gnome-solardawn/*.css $(distdir)/gnome-solardawn
-cp gnome-solardawn.html $(distdir)
install-data-local: gnome-solardawn.html
$(mkinstalldirs) $(gnome_hello_helpdir)/images
-for file in $(srcdir)/gnome-solardawn/*.html $(srcdir)/gnome-solardawn/*.css; do \
basefile=‘basename $$file‘; \
$(INSTALL_DATA) $(srcdir)/$$file $(gnome_hello_helpdir)/$$basefile; \
done
gnome-solardawn.ps: gnome-solardawn.sgml
-db2ps $<
gnome-solardawn..rtf: gnome-hello.sgml
-db2rtf $<

