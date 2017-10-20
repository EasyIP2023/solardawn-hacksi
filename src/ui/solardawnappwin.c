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
#include <stdlib.h>
#include <pthread.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"
#include "../hardware/hardwaretest.h"

struct _SolarDawnAppWindow {
  GtkApplicationWindow parent;
};

typedef struct _SolarDawnAppWindowPrivate SolarDawnAppWindowPrivate;

struct _SolarDawnAppWindowPrivate {
  GSettings *settings;
  GtkWidget *stack;
  GtkWidget *watts;
  GtkWidget *watt_hours;
  GtkWidget *amount_produced;
  GtkWidget *amount_used;
  GtkWidget *total_power;
  GtkWidget *see_power_button;
  GtkWidget *buy_power_button;
  GtkWidget *enter_info_button;
};

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppWindow, solardawn_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void update_watt_hours (SolarDawnAppWindow *win, double value) {
  SolarDawnAppWindowPrivate *priv;
  gchar *watt_hours;

  priv = solardawn_app_window_get_instance_private (win);

  watt_hours = g_strdup_printf ("%f watt/hours", value);
  gtk_label_set_text (GTK_LABEL (priv->watt_hours), watt_hours);

  g_free (watt_hours);
}

static void update_watts (SolarDawnAppWindow *win, double value) {
  SolarDawnAppWindowPrivate *priv;
  gchar *watts;

  priv = solardawn_app_window_get_instance_private (win);

  watts = g_strdup_printf ("%f watts", value);
  gtk_label_set_text (GTK_LABEL (priv->watts), watts);
  g_free (watts);
}

static void update_amount_produced (SolarDawnAppWindow *win, double value) {
  SolarDawnAppWindowPrivate *priv;
  gchar *amount_produced;

  priv = solardawn_app_window_get_instance_private (win);

  amount_produced = g_strdup_printf ("%f watts", value);
  gtk_label_set_text (GTK_LABEL (priv->amount_produced), amount_produced);
  g_free (amount_produced);
}

static void update_amount_used (SolarDawnAppWindow *win, double value) {
  SolarDawnAppWindowPrivate *priv;
  gchar *amount_used;

  priv = solardawn_app_window_get_instance_private (win);

  amount_used = g_strdup_printf ("%f watts", value);
  gtk_label_set_text (GTK_LABEL (priv->amount_used), amount_used);
  g_free (amount_used);
}

static void update_total_power (SolarDawnAppWindow *win, double value) {
  SolarDawnAppWindowPrivate *priv;
  gchar *total_power;

  priv = solardawn_app_window_get_instance_private (win);

  total_power = g_strdup_printf ("%f watts", value);
  gtk_label_set_text (GTK_LABEL (priv->total_power), total_power);
  g_free (total_power);
}

void *update_amount_produced_label (void *win) {
  SolarDawnAppWindow *window = (SolarDawnAppWindow *)win;

  while (1) {
    update_amount_produced(window, return_amount_produced());
    sleep(4);
  }
}

void *update_amount_used_label (void *win) {
  SolarDawnAppWindow *window = (SolarDawnAppWindow *)win;

  while (1) {
    update_amount_used(window, return_amount_used());
    sleep(1);
  }
}

void *update_watt_hours_label (void *win) {
  SolarDawnAppWindow *window = (SolarDawnAppWindow *)win;

  while (1) {
    update_watt_hours(window, return_watt_hours());
    sleep(2);
  }
}

void *update_watts_label (void *win) {
  SolarDawnAppWindow *window = (SolarDawnAppWindow *)win;

  while (1) {
    update_watts(window, return_watts());
    sleep(5);
  }
}

void *update_total_power_label (void *win) {
  SolarDawnAppWindow *window = (SolarDawnAppWindow *)win;

  while (1) {
    update_total_power(window, return_total_power());
    sleep(5);
  }
}

static void update_labels_with_threads (SolarDawnAppWindow *win) {
  pthread_t thread;
  if (pthread_create(&thread, NULL, update_amount_produced_label, (void *) win) != 0) {
    perror("pthread_create failed");
    exit(1);
  }

  if (pthread_create(&thread, NULL, update_amount_used_label, (void *) win) != 0) {
    perror("pthread_create failed");
    exit(1);
  }

  if (pthread_create(&thread, NULL, update_watt_hours_label, (void *) win) != 0) {
    perror("pthread_create failed");
    exit(1);
  }

  if (pthread_create(&thread, NULL, update_watts_label, (void *) win) != 0) {
    perror("pthread_create failed");
    exit(1);
  }

  if (pthread_create(&thread, NULL, update_total_power_label, (void *) win) != 0) {
    perror("pthread_create failed");
    exit(1);
  }
}

/*
void enter_info_label_clicked_cb (SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;

  priv = solardawn_app_window_get_instance_private (win);
  if (gtk_button_clicked(priv->enter_info_button))

}
*/
static void solardawn_app_window_init (SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;

  priv = solardawn_app_window_get_instance_private (win);
  gtk_widget_init_template (GTK_WIDGET (win));

  priv->settings = g_settings_new ("org.gtk.solardawnapp");

  g_settings_bind (priv->settings, "transition", priv->stack, "transition-type", G_SETTINGS_BIND_DEFAULT);

  update_labels_with_threads(win);
}

static void solardawn_app_window_dispose (GObject *object) {
  SolarDawnAppWindow *win;
  SolarDawnAppWindowPrivate *priv;

  win = SOLARDAWN_APP_WINDOW (object);
  priv = solardawn_app_window_get_instance_private (win);

  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (solardawn_app_window_parent_class)->dispose (object);
}

static void solardawn_app_window_class_init (SolarDawnAppWindowClass *class) {
  G_OBJECT_CLASS (class)->dispose = solardawn_app_window_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/gtk/solardawnapp/window.ui");

  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, stack);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, watt_hours);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, watts);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, amount_used);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, amount_produced);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, total_power);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, see_power_button);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, buy_power_button);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, enter_info_button);
}

SolarDawnAppWindow *solardawn_app_window_new (SolarDawnApp *app) {
  return g_object_new (SOLARDAWN_APP_WINDOW_TYPE, "application", app, NULL);
}
