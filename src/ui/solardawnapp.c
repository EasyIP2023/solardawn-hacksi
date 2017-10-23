/*
 * Copyright (c) 2017, Vincent Davis
 *
 *----------------------------------------------------------------------
 * This file is part of project solardawn.
 *
 *  solardawn is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  solardawn is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with solardawn; if not, write to the Free Software
 *  Foundation, Inc.:
 *      59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *----------------------------------------------------------------------
 */

#include <gtk/gtk.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"

struct _SolarDawnApp {
  GtkApplication parent;
};

G_DEFINE_TYPE(SolarDawnApp, solardawn_app, GTK_TYPE_APPLICATION);

static void solardawn_app_init (SolarDawnApp *app) {}

static void solardawn_app_startup (GApplication *app) {
  G_APPLICATION_CLASS (solardawn_app_parent_class)->startup (app);
}

static void solardawn_app_activate (GApplication *app) {
  SolarDawnAppWindow *win;

  win = solardawn_app_window_new (SOLARDAWN_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void solardawn_app_class_init (SolarDawnAppClass *class) {
  G_APPLICATION_CLASS (class)->startup  = solardawn_app_startup;
  G_APPLICATION_CLASS (class)->activate = solardawn_app_activate;
}

SolarDawnApp *solardawn_app_new (void) {
  return g_object_new (SOLARDAWN_APP_TYPE, "application-id", "org.gtk.solardawnapp",
                      "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
