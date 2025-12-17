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

## BSP

BSP (Binary Space Partitioning) — это алгоритм, который позволяет определить, находится ли точка P внутри треугольника ABC.
### Как определить, где точка P относительно треугольника ABC?

[Вот статья по 2-м самым популярным способам](https://www.sunshine2k.de/coding/java/PointInTriangle/PointInTriangle.html) (на английском).

И есть несколько способов это сделать.
- использовать векторное произведение (cross product) двух векторов.
- использовать барицентрические координаты.
- использовать площадь треугольников.
- использовать углы между векторами.
- и т.д.
В данном модуле мы реализуем первый способ — используя векторное произведение.

### Векторное произведение (Cross Product)

Точка — это позиция: A(x, y).

Вектор — это направление + длина, которое получается как “перейти из одной точки в другую”.

Пример:
- A(0,0)
- B(10,0)

Тогда вектор AB = B - A:
- AB.x = B.x - A.x = 10 - 0 = 10
- AB.y = B.y - A.y = 0 - 0 = 0

То есть AB = (10, 0) — стрелка вправо.
Точно так же:
- AP = P - A
- BC = C - B
- BP = P - B
- и т.д.

👉 В коде это вот эти строки:

```cpp
Fixed abx = b.getX() - a.getX();
Fixed aby = b.getY() - a.getY();
Fixed apx = p.getX() - a.getX();
Fixed apy = p.getY() - a.getY();
```

Формула:
```
cross(AB, AP) = AB.x * AP.y - AB.y * AP.x
```

cross 2-х векторов это по сути вектор перпендикулярный 2-м нашим векторам (по сути если у нас вектора XY, то cross будет Z).
И исходя из правила правой руки, мы можем понять, где точка P относительно линии AB.

Варианты правила правой руки:
1. Index finger, middle finger RHR (Правило трёх пальцев правой руки).

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Right_hand_rule_cross_product.svg/1200px-Right_hand_rule_cross_product.svg.png" alt="Правило трёх пальцев правой руки" width="300"/>

2. Curl Fingers RHR (Правило правого винта).

<img src="https://philschatz.com/calculus-book/resources/CNX_Calc_Figure_12_04_001.jpg" alt="Правило правого винта" width="300"/>

3. Palm-push RHR (Правило правой ладони).

<img src="https://files.mtstatic.com/site_4539/34581/0/webview?Expires=1765924494&Signature=EYmoevzGFthZ8Pkzr~AsavqwswsyR8o010gKBb~1J1ajA-saICuSBqae62GxwFYk7nFO3jeoMDYko9ydle-c86xeh1LPRICS8Hu-0Ux-jcpZsS~jqx9nGuktVN-6XEQJSJC1wQNg~TMSRE57GAeDpkQEesClmBPy~Yuc7UnJBds_&Key-Pair-Id=APKAJ5Y6AV4GI7A555NA" alt="Правило правой ладони" width="300"/>


Что это число означает (самое важное!)
- ЗНАК говорит, где точка P относительно линии AB:
    - cross > 0 → P слева
    - cross < 0 → P справа
    - cross = 0 → P на линии AB (на границе)