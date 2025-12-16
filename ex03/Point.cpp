#include "Point.hpp"

Point::Point(void) 
    : x(0), y(0) {}

Point::Point(float const xVal, float const yVal) 
    : x(xVal), y(yVal) {}

Point::Point(Point const &other) 
    : x(other.x), y(other.y) {}

Point &Point::operator=(Point const &other)
{
	(void)other;
    // x and y are const, they cannot be reassigned after initialization.
	return (*this);
}

Point::~Point(void) {}

Fixed const &Point::getX(void) const
{
	return (this->x);
}

Fixed const &Point::getY(void) const
{
	return (this->y);
}
