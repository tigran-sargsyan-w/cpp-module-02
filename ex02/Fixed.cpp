#include "Fixed.hpp"
#include <cmath>

const int Fixed::fractionalBits = 8;

/**
 * @brief Default constructor.
 * Initializes the fixed-point number to 0.
 */
Fixed::Fixed() : value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

/**
 * @brief Integer constructor.
 * Stores int as fixed-point number.
 * @param intValue The integer value to store as a fixed-point number.
 */
Fixed::Fixed(const int intValue)
{
    std::cout << "Int constructor called" << std::endl;
    value = intValue << fractionalBits;
}

/**
 * @brief Float constructor.
 * Stores float as fixed-point number.
 * @param floatValue The float value to store as a fixed-point number.
 */
Fixed::Fixed(const float floatValue)
{
    std::cout << "Float constructor called" << std::endl;
    value = static_cast<int>(roundf(floatValue * (1 << fractionalBits)));
}

/**
 * @brief Copy constructor.
 * @param other The other Fixed object to copy from.
 */
Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

/**
 * @brief Copy assignment operator.
 * @param other The other Fixed object to assign from.
 * @return A reference to the assigned Fixed object.
 */
Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->value = other.value;
    return *this;
}

/**
 * @brief Destructor.
 */
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

/**
 * @brief Gets the raw value of the fixed-point number.
 * @return The raw value of the fixed-point number.
 */
int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->value;
}

/**
 * @brief Sets the raw value of the fixed-point number.
 * @param raw The new raw value.
 */
void Fixed::setRawBits(int const raw)
{
    this->value = raw;
}

/**
 * @brief Converts the fixed-point number to a float.
 * @return The float representation of the fixed-point number.
 */
float Fixed::toFloat() const
{
    return static_cast<float>(value) / (1 << fractionalBits);
}

/**
 * @brief Converts the fixed-point number to an integer.
 * @return The integer representation of the fixed-point number.
 */
int Fixed::toInt() const
{
    return value >> fractionalBits;
}

/**
 * @brief Overloads the << operator to print the Fixed object.
 * Prints the float representation of the fixed-point number.
 * @param out The output stream.
 * @param fixed The Fixed object to print.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return out;
}


// ===== Comparison operators =====

bool Fixed::operator>(const Fixed &rhs) const { return (value > rhs.value); }
bool Fixed::operator<(const Fixed &rhs) const { return (value < rhs.value); }
bool Fixed::operator>=(const Fixed &rhs) const { return (value >= rhs.value); }
bool Fixed::operator<=(const Fixed &rhs) const { return (value <= rhs.value); }
bool Fixed::operator==(const Fixed &rhs) const { return (value == rhs.value); }
bool Fixed::operator!=(const Fixed &rhs) const { return (value != rhs.value); }

// ===== Arithmetic operators =====

Fixed Fixed::operator+(const Fixed &rhs) const
{
	Fixed out;
	out.setRawBits(value + rhs.value);
	return (out);
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	Fixed out;
	out.setRawBits(value - rhs.value);
	return (out);
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	Fixed out;
	long long prod;

	prod = static_cast<long long>(value) * static_cast<long long>(rhs.value);
	out.setRawBits(static_cast<int>(prod >> fractionalBits));
	return (out);
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	Fixed out;
	long long num;

	// Division by 0 may crash
	num = (static_cast<long long>(value) << fractionalBits);
	out.setRawBits(static_cast<int>(num / rhs.value));
	return (out);
}

// ===== Increment / Decrement =====
// C++ rule: postfix increment/decrement are declared with a dummy `int`.
// The argument is not used; the compiler passes an arbitrary value (typically 0).
// This makes the signature different: ++a -> operator++(), a++ -> operator++(int).

Fixed &Fixed::operator++(void)
{
	value += 1;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed old(*this);
	value += 1;
	return (old);
}

Fixed &Fixed::operator--(void)
{
	value -= 1;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed old(*this);
	value -= 1;
	return (old);
}

// ===== Min / Max =====

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b ? a : b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b ? a : b);
}