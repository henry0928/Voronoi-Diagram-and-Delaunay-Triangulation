#include "Point.h"
#include "Seg.h"
#include "Arc_Event.h"
#include <string>

Arc::Arc() : _site(Point()), _left(Seg()), _right(Seg()), prev(NULL), next(NULL), event(NULL) {}
Arc::Arc(Point p, Seg s1, Seg s2) : _site(p), _left(s1), _right(s2), prev(NULL), next(NULL), event(NULL) {}
Arc & Arc::operator=( const Arc & other ) {
    _site =  other.site() ;
    _left = other.left_seg() ;
    _right = other.right_seg() ;
    prev = other.prev ;
    next = other.next ;
    event = other.event ;
    return *this ;
} // copy assignment constructor  
Point & Arc::site() { return _site ; }
const Point Arc::site() const { return _site ; }
Seg & Arc::left_seg() { return _left; }
const Seg & Arc::left_seg() const { return _left ; }
Seg & Arc::right_seg() { return _right ; }
const Seg & Arc::right_seg() const { return _right ; } 


Event::Event() : _pos(Point()),_circle_centre(Point()),_valid(0), arc(NULL) {}
Point & Event::pos() {return _pos ;}
const Point Event::pos() const {return _pos ;}
std::string & Event::type() {return _type ;}
const std::string Event::type() const {return _type ;} 
Point & Event::circle_centre() {return _circle_centre ;} 
const Point Event::circle_centre() const {return _circle_centre ;}
bool & Event::valid() {return _valid ;} 
const bool Event::valid() const {return _valid ;}

