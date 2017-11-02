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

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int update_db () {
  sqlite3* sqlite_db = NULL;
  sqlite3_stmt* query = NULL;
  int ret = 0;

  if (SQLITE_OK != (ret = sqlite3_open(":memory:", &sqlite_db))) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(sqlite_db));
    sqlite3_close(sqlite_db);
    return 1;
  }

  if (SQLITE_OK != (ret = sqlite3_prepare_v2(sqlite_db, "SELECT SQLITE_VERSION()", -1, &query, 0))) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(sqlite_db));
    sqlite3_close(sqlite_db);
    return 1;
  }

  if (SQLITE_OK != (ret = sqlite3_prepare_v2(sqlite_db, "SELECT TEST", -1, &query, NULL))) {
      printf("Failed to prepare insert: %d, %s\n", ret, sqlite3_errmsg(sqlite_db));
      return 1;
  }

  if (SQLITE_ROW != (ret = sqlite3_step(query))) {
      printf("Failed to step: %d, %s\n", ret, sqlite3_errmsg(sqlite_db));
      return 1;
  }
  // ... and print the value of column 0 (expect 2012 here)
  printf("Value from sqlite: %s", sqlite3_column_text(query, 0));


  if (NULL != query) sqlite3_finalize(query);
  if (NULL != sqlite_db) sqlite3_close(sqlite_db);
  sqlite3_shutdown();
  return ret;
}
