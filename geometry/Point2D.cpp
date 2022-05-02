#include "Point2D.h"
#include <cmath>

namespace geometry
{
	template<typename T>
	double computeDistance( const Point2D<T> &p, const Point2D<T> &q )
	{
		return sqrt( ( p.x - q.x ) * ( p.x - q.x ) + ( p.y - q.y ) * ( p.y - q.y ) );
	}

	template<typename T>
	T crossProduct( const Point2D<T> &p, const Point2D<T> &q )
	{
		return p.x * q.y - p.y * q.x;
	}

	template<typename T>
	T dotProduct( const Point2D<T> &p, const Point2D<T> &q )
	{
		return p.x * q.x + p.y * q.y;
	}

	template<typename T>
	Point2D<T> Point2D<T>::operator + ( const Point2D<T> &p ) const
	{
		return Point2D<T>( x + p.x, y + p.y );
	}

	template<typename T>
	Point2D<T> Point2D<T>::operator - ( const Point2D<T> &p ) const
	{
		return Point2D<T>( x - p.x, y - p.y );
	}

	template<typename T>
	double Point2D<T>::getNorm() const
	{
		return sqrt( x * x + y * y );
	}
};

