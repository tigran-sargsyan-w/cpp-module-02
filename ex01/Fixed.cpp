#include "Fixed.hpp"
#include <cmath>

const int Fixed::fractionalBits = 8;

Fixed::Fixed() : value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int intValue)
{
    std::cout << "Int constructor called" << std::endl;
    // store int as fixed-point: shift left by fractionalBits
    value = intValue << fractionalBits;
}

Fixed::Fixed(const float floatValue)
{
    std::cout << "Float constructor called" << std::endl;
    // store float as fixed-point: roundf(f * 2^fractionalBits)
    value = static_cast<int>(roundf(floatValue * (1 << fractionalBits)));
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    value = other.value;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->value = other.value;
    return *this;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->value;
}

void Fixed::setRawBits(int const raw)
{
    this->value = raw;
}

float Fixed::toFloat() const
{
    // convert fixed-point to float: raw / 2^fractionalBits
    return static_cast<float>(value) / (1 << fractionalBits);
}

int Fixed::toInt() const
{
    // convert fixed-point to int: shift right by fractionalBits
    return value >> fractionalBits;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    // print as float representation
    out << fixed.toFloat();
    return out;
}