#include <gtk/gtk.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"
#include "solardawnappprefs.h"

struct _SolarDawnAppPrefs {
  GtkDialog parent;
};

typedef struct _SolarDawnAppPrefsPrivate SolarDawnAppPrefsPrivate;

struct _SolarDawnAppPrefsPrivate {
  GSettings *settings;
  GtkWidget *font;
  GtkWidget *transition;
};

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppPrefs, solardawn_app_prefs, GTK_TYPE_DIALOG)

static void solardawn_app_prefs_init (SolarDawnAppPrefs *prefs) {
  SolarDawnAppPrefsPrivate *priv;

  priv = solardawn_app_prefs_get_instance_private (prefs);
  gtk_widget_init_template (GTK_WIDGET (prefs));
  priv->settings = g_settings_new ("org.gtk.solardawnapp");

  g_settings_bind (priv->settings, "font", priv->font, "font", G_SETTINGS_BIND_DEFAULT);
  g_settings_bind (priv->settings, "transition", priv->transition, "active-id", G_SETTINGS_BIND_DEFAULT);
}

static void solardawn_app_prefs_dispose (GObject *object) {
  SolarDawnAppPrefsPrivate *priv;

  priv = solardawn_app_prefs_get_instance_private (SOLARDAWN_APP_PREFS (object));
  g_clear_object (&priv->settings);

  G_OBJECT_CLASS (solardawn_app_prefs_parent_class)->dispose (object);
}

static void solardawn_app_prefs_class_init (SolarDawnAppPrefsClass *class) {
  G_OBJECT_CLASS (class)->dispose = solardawn_app_prefs_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/org/gtk/solardawnapp/prefs.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppPrefs, font);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppPrefs, transition);
}

SolarDawnAppPrefs *solardawn_app_prefs_new (SolarDawnAppWindow *win) {
  return g_object_new (SOLARDAWN_APP_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
