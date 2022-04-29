#include "Point2D.h"
#include <cmath>

namespace geometry
{
	template<typename T>
	double computeDistance( const Point2D<T> &p, const Point2D<T> &q )
	{
		return sqrt( ( p.x - q.x ) * ( p.x - q.x ) + ( p.y - q.x ) * ( p.x - q.y ) );
	}
};
