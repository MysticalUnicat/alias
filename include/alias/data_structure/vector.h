#ifndef _ALIAS_DATA_STRUCTURE_VECTOR_H_
#define _ALIAS_DATA_STRUCTURE_VECTOR_H_

#include <stdint.h>

#include <alias/memory.h>

#define alias_Vector(T) struct { uint32_t capacity; uint32_t length; T * data; }

#endif
