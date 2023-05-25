#include "Point.h"

Point::Point(): _x(0), _y(0) {}
Point::Point(double x, double y) : _x(x), _y(y) {}
Point & Point::operator=( const Point & other ) {
    _x = other.x() ;
    _y = other.y() ;
    return *this ;
} // copy assignment constructor 

bool Point::operator==( const Point & other ) {
    if ( other.x() == this->x() && other.y() == this->y() )
        return true ;
    else
        return false ;
} // equal()

bool Point::operator!=( const Point & other ) {
    if ( other.x() != this->x() || other.y() != this->y() )
        return true ;
    else
        return false ;
} // equal()

bool Point::Point_equal(Point other) { 
    if ( other.x() == this->x() &&  other.y() == this->y() )
      return true ;
    else 
      return false ;
} // Point_equal()

double & Point::x() { return _x ; }
const double & Point::x() const { return _x ; } 
const double & Point::return_x() const { return _x ; } 
double & Point::y() { return _y ; }
const double & Point::y() const { return _y ; } 
const double & Point::return_y() const { return _y ; } 