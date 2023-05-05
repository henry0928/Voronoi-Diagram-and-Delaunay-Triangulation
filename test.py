import _Voronoi
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d

def setup_list1():
    site_list = []
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
    return site_list

def setup_list2():
    site_list = []
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
    temp_point = _Voronoi.Point(10,15)
    site_list.append(temp_point)
    return site_list

def setup_list3():
    site_list = []
    temp_point = _Voronoi.Point(4,33)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(10,27)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(15,15)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(21,30)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(29,12)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(34,8)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(39,36)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(25,20)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(7,5)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(18,11)
    site_list.append(temp_point)
    return site_list

def ans_voronoi():
    points = np.array([[3,23],[9,23],[13,8],
                       [5,16],[18,21],[22,11],[27,18]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

def ans_voronoi3():
    points = np.array([[4,33],[10,27],[15,15],[21,30],[29,12],
                       [34,8],[39,36],[25,20],[7,5],[18,11]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

def Create_diagram(_list, p1, p2):
    diagram = _Voronoi.Voronoi()
    return diagram.Create_graph(_list, p1, p2) # return edge_list

def Draw_diagram3(_list):
    x = np.array([4,10,15,21,29,34,39,25,7,18])
    y = np.array([33,27,15,30,12,8,36,20,5,11])
    plt.plot([0,40], [0,0], color="blue")
    plt.plot([0,0], [0,40], color="blue")
    plt.plot([40,40], [0,40], color="blue")
    plt.plot([0,40], [40,40], color="blue")
    plt.plot(x,y,"ob")
    for edge in edge_list:
        start = edge.start
        end = edge.end
        p1 = [start.x, end.x]
        p2 = [start.y, end.y]
        plt.plot(p1, p2, color="red")
    plt.show()

def Draw_diagram2(_list):
    x = np.array([5,5,10,10,15,15,5,10])
    y = np.array([5,10,5,10,5,10,15,15])
    plt.plot([0,20], [0,0], color="blue")
    plt.plot([0,0], [0,20], color="blue")
    plt.plot([20,20], [0,20], color="blue")
    plt.plot([0,20], [20,20], color="blue")
    plt.plot(x,y,"ob")
    for edge in edge_list:
        start = edge.start
        end = edge.end
        p1 = [start.x, end.x]
        p2 = [start.y, end.y]
        plt.plot(p1, p2, color="red")
    plt.show()

def Draw_diagram1(_list):
    x = np.array([3,9,13,5,18,22,27])
    y = np.array([23,23,8,16,21,11,18])
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

if __name__== '__main__':
    list1 = setup_list1()
    list2 = setup_list2()
    list3 = setup_list3()
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(30,30)
    edge_list = Create_diagram(list1, bbox_1, bbox_2)
    Draw_diagram1(edge_list)
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(20,20)
    edge_list = Create_diagram(list2, bbox_1, bbox_2)
    Draw_diagram2(edge_list)
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(40,40)
    edge_list = Create_diagram(list3, bbox_1, bbox_2)
    Draw_diagram3(edge_list)


    # test1
    # x = np.array([3,9,13,5,18,22,27])
    # y = np.array([23,23,8,16,21,11,18])
    # test2
    # x = np.array([5,5,10,10,15,15,5,10])
    # y = np.array([5,10,5,10,5,10,15,15])
    # test3
    # x = np.array([4,10,15,21,29,34,39,25,7,18])
    # y = np.array([33,27,15,30,12,8,36,20,5,11])
