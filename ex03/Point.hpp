#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class Point
{
	private:
		Fixed const x;
		Fixed const y;

	public:
		Point(void);
		Point(float const xVal, float const yVal);
		Point(Point const &other);
		Point &operator=(Point const &other);
		~Point(void);

		Fixed const &getX(void) const;
		Fixed const &getY(void) const;
};


#endif