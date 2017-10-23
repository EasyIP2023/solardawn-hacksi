#ifndef __SOLARDAWNAPPENTERINFO_H
#define __SOLARDAWNAPPENTERINFO_H

#include <gtk/gtk.h>
#include "solardawnappwin.h"


#define SOLARDAWN_APP_ENTER_INFO_TYPE (solardawn_app_enter_info_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppEnterInfo, solardawn_app_enter_info, SOLARDAWN, APP_ENTER_INFO, GtkDialog)

SolarDawnAppEnterInfo *solardawn_app_enter_info_new (SolarDawnAppWindow *win);

void enter_info_activated (SolarDawnAppWindow *win);

#endif
