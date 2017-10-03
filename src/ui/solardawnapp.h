#ifndef __SOLARDAWNAPP_H
#define __SOLARDAWNAPP_H

#include <gtk/gtk.h>

#define SOLARDAWN_APP_TYPE (solardawn_app_get_type())
G_DECLARE_FINAL_TYPE (SolarDawnApp, solardawn_app, SOLARDAWN, APP, GtkApplication)

SolarDawnApp *solardawn_app_new (void);

#endif
