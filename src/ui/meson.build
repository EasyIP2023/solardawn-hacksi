solardawnapp_resources = gnome.compile_resources('solardawnapp_resources',
  'ui_files/solardawn.gresource.xml',
  source_dir: '.')

executable('solardawnapp',
  'solardawnapp.c', 'solardawnappwin.c', 'main.c', solardawnapp_resources,
  dependencies: libgtk_dep)
