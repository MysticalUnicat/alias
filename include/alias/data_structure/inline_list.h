// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALIAS_DATA_STRUCTURE_INLINE_LIST_H_
#define _ALIAS_DATA_STRUCTURE_INLINE_LIST_H_

#include <stdbool.h>

typedef struct alias_InlineList {
  struct alias_InlineList * prev;
  struct alias_InlineList * next;
} alias_InlineList;

#define ALIAS_INLINE_LIST_INIT(X) { .prev = &X, .next = &X }

#define ALIAS_INLINE_LIST_CONTAINER(ITEM, TYPE, MEMBER) ((TYPE *)((unsigned char *)(ITEM)) - offsetof(TYPE, MEMBER))

#define ALIAS_INLINE_LIST_EACH(LIST, ITEM) \
  for(ITEM = (LIST)->next; ITEM != (LIST); ITEM = ITEM->next)

#define ALIAS_INLINE_LIST_EACH_CONTAINER(LIST, ITEM, MEMBER)                        \
  for( ITEM = ALIAS_INLINE_LIST_CONTAINER((LIST)->next, typeof(*ITEM), MEMBER)      \
     ; &ITEM->MEMBER != (LIST)                                                      \
     ; ITEM = ALIAS_INLINE_LIST_CONTAINER(ITEM->MEMBER.next, typeof(*ITEM), MEMBER) \
     )

#define ALIAS_INLINE_LIST_EACH_CONTAINER_SAFE(LIST, ITEM, NEXT, MEMBER)             \
  for( ITEM = ALIAS_INLINE_LIST_CONTAINER((LIST)->next, typeof(*ITEM), MEMBER)      \
     , NEXT = ALIAS_INLINE_LIST_CONTAINER(ITEM->MEMBER.next, typeof(*ITEM), MEMBER) \
     ; &ITEM->MEMBER != (LIST)                                                      \
     ; ITEM = NEXT                                                                  \
     , NEXT = ALIAS_INLINE_LIST_CONTAINER(NEXT->MEMBER.next, typeof(*ITEM), MEMBER) \
     )

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

static inline void alias_InlineList_push_list(alias_InlineList * list, alias_InlineList * other) {
  alias_InlineList * prev = list->prev;
  alias_InlineList * next = list;
  alias_InlineList * frst = other->next;
  alias_InlineList * last = other->prev;
  frst->prev = prev;
  prev->next = frst;
  last->next = next;
  next->prev = last;
}

static inline void alias_InlineList_unshift_list(alias_InlineList * list, alias_InlineList * other) {
  alias_InlineList * prev = list;
  alias_InlineList * next = list->next;
  alias_InlineList * frst = other->next;
  alias_InlineList * last = other->prev;
  prev->next = frst;
  frst->prev = prev;
  next->prev = last;
  last->next = next;
}

#endif

