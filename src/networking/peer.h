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

#ifndef __PEER_H
#define __PEER_H

#include "data.h"

#define WATCHER_PORT 8080

void create_room_request         ();
void request_available_rooms     ();
void get_room_info               ();
void receive_packet              ();
void leave_room_request          ();

void *read_input                 (void *ptr);
void join_room_request           (int new_room_num);
void send_message                (char *msg);
void create_room_reply           (packet *pkt);
void join_room_reply             (packet *pkt);
void leave_room_reply            (packet *pkt);
void user_connection_updates     (packet *pkt);
void receive_available_producers (packet *pkt);
void receive_power               (struct sockaddr_in *sender_addr, packet *pkt);
void reply_to_ping               (struct sockaddr_in *sender_addr);

#endif
