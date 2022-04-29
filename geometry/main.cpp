#include "Point2D.cpp"
#include <iostream>

int main()
{
	geometry::Point2D a( 3.5, 3.5 ), b( 4.0, 4.0 );
	std::cout << geometry::computeDistance( a, b ) << std::endl;
	return 0;
}
