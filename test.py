import _Voronoi
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d

site_list = []

def setup_list():
    global site_list
    temp_point = _Voronoi.Point(3,23)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(9,23)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(13,8)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(5,16)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(18,21)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(22,11)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(27,18)
    site_list.append(temp_point)
    # temp_point = _Voronoi.Point(27,20)
    # site_list.append(temp_point)

def setup_list2():
    global site_list
    temp_point = _Voronoi.Point(5,5)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(5,10)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(10,5)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(10,10)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(15,5)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(15,10)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(5,15)
    site_list.append(temp_point)
    # temp_point = _Voronoi.Point(15,15)
    # site_list.append(temp_point)
    temp_point = _Voronoi.Point(10,15)
    site_list.append(temp_point)

def ans_voronoi():
    points = np.array([[3,23],[9,23],[13,8],
                       [5,16],[18,21],[22,11],[27,18]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

if __name__== '__main__':
    setup_list()
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(30,30)
    _Voronoi.Voronoi(site_list, bbox_1, bbox_2)
    edge_list = _Voronoi.Output()
    x = np.array([3,9,13,5,18,22,27])
    y = np.array([23,23,8,16,21,11,18])
    # x = np.array([5,5,10,10,15,15,5,10])
    # y = np.array([5,10,5,10,5,10,15,15])
    plt.plot([0,30], [0,0], color="blue")
    plt.plot([0,0], [0,30], color="blue")
    plt.plot([30,30], [0,30], color="blue")
    plt.plot([0,30], [30,30], color="blue")
    plt.plot(x,y,"ob")
    for edge in edge_list:
        start = edge.start
        end = edge.end
        p1 = [start.x, end.x]
        p2 = [start.y, end.y]
        plt.plot(p1, p2, color="red")
    plt.show()
    # ans_voronoi()
