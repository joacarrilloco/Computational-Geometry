struct pt
{
    lf x,y;
    pt(){}
    pt(lf a , lf b): x(a), y(b){}

    pt operator - (const pt &q ) const {
        return {x - q.x , y - q.y };
    }

    pt operator + (const pt &q ) const {
        return {x + q.x , y + q.y };
    }

    pt operator * (const lf &t ) const {
        return {x * t , y * t };
    }

};


inline lf norm2 ( pt p ) { return p.x * p.x + p.y * p.y; }
inline ll dis2 ( pt p, pt q ) { return norm2(p-q); }

inline lf norm ( pt p ) { return hypot ( p.x, p.y ); }
inline lf dis( pt p, pt q ) { return norm( p - q ); }

inline lf dot( pt p, pt q ) { return p.x * q.x + p.y * p.y; }
inline lf cross( pt p, pt q ) { return p.x * q.y - q.x * p.y ; }


//check
pt closestInLine ( pt &a, pt &b, pt &p ){
	double t = dot ( b - a, p - a ) / norm2( b - a );
	return a + ( b - a ) * t;
}


//check
double disToLine ( pt &a, pt &b, pt &p ){
	pt q = closestInLine( a, b, p );
	return dis( p, q );
}


//check
pt linesIntersection (pt &a, pt &b, pt &c, pt &d) {
    lf t = cross( a, b - a ) - cross ( c, b - a );
    t /= cross ( c - d , b - a );
    return a + (b - a) * t;
}


vector < pt > convexHull( vector < pt > a ){

    if( a.size() < 3 ) return a;    
    sort( a.begin(), a.end() );

    vector<pt> ch ( 2 * a.size() );

    int k = 0, t = 2;

    for( int it = 0; it < 2; it++ ){
        for( pt &p : a ){
            while( k>=t && cross( ch[k-1] - ch[k-2], p - ch[k-2] ) <= 0 ) k--;
            ch[k++] = p; 
        }
        reverse(a.begin(), a.end()); 
        t = k + 1;
    }
    ch.resize(k-1);
    return ch;
}

//closest pair n*log(n), first sort arr by x, INF ~~ 2e9 + 1 ;)
pt arr[N], lt[N], rt[N];

pair < pt, pt >  closest ( int l, int r ){

    if( r == l ) return { {INF,0}, {0,INF} };

    int mid = ( l + r ) / 2, xmid = arr[mid].x;

    pair < pt, pt > ans = closest( l, mid ); 
    pair < pt, pt > ra = closest( mid + 1, r );

    ll d = dis2( ans.first, ans.second);
    ll dr = dis2( ra.first, ra.second );

    if( dr < d ) d = dr, ans = ra;

    for( int i = l; i<=mid; i ++ ) lt[i - l] = arr[i]; 
    for( int i = mid + 1; i<=r; i ++ ) rt[i - mid - 1] = arr[i]; 

    int it1 = 0, it2 = 0;

    while ( it1 <= mid - l && it2 < r - mid ){
        if( lt[it1].y < rt[it2].y ) arr[l+it1+it2] = lt[it1++];
        else arr[l+it1+it2] = rt[it2++];
    } 

    while( it1 <= mid - l ) arr[l+it1+it2] = lt[it1++];
    while( it2 < r - mid ) arr[l+it1+it2] = rt[it2++];

    vector < pt > v;

    for( int i = l; i<=r; i++ ){
        ll aux = (ll) ( xmid - arr[i].x ) * ( xmid - arr[i].x );
        if( aux < d ) v.push_back( arr[i] );
    }

    for( int i = 0; i<v.size(); i++ ){
        for( int k = i + 1; k<v.size(); k++ ){
            ll aux = (ll) (v[i].y - v[k].y) * (v[i].y - v[k].y);
            if( aux > d ) break;
            ll nd = dis2( v[i], v[k] );
            if( nd < d ) d = nd, ans = {v[i], v[k]};
        }
    }
    return ans;
}


bool insideConvecPol( vector < pt > &pol, pt p ){
    int low = 1, high = pol.size() - 1;
    while( high - low > 1 ){
        int mid = ( high + low ) / 2;
        if( cross( pol[mid] - pol[0] , p - pol[0] ) >= 0 ) low = mid;
        else high = mid;
    }
    if( cross( pol[low] - pol[0] , p - pol[0] ) < 0 ) return false;
    if( cross( pol[high] - pol[low] , p - pol[low] ) < 0 ) return false;
    if( cross( pol[0] - pol[high] , p - pol[high] ) < 0 ) return false;
    return true;    
}