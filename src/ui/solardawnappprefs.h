#ifndef __SOLARDAWNAPPPREFS_H
#define __SOLARDAWNAPPPREFS_H

#include <gtk/gtk.h>
#include "solardawnappwin.h"


#define SOLARDAWN_APP_PREFS_TYPE (solardawn_app_prefs_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppPrefs, solardawn_app_prefs, SOLARDAWN, APP_PREFS, GtkDialog)

SolarDawnAppPrefs *solardawn_app_prefs_new (SolarDawnAppWindow *win);

#endif
