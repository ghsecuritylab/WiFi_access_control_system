/*
 *  Variable implementation in finsh shell.
 *
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 * 2012-04-27     Bernard      fixed finsh_var_delete issue which
 *                             is found by Grissiom.
 */
#include <finsh.h>
#include "finsh_var.h"

struct finsh_var global_variable[FINSH_VARIABLE_MAX];
struct finsh_sysvar_item* global_sysvar_list;

int finsh_var_init()
{
    memset(global_variable, 0, sizeof(global_variable));

    return 0;
}

int finsh_var_insert(const char* name, int type)
{
    int i, empty;

    empty = -1;
    for (i = 0; i < FINSH_VARIABLE_MAX; i ++)
    {
        /* there is a same name variable exist. */
        if (strncmp(global_variable[i].name, name, FINSH_NAME_MAX) == 0)
            return -1;

        if (global_variable[i].type == finsh_type_unknown && empty == -1)
        {
            empty = i;
        }
    }

    /* there is no empty entry */
    if (empty == -1) return -1;

    /* insert entry */
    strncpy(global_variable[empty].name, name, FINSH_NAME_MAX);
    global_variable[empty].type = type;

    /* return the offset */
    return empty;
}

int finsh_var_delete(const char* name)
{
    int i;

    for (i = 0; i < FINSH_VARIABLE_MAX; i ++)
    {
        if (strncmp(global_variable[i].name, name, FINSH_NAME_MAX) == 0)
            break;
    }

    /* can't find variable */
    if (i == FINSH_VARIABLE_MAX) return -1;

    memset(&global_variable[i], 0, sizeof(struct finsh_var));

    return 0;
}

struct finsh_var* finsh_var_lookup(const char* name)
{
    int i;

    for (i = 0; i < FINSH_VARIABLE_MAX; i ++)
    {
        if (strncmp(global_variable[i].name, name, FINSH_NAME_MAX) == 0)
            break;
    }

    /* can't find variable */
    if (i == FINSH_VARIABLE_MAX) return NULL;

    return &global_variable[i];
}

#ifdef RT_USING_HEAP
void finsh_sysvar_append(const char* name, u_char type, void* var_addr)
{
    /* create a sysvar */
    struct finsh_sysvar_item* item;

    item = (struct finsh_sysvar_item*) rt_malloc (sizeof(struct finsh_sysvar_item));
    if (item != NULL)
    {
        item->next = NULL;
        item->sysvar.name = rt_strdup(name);
        item->sysvar.type = type;
        item->sysvar.var = var_addr;

        if (global_sysvar_list == NULL)
        {
            global_sysvar_list = item;
        }
        else
        {
            item->next = global_sysvar_list;
            global_sysvar_list = item;
        }
    }
}
#endif

struct finsh_sysvar* finsh_sysvar_lookup(const char* name)
{
    struct finsh_sysvar* index;
    struct finsh_sysvar_item* item;

    for (index = _sysvar_table_begin;
         index < _sysvar_table_end;
         FINSH_NEXT_SYSVAR(index))
    {
        if (strcmp(index->name, name) == 0)
            return index;
    }

    /* find in sysvar list */
    item = global_sysvar_list;
    while (item != NULL)
    {
        if (strncmp(item->sysvar.name, name, strlen(name)) == 0)
        {
            return &(item->sysvar);
        }

        /* move to next item */
        item = item->next;
    }

    /* can't find variable */
    return NULL;
}
