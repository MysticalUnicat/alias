#ifndef _ALIAS_PGA_REGRESSIVE_PRODUCT_H_
#define _ALIAS_PGA_REGRESSIVE_PRODUCT_H_

#include <alias/pga/real.h>
#include <alias/pga/binary.h>

// perform duals in return order and argument passing
// outer product body
#define ALIAS_PGA_BINARY_REGRESSIVE_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_BINARY_REGRESSIVE_PRODUCT_(RETURN, P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A, p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a, ALIAS_PGA_RZ_ADD_MUL,ALIAS_PGA_RZ_SUBTRACT_MUL,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_REGRESSIVE_PRODUCT_(RETURN, One,E0,E1,E2,E3,E01,E02,E03,E12,E31,E23,E021,E013,E032,E123,E0123, one,e0,e1,e2,e3,e01,e02,e03,e12,e31,e23,e021,e013,e032,e123,e0123, P,M, ...) \
  RETURN( \
    0 P(One, e0123) P(E0, e123) P(E1, e032)  P(E2, e013)  P(E3, e021)  P(E01, e23)  P(E02, e31)  P(E03, e12)  P(E12, e03)   P(E31, e02)   P(E23, e01)   M(E021, e3)   M(E013, e2)   M(E032, e1)   M(E123, e0)    P(E0123, one) \
  , 0 P(One, e123)              P(E1, e23)   P(E2, e31)   P(E3, e12)                                          P(E12, e3)    P(E31, e2)    P(E23, e1)                                              P(E123, one) \
  , 0 P(One, e032)  M(E0, e23)               M(E2, e03)   M(E3, e02)                M(E02, e3)   P(E03, e2)                               M(E23, e0)                                P(E032, one) \
  , 0 P(One, e013)  M(E0, e31)  M(E1, e03)                P(E3, e01)   P(E01, e3)                M(E03, e1)                 M(E31, e0)                                P(E013, one) \
  , 0 P(One, e021)  M(E0, e12)  P(E1, e02)   M(E2, e01)                M(E01, e2)   P(E02, e1)                M(E12, e0)                                P(E021, one) \
  , 0 P(One, e23)                            M(E2, e3)    M(E3, e2)                                                                       P(E23, one) \
  , 0 P(One, e31)               M(E1, e3)                 P(E3, e1)                                                         P(E31, one) \
  , 0 P(One, e12)               P(E1, e2)    M(E2, e1)                                                        P(E12, one) \
  , 0 P(One, e03)   P(E0, e3)                             M(E3, e0)                              P(E03, one) \
  , 0 P(One, e02)   P(E0, e2)                M(E2, e0)                              P(E02, one) \
  , 0 P(One, e01)   P(E0, e1)   M(E1, e0)                              P(E01, one) \
  , 0 P(One, e3)                                          P(E3, one) \
  , 0 P(One, e2)                             P(E2, one) \
  , 0 P(One, e1)                P(E1, one) \
  , 0 P(One, e0)    P(E0, one) \
  , 0 P(One, one) \
  , ## __VA_ARGS__ \
  )

#endif

