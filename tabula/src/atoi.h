// atoi
intmax_t tabula_atoi(const char * restrict in, const char ** restrict out_ptr);
uintmax_t tabula_atou(const char * restrict in, const char ** restrict out_ptr);

#ifndef TABULA_NO_REPLACEMENT_MACROS
#define atoi tabula_atoi
#define atou tabula_atou
#endif

