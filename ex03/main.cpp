#include <iostream>
#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

static void	test(Point const &a, Point const &b, Point const &c, Point const &p, char const *label)
{
	std::cout << label << ": ";
	std::cout << (bsp(a, b, c, p) ? "INSIDE" : "NOT INSIDE") << std::endl;
}

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
