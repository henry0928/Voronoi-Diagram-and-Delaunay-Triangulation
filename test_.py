import numpy as np
import pytest
import _Voronoi
import random
import numpy as np
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.spatial import Delaunay

def make_sitelist(count):
    site_list = []
    scipy_site_list = []
    i = 0
    while i < count :
        x = float(random.randint(1,99))
        y = float(random.randint(1,99))
        scipy_input = [x,y]
        scipy_site_list.append(scipy_input)
        site_list.append(_Voronoi.Point(x,y))
        i = i + 1 
    return site_list, scipy_site_list

def test_Point():
    p1 = _Voronoi.Point(100,99)
    assert p1.x == 100
    assert p1.y == 99 
    p2 = _Voronoi.Point(20,65)
    p3 = _Voronoi.Point(20,65)
    assert p2.Point_equal(p3) == True

def test_Seg():
    p1 = _Voronoi.Point(50,50)
    p2 = _Voronoi.Point(100,100)
    s1 = _Voronoi.Seg(p1,p2)
    s2 = _Voronoi.Seg(p1,p2)
    assert s1.start.Point_equal(p1) == True
    assert s1.end.Point_equal(p2) == True
    assert s1.Seg_equal(s2) == True
    slope = ( s1.end.y - s1.start.y ) / ( s1.end.x - s1.start.x ) 
    assert slope == 1 

def test_Arc():
    p1 = _Voronoi.Point(25,40)
    p2 = _Voronoi.Point(10,60)
    p3 = _Voronoi.Point(40,60)
    s1 = _Voronoi.Seg(p2,p3)
    s2 = _Voronoi.Seg(p2,p3)
    arc = _Voronoi.Arc(p1,s1,s2)
    assert arc.site.Point_equal(p1) == True
    assert arc.left_seg.Seg_equal(arc.right_seg) == True
    assert arc.next == None
    assert arc.prev == None
    assert arc.next == arc.prev 

def test_Event():
    e = _Voronoi.Event()
    assert e.pos.x == 0 
    assert e.pos.y == 0
    assert e.pos.Point_equal(e.circle_centre)
    assert e.valid == 0 

def test_Shader():
    shader = _Voronoi.Shader()
    pixel1 = shader.getter_pixel(2,7)
    p1 = _Voronoi.Point(2,7)
    pixel2 = shader.getter_pixel(70,83)
    p2 = _Voronoi.Point(70,83)
    assert pixel1.color == pixel2.color 
    assert pixel1.p.Point_equal(p1) == True
    assert pixel2.p.Point_equal(p2) == True

    
