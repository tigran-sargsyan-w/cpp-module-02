#include "Fixed.hpp"

const int Fixed::fractionalBits = 8;

/**
 * @brief Default constructor.
 * Initializes the fixed-point number to 0.
 */
Fixed::Fixed() : rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
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
        this->rawBits = other.getRawBits();
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
    return this->rawBits;
}

/**
 * @brief Sets the raw value of the fixed-point number.
 * @param raw The new raw value.
 */
void Fixed::setRawBits(int const raw)
{
    this->rawBits = raw;
}
