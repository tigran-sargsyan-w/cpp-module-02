# C++ Module 02 – Fixed-Point Numbers & Operator Overloading 🔢🧩

✅ **Status**: Completed – all exercises *(ex03 optional)*

🏫 **School**: 42 – C++ Modules (Module 02)

> *Ad-hoc polymorphism, operator overloading, and the Orthodox Canonical Class Form (C++98).*

---

## 📚 Table of Contents

* [Description](#-description)
* [Goals of the Module](#-goals-of-the-module)
* [How `Fixed` Works (Quick Intuition)](#-how-fixed-works-quick-intuition)

  * [Bit Shifts and Powers of Two](#bit-shifts-and-powers-of-two)
* [How BSP Works (ex03)](#-how-bsp-works-ex03)

  * [BSP](#bsp)
  * [Векторное произведение (Cross Product)](#векторное-произведение-cross-product)
  * [Правило правой руки](#правило-правой-руки)
  * [Что означает значение cross](#что-означает-значение-cross)
* [Exercises Overview](#-exercises-overview)

  * [ex00 – My First Class in Orthodox Canonical Form](#ex00--my-first-class-in-orthodox-canonical-form)
  * [ex01 – Towards a more useful fixed-point number class](#ex01--towards-a-more-useful-fixed-point-number-class)
  * [ex02 – Now we’re talking](#ex02--now-were-talking)
  * [ex03 – BSP (optional)](#ex03--bsp-optional)
* [Requirements](#-requirements)
* [Build & Run](#-build--run)
* [Repository Layout](#-repository-layout)
* [Testing Tips](#-testing-tips)
* [42 Notes](#-42-notes)

---

## 📝 Description

This repository contains my solutions to **42’s C++ Module 02 (C++98)**.
The module focuses on building a **fixed-point number class**, progressively enhancing it with conversions, stream output, comparisons, arithmetic, and increment/decrement operators — all while respecting the **Orthodox Canonical Form**.

---

## 🎯 Goals of the Module

Concepts covered:

* **Orthodox Canonical Form** (default ctor, copy ctor, copy assignment, destructor)
* **Operator overloading** (`<<`, comparisons, arithmetic, ++/--, min/max)
* Fixed-point representation and precision behavior (fractional bits)
* Clean separation: **headers** (`.hpp`) vs **implementation** (`.cpp`)

---

## 🧠 How `Fixed` Works (Quick Intuition)

In this module, `Fixed` stores a real number using an **integer** internally:

* The internal storage is usually something like `int raw`.
* The class uses a constant number of **fractional bits** (in the subject it’s typically `8`).
* That means your value is scaled by:

```cpp
scale = 1 << fractionalBits; // for 8 bits => 1 << 8 == 256
```

So you can think of it like:

* **Real value** = `raw / 256`
* **Raw value** = `real * 256`

Examples (with 8 fractional bits):

* `1.0` is stored as `256`
* `42.0` is stored as `42 * 256 = 10752`
* the smallest step (epsilon) is `1 / 256`

That’s also why in **ex02** `++fixed` increases the value by exactly **one epsilon**: it increments the raw integer by `1`, which corresponds to `+1/256`.

---

### Bit Shifts and Powers of Two

#### Multiplying by 2^n

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

#### Dividing by 2^n

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

> 🔗 How it maps to `Fixed`
> If your `Fixed` has `fractionalBits = 8`, then:
>
> * Converting `int -> Fixed` is basically `raw = i << 8`
> * Converting `Fixed -> int` is basically `i = raw >> 8` (discarding fractions)

---

## 📐 How BSP Works (ex03)

This section is a practical explanation of the idea behind **ex03**: checking whether a point `P` lies strictly inside triangle `ABC`.
In this module we typically use the **cross product** approach (orientation test).

### BSP

BSP (Binary Space Partitioning) — это алгоритм, который позволяет определить, находится ли точка P внутри треугольника ABC.

#### Как определить, где точка P относительно треугольника ABC?

[Вот статья по 2-м самым популярным способам](https://www.sunshine2k.de/coding/java/PointInTriangle/PointInTriangle.html) (на английском).

И есть несколько способов это сделать:

* использовать векторное произведение (cross product) двух векторов
* использовать барицентрические координаты
* использовать площадь треугольников
* использовать углы между векторами
* и т.д.

В данном модуле мы реализуем первый способ — используя векторное произведение.

---

### Векторное произведение (Cross Product)

Точка — это позиция: A(x, y).

Вектор — это направление + длина, которое получается как “перейти из одной точки в другую”.

Пример:

* A(0,0)
* B(10,0)

Тогда вектор AB = B - A:

* AB.x = B.x - A.x = 10 - 0 = 10
* AB.y = B.y - A.y = 0 - 0 = 0

То есть AB = (10, 0) — стрелка вправо.
Точно так же:

* AP = P - A
* BC = C - B
* BP = P - B
* и т.д.

👉 В коде это вот эти строки:

```cpp
Fixed abx = b.getX() - a.getX();
Fixed aby = b.getY() - a.getY();
Fixed apx = p.getX() - a.getX();
Fixed apy = p.getY() - a.getY();
```

Формула:

```text
cross(AB, AP) = AB.x * AP.y - AB.y * AP.x
```

`cross` 2-х векторов — это по сути вектор перпендикулярный 2-м нашим векторам
(в 2D мы считаем “z-компоненту”, которая говорит ориентацию: по/против часовой).

---

### Правило правой руки

Исходя из правила правой руки, мы можем понять, где точка P относительно линии AB.

Варианты правила правой руки:

1. Index finger, middle finger RHR (Правило трёх пальцев правой руки).

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Right_hand_rule_cross_product.svg/1200px-Right_hand_rule_cross_product.svg.png" alt="Правило трёх пальцев правой руки" width="300"/>

2. Curl Fingers RHR (Правило правого винта).

<img src="https://philschatz.com/calculus-book/resources/CNX_Calc_Figure_12_04_001.jpg" alt="Правило правого винта" width="300"/>

3. Palm-push RHR (Правило правой ладони).

<img src="https://files.mtstatic.com/site_4539/34581/0/webview?Expires=1765924494&Signature=EYmoevzGFthZ8Pkzr~AsavqwswsyR8o010gKBb~1J1ajA-saICuSBqae62GxwFYk7nFO3jeoMDYko9ydle-c86xeh1LPRICS8Hu-0Ux-jcpZsS~jqx9nGuktVN-6XEQJSJC1wQNg~TMSRE57GAeDpkQEesClmBPy~Yuc7UnJBds_&Key-Pair-Id=APKAJ5Y6AV4GI7A555NA" alt="Правило правой ладони" width="300"/>

> ⚠️ Note: the last image link may expire (it contains a signed URL). If you want long-term stability on GitHub, consider rehosting it or switching to a stable source.

---

### Что означает значение cross

Что это число означает (самое важное!):

* **ЗНАК** говорит, где точка P относительно линии AB:

  * `cross > 0` → P слева
  * `cross < 0` → P справа
  * `cross = 0` → P на линии AB (на границе)

👉 Как это используется для треугольника `ABC`:

* Вычисляем `cross(AB, AP)`, `cross(BC, BP)`, `cross(CA, CP)`
* Если все три **одного знака** (и ни одно не равно 0), то точка **строго внутри**
* Если хотя бы одно равно 0 → точка на границе → **false** (по subject: edges/vertices are excluded)

---

## 📦 Exercises Overview

### ex00 – My First Class in Orthodox Canonical Form

**Goal:** Create a `Fixed` class (OCF) storing a fixed-point value as an `int`, with **8 fractional bits** stored as a `static const int`. Add `getRawBits()` / `setRawBits()`.

---

### ex01 – Towards a more useful fixed-point number class

**Goal:** Add:

* `Fixed(int const)`
* `Fixed(float const)`
* `toFloat()` and `toInt()`
* `operator<<` to print float representation

**Allowed function:** `roundf` (from `<cmath>`)

---

### ex02 – Now we’re talking

**Goal:** Add:

* Comparisons: `> < >= <= == !=`
* Arithmetic: `+ - * /`
* Pre/Post increment & decrement
* Static `min` / `max` overloads for const and non-const references

**Allowed function:** `roundf` (from `<cmath>`)

---

### ex03 – BSP (optional)

**Goal:** Implement:

* `Point` class with **const** `Fixed` coordinates
* `bsp(a, b, c, point)` → `true` only if `point` is strictly inside triangle (edges/vertices → false)

---

## 🛠 Requirements

From the subject:

* **Compiler**: `c++`
* **Flags**: `-Wall -Wextra -Werror` + `-std=c++98`
* Forbidden: `printf`, `malloc/alloc`, `free` (and family)
* Also forbidden unless explicitly allowed: `using namespace ...`, `friend`
* **No STL containers/algorithms** until later modules (08/09)

Makefile expectations follow the same rules as in C projects (targets like `all/clean/fclean/re`, no unnecessary relink, etc.).

---

## ▶️ Build & Run

```bash
git clone <this-repo-url>
cd cpp-module-02
```

```bash
cd ex00 && make && ./a.out
cd ../ex01 && make && ./a.out
cd ../ex02 && make && ./a.out
cd ../ex03 && make && ./a.out   # optional
```

---

## 📂 Repository Layout

```text
cpp-module-02/
├── ex00/  (Fixed OCF + raw bits)
├── ex01/  (int/float conversions + operator<<)
├── ex02/  (full operators)
└── ex03/  (Point + bsp)  [optional]
```

---

## 🔍 Testing Tips

* Verify that `toInt()` truncates toward zero (fraction discarded)
* Compare `a++` vs `++a`
* Validate `min/max` for const and non-const overloads
* For ex03: points inside/outside/on-edge/on-vertex (edge & vertex must be false)

---

## 🧾 42 Notes

* C++ modules do **not** use Norminette; readability still matters for peer evaluation.
* From Module 02 onward, **Orthodox Canonical Form is mandatory** unless stated otherwise.
