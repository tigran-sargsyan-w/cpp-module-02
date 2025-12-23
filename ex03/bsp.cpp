#include "Point.hpp"

/**
 * @brief Helper function to compute the cross product of vectors AB and AP.
 * @param a The starting point of both vectors.
 * @param b The end point of vector AB.
 * @param p The end point of vector AP.
 * @return The cross product as a Fixed number.
 */
static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	Fixed abx = b.getX() - a.getX();
	Fixed aby = b.getY() - a.getY();
	Fixed apx = p.getX() - a.getX();
	Fixed apy = p.getY() - a.getY();

	return (abx * apy - aby * apx);
}

/**
 * @brief Determines if a point is inside the triangle formed by points a, b, and c.
 * Uses the cross product method to check the relative position of the point to the triangle edges.
 * @param a The first vertex of the triangle.
 * @param b The second vertex of the triangle.
 * @param c The third vertex of the triangle.
 * @param point The point to test.
 * @return true if the point is inside the triangle, false otherwise.
 */
bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed d1 = cross(a, b, point);
	Fixed d2 = cross(b, c, point);
	Fixed d3 = cross(c, a, point);

	// On the edge (or on the line of the edge) — not allowed
	if (d1 == 0 || d2 == 0 || d3 == 0)
		return (false);
	
	bool allPositive = ((d1 > 0) && (d2 > 0) && (d3 > 0));
	bool allNegative = ((d1 < 0) && (d2 < 0) && (d3 < 0));

	return (allPositive || allNegative);
}
