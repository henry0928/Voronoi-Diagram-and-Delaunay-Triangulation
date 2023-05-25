#ifndef _POINT_H_
#define _POINT_H_

class Point {
  double _x ;
  double _y ;

  public:
    Point() ;
    Point(double x, double y) ;
    Point & operator=( const Point & other ) ;
    bool operator==( const Point & other ) ;
    bool operator!=( const Point & other ) ;
    bool Point_equal(Point other) ;
    double & x() ;
    const double & x() const ;
    const double & return_x() const ;
    double & y() ;
    const double & y() const ;
    const double & return_y() const ;
};

#endif