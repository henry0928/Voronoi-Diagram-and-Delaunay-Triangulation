#include <iostream> 
#include <vector>
#include <queue>
#include <math.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std ;
class Point ;
class Seg ;
class Arg ;
class Event ;


class Point {
  private:
    double _x ;
    double _y ;

  public:
    Point(): _x(0), _y(0) {}
    Point(double x, double y) : _x(x), _y(y) {}
    Point & operator=( const Point & other ) {
      _x = other.x() ;
      _y = other.y() ;
      return *this ;
    } // copy assignment constructor 
    bool operator==( const Point & other ) {
      if ( other.x() == this->x() && other.y() == this->y() )
        return true ;
      else
        return false ;
    } // equal()
    double & x() { return _x ; }
    const double & x() const { return _x ; } 
    const double & return_x() const { return _x ; } 
    double & y() { return _y ; }
    const double & y() const { return _y ; } 
    const double & return_y() const { return _y ; } 
}; 

class Seg {
  private:
    Point _start ;
    Point _end ;
  
  public:
    bool done ;

    Seg(): _start(Point()), _end(Point()), done(0) {}
    Seg(Point p) : _start(p), _end(Point()), done(0) {} 
    // Seg(Seg other) : _start(other.start()), _end(other.end()), done(0) {}
    Seg & operator=( const Seg & other ) {
      _start =  other.start() ;
      _end = other.end() ;
      done = false ;
      return *this ;
    } // copy assignment constructor  
    const Point & start() const { return _start ;}
    Point & start() { return _start ;}
    const Point & return_start() const { return _start ;}
    const Point & end() const { return _end ;}
    Point & end() { return _end ;}
    const Point & return_end() const { return _end ;}
    void finish(Point p, vector<Seg> & vec) {
      _end = p ;
      done = true ;
      vec.push_back(*this) ;
    } // finish()

} ; 

class Arc {
  private:
    Point _site ;
    Seg _left ;
    Seg _right ;

  public:
    Event* event ;
    Arc* prev ;
    Arc* next ;
    
    Arc() : _site(Point()), _left(Seg()), _right(Seg()), prev(NULL), next(NULL), event(NULL) {}
    Arc & operator=( const Arc & other ) {
      _site =  other.site() ;
      _left = other.left_seg() ;
      _right = other.right_seg() ;
      prev = other.prev ;
      next = other.next ;
      event = other.event ;
      return *this ;
    } // copy assignment constructor  
    Point & site() { return _site ; }
    const Point site() const { return _site ; }
    Seg & left_seg() { return _left; }
    const Seg & left_seg() const { return _left ; }
    Seg & right_seg() { return _right ; }
    const Seg & right_seg() const { return _right ; } 
}; 

class Event {
  private:
    Point _pos ;
    string _type ;
    Point _circle_centre ;
    bool _valid ;
  
  public:
    Arc * arc ;

    Event() : _pos(Point()),_circle_centre(Point()),_valid(0), arc(NULL) {}
    Point & pos() {return _pos ;}
    const Point pos() const {return _pos ;}
    string & type() {return _type ;}
    const string type() const {return _type ;} 
    Point & circle_centre() {return _circle_centre ;} 
    const Point circle_centre() const {return _circle_centre ;}
    bool & valid() {return _valid ;} 
    const bool valid() const {return _valid ;}

};

struct adjacent_info {
  Point p1 ;
  Point p2 ;
  Point p3 ;
  Point centre ;
  bool valid ;
  bool third ;
};