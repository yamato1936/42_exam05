# Exam 05: reconstruction guide

Memorize the **algorithm**, then reconstruct the code from scratch. The goal is a correct program, not the fewest characters.

## Level 0 / polyset (only `solution/` is your implementation)

The files under `given/` are the exam-style supplied starting code. Do not memorize or recreate them; examine the class members and inheritances.

Reconstruct the **six** `solution/` files in this order:

1. Headers: both searchable classes inherit their corresponding bag **and** `searchable_bag`.
2. Array `has(n)`: loop over `data[0..size)` and compare to `n`.
3. Tree `has(n)`: from `tree`, go left for `n < value`, right otherwise.
4. `set`: store a *non-owning pointer* to the searchable bag.
5. `set::insert(n)`: insert only if `!has(n)`; array insertion loops through single insert.
6. Copy constructor, assignment, destructor: same minimal canonical pattern.

**Important:** This wrapper does not eliminate duplicates already present inside a bag. Begin with an empty bag.

## Level 0 / bigint

Representation: **`std::string s` with no leading zeros**, except `"0"`.

1. Constructor: extract `n % 10` and prepend digits; use `do / while` for zero.
2. `cmp`: first compare string length, then lexicographic order.
3. `+=`: add from the right with `carry`.
4. `<<=`: append zeros; `>>=`: remove final digits (or become `"0"`).
5. Bigint shift amount: check its size against a bound, convert its digits, call the integer-shift overload.
6. Every non-mutating operator is a **copy then modify**; six comparisons delegate to `cmp`.

Try the original subject's main as well as `make bigint`.

## Level 1 / bsq

Memorize **parse -> DP -> paint -> output**.

1. Header: number of rows and three distinct marker characters.
2. Map: `getline` each row, validate width, characters, and newline.
3. One-dimensional DP: `dp[j]` is the **top**, `dp[j-1]` the **left**, and `diag` the **top-left** (save top before overwriting).
4. Free cell: `dp[j] = 1 + min(top, left, diag)`; obstacle: `dp[j] = 0`.
5. Update best **only when strictly greater**: row-major scan resolves ties top-to-bottom, then left-to-right.
6. Overwrite winning square with fill marker, print map. Report `map error` on invalid maps.

This source uses only the permitted input/output and allocation functions from the archived subject.

## Practice

```sh
make test
make clean
# Then hide the solutions and write each one from memory.
```

`vect2` and `life` intentionally remain unchanged.
