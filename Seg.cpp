#include "Seg.h"
#include <vector>

Seg::Seg(): _start(Point()), _end(Point()), done(0) {}
Seg::Seg(Point p) : _start(p), _end(Point()), done(0) {}
Seg::Seg(Point p1, Point p2) : _start(p1), _end(p2), done(0) {}

Seg & Seg::operator=( const Seg & other ) {
    _start =  other.start() ;
    _end = other.end() ;
    done = false ;
    return *this ;
} // copy assignment constructor 

bool Seg::Seg_equal( Seg other ) {
  if ( other.start().Point_equal(this->start()) && other.end().Point_equal(this->end()) )
    return true ;

  return false ; 
} // Seg_equal()

const Point & Seg::start() const { return _start ;}
Point & Seg::start() { return _start ;}
const Point & Seg::return_start() const { return _start ;}
const Point & Seg::end() const { return _end ;}
Point & Seg::end() { return _end ;}
const Point & Seg::return_end() const { return _end ;}
void Seg::finish(Point p, std::vector<Seg> & vec) {
    _end = p ;
    done = true ;
    vec.push_back(*this) ;
} // finish()