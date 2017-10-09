#ifndef __SOLARDAWNAPPWIN_H
#define __SOLARDAWNAPPWIN_H

#include <gtk/gtk.h>
#include "solardawnapp.h"


#define SOLARDAWN_APP_WINDOW_TYPE (solardawn_app_window_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppWindow, solardawn_app_window, SOLARDAWN, APP_WINDOW, GtkApplicationWindow)

SolarDawnAppWindow *solardawn_app_window_new           (SolarDawnApp       *app);
void                solardawn_app_window_update_labels (SolarDawnAppWindow *win);

#endif
