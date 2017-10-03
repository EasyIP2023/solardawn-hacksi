#include <gtk/gtk.h>

#include "solardawnapp.h"

int main (int argc, char *argv[]) {
  return g_application_run (G_APPLICATION (solardawn_app_new ()), argc, argv);
}

