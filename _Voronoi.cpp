#include "include.h"
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

class Voronoi {
  private:
    vector<Event> Event_queue ;  // voronoi diagram event_queue  
    vector<Seg> Output ; // voronoi diagram Output vector
    vector<Point> invalid_circle ; // to discard invalid circle
    vector<Seg> answer ; // for after fix Output vector
    vector<adjacent_info> adj_list ; // for record adjacent infomation
    vector<Seg> delaunay_edge ;
    vector<delaunay_circle_event> dc_event ; // for record delaunay circle event
    vector<Point> voronoi_cell ;
    Arc * root ; // This is beachline head pointer
    Point bbox_ld ;
    Point bbox_ru ;
    //vector<Point> site_list ;

  public:
    Voronoi() :root(NULL) {} 

    vector<Seg> Create_voronoi( vector<Point> site_list, Point bb_point1, Point bb_point2 ) {
      Event_queue.clear() ;
      Output.clear() ;
      invalid_circle.clear() ;
      answer.clear() ;
      adj_list.clear() ;
      delaunay_edge.clear() ;
      voronoi_cell.clear() ;
      root = NULL ;
      Event temp ;
      for( size_t i = 0 ; i < site_list.size() ; i++ ) {
        temp.pos() = site_list[i] ;
        temp.type() = "site" ;
        Event_queue.push_back(temp) ;
      } // for 

      // Initialize bbox points 
      bbox_ld = bb_point1 ;
      bbox_ru = bb_point2 ;  

      // execute Fortune algorithm
      Fortune() ;
      modify_edge() ; 

      for ( size_t i = 0 ; i < Output.size() ; i++ ) {
        if ( Output[i].done == true )
          answer.push_back(Output[i]) ;
      } // for

      // debug_output() ;
      return answer ;

    } // Create_voronoi()

    void Fortune() {
      size_t delete_index = 0 ;
      Event now_event ;
      while( Event_queue.size() != 0 ) {
        now_event = que_pop(delete_index) ;
        Event_queue.erase(Event_queue.begin() + delete_index) ;
        if ( now_event.type() == "site" )
          handle_site(now_event) ;
        else
          handle_circle(now_event) ;
      } // while

      finish_edges() ;
    } // Fortune()
    
    Event que_pop( size_t & index ) {
      double y_temp = -1000 ;
      double x_temp = -1000 ;
      for ( size_t i = 0 ; i < Event_queue.size() ; i++ ) {
        if ( Event_queue[i].pos().y() >= y_temp ) {
          if ( Event_queue[i].pos().y() == y_temp ) {
            if ( Event_queue[i].pos().x() < x_temp ) {
              index = i ; 
              x_temp = Event_queue[i].pos().x() ;
              y_temp = Event_queue[i].pos().y() ;
            } // if 
          } // if 
          else {
            index = i ; 
            x_temp = Event_queue[i].pos().x() ;
            y_temp = Event_queue[i].pos().y() ;
          } // else 
        } // if   
      } // for

      return Event_queue[index] ;
    } // que_pop()

    void handle_site( Event n_event ) {
      //site_list.push_back(n_event.pos()) ;
      Point interset_point ;
      Point zz ;
      Point start ;
      Arc * arc_ptr ;
      Seg * seg_ptr ;
      if ( root == NULL ) {
        root = new Arc() ;
        root->site() = n_event.pos() ;
        //cout << "success create root" << endl ;
        return ;
      } // if
      else {
        for ( Arc*temp = root ; temp ; temp = temp->next ) {
          if ( intersect( n_event.pos(), temp, interset_point) == true ) {
            // duplicate the temp arc to temp->next
            arc_ptr = new Arc() ;
            arc_ptr->site() = temp->site() ;
            arc_ptr->prev = temp ;
            if (temp->next) {
              arc_ptr->next = temp->next ;
              temp->next = arc_ptr ;
              arc_ptr->next->prev = arc_ptr ;
            } // if   
            else { 
              arc_ptr->next = NULL ;
              temp->next = arc_ptr ; 
            } // else
            
            temp->next->right_seg() = temp->right_seg() ; // To replace the seg !
            
            // Put the new arc into beachline
            arc_ptr = new Arc() ;
            arc_ptr->site() = n_event.pos() ;
            // Create a seg for new arc to copy by it 
            seg_ptr = new Seg(interset_point) ;
            arc_ptr->left_seg() = *seg_ptr  ;
            arc_ptr->right_seg() = *seg_ptr ;
            // To prevent memory leak 
            delete seg_ptr ;
            // Put new arc into beachline
            arc_ptr->next = temp->next ; 
            arc_ptr->prev = temp ; 
            temp->next = arc_ptr ; 
            arc_ptr->next->prev = arc_ptr ; 
            temp = temp->next ; //  NOW temp point to the new arc
            // Setup the both side seg
            temp->prev->right_seg() = temp->left_seg() ;
            temp->next->left_seg() = temp->right_seg() ;

            // TODO: check circle event
            checkcircle(temp, n_event.pos().y()) ;
            checkcircle(temp->prev, n_event.pos().y()) ;
            // checkcircle(temp, n_event.pos().y()) ;
            checkcircle(temp->next, n_event.pos().y()) ;
            return ;
          } // if 
        } // for
        
        //cout << "There is a special case!" << endl ;

        // Append to the rightmost
        Arc * rightmost = root ;
        while ( rightmost->next != NULL )
          rightmost = rightmost->next ;
        arc_ptr = new Arc() ;
        arc_ptr->site() = n_event.pos() ;
        arc_ptr->prev = rightmost ; 
        rightmost->next = arc_ptr ;

        // Set the seg
        start.x() = (rightmost->site().x() + rightmost->next->site().x())  / 2 ;
        start.y() = bbox_ru.y() ; // Need to modify  
        seg_ptr = new Seg(start) ;
        rightmost->right_seg() = *seg_ptr ;
        rightmost->next->left_seg() = *seg_ptr ;
        delete seg_ptr ; 
        return ;
      } // else

    } // handle_site()

    bool intersect( Point new_site, Arc * arc, Point & res_point ) {
      double check_point_x1 ;
      double check_point_x2 ;
      if ( arc->site().y() == new_site.y() )
        return false ; // There will not have intersection! 
      if (arc->prev)
        check_point_x1 = intersection(arc->prev->site(), arc->site(), new_site.y()).x() ;
      if (arc->next)
        check_point_x2 = intersection(arc->site(), arc->next->site(), new_site.y()).x() ;

      if (( !arc->prev || check_point_x1 < new_site.x() ) && ( !arc->next || check_point_x2 > new_site.x() )) {
        //cout << "There is an intersect point!" << endl ;
        res_point.x() = new_site.x() ;
        double t = res_point.x() - arc->site().x() ; // just for convinence
        res_point.y() = (1 / ( 2 * (arc->site().y() - new_site.y()))) * (t * t) 
                        + ((arc->site().y() + new_site.y()) / 2) ; 
        //print_point(res_point, "intersection point:") ;
        return true;
      } // if 
      else {
        //print_point(arc->site(), "need to be false") ;
        return false ;
      } // else   
      
      return false ;
    } // intersect()

    Point intersection(Point p0, Point p1, double l) {
      Point res, p = p0;

      double z0 = 2*(p0.y() - l);
      double z1 = 2*(p1.y() - l);

      if (p0.y() == p1.y())
        res.x() = (p0.x() + p1.x()) / 2;
      else if (p1.y() == l)
        res.x() = p1.x();
      else if (p0.y() == l) {
        res.x() = p0.x();
        p = p1; // arc is a line
      } // else if 
      else {
        // Use the quadratic formula.
        double a = 1/z0 - 1/z1;
        //double b = -2*(p0.y/z0 - p1.y/z1);
        double b = -2*(p0.x()/z0 - p1.x()/z1);
        // double c = (p0.y*p0.y + p0.x*p0.x - l*l)/z0
        //          - (p1.y*p1.y + p1.x*p1.x - l*l)/z1;
        double c = (p0.y()*p0.y() + p0.x()*p0.x() - l*l)/z0
                    - (p1.y()*p1.y() + p1.x()*p1.x() - l*l)/z1;
        //res.y = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);
        res.x() = ( -b + sqrt(b*b - 4*a*c) ) / (2*a);
      } // else

      //res.x = (p.x*p.x + (p.y-res.y)*(p.y-res.y) - l*l)/(2*p.x-2*l);
      res.y() = (p.y()*p.y() + (p.x()-res.x())*(p.x()-res.x()) - l*l)/(2*p.y()-2*l);
      return res;
    } // intersection()

    void handle_circle(Event n_event) {
      if ( check_invalid_circle(n_event.circle_centre()) ) {
        return ;
      } // if 
      voronoi_cell.push_back(n_event.circle_centre()) ;
      // Remove the arc from the beachline
      Arc * rm_ptr = n_event.arc ;
      rm_ptr->prev->next = rm_ptr->next ;
      rm_ptr->next->prev = rm_ptr->prev ;

      // Set left and right seg
      rm_ptr->left_seg().finish(n_event.circle_centre(), Output) ;
      rm_ptr->right_seg().finish(n_event.circle_centre(), Output) ;

      // To recover remain arc's left and right seg
      Seg * temp_seg = new Seg(n_event.circle_centre()) ;
      rm_ptr->prev->right_seg() = *temp_seg ;
      rm_ptr->next->left_seg() = *temp_seg ;
      delete temp_seg ;

      // Check another circle event
      checkcircle(rm_ptr->prev, n_event.pos().y()) ;
      checkcircle(rm_ptr->next, n_event.pos().y()) ;

      // To prevent memory leak
      //delete rm_ptr ; 

    } // handle_circle()

    void checkcircle(Arc * arc, double beachline) {
      if ( arc->event && arc->event->pos().y() != beachline ) {
          invalid_circle.push_back(arc->event->circle_centre()) ;
          // arc->event->valid() = false;
      } // if    
      arc->event = NULL;

      if ( !arc->prev || !arc->next )
        return ;
      if ( arc->prev == arc->next )
        return ;
      
      Point p1 = arc->prev->site() ;
      Point p2 = arc->site() ;
      Point p3 = arc->next->site() ;
      Point center ;
      double y31 = p3.y() - p1.y() ;
      double x23 = p2.x() - p3.x() ;
      double y23 = p2.y() - p3.y() ;
      double x31 = p3.x() - p1.x() ; 
      if ( (y23 * x31) - (y31 * x23) <= 0 ) {
        return ; // Points in a line
      } // if 
      
      double radius = findcircle(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), center) ;

      if ( (center.y() - radius) <= beachline && (center.y() - radius) >= bbox_ld.y()) {
        // There is a circle event!
        Event * event = new Event() ;
        adjacent_info temp ;
        event->pos().x() = 0 ; // Useless, won't use at circle event 
        //cout << "check this number:" << center.y() - radius << endl ;
        event->pos().y() = center.y() - radius ;
        event->arc = arc ;
        event->type() = "circle" ;
        event->circle_centre() = center ;
        event->valid() = true ;
        arc->event = event ;

        // to record adjacent_info
        temp.p1 = p1 ;
        temp.p2 = p2 ;
        temp.p3 = p3 ;
        temp.centre = center ;
        temp.valid = true ;
        temp.third = true ;
        adj_list.push_back(temp) ;
        
        Event_queue.push_back(*event) ;
      } // if

      return ;
    } // checkcircle()

    double findcircle(double x1, double y1, double x2, double y2, double x3, double y3, Point & centre) {
        double x12 = x1 - x2;
        double x13 = x1 - x3;
    
        double y12 = y1 - y2;
        double y13 = y1 - y3;
    
        double y31 = y3 - y1;
        double y21 = y2 - y1;
    
        double x31 = x3 - x1;
        double x21 = x2 - x1;
    
        // x1^2 - x3^2
        double sx13 = pow(x1, 2) - pow(x3, 2);
    
        // y1^2 - y3^2
        double sy13 = pow(y1, 2) - pow(y3, 2);
    
        double sx21 = pow(x2, 2) - pow(x1, 2);
        double sy21 = pow(y2, 2) - pow(y1, 2);
    
        double f = ((sx13) * (x12)
                + (sy13) * (x12)
                + (sx21) * (x13)
                + (sy21) * (x13))
                / (2 * ((y31) * (x12) - (y21) * (x13)));
        double g = ((sx13) * (y12)
                + (sy13) * (y12)
                + (sx21) * (y13)
                + (sy21) * (y13))
                / (2 * ((x31) * (y12) - (x21) * (y13)));
    
        double c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;
    
        // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0
        // where centre is (h = -g, k = -f) and radius r
        // as r^2 = h^2 + k^2 - c
        double h = -g;
        double k = -f;
        double sqr_of_r = h * h + k * k - c;
        // Set the centre point 
        centre.x() = h ;
        centre.y() = k ;
        //print_point(centre, "circle") ;
        // r is the radius
        double r = sqrt(sqr_of_r);
        return r ;

    } // findcircle()

    bool check_invalid_circle(Point p1) {
      for ( size_t i = 0 ; i < invalid_circle.size() ; i++ ) {
        if ( invalid_circle[i] == p1 )
          return true ;
      } // for

      return false ; 

    } // check_invalid_circle()

    void find_rest_cricle(Arc * arc, double beachline) {
      delaunay_circle_event dc_e ; 
      // arc->event = NULL;

      if ( !arc->prev || !arc->next )
        return ;
      if ( arc->prev == arc->next )
        return ;
      
      Point p1 = arc->prev->site() ;
      Point p2 = arc->site() ;
      Point p3 = arc->next->site() ;
      Point center ;
      double y31 = p3.y() - p1.y() ;
      double x23 = p2.x() - p3.x() ;
      double y23 = p2.y() - p3.y() ;
      double x31 = p3.x() - p1.x() ; 
      if ( (y23 * x31) - (y31 * x23) <= 0 ) {
        return ; // Points in a line
      } // if 
      
      findcircle(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), center) ;
      if ( center.y() >= 0 && center.x() >= 0 )  {
        voronoi_cell.push_back(center) ;
        arc->next->prev = arc->prev ;
        arc->prev->next = arc->next ;
        if ( arc->left_seg().done == false )
          arc->left_seg().finish(center, Output) ;
        if ( arc->right_seg().done == false )
          arc->right_seg().finish(center, Output) ;

        // To recover remain arc's left and right seg
        Seg * temp_seg = new Seg(center) ;
        arc->prev->right_seg() = *temp_seg ;
        arc->next->left_seg() = *temp_seg ;
        delete temp_seg ;
      } // if


      dc_e.arc = arc ;
      dc_e.circle_centre = center ;
      dc_event.push_back(dc_e) ;

    } // find_rest_cricle()

    void deal_dc_event() {
      size_t index = 0 ;
      while ( dc_event.size() != 0 ) {
        index = dc_pop() ;
        handle_dc_event(dc_event[index]) ;
        dc_event.erase(dc_event.begin()+index) ;
      } // while 
      
    } // deal_dc_event()

    size_t dc_pop() {
      double temp = -10000 ;
      size_t _index = 0 ;
      for ( size_t i = 0 ; i < dc_event.size() ; i++ ) {
        if ( temp < dc_event[i].circle_centre.y() ) {
          temp = dc_event[i].circle_centre.y() ;
          _index = i ;
        } // if 
      } // for 

      return _index ;
    } // dc_pop()

    void handle_dc_event(delaunay_circle_event e) {
      // to record adjacent_info
      adjacent_info temp ;
      temp.p1 = e.arc->prev->site() ;
      temp.p2 = e.arc->site();
      temp.p3 = e.arc->next->site();
      temp.centre = e.circle_centre ;
      temp.valid = true ;
      temp.third = true ;
      adj_list.push_back(temp) ;
      e.arc->next->prev = e.arc->prev ;
      e.arc->prev->next = e.arc->next ;
      find_rest_cricle(e.arc->prev, -(bbox_ru.y() / 4)) ;
      find_rest_cricle(e.arc->next, -(bbox_ru.y() / 4)) ;
    } // handle_dc_event()

    void finish_edges() {
      // Advance the sweep line so no parabolas can cross the bounding box.
      double beachline = bbox_ru.y() ; 

      // Extend each remaining segment to the new parabola intersections.
      for (Arc *i = root ; i->next ; i = i->next) {
          find_rest_cricle(i,-(bbox_ru.y() / 4)) ;
          // if (i->right_seg().done == false && i->site() != i->next->site() ) { 
          //   i->right_seg().finish(intersection(i->site(), i->next->site(), -beachline), Output);
          // } // if 
      } // for 
      for (Arc *j = root ; j->next ; j = j->next) {
        if (j->right_seg().done == false && j->site() != j->next->site() ) { 
          j->right_seg().finish(intersection(j->site(), j->next->site(), -beachline), Output);
        } // if 
      } // for 
      
    } // finish_edge()

    void modify_edge() {
      Point new_start ;
      Point new_end ;
      Point reserve_point ;
      int type_num = 0 ; 
      bool is_reserve = false ;
      vector<size_t> vec ;
      size_t i ; 
      for ( i = 0 ; i < Output.size() ; i++ ) {
        if ( Output[i].start().x() > bbox_ru.x() || Output[i].start().x() < bbox_ld.x()
            || Output[i].start().y() > bbox_ru.y() || Output[i].start().y() < bbox_ld.y()
            || Output[i].end().x() > bbox_ru.x() || Output[i].end().x() < bbox_ld.x()
            || Output[i].end().y() > bbox_ru.y() || Output[i].end().y() < bbox_ld.y() ) {
          // TODO origin fit point don't need to change!
          is_reserve = reserve(Output[i].start(), Output[i].end(), reserve_point, type_num) ; 
          if ( reset_seg(Output[i].start(), Output[i].end(), new_start, new_end) ) {
            Output[i].start() = new_start ;
            Output[i].end() = new_end ;
            if ( is_reserve ) {
              // print_point(reserve_point, "reserve:") ;
              if ( type_num == 1 )
                Output[i].start() = reserve_point ;
              else if ( type_num == 2 )
                Output[i].end() = reserve_point ;
              else 
                ;
            } // if 
              
          } // if 
          else 
            Output[i].done = false ;
        } // if 
      } // for 

    } // modify_edge()

    bool reserve(Point start, Point end, Point & p1, int & type) {
      if ( start.x() <= bbox_ru.x() && start.x() >= bbox_ld.x() 
          && start.y() <= bbox_ru.y() && start.y() >= bbox_ld.y() ) {
        p1 = start ;
        type = 1 ;
        return true ;
      } // if 
      else if ( end.x() <= bbox_ru.x() && end.x() >= bbox_ld.x() 
                && end.y() <= bbox_ru.y() && end.y() >= bbox_ld.y() ) {
        p1 = end ;
        type = 2 ;
        return true ;
      } // else if   
      else 
        return false ;
    } // reserve()

    bool reset_seg(Point start, Point end, Point & p1, Point & p2) {
      double m = 0 ;
      if ( start.x() != end.x() )
        m = (start.y() - end.y()) / (start.x() - end.x()) ;
      double ans_x1, ans_x2 ;
      double ans_y1, ans_y2 ;
      ans_x1 = -1 ;  // for init ans_point
      ans_x2 = -1 ;
      ans_y1 = -1 ;
      ans_y2 = -1 ;
      vector<Point> vec ;
      if ( start.x() != end.x() ) {
        ans_y1 = m*bbox_ld.x() - m*start.x() + start.y() ;
        ans_y2 = m*bbox_ru.x() - m*start.x() + start.y() ;
        ans_x1 = ((bbox_ld.y() - start.y()) / m) + start.x() ; 
        ans_x2 = ((bbox_ru.y() - start.y()) / m) + start.x() ;
      } // if
      else {
        ans_x1 = bbox_ld.x() ;
        ans_x2 = bbox_ru.x() ;
        ans_y1 = -1 ; // just want it become impossible
        ans_y2 = -1 ;
      } // else  
      if ( ans_y1 >= -10e-6 && ans_y1 <= 10e-6 )
        ans_y1 = 0 ;
      if ( ans_y2 >= -10e-6 && ans_y2 <= 10e-6 )
        ans_y2 = 0 ;
      if ( ans_x1 >= -10e-6 && ans_x1 <= 10e-6 )
        ans_x1 = 0 ;
      if ( ans_x2 >= -10e-6 && ans_x2 <= 10e-6 )
        ans_x2 = 0 ;  
      
      if ( ans_y1 >= bbox_ld.y() && ans_y1 <= bbox_ru.y() )
        vec.push_back(Point(bbox_ld.x(), ans_y1)) ;
      if ( ans_y2 >= bbox_ld.y() && ans_y2 <= bbox_ru.y() )
        vec.push_back(Point(bbox_ru.x(), ans_y2)) ;
      if ( ans_x1 >= bbox_ld.x() && ans_x1 <= bbox_ru.x() )
        vec.push_back(Point(ans_x1,bbox_ld.y())) ;
      if ( ans_x2 >= bbox_ld.x() && ans_x2 <= bbox_ru.x() )
        vec.push_back(Point(ans_x2,bbox_ru.y())) ;

      if ( vec.size() == 2 || vec.size() == 3 || vec.size() == 4 ) {
        if ( violate(start) && violate(end) ) {
          // print_point(start, "debug start:") ;
          // print_point(end, "debug end:") ;
          return false ;
        } // if   
        else if ( violate(start) && !violate(end) ) {
          p1 = closet_point(start, vec[0], vec[1]) ;
        } // else if 
        else if ( !violate(start) && violate(end) ) {
          p2 = closet_point(end, vec[0], vec[1]) ;
        } // else if

        return true ;
      } // if
      else 
        return false ;
      
    } // reset_seg()

    bool violate(Point p) {
      if ( p.x() > bbox_ru.x() || p.x() < bbox_ld.x() || p.y() > bbox_ru.y() 
          || p.y() < bbox_ld.y() )
        return true ;
      else 
        return false ;

    } // violate()

    Point closet_point(Point pt, Point p1, Point p2) {
      double dis1 = (pt.x() - p1.x()) * (pt.x() - p1.x()) + (pt.y() - p1.y()) * (pt.y() - p1.y()) ;
      double dis2 = (pt.x() - p2.x()) * (pt.x() - p2.x()) + (pt.y() - p2.y()) * (pt.y() - p2.y()) ;
      if ( dis1 > dis2 ) 
        return p2 ;
      else void modify_output() ;
        return p1 ;
    } // closet_point()

    vector<Seg> Create_delaunay() {
      deal_dc_event() ;
      for ( size_t i = 0 ; i < adj_list.size() ; i++ ) {
        if ( adj_list[i].third )
          check_invalid_adj(adj_list[i].centre, i) ;
      } // for
      
      for ( size_t j = 0 ; j < adj_list.size() ; j++ ) {
        if ( adj_list[j].valid ) {
          if ( adj_list[j].third ) { // need to genarate three seg
            delaunay_edge.push_back(genarate_seg(adj_list[j].p1, adj_list[j].p2)) ;
            delaunay_edge.push_back(genarate_seg(adj_list[j].p1, adj_list[j].p3)) ;
            delaunay_edge.push_back(genarate_seg(adj_list[j].p2, adj_list[j].p3)) ;
          } // if 
          else
            delaunay_edge.push_back(genarate_seg(adj_list[j].p1, adj_list[j].p2)) ;
        } // if
      } // for

      return delaunay_edge ;
    } // Create_delaunay()

    void check_invalid_adj(Point p1, size_t index) {
      for ( size_t i = 0 ; i < invalid_circle.size() ; i++ ) {
        if ( invalid_circle[i] == p1 )
          adj_list[index].valid = false ;
      } // for

    } // check_invalid_adj()

    Seg genarate_seg(Point p1, Point p2) {
      Seg seg ;
      seg.start() = p1 ;
      seg.end() = p2 ;
      return seg ;
    } // generate_seg()

    void debug_linklist() {
      Arc * temp = root ;
      while (temp) {
        print_point(temp->site(), "linklist node");
        temp = temp->next ;
      } // while 
    } // debug_linklist()

    void print_point(Point p, string str) {

      cout << str << "  (" << p.x() << "," << p.y() << ")" << endl ;   

    } // print_point()

    void debug_output() {
      for ( size_t i = 0 ; i < answer.size() ; i++ ) {
        print_point(answer[i].start(), "start:") ;
        print_point(answer[i].end(), "end:") ;  
      } // for 

    } // debug_output

    vector<Point> debug_voronoi_cell() { return voronoi_cell ; } 
 
}; // Voronoi

PYBIND11_MODULE(_Voronoi, m){
    m.doc() = "pybind11 Voronoi";
    pybind11::class_<Point>(m, "Point")
        .def( pybind11::init<double, double>()) 
        .def( "Point_equal", &Point::Point_equal )
        .def_property_readonly("x", [](const Point &p) { return p.x(); })
        .def_property_readonly("y", [](const Point &p) { return p.y(); }) ;
    pybind11::class_<Seg>(m, "Seg")
        .def( pybind11::init<>())
        .def( pybind11::init<Point, Point>()) 
        .def( "Seg_equal", &Seg::Seg_equal )
        .def_property_readonly("start", [](const Seg &s) { return s.start(); })
        .def_property_readonly("end", [](const Seg &s) { return s.end(); }) ;
    pybind11::class_<Arc>(m, "Arc")
        .def( pybind11::init<>())
        .def( pybind11::init<Point, Seg, Seg>()) 
        .def_property_readonly("site", [](const Arc &a) { return a.site(); }) 
        .def_property_readonly("left_seg", [](const Arc &a) { return a.left_seg(); }) 
        .def_property_readonly("right_seg", [](const Arc &a) { return a.right_seg(); }) 
        .def_property_readonly("next", [](const Arc &a) { return a.next; }) 
        .def_property_readonly("prev", [](const Arc &a) { return a.prev; }) ;
    pybind11::class_<Event>(m, "Event")
        .def( pybind11::init<>()) 
        .def_property_readonly("pos", [](const Event &e) { return e.pos(); }) 
        .def_property_readonly("type", [](const Event &e) { return e.type(); })
        .def_property_readonly("valid", [](const Event &e) { return e.valid(); }) 
        .def_property_readonly("circle_centre", [](const Event &e) { return e.circle_centre(); }) ; 
    pybind11::class_<Pixel>(m, "Pixel")
        .def( pybind11::init<>()) 
        .def_property_readonly("color", [](const Pixel &pixel) { return pixel.color; })
        .def_property_readonly("p", [](const Pixel &pixel) { return pixel.p; })
        .def_property_readonly("valid", [](const Pixel &pixel) { return pixel.valid; }) ;
    pybind11::class_<Shader>(m, "Shader")
        .def( pybind11::init<>()) 
        .def( "Draw_color", &Shader::Distance_draw_color )
        .def( "getter_pixel", &Shader::getter_pixel ) ;
    pybind11::class_<Voronoi>(m, "Voronoi")
        .def( pybind11::init<>())
        .def( "Create_voronoi", &Voronoi::Create_voronoi )
        .def( "Create_delaunay", &Voronoi::Create_delaunay )
        .def( "debug_voronoi_cell", &Voronoi::debug_voronoi_cell ) ;
}