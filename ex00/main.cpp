#include <iostream>
#include "Fixed.hpp"

/**
 * @brief The main function.
 * @return 0 on success.
 */
int	main(void)
{
	Fixed a;
	Fixed b(a);
	Fixed c;

	c = b;
	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;
	return (0);
}