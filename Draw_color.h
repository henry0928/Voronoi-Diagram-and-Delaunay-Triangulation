#include <vector>
#include <queue>
#include "Point.h"

class Pixel{
  public:  
    int color ;
    bool valid ;
    Point p ;
 
    Pixel & operator=(const Pixel & other) ;
};

class Shader {
  Pixel map[100][100] ;
  std::queue<Pixel> bfs_queue ;

  public:
    Shader() ;
    Pixel getter_pixel(int x, int y) ;
    std::vector<Pixel> Distance_draw_color(std::vector<Point> site_list) ;
    double distance(Point p, int x, int y) ;
    std::vector<Pixel> BFS_draw_color(std::vector<Point> site_list) ;
    void bfs(Point p, int color) ;
};