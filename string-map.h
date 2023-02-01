/*
  Copyright (C) 2022 Miguel Ángel Martínez Quevedo
  
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
*/

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DECLARE_STRING_MAP(typename, T)					\
  struct typename;

#define DEFINE_STRING_MAP(typename, T)					\
  struct typename							\
  {									\
    T value;								\
    bool has_value;							\
    struct typename *transition[256];					\
  };									\
  struct typename*							\
  typename##_new ()							\
  {									\
    struct typename *map = malloc (sizeof (struct typename));		\
    memset (map->transition, 0, sizeof (map->transition));		\
    map->has_value = 0;							\
    return map;								\
  }									\
									\
  struct typename*							\
  typename##_search_node (struct typename *map, const char *str)		\
  {									\
    for (; *str; str++)							\
      {									\
	struct typename *next = map->transition[(int)*str];		\
	if (next) map = next;						\
	else return NULL;						\
      }									\
    assert (!*str);							\
    return map->has_value? map : NULL;					\
  }									\
									\
  struct typename *							\
  typename##_search_node_brange (struct typename *map, const char *beg, const char *end) \
  {									\
    for (; beg != end; beg++)						\
      {									\
	struct typename *next = map->transition[(int)*beg];		\
	if (next) map = next;						\
	else return NULL;						\
      }									\
    assert (beg == end);						\
    return map->has_value? map : NULL;					\
  }									\
									\
  int									\
  typename##_search (struct typename *map, const char *str, T* value)		\
  {									\
    map = typename##_search_node (map, str);				\
    if (map && map->has_value)						\
      {									\
	*value = map->value;						\
	return 1;							\
      }									\
    return 0;								\
  }									\
									\
  struct typename *							\
  typename##_set (struct typename *map, const char *str, T value)		\
  {									\
    for (; *str; str++)							\
      {									\
	if (!map->transition[(int)*str])				\
	  {								\
	    map->transition[(int)*str] = typename##_new ();		\
	  }								\
	map = map->transition[(int)*str];				\
      }									\
    assert (!*str);							\
    map->has_value = true;						\
    map->value = value;							\
    return map;								\
  }									\
  struct typename *							\
  typename##_set_brange (struct typename *map, const char *beg, const char *end, T value) \
  {									\
    for (; beg != end; beg++)						\
      {									\
	if (!map->transition[(int)*beg])				\
	  {								\
	    map->transition[(int)*beg] = typename##_new ();		\
	  }								\
	map = map->transition[(int)*beg];				\
      }									\
    assert (beg == end);						\
    map->has_value = true;						\
    map->value = value;							\
    return map;								\
  }
