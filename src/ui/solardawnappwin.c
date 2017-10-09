#include <gtk/gtk.h>
#include <stdlib.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"

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
};

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppWindow, solardawn_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void update_watt_hours(SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;
  gchar *watt_hours;

  priv = solardawn_app_window_get_instance_private (win);

  watt_hours = g_strdup_printf ("%f watt/hours", rand());
  gtk_label_set_text (GTK_LABEL (priv->watt_hours), watt_hours);

  g_free (watt_hours);
}

static void update_watts(SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;
  gchar *watts;

  priv = solardawn_app_window_get_instance_private (win);

  watts = g_strdup_printf ("%f watts", rand());
  gtk_label_set_text (GTK_LABEL (priv->watts), watts);
  g_free (watts);
}

static void update_amount_produced(SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;
  gchar *amount_produced;

  priv = solardawn_app_window_get_instance_private (win);

  amount_produced = g_strdup_printf ("%f watts", rand());
  gtk_label_set_text (GTK_LABEL (priv->amount_produced), amount_produced);
  g_free (amount_produced);
}

static void update_amount_used(SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;
  gchar *amount_used;

  priv = solardawn_app_window_get_instance_private (win);

  amount_used = g_strdup_printf ("%f watts", rand());
  gtk_label_set_text (GTK_LABEL (priv->amount_used), amount_used);
  g_free (amount_used);
}

static void update_total_power(SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;
  gchar *total_power;

  priv = solardawn_app_window_get_instance_private (win);

  total_power = g_strdup_printf ("%f watts", rand());
  gtk_label_set_text (GTK_LABEL (priv->total_power), total_power);
  g_free (total_power);
}

static void solardawn_app_window_init (SolarDawnAppWindow *win) {
  SolarDawnAppWindowPrivate *priv;

  priv = solardawn_app_window_get_instance_private (win);
  gtk_widget_init_template (GTK_WIDGET (win));

  solardawn_app_window_update_labels(win);

  priv->settings = g_settings_new ("org.gtk.solardawnapp");

  g_settings_bind (priv->settings, "transition", priv->stack, "transition-type", G_SETTINGS_BIND_DEFAULT);
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
}

SolarDawnAppWindow *solardawn_app_window_new (SolarDawnApp *app) {
  return g_object_new (SOLARDAWN_APP_WINDOW_TYPE, "application", app, NULL);
}

void solardawn_app_window_update_labels (SolarDawnAppWindow *win) {
  update_watt_hours(win);
  update_watts(win);
  update_amount_produced(win);
  update_amount_used(win);
  update_total_power(win);
}
