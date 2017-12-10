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

#ifndef __SOLARDAWNAPPBUYPOWER_H
#define __SOLARDAWNAPPBUYPOWER_H

#include <gtk/gtk.h>
#include "solardawnappwin.h"

#define SOLARDAWN_APP_BUY_POWER_TYPE (solardawn_app_buy_power_get_type ())
G_DECLARE_FINAL_TYPE (SolarDawnAppBuyPower, solardawn_app_buy_power, SOLARDAWN, APP_BUY_POWER, GtkDialog)

SolarDawnAppBuyPower *solardawn_app_buy_power_new (SolarDawnAppWindow *win);

void buy_power_activated (SolarDawnAppWindow *win);

#endif
