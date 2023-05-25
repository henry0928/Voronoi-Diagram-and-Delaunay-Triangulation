#ifndef _SEG_H_
#define _SEG_H_
#include "Point.h"
#include <vector>
// #include "Class_def.h"

class Seg {
  Point _start ;
  Point _end ;
  
  public:
    bool done ;

    Seg() ;
    Seg(Point p) ;
    Seg(Point p1, Point p2) ;
    Seg & operator=( const Seg & other ) ; 
    bool Seg_equal( Seg other ) ;
    const Point & start() const ;
    Point & start() ;
    const Point & return_start() const ;
    const Point & end() const ;
    Point & end() ;
    const Point & return_end() const ;
    void finish(Point p, std::vector<Seg> & vec) ;
} ;

#endif