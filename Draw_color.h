#include "Class_def.h"
#include <queue>

class Pixel{
  public:  
    int color ;
    bool valid ;
    Point p ;
 
    Pixel & operator=(const Pixel & other) {
      if ( this != &other ) {
        this->color = other.color ;
        this->valid = other.valid ;
        this->p = other.p ;  
      } // if  

      return *this ;
    }
};

class Shader {
  private:
    Pixel map[100][100] ;
    queue<Pixel> bfs_queue ;

  public:
    
    Shader() {
      double x = 0 ;
      double y = 0 ;
      for ( size_t i = 0 ; i < 100 ; i++ ) {
        y = 0 ;
        for ( size_t j = 0 ; j < 100 ; j++ ) {
          map[i][j].valid = true ;
          map[i][j].p = Point(x,y) ;
          y++ ;
        } // for
        x++ ;
      } // for 
    } // Shader()

    vector<Pixel> Distance_draw_color(vector<Point> site_list) {
      double temp = 1000000;
      double dis ;
      size_t index ;
      Pixel pixel ; 
      vector<Pixel> color_list ; 
      for ( int i = 1 ; i < 100 ; i++ ) {
        for ( int j = 1 ; j < 100 ; j++ ) {
          temp = 1000000 ;
          for ( size_t k = 0 ; k < site_list.size() ; k++ ) { 
            dis = distance(site_list[k], i, j) ;
            if ( dis < temp ) {
              temp = dis ;
              index = k ;
            } // if 
          } // for 

          pixel.valid = false ;
          pixel.color = (int)index ;
          pixel.p.x() = i ;
          pixel.p.y() = j ;
          color_list.push_back(pixel) ;

        } // for 
      } // for 
      
      return color_list ;
    } // Distance_draw_color()

    double distance(Point p, int x, int y) {
      double xx = p.x()-x ;
      double yy = p.y()-y ;
      return (xx * xx) + (yy * yy) ;
    } // distance()

    vector<Pixel> BFS_draw_color(vector<Point> site_list) {
      int x, y ;
      int _color = 1 ;
      vector<Pixel> color_list ; 
      Pixel n_pixel ;
      for ( size_t i = 0 ; i < site_list.size() ; i++ ) {
        x = site_list[i].x() ;
        y = site_list[i].y() ;
        map[x][y].valid = false ;
        map[x][y].color = _color ;
        bfs_queue.push(map[x][y]) ;
        _color++ ;
      } // for 

      while ( !bfs_queue.empty() ) {
        n_pixel = bfs_queue.front() ;
        bfs_queue.pop() ;
        bfs(n_pixel.p, n_pixel.color); 
      } // while

      for ( int i = 1 ; i < 100 ; i++ ) {
        for ( int j = 1 ; j < 100 ; j++ ) {
          color_list.push_back(map[i][j]) ;
        } // for
      } // for 

      return color_list ;

    } // draw_color()

    void bfs(Point p, int color) {
      int x = p.x() ;
      int y = p.y() ;
      int x_index = x-1 ;
      int y_index = y-1 ;
      int test_num = 0 ;
      while ( x_index <= x+1 ) {
        y_index = y-1 ;
        while ( y_index <= y+1 ) {
          if ( x_index >= 0 && x_index < 100 && y_index >= 0 && y_index < 100 ) {
            if ( map[x_index][y_index].valid == true ) {
              map[x_index][y_index].color = color ;
              map[x_index][y_index].valid = false ;
              bfs_queue.push(map[x_index][y_index]) ;
            } // if  
          } // if
          
          test_num++ ;
          y_index++ ;
        } // while 

        x_index++ ;
      } // while 
    } // bfs()
};