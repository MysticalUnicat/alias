#ifndef _ALIAS_DATA_STRUCTURE_INLINE_LIST_H_
#define _ALIAS_DATA_STRUCTURE_INLINE_LIST_H_

#include <stdbool.h>

typedef struct alias_InlineList {
  struct alias_InlineList * prev;
  struct alias_InlineList * next;
} alias_InlineList;

#define ALIAS_INLINE_LIST_INIT(X) { .prev = &X, .next = &X }

#define ALIAS_INLINE_LIST_CONTAINER(ITEM, TYPE, MEMBER) ((TYPE *)((unsigned char *)(ITEM)) - offsetof(TYPE, MEMBER))

static inline void alias_InlineList_init(alias_InlineList * list) {
  list->next = list;
  list->prev = list;
}

static inline bool alias_InlineList_is_empty(alias_InlineList * list) {
  return list->next == list->prev && list->next == list;
}

static inline void alias_InlineList_remove_self(alias_InlineList * item) {
  item->next->prev = item->prev;
  item->prev->next = item->next;
}

static inline void alias_InlineList_push(alias_InlineList * list, alias_InlineList * item) {
  alias_InlineList * prev = list->prev, * next = list;
  next->prev = item;
  prev->next = item;
  item->next = next;
  item->prev = prev;
}

static inline void alias_InlineList_unshift(alias_InlineList * list, alias_InlineList * item) {
  alias_InlineList * prev = list, * next = list->next;
  next->prev = item;
  prev->next = item;
  item->next = next;
  item->prev = prev;
}

static inline alias_InlineList * alias_InlineList_pop(alias_InlineList * list) {
  alias_InlineList * item = list->prev;
  alias_InlineList_remove_self(item);
  alias_InlineList_init(item);
  return item;
}

static inline alias_InlineList * alias_InlineList_shift(alias_InlineList * list) {
  alias_InlineList * item = list->next;
  alias_InlineList_remove_self(item);
  alias_InlineList_init(item);
  return item;
}

#endif

