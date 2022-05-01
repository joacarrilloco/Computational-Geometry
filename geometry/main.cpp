#include "Point2D.cpp"
#include <iostream>

int main()
{
	{ //default T = double
		geometry::Point2D a( 3.5, 1.5 ), b( 4.0, 2.0 );
		std::cout << geometry::computeDistance( a, b ) << std::endl;

		geometry::Point2D c = a + b;
		std::cout << c.x << " " << c.y << std::endl;
		std::cout << c.getNorm() << std::endl;
	}

	{ //non-default T = int
		geometry::Point2D<int> a( 3, 1 ), b( 4, 2 );
		std::cout << geometry::computeDistance( a, b ) << std::endl;

		auto c = a + b;
		std::cout << c.x << " " << c.y << std::endl;
		std::cout << c.getNorm() << std::endl;
	}

	return 0;
}
