#ifndef _ALIAS_PGA_COMMUTATOR_PRODUCT_H_
#define _ALIAS_PGA_COMMUTATOR_PRODUCT_H_

#include <alias/pga/real.h>
#include <alias/pga/geometric_product.h>
#include <alias/pga/subtract.h>

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

#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_1, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, RETURN,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_1(Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp, RETURN,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  ALIAS_PGA_BINARY_GEOMETRIC_PRODUCT2(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_2, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_2(aA,bB,cC,dD,eE,fF,gG,hH,iI,jJ,kK,lL,mM,nN,oO,pP, RETURN,Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp, ...) \
  ALIAS_PGA_BINARY_SUBTRACT(ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_3, Aa,Bb,Cc,Dd,Ee,Ff,Gg,Hh,Ii,Jj,Kk,Ll,Mm,Nn,Oo,Pp, aA,bB,cC,dD,eE,fF,gG,hH,iI,jJ,kK,lL,mM,nN,oO,pP, RETURN,## __VA_ARGS__)
#define ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT_3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, RETURN,...) \
  RETURN( \
      ALIAS_PGA_RZ_MUL(A, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(B, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(C, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(D, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(E, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(F, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(G, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(H, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(I, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(J, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(K, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(L, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(M, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(N, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(O, (alias_R)(0.5)) \
    , ALIAS_PGA_RZ_MUL(P, (alias_R)(0.5)) \
    , ## __VA_ARGS__ \
    )

/* ALIAS_PGA_BINARY_COMMUTATOR_PRODUCT(cp, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, extra)
cp(
    ((0 +((A)*(a)) +((C)*(c)) +((D)*(d)) +((E)*(e)) -((I)*(i)) -((J)*(j)) -((K)*(k)) -((O)*(o)))  -  (0 +((a)*(A)) +((c)*(C)) +((d)*(D)) +((e)*(E)) -((i)*(I)) -((j)*(J)) -((k)*(K)) -((o)*(O))))*((alias_R)(0.5))
  , ((0 +((A)*(b)) +((B)*(a)) -((C)*(f)) -((D)*(g)) -((E)*(h)) +((F)*(c)) -((G)*(d)) +((H)*(e)) +((I)*(l)) +((J)*(m)) +((K)*(n)) +((L)*(i)) +((M)*(j)) -((N)*(k)) +((O)*(p)) -((P)*(o)))  -  (0 +((a)*(B)) +((b)*(A)) -((c)*(F)) -((d)*(G)) -((e)*(H)) +((f)*(C)) -((g)*(D)) +((h)*(E)) +((i)*(L)) +((j)*(M)) +((k)*(N)) +((l)*(I)) +((m)*(J)) -((n)*(K)) +((o)*(P)) -((p)*(O))))*((alias_R)(0.5))
  , ((0 +((A)*(c)) +((C)*(a)) -((D)*(i)) +((E)*(j)) +((I)*(d)) -((J)*(e)) -((K)*(o)) -((O)*(k)))-(0 +((a)*(C)) +((c)*(A)) -((d)*(I)) +((e)*(J)) +((i)*(D)) -((j)*(E)) -((k)*(O)) -((o)*(K))))*((alias_R)(0.5))
  , ((0 +((A)*(d)) +((C)*(i)) +((D)*(a)) -((E)*(k)) -((I)*(c)) -((J)*(o)) +((K)*(e)) -((O)*(j)))-(0 +((a)*(D)) +((c)*(I)) +((d)*(A)) -((e)*(K)) -((i)*(C)) -((j)*(O)) +((k)*(E)) -((o)*(J))))*((alias_R)(0.5))
  , ((0 +((A)*(e)) -((C)*(j)) +((D)*(k)) +((E)*(a)) -((I)*(o)) +((J)*(c)) -((K)*(d)) -((O)*(i)))-(0 +((a)*(E)) -((c)*(J)) +((d)*(K)) +((e)*(A)) -((i)*(O)) +((j)*(C)) -((k)*(D)) -((o)*(I))))*((alias_R)(0.5))
  , ((0 +((A)*(f)) +((B)*(c)) -((C)*(b)) -((D)*(l)) +((E)*(m)) +((F)*(a)) -((G)*(i)) +((H)*(j)) +((I)*(g)) -((J)*(h)) -((K)*(p)) -((L)*(d)) +((M)*(e)) +((N)*(o)) -((O)*(n)) -((P)*(k)))-(0 +((a)*(F)) +((b)*(C)) -((c)*(B)) -((d)*(L)) +((e)*(M)) +((f)*(A)) -((g)*(I)) +((h)*(J)) +((i)*(G)) -((j)*(H)) -((k)*(P)) -((l)*(D)) +((m)*(E)) +((n)*(O)) -((o)*(N)) -((p)*(K))))*((alias_R)(0.5))
  , ((0 +((A)*(g)) +((B)*(d)) +((C)*(l)) -((D)*(b)) -((E)*(n)) +((F)*(i)) +((G)*(a)) -((H)*(k)) -((I)*(f)) -((J)*(p)) +((K)*(h)) +((L)*(c)) +((M)*(o)) -((N)*(e)) -((O)*(m)) -((P)*(j)))-(0 +((a)*(G)) +((b)*(D)) +((c)*(L)) -((d)*(B)) -((e)*(N)) +((f)*(I)) +((g)*(A)) -((h)*(K)) -((i)*(F)) -((j)*(P)) +((k)*(H)) +((l)*(C)) +((m)*(O)) -((n)*(E)) -((o)*(M)) -((p)*(J))))*((alias_R)(0.5))
  , ((0 +((A)*(h)) +((B)*(e)) -((C)*(m)) +((D)*(n)) -((E)*(b)) -((F)*(j)) +((G)*(k)) +((H)*(a)) -((I)*(p)) +((J)*(f)) -((K)*(g)) +((L)*(o)) -((M)*(c)) +((N)*(d)) -((O)*(l)) -((P)*(i)))-(0 +((a)*(H)) +((b)*(E)) -((c)*(M)) +((d)*(N)) -((e)*(B)) -((f)*(J)) +((g)*(K)) +((h)*(A)) -((i)*(P)) +((j)*(F)) -((k)*(G)) +((l)*(O)) -((m)*(C)) +((n)*(D)) -((o)*(L)) -((p)*(I))))*((alias_R)(0.5))
  , ((0 +((A)*(i)) +((C)*(d)) -((D)*(c)) +((E)*(o)) +((I)*(a)) +((J)*(k)) -((K)*(j)) +((O)*(e)))-(0 +((a)*(I)) +((c)*(D)) -((d)*(C)) +((e)*(O)) +((i)*(A)) +((j)*(K)) -((k)*(J)) +((o)*(E))))*((alias_R)(0.5))
  , ((0 +((A)*(j)) -((C)*(e)) +((D)*(o)) +((E)*(c)) -((I)*(k)) +((J)*(a)) +((K)*(i)) +((O)*(d)))-(0 +((a)*(J)) -((c)*(E)) +((d)*(O)) +((e)*(C)) -((i)*(K)) +((j)*(A)) +((k)*(I)) +((o)*(D))))*((alias_R)(0.5))
  , ((0 +((A)*(k)) +((C)*(o)) -((D)*(e)) -((E)*(d)) +((I)*(j)) -((J)*(i)) +((K)*(a)) +((O)*(c)))-(0 +((a)*(K)) +((c)*(O)) -((d)*(E)) -((e)*(D)) +((i)*(J)) -((j)*(I)) +((k)*(A)) +((o)*(C))))*((alias_R)(0.5))
  , ((0 +((A)*(l)) -((B)*(i)) +((C)*(g)) -((D)*(f)) +((E)*(p)) -((F)*(d)) +((G)*(c)) -((H)*(o)) -((I)*(b)) +((J)*(n)) -((K)*(m)) +((L)*(a)) +((M)*(k)) -((N)*(j)) +((O)*(h)) -((P)*(e)))-(0 +((a)*(L)) -((b)*(I)) +((c)*(G)) -((d)*(F)) +((e)*(P)) -((f)*(D)) +((g)*(C)) -((h)*(O)) -((i)*(B)) +((j)*(N)) -((k)*(M)) +((l)*(A)) +((m)*(K)) -((n)*(J)) +((o)*(H)) -((p)*(E))))*((alias_R)(0.5))
  , ((0 +((A)*(m)) -((B)*(j)) -((C)*(h)) +((D)*(p)) +((E)*(f)) +((F)*(e)) -((G)*(o)) -((H)*(c)) -((I)*(n)) -((J)*(b)) +((K)*(l)) -((L)*(k)) +((M)*(a)) -((N)*(i)) +((O)*(g)) -((P)*(d)))-(0 +((a)*(M)) -((b)*(J)) -((c)*(H)) +((d)*(P)) +((e)*(F)) +((f)*(E)) -((g)*(O)) -((h)*(C)) -((i)*(N)) -((j)*(B)) +((k)*(L)) -((l)*(K)) +((m)*(A)) -((n)*(I)) +((o)*(G)) -((p)*(D))))*((alias_R)(0.5))
  , ((0 +((A)*(n)) -((B)*(k)) +((C)*(p)) -((D)*(h)) -((E)*(g)) -((F)*(o)) -((G)*(e)) +((H)*(d)) +((I)*(m)) -((J)*(l)) -((K)*(b)) +((L)*(j)) -((M)*(i)) +((N)*(a)) +((O)*(f)) -((P)*(c)))-(0 +((a)*(N)) -((b)*(K)) +((c)*(P)) -((d)*(H)) -((e)*(G)) -((f)*(O)) -((g)*(E)) +((h)*(D)) +((i)*(M)) -((j)*(L)) -((k)*(B)) +((l)*(J)) -((m)*(I)) +((n)*(A)) +((o)*(F)) -((p)*(C))))*((alias_R)(0.5))
  , ((0 +((A)*(o)) +((C)*(k)) +((D)*(j)) +((E)*(i)) +((I)*(e)) +((J)*(d)) +((K)*(c)) +((O)*(a)))-(0 +((a)*(O)) +((c)*(K)) +((d)*(J)) +((e)*(I)) +((i)*(E)) +((j)*(D)) +((k)*(C)) +((o)*(A))))*((alias_R)(0.5))
  , ((0 +((A)*(p)) +((B)*(o)) +((C)*(n)) +((D)*(m)) +((E)*(l)) +((F)*(k)) +((G)*(j)) +((H)*(i)) +((I)*(h)) +((J)*(g)) +((K)*(f)) -((L)*(e)) -((M)*(d)) -((N)*(c)) -((O)*(b)) +((P)*(a)))-(0 +((a)*(P)) +((b)*(O)) +((c)*(N)) +((d)*(M)) +((e)*(L)) +((f)*(K)) +((g)*(J)) +((h)*(I)) +((i)*(H)) +((j)*(G)) +((k)*(F)) -((l)*(E)) -((m)*(D)) -((n)*(C)) -((o)*(B)) +((p)*(A))))*((alias_R)(0.5))
  , extra
  )
*/

RETURN( \
    0 \
  , ((A*b) + (B*a) - (C*f) - (D*g) - (E*h) + (F*c) - (G*d) + (H*e) + (I*l) + (J*m) + (K*n) + (L*i) + (M*j) - (N*k) + (O*p) - (P*o) - (a*B) - (b*A) + (c*F) + (d*G) + (e*H) - (f*C) + (g*D) - (h*E) - (i*L) - (j*M) - (k*N) - (l*I) - (m*J) + (n*K) - (o*P) + (p*O))/2


/*

[
    ((0 +((A)*(a)) +((C)*(c)) +((D)*(d)) +((E)*(e)) -((I)*(i)) -((J)*(j)) -((K)*(k)) -((O)*(o)))  -  (0 +((a)*(A)) +((c)*(C)) +((d)*(D)) +((e)*(E)) -((i)*(I)) -((j)*(J)) -((k)*(K)) -((o)*(O))))*((alias_R)(0.5))
  , ((0 +((A)*(b)) +((B)*(a)) -((C)*(f)) -((D)*(g)) -((E)*(h)) +((F)*(c)) -((G)*(d)) +((H)*(e)) +((I)*(l)) +((J)*(m)) +((K)*(n)) +((L)*(i)) +((M)*(j)) -((N)*(k)) +((O)*(p)) -((P)*(o)))  -  (0 +((a)*(B)) +((b)*(A)) -((c)*(F)) -((d)*(G)) -((e)*(H)) +((f)*(C)) -((g)*(D)) +((h)*(E)) +((i)*(L)) +((j)*(M)) +((k)*(N)) +((l)*(I)) +((m)*(J)) -((n)*(K)) +((o)*(P)) -((p)*(O))))*((alias_R)(0.5))
  , ((0 +((A)*(c)) +((C)*(a)) -((D)*(i)) +((E)*(j)) +((I)*(d)) -((J)*(e)) -((K)*(o)) -((O)*(k)))-(0 +((a)*(C)) +((c)*(A)) -((d)*(I)) +((e)*(J)) +((i)*(D)) -((j)*(E)) -((k)*(O)) -((o)*(K))))*((alias_R)(0.5))
  , ((0 +((A)*(d)) +((C)*(i)) +((D)*(a)) -((E)*(k)) -((I)*(c)) -((J)*(o)) +((K)*(e)) -((O)*(j)))-(0 +((a)*(D)) +((c)*(I)) +((d)*(A)) -((e)*(K)) -((i)*(C)) -((j)*(O)) +((k)*(E)) -((o)*(J))))*((alias_R)(0.5))
  , ((0 +((A)*(e)) -((C)*(j)) +((D)*(k)) +((E)*(a)) -((I)*(o)) +((J)*(c)) -((K)*(d)) -((O)*(i)))-(0 +((a)*(E)) -((c)*(J)) +((d)*(K)) +((e)*(A)) -((i)*(O)) +((j)*(C)) -((k)*(D)) -((o)*(I))))*((alias_R)(0.5))
  , ((0 +((A)*(f)) +((B)*(c)) -((C)*(b)) -((D)*(l)) +((E)*(m)) +((F)*(a)) -((G)*(i)) +((H)*(j)) +((I)*(g)) -((J)*(h)) -((K)*(p)) -((L)*(d)) +((M)*(e)) +((N)*(o)) -((O)*(n)) -((P)*(k)))-(0 +((a)*(F)) +((b)*(C)) -((c)*(B)) -((d)*(L)) +((e)*(M)) +((f)*(A)) -((g)*(I)) +((h)*(J)) +((i)*(G)) -((j)*(H)) -((k)*(P)) -((l)*(D)) +((m)*(E)) +((n)*(O)) -((o)*(N)) -((p)*(K))))*((alias_R)(0.5))
  , ((0 +((A)*(g)) +((B)*(d)) +((C)*(l)) -((D)*(b)) -((E)*(n)) +((F)*(i)) +((G)*(a)) -((H)*(k)) -((I)*(f)) -((J)*(p)) +((K)*(h)) +((L)*(c)) +((M)*(o)) -((N)*(e)) -((O)*(m)) -((P)*(j)))-(0 +((a)*(G)) +((b)*(D)) +((c)*(L)) -((d)*(B)) -((e)*(N)) +((f)*(I)) +((g)*(A)) -((h)*(K)) -((i)*(F)) -((j)*(P)) +((k)*(H)) +((l)*(C)) +((m)*(O)) -((n)*(E)) -((o)*(M)) -((p)*(J))))*((alias_R)(0.5))
  , ((0 +((A)*(h)) +((B)*(e)) -((C)*(m)) +((D)*(n)) -((E)*(b)) -((F)*(j)) +((G)*(k)) +((H)*(a)) -((I)*(p)) +((J)*(f)) -((K)*(g)) +((L)*(o)) -((M)*(c)) +((N)*(d)) -((O)*(l)) -((P)*(i)))-(0 +((a)*(H)) +((b)*(E)) -((c)*(M)) +((d)*(N)) -((e)*(B)) -((f)*(J)) +((g)*(K)) +((h)*(A)) -((i)*(P)) +((j)*(F)) -((k)*(G)) +((l)*(O)) -((m)*(C)) +((n)*(D)) -((o)*(L)) -((p)*(I))))*((alias_R)(0.5))
  , ((0 +((A)*(i)) +((C)*(d)) -((D)*(c)) +((E)*(o)) +((I)*(a)) +((J)*(k)) -((K)*(j)) +((O)*(e)))-(0 +((a)*(I)) +((c)*(D)) -((d)*(C)) +((e)*(O)) +((i)*(A)) +((j)*(K)) -((k)*(J)) +((o)*(E))))*((alias_R)(0.5))
  , ((0 +((A)*(j)) -((C)*(e)) +((D)*(o)) +((E)*(c)) -((I)*(k)) +((J)*(a)) +((K)*(i)) +((O)*(d)))-(0 +((a)*(J)) -((c)*(E)) +((d)*(O)) +((e)*(C)) -((i)*(K)) +((j)*(A)) +((k)*(I)) +((o)*(D))))*((alias_R)(0.5))
  , ((0 +((A)*(k)) +((C)*(o)) -((D)*(e)) -((E)*(d)) +((I)*(j)) -((J)*(i)) +((K)*(a)) +((O)*(c)))-(0 +((a)*(K)) +((c)*(O)) -((d)*(E)) -((e)*(D)) +((i)*(J)) -((j)*(I)) +((k)*(A)) +((o)*(C))))*((alias_R)(0.5))
  , ((0 +((A)*(l)) -((B)*(i)) +((C)*(g)) -((D)*(f)) +((E)*(p)) -((F)*(d)) +((G)*(c)) -((H)*(o)) -((I)*(b)) +((J)*(n)) -((K)*(m)) +((L)*(a)) +((M)*(k)) -((N)*(j)) +((O)*(h)) -((P)*(e)))-(0 +((a)*(L)) -((b)*(I)) +((c)*(G)) -((d)*(F)) +((e)*(P)) -((f)*(D)) +((g)*(C)) -((h)*(O)) -((i)*(B)) +((j)*(N)) -((k)*(M)) +((l)*(A)) +((m)*(K)) -((n)*(J)) +((o)*(H)) -((p)*(E))))*((alias_R)(0.5))
  , ((0 +((A)*(m)) -((B)*(j)) -((C)*(h)) +((D)*(p)) +((E)*(f)) +((F)*(e)) -((G)*(o)) -((H)*(c)) -((I)*(n)) -((J)*(b)) +((K)*(l)) -((L)*(k)) +((M)*(a)) -((N)*(i)) +((O)*(g)) -((P)*(d)))-(0 +((a)*(M)) -((b)*(J)) -((c)*(H)) +((d)*(P)) +((e)*(F)) +((f)*(E)) -((g)*(O)) -((h)*(C)) -((i)*(N)) -((j)*(B)) +((k)*(L)) -((l)*(K)) +((m)*(A)) -((n)*(I)) +((o)*(G)) -((p)*(D))))*((alias_R)(0.5))
  , ((0 +((A)*(n)) -((B)*(k)) +((C)*(p)) -((D)*(h)) -((E)*(g)) -((F)*(o)) -((G)*(e)) +((H)*(d)) +((I)*(m)) -((J)*(l)) -((K)*(b)) +((L)*(j)) -((M)*(i)) +((N)*(a)) +((O)*(f)) -((P)*(c)))-(0 +((a)*(N)) -((b)*(K)) +((c)*(P)) -((d)*(H)) -((e)*(G)) -((f)*(O)) -((g)*(E)) +((h)*(D)) +((i)*(M)) -((j)*(L)) -((k)*(B)) +((l)*(J)) -((m)*(I)) +((n)*(A)) +((o)*(F)) -((p)*(C))))*((alias_R)(0.5))
  , ((0 +((A)*(o)) +((C)*(k)) +((D)*(j)) +((E)*(i)) +((I)*(e)) +((J)*(d)) +((K)*(c)) +((O)*(a)))-(0 +((a)*(O)) +((c)*(K)) +((d)*(J)) +((e)*(I)) +((i)*(E)) +((j)*(D)) +((k)*(C)) +((o)*(A))))*((alias_R)(0.5))
  , ((0 +((A)*(p)) +((B)*(o)) +((C)*(n)) +((D)*(m)) +((E)*(l)) +((F)*(k)) +((G)*(j)) +((H)*(i)) +((I)*(h)) +((J)*(g)) +((K)*(f)) -((L)*(e)) -((M)*(d)) -((N)*(c)) -((O)*(b)) +((P)*(a)))-(0 +((a)*(P)) +((b)*(O)) +((c)*(N)) +((d)*(M)) +((e)*(L)) +((f)*(K)) +((g)*(J)) +((h)*(I)) +((i)*(H)) +((j)*(G)) +((k)*(F)) -((l)*(E)) -((m)*(D)) -((n)*(C)) -((o)*(B)) +((p)*(A))))*((alias_R)(0.5))
  ]

       */



#endif

