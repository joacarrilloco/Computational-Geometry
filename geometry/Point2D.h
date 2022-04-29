#ifndef POINT2D_H
#define POINT2D_H

namespace geometry
{
	template< typename T = double>
	class Point2D
	{
		public:
			Point2D( const T &_x, const T &_y ) : x ( _x ), y ( _y ) {};
		public:
			T x, y;
	};
}
#endif
