#ifndef _ARC_H_
#define _ARC_H_
#include "Point.h"
#include "Seg.h"
#include <string>

class Arc ;
class Event ;

class Arc {
  Point _site ;
  Seg _left ;
  Seg _right ;

  public:
    //delaunay_circle_event* dcc_event ; // since have too many same name!
    Event* event ;
    Arc* prev ;
    Arc* next ;
    
    Arc() ;
    Arc(Point p, Seg s1, Seg s2) ;
    Arc & operator=( const Arc & other ) ;
    Point & site() ;
    const Point site() const ;
    Seg & left_seg() ;
    const Seg & left_seg() const ;
    Seg & right_seg() ;
    const Seg & right_seg() const ; 
};

class Event {

  Point _pos ;
  std::string _type ;
  Point _circle_centre ;
  bool _valid ;
  
  public:
    Arc * arc ;

    Event() ;
    Point & pos() ;
    const Point pos() const ;
    std::string & type() ;
    const std::string type() const ;
    Point & circle_centre() ;
    const Point circle_centre() const ;
    bool & valid() ; 
    const bool valid() const ;

};

#endif