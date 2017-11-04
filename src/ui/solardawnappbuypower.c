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
#include "solardawnappbuypower.h"

struct _SolarDawnAppBuyPower {
  GtkDialog parent;
};

typedef struct _SolarDawnAppBuyPowerPrivate {
  GtkWidget *show_watcher_toggle;
  GtkWidget *watcher_ip;
  GtkWidget *connect_watcher;
  GtkWidget *watcher_visibility;
} SolarDawnAppBuyPowerPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppBuyPower, solardawn_app_buy_power, GTK_TYPE_DIALOG)

static void visbility_hide (SolarDawnAppBuyPower *power) {
  SolarDawnAppBuyPowerPrivate *priv;

  priv = solardawn_app_buy_power_get_instance_private (power);
  gtk_widget_set_visible(priv->watcher_visibility, FALSE);
  gtk_widget_show(priv->watcher_visibility);
}

static void visbility_show (SolarDawnAppBuyPower *power) {
  SolarDawnAppBuyPowerPrivate *priv;
  gboolean visible = 1;

  priv = solardawn_app_buy_power_get_instance_private (power);
  gtk_widget_set_visible(priv->watcher_visibility, TRUE);
  gtk_widget_show(priv->watcher_visibility);
}

static void solardawn_app_buy_power_init (SolarDawnAppBuyPower *power) {
  gtk_widget_init_template (GTK_WIDGET (power));
}

static void solardawn_app_buy_power_dispose (GObject *object) {

  G_OBJECT_CLASS (solardawn_app_buy_power_parent_class)->dispose (object);
}

static void solardawn_app_buy_power_class_init (SolarDawnAppBuyPowerClass *class) {
  G_OBJECT_CLASS (class)->dispose = solardawn_app_buy_power_dispose;

  gtk_widget_class_set_template_from_resource  (GTK_WIDGET_CLASS (class), "/org/gtk/solardawnapp/buypower.ui");

  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, show_watcher_toggle);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, watcher_ip);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, connect_watcher);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, watcher_visibility);
}

SolarDawnAppBuyPower *solardawn_app_buy_power_new (SolarDawnAppWindow *win) {
  return g_object_new (SOLARDAWN_APP_BUY_POWER_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}

void buy_power_activated (SolarDawnAppWindow *win) {
  SolarDawnAppBuyPower *power;
  power = solardawn_app_buy_power_new (SOLARDAWN_APP_WINDOW (win));
  gtk_window_present (GTK_WINDOW (power));
}
