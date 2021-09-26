#ifndef _ALIAS_PGA_COMMUTATOR_PRODUCT_H_
#define _ALIAS_PGA_COMMUTATOR_PRODUCT_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_ADD_MUL,ALIAS_PGA_RZ_SUBTRACT_MUL,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, P_,M_, ...) \
  RETURN( \
   0 \
 , 0 P_(F,c) M_(E,h) P_(C,f) P_(H,e) P_(K,n) M_(N,k) P_(O,p) M_(P,o) \
 , 0 P_(E,j) M_(D,i) P_(I,d) M_(J,e) \
 , 0 P_(C,i) M_(E,k) M_(I,c) P_(K,e) \
 , 0 P_(D,k) M_(C,j) P_(J,c) M_(K,d) \
 , 0 P_(B,c) M_(C,b) M_(G,i) P_(H,j) P_(I,g) M_(J,h) P_(N,o) M_(O,n) \
 , 0 P_(B,d) M_(D,b) P_(F,i) M_(H,k) M_(I,f) P_(K,h) P_(M,o) M_(O,m) \
 , 0 P_(B,e) M_(E,b) M_(F,j) P_(G,k) P_(J,f) M_(K,g) P_(L,o) M_(O,l) \
 , 0 P_(C,d) M_(D,c) P_(J,k) M_(K,j) \
 , 0 P_(E,c) M_(C,e) M_(I,k) P_(K,i) \
 , 0 P_(I,j) M_(J,i) \
 , 0 P_(E,p) M_(H,o) P_(J,n) M_(K,m) P_(M,k) M_(N,j) P_(O,h) M_(P,e) \
 , 0 P_(D,p) M_(G,o) P_(K,l) M_(L,k) P_(O,g) M_(P,d) \
 , 0 P_(C,p) M_(D,h) M_(F,o) P_(H,d) P_(I,m) M_(J,l) P_(L,j) M_(M,i) P_(O,f) M_(P,c) \
 , 0 \
 , 0 P_(B,o) P_(C,n) P_(D,m) P_(E,l) M_(L,e) M_(M,d) M_(N,c) M_(O,b) \
 , ## __VA_ARGS__ \
 )

ALIAS_PGA_GENERATE_BINARY_FUNCTIONS(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT, commutator_product)

#define alias_pga_commutator_product(A, B) ALIAS_PGA_USE_BINARY(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT, commutator_product, A, B)

#endif

