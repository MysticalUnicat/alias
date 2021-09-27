#ifndef _ALIAS_PGA_GEOMETRIC_PRODUCT_H_
#define _ALIAS_PGA_GEOMETRIC_PRODUCT_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

#define ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_ADD_MUL,ALIAS_PGA_RZ_SUBTRACT_MUL,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT_(RETURN, One,E0,E1,E2,E3,E01,E02,E03,E12,E31,E23,E021,E013,E032,E123,E0123, one,e0,e1,e2,e3,e01,e02,e03,e12,e31,e23,e021,e013,e032,e123,e0123, P,M, ...) \
  RETURN( \
    0 P(One, one)               P(E1, e1)    P(E2, e2)    P(E3, e3)                                           M(E12, e12)   M(E31, e31)   M(E23, e23)                                             M(E123, e123)                 \
  , 0 P(One, e0)    P(E0, one)  M(E1, e01)   M(E2, e02)   M(E3, e03)   P(E01, e1)   M(E02, e2)   P(E03, e3)   P(E12, e021)  P(E31, e013)  P(E23, e032)  P(E021, e12)  P(E013, e31)  M(E032, e23)  P(E123, e0123) M(E0123, e123) \
  , 0 P(One, e1)                P(E1, one)   M(E2, e12)   P(E3, e31)                                          P(E12, e2)    M(E31, e3)    M(E23, e123)                                            M(E123, e23)                  \
  , 0 P(One, e2)                P(E1, e12)   P(E2, one)   M(E3, e23)                                          M(E12, e1)    M(E31, e123)  P(E23, e3)                                              M(E123, e31)                  \
  , 0 P(One, e3)                M(E1, e31)   P(E2, e23)   P(E3, one)                                          M(E12, e123)  P(E31, e1)    M(E23, e2)                                              M(E123, e12)                  \
  , 0 P(One, e01)   P(E0, e1)   M(E1, e0)    M(E2, e021)  P(E3, e013)  P(E01, one)  M(E02, e12)  P(E03, e31)  P(E12, e02)   M(E31, e03)   M(E23, e0123) M(E021, e2)   P(E013, e3)   P(E032, e123) M(E123, e032)  M(E0123, e23)  \
  , 0 P(One, e02)   P(E0, e2)   P(E1, e021)  M(E2, e0)    M(E3, e032)  P(E01, e12)  P(E02, one)  M(E03, e23)  M(E12, e01)   M(E31, e0123) P(E23, e03)   P(E021, e1)   P(E013, e123) M(E032, e3)   M(E123, e013)  M(E0123, e31)  \
  , 0 P(One, e03)   P(E0, e3)   M(E1, e013)  P(E2, e032)  M(E3, e0)    M(E01, e31)  P(E02, e23)  P(E03, one)  M(E12, e0123) P(E31, e01)   M(E23, e02)   P(E021, e123) M(E013, e1)   P(E032, e2)   M(E123, e021)  M(E0123, e12)  \
  , 0 P(One, e12)               P(E1, e2)    M(E2, e1)    P(E3, e123)                                         P(E12, one)   P(E31, e23)   M(E23, e31)                                             P(E123, e3)                   \
  , 0 P(One, e31)               M(E1, e3)    P(E2, e123)  P(E3, e1)                                           M(E12, e23)   P(E31, one)   P(E23, e12)                                             P(E123, e2)                   \
  , 0 P(One, e23)               P(E1, e123)  M(E2, e3)    M(E3, e2)                                           P(E12, e31)   M(E31, e12)   P(E23, one)                                             P(E123, e1)                   \
  , 0 P(One, e021)  M(E0, e12)  P(E1, e02)   M(E2, e01)   P(E3, e0123) M(E01, e2)   P(E02, e1)   M(E03, e123) M(E12, e0)    P(E31, e032)  M(E23, e013)  P(E021, one)  P(E013, e23)  M(E032, e31)  P(E123, e03)   M(E0123, e3)   \
  , 0 P(One, e013)  M(E0, e31)  M(E1, e03)   P(E2, e0123) P(E3, e01)   P(E01, e3)   M(E02, e123) M(E03, e1)   M(E12, e032)  M(E31, e0)    P(E23, e021)  M(E021, e23)  P(E013, one)  M(E032, e12)  P(E123, e02)   M(E0123, e2)   \
  , 0 P(One, e032)  M(E0, e23)  P(E1, e0123) M(E2, e03)   M(E3, e02)   M(E01, e123) M(E02, e3)   P(E03, e2)   P(E12, e013)  M(E31, e021)  M(E23, e0)    P(E021, e31)  M(E013, e12)  P(E032, one)  P(E123, e01)   M(E0123, e1)   \
  , 0 P(One, e123)              P(E1, e23)   P(E2, e31)   P(E3, e12)                                          P(E12, e3)    P(E31, e2)    P(E23, e1)                                              P(E123, one)                  \
  , 0 P(One, e0123) P(E0, e123) P(E1, e032)  P(E2, e013)  P(E3, e021)  P(E01, e23)  P(E02, e31)  P(E03, e12)  P(E12, e03)   P(E31, e02)   P(E23, e01)   M(E021, e3)   M(E013, e2)   M(E032, e1)   M(E123, e0)    P(E0123, one)  \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT2(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT2_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_ADD_MUL,ALIAS_PGA_RZ_SUBTRACT_MUL,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT2_(RETURN, One,E0,E1,E2,E3,E01,E02,E03,E12,E31,E23,E021,E013,E032,E123,E0123, one,e0,e1,e2,e3,e01,e02,e03,e12,e31,e23,e021,e013,e032,e123,e0123, P,M, ...) \
  RETURN( \
    0 P(One, one)               P(E1, e1)    P(E2, e2)    P(E3, e3)                                           M(E12, e12)   M(E31, e31)   M(E23, e23)                                             M(E123, e123)                 \
  , 0 P(One, e0)    P(E0, one)  M(E1, e01)   M(E2, e02)   M(E3, e03)   P(E01, e1)   M(E02, e2)   P(E03, e3)   P(E12, e021)  P(E31, e013)  P(E23, e032)  P(E021, e12)  P(E013, e31)  M(E032, e23)  P(E123, e0123) M(E0123, e123) \
  , 0 P(One, e1)                P(E1, one)   M(E2, e12)   P(E3, e31)                                          P(E12, e2)    M(E31, e3)    M(E23, e123)                                            M(E123, e23)                  \
  , 0 P(One, e2)                P(E1, e12)   P(E2, one)   M(E3, e23)                                          M(E12, e1)    M(E31, e123)  P(E23, e3)                                              M(E123, e31)                  \
  , 0 P(One, e3)                M(E1, e31)   P(E2, e23)   P(E3, one)                                          M(E12, e123)  P(E31, e1)    M(E23, e2)                                              M(E123, e12)                  \
  , 0 P(One, e01)   P(E0, e1)   M(E1, e0)    M(E2, e021)  P(E3, e013)  P(E01, one)  M(E02, e12)  P(E03, e31)  P(E12, e02)   M(E31, e03)   M(E23, e0123) M(E021, e2)   P(E013, e3)   P(E032, e123) M(E123, e032)  M(E0123, e23)  \
  , 0 P(One, e02)   P(E0, e2)   P(E1, e021)  M(E2, e0)    M(E3, e032)  P(E01, e12)  P(E02, one)  M(E03, e23)  M(E12, e01)   M(E31, e0123) P(E23, e03)   P(E021, e1)   P(E013, e123) M(E032, e3)   M(E123, e013)  M(E0123, e31)  \
  , 0 P(One, e03)   P(E0, e3)   M(E1, e013)  P(E2, e032)  M(E3, e0)    M(E01, e31)  P(E02, e23)  P(E03, one)  M(E12, e0123) P(E31, e01)   M(E23, e02)   P(E021, e123) M(E013, e1)   P(E032, e2)   M(E123, e021)  M(E0123, e12)  \
  , 0 P(One, e12)               P(E1, e2)    M(E2, e1)    P(E3, e123)                                         P(E12, one)   P(E31, e23)   M(E23, e31)                                             P(E123, e3)                   \
  , 0 P(One, e31)               M(E1, e3)    P(E2, e123)  P(E3, e1)                                           M(E12, e23)   P(E31, one)   P(E23, e12)                                             P(E123, e2)                   \
  , 0 P(One, e23)               P(E1, e123)  M(E2, e3)    M(E3, e2)                                           P(E12, e31)   M(E31, e12)   P(E23, one)                                             P(E123, e1)                   \
  , 0 P(One, e021)  M(E0, e12)  P(E1, e02)   M(E2, e01)   P(E3, e0123) M(E01, e2)   P(E02, e1)   M(E03, e123) M(E12, e0)    P(E31, e032)  M(E23, e013)  P(E021, one)  P(E013, e23)  M(E032, e31)  P(E123, e03)   M(E0123, e3)   \
  , 0 P(One, e013)  M(E0, e31)  M(E1, e03)   P(E2, e0123) P(E3, e01)   P(E01, e3)   M(E02, e123) M(E03, e1)   M(E12, e032)  M(E31, e0)    P(E23, e021)  M(E021, e23)  P(E013, one)  M(E032, e12)  P(E123, e02)   M(E0123, e2)   \
  , 0 P(One, e032)  M(E0, e23)  P(E1, e0123) M(E2, e03)   M(E3, e02)   M(E01, e123) M(E02, e3)   P(E03, e2)   P(E12, e013)  M(E31, e021)  M(E23, e0)    P(E021, e31)  M(E013, e12)  P(E032, one)  P(E123, e01)   M(E0123, e1)   \
  , 0 P(One, e123)              P(E1, e23)   P(E2, e31)   P(E3, e12)                                          P(E12, e3)    P(E31, e2)    P(E23, e1)                                              P(E123, one)                  \
  , 0 P(One, e0123) P(E0, e123) P(E1, e032)  P(E2, e013)  P(E3, e021)  P(E01, e23)  P(E02, e31)  P(E03, e12)  P(E12, e03)   P(E31, e02)   P(E23, e01)   M(E021, e3)   M(E013, e2)   M(E032, e1)   M(E123, e0)    P(E0123, one)  \
  , ## __VA_ARGS__ \
  )

#endif

