#ifndef _ALIAS_PGA_OPERATORS_H_
#define _ALIAS_PGA_OPERATORS_H_

#include <alias/cpp/boolean.h>

#define ALIAS_PGA_UNARY_OPERATORS(X, ...) \
  X(ALIAS_PGA_OP_NEGATE,             negate,             ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_DUAL,               dual,               ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_POLARITY,           polarity,           ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_REVERSE,            reverse,            ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SELECT_GRADE_0,     select_grade_0,     ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SELECT_GRADE_1,     select_grade_1,     ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SELECT_GRADE_2,     select_grade_2,     ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SELECT_GRADE_3,     select_grade_3,     ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SELECT_GRADE_4,     select_grade_4,     ## __VA_ARGS__)

#define ALIAS_PGA_BINARY_OPERATORS(X, ...) \
  X(ALIAS_PGA_OP_ADD,                add,                ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_SUBTRACT,           subtract,           ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_GEOMETRIC_PRODUCT,  geometric_product,  ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_OUTER_PRODUCT,      outer_product,      ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_REGRESSIVE_PRODUCT, regressive_product, ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_INNER_PRODUCT,      inner_product,      ## __VA_ARGS__) \
  X(ALIAS_PGA_OP_COMMUTATOR_PRODUCT, commutator_product, ## __VA_ARGS__)

#define ALIAS_PGA_RZ_NEG(A) ALIAS_CPP_IF1(ALIAS_CPP_IS_ZERO(A))(0)(-A)

#define ALIAS_PGA_RZ_ADD(A, B) ALIAS_CPP_IF2(ALIAS_CPP_IS_ZERO(A), ALIAS_CPP_IS_ZERO(B))(0)( B)(A)(A+B)
#define ALIAS_PGA_RZ_SUB(A, B) ALIAS_CPP_IF2(ALIAS_CPP_IS_ZERO(A), ALIAS_CPP_IS_ZERO(B))(0)(-B)(A)(A-B)
#define ALIAS_PGA_RZ_AML(A, B) ALIAS_CPP_IF2(ALIAS_CPP_IS_ZERO(A), ALIAS_CPP_IS_ZERO(B))( )(  )( )(+(A*B))
#define ALIAS_PGA_RZ_SML(A, B) ALIAS_CPP_IF2(ALIAS_CPP_IS_ZERO(A), ALIAS_CPP_IS_ZERO(B))( )(  )( )(-(A*B))

#define ALIAS_PGA_OP_NEGATE(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  ALIAS_PGA_OP_NEGATE_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ALIAS_PGA_RZ_NEG,##__VA_ARGS__)
#define ALIAS_PGA_OP_NEGATE_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, NEG,...) \
  RETURN( \
     NEG(A) \
   , NEG(B) \
   , NEG(C) \
   , NEG(D) \
   , NEG(E) \
   , NEG(F) \
   , NEG(G) \
   , NEG(H) \
   , NEG(I) \
   , NEG(J) \
   , NEG(K) \
   , NEG(L) \
   , NEG(M) \
   , NEG(N) \
   , NEG(O) \
   , NEG(P) \
   , ## __VA_ARGS__ \
   )

#define ALIAS_PGA_OP_DUAL(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  RETURN( \
    P \
  , O, N, M, L \
  , K, J, I, H, G, F \
  , E, D, C, B \
  , A \
  , ## __VA_ARGS__ \
  )

// alias_pga_geometric_product(A, alias_pga_antiscalar(1))
#define ALIAS_PGA_OP_POLARITY(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  ALIAS_PGA_OP_POLARITY(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ALIAS_PGA_RZ_NEG,##__VA_ARGS__)
#define ALIAS_PGA_OP_POLARITY_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, NEG,...) \
  RETURN( \
    0 \
  , O, 0, 0, 0 \
  , NEG(K), NEG(J), NEG(I), 0, 0, 0 \
  , E, D, C, 0 \
  , A \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_OP_REVERSE(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) \
  ALIAS_PGA_OP_REVERSE_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ALIAS_PGA_RZ_NEG,##__VA_ARGS__)
#define ALIAS_PGA_OP_REVERSE_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, NEG,...) \
  RETURN( \
    A \
  , B, C, D, E \
  , NEG(F), NEG(G), NEG(H), NEG(I), NEG(J), NEG(K) \
  , NEG(L), NEG(M), NEG(N), NEG(O) \
  , NEG(P) \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_OP_SELECT_GRADE(RETURN, n, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) ALIAS_CPP_CAT(ALIAS_PGA_OP_SELECT_GRADE_, n)(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ## __VA_ARGS__)

#define ALIAS_PGA_OP_SELECT_GRADE_0(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(A,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,## __VA_ARGS__)
#define ALIAS_PGA_OP_SELECT_GRADE_1(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,B,C,D,E,0,0,0,0,0,0,0,0,0,0,0,## __VA_ARGS__)
#define ALIAS_PGA_OP_SELECT_GRADE_2(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,F,G,H,I,J,K,0,0,0,0,0,## __VA_ARGS__)
#define ALIAS_PGA_OP_SELECT_GRADE_3(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,0,0,0,0,0,0,L,M,N,O,0,## __VA_ARGS__)
#define ALIAS_PGA_OP_SELECT_GRADE_4(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, ...) RETURN(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,P,## __VA_ARGS__)

#define ALIAS_PGA_OP_ADD(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  ALIAS_PGA_OP_ADD_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_ADD,##_VA_ARGS__)
#define ALIAS_PGA_OP_ADD_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,...) \
  RETURN( \
     ADD(A, a) \
   , ADD(B, b) \
   , ADD(C, c) \
   , ADD(D, d) \
   , ADD(E, e) \
   , ADD(F, f) \
   , ADD(G, g) \
   , ADD(H, h) \
   , ADD(I, i) \
   , ADD(J, j) \
   , ADD(K, k) \
   , ADD(L, l) \
   , ADD(M, m) \
   , ADD(N, n) \
   , ADD(O, o) \
   , ADD(P, p) \
   , ## __VA_ARGS__ \
   )

#define ALIAS_PGA_OP_SUBTRACT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) \
  ALIAS_PGA_OP_SUBTRACT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_SUB,##__VA_ARGS__)
#define ALIAS_PGA_OP_SUBTRACT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, SUB,...) \
  RETURN( \
     SUB(A, a) \
   , SUB(B, b) \
   , SUB(C, c) \
   , SUB(D, d) \
   , SUB(E, e) \
   , SUB(F, f) \
   , SUB(G, g) \
   , SUB(H, h) \
   , SUB(I, i) \
   , SUB(J, j) \
   , SUB(K, k) \
   , SUB(L, l) \
   , SUB(M, m) \
   , SUB(N, n) \
   , SUB(O, o) \
   , SUB(P, p) \
   , ## __VA_ARGS__ \
   )

#define ALIAS_PGA_OP_GEOMETRIC_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_OP_GEOMETRIC_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_AML,ALIAS_PGA_RZ_SML,## __VA_ARGS__)
#define ALIAS_PGA_OP_GEOMETRIC_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,SUB, ...) \
  RETURN( \
    0 ADD(A, a)           ADD(C, c) ADD(D, d) ADD(E, e)                               SUB(I, i) SUB(J, j) SUB(K, k)                               SUB(O, o)           \
  , 0 ADD(A, b) ADD(B, a) SUB(C, f) SUB(D, g) SUB(E, h) ADD(F, c) SUB(G, d) ADD(H, e) ADD(I, l) ADD(J, m) ADD(K, n) ADD(L, i) ADD(M, j) SUB(N, k) ADD(O, p) SUB(P, o) \
  , 0 ADD(A, c)           ADD(C, a) SUB(D, i) ADD(E, j)                               ADD(I, d) SUB(J, e) SUB(K, o)                               SUB(O, k)           \
  , 0 ADD(A, d)           ADD(C, i) ADD(D, a) SUB(E, k)                               SUB(I, c) SUB(J, o) ADD(K, e)                               SUB(O, j)           \
  , 0 ADD(A, e)           SUB(C, j) ADD(D, k) ADD(E, a)                               SUB(I, o) ADD(J, c) SUB(K, d)                               SUB(O, i)           \
  , 0 ADD(A, f) ADD(B, c) SUB(C, b) SUB(D, l) ADD(E, m) ADD(F, a) SUB(G, i) ADD(H, j) ADD(I, g) SUB(J, h) SUB(K, p) SUB(L, d) ADD(M, e) ADD(N, o) SUB(O, n) SUB(P, k) \
  , 0 ADD(A, g) ADD(B, d) ADD(C, l) SUB(D, b) SUB(E, n) ADD(F, i) ADD(G, a) SUB(H, k) SUB(I, f) SUB(J, p) ADD(K, h) ADD(L, c) ADD(M, o) SUB(N, e) SUB(O, m) SUB(P, j) \
  , 0 ADD(A, h) ADD(B, e) SUB(C, m) ADD(D, n) SUB(E, b) SUB(F, j) ADD(G, k) ADD(H, a) SUB(I, p) ADD(J, f) SUB(K, g) ADD(L, o) SUB(M, c) ADD(N, d) SUB(O, l) SUB(P, i) \
  , 0 ADD(A, i)           ADD(C, d) SUB(D, c) ADD(E, o)                               ADD(I, a) ADD(J, k) SUB(K, j)                               ADD(O, e)           \
  , 0 ADD(A, j)           SUB(C, e) ADD(D, o) ADD(E, c)                               SUB(I, k) ADD(J, a) ADD(K, i)                               ADD(O, d)           \
  , 0 ADD(A, k)           ADD(C, o) SUB(D, e) SUB(E, d)                               ADD(I, j) SUB(J, i) ADD(K, a)                               ADD(O, c)           \
  , 0 ADD(A, l) SUB(B, i) ADD(C, g) SUB(D, f) ADD(E, p) SUB(F, d) ADD(G, c) SUB(H, o) SUB(I, b) ADD(J, n) SUB(K, m) ADD(L, a) ADD(M, k) SUB(N, j) ADD(O, h) SUB(P, e) \
  , 0 ADD(A, m) SUB(B, j) SUB(C, h) ADD(D, p) ADD(E, f) ADD(F, e) SUB(G, o) SUB(H, c) SUB(I, n) SUB(J, b) ADD(K, l) SUB(L, k) ADD(M, a) SUB(N, i) ADD(O, g) SUB(P, d) \
  , 0 ADD(A, n) SUB(B, k) ADD(C, p) SUB(D, h) SUB(E, g) SUB(F, o) SUB(G, e) ADD(H, d) ADD(I, m) SUB(J, l) SUB(K, b) ADD(L, j) SUB(M, i) ADD(N, a) ADD(O, f) SUB(P, c) \
  , 0 ADD(A, o)           ADD(C, k) ADD(D, j) ADD(E, i)                               ADD(I, e) ADD(J, d) ADD(K, c)                               ADD(O, a)           \
  , 0 ADD(A, p) ADD(B, o) ADD(C, n) ADD(D, m) ADD(E, l) ADD(F, k) ADD(G, j) ADD(H, i) ADD(I, h) ADD(J, g) ADD(K, f) SUB(L, e) SUB(M, d) SUB(N, c) SUB(O, b) ADD(P, a) \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_OP_OUTER_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_OP_OUTER_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_AML,ALIAS_PGA_RZ_SML,## __VA_ARGS__)
#define ALIAS_PGA_OP_OUTER_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,SUB, ...) \
  RETURN( \
    0 ADD(A, a) \
  , 0 ADD(A, b) ADD(B, a) \
  , 0 ADD(A, c)           ADD(C, a) \
  , 0 ADD(A, d)                     ADD(D, a) \
  , 0 ADD(A, e)                               ADD(E, a) \
  , 0 ADD(A, f) ADD(B, c) SUB(C, b)                     ADD(F, a) \
  , 0 ADD(A, g) ADD(B, d)           SUB(D, b)                     ADD(G, a) \
  , 0 ADD(A, h) ADD(B, e)                     SUB(E, b)                     ADD(H, a) \
  , 0 ADD(A, i)           ADD(C, d) SUB(D, c)                                         ADD(I, a) \
  , 0 ADD(A, j)           SUB(C, e)           ADD(E, c)                                         ADD(J, a) \
  , 0 ADD(A, k)                     SUB(D, e) SUB(E, d)                                                   ADD(K, a) \
  , 0 ADD(A, l) SUB(B, i) ADD(C, g) SUB(D, f)           SUB(F, d) ADD(G, c)           SUB(I, b)                     ADD(L, a) \
  , 0 ADD(A, m) SUB(B, j) SUB(C, h)           ADD(E, f) ADD(F, e)           SUB(H, c)           SUB(J, b)                     ADD(M, a) \
  , 0 ADD(A, n) SUB(B, k)           SUB(D, h) SUB(E, g)           SUB(G, e) ADD(H, d)                     SUB(K, b)                     ADD(N, a) \
  , 0 ADD(A, o)           ADD(C, k) ADD(D, j) ADD(E, i)                               ADD(I, e) ADD(J, d) ADD(K, c)                               ADD(O, a) \
  , 0 ADD(A, p) ADD(B, o) ADD(C, n) ADD(D, m) ADD(E, l) ADD(F, k) ADD(G, j) ADD(H, i) ADD(I, h) ADD(J, g) ADD(K, f) SUB(L, e) SUB(M, d) SUB(N, c) SUB(O, b) ADD(P, a) \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_OP_REGRESSIVE_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_OP_REGRESSIVE_PRODUCT_(RETURN, P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A, p,o,n,m,l,k,j,i,h,g,f,e,d,c,b,a, ALIAS_PGA_RZ_AML,ALIAS_PGA_RZ_SML,## __VA_ARGS__)
#define ALIAS_PGA_OP_REGRESSIVE_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,SUB, ...) \
  RETURN( \
    0 ADD(A, p) ADD(B, o) ADD(C, n) ADD(D, m) ADD(E, l) ADD(F, k) ADD(G, j) ADD(H, i) ADD(I, h) ADD(J, g) ADD(K, f) SUB(L, e) SUB(M, d) SUB(N, c) SUB(O, b) ADD(P, a) \
  , 0 ADD(A, o)           ADD(C, k) ADD(D, j) ADD(E, i)                               ADD(I, e) ADD(J, d) ADD(K, c)                               ADD(O, a) \
  , 0 ADD(A, n) SUB(B, k)           SUB(D, h) SUB(E, g)           SUB(G, e) ADD(H, d)                     SUB(K, b)                     ADD(N, a) \
  , 0 ADD(A, m) SUB(B, j) SUB(C, h)           ADD(E, f) ADD(F, e)           SUB(H, c)           SUB(J, b)                     ADD(M, a) \
  , 0 ADD(A, l) SUB(B, i) ADD(C, g) SUB(D, f)           SUB(F, d) ADD(G, c)           SUB(I, b)                     ADD(L, a) \
  , 0 ADD(A, k)                     SUB(D, e) SUB(E, d)                                                   ADD(K, a) \
  , 0 ADD(A, j)           SUB(C, e)           ADD(E, c)                                         ADD(J, a) \
  , 0 ADD(A, i)           ADD(C, d) SUB(D, c)                                         ADD(I, a) \
  , 0 ADD(A, h) ADD(B, e)                     SUB(E, b)                     ADD(H, a) \
  , 0 ADD(A, g) ADD(B, d)           SUB(D, b)                     ADD(G, a) \
  , 0 ADD(A, f) ADD(B, c) SUB(C, b)                     ADD(F, a) \
  , 0 ADD(A, e)                               ADD(E, a) \
  , 0 ADD(A, d)                     ADD(D, a) \
  , 0 ADD(A, c)           ADD(C, a) \
  , 0 ADD(A, b) ADD(B, a) \
  , 0 ADD(A, a) \
  , ## __VA_ARGS__ \
  )

#define ALIAS_PGA_OP_INNER_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_OP_INNER_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_AML,ALIAS_PGA_RZ_SML,## __VA_ARGS__)
#define ALIAS_PGA_OP_INNER_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,SUB, ...) \
  RETURN( \
    0 ADD(A, a)           ADD(C, c) ADD(D, d) ADD(E, e)                               SUB(I, i) SUB(J, j) SUB(K, k)                               SUB(O, o)           \
  , 0 ADD(A, b) ADD(B, a) SUB(C, f) SUB(D, g) SUB(E, h) ADD(F, c) SUB(G, d) ADD(H, e) ADD(I, l) ADD(J, m) ADD(K, n) ADD(L, i) ADD(M, j) SUB(N, k) ADD(O, p) SUB(P, o) \
  , 0 ADD(A, c)           ADD(C, a) SUB(D, i) ADD(E, j)                               ADD(I, d) SUB(J, e) SUB(K, o)                               SUB(O, k)           \
  , 0 ADD(A, d)           ADD(C, i) ADD(D, a) SUB(E, k)                               SUB(I, c) SUB(J, o) ADD(K, e)                               SUB(O, j)           \
  , 0 ADD(A, e)           SUB(C, j) ADD(D, k) ADD(E, a)                               SUB(I, o) ADD(J, c) SUB(K, d)                               SUB(O, i)           \
  , 0 ADD(A, f)                     SUB(D, l) ADD(E, m) ADD(F, a)                                         SUB(K, p) SUB(L, d) ADD(M, e)                     SUB(P, k) \
  , 0 ADD(A, g)           ADD(C, l)           SUB(E, n)           ADD(G, a)                     SUB(J, p)           ADD(L, c)           SUB(N, e)           SUB(P, j) \
  , 0 ADD(A, h)           SUB(C, m) ADD(D, n)                               ADD(H, a) SUB(I, p)                               SUB(M, c) ADD(N, d)           SUB(P, i) \
  , 0 ADD(A, i)                               ADD(E, o)                               ADD(I, a)                                                   ADD(O, e)           \
  , 0 ADD(A, j)                     ADD(D, o)                                                   ADD(J, a)                                         ADD(O, d)           \
  , 0 ADD(A, k)           ADD(C, o)                                                                       ADD(K, a)                               ADD(O, c)           \
  , 0 ADD(A, l)                               ADD(E, p)                                                             ADD(L, a)                               SUB(P, e) \
  , 0 ADD(A, m)                     ADD(D, p)                                                                                 ADD(M, a)                     SUB(P, d) \
  , 0 ADD(A, n)           ADD(C, p)                                                                                                     ADD(N, a)           SUB(P, c) \
  , 0 ADD(A, o)                                                                                                                                   ADD(O, a)           \
  , 0 ADD(A, p)                                                                                                                                             ADD(P, a) \
  , ## __VA_ARGS__ \
  )

// 1/2(ab - ba)
#define ALIAS_PGA_OP_COMMUTATOR_PRODUCT(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ...) ALIAS_PGA_OP_COMMUTATOR_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ALIAS_PGA_RZ_AML,ALIAS_PGA_RZ_SML,## __VA_ARGS__)
#define ALIAS_PGA_OADDCOMMUTATOR_PRODUCT_(RETURN, A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p, ADD,SUB, ...) \
  RETURN( \
   0 \
 , 0 ADD(F,c) SUB(E,h) ADD(C,f) ADD(H,e) ADD(K,n) SUB(N,k) ADD(O,p) SUB(P,o) \
 , 0 ADD(E,j) SUB(D,i) ADD(I,d) SUB(J,e) \
 , 0 ADD(C,i) SUB(E,k) SUB(I,c) ADD(K,e) \
 , 0 ADD(D,k) SUB(C,j) ADD(J,c) SUB(K,d) \
 , 0 ADD(B,c) SUB(C,b) SUB(G,i) ADD(H,j) ADD(I,g) SUB(J,h) ADD(N,o) SUB(O,n) \
 , 0 ADD(B,d) SUB(D,b) ADD(F,i) SUB(H,k) SUB(I,f) ADD(K,h) ADD(M,o) SUB(O,m) \
 , 0 ADD(B,e) SUB(E,b) SUB(F,j) ADD(G,k) ADD(J,f) SUB(K,g) ADD(L,o) SUB(O,l) \
 , 0 ADD(C,d) SUB(D,c) ADD(J,k) SUB(K,j) \
 , 0 ADD(E,c) SUB(C,e) SUB(I,k) ADD(K,i) \
 , 0 ADD(I,j) SUB(J,i) \
 , 0 ADD(E,p) SUB(H,o) ADD(J,n) SUB(K,m) ADD(M,k) SUB(N,j) ADD(O,h) SUB(P,e) \
 , 0 ADD(D,p) SUB(G,o) ADD(K,l) SUB(L,k) ADD(O,g) SUB(P,d) \
 , 0 ADD(C,p) SUB(D,h) SUB(F,o) ADD(H,d) ADD(I,m) SUB(J,l) ADD(L,j) SUB(M,i) ADD(O,f) SUB(P,c) \
 , 0 \
 , 0 ADD(B,o) ADD(C,n) ADD(D,m) ADD(E,l) SUB(L,e) SUB(M,d) SUB(N,c) SUB(O,b) \
 , ## __VA_ARGS__ \
 )

// ab~a
#include <alias/pga/sandwich.h>

// #include <alias/pga/normalization.h>

#endif

