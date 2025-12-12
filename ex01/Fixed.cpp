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