/* replacement of a few functions that are not so great on windows CRT
 * 
 * an attempt to normalize behavior, breaking api to have additional safety
 * 
 * a nice confortable white t-shirt.
 * 
 * general:
 *  - Normalize: UTF-8 support by default
 *
 * printf family:
 *  - Behavior:  microsoft vs posix.
 *  - Behavior:  mingw sometimes uses an older version of microsoft CRT.
 *  - Normalize: may be minor differences that effect text matching and types (why we need PRI macros)
 *  - Normalize: missing asprintf in many places
 *  - Safety:    sprintf and snprintf do not bounds check the destination buffer
 * 
 */

#ifndef _TABULA_H_
#define _TABULA_H_

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#if 0
#include <uchar.h>
#else
typedef uint16_t tabula_char16_t;
typedef uint32_t tabula_char32_t;

#define char16_t tabula_char16_t;
#define char32_t tabula_char32_t;

// missing:
//  - mbstate_t
//  - mbrtoc16
//  - c16rtomb
//  - mbrtoc32
//  - c32rtomb
//  - mbrtoc8
//  - c8rtomb
#endif
