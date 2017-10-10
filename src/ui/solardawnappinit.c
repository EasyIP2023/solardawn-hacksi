#include <gtk/gtk.h>

#include "solardawnapp.h"

int init_gui() {
  /* Since this example is running uninstalled,
   * we have to help it find its schema. This
   * is *not* necessary in properly installed
   * application.
   */
  g_setenv ("GSETTINGS_SCHEMA_DIR", "ui/", FALSE);

  return g_application_run (G_APPLICATION (solardawn_app_new ()), 0, NULL);
}
