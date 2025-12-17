#include "Point.hpp"

static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	Fixed abx = b.getX() - a.getX();
	Fixed aby = b.getY() - a.getY();
	Fixed apx = p.getX() - a.getX();
	Fixed apy = p.getY() - a.getY();

	return (abx * apy - aby * apx);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed d1 = cross(a, b, point);
	Fixed d2 = cross(b, c, point);
	Fixed d3 = cross(c, a, point);

	// На ребре (или на прямой ребра) — нельзя
	if (d1 == 0 || d2 == 0 || d3 == 0)
		return (false);
	
	bool allPositive = ((d1 > 0) && (d2 > 0) && (d3 > 0));
	bool allNegative = ((d1 < 0) && (d2 < 0) && (d3 < 0));

	return (allPositive || allNegative);
}
