# Cheat Sheet: `float` (IEEE‑754, 32‑bit) 💧

## 1. What `float` actually is 🧮

* A **floating‑point** type: the value is stored approximately as

  **value = (−1)^sign × 1.mantissa₂ × 2^e**

  where `1.mantissa₂` is the binary significand (mantissa) and `e` is an integer exponent.
* Represents **approximate real numbers**, *not* exact math. Many decimal fractions (0.1, 0.2, 0.3, …) cannot be represented exactly.

---

## 2. Internal layout of a 32‑bit `float` 🧱

Total **32 bits**:

* 1 bit — **sign** (0 = positive, 1 = negative ➕➖)
* 8 bits — **exponent** (stored with bias = 127)
* 23 bits — **fraction** (fractional part of the mantissa)

Decoded value:

```text
value = (−1)^sign_bit × 1.fraction_bits₂ × 2^(exponent_bits − 127)
```

* `1.fraction_bits₂` = implicit leading 1 + 23 fractional bits.
* `exponent_bits` is the unsigned value stored in the exponent field.

---

## 3. Range and precision 🎯

* Approximate magnitude range: **from ~1.18×10⁻³⁸ to ~3.4×10³⁸**.
* Precision: about **6–7 decimal significant digits**.

👉 Rule of thumb: `float` is fine for *rough* real numbers, but not for money, high‑precision physics, etc.

---

## 4. Special values ⚠️

Reserved bit patterns:

* **+0.0 / −0.0** — exponent = 0, fraction = 0, sign decides +0 / −0.
* **+∞ / −∞** — exponent = 255 (all ones), fraction = 0.
* **NaN** (Not a Number) — exponent = 255, fraction ≠ 0.

NaN shows up when a result is mathematically “undefined”, like `0.0f / 0.0f`.

---

## 5. Typical pitfalls with `float` 🪤

1. **Using `==` for comparison is unsafe in general**

   ```cpp
   float a = 0.1f + 0.2f;
   float b = 0.3f;

   // Bad (might be false due to rounding):
   if (a == b) { /* ... */ }

   // Better:
   if (fabs(a - b) < 1e-6f) { /* ... */ }
   ```

   Many decimal fractions are not exactly representable in binary → tiny rounding errors.

2. **Error accumulation** ⏱️

   A long sequence of operations can accumulate rounding error.

3. **Overflow and loss of significance** 💥

   * Very large results → ±∞.
   * Subtracting nearly equal numbers → loss of significant digits (cancellation).

---

## 6. `float` vs `double` 🆚

* `float`: 32 bits, ~6–7 decimal digits of precision.
* `double`: 64 bits, ~15–16 decimal digits of precision.

👉 In most serious numeric code, `double` is preferred; `float` is used when memory/performance really matters (graphics, large arrays, etc.).

---

## 7. Relation to fixed‑point (`Fixed` from C++ Module 02) ⚖️

* `float`: mantissa + exponent → the **binary point “floats”**; spacing between representable numbers grows with magnitude.
* fixed‑point: one integer + a fixed number of fractional bits → the **binary point is fixed**; spacing between representable numbers is constant (step = `1 / 2^fractionalBits`).

Think of it like this:

* `float` = scientific notation in base 2.
* fixed‑point = integer grid with a constant step size.

---

# Cheat Sheet: Converting a number to ±1.xxx₂ × 2^e 🔄

How to get the **normalized binary form** used conceptually by IEEE‑754.

## 1. Core idea 💡

For any non‑zero finite value:

> **x = (±1.xxx₂) × 2^e**

where the part before the binary point is always exactly `1` (normalized form).

---

## 2. High‑level algorithm (math view) 📐

### Step 1. Determine the sign

* If `x < 0` → `sign = 1`, work with `|x|`.
* If `x ≥ 0` → `sign = 0`.

### Step 2. Convert to binary

Split `x` into integer and fractional parts:

```text
x = N + f, where N is integer, f is fractional (0 ≤ f < 1)
```

1. Convert **N** to binary by repeated division by 2, collecting remainders (from bottom to top).
2. Convert **f** to binary by repeatedly multiplying by 2 and recording the integer part (0 or 1) as each next bit after the point.

Result: a binary representation like `…xxx.yyy₂`.

### Step 3. Normalize to 1.xxx₂

Move the binary point so that there is exactly one `1` to the left of it.

* Example (larger number):

  * `101.11₂ → 1.0111₂ × 2²`
  * We shifted the point **left by 2 positions** → exponent `e = 2`.

* Example (small number):

  * `0.00101₂ → 1.01₂ × 2⁻³`
  * We shifted the point **right by 3 positions** → exponent `e = −3`.

Rule of thumb:

* Shift **left by k** → multiply by `2^k`.
* Shift **right by k** → multiply by `2^(−k)`.

We compensate that shift with the exponent `e`.

### Step 4. Final normalized form ✅

Write the number as:

```text
x = (±1.mantissa₂) × 2^e
```

where `1.mantissa₂` is the normalized significand and `e` is the exponent.

---

## 3. Mapping normalized form to IEEE‑754 `float` 🧾

Once we have `x = (±1.mantissa₂) × 2^e`, we build the actual `float` fields:

1. **Sign bit**:

   * 0 if `x ≥ 0`,
   * 1 if `x < 0`.

2. **Exponent field (8 bits)**:

   * `exponent_bits = e + 127` (for 32‑bit float, bias = 127).

3. **Fraction field (23 bits)**:

   * store only the fractional part of the mantissa (bits after the `1.`),
   * pad with zeros if fewer than 23 bits,
   * round if more than 23 bits.

Decoding formula:

```text
value = (−1)^sign_bit × 1.fraction_bits₂ × 2^(exponent_bits − 127)
```

---

## 4. Mini‑example (5.75) 🧊

1. Decimal to binary:

   * 5.75₁₀ = 101.11₂
2. Normalize:

   * `101.11₂ → 1.0111₂ × 2²` → mantissa = `1.0111₂`, exponent `e = 2`.
3. Sign:

   * `sign_bit = 0` (positive).
4. Exponent bits:

   * `exponent_bits = e + 127 = 2 + 127 = 129` → `10000001₂`.
5. Fraction bits:

   * fractional part = `0111`, padded to 23 bits: `01110000000000000000000`.

Final IEEE‑754 layout:

```text
sign      exponent        fraction
0         10000001        01110000000000000000000
```

This bit pattern is exactly `5.75f` in memory 💾.
