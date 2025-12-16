#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
  private:
  	int value;
	static const int fractionalBits;

  public:
	Fixed();
	Fixed(const int intValue);
    Fixed(const float floatValue);
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);

	float toFloat() const;
    int toInt() const;

	// Comparison operators
	bool operator>(const Fixed &rhs) const;
	bool operator<(const Fixed &rhs) const;
	bool operator>=(const Fixed &rhs) const;
	bool operator<=(const Fixed &rhs) const;
	bool operator==(const Fixed &rhs) const;
	bool operator!=(const Fixed &rhs) const;

	// Arithmetic operators
	Fixed operator+(const Fixed &rhs) const;
	Fixed operator-(const Fixed &rhs) const;
	Fixed operator*(const Fixed &rhs) const;
	Fixed operator/(const Fixed &rhs) const;
	
	// Increment / Decrement
	Fixed &operator++(void); // pre-increment
	Fixed operator++(int); // post-increment
	Fixed &operator--(void); // pre-decrement
	Fixed operator--(int); // post-decrement

	// Min / Max
	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);
};

	std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
