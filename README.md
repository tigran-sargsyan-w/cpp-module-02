# cpp-module-02
This module is designed to help you understand ad-hoc polymorphism, function overloading, and orthodox canonical classes in C++.

# Bit Shifts and Powers of Two

## Multiplying by 2^n

For integer values, multiplying by 2^n can be done in several ways.

* **Using bitwise left shift** (recommended for integers):

```cpp
int result = x << n; // x * 2^n
```

* **Using the `pow` function from the `<cmath>` library** (less ideal for integers because it uses floating point):

```cpp
#include <cmath>

int result = static_cast<int>(x * pow(2, n)); // x * 2^n
```

* **Using a loop**:

```cpp
int result = x;
for (int i = 0; i < n; ++i)
{
    result *= 2; // multiply by 2 each step
}
```

---

## Dividing by 2^n

For positive integers, dividing by 2^n can also be written in several ways.

* **Using bitwise right shift** (for non-negative integers):

```cpp
int result = x >> n; // x / 2^n, fractional part is discarded
```

* **Using integer division with a power-of-two factor**:

```cpp
int result = x / (1 << n); // x / 2^n, integer division
```

* **Using a loop**:

```cpp
int result = x;
for (int i = 0; i < n; ++i)
{
    result /= 2; // divide by 2 each step, discarding fractions
}
```

In summary:

* `x << n` is equivalent to `x * 2^n` (for integers without overflow).
* `x >> n` is roughly equivalent to `x / 2^n` for non-negative integers, with the fractional part discarded.
