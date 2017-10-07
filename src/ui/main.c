#include <gtk/gtk.h>

#include "solardawnapp.h"

int main () {
  /* Since this example is running uninstalled,
   * we have to help it find its schema. This
   * is *not* necessary in properly installed
   * application.
   */
  g_setenv ("GSETTINGS_SCHEMA_DIR", ".", FALSE);

  return g_application_run (G_APPLICATION (solardawn_app_new ()), 0, NULL);
}
