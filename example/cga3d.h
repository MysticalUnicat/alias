// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// generated with alias_gen_geometric_algebra (author Sarah Burns <mystical.unicat@gmail.com>)
// options: -p 4 -n 1 --binary meet outer_product --binary join regressive_product
#ifndef _ALIAS_CGA3D_H_
#define _ALIAS_CGA3D_H_
// 4 positive dimension(s)
// 1 negative dimension(s)
// 0 deginerate dimension(s)
// 5 total dimension(s)
// 6 total grade(s)
#define ALIAS_CGA3D_EMPTY(...)
#define ALIAS_CGA3D_UNPACK(...) __VA_ARGS__
#define ALIAS_CGA3D_CAT(X, ...) ALIAS_CGA3D_CAT0(X, ## __VA_ARGS__)
#define ALIAS_CGA3D_CAT0(X, ...) X ## __VA_ARGS__
#define ALIAS_CGA3D_CAT3(X, Y, ...) ALIAS_CGA3D_CAT30(X, Y, ## __VA_ARGS__)
#define ALIAS_CGA3D_CAT30(X, Y, ...) X ## Y ## __VA_ARGS__
#define ALIAS_CGA3D_OR(X, Y) ALIAS_CGA3D_CAT3(ALIAS_CGA3D_OR_, X, Y)
#define ALIAS_CGA3D_OR_00 0
#define ALIAS_CGA3D_OR_01 1
#define ALIAS_CGA3D_OR_10 1
#define ALIAS_CGA3D_OR_11 1
#define ALIAS_CGA3D_IFF(X) ALIAS_CGA3D_CAT(ALIAS_CGA3D_IFF_, X)
#define ALIAS_CGA3D_IFF_0(T, F) F
#define ALIAS_CGA3D_IFF_1(T, F) T
#define ALIAS_CGA3D_IF2(X, Y) ALIAS_CGA3D_CAT3(ALIAS_CGA3D_IF2_, X, Y)
#define ALIAS_CGA3D_IF(X) ALIAS_CGA3D_CAT(ALIAS_CGA3D_IF_, X)
#define ALIAS_CGA3D_IF_0(...) ALIAS_CGA3D_UNPACK
#define ALIAS_CGA3D_IF_1(...) __VA_ARGS__ ALIAS_CGA3D_EMPTY
#define ALIAS_CGA3D_IF2(X, Y) ALIAS_CGA3D_CAT3(ALIAS_CGA3D_IF2_, X, Y)
#define ALIAS_CGA3D_IF2_00(...) ALIAS_CGA3D_IF2_000
#define ALIAS_CGA3D_IF2_000(...) ALIAS_CGA3D_IF2_001
#define ALIAS_CGA3D_IF2_001(...) ALIAS_CGA3D_UNPACK
#define ALIAS_CGA3D_IF2_01(...) ALIAS_CGA3D_IF2_010
#define ALIAS_CGA3D_IF2_010(...) ALIAS_CGA3D_IF2_011
#define ALIAS_CGA3D_IF2_011(...) __VA_ARGS__ ALIAS_CGA3D_EMPTY
#define ALIAS_CGA3D_IF2_10(...) ALIAS_CGA3D_IF2_100
#define ALIAS_CGA3D_IF2_100(...) __VA_ARGS__ ALIAS_CGA3D_IF2_101
#define ALIAS_CGA3D_IF2_101(...) ALIAS_CGA3D_EMPTY
#define ALIAS_CGA3D_IF2_11(...) __VA_ARGS__ ALIAS_CGA3D_IF2_110
#define ALIAS_CGA3D_IF2_110(...) ALIAS_CGA3D_IF2_111
#define ALIAS_CGA3D_IF2_111(...) ALIAS_CGA3D_EMPTY
#define ALIAS_CGA3D_PROBE(...) ~,1
#define ALIAS_CGA3D_IS_PROBE(...) ALIAS_CGA3D_IS_PROBE0(__VA_ARGS__, 0, 0)
#define ALIAS_CGA3D_IS_PROBE0(X, Y, ...) Y
#define ALIAS_CGA3D_IS_ZERO(X) ALIAS_CGA3D_IFF(ALIAS_CGA3D_IS_PROBE(ALIAS_CGA3D_PROBE X))(ALIAS_CGA3D_IS_ZERO1, ALIAS_CGA3D_IS_ZERO2)(X)
#define ALIAS_CGA3D_IS_ZERO1(X) 0
#define ALIAS_CGA3D_IS_ZERO2(X) ALIAS_CGA3D_IS_PROBE(ALIAS_CGA3D_CAT(ALIAS_CGA3D_IS_ZERO3_, X)())
#define ALIAS_CGA3D_IS_ZERO3_0 ALIAS_CGA3D_PROBE
#define ALIAS_CGA3D_IS_NONZERO(X) ALIAS_CGA3D_IF(ALIAS_CGA3D_IS_ZERO(X))(0)(1)
#define ALIAS_CGA3D_NEG(X) ALIAS_CGA3D_IF(ALIAS_CGA3D_IS_ZERO(X))( 0 )( (-X) )
#define ALIAS_CGA3D_ADD(X, Y) ALIAS_CGA3D_IF2(ALIAS_CGA3D_IS_ZERO(X), ALIAS_CGA3D_IS_ZERO(Y))( 0 )(   Y  )( X )( X+Y )
#define ALIAS_CGA3D_SUB(X, Y) ALIAS_CGA3D_IF2(ALIAS_CGA3D_IS_ZERO(X), ALIAS_CGA3D_IS_ZERO(Y))( 0 )( (-Y) )( X )( X-Y )
#define ALIAS_CGA3D_ADD_MUL(X, Y) ALIAS_CGA3D_IF(ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_ZERO(X), ALIAS_CGA3D_IS_ZERO(Y)))( )( +(X*Y) )
#define ALIAS_CGA3D_SUB_MUL(X, Y) ALIAS_CGA3D_IF(ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_ZERO(X), ALIAS_CGA3D_IS_ZERO(Y)))( )( -(X*Y) )
// cayley table:
// one    e1     e2     e3     e4     e5     e12    e13    e14    e15    e23    e24    e25    e34    e35    e45    e123   e124   e125   e134   e135   e145   e234   e235   e245   e345   e1234  e1235  e1245  e1345  e2345  e12345
// e1     one    e12    e13    e14    e15    e2     e3     e4     e5     e123   e124   e125   e134   e135   e145   e23    e24    e25    e34    e35    e45    e1234  e1235  e1245  e1345  e234   e235   e245   e345   e12345 e2345 
// e2     -e12   one    e23    e24    e25    -e1    -e123  -e124  -e125  e3     e4     e5     e234   e235   e245   -e13   -e14   -e15   -e1234 -e1235 -e1245 e34    e35    e45    e2345  -e134  -e135  -e145  -e12345 e345   -e1345
// e3     -e13   -e23   one    e34    e35    e123   -e1    -e134  -e135  -e2    -e234  -e235  e4     e5     e345   e12    e1234  e1235  -e14   -e15   -e1345 -e24   -e25   -e2345 e45    e124   e125   e12345 -e145  -e245  e1245 
// e4     -e14   -e24   -e34   one    e45    e124   e134   -e1    -e145  e234   -e2    -e245  -e3    -e345  e5     -e1234 e12    e1245  e13    e1345  -e15   e23    e2345  -e25   -e35   -e123  -e12345 e125   e135   e235   -e1235
// e5     -e15   -e25   -e35   -e45   -one   e125   e135   e145   e1     e235   e245   e2     e345   e3     e4     -e1235 -e1245 -e12   -e1345 -e13   -e14   -e2345 -e23   -e24   -e34   e12345 e123   e124   e134   e234   -e1234
// e12    -e2    e1     e123   e124   e125   -one   -e23   -e24   -e25   e13    e14    e15    e1234  e1235  e1245  -e3    -e4    -e5    -e234  -e235  -e245  e134   e135   e145   e12345 -e34   -e35   -e45   -e2345 e1345  -e345 
// e13    -e3    -e123  e1     e134   e135   e23    -one   -e34   -e35   -e12   -e1234 -e1235 e14    e15    e1345  e2     e234   e235   -e4    -e5    -e345  -e124  -e125  -e12345 e145   e24    e25    e2345  -e45   -e1245 e245  
// e14    -e4    -e124  -e134  e1     e145   e24    e34    -one   -e45   e1234  -e12   -e1245 -e13   -e1345 e15    -e234  e2     e245   e3     e345   -e5    e123   e12345 -e125  -e135  -e23   -e2345 e25    e35    e1235  -e235 
// e15    -e5    -e125  -e135  -e145  -e1    e25    e35    e45    one    e1235  e1245  e12    e1345  e13    e14    -e235  -e245  -e2    -e345  -e3    -e4    -e12345 -e123  -e124  -e134  e2345  e23    e24    e34    e1234  -e234 
// e23    e123   -e3    e2     e234   e235   -e13   e12    e1234  e1235  -one   -e34   -e35   e24    e25    e2345  -e1    -e134  -e135  e124   e125   e12345 -e4    -e5    -e345  e245   -e14   -e15   -e1345 e1245  -e45   -e145 
// e24    e124   -e4    -e234  e2     e245   -e14   -e1234 e12    e1245  e34    -one   -e45   -e23   -e2345 e25    e134   -e1    -e145  -e123  -e12345 e125   e3     e345   -e5    -e235  e13    e1345  -e15   -e1235 e35    e135  
// e25    e125   -e5    -e235  -e245  -e2    -e15   -e1235 -e1245 -e12   e35    e45    one    e2345  e23    e24    e135   e145   e1     e12345 e123   e124   -e345  -e3    -e4    -e234  -e1345 -e13   -e14   -e1234 e34    e134  
// e34    e134   e234   -e4    e3     e345   e1234  -e14   e13    e1345  -e24   e23    e2345  -one   -e45   e35    -e124  e123   e12345 -e1    -e145  e135   -e2    -e245  e235   -e5    -e12   -e1245 e1235  -e15   -e25   -e125 
// e35    e135   e235   -e5    -e345  -e3    e1235  -e15   -e1345 -e13   -e25   -e2345 -e23   e45    one    e34    -e125  -e12345 -e123  e145   e1     e134   e245   e2     e234   -e4    e1245  e12    e1234  -e14   -e24   -e124 
// e45    e145   e245   e345   -e5    -e4    e1245  e1345  -e15   -e14   e2345  -e25   -e24   -e35   -e34   one    e12345 -e125  -e124  -e135  -e134  e1     -e235  -e234  e2     e3     -e1235 -e1234 e12    e13    e23    e123  
// e123   e23    -e13   e12    e1234  e1235  -e3    e2     e234   e235   -e1    -e134  -e135  e124   e125   e12345 -one   -e34   -e35   e24    e25    e2345  -e14   -e15   -e1345 e1245  -e4    -e5    -e345  e245   -e145  -e45  
// e124   e24    -e14   -e1234 e12    e1245  -e4    -e234  e2     e245   e134   -e1    -e145  -e123  -e12345 e125   e34    -one   -e45   -e23   -e2345 e25    e13    e1345  -e15   -e1235 e3     e345   -e5    -e235  e135   e35   
// e125   e25    -e15   -e1235 -e1245 -e12   -e5    -e235  -e245  -e2    e135   e145   e1     e12345 e123   e124   e35    e45    one    e2345  e23    e24    -e1345 -e13   -e14   -e1234 -e345  -e3    -e4    -e234  e134   e34   
// e134   e34    e1234  -e14   e13    e1345  e234   -e4    e3     e345   -e124  e123   e12345 -e1    -e145  e135   -e24   e23    e2345  -one   -e45   e35    -e12   -e1245 e1235  -e15   -e2    -e245  e235   -e5    -e125  -e25  
// e135   e35    e1235  -e15   -e1345 -e13   e235   -e5    -e345  -e3    -e125  -e12345 -e123  e145   e1     e134   -e25   -e2345 -e23   e45    one    e34    e1245  e12    e1234  -e14   e245   e2     e234   -e4    -e124  -e24  
// e145   e45    e1245  e1345  -e15   -e14   e245   e345   -e5    -e4    e12345 -e125  -e124  -e135  -e134  e1     e2345  -e25   -e24   -e35   -e34   one    -e1235 -e1234 e12    e13    -e235  -e234  e2     e3     e123   e23   
// e234   -e1234 e34    -e24   e23    e2345  -e134  e124   -e123  -e12345 -e4    e3     e345   -e2    -e245  e235   e14    -e13   -e1345 e12    e1245  -e1235 -one   -e45   e35    -e25   e1     e145   -e135  e125   -e5    e15   
// e235   -e1235 e35    -e25   -e2345 -e23   -e135  e125   e12345 e123   -e5    -e345  -e3    e245   e2     e234   e15    e1345  e13    -e1245 -e12   -e1234 e45    one    e34    -e24   -e145  -e1    -e134  e124   -e4    e14   
// e245   -e1245 e45    e2345  -e25   -e24   -e145  -e12345 e125   e124   e345   -e5    -e4    -e235  -e234  e2     -e1345 e15    e14    e1235  e1234  -e12   -e35   -e34   one    e23    e135   e134   -e1    -e123  e3     -e13  
// e345   -e1345 -e2345 e45    -e35   -e34   e12345 -e145  e135   e134   -e245  e235   e234   -e5    -e4    e3     e1245  -e1235 -e1234 e15    e14    -e13   e25    e24    -e23   one    -e125  -e124  e123   -e1    -e2    e12   
// e1234  -e234  e134   -e124  e123   e12345 -e34   e24    -e23   -e2345 -e14   e13    e1345  -e12   -e1245 e1235  e4     -e3    -e345  e2     e245   -e235  -e1    -e145  e135   -e125  -one   e45    -e35   e25    -e15   e5    
// e1235  -e235  e135   -e125  -e12345 -e123  -e35   e25    e2345  e23    -e15   -e1345 -e13   e1245  e12    e1234  e5     e345   e3     -e245  -e2    -e234  e145   e1     e134   -e124  -e45   one    -e34   e24    -e14   e4    
// e1245  -e245  e145   e12345 -e125  -e124  -e45   -e2345 e25    e24    e1345  -e15   -e14   -e1235 -e1234 e12    -e345  e5     e4     e235   e234   -e2    -e135  -e134  e1     e123   e35    e34    one    -e23   e13    -e3   
// e1345  -e345  -e12345 e145   -e135  -e134  e2345  -e45   e35    e34    -e1245 e1235  e1234  -e15   -e14   e13    e245   -e235  -e234  e5     e4     -e3    e125   e124   -e123  e1     -e25   -e24   e23    one    -e12   e2    
// e2345  e12345 -e345  e245   -e235  -e234  -e1345 e1245  -e1235 -e1234 -e45   e35    e34    -e25   -e24   e23    -e145  e135   e134   -e125  -e124  e123   e5     e4     -e3    e2     e15    e14    -e13   e12    one    -e1   
// e12345 e2345  -e1345 e1245  -e1235 -e1234 -e345  e245   -e235  -e234  -e145  e135   e134   -e125  -e124  e123   -e45   e35    e34    -e25   -e24   e23    e15    e14    -e13   e12    e5     e4     -e3    e2     -e1    one   
typedef struct alias_cga3d_000000 { union { float _; }; } alias_cga3d_000000;
typedef struct alias_cga3d_100000 { union { float _; struct { float one; }; }; } alias_cga3d_100000, alias_cga3d_Scalar;
typedef struct alias_cga3d_010000 { union { float _; struct { float e1, e2, e3, e4, e5; }; }; } alias_cga3d_010000, alias_cga3d_Vector;
typedef struct alias_cga3d_110000 { union { float _; struct { float one, e1, e2, e3, e4, e5; }; }; } alias_cga3d_110000;
typedef struct alias_cga3d_001000 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45; }; }; } alias_cga3d_001000, alias_cga3d_Bivector, alias_cga3d_AntiTrivector;
typedef struct alias_cga3d_101000 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45; }; }; } alias_cga3d_101000;
typedef struct alias_cga3d_011000 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45; }; }; } alias_cga3d_011000;
typedef struct alias_cga3d_111000 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45; }; }; } alias_cga3d_111000;
typedef struct alias_cga3d_000100 { union { float _; struct { float e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_000100, alias_cga3d_Trivector, alias_cga3d_AntiBivector;
typedef struct alias_cga3d_100100 { union { float _; struct { float one, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_100100;
typedef struct alias_cga3d_010100 { union { float _; struct { float e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_010100;
typedef struct alias_cga3d_110100 { union { float _; struct { float one, e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_110100;
typedef struct alias_cga3d_001100 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_001100;
typedef struct alias_cga3d_101100 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_101100;
typedef struct alias_cga3d_011100 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_011100;
typedef struct alias_cga3d_111100 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345; }; }; } alias_cga3d_111100;
typedef struct alias_cga3d_000010 { union { float _; struct { float e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_000010, alias_cga3d_AntiVector;
typedef struct alias_cga3d_100010 { union { float _; struct { float one, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_100010;
typedef struct alias_cga3d_010010 { union { float _; struct { float e1, e2, e3, e4, e5, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_010010;
typedef struct alias_cga3d_110010 { union { float _; struct { float one, e1, e2, e3, e4, e5, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_110010;
typedef struct alias_cga3d_001010 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_001010;
typedef struct alias_cga3d_101010 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_101010;
typedef struct alias_cga3d_011010 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_011010;
typedef struct alias_cga3d_111010 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_111010;
typedef struct alias_cga3d_000110 { union { float _; struct { float e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_000110;
typedef struct alias_cga3d_100110 { union { float _; struct { float one, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_100110;
typedef struct alias_cga3d_010110 { union { float _; struct { float e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_010110;
typedef struct alias_cga3d_110110 { union { float _; struct { float one, e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_110110;
typedef struct alias_cga3d_001110 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_001110;
typedef struct alias_cga3d_101110 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_101110;
typedef struct alias_cga3d_011110 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_011110;
typedef struct alias_cga3d_111110 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345; }; }; } alias_cga3d_111110;
typedef struct alias_cga3d_000001 { union { float _; struct { float e12345; }; }; } alias_cga3d_000001, alias_cga3d_AntiScalar;
typedef struct alias_cga3d_100001 { union { float _; struct { float one, e12345; }; }; } alias_cga3d_100001;
typedef struct alias_cga3d_010001 { union { float _; struct { float e1, e2, e3, e4, e5, e12345; }; }; } alias_cga3d_010001;
typedef struct alias_cga3d_110001 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12345; }; }; } alias_cga3d_110001;
typedef struct alias_cga3d_001001 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e12345; }; }; } alias_cga3d_001001;
typedef struct alias_cga3d_101001 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e12345; }; }; } alias_cga3d_101001;
typedef struct alias_cga3d_011001 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e12345; }; }; } alias_cga3d_011001;
typedef struct alias_cga3d_111001 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e12345; }; }; } alias_cga3d_111001;
typedef struct alias_cga3d_000101 { union { float _; struct { float e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_000101;
typedef struct alias_cga3d_100101 { union { float _; struct { float one, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_100101;
typedef struct alias_cga3d_010101 { union { float _; struct { float e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_010101;
typedef struct alias_cga3d_110101 { union { float _; struct { float one, e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_110101;
typedef struct alias_cga3d_001101 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_001101;
typedef struct alias_cga3d_101101 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_101101;
typedef struct alias_cga3d_011101 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_011101;
typedef struct alias_cga3d_111101 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e12345; }; }; } alias_cga3d_111101;
typedef struct alias_cga3d_000011 { union { float _; struct { float e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_000011;
typedef struct alias_cga3d_100011 { union { float _; struct { float one, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_100011;
typedef struct alias_cga3d_010011 { union { float _; struct { float e1, e2, e3, e4, e5, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_010011;
typedef struct alias_cga3d_110011 { union { float _; struct { float one, e1, e2, e3, e4, e5, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_110011;
typedef struct alias_cga3d_001011 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_001011;
typedef struct alias_cga3d_101011 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_101011;
typedef struct alias_cga3d_011011 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_011011;
typedef struct alias_cga3d_111011 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_111011;
typedef struct alias_cga3d_000111 { union { float _; struct { float e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_000111;
typedef struct alias_cga3d_100111 { union { float _; struct { float one, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_100111;
typedef struct alias_cga3d_010111 { union { float _; struct { float e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_010111;
typedef struct alias_cga3d_110111 { union { float _; struct { float one, e1, e2, e3, e4, e5, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_110111;
typedef struct alias_cga3d_001111 { union { float _; struct { float e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_001111;
typedef struct alias_cga3d_101111 { union { float _; struct { float one, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_101111;
typedef struct alias_cga3d_011111 { union { float _; struct { float e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_011111;
typedef struct alias_cga3d_111111 { union { float _; struct { float one, e1, e2, e3, e4, e5, e12, e13, e14, e15, e23, e24, e25, e34, e35, e45, e123, e124, e125, e134, e135, e145, e234, e235, e245, e345, e1234, e1235, e1245, e1345, e2345, e12345; }; }; } alias_cga3d_111111;
#define ALIAS_CGA3D_GRADE(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    ALIAS_CGA3D_IS_NONZERO(Xone) \
  , ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe1), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe2), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe3), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe4), ALIAS_CGA3D_IS_NONZERO(Xe5))))) \
  , ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe12), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe13), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe14), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe15), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe23), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe24), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe25), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe34), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe35), ALIAS_CGA3D_IS_NONZERO(Xe45)))))))))) \
  , ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe123), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe124), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe125), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe134), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe135), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe145), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe234), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe235), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe245), ALIAS_CGA3D_IS_NONZERO(Xe345)))))))))) \
  , ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe1234), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe1235), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe1245), ALIAS_CGA3D_OR(ALIAS_CGA3D_IS_NONZERO(Xe1345), ALIAS_CGA3D_IS_NONZERO(Xe2345))))) \
  , ALIAS_CGA3D_IS_NONZERO(Xe12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_TYPE(X0,X1,X2,X3,X4,X5) ALIAS_CGA3D_TYPE_(X0,X1,X2,X3,X4,X5)
#define ALIAS_CGA3D_TYPE_(X0,X1,X2,X3,X4,X5) alias_cga3d_ ## X0 ## X1 ## X2 ## X3 ## X4 ## X5
#define ALIAS_CGA3D_UNARY(OP, X) ALIAS_CGA3D_UNARY0(OP, ALIAS_CGA3D_UNPACK X)
#define ALIAS_CGA3D_UNARY0(...) ALIAS_CGA3D_UNARY1(__VA_ARGS__)
#define ALIAS_CGA3D_UNARY1(OP, X0,X1,X2,X3,X4,X5,X) ALIAS_CGA3D_UNARY2( \
    OP \
  , ALIAS_CGA3D_IF(X0)(_x.one)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e1)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e2)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e3)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e4)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e5)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e12)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e13)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e14)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e15)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e23)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e24)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e25)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e34)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e35)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e45)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e123)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e124)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e125)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e134)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e135)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e145)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e234)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e235)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e245)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e345)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1234)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1235)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1245)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1345)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e2345)(0) \
  , ALIAS_CGA3D_IF(X5)(_x.e12345)(0) \
  , X0,X1,X2,X3,X4,X5,X \
  )
#define ALIAS_CGA3D_UNARY2(OP, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345,X0,X1,X2,X3,X4,X5,X) OP(ALIAS_CGA3D_UNARY3, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, X0,X1,X2,X3,X4,X5,X)
#define ALIAS_CGA3D_UNARY3(Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X) ALIAS_CGA3D_GRADE(ALIAS_CGA3D_UNARY4, Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345, Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X)
#define ALIAS_CGA3D_UNARY4(Z0,Z1,Z2,Z3,Z4,Z5,Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X) (Z0,Z1,Z2,Z3,Z4,Z5, __extension__ ({ \
  ALIAS_CGA3D_TYPE(X0,X1,X2,X3,X4,X5) _x = X; \
  (ALIAS_CGA3D_TYPE(Z0,Z1,Z2,Z3,Z4,Z5)) { \
    ._ = 0 \
    ALIAS_CGA3D_IF(Z0)(, .one = Zone)() \
    ALIAS_CGA3D_IF(Z1)(, .e1 = Ze1)() \
    ALIAS_CGA3D_IF(Z1)(, .e2 = Ze2)() \
    ALIAS_CGA3D_IF(Z1)(, .e3 = Ze3)() \
    ALIAS_CGA3D_IF(Z1)(, .e4 = Ze4)() \
    ALIAS_CGA3D_IF(Z1)(, .e5 = Ze5)() \
    ALIAS_CGA3D_IF(Z2)(, .e12 = Ze12)() \
    ALIAS_CGA3D_IF(Z2)(, .e13 = Ze13)() \
    ALIAS_CGA3D_IF(Z2)(, .e14 = Ze14)() \
    ALIAS_CGA3D_IF(Z2)(, .e15 = Ze15)() \
    ALIAS_CGA3D_IF(Z2)(, .e23 = Ze23)() \
    ALIAS_CGA3D_IF(Z2)(, .e24 = Ze24)() \
    ALIAS_CGA3D_IF(Z2)(, .e25 = Ze25)() \
    ALIAS_CGA3D_IF(Z2)(, .e34 = Ze34)() \
    ALIAS_CGA3D_IF(Z2)(, .e35 = Ze35)() \
    ALIAS_CGA3D_IF(Z2)(, .e45 = Ze45)() \
    ALIAS_CGA3D_IF(Z3)(, .e123 = Ze123)() \
    ALIAS_CGA3D_IF(Z3)(, .e124 = Ze124)() \
    ALIAS_CGA3D_IF(Z3)(, .e125 = Ze125)() \
    ALIAS_CGA3D_IF(Z3)(, .e134 = Ze134)() \
    ALIAS_CGA3D_IF(Z3)(, .e135 = Ze135)() \
    ALIAS_CGA3D_IF(Z3)(, .e145 = Ze145)() \
    ALIAS_CGA3D_IF(Z3)(, .e234 = Ze234)() \
    ALIAS_CGA3D_IF(Z3)(, .e235 = Ze235)() \
    ALIAS_CGA3D_IF(Z3)(, .e245 = Ze245)() \
    ALIAS_CGA3D_IF(Z3)(, .e345 = Ze345)() \
    ALIAS_CGA3D_IF(Z4)(, .e1234 = Ze1234)() \
    ALIAS_CGA3D_IF(Z4)(, .e1235 = Ze1235)() \
    ALIAS_CGA3D_IF(Z4)(, .e1245 = Ze1245)() \
    ALIAS_CGA3D_IF(Z4)(, .e1345 = Ze1345)() \
    ALIAS_CGA3D_IF(Z4)(, .e2345 = Ze2345)() \
    ALIAS_CGA3D_IF(Z5)(, .e12345 = Ze12345)() \
  }; \
}))
#define ALIAS_CGA3D_OP_GRADE_0(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    Xone \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GRADE_1(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    0 \
  , Xe1 \
  , Xe2 \
  , Xe3 \
  , Xe4 \
  , Xe5 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GRADE_2(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe12 \
  , Xe13 \
  , Xe14 \
  , Xe15 \
  , Xe23 \
  , Xe24 \
  , Xe25 \
  , Xe34 \
  , Xe35 \
  , Xe45 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GRADE_3(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe123 \
  , Xe124 \
  , Xe125 \
  , Xe134 \
  , Xe135 \
  , Xe145 \
  , Xe234 \
  , Xe235 \
  , Xe245 \
  , Xe345 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GRADE_4(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe1234 \
  , Xe1235 \
  , Xe1245 \
  , Xe1345 \
  , Xe2345 \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GRADE_5(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , 0 \
  , Xe12345 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_NEGATE(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    ALIAS_CGA3D_NEG(Xone) \
  , ALIAS_CGA3D_NEG(Xe1) \
  , ALIAS_CGA3D_NEG(Xe2) \
  , ALIAS_CGA3D_NEG(Xe3) \
  , ALIAS_CGA3D_NEG(Xe4) \
  , ALIAS_CGA3D_NEG(Xe5) \
  , ALIAS_CGA3D_NEG(Xe12) \
  , ALIAS_CGA3D_NEG(Xe13) \
  , ALIAS_CGA3D_NEG(Xe14) \
  , ALIAS_CGA3D_NEG(Xe15) \
  , ALIAS_CGA3D_NEG(Xe23) \
  , ALIAS_CGA3D_NEG(Xe24) \
  , ALIAS_CGA3D_NEG(Xe25) \
  , ALIAS_CGA3D_NEG(Xe34) \
  , ALIAS_CGA3D_NEG(Xe35) \
  , ALIAS_CGA3D_NEG(Xe45) \
  , ALIAS_CGA3D_NEG(Xe123) \
  , ALIAS_CGA3D_NEG(Xe124) \
  , ALIAS_CGA3D_NEG(Xe125) \
  , ALIAS_CGA3D_NEG(Xe134) \
  , ALIAS_CGA3D_NEG(Xe135) \
  , ALIAS_CGA3D_NEG(Xe145) \
  , ALIAS_CGA3D_NEG(Xe234) \
  , ALIAS_CGA3D_NEG(Xe235) \
  , ALIAS_CGA3D_NEG(Xe245) \
  , ALIAS_CGA3D_NEG(Xe345) \
  , ALIAS_CGA3D_NEG(Xe1234) \
  , ALIAS_CGA3D_NEG(Xe1235) \
  , ALIAS_CGA3D_NEG(Xe1245) \
  , ALIAS_CGA3D_NEG(Xe1345) \
  , ALIAS_CGA3D_NEG(Xe2345) \
  , ALIAS_CGA3D_NEG(Xe12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_DUAL(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    Xe12345 \
  , Xe2345 \
  , ALIAS_CGA3D_NEG(Xe1345) \
  , Xe1245 \
  , ALIAS_CGA3D_NEG(Xe1235) \
  , ALIAS_CGA3D_NEG(Xe1234) \
  , ALIAS_CGA3D_NEG(Xe345) \
  , Xe245 \
  , ALIAS_CGA3D_NEG(Xe235) \
  , ALIAS_CGA3D_NEG(Xe234) \
  , ALIAS_CGA3D_NEG(Xe145) \
  , Xe135 \
  , Xe134 \
  , ALIAS_CGA3D_NEG(Xe125) \
  , ALIAS_CGA3D_NEG(Xe124) \
  , Xe123 \
  , ALIAS_CGA3D_NEG(Xe45) \
  , Xe35 \
  , Xe34 \
  , ALIAS_CGA3D_NEG(Xe25) \
  , ALIAS_CGA3D_NEG(Xe24) \
  , Xe23 \
  , Xe15 \
  , Xe14 \
  , ALIAS_CGA3D_NEG(Xe13) \
  , Xe12 \
  , Xe5 \
  , Xe4 \
  , ALIAS_CGA3D_NEG(Xe3) \
  , Xe2 \
  , ALIAS_CGA3D_NEG(Xe1) \
  , Xone \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_REVERSE(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    Xone \
  , Xe1 \
  , Xe2 \
  , Xe3 \
  , Xe4 \
  , Xe5 \
  , ALIAS_CGA3D_NEG(Xe12) \
  , ALIAS_CGA3D_NEG(Xe13) \
  , ALIAS_CGA3D_NEG(Xe14) \
  , ALIAS_CGA3D_NEG(Xe15) \
  , ALIAS_CGA3D_NEG(Xe23) \
  , ALIAS_CGA3D_NEG(Xe24) \
  , ALIAS_CGA3D_NEG(Xe25) \
  , ALIAS_CGA3D_NEG(Xe34) \
  , ALIAS_CGA3D_NEG(Xe35) \
  , ALIAS_CGA3D_NEG(Xe45) \
  , ALIAS_CGA3D_NEG(Xe123) \
  , ALIAS_CGA3D_NEG(Xe124) \
  , ALIAS_CGA3D_NEG(Xe125) \
  , ALIAS_CGA3D_NEG(Xe134) \
  , ALIAS_CGA3D_NEG(Xe135) \
  , ALIAS_CGA3D_NEG(Xe145) \
  , ALIAS_CGA3D_NEG(Xe234) \
  , ALIAS_CGA3D_NEG(Xe235) \
  , ALIAS_CGA3D_NEG(Xe245) \
  , ALIAS_CGA3D_NEG(Xe345) \
  , Xe1234 \
  , Xe1235 \
  , Xe1245 \
  , Xe1345 \
  , Xe2345 \
  , Xe12345 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_INVOLUTE(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    Xone \
  , ALIAS_CGA3D_NEG(Xe1) \
  , ALIAS_CGA3D_NEG(Xe2) \
  , ALIAS_CGA3D_NEG(Xe3) \
  , ALIAS_CGA3D_NEG(Xe4) \
  , ALIAS_CGA3D_NEG(Xe5) \
  , Xe12 \
  , Xe13 \
  , Xe14 \
  , Xe15 \
  , Xe23 \
  , Xe24 \
  , Xe25 \
  , Xe34 \
  , Xe35 \
  , Xe45 \
  , ALIAS_CGA3D_NEG(Xe123) \
  , ALIAS_CGA3D_NEG(Xe124) \
  , ALIAS_CGA3D_NEG(Xe125) \
  , ALIAS_CGA3D_NEG(Xe134) \
  , ALIAS_CGA3D_NEG(Xe135) \
  , ALIAS_CGA3D_NEG(Xe145) \
  , ALIAS_CGA3D_NEG(Xe234) \
  , ALIAS_CGA3D_NEG(Xe235) \
  , ALIAS_CGA3D_NEG(Xe245) \
  , ALIAS_CGA3D_NEG(Xe345) \
  , Xe1234 \
  , Xe1235 \
  , Xe1245 \
  , Xe1345 \
  , Xe2345 \
  , ALIAS_CGA3D_NEG(Xe12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_CONJUGATE(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, ...) RETURN( \
    Xone \
  , ALIAS_CGA3D_NEG(Xe1) \
  , ALIAS_CGA3D_NEG(Xe2) \
  , ALIAS_CGA3D_NEG(Xe3) \
  , ALIAS_CGA3D_NEG(Xe4) \
  , ALIAS_CGA3D_NEG(Xe5) \
  , ALIAS_CGA3D_NEG(Xe12) \
  , ALIAS_CGA3D_NEG(Xe13) \
  , ALIAS_CGA3D_NEG(Xe14) \
  , ALIAS_CGA3D_NEG(Xe15) \
  , ALIAS_CGA3D_NEG(Xe23) \
  , ALIAS_CGA3D_NEG(Xe24) \
  , ALIAS_CGA3D_NEG(Xe25) \
  , ALIAS_CGA3D_NEG(Xe34) \
  , ALIAS_CGA3D_NEG(Xe35) \
  , ALIAS_CGA3D_NEG(Xe45) \
  , Xe123 \
  , Xe124 \
  , Xe125 \
  , Xe134 \
  , Xe135 \
  , Xe145 \
  , Xe234 \
  , Xe235 \
  , Xe245 \
  , Xe345 \
  , Xe1234 \
  , Xe1235 \
  , Xe1245 \
  , Xe1345 \
  , Xe2345 \
  , ALIAS_CGA3D_NEG(Xe12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_BINARY(OP, X, Y) ALIAS_CGA3D_BINARY0(OP, ALIAS_CGA3D_UNPACK X, ALIAS_CGA3D_UNPACK Y)
#define ALIAS_CGA3D_BINARY0(...) ALIAS_CGA3D_BINARY1(__VA_ARGS__)
#define ALIAS_CGA3D_BINARY1(OP, X0,X1,X2,X3,X4,X5,X,Y0,Y1,Y2,Y3,Y4,Y5,Y) ALIAS_CGA3D_BINARY2( \
    OP \
  , ALIAS_CGA3D_IF(X0)(_x.one)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e1)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e2)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e3)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e4)(0) \
  , ALIAS_CGA3D_IF(X1)(_x.e5)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e12)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e13)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e14)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e15)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e23)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e24)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e25)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e34)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e35)(0) \
  , ALIAS_CGA3D_IF(X2)(_x.e45)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e123)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e124)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e125)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e134)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e135)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e145)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e234)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e235)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e245)(0) \
  , ALIAS_CGA3D_IF(X3)(_x.e345)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1234)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1235)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1245)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e1345)(0) \
  , ALIAS_CGA3D_IF(X4)(_x.e2345)(0) \
  , ALIAS_CGA3D_IF(X5)(_x.e12345)(0) \
  , ALIAS_CGA3D_IF(Y0)(_y.one)(0) \
  , ALIAS_CGA3D_IF(Y1)(_y.e1)(0) \
  , ALIAS_CGA3D_IF(Y1)(_y.e2)(0) \
  , ALIAS_CGA3D_IF(Y1)(_y.e3)(0) \
  , ALIAS_CGA3D_IF(Y1)(_y.e4)(0) \
  , ALIAS_CGA3D_IF(Y1)(_y.e5)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e12)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e13)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e14)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e15)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e23)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e24)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e25)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e34)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e35)(0) \
  , ALIAS_CGA3D_IF(Y2)(_y.e45)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e123)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e124)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e125)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e134)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e135)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e145)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e234)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e235)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e245)(0) \
  , ALIAS_CGA3D_IF(Y3)(_y.e345)(0) \
  , ALIAS_CGA3D_IF(Y4)(_y.e1234)(0) \
  , ALIAS_CGA3D_IF(Y4)(_y.e1235)(0) \
  , ALIAS_CGA3D_IF(Y4)(_y.e1245)(0) \
  , ALIAS_CGA3D_IF(Y4)(_y.e1345)(0) \
  , ALIAS_CGA3D_IF(Y4)(_y.e2345)(0) \
  , ALIAS_CGA3D_IF(Y5)(_y.e12345)(0) \
  , X0,X1,X2,X3,X4,X5,X \
  , Y0,Y1,Y2,Y3,Y4,Y5,Y \
  )
#define ALIAS_CGA3D_BINARY2(OP, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345,Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345,X0,X1,X2,X3,X4,X5,X, Y0,Y1,Y2,Y3,Y4,Y5,Y) OP(ALIAS_CGA3D_BINARY3, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345,Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, X0,X1,X2,X3,X4,X5,X, Y0,Y1,Y2,Y3,Y4,Y5,Y)
#define ALIAS_CGA3D_BINARY3(Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X, Y0,Y1,Y2,Y3,Y4,Y5,Y) ALIAS_CGA3D_GRADE(ALIAS_CGA3D_BINARY4, Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345, Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X, Y0,Y1,Y2,Y3,Y4,Y5,Y)
#define ALIAS_CGA3D_BINARY4(Z0,Z1,Z2,Z3,Z4,Z5,Zone,Ze1,Ze2,Ze3,Ze4,Ze5,Ze12,Ze13,Ze14,Ze15,Ze23,Ze24,Ze25,Ze34,Ze35,Ze45,Ze123,Ze124,Ze125,Ze134,Ze135,Ze145,Ze234,Ze235,Ze245,Ze345,Ze1234,Ze1235,Ze1245,Ze1345,Ze2345,Ze12345,X0,X1,X2,X3,X4,X5,X, Y0,Y1,Y2,Y3,Y4,Y5,Y) (Z0,Z1,Z2,Z3,Z4,Z5, __extension__ ({ \
  ALIAS_CGA3D_TYPE(X0,X1,X2,X3,X4,X5) _x = X; \
  ALIAS_CGA3D_TYPE(Y0,Y1,Y2,Y3,Y4,Y5) _y = Y; \
  (ALIAS_CGA3D_TYPE(Z0,Z1,Z2,Z3,Z4,Z5)) { \
    ._ = 0 \
    ALIAS_CGA3D_IF(Z0)(, .one = Zone)() \
    ALIAS_CGA3D_IF(Z1)(, .e1 = Ze1)() \
    ALIAS_CGA3D_IF(Z1)(, .e2 = Ze2)() \
    ALIAS_CGA3D_IF(Z1)(, .e3 = Ze3)() \
    ALIAS_CGA3D_IF(Z1)(, .e4 = Ze4)() \
    ALIAS_CGA3D_IF(Z1)(, .e5 = Ze5)() \
    ALIAS_CGA3D_IF(Z2)(, .e12 = Ze12)() \
    ALIAS_CGA3D_IF(Z2)(, .e13 = Ze13)() \
    ALIAS_CGA3D_IF(Z2)(, .e14 = Ze14)() \
    ALIAS_CGA3D_IF(Z2)(, .e15 = Ze15)() \
    ALIAS_CGA3D_IF(Z2)(, .e23 = Ze23)() \
    ALIAS_CGA3D_IF(Z2)(, .e24 = Ze24)() \
    ALIAS_CGA3D_IF(Z2)(, .e25 = Ze25)() \
    ALIAS_CGA3D_IF(Z2)(, .e34 = Ze34)() \
    ALIAS_CGA3D_IF(Z2)(, .e35 = Ze35)() \
    ALIAS_CGA3D_IF(Z2)(, .e45 = Ze45)() \
    ALIAS_CGA3D_IF(Z3)(, .e123 = Ze123)() \
    ALIAS_CGA3D_IF(Z3)(, .e124 = Ze124)() \
    ALIAS_CGA3D_IF(Z3)(, .e125 = Ze125)() \
    ALIAS_CGA3D_IF(Z3)(, .e134 = Ze134)() \
    ALIAS_CGA3D_IF(Z3)(, .e135 = Ze135)() \
    ALIAS_CGA3D_IF(Z3)(, .e145 = Ze145)() \
    ALIAS_CGA3D_IF(Z3)(, .e234 = Ze234)() \
    ALIAS_CGA3D_IF(Z3)(, .e235 = Ze235)() \
    ALIAS_CGA3D_IF(Z3)(, .e245 = Ze245)() \
    ALIAS_CGA3D_IF(Z3)(, .e345 = Ze345)() \
    ALIAS_CGA3D_IF(Z4)(, .e1234 = Ze1234)() \
    ALIAS_CGA3D_IF(Z4)(, .e1235 = Ze1235)() \
    ALIAS_CGA3D_IF(Z4)(, .e1245 = Ze1245)() \
    ALIAS_CGA3D_IF(Z4)(, .e1345 = Ze1345)() \
    ALIAS_CGA3D_IF(Z4)(, .e2345 = Ze2345)() \
    ALIAS_CGA3D_IF(Z5)(, .e12345 = Ze12345)() \
  }; \
}))
#define ALIAS_CGA3D_OP_ADD(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    ALIAS_CGA3D_ADD(Xone, Yone) \
  , ALIAS_CGA3D_ADD(Xe1, Ye1) \
  , ALIAS_CGA3D_ADD(Xe2, Ye2) \
  , ALIAS_CGA3D_ADD(Xe3, Ye3) \
  , ALIAS_CGA3D_ADD(Xe4, Ye4) \
  , ALIAS_CGA3D_ADD(Xe5, Ye5) \
  , ALIAS_CGA3D_ADD(Xe12, Ye12) \
  , ALIAS_CGA3D_ADD(Xe13, Ye13) \
  , ALIAS_CGA3D_ADD(Xe14, Ye14) \
  , ALIAS_CGA3D_ADD(Xe15, Ye15) \
  , ALIAS_CGA3D_ADD(Xe23, Ye23) \
  , ALIAS_CGA3D_ADD(Xe24, Ye24) \
  , ALIAS_CGA3D_ADD(Xe25, Ye25) \
  , ALIAS_CGA3D_ADD(Xe34, Ye34) \
  , ALIAS_CGA3D_ADD(Xe35, Ye35) \
  , ALIAS_CGA3D_ADD(Xe45, Ye45) \
  , ALIAS_CGA3D_ADD(Xe123, Ye123) \
  , ALIAS_CGA3D_ADD(Xe124, Ye124) \
  , ALIAS_CGA3D_ADD(Xe125, Ye125) \
  , ALIAS_CGA3D_ADD(Xe134, Ye134) \
  , ALIAS_CGA3D_ADD(Xe135, Ye135) \
  , ALIAS_CGA3D_ADD(Xe145, Ye145) \
  , ALIAS_CGA3D_ADD(Xe234, Ye234) \
  , ALIAS_CGA3D_ADD(Xe235, Ye235) \
  , ALIAS_CGA3D_ADD(Xe245, Ye245) \
  , ALIAS_CGA3D_ADD(Xe345, Ye345) \
  , ALIAS_CGA3D_ADD(Xe1234, Ye1234) \
  , ALIAS_CGA3D_ADD(Xe1235, Ye1235) \
  , ALIAS_CGA3D_ADD(Xe1245, Ye1245) \
  , ALIAS_CGA3D_ADD(Xe1345, Ye1345) \
  , ALIAS_CGA3D_ADD(Xe2345, Ye2345) \
  , ALIAS_CGA3D_ADD(Xe12345, Ye12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_SUBTRACT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    ALIAS_CGA3D_SUB(Xone, Yone) \
  , ALIAS_CGA3D_SUB(Xe1, Ye1) \
  , ALIAS_CGA3D_SUB(Xe2, Ye2) \
  , ALIAS_CGA3D_SUB(Xe3, Ye3) \
  , ALIAS_CGA3D_SUB(Xe4, Ye4) \
  , ALIAS_CGA3D_SUB(Xe5, Ye5) \
  , ALIAS_CGA3D_SUB(Xe12, Ye12) \
  , ALIAS_CGA3D_SUB(Xe13, Ye13) \
  , ALIAS_CGA3D_SUB(Xe14, Ye14) \
  , ALIAS_CGA3D_SUB(Xe15, Ye15) \
  , ALIAS_CGA3D_SUB(Xe23, Ye23) \
  , ALIAS_CGA3D_SUB(Xe24, Ye24) \
  , ALIAS_CGA3D_SUB(Xe25, Ye25) \
  , ALIAS_CGA3D_SUB(Xe34, Ye34) \
  , ALIAS_CGA3D_SUB(Xe35, Ye35) \
  , ALIAS_CGA3D_SUB(Xe45, Ye45) \
  , ALIAS_CGA3D_SUB(Xe123, Ye123) \
  , ALIAS_CGA3D_SUB(Xe124, Ye124) \
  , ALIAS_CGA3D_SUB(Xe125, Ye125) \
  , ALIAS_CGA3D_SUB(Xe134, Ye134) \
  , ALIAS_CGA3D_SUB(Xe135, Ye135) \
  , ALIAS_CGA3D_SUB(Xe145, Ye145) \
  , ALIAS_CGA3D_SUB(Xe234, Ye234) \
  , ALIAS_CGA3D_SUB(Xe235, Ye235) \
  , ALIAS_CGA3D_SUB(Xe245, Ye245) \
  , ALIAS_CGA3D_SUB(Xe345, Ye345) \
  , ALIAS_CGA3D_SUB(Xe1234, Ye1234) \
  , ALIAS_CGA3D_SUB(Xe1235, Ye1235) \
  , ALIAS_CGA3D_SUB(Xe1245, Ye1245) \
  , ALIAS_CGA3D_SUB(Xe1345, Ye1345) \
  , ALIAS_CGA3D_SUB(Xe2345, Ye2345) \
  , ALIAS_CGA3D_SUB(Xe12345, Ye12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_GEOMETRIC_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 ALIAS_CGA3D_ADD_MUL(Xone,Yone) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2) ALIAS_CGA3D_ADD_MUL(Xe3,Ye3) ALIAS_CGA3D_ADD_MUL(Xe4,Ye4) ALIAS_CGA3D_SUB_MUL(Xe5,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12) ALIAS_CGA3D_SUB_MUL(Xe13,Ye13) ALIAS_CGA3D_SUB_MUL(Xe14,Ye14) ALIAS_CGA3D_ADD_MUL(Xe15,Ye15) ALIAS_CGA3D_SUB_MUL(Xe23,Ye23) ALIAS_CGA3D_SUB_MUL(Xe24,Ye24) ALIAS_CGA3D_ADD_MUL(Xe25,Ye25) ALIAS_CGA3D_SUB_MUL(Xe34,Ye34) ALIAS_CGA3D_ADD_MUL(Xe35,Ye35) ALIAS_CGA3D_ADD_MUL(Xe45,Ye45) ALIAS_CGA3D_SUB_MUL(Xe123,Ye123) ALIAS_CGA3D_SUB_MUL(Xe124,Ye124) ALIAS_CGA3D_ADD_MUL(Xe125,Ye125) ALIAS_CGA3D_SUB_MUL(Xe134,Ye134) ALIAS_CGA3D_ADD_MUL(Xe135,Ye135) ALIAS_CGA3D_ADD_MUL(Xe145,Ye145) ALIAS_CGA3D_SUB_MUL(Xe234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe345,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1,Yone) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye13) ALIAS_CGA3D_SUB_MUL(Xe4,Ye14) ALIAS_CGA3D_ADD_MUL(Xe5,Ye15) ALIAS_CGA3D_ADD_MUL(Xe12,Ye2) ALIAS_CGA3D_ADD_MUL(Xe13,Ye3) ALIAS_CGA3D_ADD_MUL(Xe14,Ye4) ALIAS_CGA3D_SUB_MUL(Xe15,Ye5) ALIAS_CGA3D_SUB_MUL(Xe23,Ye123) ALIAS_CGA3D_SUB_MUL(Xe24,Ye124) ALIAS_CGA3D_ADD_MUL(Xe25,Ye125) ALIAS_CGA3D_SUB_MUL(Xe34,Ye134) ALIAS_CGA3D_ADD_MUL(Xe35,Ye135) ALIAS_CGA3D_ADD_MUL(Xe45,Ye145) ALIAS_CGA3D_SUB_MUL(Xe123,Ye23) ALIAS_CGA3D_SUB_MUL(Xe124,Ye24) ALIAS_CGA3D_ADD_MUL(Xe125,Ye25) ALIAS_CGA3D_SUB_MUL(Xe134,Ye34) ALIAS_CGA3D_ADD_MUL(Xe135,Ye35) ALIAS_CGA3D_ADD_MUL(Xe145,Ye45) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye2345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12) ALIAS_CGA3D_ADD_MUL(Xe2,Yone) ALIAS_CGA3D_SUB_MUL(Xe3,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye24) ALIAS_CGA3D_ADD_MUL(Xe5,Ye25) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1) ALIAS_CGA3D_ADD_MUL(Xe13,Ye123) ALIAS_CGA3D_ADD_MUL(Xe14,Ye124) ALIAS_CGA3D_SUB_MUL(Xe15,Ye125) ALIAS_CGA3D_ADD_MUL(Xe23,Ye3) ALIAS_CGA3D_ADD_MUL(Xe24,Ye4) ALIAS_CGA3D_SUB_MUL(Xe25,Ye5) ALIAS_CGA3D_SUB_MUL(Xe34,Ye234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye245) ALIAS_CGA3D_ADD_MUL(Xe123,Ye13) ALIAS_CGA3D_ADD_MUL(Xe124,Ye14) ALIAS_CGA3D_SUB_MUL(Xe125,Ye15) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe234,Ye34) ALIAS_CGA3D_ADD_MUL(Xe235,Ye35) ALIAS_CGA3D_ADD_MUL(Xe245,Ye45) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye3) ALIAS_CGA3D_ADD_MUL(Xe1,Ye13) ALIAS_CGA3D_ADD_MUL(Xe2,Ye23) ALIAS_CGA3D_ADD_MUL(Xe3,Yone) ALIAS_CGA3D_SUB_MUL(Xe4,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye35) ALIAS_CGA3D_SUB_MUL(Xe12,Ye123) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1) ALIAS_CGA3D_ADD_MUL(Xe14,Ye134) ALIAS_CGA3D_SUB_MUL(Xe15,Ye135) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2) ALIAS_CGA3D_ADD_MUL(Xe24,Ye234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye235) ALIAS_CGA3D_ADD_MUL(Xe34,Ye4) ALIAS_CGA3D_SUB_MUL(Xe35,Ye5) ALIAS_CGA3D_ADD_MUL(Xe45,Ye345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye12) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe134,Ye14) ALIAS_CGA3D_SUB_MUL(Xe135,Ye15) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye24) ALIAS_CGA3D_SUB_MUL(Xe235,Ye25) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye125) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye145) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye245) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2,Ye24) ALIAS_CGA3D_ADD_MUL(Xe3,Ye34) ALIAS_CGA3D_ADD_MUL(Xe4,Yone) ALIAS_CGA3D_ADD_MUL(Xe5,Ye45) ALIAS_CGA3D_SUB_MUL(Xe12,Ye124) ALIAS_CGA3D_SUB_MUL(Xe13,Ye134) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1) ALIAS_CGA3D_SUB_MUL(Xe15,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye234) ALIAS_CGA3D_SUB_MUL(Xe24,Ye2) ALIAS_CGA3D_SUB_MUL(Xe25,Ye245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye3) ALIAS_CGA3D_SUB_MUL(Xe35,Ye345) ALIAS_CGA3D_SUB_MUL(Xe45,Ye5) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe124,Ye12) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye13) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye15) ALIAS_CGA3D_SUB_MUL(Xe234,Ye23) ALIAS_CGA3D_SUB_MUL(Xe235,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe245,Ye25) ALIAS_CGA3D_SUB_MUL(Xe345,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye235) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2,Ye25) ALIAS_CGA3D_ADD_MUL(Xe3,Ye35) ALIAS_CGA3D_ADD_MUL(Xe4,Ye45) ALIAS_CGA3D_ADD_MUL(Xe5,Yone) ALIAS_CGA3D_SUB_MUL(Xe12,Ye125) ALIAS_CGA3D_SUB_MUL(Xe13,Ye135) ALIAS_CGA3D_SUB_MUL(Xe14,Ye145) ALIAS_CGA3D_SUB_MUL(Xe15,Ye1) ALIAS_CGA3D_SUB_MUL(Xe23,Ye235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye245) ALIAS_CGA3D_SUB_MUL(Xe25,Ye2) ALIAS_CGA3D_SUB_MUL(Xe34,Ye345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye3) ALIAS_CGA3D_SUB_MUL(Xe45,Ye4) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe125,Ye12) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye13) ALIAS_CGA3D_SUB_MUL(Xe145,Ye14) ALIAS_CGA3D_SUB_MUL(Xe234,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye23) ALIAS_CGA3D_SUB_MUL(Xe245,Ye24) ALIAS_CGA3D_SUB_MUL(Xe345,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye234) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1,Ye2) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1) ALIAS_CGA3D_ADD_MUL(Xe3,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye124) ALIAS_CGA3D_SUB_MUL(Xe5,Ye125) ALIAS_CGA3D_ADD_MUL(Xe12,Yone) ALIAS_CGA3D_SUB_MUL(Xe13,Ye23) ALIAS_CGA3D_SUB_MUL(Xe14,Ye24) ALIAS_CGA3D_ADD_MUL(Xe15,Ye25) ALIAS_CGA3D_ADD_MUL(Xe23,Ye13) ALIAS_CGA3D_ADD_MUL(Xe24,Ye14) ALIAS_CGA3D_SUB_MUL(Xe25,Ye15) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe123,Ye3) ALIAS_CGA3D_ADD_MUL(Xe124,Ye4) ALIAS_CGA3D_SUB_MUL(Xe125,Ye5) ALIAS_CGA3D_SUB_MUL(Xe134,Ye234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye245) ALIAS_CGA3D_ADD_MUL(Xe234,Ye134) ALIAS_CGA3D_SUB_MUL(Xe235,Ye135) ALIAS_CGA3D_SUB_MUL(Xe245,Ye145) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1,Ye3) ALIAS_CGA3D_SUB_MUL(Xe2,Ye123) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1) ALIAS_CGA3D_ADD_MUL(Xe4,Ye134) ALIAS_CGA3D_SUB_MUL(Xe5,Ye135) ALIAS_CGA3D_ADD_MUL(Xe12,Ye23) ALIAS_CGA3D_ADD_MUL(Xe13,Yone) ALIAS_CGA3D_SUB_MUL(Xe14,Ye34) ALIAS_CGA3D_ADD_MUL(Xe15,Ye35) ALIAS_CGA3D_SUB_MUL(Xe23,Ye12) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe34,Ye14) ALIAS_CGA3D_SUB_MUL(Xe35,Ye15) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye2) ALIAS_CGA3D_ADD_MUL(Xe124,Ye234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye235) ALIAS_CGA3D_ADD_MUL(Xe134,Ye4) ALIAS_CGA3D_SUB_MUL(Xe135,Ye5) ALIAS_CGA3D_ADD_MUL(Xe145,Ye345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye124) ALIAS_CGA3D_ADD_MUL(Xe235,Ye125) ALIAS_CGA3D_SUB_MUL(Xe245,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe345,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye45) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1,Ye4) ALIAS_CGA3D_SUB_MUL(Xe2,Ye124) ALIAS_CGA3D_SUB_MUL(Xe3,Ye134) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1) ALIAS_CGA3D_SUB_MUL(Xe5,Ye145) ALIAS_CGA3D_ADD_MUL(Xe12,Ye24) ALIAS_CGA3D_ADD_MUL(Xe13,Ye34) ALIAS_CGA3D_ADD_MUL(Xe14,Yone) ALIAS_CGA3D_ADD_MUL(Xe15,Ye45) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe24,Ye12) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye13) ALIAS_CGA3D_SUB_MUL(Xe35,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe45,Ye15) ALIAS_CGA3D_SUB_MUL(Xe123,Ye234) ALIAS_CGA3D_SUB_MUL(Xe124,Ye2) ALIAS_CGA3D_SUB_MUL(Xe125,Ye245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye3) ALIAS_CGA3D_SUB_MUL(Xe135,Ye345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye5) ALIAS_CGA3D_ADD_MUL(Xe234,Ye123) ALIAS_CGA3D_ADD_MUL(Xe235,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe245,Ye125) ALIAS_CGA3D_ADD_MUL(Xe345,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye35) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1,Ye5) ALIAS_CGA3D_SUB_MUL(Xe2,Ye125) ALIAS_CGA3D_SUB_MUL(Xe3,Ye135) ALIAS_CGA3D_SUB_MUL(Xe4,Ye145) ALIAS_CGA3D_SUB_MUL(Xe5,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12,Ye25) ALIAS_CGA3D_ADD_MUL(Xe13,Ye35) ALIAS_CGA3D_ADD_MUL(Xe14,Ye45) ALIAS_CGA3D_ADD_MUL(Xe15,Yone) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe25,Ye12) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye13) ALIAS_CGA3D_SUB_MUL(Xe45,Ye14) ALIAS_CGA3D_SUB_MUL(Xe123,Ye235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye245) ALIAS_CGA3D_SUB_MUL(Xe125,Ye2) ALIAS_CGA3D_SUB_MUL(Xe134,Ye345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye3) ALIAS_CGA3D_SUB_MUL(Xe145,Ye4) ALIAS_CGA3D_ADD_MUL(Xe234,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe235,Ye123) ALIAS_CGA3D_ADD_MUL(Xe245,Ye124) ALIAS_CGA3D_ADD_MUL(Xe345,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye34) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye23) ALIAS_CGA3D_ADD_MUL(Xe1,Ye123) ALIAS_CGA3D_ADD_MUL(Xe2,Ye3) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2) ALIAS_CGA3D_ADD_MUL(Xe4,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye235) ALIAS_CGA3D_SUB_MUL(Xe12,Ye13) ALIAS_CGA3D_ADD_MUL(Xe13,Ye12) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe23,Yone) ALIAS_CGA3D_SUB_MUL(Xe24,Ye34) ALIAS_CGA3D_ADD_MUL(Xe25,Ye35) ALIAS_CGA3D_ADD_MUL(Xe34,Ye24) ALIAS_CGA3D_SUB_MUL(Xe35,Ye25) ALIAS_CGA3D_ADD_MUL(Xe45,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe123,Ye1) ALIAS_CGA3D_SUB_MUL(Xe124,Ye134) ALIAS_CGA3D_ADD_MUL(Xe125,Ye135) ALIAS_CGA3D_ADD_MUL(Xe134,Ye124) ALIAS_CGA3D_SUB_MUL(Xe135,Ye125) ALIAS_CGA3D_ADD_MUL(Xe145,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye4) ALIAS_CGA3D_SUB_MUL(Xe235,Ye5) ALIAS_CGA3D_ADD_MUL(Xe245,Ye345) ALIAS_CGA3D_SUB_MUL(Xe345,Ye245) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye15) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye45) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye145) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye24) ALIAS_CGA3D_ADD_MUL(Xe1,Ye124) ALIAS_CGA3D_ADD_MUL(Xe2,Ye4) ALIAS_CGA3D_SUB_MUL(Xe3,Ye234) ALIAS_CGA3D_SUB_MUL(Xe4,Ye2) ALIAS_CGA3D_SUB_MUL(Xe5,Ye245) ALIAS_CGA3D_SUB_MUL(Xe12,Ye14) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe14,Ye12) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe23,Ye34) ALIAS_CGA3D_ADD_MUL(Xe24,Yone) ALIAS_CGA3D_ADD_MUL(Xe25,Ye45) ALIAS_CGA3D_SUB_MUL(Xe34,Ye23) ALIAS_CGA3D_SUB_MUL(Xe35,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe45,Ye25) ALIAS_CGA3D_ADD_MUL(Xe123,Ye134) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1) ALIAS_CGA3D_ADD_MUL(Xe125,Ye145) ALIAS_CGA3D_SUB_MUL(Xe134,Ye123) ALIAS_CGA3D_SUB_MUL(Xe135,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye125) ALIAS_CGA3D_SUB_MUL(Xe234,Ye3) ALIAS_CGA3D_SUB_MUL(Xe235,Ye345) ALIAS_CGA3D_SUB_MUL(Xe245,Ye5) ALIAS_CGA3D_ADD_MUL(Xe345,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye15) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye35) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye135) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1,Ye125) ALIAS_CGA3D_ADD_MUL(Xe2,Ye5) ALIAS_CGA3D_SUB_MUL(Xe3,Ye235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye245) ALIAS_CGA3D_SUB_MUL(Xe5,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12,Ye15) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe15,Ye12) ALIAS_CGA3D_ADD_MUL(Xe23,Ye35) ALIAS_CGA3D_ADD_MUL(Xe24,Ye45) ALIAS_CGA3D_ADD_MUL(Xe25,Yone) ALIAS_CGA3D_SUB_MUL(Xe34,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye23) ALIAS_CGA3D_SUB_MUL(Xe45,Ye24) ALIAS_CGA3D_ADD_MUL(Xe123,Ye135) ALIAS_CGA3D_ADD_MUL(Xe124,Ye145) ALIAS_CGA3D_ADD_MUL(Xe125,Ye1) ALIAS_CGA3D_SUB_MUL(Xe134,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye123) ALIAS_CGA3D_SUB_MUL(Xe145,Ye124) ALIAS_CGA3D_SUB_MUL(Xe234,Ye345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye3) ALIAS_CGA3D_SUB_MUL(Xe245,Ye4) ALIAS_CGA3D_ADD_MUL(Xe345,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye14) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye34) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye134) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2,Ye234) ALIAS_CGA3D_ADD_MUL(Xe3,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye3) ALIAS_CGA3D_SUB_MUL(Xe5,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe13,Ye14) ALIAS_CGA3D_ADD_MUL(Xe14,Ye13) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye24) ALIAS_CGA3D_ADD_MUL(Xe24,Ye23) ALIAS_CGA3D_ADD_MUL(Xe25,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe34,Yone) ALIAS_CGA3D_ADD_MUL(Xe35,Ye45) ALIAS_CGA3D_SUB_MUL(Xe45,Ye35) ALIAS_CGA3D_SUB_MUL(Xe123,Ye124) ALIAS_CGA3D_ADD_MUL(Xe124,Ye123) ALIAS_CGA3D_ADD_MUL(Xe125,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye1) ALIAS_CGA3D_ADD_MUL(Xe135,Ye145) ALIAS_CGA3D_SUB_MUL(Xe145,Ye135) ALIAS_CGA3D_ADD_MUL(Xe234,Ye2) ALIAS_CGA3D_ADD_MUL(Xe235,Ye245) ALIAS_CGA3D_SUB_MUL(Xe245,Ye235) ALIAS_CGA3D_SUB_MUL(Xe345,Ye5) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye12) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye25) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye125) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2,Ye235) ALIAS_CGA3D_ADD_MUL(Xe3,Ye5) ALIAS_CGA3D_SUB_MUL(Xe4,Ye345) ALIAS_CGA3D_SUB_MUL(Xe5,Ye3) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe13,Ye15) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe15,Ye13) ALIAS_CGA3D_SUB_MUL(Xe23,Ye25) ALIAS_CGA3D_ADD_MUL(Xe24,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye23) ALIAS_CGA3D_ADD_MUL(Xe34,Ye45) ALIAS_CGA3D_ADD_MUL(Xe35,Yone) ALIAS_CGA3D_SUB_MUL(Xe45,Ye34) ALIAS_CGA3D_SUB_MUL(Xe123,Ye125) ALIAS_CGA3D_ADD_MUL(Xe124,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe125,Ye123) ALIAS_CGA3D_ADD_MUL(Xe134,Ye145) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1) ALIAS_CGA3D_SUB_MUL(Xe145,Ye134) ALIAS_CGA3D_ADD_MUL(Xe234,Ye245) ALIAS_CGA3D_ADD_MUL(Xe235,Ye2) ALIAS_CGA3D_SUB_MUL(Xe245,Ye234) ALIAS_CGA3D_SUB_MUL(Xe345,Ye4) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye24) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye124) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1,Ye145) ALIAS_CGA3D_ADD_MUL(Xe2,Ye245) ALIAS_CGA3D_ADD_MUL(Xe3,Ye345) ALIAS_CGA3D_ADD_MUL(Xe4,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye4) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe14,Ye15) ALIAS_CGA3D_ADD_MUL(Xe15,Ye14) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe24,Ye25) ALIAS_CGA3D_ADD_MUL(Xe25,Ye24) ALIAS_CGA3D_SUB_MUL(Xe34,Ye35) ALIAS_CGA3D_ADD_MUL(Xe35,Ye34) ALIAS_CGA3D_ADD_MUL(Xe45,Yone) ALIAS_CGA3D_SUB_MUL(Xe123,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe124,Ye125) ALIAS_CGA3D_ADD_MUL(Xe125,Ye124) ALIAS_CGA3D_SUB_MUL(Xe134,Ye135) ALIAS_CGA3D_ADD_MUL(Xe135,Ye134) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1) ALIAS_CGA3D_SUB_MUL(Xe234,Ye235) ALIAS_CGA3D_ADD_MUL(Xe235,Ye234) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2) ALIAS_CGA3D_ADD_MUL(Xe345,Ye3) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye12) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye13) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye23) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye123) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1,Ye23) ALIAS_CGA3D_SUB_MUL(Xe2,Ye13) ALIAS_CGA3D_ADD_MUL(Xe3,Ye12) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe12,Ye3) ALIAS_CGA3D_SUB_MUL(Xe13,Ye2) ALIAS_CGA3D_ADD_MUL(Xe14,Ye234) ALIAS_CGA3D_SUB_MUL(Xe15,Ye235) ALIAS_CGA3D_ADD_MUL(Xe23,Ye1) ALIAS_CGA3D_SUB_MUL(Xe24,Ye134) ALIAS_CGA3D_ADD_MUL(Xe25,Ye135) ALIAS_CGA3D_ADD_MUL(Xe34,Ye124) ALIAS_CGA3D_SUB_MUL(Xe35,Ye125) ALIAS_CGA3D_ADD_MUL(Xe45,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe123,Yone) ALIAS_CGA3D_SUB_MUL(Xe124,Ye34) ALIAS_CGA3D_ADD_MUL(Xe125,Ye35) ALIAS_CGA3D_ADD_MUL(Xe134,Ye24) ALIAS_CGA3D_SUB_MUL(Xe135,Ye25) ALIAS_CGA3D_ADD_MUL(Xe145,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye14) ALIAS_CGA3D_ADD_MUL(Xe235,Ye15) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye4) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye245) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye145) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye45) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1,Ye24) ALIAS_CGA3D_SUB_MUL(Xe2,Ye14) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe4,Ye12) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe12,Ye4) ALIAS_CGA3D_SUB_MUL(Xe13,Ye234) ALIAS_CGA3D_SUB_MUL(Xe14,Ye2) ALIAS_CGA3D_SUB_MUL(Xe15,Ye245) ALIAS_CGA3D_ADD_MUL(Xe23,Ye134) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1) ALIAS_CGA3D_ADD_MUL(Xe25,Ye145) ALIAS_CGA3D_SUB_MUL(Xe34,Ye123) ALIAS_CGA3D_SUB_MUL(Xe35,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe45,Ye125) ALIAS_CGA3D_ADD_MUL(Xe123,Ye34) ALIAS_CGA3D_ADD_MUL(Xe124,Yone) ALIAS_CGA3D_ADD_MUL(Xe125,Ye45) ALIAS_CGA3D_SUB_MUL(Xe134,Ye23) ALIAS_CGA3D_SUB_MUL(Xe135,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye25) ALIAS_CGA3D_ADD_MUL(Xe234,Ye13) ALIAS_CGA3D_ADD_MUL(Xe235,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe245,Ye15) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye235) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye135) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye35) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1,Ye25) ALIAS_CGA3D_SUB_MUL(Xe2,Ye15) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe5,Ye12) ALIAS_CGA3D_ADD_MUL(Xe12,Ye5) ALIAS_CGA3D_SUB_MUL(Xe13,Ye235) ALIAS_CGA3D_SUB_MUL(Xe14,Ye245) ALIAS_CGA3D_SUB_MUL(Xe15,Ye2) ALIAS_CGA3D_ADD_MUL(Xe23,Ye135) ALIAS_CGA3D_ADD_MUL(Xe24,Ye145) ALIAS_CGA3D_ADD_MUL(Xe25,Ye1) ALIAS_CGA3D_SUB_MUL(Xe34,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye123) ALIAS_CGA3D_SUB_MUL(Xe45,Ye124) ALIAS_CGA3D_ADD_MUL(Xe123,Ye35) ALIAS_CGA3D_ADD_MUL(Xe124,Ye45) ALIAS_CGA3D_ADD_MUL(Xe125,Yone) ALIAS_CGA3D_SUB_MUL(Xe134,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye23) ALIAS_CGA3D_SUB_MUL(Xe145,Ye24) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe235,Ye13) ALIAS_CGA3D_ADD_MUL(Xe245,Ye14) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye234) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye134) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye34) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye134) ALIAS_CGA3D_ADD_MUL(Xe1,Ye34) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe3,Ye14) ALIAS_CGA3D_ADD_MUL(Xe4,Ye13) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye234) ALIAS_CGA3D_ADD_MUL(Xe13,Ye4) ALIAS_CGA3D_SUB_MUL(Xe14,Ye3) ALIAS_CGA3D_SUB_MUL(Xe15,Ye345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye124) ALIAS_CGA3D_ADD_MUL(Xe24,Ye123) ALIAS_CGA3D_ADD_MUL(Xe25,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye1) ALIAS_CGA3D_ADD_MUL(Xe35,Ye145) ALIAS_CGA3D_SUB_MUL(Xe45,Ye135) ALIAS_CGA3D_SUB_MUL(Xe123,Ye24) ALIAS_CGA3D_ADD_MUL(Xe124,Ye23) ALIAS_CGA3D_ADD_MUL(Xe125,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe134,Yone) ALIAS_CGA3D_ADD_MUL(Xe135,Ye45) ALIAS_CGA3D_SUB_MUL(Xe145,Ye35) ALIAS_CGA3D_SUB_MUL(Xe234,Ye12) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe245,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe345,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye245) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye235) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye5) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye125) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye25) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye135) ALIAS_CGA3D_ADD_MUL(Xe1,Ye35) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe3,Ye15) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe5,Ye13) ALIAS_CGA3D_ADD_MUL(Xe12,Ye235) ALIAS_CGA3D_ADD_MUL(Xe13,Ye5) ALIAS_CGA3D_SUB_MUL(Xe14,Ye345) ALIAS_CGA3D_SUB_MUL(Xe15,Ye3) ALIAS_CGA3D_SUB_MUL(Xe23,Ye125) ALIAS_CGA3D_ADD_MUL(Xe24,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye123) ALIAS_CGA3D_ADD_MUL(Xe34,Ye145) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1) ALIAS_CGA3D_SUB_MUL(Xe45,Ye134) ALIAS_CGA3D_SUB_MUL(Xe123,Ye25) ALIAS_CGA3D_ADD_MUL(Xe124,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe125,Ye23) ALIAS_CGA3D_ADD_MUL(Xe134,Ye45) ALIAS_CGA3D_ADD_MUL(Xe135,Yone) ALIAS_CGA3D_SUB_MUL(Xe145,Ye34) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe235,Ye12) ALIAS_CGA3D_ADD_MUL(Xe245,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe345,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye234) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye4) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye124) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye24) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1,Ye45) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe4,Ye15) ALIAS_CGA3D_ADD_MUL(Xe5,Ye14) ALIAS_CGA3D_ADD_MUL(Xe12,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye345) ALIAS_CGA3D_ADD_MUL(Xe14,Ye5) ALIAS_CGA3D_SUB_MUL(Xe15,Ye4) ALIAS_CGA3D_SUB_MUL(Xe23,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe24,Ye125) ALIAS_CGA3D_ADD_MUL(Xe25,Ye124) ALIAS_CGA3D_SUB_MUL(Xe34,Ye135) ALIAS_CGA3D_ADD_MUL(Xe35,Ye134) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1) ALIAS_CGA3D_SUB_MUL(Xe123,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe124,Ye25) ALIAS_CGA3D_ADD_MUL(Xe125,Ye24) ALIAS_CGA3D_SUB_MUL(Xe134,Ye35) ALIAS_CGA3D_ADD_MUL(Xe135,Ye34) ALIAS_CGA3D_ADD_MUL(Xe145,Yone) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe245,Ye12) ALIAS_CGA3D_SUB_MUL(Xe345,Ye13) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye3) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye123) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye23) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe2,Ye34) ALIAS_CGA3D_SUB_MUL(Xe3,Ye24) ALIAS_CGA3D_ADD_MUL(Xe4,Ye23) ALIAS_CGA3D_ADD_MUL(Xe5,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye134) ALIAS_CGA3D_ADD_MUL(Xe13,Ye124) ALIAS_CGA3D_SUB_MUL(Xe14,Ye123) ALIAS_CGA3D_SUB_MUL(Xe15,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe23,Ye4) ALIAS_CGA3D_SUB_MUL(Xe24,Ye3) ALIAS_CGA3D_SUB_MUL(Xe25,Ye345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye2) ALIAS_CGA3D_ADD_MUL(Xe35,Ye245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye235) ALIAS_CGA3D_ADD_MUL(Xe123,Ye14) ALIAS_CGA3D_SUB_MUL(Xe124,Ye13) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye12) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe145,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe234,Yone) ALIAS_CGA3D_ADD_MUL(Xe235,Ye45) ALIAS_CGA3D_SUB_MUL(Xe245,Ye35) ALIAS_CGA3D_ADD_MUL(Xe345,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye125) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye15) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe2,Ye35) ALIAS_CGA3D_SUB_MUL(Xe3,Ye25) ALIAS_CGA3D_ADD_MUL(Xe4,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe5,Ye23) ALIAS_CGA3D_SUB_MUL(Xe12,Ye135) ALIAS_CGA3D_ADD_MUL(Xe13,Ye125) ALIAS_CGA3D_SUB_MUL(Xe14,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe15,Ye123) ALIAS_CGA3D_ADD_MUL(Xe23,Ye5) ALIAS_CGA3D_SUB_MUL(Xe24,Ye345) ALIAS_CGA3D_SUB_MUL(Xe25,Ye3) ALIAS_CGA3D_ADD_MUL(Xe34,Ye245) ALIAS_CGA3D_ADD_MUL(Xe35,Ye2) ALIAS_CGA3D_SUB_MUL(Xe45,Ye234) ALIAS_CGA3D_ADD_MUL(Xe123,Ye15) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe125,Ye13) ALIAS_CGA3D_ADD_MUL(Xe134,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe135,Ye12) ALIAS_CGA3D_SUB_MUL(Xe145,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe234,Ye45) ALIAS_CGA3D_ADD_MUL(Xe235,Yone) ALIAS_CGA3D_SUB_MUL(Xe245,Ye34) ALIAS_CGA3D_ADD_MUL(Xe345,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye145) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye124) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye4) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye14) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe2,Ye45) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe4,Ye25) ALIAS_CGA3D_ADD_MUL(Xe5,Ye24) ALIAS_CGA3D_SUB_MUL(Xe12,Ye145) ALIAS_CGA3D_ADD_MUL(Xe13,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe14,Ye125) ALIAS_CGA3D_SUB_MUL(Xe15,Ye124) ALIAS_CGA3D_ADD_MUL(Xe23,Ye345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye5) ALIAS_CGA3D_SUB_MUL(Xe25,Ye4) ALIAS_CGA3D_SUB_MUL(Xe34,Ye235) ALIAS_CGA3D_ADD_MUL(Xe35,Ye234) ALIAS_CGA3D_ADD_MUL(Xe45,Ye2) ALIAS_CGA3D_ADD_MUL(Xe123,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye15) ALIAS_CGA3D_SUB_MUL(Xe125,Ye14) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe145,Ye12) ALIAS_CGA3D_SUB_MUL(Xe234,Ye35) ALIAS_CGA3D_ADD_MUL(Xe235,Ye34) ALIAS_CGA3D_ADD_MUL(Xe245,Yone) ALIAS_CGA3D_SUB_MUL(Xe345,Ye23) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye123) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye3) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye13) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe3,Ye45) ALIAS_CGA3D_SUB_MUL(Xe4,Ye35) ALIAS_CGA3D_ADD_MUL(Xe5,Ye34) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe13,Ye145) ALIAS_CGA3D_ADD_MUL(Xe14,Ye135) ALIAS_CGA3D_SUB_MUL(Xe15,Ye134) ALIAS_CGA3D_SUB_MUL(Xe23,Ye245) ALIAS_CGA3D_ADD_MUL(Xe24,Ye235) ALIAS_CGA3D_SUB_MUL(Xe25,Ye234) ALIAS_CGA3D_ADD_MUL(Xe34,Ye5) ALIAS_CGA3D_SUB_MUL(Xe35,Ye4) ALIAS_CGA3D_ADD_MUL(Xe45,Ye3) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe134,Ye15) ALIAS_CGA3D_SUB_MUL(Xe135,Ye14) ALIAS_CGA3D_ADD_MUL(Xe145,Ye13) ALIAS_CGA3D_ADD_MUL(Xe234,Ye25) ALIAS_CGA3D_SUB_MUL(Xe235,Ye24) ALIAS_CGA3D_ADD_MUL(Xe245,Ye23) ALIAS_CGA3D_ADD_MUL(Xe345,Yone) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye124) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye123) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye12) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1,Ye234) ALIAS_CGA3D_SUB_MUL(Xe2,Ye134) ALIAS_CGA3D_ADD_MUL(Xe3,Ye124) ALIAS_CGA3D_SUB_MUL(Xe4,Ye123) ALIAS_CGA3D_SUB_MUL(Xe5,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye34) ALIAS_CGA3D_SUB_MUL(Xe13,Ye24) ALIAS_CGA3D_ADD_MUL(Xe14,Ye23) ALIAS_CGA3D_ADD_MUL(Xe15,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe23,Ye14) ALIAS_CGA3D_SUB_MUL(Xe24,Ye13) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye12) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe123,Ye4) ALIAS_CGA3D_SUB_MUL(Xe124,Ye3) ALIAS_CGA3D_SUB_MUL(Xe125,Ye345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye2) ALIAS_CGA3D_ADD_MUL(Xe135,Ye245) ALIAS_CGA3D_SUB_MUL(Xe145,Ye235) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1) ALIAS_CGA3D_SUB_MUL(Xe235,Ye145) ALIAS_CGA3D_ADD_MUL(Xe245,Ye135) ALIAS_CGA3D_SUB_MUL(Xe345,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1234,Yone) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye25) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye15) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1,Ye235) ALIAS_CGA3D_SUB_MUL(Xe2,Ye135) ALIAS_CGA3D_ADD_MUL(Xe3,Ye125) ALIAS_CGA3D_SUB_MUL(Xe4,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe5,Ye123) ALIAS_CGA3D_ADD_MUL(Xe12,Ye35) ALIAS_CGA3D_SUB_MUL(Xe13,Ye25) ALIAS_CGA3D_ADD_MUL(Xe14,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe15,Ye23) ALIAS_CGA3D_ADD_MUL(Xe23,Ye15) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe25,Ye13) ALIAS_CGA3D_ADD_MUL(Xe34,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe35,Ye12) ALIAS_CGA3D_SUB_MUL(Xe45,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe123,Ye5) ALIAS_CGA3D_SUB_MUL(Xe124,Ye345) ALIAS_CGA3D_SUB_MUL(Xe125,Ye3) ALIAS_CGA3D_ADD_MUL(Xe134,Ye245) ALIAS_CGA3D_ADD_MUL(Xe135,Ye2) ALIAS_CGA3D_SUB_MUL(Xe145,Ye234) ALIAS_CGA3D_SUB_MUL(Xe234,Ye145) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1) ALIAS_CGA3D_ADD_MUL(Xe245,Ye134) ALIAS_CGA3D_SUB_MUL(Xe345,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1235,Yone) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye24) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye14) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye4) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1,Ye245) ALIAS_CGA3D_SUB_MUL(Xe2,Ye145) ALIAS_CGA3D_ADD_MUL(Xe3,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe4,Ye125) ALIAS_CGA3D_SUB_MUL(Xe5,Ye124) ALIAS_CGA3D_ADD_MUL(Xe12,Ye45) ALIAS_CGA3D_SUB_MUL(Xe13,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe14,Ye25) ALIAS_CGA3D_ADD_MUL(Xe15,Ye24) ALIAS_CGA3D_ADD_MUL(Xe23,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye15) ALIAS_CGA3D_SUB_MUL(Xe25,Ye14) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe45,Ye12) ALIAS_CGA3D_ADD_MUL(Xe123,Ye345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye5) ALIAS_CGA3D_SUB_MUL(Xe125,Ye4) ALIAS_CGA3D_SUB_MUL(Xe134,Ye235) ALIAS_CGA3D_ADD_MUL(Xe135,Ye234) ALIAS_CGA3D_ADD_MUL(Xe145,Ye2) ALIAS_CGA3D_ADD_MUL(Xe234,Ye135) ALIAS_CGA3D_SUB_MUL(Xe235,Ye134) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1) ALIAS_CGA3D_ADD_MUL(Xe345,Ye123) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1245,Yone) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye23) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye13) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye3) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye345) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye145) ALIAS_CGA3D_ADD_MUL(Xe4,Ye135) ALIAS_CGA3D_SUB_MUL(Xe5,Ye134) ALIAS_CGA3D_ADD_MUL(Xe12,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye45) ALIAS_CGA3D_SUB_MUL(Xe14,Ye35) ALIAS_CGA3D_ADD_MUL(Xe15,Ye34) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe34,Ye15) ALIAS_CGA3D_SUB_MUL(Xe35,Ye14) ALIAS_CGA3D_ADD_MUL(Xe45,Ye13) ALIAS_CGA3D_SUB_MUL(Xe123,Ye245) ALIAS_CGA3D_ADD_MUL(Xe124,Ye235) ALIAS_CGA3D_SUB_MUL(Xe125,Ye234) ALIAS_CGA3D_ADD_MUL(Xe134,Ye5) ALIAS_CGA3D_SUB_MUL(Xe135,Ye4) ALIAS_CGA3D_ADD_MUL(Xe145,Ye3) ALIAS_CGA3D_SUB_MUL(Xe234,Ye125) ALIAS_CGA3D_ADD_MUL(Xe235,Ye124) ALIAS_CGA3D_SUB_MUL(Xe245,Ye123) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye24) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye23) ALIAS_CGA3D_ADD_MUL(Xe1345,Yone) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye12) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye2) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye245) ALIAS_CGA3D_ADD_MUL(Xe4,Ye235) ALIAS_CGA3D_SUB_MUL(Xe5,Ye234) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe23,Ye45) ALIAS_CGA3D_SUB_MUL(Xe24,Ye35) ALIAS_CGA3D_ADD_MUL(Xe25,Ye34) ALIAS_CGA3D_ADD_MUL(Xe34,Ye25) ALIAS_CGA3D_SUB_MUL(Xe35,Ye24) ALIAS_CGA3D_ADD_MUL(Xe45,Ye23) ALIAS_CGA3D_ADD_MUL(Xe123,Ye145) ALIAS_CGA3D_SUB_MUL(Xe124,Ye135) ALIAS_CGA3D_ADD_MUL(Xe125,Ye134) ALIAS_CGA3D_ADD_MUL(Xe134,Ye125) ALIAS_CGA3D_SUB_MUL(Xe135,Ye124) ALIAS_CGA3D_ADD_MUL(Xe145,Ye123) ALIAS_CGA3D_ADD_MUL(Xe234,Ye5) ALIAS_CGA3D_SUB_MUL(Xe235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe245,Ye3) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye14) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye12) ALIAS_CGA3D_ADD_MUL(Xe2345,Yone) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12,Ye345) ALIAS_CGA3D_SUB_MUL(Xe13,Ye245) ALIAS_CGA3D_ADD_MUL(Xe14,Ye235) ALIAS_CGA3D_SUB_MUL(Xe15,Ye234) ALIAS_CGA3D_ADD_MUL(Xe23,Ye145) ALIAS_CGA3D_SUB_MUL(Xe24,Ye135) ALIAS_CGA3D_ADD_MUL(Xe25,Ye134) ALIAS_CGA3D_ADD_MUL(Xe34,Ye125) ALIAS_CGA3D_SUB_MUL(Xe35,Ye124) ALIAS_CGA3D_ADD_MUL(Xe45,Ye123) ALIAS_CGA3D_ADD_MUL(Xe123,Ye45) ALIAS_CGA3D_SUB_MUL(Xe124,Ye35) ALIAS_CGA3D_ADD_MUL(Xe125,Ye34) ALIAS_CGA3D_ADD_MUL(Xe134,Ye25) ALIAS_CGA3D_SUB_MUL(Xe135,Ye24) ALIAS_CGA3D_ADD_MUL(Xe145,Ye23) ALIAS_CGA3D_SUB_MUL(Xe234,Ye15) ALIAS_CGA3D_ADD_MUL(Xe235,Ye14) ALIAS_CGA3D_SUB_MUL(Xe245,Ye13) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye5) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye2) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12345,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_OUTER_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 ALIAS_CGA3D_ADD_MUL(Xone,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2) ALIAS_CGA3D_ADD_MUL(Xe2,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye3) ALIAS_CGA3D_ADD_MUL(Xe3,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye4) ALIAS_CGA3D_ADD_MUL(Xe4,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye5) ALIAS_CGA3D_ADD_MUL(Xe5,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1,Ye2) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1,Ye3) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1) ALIAS_CGA3D_ADD_MUL(Xe13,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1) ALIAS_CGA3D_ADD_MUL(Xe14,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye1) ALIAS_CGA3D_ADD_MUL(Xe15,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye23) ALIAS_CGA3D_ADD_MUL(Xe2,Ye3) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2) ALIAS_CGA3D_ADD_MUL(Xe23,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye24) ALIAS_CGA3D_ADD_MUL(Xe2,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye2) ALIAS_CGA3D_ADD_MUL(Xe24,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye25) ALIAS_CGA3D_ADD_MUL(Xe2,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye2) ALIAS_CGA3D_ADD_MUL(Xe25,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye34) ALIAS_CGA3D_ADD_MUL(Xe3,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye3) ALIAS_CGA3D_ADD_MUL(Xe34,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye35) ALIAS_CGA3D_ADD_MUL(Xe3,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye3) ALIAS_CGA3D_ADD_MUL(Xe35,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye45) ALIAS_CGA3D_ADD_MUL(Xe4,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye4) ALIAS_CGA3D_ADD_MUL(Xe45,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1,Ye23) ALIAS_CGA3D_SUB_MUL(Xe2,Ye13) ALIAS_CGA3D_ADD_MUL(Xe3,Ye12) ALIAS_CGA3D_ADD_MUL(Xe12,Ye3) ALIAS_CGA3D_SUB_MUL(Xe13,Ye2) ALIAS_CGA3D_ADD_MUL(Xe23,Ye1) ALIAS_CGA3D_ADD_MUL(Xe123,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1,Ye24) ALIAS_CGA3D_SUB_MUL(Xe2,Ye14) ALIAS_CGA3D_ADD_MUL(Xe4,Ye12) ALIAS_CGA3D_ADD_MUL(Xe12,Ye4) ALIAS_CGA3D_SUB_MUL(Xe14,Ye2) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1) ALIAS_CGA3D_ADD_MUL(Xe124,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1,Ye25) ALIAS_CGA3D_SUB_MUL(Xe2,Ye15) ALIAS_CGA3D_ADD_MUL(Xe5,Ye12) ALIAS_CGA3D_ADD_MUL(Xe12,Ye5) ALIAS_CGA3D_SUB_MUL(Xe15,Ye2) ALIAS_CGA3D_ADD_MUL(Xe25,Ye1) ALIAS_CGA3D_ADD_MUL(Xe125,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye134) ALIAS_CGA3D_ADD_MUL(Xe1,Ye34) ALIAS_CGA3D_SUB_MUL(Xe3,Ye14) ALIAS_CGA3D_ADD_MUL(Xe4,Ye13) ALIAS_CGA3D_ADD_MUL(Xe13,Ye4) ALIAS_CGA3D_SUB_MUL(Xe14,Ye3) ALIAS_CGA3D_ADD_MUL(Xe34,Ye1) ALIAS_CGA3D_ADD_MUL(Xe134,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye135) ALIAS_CGA3D_ADD_MUL(Xe1,Ye35) ALIAS_CGA3D_SUB_MUL(Xe3,Ye15) ALIAS_CGA3D_ADD_MUL(Xe5,Ye13) ALIAS_CGA3D_ADD_MUL(Xe13,Ye5) ALIAS_CGA3D_SUB_MUL(Xe15,Ye3) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1) ALIAS_CGA3D_ADD_MUL(Xe135,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1,Ye45) ALIAS_CGA3D_SUB_MUL(Xe4,Ye15) ALIAS_CGA3D_ADD_MUL(Xe5,Ye14) ALIAS_CGA3D_ADD_MUL(Xe14,Ye5) ALIAS_CGA3D_SUB_MUL(Xe15,Ye4) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1) ALIAS_CGA3D_ADD_MUL(Xe145,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye234) ALIAS_CGA3D_ADD_MUL(Xe2,Ye34) ALIAS_CGA3D_SUB_MUL(Xe3,Ye24) ALIAS_CGA3D_ADD_MUL(Xe4,Ye23) ALIAS_CGA3D_ADD_MUL(Xe23,Ye4) ALIAS_CGA3D_SUB_MUL(Xe24,Ye3) ALIAS_CGA3D_ADD_MUL(Xe34,Ye2) ALIAS_CGA3D_ADD_MUL(Xe234,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye235) ALIAS_CGA3D_ADD_MUL(Xe2,Ye35) ALIAS_CGA3D_SUB_MUL(Xe3,Ye25) ALIAS_CGA3D_ADD_MUL(Xe5,Ye23) ALIAS_CGA3D_ADD_MUL(Xe23,Ye5) ALIAS_CGA3D_SUB_MUL(Xe25,Ye3) ALIAS_CGA3D_ADD_MUL(Xe35,Ye2) ALIAS_CGA3D_ADD_MUL(Xe235,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye245) ALIAS_CGA3D_ADD_MUL(Xe2,Ye45) ALIAS_CGA3D_SUB_MUL(Xe4,Ye25) ALIAS_CGA3D_ADD_MUL(Xe5,Ye24) ALIAS_CGA3D_ADD_MUL(Xe24,Ye5) ALIAS_CGA3D_SUB_MUL(Xe25,Ye4) ALIAS_CGA3D_ADD_MUL(Xe45,Ye2) ALIAS_CGA3D_ADD_MUL(Xe245,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye345) ALIAS_CGA3D_ADD_MUL(Xe3,Ye45) ALIAS_CGA3D_SUB_MUL(Xe4,Ye35) ALIAS_CGA3D_ADD_MUL(Xe5,Ye34) ALIAS_CGA3D_ADD_MUL(Xe34,Ye5) ALIAS_CGA3D_SUB_MUL(Xe35,Ye4) ALIAS_CGA3D_ADD_MUL(Xe45,Ye3) ALIAS_CGA3D_ADD_MUL(Xe345,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1,Ye234) ALIAS_CGA3D_SUB_MUL(Xe2,Ye134) ALIAS_CGA3D_ADD_MUL(Xe3,Ye124) ALIAS_CGA3D_SUB_MUL(Xe4,Ye123) ALIAS_CGA3D_ADD_MUL(Xe12,Ye34) ALIAS_CGA3D_SUB_MUL(Xe13,Ye24) ALIAS_CGA3D_ADD_MUL(Xe14,Ye23) ALIAS_CGA3D_ADD_MUL(Xe23,Ye14) ALIAS_CGA3D_SUB_MUL(Xe24,Ye13) ALIAS_CGA3D_ADD_MUL(Xe34,Ye12) ALIAS_CGA3D_ADD_MUL(Xe123,Ye4) ALIAS_CGA3D_SUB_MUL(Xe124,Ye3) ALIAS_CGA3D_ADD_MUL(Xe134,Ye2) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1234,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1,Ye235) ALIAS_CGA3D_SUB_MUL(Xe2,Ye135) ALIAS_CGA3D_ADD_MUL(Xe3,Ye125) ALIAS_CGA3D_SUB_MUL(Xe5,Ye123) ALIAS_CGA3D_ADD_MUL(Xe12,Ye35) ALIAS_CGA3D_SUB_MUL(Xe13,Ye25) ALIAS_CGA3D_ADD_MUL(Xe15,Ye23) ALIAS_CGA3D_ADD_MUL(Xe23,Ye15) ALIAS_CGA3D_SUB_MUL(Xe25,Ye13) ALIAS_CGA3D_ADD_MUL(Xe35,Ye12) ALIAS_CGA3D_ADD_MUL(Xe123,Ye5) ALIAS_CGA3D_SUB_MUL(Xe125,Ye3) ALIAS_CGA3D_ADD_MUL(Xe135,Ye2) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1235,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1,Ye245) ALIAS_CGA3D_SUB_MUL(Xe2,Ye145) ALIAS_CGA3D_ADD_MUL(Xe4,Ye125) ALIAS_CGA3D_SUB_MUL(Xe5,Ye124) ALIAS_CGA3D_ADD_MUL(Xe12,Ye45) ALIAS_CGA3D_SUB_MUL(Xe14,Ye25) ALIAS_CGA3D_ADD_MUL(Xe15,Ye24) ALIAS_CGA3D_ADD_MUL(Xe24,Ye15) ALIAS_CGA3D_SUB_MUL(Xe25,Ye14) ALIAS_CGA3D_ADD_MUL(Xe45,Ye12) ALIAS_CGA3D_ADD_MUL(Xe124,Ye5) ALIAS_CGA3D_SUB_MUL(Xe125,Ye4) ALIAS_CGA3D_ADD_MUL(Xe145,Ye2) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1245,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye145) ALIAS_CGA3D_ADD_MUL(Xe4,Ye135) ALIAS_CGA3D_SUB_MUL(Xe5,Ye134) ALIAS_CGA3D_ADD_MUL(Xe13,Ye45) ALIAS_CGA3D_SUB_MUL(Xe14,Ye35) ALIAS_CGA3D_ADD_MUL(Xe15,Ye34) ALIAS_CGA3D_ADD_MUL(Xe34,Ye15) ALIAS_CGA3D_SUB_MUL(Xe35,Ye14) ALIAS_CGA3D_ADD_MUL(Xe45,Ye13) ALIAS_CGA3D_ADD_MUL(Xe134,Ye5) ALIAS_CGA3D_SUB_MUL(Xe135,Ye4) ALIAS_CGA3D_ADD_MUL(Xe145,Ye3) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1345,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye245) ALIAS_CGA3D_ADD_MUL(Xe4,Ye235) ALIAS_CGA3D_SUB_MUL(Xe5,Ye234) ALIAS_CGA3D_ADD_MUL(Xe23,Ye45) ALIAS_CGA3D_SUB_MUL(Xe24,Ye35) ALIAS_CGA3D_ADD_MUL(Xe25,Ye34) ALIAS_CGA3D_ADD_MUL(Xe34,Ye25) ALIAS_CGA3D_SUB_MUL(Xe35,Ye24) ALIAS_CGA3D_ADD_MUL(Xe45,Ye23) ALIAS_CGA3D_ADD_MUL(Xe234,Ye5) ALIAS_CGA3D_SUB_MUL(Xe235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe245,Ye3) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2) ALIAS_CGA3D_ADD_MUL(Xe2345,Yone) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12,Ye345) ALIAS_CGA3D_SUB_MUL(Xe13,Ye245) ALIAS_CGA3D_ADD_MUL(Xe14,Ye235) ALIAS_CGA3D_SUB_MUL(Xe15,Ye234) ALIAS_CGA3D_ADD_MUL(Xe23,Ye145) ALIAS_CGA3D_SUB_MUL(Xe24,Ye135) ALIAS_CGA3D_ADD_MUL(Xe25,Ye134) ALIAS_CGA3D_ADD_MUL(Xe34,Ye125) ALIAS_CGA3D_SUB_MUL(Xe35,Ye124) ALIAS_CGA3D_ADD_MUL(Xe45,Ye123) ALIAS_CGA3D_ADD_MUL(Xe123,Ye45) ALIAS_CGA3D_SUB_MUL(Xe124,Ye35) ALIAS_CGA3D_ADD_MUL(Xe125,Ye34) ALIAS_CGA3D_ADD_MUL(Xe134,Ye25) ALIAS_CGA3D_SUB_MUL(Xe135,Ye24) ALIAS_CGA3D_ADD_MUL(Xe145,Ye23) ALIAS_CGA3D_SUB_MUL(Xe234,Ye15) ALIAS_CGA3D_ADD_MUL(Xe235,Ye14) ALIAS_CGA3D_SUB_MUL(Xe245,Ye13) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye5) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye2) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12345,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_REGRESSIVE_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12,Ye345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye245) ALIAS_CGA3D_ADD_MUL(Xe14,Ye235) ALIAS_CGA3D_ADD_MUL(Xe15,Ye234) ALIAS_CGA3D_ADD_MUL(Xe23,Ye145) ALIAS_CGA3D_ADD_MUL(Xe24,Ye135) ALIAS_CGA3D_ADD_MUL(Xe25,Ye134) ALIAS_CGA3D_ADD_MUL(Xe34,Ye125) ALIAS_CGA3D_ADD_MUL(Xe35,Ye124) ALIAS_CGA3D_ADD_MUL(Xe45,Ye123) ALIAS_CGA3D_ADD_MUL(Xe123,Ye45) ALIAS_CGA3D_ADD_MUL(Xe124,Ye35) ALIAS_CGA3D_ADD_MUL(Xe125,Ye34) ALIAS_CGA3D_ADD_MUL(Xe134,Ye25) ALIAS_CGA3D_ADD_MUL(Xe135,Ye24) ALIAS_CGA3D_ADD_MUL(Xe145,Ye23) ALIAS_CGA3D_ADD_MUL(Xe234,Ye15) ALIAS_CGA3D_ADD_MUL(Xe235,Ye14) ALIAS_CGA3D_ADD_MUL(Xe245,Ye13) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye3) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye2) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12345,Yone) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe1,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe15,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe123,Ye145) ALIAS_CGA3D_ADD_MUL(Xe124,Ye135) ALIAS_CGA3D_SUB_MUL(Xe125,Ye134) ALIAS_CGA3D_SUB_MUL(Xe134,Ye125) ALIAS_CGA3D_ADD_MUL(Xe135,Ye124) ALIAS_CGA3D_SUB_MUL(Xe145,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye15) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye13) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye12) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe23,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe25,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe123,Ye245) ALIAS_CGA3D_SUB_MUL(Xe124,Ye235) ALIAS_CGA3D_ADD_MUL(Xe125,Ye234) ALIAS_CGA3D_ADD_MUL(Xe234,Ye125) ALIAS_CGA3D_SUB_MUL(Xe235,Ye124) ALIAS_CGA3D_ADD_MUL(Xe245,Ye123) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye23) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye12) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye2) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe3,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe35,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe123,Ye345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye235) ALIAS_CGA3D_SUB_MUL(Xe135,Ye234) ALIAS_CGA3D_SUB_MUL(Xe234,Ye135) ALIAS_CGA3D_ADD_MUL(Xe235,Ye134) ALIAS_CGA3D_SUB_MUL(Xe345,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye35) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye23) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye13) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye3) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe4,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe14,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe124,Ye345) ALIAS_CGA3D_SUB_MUL(Xe134,Ye245) ALIAS_CGA3D_ADD_MUL(Xe145,Ye234) ALIAS_CGA3D_ADD_MUL(Xe234,Ye145) ALIAS_CGA3D_SUB_MUL(Xe245,Ye134) ALIAS_CGA3D_ADD_MUL(Xe345,Ye124) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye34) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye24) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye14) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye4) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe5,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe15,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe125,Ye345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye245) ALIAS_CGA3D_ADD_MUL(Xe145,Ye235) ALIAS_CGA3D_ADD_MUL(Xe235,Ye145) ALIAS_CGA3D_SUB_MUL(Xe245,Ye135) ALIAS_CGA3D_ADD_MUL(Xe345,Ye125) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye35) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye25) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye15) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe12,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe123,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe125,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye125) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye123) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye12) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe13,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye135) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye123) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye13) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe14,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye145) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye134) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye124) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye14) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe15,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe125,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye145) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye135) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye125) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye15) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe23,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe123,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe235,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye235) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye234) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye123) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye23) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe24,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe124,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye234) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye124) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye24) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe25,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe125,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe235,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye235) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye125) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye25) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe34,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye234) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye134) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye34) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe35,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe135,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye235) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye135) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye35) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe45,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe245,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye245) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye145) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye45) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe123,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye123) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe124,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye124) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe125,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye125) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe134,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye134) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe135,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye135) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe145,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye145) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe234,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye234) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe235,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe245,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye245) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe345,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye345) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe1234,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1234) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe1235,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1245,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1245) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe1345,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2345,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye2345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe12345,Ye12345) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_COMMUTATOR_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe2,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye13) ALIAS_CGA3D_SUB_MUL(Xe4,Ye14) ALIAS_CGA3D_ADD_MUL(Xe5,Ye15) ALIAS_CGA3D_ADD_MUL(Xe12,Ye2) ALIAS_CGA3D_ADD_MUL(Xe13,Ye3) ALIAS_CGA3D_ADD_MUL(Xe14,Ye4) ALIAS_CGA3D_SUB_MUL(Xe15,Ye5) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye24) ALIAS_CGA3D_ADD_MUL(Xe5,Ye25) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1) ALIAS_CGA3D_ADD_MUL(Xe23,Ye3) ALIAS_CGA3D_ADD_MUL(Xe24,Ye4) ALIAS_CGA3D_SUB_MUL(Xe25,Ye5) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye145) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye13) ALIAS_CGA3D_ADD_MUL(Xe2,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye35) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2) ALIAS_CGA3D_ADD_MUL(Xe34,Ye4) ALIAS_CGA3D_SUB_MUL(Xe35,Ye5) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye125) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye145) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2,Ye24) ALIAS_CGA3D_ADD_MUL(Xe3,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye45) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1) ALIAS_CGA3D_SUB_MUL(Xe24,Ye2) ALIAS_CGA3D_SUB_MUL(Xe34,Ye3) ALIAS_CGA3D_SUB_MUL(Xe45,Ye5) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2,Ye25) ALIAS_CGA3D_ADD_MUL(Xe3,Ye35) ALIAS_CGA3D_ADD_MUL(Xe4,Ye45) ALIAS_CGA3D_SUB_MUL(Xe15,Ye1) ALIAS_CGA3D_SUB_MUL(Xe25,Ye2) ALIAS_CGA3D_SUB_MUL(Xe35,Ye3) ALIAS_CGA3D_SUB_MUL(Xe45,Ye4) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye2) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1) ALIAS_CGA3D_SUB_MUL(Xe13,Ye23) ALIAS_CGA3D_SUB_MUL(Xe14,Ye24) ALIAS_CGA3D_ADD_MUL(Xe15,Ye25) ALIAS_CGA3D_ADD_MUL(Xe23,Ye13) ALIAS_CGA3D_ADD_MUL(Xe24,Ye14) ALIAS_CGA3D_SUB_MUL(Xe25,Ye15) ALIAS_CGA3D_SUB_MUL(Xe134,Ye234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye245) ALIAS_CGA3D_ADD_MUL(Xe234,Ye134) ALIAS_CGA3D_SUB_MUL(Xe235,Ye135) ALIAS_CGA3D_SUB_MUL(Xe245,Ye145) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye3) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12,Ye23) ALIAS_CGA3D_SUB_MUL(Xe14,Ye34) ALIAS_CGA3D_ADD_MUL(Xe15,Ye35) ALIAS_CGA3D_SUB_MUL(Xe23,Ye12) ALIAS_CGA3D_ADD_MUL(Xe34,Ye14) ALIAS_CGA3D_SUB_MUL(Xe35,Ye15) ALIAS_CGA3D_ADD_MUL(Xe124,Ye234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye124) ALIAS_CGA3D_ADD_MUL(Xe235,Ye125) ALIAS_CGA3D_SUB_MUL(Xe345,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye1245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12,Ye24) ALIAS_CGA3D_ADD_MUL(Xe13,Ye34) ALIAS_CGA3D_ADD_MUL(Xe15,Ye45) ALIAS_CGA3D_SUB_MUL(Xe24,Ye12) ALIAS_CGA3D_SUB_MUL(Xe34,Ye13) ALIAS_CGA3D_SUB_MUL(Xe45,Ye15) ALIAS_CGA3D_SUB_MUL(Xe123,Ye234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye245) ALIAS_CGA3D_SUB_MUL(Xe135,Ye345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye123) ALIAS_CGA3D_ADD_MUL(Xe245,Ye125) ALIAS_CGA3D_ADD_MUL(Xe345,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye1) ALIAS_CGA3D_ADD_MUL(Xe12,Ye25) ALIAS_CGA3D_ADD_MUL(Xe13,Ye35) ALIAS_CGA3D_ADD_MUL(Xe14,Ye45) ALIAS_CGA3D_SUB_MUL(Xe25,Ye12) ALIAS_CGA3D_SUB_MUL(Xe35,Ye13) ALIAS_CGA3D_SUB_MUL(Xe45,Ye14) ALIAS_CGA3D_SUB_MUL(Xe123,Ye235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye345) ALIAS_CGA3D_ADD_MUL(Xe235,Ye123) ALIAS_CGA3D_ADD_MUL(Xe245,Ye124) ALIAS_CGA3D_ADD_MUL(Xe345,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye1234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2,Ye3) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12,Ye13) ALIAS_CGA3D_ADD_MUL(Xe13,Ye12) ALIAS_CGA3D_SUB_MUL(Xe24,Ye34) ALIAS_CGA3D_ADD_MUL(Xe25,Ye35) ALIAS_CGA3D_ADD_MUL(Xe34,Ye24) ALIAS_CGA3D_SUB_MUL(Xe35,Ye25) ALIAS_CGA3D_SUB_MUL(Xe124,Ye134) ALIAS_CGA3D_ADD_MUL(Xe125,Ye135) ALIAS_CGA3D_ADD_MUL(Xe134,Ye124) ALIAS_CGA3D_SUB_MUL(Xe135,Ye125) ALIAS_CGA3D_ADD_MUL(Xe245,Ye345) ALIAS_CGA3D_SUB_MUL(Xe345,Ye245) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12,Ye14) ALIAS_CGA3D_ADD_MUL(Xe14,Ye12) ALIAS_CGA3D_ADD_MUL(Xe23,Ye34) ALIAS_CGA3D_ADD_MUL(Xe25,Ye45) ALIAS_CGA3D_SUB_MUL(Xe34,Ye23) ALIAS_CGA3D_SUB_MUL(Xe45,Ye25) ALIAS_CGA3D_ADD_MUL(Xe123,Ye134) ALIAS_CGA3D_ADD_MUL(Xe125,Ye145) ALIAS_CGA3D_SUB_MUL(Xe134,Ye123) ALIAS_CGA3D_SUB_MUL(Xe145,Ye125) ALIAS_CGA3D_SUB_MUL(Xe235,Ye345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12,Ye15) ALIAS_CGA3D_ADD_MUL(Xe15,Ye12) ALIAS_CGA3D_ADD_MUL(Xe23,Ye35) ALIAS_CGA3D_ADD_MUL(Xe24,Ye45) ALIAS_CGA3D_SUB_MUL(Xe35,Ye23) ALIAS_CGA3D_SUB_MUL(Xe45,Ye24) ALIAS_CGA3D_ADD_MUL(Xe123,Ye135) ALIAS_CGA3D_ADD_MUL(Xe124,Ye145) ALIAS_CGA3D_SUB_MUL(Xe135,Ye123) ALIAS_CGA3D_SUB_MUL(Xe145,Ye124) ALIAS_CGA3D_SUB_MUL(Xe234,Ye345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe3,Ye4) ALIAS_CGA3D_SUB_MUL(Xe4,Ye3) ALIAS_CGA3D_SUB_MUL(Xe13,Ye14) ALIAS_CGA3D_ADD_MUL(Xe14,Ye13) ALIAS_CGA3D_SUB_MUL(Xe23,Ye24) ALIAS_CGA3D_ADD_MUL(Xe24,Ye23) ALIAS_CGA3D_ADD_MUL(Xe35,Ye45) ALIAS_CGA3D_SUB_MUL(Xe45,Ye35) ALIAS_CGA3D_SUB_MUL(Xe123,Ye124) ALIAS_CGA3D_ADD_MUL(Xe124,Ye123) ALIAS_CGA3D_ADD_MUL(Xe135,Ye145) ALIAS_CGA3D_SUB_MUL(Xe145,Ye135) ALIAS_CGA3D_ADD_MUL(Xe235,Ye245) ALIAS_CGA3D_SUB_MUL(Xe245,Ye235) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe3,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye3) ALIAS_CGA3D_SUB_MUL(Xe13,Ye15) ALIAS_CGA3D_ADD_MUL(Xe15,Ye13) ALIAS_CGA3D_SUB_MUL(Xe23,Ye25) ALIAS_CGA3D_ADD_MUL(Xe25,Ye23) ALIAS_CGA3D_ADD_MUL(Xe34,Ye45) ALIAS_CGA3D_SUB_MUL(Xe45,Ye34) ALIAS_CGA3D_SUB_MUL(Xe123,Ye125) ALIAS_CGA3D_ADD_MUL(Xe125,Ye123) ALIAS_CGA3D_ADD_MUL(Xe134,Ye145) ALIAS_CGA3D_SUB_MUL(Xe145,Ye134) ALIAS_CGA3D_ADD_MUL(Xe234,Ye245) ALIAS_CGA3D_SUB_MUL(Xe245,Ye234) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe4,Ye5) ALIAS_CGA3D_SUB_MUL(Xe5,Ye4) ALIAS_CGA3D_SUB_MUL(Xe14,Ye15) ALIAS_CGA3D_ADD_MUL(Xe15,Ye14) ALIAS_CGA3D_SUB_MUL(Xe24,Ye25) ALIAS_CGA3D_ADD_MUL(Xe25,Ye24) ALIAS_CGA3D_SUB_MUL(Xe34,Ye35) ALIAS_CGA3D_ADD_MUL(Xe35,Ye34) ALIAS_CGA3D_SUB_MUL(Xe124,Ye125) ALIAS_CGA3D_ADD_MUL(Xe125,Ye124) ALIAS_CGA3D_SUB_MUL(Xe134,Ye135) ALIAS_CGA3D_ADD_MUL(Xe135,Ye134) ALIAS_CGA3D_SUB_MUL(Xe234,Ye235) ALIAS_CGA3D_ADD_MUL(Xe235,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1234) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe4,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye234) ALIAS_CGA3D_SUB_MUL(Xe15,Ye235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye134) ALIAS_CGA3D_ADD_MUL(Xe25,Ye135) ALIAS_CGA3D_ADD_MUL(Xe34,Ye124) ALIAS_CGA3D_SUB_MUL(Xe35,Ye125) ALIAS_CGA3D_SUB_MUL(Xe124,Ye34) ALIAS_CGA3D_ADD_MUL(Xe125,Ye35) ALIAS_CGA3D_ADD_MUL(Xe134,Ye24) ALIAS_CGA3D_SUB_MUL(Xe135,Ye25) ALIAS_CGA3D_SUB_MUL(Xe234,Ye14) ALIAS_CGA3D_ADD_MUL(Xe235,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye4) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe3,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe13,Ye234) ALIAS_CGA3D_SUB_MUL(Xe15,Ye245) ALIAS_CGA3D_ADD_MUL(Xe23,Ye134) ALIAS_CGA3D_ADD_MUL(Xe25,Ye145) ALIAS_CGA3D_SUB_MUL(Xe34,Ye123) ALIAS_CGA3D_SUB_MUL(Xe45,Ye125) ALIAS_CGA3D_ADD_MUL(Xe123,Ye34) ALIAS_CGA3D_ADD_MUL(Xe125,Ye45) ALIAS_CGA3D_SUB_MUL(Xe134,Ye23) ALIAS_CGA3D_SUB_MUL(Xe145,Ye25) ALIAS_CGA3D_ADD_MUL(Xe234,Ye13) ALIAS_CGA3D_ADD_MUL(Xe245,Ye15) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe3,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe13,Ye235) ALIAS_CGA3D_SUB_MUL(Xe14,Ye245) ALIAS_CGA3D_ADD_MUL(Xe23,Ye135) ALIAS_CGA3D_ADD_MUL(Xe24,Ye145) ALIAS_CGA3D_SUB_MUL(Xe35,Ye123) ALIAS_CGA3D_SUB_MUL(Xe45,Ye124) ALIAS_CGA3D_ADD_MUL(Xe123,Ye35) ALIAS_CGA3D_ADD_MUL(Xe124,Ye45) ALIAS_CGA3D_SUB_MUL(Xe135,Ye23) ALIAS_CGA3D_SUB_MUL(Xe145,Ye24) ALIAS_CGA3D_ADD_MUL(Xe235,Ye13) ALIAS_CGA3D_ADD_MUL(Xe245,Ye14) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye4) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe2,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye234) ALIAS_CGA3D_SUB_MUL(Xe15,Ye345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye124) ALIAS_CGA3D_ADD_MUL(Xe24,Ye123) ALIAS_CGA3D_ADD_MUL(Xe35,Ye145) ALIAS_CGA3D_SUB_MUL(Xe45,Ye135) ALIAS_CGA3D_SUB_MUL(Xe123,Ye24) ALIAS_CGA3D_ADD_MUL(Xe124,Ye23) ALIAS_CGA3D_ADD_MUL(Xe135,Ye45) ALIAS_CGA3D_SUB_MUL(Xe145,Ye35) ALIAS_CGA3D_SUB_MUL(Xe234,Ye12) ALIAS_CGA3D_ADD_MUL(Xe345,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye5) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe2,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye235) ALIAS_CGA3D_SUB_MUL(Xe14,Ye345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye125) ALIAS_CGA3D_ADD_MUL(Xe25,Ye123) ALIAS_CGA3D_ADD_MUL(Xe34,Ye145) ALIAS_CGA3D_SUB_MUL(Xe45,Ye134) ALIAS_CGA3D_SUB_MUL(Xe123,Ye25) ALIAS_CGA3D_ADD_MUL(Xe125,Ye23) ALIAS_CGA3D_ADD_MUL(Xe134,Ye45) ALIAS_CGA3D_SUB_MUL(Xe145,Ye34) ALIAS_CGA3D_SUB_MUL(Xe235,Ye12) ALIAS_CGA3D_ADD_MUL(Xe345,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye4) \
  , 0 ALIAS_CGA3D_SUB_MUL(Xe2,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe12,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye345) ALIAS_CGA3D_SUB_MUL(Xe24,Ye125) ALIAS_CGA3D_ADD_MUL(Xe25,Ye124) ALIAS_CGA3D_SUB_MUL(Xe34,Ye135) ALIAS_CGA3D_ADD_MUL(Xe35,Ye134) ALIAS_CGA3D_SUB_MUL(Xe124,Ye25) ALIAS_CGA3D_ADD_MUL(Xe125,Ye24) ALIAS_CGA3D_SUB_MUL(Xe134,Ye35) ALIAS_CGA3D_ADD_MUL(Xe135,Ye34) ALIAS_CGA3D_SUB_MUL(Xe245,Ye12) ALIAS_CGA3D_SUB_MUL(Xe345,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye3) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye134) ALIAS_CGA3D_ADD_MUL(Xe13,Ye124) ALIAS_CGA3D_SUB_MUL(Xe14,Ye123) ALIAS_CGA3D_SUB_MUL(Xe25,Ye345) ALIAS_CGA3D_ADD_MUL(Xe35,Ye245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye235) ALIAS_CGA3D_ADD_MUL(Xe123,Ye14) ALIAS_CGA3D_SUB_MUL(Xe124,Ye13) ALIAS_CGA3D_ADD_MUL(Xe134,Ye12) ALIAS_CGA3D_ADD_MUL(Xe235,Ye45) ALIAS_CGA3D_SUB_MUL(Xe245,Ye35) ALIAS_CGA3D_ADD_MUL(Xe345,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye135) ALIAS_CGA3D_ADD_MUL(Xe13,Ye125) ALIAS_CGA3D_SUB_MUL(Xe15,Ye123) ALIAS_CGA3D_SUB_MUL(Xe24,Ye345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye234) ALIAS_CGA3D_ADD_MUL(Xe123,Ye15) ALIAS_CGA3D_SUB_MUL(Xe125,Ye13) ALIAS_CGA3D_ADD_MUL(Xe135,Ye12) ALIAS_CGA3D_ADD_MUL(Xe234,Ye45) ALIAS_CGA3D_SUB_MUL(Xe245,Ye34) ALIAS_CGA3D_ADD_MUL(Xe345,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye4) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye145) ALIAS_CGA3D_ADD_MUL(Xe14,Ye125) ALIAS_CGA3D_SUB_MUL(Xe15,Ye124) ALIAS_CGA3D_ADD_MUL(Xe23,Ye345) ALIAS_CGA3D_SUB_MUL(Xe34,Ye235) ALIAS_CGA3D_ADD_MUL(Xe35,Ye234) ALIAS_CGA3D_ADD_MUL(Xe124,Ye15) ALIAS_CGA3D_SUB_MUL(Xe125,Ye14) ALIAS_CGA3D_ADD_MUL(Xe145,Ye12) ALIAS_CGA3D_SUB_MUL(Xe234,Ye35) ALIAS_CGA3D_ADD_MUL(Xe235,Ye34) ALIAS_CGA3D_SUB_MUL(Xe345,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye3) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe13,Ye145) ALIAS_CGA3D_ADD_MUL(Xe14,Ye135) ALIAS_CGA3D_SUB_MUL(Xe15,Ye134) ALIAS_CGA3D_SUB_MUL(Xe23,Ye245) ALIAS_CGA3D_ADD_MUL(Xe24,Ye235) ALIAS_CGA3D_SUB_MUL(Xe25,Ye234) ALIAS_CGA3D_ADD_MUL(Xe134,Ye15) ALIAS_CGA3D_SUB_MUL(Xe135,Ye14) ALIAS_CGA3D_ADD_MUL(Xe145,Ye13) ALIAS_CGA3D_ADD_MUL(Xe234,Ye25) ALIAS_CGA3D_SUB_MUL(Xe235,Ye24) ALIAS_CGA3D_ADD_MUL(Xe245,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye2) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye234) ALIAS_CGA3D_SUB_MUL(Xe2,Ye134) ALIAS_CGA3D_ADD_MUL(Xe3,Ye124) ALIAS_CGA3D_SUB_MUL(Xe4,Ye123) ALIAS_CGA3D_ADD_MUL(Xe15,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe123,Ye4) ALIAS_CGA3D_SUB_MUL(Xe124,Ye3) ALIAS_CGA3D_ADD_MUL(Xe134,Ye2) ALIAS_CGA3D_SUB_MUL(Xe234,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye25) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye15) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye235) ALIAS_CGA3D_SUB_MUL(Xe2,Ye135) ALIAS_CGA3D_ADD_MUL(Xe3,Ye125) ALIAS_CGA3D_SUB_MUL(Xe5,Ye123) ALIAS_CGA3D_ADD_MUL(Xe14,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe34,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe45,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe123,Ye5) ALIAS_CGA3D_SUB_MUL(Xe125,Ye3) ALIAS_CGA3D_ADD_MUL(Xe135,Ye2) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye24) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye14) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye245) ALIAS_CGA3D_SUB_MUL(Xe2,Ye145) ALIAS_CGA3D_ADD_MUL(Xe4,Ye125) ALIAS_CGA3D_SUB_MUL(Xe5,Ye124) ALIAS_CGA3D_SUB_MUL(Xe13,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe23,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe124,Ye5) ALIAS_CGA3D_SUB_MUL(Xe125,Ye4) ALIAS_CGA3D_ADD_MUL(Xe145,Ye2) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye34) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye23) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye13) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe1,Ye345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye145) ALIAS_CGA3D_ADD_MUL(Xe4,Ye135) ALIAS_CGA3D_SUB_MUL(Xe5,Ye134) ALIAS_CGA3D_ADD_MUL(Xe12,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe134,Ye5) ALIAS_CGA3D_SUB_MUL(Xe135,Ye4) ALIAS_CGA3D_ADD_MUL(Xe145,Ye3) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye24) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye23) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye12) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xe2,Ye345) ALIAS_CGA3D_SUB_MUL(Xe3,Ye245) ALIAS_CGA3D_ADD_MUL(Xe4,Ye235) ALIAS_CGA3D_SUB_MUL(Xe5,Ye234) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe234,Ye5) ALIAS_CGA3D_SUB_MUL(Xe235,Ye4) ALIAS_CGA3D_ADD_MUL(Xe245,Ye3) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye15) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye14) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye12) \
  , 0 \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_INNER_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 ALIAS_CGA3D_ADD_MUL(Xone,Yone) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2) ALIAS_CGA3D_ADD_MUL(Xe3,Ye3) ALIAS_CGA3D_ADD_MUL(Xe4,Ye4) ALIAS_CGA3D_SUB_MUL(Xe5,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12) ALIAS_CGA3D_SUB_MUL(Xe13,Ye13) ALIAS_CGA3D_SUB_MUL(Xe14,Ye14) ALIAS_CGA3D_ADD_MUL(Xe15,Ye15) ALIAS_CGA3D_SUB_MUL(Xe23,Ye23) ALIAS_CGA3D_SUB_MUL(Xe24,Ye24) ALIAS_CGA3D_ADD_MUL(Xe25,Ye25) ALIAS_CGA3D_SUB_MUL(Xe34,Ye34) ALIAS_CGA3D_ADD_MUL(Xe35,Ye35) ALIAS_CGA3D_ADD_MUL(Xe45,Ye45) ALIAS_CGA3D_SUB_MUL(Xe123,Ye123) ALIAS_CGA3D_SUB_MUL(Xe124,Ye124) ALIAS_CGA3D_ADD_MUL(Xe125,Ye125) ALIAS_CGA3D_SUB_MUL(Xe134,Ye134) ALIAS_CGA3D_ADD_MUL(Xe135,Ye135) ALIAS_CGA3D_ADD_MUL(Xe145,Ye145) ALIAS_CGA3D_SUB_MUL(Xe234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe345,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1) ALIAS_CGA3D_ADD_MUL(Xe1,Yone) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye13) ALIAS_CGA3D_SUB_MUL(Xe4,Ye14) ALIAS_CGA3D_ADD_MUL(Xe5,Ye15) ALIAS_CGA3D_ADD_MUL(Xe12,Ye2) ALIAS_CGA3D_ADD_MUL(Xe13,Ye3) ALIAS_CGA3D_ADD_MUL(Xe14,Ye4) ALIAS_CGA3D_SUB_MUL(Xe15,Ye5) ALIAS_CGA3D_SUB_MUL(Xe23,Ye123) ALIAS_CGA3D_SUB_MUL(Xe24,Ye124) ALIAS_CGA3D_ADD_MUL(Xe25,Ye125) ALIAS_CGA3D_SUB_MUL(Xe34,Ye134) ALIAS_CGA3D_ADD_MUL(Xe35,Ye135) ALIAS_CGA3D_ADD_MUL(Xe45,Ye145) ALIAS_CGA3D_SUB_MUL(Xe123,Ye23) ALIAS_CGA3D_SUB_MUL(Xe124,Ye24) ALIAS_CGA3D_ADD_MUL(Xe125,Ye25) ALIAS_CGA3D_SUB_MUL(Xe134,Ye34) ALIAS_CGA3D_ADD_MUL(Xe135,Ye35) ALIAS_CGA3D_ADD_MUL(Xe145,Ye45) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye2345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12) ALIAS_CGA3D_ADD_MUL(Xe2,Yone) ALIAS_CGA3D_SUB_MUL(Xe3,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye24) ALIAS_CGA3D_ADD_MUL(Xe5,Ye25) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1) ALIAS_CGA3D_ADD_MUL(Xe13,Ye123) ALIAS_CGA3D_ADD_MUL(Xe14,Ye124) ALIAS_CGA3D_SUB_MUL(Xe15,Ye125) ALIAS_CGA3D_ADD_MUL(Xe23,Ye3) ALIAS_CGA3D_ADD_MUL(Xe24,Ye4) ALIAS_CGA3D_SUB_MUL(Xe25,Ye5) ALIAS_CGA3D_SUB_MUL(Xe34,Ye234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye245) ALIAS_CGA3D_ADD_MUL(Xe123,Ye13) ALIAS_CGA3D_ADD_MUL(Xe124,Ye14) ALIAS_CGA3D_SUB_MUL(Xe125,Ye15) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe234,Ye34) ALIAS_CGA3D_ADD_MUL(Xe235,Ye35) ALIAS_CGA3D_ADD_MUL(Xe245,Ye45) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye134) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye135) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye145) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye3) ALIAS_CGA3D_ADD_MUL(Xe1,Ye13) ALIAS_CGA3D_ADD_MUL(Xe2,Ye23) ALIAS_CGA3D_ADD_MUL(Xe3,Yone) ALIAS_CGA3D_SUB_MUL(Xe4,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye35) ALIAS_CGA3D_SUB_MUL(Xe12,Ye123) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1) ALIAS_CGA3D_ADD_MUL(Xe14,Ye134) ALIAS_CGA3D_SUB_MUL(Xe15,Ye135) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2) ALIAS_CGA3D_ADD_MUL(Xe24,Ye234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye235) ALIAS_CGA3D_ADD_MUL(Xe34,Ye4) ALIAS_CGA3D_SUB_MUL(Xe35,Ye5) ALIAS_CGA3D_ADD_MUL(Xe45,Ye345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye12) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe134,Ye14) ALIAS_CGA3D_SUB_MUL(Xe135,Ye15) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye24) ALIAS_CGA3D_SUB_MUL(Xe235,Ye25) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe345,Ye45) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye125) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye145) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye245) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye1245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2,Ye24) ALIAS_CGA3D_ADD_MUL(Xe3,Ye34) ALIAS_CGA3D_ADD_MUL(Xe4,Yone) ALIAS_CGA3D_ADD_MUL(Xe5,Ye45) ALIAS_CGA3D_SUB_MUL(Xe12,Ye124) ALIAS_CGA3D_SUB_MUL(Xe13,Ye134) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1) ALIAS_CGA3D_SUB_MUL(Xe15,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye234) ALIAS_CGA3D_SUB_MUL(Xe24,Ye2) ALIAS_CGA3D_SUB_MUL(Xe25,Ye245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye3) ALIAS_CGA3D_SUB_MUL(Xe35,Ye345) ALIAS_CGA3D_SUB_MUL(Xe45,Ye5) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe124,Ye12) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye13) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe145,Ye15) ALIAS_CGA3D_SUB_MUL(Xe234,Ye23) ALIAS_CGA3D_SUB_MUL(Xe235,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe245,Ye25) ALIAS_CGA3D_SUB_MUL(Xe345,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye125) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye235) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2,Ye25) ALIAS_CGA3D_ADD_MUL(Xe3,Ye35) ALIAS_CGA3D_ADD_MUL(Xe4,Ye45) ALIAS_CGA3D_ADD_MUL(Xe5,Yone) ALIAS_CGA3D_SUB_MUL(Xe12,Ye125) ALIAS_CGA3D_SUB_MUL(Xe13,Ye135) ALIAS_CGA3D_SUB_MUL(Xe14,Ye145) ALIAS_CGA3D_SUB_MUL(Xe15,Ye1) ALIAS_CGA3D_SUB_MUL(Xe23,Ye235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye245) ALIAS_CGA3D_SUB_MUL(Xe25,Ye2) ALIAS_CGA3D_SUB_MUL(Xe34,Ye345) ALIAS_CGA3D_SUB_MUL(Xe35,Ye3) ALIAS_CGA3D_SUB_MUL(Xe45,Ye4) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe125,Ye12) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye13) ALIAS_CGA3D_SUB_MUL(Xe145,Ye14) ALIAS_CGA3D_SUB_MUL(Xe234,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye23) ALIAS_CGA3D_SUB_MUL(Xe245,Ye24) ALIAS_CGA3D_SUB_MUL(Xe345,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye123) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye124) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye234) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12) ALIAS_CGA3D_ADD_MUL(Xe3,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye124) ALIAS_CGA3D_SUB_MUL(Xe5,Ye125) ALIAS_CGA3D_ADD_MUL(Xe12,Yone) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe123,Ye3) ALIAS_CGA3D_ADD_MUL(Xe124,Ye4) ALIAS_CGA3D_SUB_MUL(Xe125,Ye5) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye45) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye13) ALIAS_CGA3D_SUB_MUL(Xe2,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye134) ALIAS_CGA3D_SUB_MUL(Xe5,Ye135) ALIAS_CGA3D_ADD_MUL(Xe13,Yone) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye2) ALIAS_CGA3D_ADD_MUL(Xe134,Ye4) ALIAS_CGA3D_SUB_MUL(Xe135,Ye5) ALIAS_CGA3D_SUB_MUL(Xe245,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye45) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye245) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye14) ALIAS_CGA3D_SUB_MUL(Xe2,Ye124) ALIAS_CGA3D_SUB_MUL(Xe3,Ye134) ALIAS_CGA3D_SUB_MUL(Xe5,Ye145) ALIAS_CGA3D_ADD_MUL(Xe14,Yone) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe124,Ye2) ALIAS_CGA3D_SUB_MUL(Xe134,Ye3) ALIAS_CGA3D_SUB_MUL(Xe145,Ye5) ALIAS_CGA3D_ADD_MUL(Xe235,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye25) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye35) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye235) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye15) ALIAS_CGA3D_SUB_MUL(Xe2,Ye125) ALIAS_CGA3D_SUB_MUL(Xe3,Ye135) ALIAS_CGA3D_SUB_MUL(Xe4,Ye145) ALIAS_CGA3D_ADD_MUL(Xe15,Yone) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe125,Ye2) ALIAS_CGA3D_SUB_MUL(Xe135,Ye3) ALIAS_CGA3D_SUB_MUL(Xe145,Ye4) ALIAS_CGA3D_ADD_MUL(Xe234,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye23) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye24) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye34) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye234) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye23) ALIAS_CGA3D_ADD_MUL(Xe1,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye235) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe23,Yone) ALIAS_CGA3D_ADD_MUL(Xe45,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe123,Ye1) ALIAS_CGA3D_ADD_MUL(Xe145,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye4) ALIAS_CGA3D_SUB_MUL(Xe235,Ye5) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye14) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye45) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye145) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye24) ALIAS_CGA3D_ADD_MUL(Xe1,Ye124) ALIAS_CGA3D_SUB_MUL(Xe3,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe24,Yone) ALIAS_CGA3D_SUB_MUL(Xe35,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1) ALIAS_CGA3D_SUB_MUL(Xe135,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye3) ALIAS_CGA3D_SUB_MUL(Xe245,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye15) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye35) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye135) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1,Ye125) ALIAS_CGA3D_SUB_MUL(Xe3,Ye235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe25,Yone) ALIAS_CGA3D_SUB_MUL(Xe34,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe125,Ye1) ALIAS_CGA3D_SUB_MUL(Xe134,Ye12345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye3) ALIAS_CGA3D_SUB_MUL(Xe245,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye13) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye14) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye34) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye134) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe34,Yone) ALIAS_CGA3D_ADD_MUL(Xe125,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe134,Ye1) ALIAS_CGA3D_ADD_MUL(Xe234,Ye2) ALIAS_CGA3D_SUB_MUL(Xe345,Ye5) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye25) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye125) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2,Ye235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe35,Yone) ALIAS_CGA3D_ADD_MUL(Xe124,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1) ALIAS_CGA3D_ADD_MUL(Xe235,Ye2) ALIAS_CGA3D_SUB_MUL(Xe345,Ye4) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye12) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye24) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye124) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1,Ye145) ALIAS_CGA3D_ADD_MUL(Xe2,Ye245) ALIAS_CGA3D_ADD_MUL(Xe3,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe45,Yone) ALIAS_CGA3D_SUB_MUL(Xe123,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2) ALIAS_CGA3D_ADD_MUL(Xe345,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye12) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye13) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye23) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye123) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye123) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe123,Yone) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye4) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye5) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye45) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye124) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe124,Yone) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye35) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye125) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe125,Yone) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye3) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye4) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye34) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye134) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe134,Yone) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye5) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye25) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye135) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe135,Yone) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye2) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye4) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye24) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye145) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe145,Yone) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye3) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye23) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe15,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe234,Yone) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye15) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe14,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe235,Yone) ALIAS_CGA3D_SUB_MUL(Xe1235,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye4) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye14) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe245,Yone) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye1) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye3) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye13) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe345,Yone) ALIAS_CGA3D_SUB_MUL(Xe1345,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye2) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye12) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1234,Yone) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye5) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1235,Yone) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye4) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe3,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1245,Yone) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye3) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe1345,Yone) ALIAS_CGA3D_SUB_MUL(Xe12345,Ye2) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe2345,Yone) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye1) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12345) ALIAS_CGA3D_ADD_MUL(Xe12345,Yone) \
  , ## __VA_ARGS__)
#define ALIAS_CGA3D_OP_LEFT_DOT_PRODUCT(RETURN, Xone,Xe1,Xe2,Xe3,Xe4,Xe5,Xe12,Xe13,Xe14,Xe15,Xe23,Xe24,Xe25,Xe34,Xe35,Xe45,Xe123,Xe124,Xe125,Xe134,Xe135,Xe145,Xe234,Xe235,Xe245,Xe345,Xe1234,Xe1235,Xe1245,Xe1345,Xe2345,Xe12345, Yone,Ye1,Ye2,Ye3,Ye4,Ye5,Ye12,Ye13,Ye14,Ye15,Ye23,Ye24,Ye25,Ye34,Ye35,Ye45,Ye123,Ye124,Ye125,Ye134,Ye135,Ye145,Ye234,Ye235,Ye245,Ye345,Ye1234,Ye1235,Ye1245,Ye1345,Ye2345,Ye12345, ...) RETURN( \
    0 ALIAS_CGA3D_ADD_MUL(Xone,Yone) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2) ALIAS_CGA3D_ADD_MUL(Xe3,Ye3) ALIAS_CGA3D_ADD_MUL(Xe4,Ye4) ALIAS_CGA3D_SUB_MUL(Xe5,Ye5) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12) ALIAS_CGA3D_SUB_MUL(Xe13,Ye13) ALIAS_CGA3D_SUB_MUL(Xe14,Ye14) ALIAS_CGA3D_ADD_MUL(Xe15,Ye15) ALIAS_CGA3D_SUB_MUL(Xe23,Ye23) ALIAS_CGA3D_SUB_MUL(Xe24,Ye24) ALIAS_CGA3D_ADD_MUL(Xe25,Ye25) ALIAS_CGA3D_SUB_MUL(Xe34,Ye34) ALIAS_CGA3D_ADD_MUL(Xe35,Ye35) ALIAS_CGA3D_ADD_MUL(Xe45,Ye45) ALIAS_CGA3D_SUB_MUL(Xe123,Ye123) ALIAS_CGA3D_SUB_MUL(Xe124,Ye124) ALIAS_CGA3D_ADD_MUL(Xe125,Ye125) ALIAS_CGA3D_SUB_MUL(Xe134,Ye134) ALIAS_CGA3D_ADD_MUL(Xe135,Ye135) ALIAS_CGA3D_ADD_MUL(Xe145,Ye145) ALIAS_CGA3D_SUB_MUL(Xe234,Ye234) ALIAS_CGA3D_ADD_MUL(Xe235,Ye235) ALIAS_CGA3D_ADD_MUL(Xe245,Ye245) ALIAS_CGA3D_ADD_MUL(Xe345,Ye345) ALIAS_CGA3D_SUB_MUL(Xe1234,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe1245,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe12345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye13) ALIAS_CGA3D_SUB_MUL(Xe4,Ye14) ALIAS_CGA3D_ADD_MUL(Xe5,Ye15) ALIAS_CGA3D_SUB_MUL(Xe23,Ye123) ALIAS_CGA3D_SUB_MUL(Xe24,Ye124) ALIAS_CGA3D_ADD_MUL(Xe25,Ye125) ALIAS_CGA3D_SUB_MUL(Xe34,Ye134) ALIAS_CGA3D_ADD_MUL(Xe35,Ye135) ALIAS_CGA3D_ADD_MUL(Xe45,Ye145) ALIAS_CGA3D_ADD_MUL(Xe234,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe235,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe245,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe2345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12) ALIAS_CGA3D_SUB_MUL(Xe3,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye24) ALIAS_CGA3D_ADD_MUL(Xe5,Ye25) ALIAS_CGA3D_ADD_MUL(Xe13,Ye123) ALIAS_CGA3D_ADD_MUL(Xe14,Ye124) ALIAS_CGA3D_SUB_MUL(Xe15,Ye125) ALIAS_CGA3D_SUB_MUL(Xe34,Ye234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe135,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe345,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye3) ALIAS_CGA3D_ADD_MUL(Xe1,Ye13) ALIAS_CGA3D_ADD_MUL(Xe2,Ye23) ALIAS_CGA3D_SUB_MUL(Xe4,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye35) ALIAS_CGA3D_SUB_MUL(Xe12,Ye123) ALIAS_CGA3D_ADD_MUL(Xe14,Ye134) ALIAS_CGA3D_SUB_MUL(Xe15,Ye135) ALIAS_CGA3D_ADD_MUL(Xe24,Ye234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe145,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe245,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe1245,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye4) ALIAS_CGA3D_ADD_MUL(Xe1,Ye14) ALIAS_CGA3D_ADD_MUL(Xe2,Ye24) ALIAS_CGA3D_ADD_MUL(Xe3,Ye34) ALIAS_CGA3D_ADD_MUL(Xe5,Ye45) ALIAS_CGA3D_SUB_MUL(Xe12,Ye124) ALIAS_CGA3D_SUB_MUL(Xe13,Ye134) ALIAS_CGA3D_SUB_MUL(Xe15,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe125,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe135,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe235,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1235,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye5) ALIAS_CGA3D_ADD_MUL(Xe1,Ye15) ALIAS_CGA3D_ADD_MUL(Xe2,Ye25) ALIAS_CGA3D_ADD_MUL(Xe3,Ye35) ALIAS_CGA3D_ADD_MUL(Xe4,Ye45) ALIAS_CGA3D_SUB_MUL(Xe12,Ye125) ALIAS_CGA3D_SUB_MUL(Xe13,Ye135) ALIAS_CGA3D_SUB_MUL(Xe14,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe124,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe134,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe234,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1234,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12) ALIAS_CGA3D_ADD_MUL(Xe3,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye124) ALIAS_CGA3D_SUB_MUL(Xe5,Ye125) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe35,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe345,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye13) ALIAS_CGA3D_SUB_MUL(Xe2,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye134) ALIAS_CGA3D_SUB_MUL(Xe5,Ye135) ALIAS_CGA3D_ADD_MUL(Xe24,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe245,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye14) ALIAS_CGA3D_SUB_MUL(Xe2,Ye124) ALIAS_CGA3D_SUB_MUL(Xe3,Ye134) ALIAS_CGA3D_SUB_MUL(Xe5,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe25,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe235,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye15) ALIAS_CGA3D_SUB_MUL(Xe2,Ye125) ALIAS_CGA3D_SUB_MUL(Xe3,Ye135) ALIAS_CGA3D_SUB_MUL(Xe4,Ye145) ALIAS_CGA3D_SUB_MUL(Xe23,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe24,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe234,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye23) ALIAS_CGA3D_ADD_MUL(Xe1,Ye123) ALIAS_CGA3D_ADD_MUL(Xe4,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye235) ALIAS_CGA3D_SUB_MUL(Xe14,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe145,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye24) ALIAS_CGA3D_ADD_MUL(Xe1,Ye124) ALIAS_CGA3D_SUB_MUL(Xe3,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe135,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye25) ALIAS_CGA3D_ADD_MUL(Xe1,Ye125) ALIAS_CGA3D_SUB_MUL(Xe3,Ye235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye245) ALIAS_CGA3D_ADD_MUL(Xe13,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe134,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye34) ALIAS_CGA3D_ADD_MUL(Xe1,Ye134) ALIAS_CGA3D_ADD_MUL(Xe2,Ye234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe15,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe125,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye35) ALIAS_CGA3D_ADD_MUL(Xe1,Ye135) ALIAS_CGA3D_ADD_MUL(Xe2,Ye235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe14,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe124,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye45) ALIAS_CGA3D_ADD_MUL(Xe1,Ye145) ALIAS_CGA3D_ADD_MUL(Xe2,Ye245) ALIAS_CGA3D_ADD_MUL(Xe3,Ye345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe13,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe123,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye123) ALIAS_CGA3D_SUB_MUL(Xe4,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe45,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye124) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe35,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye125) ALIAS_CGA3D_ADD_MUL(Xe3,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe34,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye134) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe25,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye135) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe24,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye145) ALIAS_CGA3D_SUB_MUL(Xe2,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe23,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye234) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1234) ALIAS_CGA3D_ADD_MUL(Xe5,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe15,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye235) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1235) ALIAS_CGA3D_ADD_MUL(Xe4,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe14,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye245) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1245) ALIAS_CGA3D_SUB_MUL(Xe3,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe13,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye1345) ALIAS_CGA3D_ADD_MUL(Xe2,Ye2345) ALIAS_CGA3D_SUB_MUL(Xe12,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1234) ALIAS_CGA3D_SUB_MUL(Xe5,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1235) ALIAS_CGA3D_SUB_MUL(Xe4,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1245) ALIAS_CGA3D_ADD_MUL(Xe3,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye1345) ALIAS_CGA3D_SUB_MUL(Xe2,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye2345) ALIAS_CGA3D_ADD_MUL(Xe1,Ye12345) \
  , 0 ALIAS_CGA3D_ADD_MUL(Xone,Ye12345) \
  , ## __VA_ARGS__)
#define alias_cga3d_s(X) (1,0,0,0,0,0,_Generic((X), alias_cga3d_Scalar: X, default: ((alias_cga3d_Scalar){ .one = (float)X })))
#define alias_cga3d_v(X) (0,1,0,0,0,0,X)
#define alias_cga3d_b(X) (0,0,1,0,0,0,X)
#define alias_cga3d_t(X) (0,0,0,1,0,0,X)
#define alias_cga3d_V(X) (0,0,0,0,1,0,X)
#define alias_cga3d_S(X) (0,0,0,0,0,1,X)
#define alias_cga3d_grade_0(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_0, X)
#define alias_cga3d_grade_1(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_1, X)
#define alias_cga3d_grade_2(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_2, X)
#define alias_cga3d_grade_3(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_3, X)
#define alias_cga3d_grade_4(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_4, X)
#define alias_cga3d_grade_5(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_GRADE_5, X)
#define alias_cga3d_negate(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_NEGATE, X)
#define alias_cga3d_negate_s(X) alias_cga3d_negate(alias_cga3d_s(X))
#define alias_cga3d_negate_v(X) alias_cga3d_negate(alias_cga3d_v(X))
#define alias_cga3d_negate_b(X) alias_cga3d_negate(alias_cga3d_b(X))
#define alias_cga3d_negate_t(X) alias_cga3d_negate(alias_cga3d_t(X))
#define alias_cga3d_negate_V(X) alias_cga3d_negate(alias_cga3d_V(X))
#define alias_cga3d_negate_S(X) alias_cga3d_negate(alias_cga3d_S(X))
#define alias_cga3d_dual(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_DUAL, X)
#define alias_cga3d_dual_s(X) alias_cga3d_dual(alias_cga3d_s(X))
#define alias_cga3d_dual_v(X) alias_cga3d_dual(alias_cga3d_v(X))
#define alias_cga3d_dual_b(X) alias_cga3d_dual(alias_cga3d_b(X))
#define alias_cga3d_dual_t(X) alias_cga3d_dual(alias_cga3d_t(X))
#define alias_cga3d_dual_V(X) alias_cga3d_dual(alias_cga3d_V(X))
#define alias_cga3d_dual_S(X) alias_cga3d_dual(alias_cga3d_S(X))
#define alias_cga3d_reverse(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_REVERSE, X)
#define alias_cga3d_reverse_s(X) alias_cga3d_reverse(alias_cga3d_s(X))
#define alias_cga3d_reverse_v(X) alias_cga3d_reverse(alias_cga3d_v(X))
#define alias_cga3d_reverse_b(X) alias_cga3d_reverse(alias_cga3d_b(X))
#define alias_cga3d_reverse_t(X) alias_cga3d_reverse(alias_cga3d_t(X))
#define alias_cga3d_reverse_V(X) alias_cga3d_reverse(alias_cga3d_V(X))
#define alias_cga3d_reverse_S(X) alias_cga3d_reverse(alias_cga3d_S(X))
#define alias_cga3d_involute(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_INVOLUTE, X)
#define alias_cga3d_involute_s(X) alias_cga3d_involute(alias_cga3d_s(X))
#define alias_cga3d_involute_v(X) alias_cga3d_involute(alias_cga3d_v(X))
#define alias_cga3d_involute_b(X) alias_cga3d_involute(alias_cga3d_b(X))
#define alias_cga3d_involute_t(X) alias_cga3d_involute(alias_cga3d_t(X))
#define alias_cga3d_involute_V(X) alias_cga3d_involute(alias_cga3d_V(X))
#define alias_cga3d_involute_S(X) alias_cga3d_involute(alias_cga3d_S(X))
#define alias_cga3d_conjugate(X) ALIAS_CGA3D_UNARY(ALIAS_CGA3D_OP_CONJUGATE, X)
#define alias_cga3d_conjugate_s(X) alias_cga3d_conjugate(alias_cga3d_s(X))
#define alias_cga3d_conjugate_v(X) alias_cga3d_conjugate(alias_cga3d_v(X))
#define alias_cga3d_conjugate_b(X) alias_cga3d_conjugate(alias_cga3d_b(X))
#define alias_cga3d_conjugate_t(X) alias_cga3d_conjugate(alias_cga3d_t(X))
#define alias_cga3d_conjugate_V(X) alias_cga3d_conjugate(alias_cga3d_V(X))
#define alias_cga3d_conjugate_S(X) alias_cga3d_conjugate(alias_cga3d_S(X))
#define alias_cga3d_add(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_ADD, X, Y)
#define alias_cga3d_add_ss(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_add_sv(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_add_sb(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_add_st(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_add_sV(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_add_sS(X, Y) alias_cga3d_add(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_add_vs(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_add_vv(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_add_vb(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_add_vt(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_add_vV(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_add_vS(X, Y) alias_cga3d_add(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_add_bs(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_add_bv(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_add_bb(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_add_bt(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_add_bV(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_add_bS(X, Y) alias_cga3d_add(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_add_ts(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_add_tv(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_add_tb(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_add_tt(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_add_tV(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_add_tS(X, Y) alias_cga3d_add(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_add_Vs(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_add_Vv(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_add_Vb(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_add_Vt(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_add_VV(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_add_VS(X, Y) alias_cga3d_add(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_add_Ss(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_add_Sv(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_add_Sb(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_add_St(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_add_SV(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_add_SS(X, Y) alias_cga3d_add(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_SUBTRACT, X, Y)
#define alias_cga3d_subtract_ss(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_sv(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_sb(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_st(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_sV(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_sS(X, Y) alias_cga3d_subtract(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract_vs(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_vv(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_vb(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_vt(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_vV(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_vS(X, Y) alias_cga3d_subtract(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract_bs(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_bv(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_bb(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_bt(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_bV(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_bS(X, Y) alias_cga3d_subtract(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract_ts(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_tv(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_tb(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_tt(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_tV(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_tS(X, Y) alias_cga3d_subtract(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract_Vs(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_Vv(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_Vb(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_Vt(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_VV(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_VS(X, Y) alias_cga3d_subtract(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_subtract_Ss(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_subtract_Sv(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_subtract_Sb(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_subtract_St(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_subtract_SV(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_subtract_SS(X, Y) alias_cga3d_subtract(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_GEOMETRIC_PRODUCT, X, Y)
#define alias_cga3d_geometric_product_ss(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_sv(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_sb(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_st(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_sV(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_sS(X, Y) alias_cga3d_geometric_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product_vs(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_vv(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_vb(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_vt(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_vV(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_vS(X, Y) alias_cga3d_geometric_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product_bs(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_bv(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_bb(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_bt(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_bV(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_bS(X, Y) alias_cga3d_geometric_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product_ts(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_tv(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_tb(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_tt(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_tV(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_tS(X, Y) alias_cga3d_geometric_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product_Vs(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_Vv(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_Vb(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_Vt(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_VV(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_VS(X, Y) alias_cga3d_geometric_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_geometric_product_Ss(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_geometric_product_Sv(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_geometric_product_Sb(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_geometric_product_St(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_geometric_product_SV(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_geometric_product_SS(X, Y) alias_cga3d_geometric_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_OUTER_PRODUCT, X, Y)
#define alias_cga3d_outer_product_ss(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_sv(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_sb(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_st(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_sV(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_sS(X, Y) alias_cga3d_outer_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product_vs(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_vv(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_vb(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_vt(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_vV(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_vS(X, Y) alias_cga3d_outer_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product_bs(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_bv(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_bb(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_bt(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_bV(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_bS(X, Y) alias_cga3d_outer_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product_ts(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_tv(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_tb(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_tt(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_tV(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_tS(X, Y) alias_cga3d_outer_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product_Vs(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_Vv(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_Vb(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_Vt(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_VV(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_VS(X, Y) alias_cga3d_outer_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_outer_product_Ss(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_outer_product_Sv(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_outer_product_Sb(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_outer_product_St(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_outer_product_SV(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_outer_product_SS(X, Y) alias_cga3d_outer_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_REGRESSIVE_PRODUCT, X, Y)
#define alias_cga3d_regressive_product_ss(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_sv(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_sb(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_st(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_sV(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_sS(X, Y) alias_cga3d_regressive_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product_vs(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_vv(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_vb(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_vt(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_vV(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_vS(X, Y) alias_cga3d_regressive_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product_bs(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_bv(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_bb(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_bt(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_bV(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_bS(X, Y) alias_cga3d_regressive_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product_ts(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_tv(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_tb(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_tt(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_tV(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_tS(X, Y) alias_cga3d_regressive_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product_Vs(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_Vv(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_Vb(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_Vt(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_VV(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_VS(X, Y) alias_cga3d_regressive_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_regressive_product_Ss(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_regressive_product_Sv(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_regressive_product_Sb(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_regressive_product_St(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_regressive_product_SV(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_regressive_product_SS(X, Y) alias_cga3d_regressive_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_COMMUTATOR_PRODUCT, X, Y)
#define alias_cga3d_commutator_product_ss(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_sv(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_sb(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_st(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_sV(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_sS(X, Y) alias_cga3d_commutator_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product_vs(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_vv(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_vb(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_vt(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_vV(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_vS(X, Y) alias_cga3d_commutator_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product_bs(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_bv(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_bb(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_bt(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_bV(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_bS(X, Y) alias_cga3d_commutator_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product_ts(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_tv(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_tb(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_tt(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_tV(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_tS(X, Y) alias_cga3d_commutator_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product_Vs(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_Vv(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_Vb(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_Vt(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_VV(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_VS(X, Y) alias_cga3d_commutator_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_commutator_product_Ss(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_commutator_product_Sv(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_commutator_product_Sb(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_commutator_product_St(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_commutator_product_SV(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_commutator_product_SS(X, Y) alias_cga3d_commutator_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_INNER_PRODUCT, X, Y)
#define alias_cga3d_inner_product_ss(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_sv(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_sb(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_st(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_sV(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_sS(X, Y) alias_cga3d_inner_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product_vs(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_vv(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_vb(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_vt(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_vV(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_vS(X, Y) alias_cga3d_inner_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product_bs(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_bv(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_bb(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_bt(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_bV(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_bS(X, Y) alias_cga3d_inner_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product_ts(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_tv(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_tb(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_tt(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_tV(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_tS(X, Y) alias_cga3d_inner_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product_Vs(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_Vv(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_Vb(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_Vt(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_VV(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_VS(X, Y) alias_cga3d_inner_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_inner_product_Ss(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_inner_product_Sv(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_inner_product_Sb(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_inner_product_St(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_inner_product_SV(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_inner_product_SS(X, Y) alias_cga3d_inner_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product(X, Y) ALIAS_CGA3D_BINARY(ALIAS_CGA3D_OP_LEFT_DOT_PRODUCT, X, Y)
#define alias_cga3d_left_dot_product_ss(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_sv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_sb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_st(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_sV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_sS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product_vs(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_vv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_vb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_vt(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_vV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_vS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product_bs(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_bv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_bb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_bt(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_bV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_bS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product_ts(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_tv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_tb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_tt(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_tV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_tS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product_Vs(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_Vv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_Vb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_Vt(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_VV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_VS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_left_dot_product_Ss(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_left_dot_product_Sv(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_left_dot_product_Sb(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_left_dot_product_St(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_left_dot_product_SV(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_left_dot_product_SS(X, Y) alias_cga3d_left_dot_product(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_meet(X, Y) alias_cga3d_outer_product(X, Y)
#define alias_cga3d_meet_ss(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_sv(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_sb(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_st(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_sV(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_sS(X, Y) alias_cga3d_meet(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_meet_vs(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_vv(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_vb(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_vt(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_vV(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_vS(X, Y) alias_cga3d_meet(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_meet_bs(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_bv(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_bb(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_bt(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_bV(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_bS(X, Y) alias_cga3d_meet(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_meet_ts(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_tv(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_tb(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_tt(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_tV(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_tS(X, Y) alias_cga3d_meet(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_meet_Vs(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_Vv(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_Vb(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_Vt(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_VV(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_VS(X, Y) alias_cga3d_meet(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_meet_Ss(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_meet_Sv(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_meet_Sb(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_meet_St(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_meet_SV(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_meet_SS(X, Y) alias_cga3d_meet(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_join(X, Y) alias_cga3d_regressive_product(X, Y)
#define alias_cga3d_join_ss(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_join_sv(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_join_sb(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_join_st(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_join_sV(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_join_sS(X, Y) alias_cga3d_join(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_join_vs(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_join_vv(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_join_vb(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_join_vt(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_join_vV(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_join_vS(X, Y) alias_cga3d_join(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_join_bs(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_join_bv(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_join_bb(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_join_bt(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_join_bV(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_join_bS(X, Y) alias_cga3d_join(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_join_ts(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_join_tv(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_join_tb(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_join_tt(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_join_tV(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_join_tS(X, Y) alias_cga3d_join(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_join_Vs(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_join_Vv(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_join_Vb(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_join_Vt(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_join_VV(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_join_VS(X, Y) alias_cga3d_join(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_join_Ss(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_join_Sv(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_join_Sb(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_join_St(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_join_SV(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_join_SS(X, Y) alias_cga3d_join(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_neg(X) alias_cga3d_negate(X)
#define alias_cga3d_neg_s(X) alias_cga3d_neg(alias_cga3d_s(X))
#define alias_cga3d_neg_v(X) alias_cga3d_neg(alias_cga3d_v(X))
#define alias_cga3d_neg_b(X) alias_cga3d_neg(alias_cga3d_b(X))
#define alias_cga3d_neg_t(X) alias_cga3d_neg(alias_cga3d_t(X))
#define alias_cga3d_neg_V(X) alias_cga3d_neg(alias_cga3d_V(X))
#define alias_cga3d_neg_S(X) alias_cga3d_neg(alias_cga3d_S(X))
#define alias_cga3d_sub(X, Y) alias_cga3d_subtract(X, Y)
#define alias_cga3d_sub_ss(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_sv(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_sb(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_st(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_sV(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_sS(X, Y) alias_cga3d_sub(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_sub_vs(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_vv(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_vb(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_vt(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_vV(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_vS(X, Y) alias_cga3d_sub(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_sub_bs(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_bv(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_bb(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_bt(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_bV(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_bS(X, Y) alias_cga3d_sub(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_sub_ts(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_tv(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_tb(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_tt(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_tV(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_tS(X, Y) alias_cga3d_sub(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_sub_Vs(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_Vv(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_Vb(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_Vt(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_VV(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_VS(X, Y) alias_cga3d_sub(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_sub_Ss(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_sub_Sv(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_sub_Sb(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_sub_St(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_sub_SV(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_sub_SS(X, Y) alias_cga3d_sub(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_mul(X, Y) alias_cga3d_geometric_product(X, Y)
#define alias_cga3d_mul_ss(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_sv(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_sb(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_st(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_sV(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_sS(X, Y) alias_cga3d_mul(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_mul_vs(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_vv(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_vb(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_vt(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_vV(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_vS(X, Y) alias_cga3d_mul(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_mul_bs(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_bv(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_bb(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_bt(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_bV(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_bS(X, Y) alias_cga3d_mul(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_mul_ts(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_tv(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_tb(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_tt(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_tV(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_tS(X, Y) alias_cga3d_mul(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_mul_Vs(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_Vv(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_Vb(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_Vt(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_VV(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_VS(X, Y) alias_cga3d_mul(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_mul_Ss(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_mul_Sv(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_mul_Sb(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_mul_St(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_mul_SV(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_mul_SS(X, Y) alias_cga3d_mul(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_weg(X, Y) alias_cga3d_outer_product(X, Y)
#define alias_cga3d_weg_ss(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_sv(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_sb(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_st(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_sV(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_sS(X, Y) alias_cga3d_weg(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_weg_vs(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_vv(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_vb(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_vt(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_vV(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_vS(X, Y) alias_cga3d_weg(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_weg_bs(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_bv(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_bb(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_bt(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_bV(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_bS(X, Y) alias_cga3d_weg(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_weg_ts(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_tv(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_tb(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_tt(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_tV(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_tS(X, Y) alias_cga3d_weg(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_weg_Vs(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_Vv(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_Vb(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_Vt(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_VV(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_VS(X, Y) alias_cga3d_weg(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_weg_Ss(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_weg_Sv(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_weg_Sb(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_weg_St(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_weg_SV(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_weg_SS(X, Y) alias_cga3d_weg(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_vee(X, Y) alias_cga3d_regressive_product(X, Y)
#define alias_cga3d_vee_ss(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_sv(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_sb(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_st(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_sV(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_sS(X, Y) alias_cga3d_vee(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_vee_vs(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_vv(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_vb(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_vt(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_vV(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_vS(X, Y) alias_cga3d_vee(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_vee_bs(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_bv(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_bb(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_bt(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_bV(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_bS(X, Y) alias_cga3d_vee(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_vee_ts(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_tv(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_tb(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_tt(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_tV(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_tS(X, Y) alias_cga3d_vee(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_vee_Vs(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_Vv(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_Vb(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_Vt(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_VV(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_VS(X, Y) alias_cga3d_vee(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_vee_Ss(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_vee_Sv(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_vee_Sb(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_vee_St(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_vee_SV(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_vee_SS(X, Y) alias_cga3d_vee(alias_cga3d_S(X), alias_cga3d_S(Y))
#define alias_cga3d_dot(X, Y) alias_cga3d_inner_product(X, Y)
#define alias_cga3d_dot_ss(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_sv(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_sb(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_st(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_sV(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_sS(X, Y) alias_cga3d_dot(alias_cga3d_s(X), alias_cga3d_S(Y))
#define alias_cga3d_dot_vs(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_vv(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_vb(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_vt(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_vV(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_vS(X, Y) alias_cga3d_dot(alias_cga3d_v(X), alias_cga3d_S(Y))
#define alias_cga3d_dot_bs(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_bv(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_bb(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_bt(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_bV(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_bS(X, Y) alias_cga3d_dot(alias_cga3d_b(X), alias_cga3d_S(Y))
#define alias_cga3d_dot_ts(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_tv(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_tb(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_tt(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_tV(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_tS(X, Y) alias_cga3d_dot(alias_cga3d_t(X), alias_cga3d_S(Y))
#define alias_cga3d_dot_Vs(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_Vv(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_Vb(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_Vt(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_VV(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_VS(X, Y) alias_cga3d_dot(alias_cga3d_V(X), alias_cga3d_S(Y))
#define alias_cga3d_dot_Ss(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_s(Y))
#define alias_cga3d_dot_Sv(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_v(Y))
#define alias_cga3d_dot_Sb(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_b(Y))
#define alias_cga3d_dot_St(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_t(Y))
#define alias_cga3d_dot_SV(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_V(Y))
#define alias_cga3d_dot_SS(X, Y) alias_cga3d_dot(alias_cga3d_S(X), alias_cga3d_S(Y))
#endif // _ALIAS_CGA3D_H_
