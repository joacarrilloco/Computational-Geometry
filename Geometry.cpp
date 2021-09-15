#include<bits/stdc++.h>
using namespace std;
#define EPS 1e-8

const double PI = acos(-1.0);
struct Point
{
    double x,y;
    Point(double a = 0.0, double b = 0.0): x(a), y(b){};

    Point operator * (const double t ) const {
        return Point(x * t , y * t );
    }

    Point operator - (const Point other ) const {
        return Point(x - other.x , y - other.y );
    }

    Point operator + (const Point other ) const {
        return Point(x + other.x , y + other.y );
    }

    double operator % (const Point other ) const { // this operator return distance between two points
        return sqrt( ( x - other.x) * ( x - other.x)  + ( y - other.y) * ( y - other.y) );
    }

    bool operator == ( const Point other) const {
        return fabs( x - other.x ) < EPS && fabs( y - other.y ) < EPS;
    }

    bool operator < (const Point &other) const {
        if(fabs(x - other.x) > EPS) return x<other.x;
        return y<other.y;
    }

    double operator ^ ( const Point other) const { // cross product
        return x * other.y - y * other.x;
    }

    double operator * ( const Point other) const {// dot product
        return x * other.x + y * other.y;
    }

    Point operator << ( const double angle) const {// rotate point angle grades anti-clockwise
        return Point( x * cos( angle ) - y * sin( angle ), x * sin( angle ) + y * cos( angle ) );
    }

    Point operator || ( const double len) const {// scale length of this point
        double rt = len / sqrt( x * x + y * y );
        return Point ( x * rt , y * rt );
    }


    double getAngle ( Point other ){// from other to this

        double val = *this ^ other;
        if( val < 0 ) val = -1.0;
        else val = 1.0;
        double normC = other % Point(), normB = *this % Point();
        return val * acos( ( (*this % other) * (*this % other) - normC * normC - normB * normB) / ( -2.0 * normB * normC ));
    }

    void print( ){
        printf("%0.8f %0.8f\n", x, y);
    }

    void scan(){
        scanf("%lf%lf", &x, &y);
    }
};

struct Line
{
    double a, b, c;
    Line( double aa, double bb, double cc): a(aa), b(bb), c(cc){}
    Line(Point f, Point s): a(f.y-s.y), b(s.x-f.x), c(f.x*s.y-s.x*f.y){};//take care if are the same

    bool operator & (const Point t ) const { // checks if point t is inside the line
        return fabs(a * t.x + b * t.y + c) < EPS;
    }

    bool operator || (const Line &other) const { // checks if two lines are parallel 
        return fabs(a * other.b - other.a * b) < EPS;
    }

    bool operator == ( const Line &other ) const {

        return fabs(a * other.b - other.a * b) < EPS && fabs(b * other.c -  other.b * c) < EPS && fabs(a * other.c -  other.a * c)  < EPS;
    }

    double operator % ( const Point t) const {
        return fabs(a * t.x + b * t.y + c) / sqrt(a * a + b * b);
    }

    Point closset( Point p ) {
        Line l = Line(-b,a,-a * p.y + b * p.x );//perpendicular line that pass throught p
        Point ans;
        this->interscPoint(l, ans);
        return ans; 
    }
    bool interscPoint( Line other, Point &I){
        double det = a * other.b - other.a * b;
        if( fabs( det ) < EPS ) return false; // can be infinite

        I.y = (- a * other.c + c * other.a) / det;
        I.x = ( b * other.c  - c * other.b) / det;
        return true;
    }
};

struct Segment
{
    Point b, e;
    
    bool operator & (  const Point p ) const {
        if( (b == e) ) return p == b;
        return fabs( (e - b) ^ (p - b) ) < EPS && ( e - b ) * ( p - b ) > -EPS && ( b - e ) * ( p - e ) > -EPS;
    }
    
    bool segmentIntersection( Segment other, Point &p, Point &q){// if p == q, they intersect only in a Point

        Line l1 = Line( b, e ), l2 = Line( other.b, other.e );

        if( !l1.interscPoint(l2,p) ){

            Segment s1 = *this, s2 = other;
            for(int i = 0; i<2; i++){
                if( s2 & s1.b ){
                    p = q = s1.b;
                    if( s2 & s1.e && !( q == s1.e ) ) q = s1.e;
                    else if( s1 & s2.b && !( q == s2.b ) ) q = s2.b;
                    else if ( s1 & s2.e && !( q == s2.e ) ) q = s2.e;
                    return true;
                }else if( s2 & s1.e ){
                    p = q = s1.e;
                    if( s1 & s2.b && !( q == s2.b ) ) q = s2.b;
                    else if ( s1 & s2.e && !( q == s2.e ) ) q = s2.e;
                    return true;
                }
                swap( s1, s2 );
            }
            return false;  
        }
        q = p; 
        return ( *this & p ) && ( other & p );
    }
};

struct Circle
{
    Point center;
    double r;
    Circle(double xx = 0.0, double yy = 0.0, double rr = 0.0): center(Point(xx,yy)), r(rr) {}; 

    bool operator & ( const Point p ){
        return center % p <= r;
    }

    Circle(Point p, Point q, double rr){ // swap p,q for finding other center
        double dis = p % q;
        if( dis > 2 * rr ){
            center.x = center.y = r = -1.0;
            return;
        }
        Point ans = ( p + q ) * 0.5;
        Point dvec = Point( (q.y - p.y)/dis, (p.x - q.x)/dis); // perpendicular
        double len =  sqrt( rr * rr - 0.25 * dis * dis );
        ans = ans + dvec * len;
        center = Point(ans.x, ans.y), r = rr;
    }

    bool lineIntersection( Line l, Point &p, Point &q ){
        double dis = l % center;
        if( dis > r ) return false;
        Point piv = l.closset(center);
        p = piv + Point(-l.b, l.a) * ( sqrt( r * r - dis * dis )  / sqrt(l.b * l.b + l.a * l.a) );
        q = piv - Point(-l.b, l.a) * ( sqrt( r * r - dis * dis )  / sqrt(l.b * l.b + l.a * l.a) );
        return true;
    }

    bool CircunfernceIntersection( Circle other, Point &p, Point &q){// doesn't return any point if one cirlce is completely inside the other
        double dis = center % other.center;
        if( dis > r + other.r ) return false; // too far
        if( dis < fabs( r - other.r ) ) return false; // take care when they're the same
        double alpha = acos( (other.r * other. r - r * r - dis * dis) / ( -2.0 * r * dis ));
        p = ( other.center - center ) << (alpha);
        q = ( other.center - center ) << (-alpha);
        p = center + (p || r), q = center + (q || r);
        return true;
    }

};  


struct Triangle{

    Point A, B, C;
    
    double perimeter(){
        return A % B + B % C + C % A;
    }
    double area(){
        return fabs ( ( B - A ) ^ ( C - A )  ) / 2.0;
    } 

    bool Incircle(Circle &cir){
        double Ar = area();
        if( Ar < EPS ) return 0;
        double a = B % C, b = A % C, c = A % B;
        double p = a + b + c;
        cir.r = 2.0 * Ar / p;
        cir.center.x = a * A.x + b * B.x + c * C.x, cir.center.y = a * A.y + b * B.y + c * C.y;
        cir.center.x /= p, cir.center.y /= p;
        return 1;
    }
};

vector<Point> ConvexH(vector<Point> P){
    
    if(P.size()<3) return P;
    sort(P.begin(),P.end());
    vector<Point> H (2*P.size());

    int k = 0;
    for(int i = 0; i<P.size(); i++){
        while(k>=2&&(( H[k-1] - H[k-2] ) ^ ( P[i] - H[k-2] ))<= 0) k--; 
        H[k++] = P[i];
    }

    int t = k + 1;
    for(int i = P.size()-2; i>=0; i--){
        while(k>=t&&(( H[k-1] - H[k-2] ) ^ ( P[i] - H[k-2] ))<= 0) k--; 
        H[k++] = P[i];
    }

    H.resize(k-1);
    return H;
}

enum {IN,OUT,ON};

int point_in_polygon( vector< pt > &pol, pt &p )
{
  int wn = 0;
  for( int i = 0, n = pol.size(); i < n; ++ i )
  {
    long long c = orient( p, pol[i], pol[(i+1)%n] );
    if( c == 0 && dot( pol[i] - p, pol[(i+1)%n] - p ) <= 0 ) return ON; 
    if( c > 0 && pol[i].y <= p.y && pol[(i+1)%n].y > p.y ) ++ wn;
    if( c < 0 && pol[(i+1)%n].y <= p.y && pol[i].y > p.y ) --wn;
  }
  return wn ? IN : OUT;
}

bool insideConvexPol( vector < pt > &pol, pt &p ){
    int low = 1, high = pol.size() - 1;
    while( high - low > 1 ){
        int mid = ( high + low ) / 2;
        if( orient( pol[0], pol[mid], p ) >= 0 ) low = mid;
        else high = mid;
    }
    if( orient( pol[0], pol[low], p ) < 0 ) return false;
    if( orient( pol[low], pol[high], p ) < 0 ) return false;
    if( orient( pol[high], pol[0], p ) < 0 ) return false;
    return true;    
}

lf areaOfIntersectionOfTwoCircles( lf r1, lf r2, lf d )
{
  if( d >= r1 + r2 )
    return 0.0L;

  if( d <= fabsl( r2 - r1 ) )
    return PI * ( r1 < r2 ? r1 * r1 : r2 * r2 );

  lf alpha = safeAcos( ( r1 * r1 - r2 * r2 + d * d ) / ( 2.0L * d * r1 ) );
  lf betha = safeAcos( ( r2 * r2 - r1 * r1 + d * d ) / ( 2.0L * d * r2 ) );

  lf a1 = r1 * r1 * ( alpha - sinl( alpha ) * cosl( alpha ) );
  lf a2 = r2 * r2 * ( betha - sinl( betha ) * cosl( betha ) );

  return a1 + a2;
};

int main()
{
    return 0;
}
