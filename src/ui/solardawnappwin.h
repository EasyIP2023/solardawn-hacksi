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

#ifndef __SOLARDAWNAPPWIN_H
#define __SOLARDAWNAPPWIN_H

#include <gtk/gtk.h>
#include "solardawnapp.h"


#define SOLARDAWN_APP_WINDOW_TYPE (solardawn_app_window_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppWindow, solardawn_app_window, SOLARDAWN, APP_WINDOW, GtkApplicationWindow)

SolarDawnAppWindow *solardawn_app_window_new (SolarDawnApp *app);

#endif
