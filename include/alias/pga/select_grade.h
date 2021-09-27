#ifndef _ALIAS_PGA_SELECT_GRADE_H_
#define _ALIAS_PGA_SELECT_GRADE_H_

#include <alias/pga/unary.h>

#define ALIAS_PGA_UNARY_SELECT_GRADE_0(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ## __VA_ARGS__)
#define ALIAS_PGA_UNARY_SELECT_GRADE_1(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,B,C,D,E,0,0,0,0,0,0,0,0,0,0,0, ## __VA_ARGS__)
#define ALIAS_PGA_UNARY_SELECT_GRADE_2(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,F,G,H,I,J,K,0,0,0,0,0, ## __VA_ARGS__)
#define ALIAS_PGA_UNARY_SELECT_GRADE_3(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,0,0,0,0,0,0,L,M,N,O,0, ## __VA_ARGS__)
#define ALIAS_PGA_UNARY_SELECT_GRADE_4(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,P, ## __VA_ARGS__)

#endif

