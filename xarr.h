#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_XARR(typename, T)					\
struct typename								\
{									\
  T *front;								\
  T *back;								\
  size_t len;								\
  size_t capacity;							\
};									\
									\
struct typename								\
typename##_make ()							\
{									\
  struct typename xarr;							\
  xarr.front = malloc (sizeof (T));					\
  xarr.back = xarr.front;						\
  xarr.len = 0;								\
  xarr.capacity = 1;							\
  return xarr;								\
}									\
									\
 struct typename							\
 typename##_null ()							\
{									\
  struct typename xarr = {0, 0, 0, 0};					\
  return xarr;								\
}									\
									\
 bool typename##_is_null (struct typename xarr) {return xarr.front == NULL; } \
									\
 void									\
 typename##_insert (struct typename *xarr, T value)			\
{									\
  if (xarr->capacity < xarr->len + 1)					\
    {									\
      xarr->capacity <<= 1;						\
      xarr->front = realloc (xarr->front, xarr->capacity * sizeof (T));	\
      xarr->back = xarr->front + xarr->len;				\
    }									\
  xarr->len++;								\
  *(xarr->back++) = value;						\
}

#define fx(ai, xarr) for (__auto_type ai = xarr.front; ai != xarr.back; ai++)
