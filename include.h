#include <iostream> 
#include <vector>
#include <queue>
#include <math.h>
#include "Point.h"
#include "Seg.h"
#include "Arc_Event.h"
#include "Draw_color.h"

using namespace std ;

struct adjacent_info {
  Point p1 ;
  Point p2 ;
  Point p3 ;
  Point centre ;
  bool valid ;
  bool third ;
};

struct delaunay_circle_event {
  Arc * arc ;
  Point circle_centre ;
};