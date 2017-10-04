solardawnapp_resources = gnome.compile_resources('solardawnapp_resources',
  'solardawnapp.gresource.xml',
  source_dir: '.')

solardawnapp_schemas = gnome.compile_schemas()

executable('solardawnapp',
  'main.c',
  'solardawnapp.c',
  'solardawnappwin.c',
  'solardawnappprefs.c',
  solardawnapp_resources,
  solardawnapp_schemas,
  dependencies: libgtk_dep)
