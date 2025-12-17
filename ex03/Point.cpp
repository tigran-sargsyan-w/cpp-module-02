#include "Point.hpp"

/**
 * @brief Default constructor.
 * Initializes the point at the origin (0,0).
 */
Point::Point(void) 
    : x(0), y(0) {}

/**
 * @brief Parameterized constructor.
 * Initializes the point with given x and y coordinates.
 * @param xVal The x coordinate.
 * @param yVal The y coordinate.
 */
Point::Point(float const xVal, float const yVal) 
    : x(xVal), y(yVal) {}

/**
 * @brief Copy constructor.
 * @param other The other Point object to copy from.
 */
Point::Point(Point const &other) 
    : x(other.x), y(other.y) {}

/**
 * @brief Copy assignment operator.
 * Since x and y are const, they cannot be reassigned after initialization.
 * This operator does nothing and simply returns *this.
 * @param other The other Point object to assign from.
 * @return A reference to the assigned Point object.
 */
Point &Point::operator=(Point const &other)
{
	(void)other;
	return (*this);
}

/**
 * @brief Destructor.
 */
Point::~Point(void) {}

/**
 * @brief Gets the x coordinate of the point.
 * @return A constant reference to the x coordinate.
 */
Fixed const &Point::getX(void) const
{
	return (this->x);
}

/**
 * @brief Gets the y coordinate of the point.
 * @return A constant reference to the y coordinate.
 */
Fixed const &Point::getY(void) const
{
	return (this->y);
}
