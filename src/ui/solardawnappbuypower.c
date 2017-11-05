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
#include "../networking/peer.h"

struct _SolarDawnAppBuyPower {
  GtkDialog parent;
};

typedef struct _SolarDawnAppBuyPowerPrivate {
  GtkWidget *watcher_ip;
  GtkWidget *connect_watcher;
} SolarDawnAppBuyPowerPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppBuyPower, solardawn_app_buy_power, GTK_TYPE_DIALOG)

static void connect_watcher_clicked (SolarDawnAppBuyPower *power) {
  SolarDawnAppBuyPowerPrivate *priv;
  priv = solardawn_app_buy_power_get_instance_private (power);
  run ((char *) priv->watcher_ip);
}

static void solardawn_app_buy_power_init (SolarDawnAppBuyPower *power) {
  SolarDawnAppBuyPowerPrivate *priv;

  priv = solardawn_app_buy_power_get_instance_private (power);

  gtk_widget_init_template (GTK_WIDGET (power));
  g_signal_connect (priv->connect_watcher, "clicked", G_CALLBACK (connect_watcher_clicked), power);

}

static void solardawn_app_buy_power_dispose (GObject *object) {

  G_OBJECT_CLASS (solardawn_app_buy_power_parent_class)->dispose (object);
}

static void solardawn_app_buy_power_class_init (SolarDawnAppBuyPowerClass *class) {
  G_OBJECT_CLASS (class)->dispose = solardawn_app_buy_power_dispose;

  gtk_widget_class_set_template_from_resource  (GTK_WIDGET_CLASS (class), "/org/gtk/solardawnapp/buypower.ui");

  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, watcher_ip);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppBuyPower, connect_watcher);
}

SolarDawnAppBuyPower *solardawn_app_buy_power_new (SolarDawnAppWindow *win) {
  return g_object_new (SOLARDAWN_APP_BUY_POWER_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}

void buy_power_activated (SolarDawnAppWindow *win) {
  SolarDawnAppBuyPower *power;
  power = solardawn_app_buy_power_new (SOLARDAWN_APP_WINDOW (win));
  gtk_window_present (GTK_WINDOW (power));
}
