#ifndef _ALIAS_PGA_SANDWICH_H_
#define _ALIAS_PGA_SANDWICH_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

#include <alias/pga/geometric_product.h>
#include <alias/pga/reverse.h>

#define ALIAS_PGA_SANDWICH(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT(ALIAS_PGA_SANDWICH_1, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, RETURN,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,##__VA_ARGS__)
#define ALIAS_PGA_SANDWICH_1(Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp, RETURN,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,...) ALIAS_PGA_UNARY_REVERSE(ALIAS_PGA_SANDWICH_2, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp,##__VA_ARGS__)
#define ALIAS_PGA_SANDWICH_2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp,...) ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT2(ALIAS_PGA_SANDWICH_3, Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,##__VA_ARGS__)
#define ALIAS_PGA_SANDWICH_3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,...) RETURN(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,##__VA_ARGS__)

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_SANDWICH, sandwich)

#define alias_pga_sandwich(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_SANDWICH, sandwich, A, B)

#endif

