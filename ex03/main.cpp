#include <iostream>
#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

/**
 * @brief Tests if a point is inside the triangle formed by points a, b, and c.
 * Prints the result to the standard output.
 * @param a The first vertex of the triangle.
 * @param b The second vertex of the triangle.
 * @param c The third vertex of the triangle.
 * @param p The point to test.
 * @param label A label to describe the test case.
 */
static void	test(Point const &a, Point const &b, Point const &c, Point const &p, char const *label)
{
	std::cout << label << ": ";
	std::cout << (bsp(a, b, c, p) ? "INSIDE" : "NOT INSIDE") << std::endl;
}

/**
 * @brief Main function to test the bsp function with various points.
 * @return Exit status.
 */
int	main(void)
{
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(0.0f, 10.0f);

	test(a, b, c, Point(1.0f, 1.0f), "strictly inside");
	test(a, b, c, Point(4.0f, 4.0f), "strictly inside");
	test(a, b, c, Point(5.0f, 0.0f), "on edge AB");
	test(a, b, c, Point(0.0f, 0.0f), "on vertex A");
	test(a, b, c, Point(10.0f, 10.0f), "outside");

	return (0);
}
