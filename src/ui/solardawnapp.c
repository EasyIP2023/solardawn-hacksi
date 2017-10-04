#include <gtk/gtk.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"
#include "solardawnappprefs.h"

struct _SolarDawnApp {
  GtkApplication parent;
};

G_DEFINE_TYPE(SolarDawnApp, solardawn_app, GTK_TYPE_APPLICATION);

static void solardawn_app_init (SolarDawnApp *app) {}

static void preferences_activated (GSimpleAction *action, GVariant *parameter, gpointer app) {
  SolarDawnAppPrefs *prefs;
  GtkWindow *win;

  win = gtk_application_get_active_window (GTK_APPLICATION (app));
  prefs = solardawn_app_prefs_new (SOLARDAWN_APP_WINDOW (win));
  gtk_window_present (GTK_WINDOW (prefs));
}

static void quit_activated (GSimpleAction *action, GVariant *parameter, gpointer app) {
  g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
{
  { "preferences", preferences_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void solardawn_app_startup (GApplication *app) {
  GtkBuilder *builder;
  GMenuModel *app_menu;
  const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS (solardawn_app_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries, G_N_ELEMENTS (app_entries), app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", quit_accels);
  builder = gtk_builder_new_from_resource ("/org/gtk/solardawnapp/app-menu.ui");
  app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
  gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
  g_object_unref (builder);
}

static void solardawn_app_activate (GApplication *app) {
  SolarDawnAppWindow *win;

  win = solardawn_app_window_new (SOLARDAWN_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void solardawn_app_open (GApplication *app, GFile **files, gint n_files, const gchar *hint) {
  GList *windows;
  SolarDawnAppWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = SOLARDAWN_APP_WINDOW (windows->data);
  else
    win = solardawn_app_window_new (SOLARDAWN_APP (app));

  for (i = 0; i < n_files; i++)
    solardawn_app_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void solardawn_app_class_init (SolarDawnAppClass *class) {
  G_APPLICATION_CLASS (class)->startup = solardawn_app_startup;
  G_APPLICATION_CLASS (class)->activate = solardawn_app_activate;
  G_APPLICATION_CLASS (class)->open = solardawn_app_open;
}

SolarDawnApp *solardawn_app_new (void) {
  return g_object_new (SOLARDAWN_APP_TYPE, "application-id", "org.gtk.solardawnapp",
                      "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
