#include <gtk/gtk.h>

#include "solardawnapp.h"
#include "solardawnappwin.h"

struct _SolarDawnAppWindow {
	GtkApplicationWindow parent;
};

typedef struct _SolarDawnAppWindowPrivate SolarDawnAppWindowPrivate;

struct _SolarDawnAppWindowPrivate {
	GtkWidget *stack;
};

G_DEFINE_TYPE_WITH_PRIVATE(SolarDawnAppWindow, solardawn_app_window, GTK_TYPE_APPLICATION_WINDOW);

/* Initialize App window */
static void solardawn_app_window_init (SolarDawnAppWindow *win) {
	gtk_widget_init_template (GTK_WIDGET (win));
}

static void solardawn_app_window_class_init (SolarDawnAppWindowClass *class) {
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "ui_files/window.ui");
	gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), SolarDawnAppWindow, stack);
}

SolarDawnAppWindow *solardawn_app_window_new (SolarDawnApp *app) {
	return g_object_new (SOLARDAWN_APP_WINDOW_TYPE, "application", app, NULL);
}

void solardawn_app_window_open (SolarDawnAppWindow *win, GFile *file) {
	SolarDawnAppWindowPrivate *priv;
	gchar *basename;
	GtkWidget *scrolled, *view;
	gchar *contents;
	gsize length;

	priv = solardawn_app_window_get_instance_private (win);
	basename = g_file_get_basename (file);

	scrolled = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_show (scrolled);
	gtk_widget_set_hexpand (scrolled, TRUE);
	gtk_widget_set_vexpand (scrolled, TRUE);
	view = gtk_text_view_new ();
	gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
	gtk_widget_show (view);
	gtk_container_add (GTK_CONTAINER (scrolled), view);
	gtk_stack_add_titled (GTK_STACK (priv->stack), scrolled, basename, basename);

	if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL)) {
		GtkTextBuffer *buffer;
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
		gtk_text_buffer_set_text (buffer, contents, length);
		g_free (contents);
	}
	g_free (basename);
}
