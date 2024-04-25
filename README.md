# cvariant

C/C++ [stb-style header-only library](https://github.com/nothings/stb) for variant (tagged union) data type.

## Quick start

Copy [cvariant.h](./cvariant.h) into project/include then

```c
#include "cvariant.h"
```

and generate your variant structure with

```c
// UP TO 16 TYPES CURRENTLY
genvariant(name_for_variant, type1, ..., typeN);
```

(No need for implementation flag)

## Examples

```c
#include <stdio.h>
#include "cvariant.h"

genvariant(IntFloat, int, float);

void print_type(IntFloat v) {
  match( IntFloat, v,
         int, printf("int: %d\n", IntFloat_as_int(v)),
         float, printf("float: %f\n", IntFloat_as_float(v)) );
}

int main() {
  IntFloat i = IntFloat_int(420);
  IntFloat f = IntFloat_float(0.69f);

  print_type(i); // int: 420
  print_type(f); // float: 0.690000

  return 0;
}
```

```c
#include <stdio.h>
#include "cvariant.h"

typedef struct {
} none;

genvariant(shmoptional_int, int, none);

shmoptional_int checked_division(int dividend, int divisor) {
  if (divisor == 0) {
    return shmoptional_int_none((none){});
  }

  return shmoptional_int_int(dividend / divisor);
}

int main() {
  shmoptional_int exp1 = checked_division(10, 0);

  int res = 0;
  match( shmoptional_int, exp1,
         int, res = shmoptional_int_as_int(exp1),
         none, ({ printf("We messed up!\n");
                  res = -1; }) );

  printf("res = %d\n", res); // We messed up!
                             // res = -1
  return 0;
}
```

```c
#include <stdio.h>
#include "cvariant.h"

typedef struct {
  void *left_expr;
  void *right_expr;
  int (*op)(int, int);
} binary;

typedef struct {
  void *expr;
  int (*op)(int);
} unary;

typedef struct {
  int val;
} num;

genvariant(expr, binary, unary, num);

int eval_expr(expr e) {
  match( expr, e,
         num,    ({ return expr_as_num(e).val; }),

         unary,  ({ unary u = expr_as_unary(e);
                    expr e = *((expr *)u.expr);
                    return u.op(eval_expr(e)); }),

         binary, ({ binary b = expr_as_binary(e);
                    expr left = *((expr *)b.left_expr);
                    expr right = *((expr *)b.right_expr);
                    return b.op(eval_expr(left), eval_expr(right)); }) );
}

int un_minis(int x) { return -x; }

int bin_plus(int x, int y) { return x + y; }

int bin_mul(int x, int y) { return x * y; }

int main() {

  // -(5 * 2) + 44 * 4 == 166

  expr five = expr_num((num){5});
  expr two = expr_num((num){2});
  expr ff = expr_num((num){44});
  expr four = expr_num((num){4});

  expr ft = expr_binary(
      (binary){.left_expr = &five, .right_expr = &two, .op = bin_mul}); // 5 * 2
  expr fff = expr_binary(
      (binary){.left_expr = &ff, .right_expr = &four, .op = bin_mul}); // 44 * 4

  expr minft = expr_unary((unary){.expr = &ft, .op = un_minis}); // -(5 * 2)

  expr fin = expr_binary((binary){.left_expr = &minft,
                                  .right_expr = &fff,
                                  .op = bin_plus}); // (-(5 * 2)) + (44 * 4)

  printf("%d\n", eval_expr(fin)); // 166

  return 0;
}
```

