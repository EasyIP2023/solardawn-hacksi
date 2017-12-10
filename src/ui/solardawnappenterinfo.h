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

#ifndef __SOLARDAWNAPPENTERINFO_H
#define __SOLARDAWNAPPENTERINFO_H

#include <gtk/gtk.h>
#include "solardawnappwin.h"

#define SOLARDAWN_APP_ENTER_INFO_TYPE (solardawn_app_enter_info_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppEnterInfo, solardawn_app_enter_info, SOLARDAWN, APP_ENTER_INFO, GtkDialog)

SolarDawnAppEnterInfo *solardawn_app_enter_info_new (SolarDawnAppWindow *win);

void enter_info_activated (SolarDawnAppWindow *win);

#endif
