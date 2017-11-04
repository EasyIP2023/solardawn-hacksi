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
#include "solardawnappenterinfo.h"
#include "../database/solardawndb.h"

struct _SolarDawnAppEnterInfo {
  GtkDialog parent;
};

typedef struct _SolarDawnAppEnterInfoPrivate {
  GtkWidget *first_name_label;
  GtkWidget *last_name_label;
  GtkWidget *phone_label;
  GtkWidget *email_label;
  GtkWidget *address_label;
  GtkWidget *state_label;
  GtkWidget *city_label;
  GtkWidget *postal_code_label;
  GtkWidget *update_db_label;
  GtkWidget *sell_switch;
} SolarDawnAppEnterInfoPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppEnterInfo, solardawn_app_enter_info, GTK_TYPE_DIALOG)

static void solardawn_app_enter_info_init (SolarDawnAppEnterInfo *info) {
  gtk_widget_init_template (GTK_WIDGET (info));
}

static void solardawn_app_enter_info_dispose (GObject *object) {

  G_OBJECT_CLASS (solardawn_app_enter_info_parent_class)->dispose (object);
}

static void solardawn_app_enter_info_class_init (SolarDawnAppEnterInfoClass *class) {
  G_OBJECT_CLASS (class)->dispose = solardawn_app_enter_info_dispose;

  //create_db ();
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/gtk/solardawnapp/info.ui");

  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, first_name_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, last_name_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, phone_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, email_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, address_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, state_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, city_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, postal_code_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, update_db_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppEnterInfo, sell_switch);
}

SolarDawnAppEnterInfo *solardawn_app_enter_info_new (SolarDawnAppWindow *win) {
  return g_object_new (SOLARDAWN_APP_ENTER_INFO_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}

void enter_info_activated (SolarDawnAppWindow *win) {
  SolarDawnAppEnterInfo *info;
  info = solardawn_app_enter_info_new (SOLARDAWN_APP_WINDOW (win));
  gtk_window_present (GTK_WINDOW (info));
}
