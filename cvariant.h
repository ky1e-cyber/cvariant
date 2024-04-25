#ifndef CVAR_INCLUDE_H
#define CVAR_INCLUDE_H

#define _CVAR_MAPN(...)                                                        \
  _CVAR_MAPN_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, \
              1, 0)

#define _CVAR_MAPN_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,     \
                    _13, _14, _15, _16, ...)                                   \
  _CVAR_TWOMAP##_16

#define _CVAR_MAPN2(...)                                                       \
  _CVAR_MAPN2_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3,   \
               2, 1, 0)

#define _CVAR_MAPN2_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,    \
                     _13, _14, _15, _16, ...)                                  \
  _CVAR_TWOTWOMAP##_16

#define _CVAR_TWOMAP1(F, k, x) F(k, x)
#define _CVAR_TWOMAP2(F, k, x, ...) F(k, x) _CVAR_TWOMAP1(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP3(F, k, x, ...) F(k, x) _CVAR_TWOMAP2(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP4(F, k, x, ...) F(k, x) _CVAR_TWOMAP3(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP5(F, k, x, ...) F(k, x) _CVAR_TWOMAP4(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP6(F, k, x, ...) F(k, x) _CVAR_TWOMAP5(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP7(F, k, x, ...) F(k, x) _CVAR_TWOMAP6(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP8(F, k, x, ...) F(k, x) _CVAR_TWOMAP7(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP9(F, k, x, ...) F(k, x) _CVAR_TWOMAP8(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP10(F, k, x, ...) F(k, x) _CVAR_TWOMAP9(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP11(F, k, x, ...) F(k, x) _CVAR_TWOMAP10(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP12(F, k, x, ...) F(k, x) _CVAR_TWOMAP11(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP13(F, k, x, ...) F(k, x) _CVAR_TWOMAP12(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP14(F, k, x, ...) F(k, x) _CVAR_TWOMAP13(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP15(F, k, x, ...) F(k, x) _CVAR_TWOMAP14(F, k, __VA_ARGS__)
#define _CVAR_TWOMAP16(F, k, x, ...) F(k, x) _CVAR_TWOMAP15(F, k, __VA_ARGS__)

#define _CVAR_TWOMAP(F, k, x, ...)                                             \
  F(k, x) __VA_OPT__(_CVAR_MAPN(__VA_ARGS__)(F, k, __VA_ARGS__))

#define _CVAR_TWOTWOMAP2(F1, F2, k, x1, x2) F1(k, x1) F2(k, x2)
#define _CVAR_TWOTWOMAP4(F1, F2, k, x1, x2, ...)                               \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP2(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP6(F1, F2, k, x1, x2, ...)                               \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP4(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP8(F1, F2, k, x1, x2, ...)                               \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP6(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP10(F1, F2, k, x1, x2, ...)                              \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP8(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP12(F1, F2, k, x1, x2, ...)                              \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP10(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP14(F1, F2, k, x1, x2, ...)                              \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP12(F1, F2, k, __VA_ARGS__)
#define _CVAR_TWOTWOMAP16(F1, F2, k, x1, x2, ...)                              \
  F1(k, x1) F2(k, x2) _CVAR_TWOTWOMAP14(F1, F2, k, __VA_ARGS__)

#define _CVAR_TWOTWOMAP(F1, F2, k, x1, x2, ...)                                \
  F1(k, x1)                                                                    \
  F2(k, x2) __VA_OPT__(_CVAR_MAPN2(__VA_ARGS__)(F1, F2, k, __VA_ARGS__))

#define _CVAR_ENUM_TAG(name, t) _TAG_##name##_##t
#define _CVAR_UNION_T(name, t) _CTR_##name##_##t

#define _CVAR_ENUM_MEM(name, t) _CVAR_ENUM_TAG(name, t),
#define _CVAR_UNION_MEM(name, t) t _CVAR_UNION_T(name, t);

#define _CVAR_GET_FUNC(name, t)                                                \
  extern inline t name##_as_##t(name v) { return v.val._CVAR_UNION_T(name, t); }

#define _CVAR_CREATE_FUNC(name, t)                                             \
  extern inline name name##_##t(t x) {                                         \
    return (name){.tag = _CVAR_ENUM_TAG(name, t),                              \
                  .val = {._CVAR_UNION_T(name, t) = x}};                       \
  }

#define _CVAR_CASE(name, t) case _CVAR_ENUM_TAG(name, t):
#define _CVAR_CASEBODY(name, body)                                             \
  (body);                                                                      \
  break;

#define genvariant(name, ...)                                                  \
  typedef enum {                                                               \
    _CVAR_TWOMAP(_CVAR_ENUM_MEM, name, __VA_ARGS__)                            \
  } TAG##name##T;                                                              \
  typedef struct {                                                             \
    TAG##name##T tag;                                                          \
    union {                                                                    \
      _CVAR_TWOMAP(_CVAR_UNION_MEM, name, __VA_ARGS__)                         \
    } val;                                                                     \
  } name;                                                                      \
  _CVAR_TWOMAP(_CVAR_GET_FUNC, name, __VA_ARGS__)                              \
  _CVAR_TWOMAP(_CVAR_CREATE_FUNC, name, __VA_ARGS__)                           \
  void _CVAR_NOTHING##name()

#define match(typename, name, ...)                                             \
  switch (name.tag) {                                                          \
    _CVAR_TWOTWOMAP(_CVAR_CASE, _CVAR_CASEBODY, typename, __VA_ARGS__)         \
  }                                                                            \
  (int){0} = 0

#endif // #ifndef CVAR_INCLUDE_H
