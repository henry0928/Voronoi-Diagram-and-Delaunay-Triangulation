import _Voronoi
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.spatial import Delaunay

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

def ans_voronoi_1():
    points = np.array([[3,23],[9,23],[13,8],
                       [5,16],[18,21],[22,11],[27,18]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

def ans_delaunay_1():
    points = np.array([[3,23],[9,23],[13,8],
                       [5,16],[18,21],[22,11],[27,18]])
    tri = Delaunay(points)
    plt.triplot(points[:,0], points[:,1], tri.simplices)
    plt.show()

def ans_voronoi_2():
    points = np.array([[5,5],[5,10],[10,5],[10,10],
                       [15,5],[15,10],[5,15],[10,15]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

def ans_delaunay_2():
    points = np.array([[5,5],[5,10],[10,5],[10,10],
                       [15,5],[15,10],[5,15],[10,15]])
    tri = Delaunay(points)
    plt.triplot(points[:,0], points[:,1], tri.simplices)
    plt.show()

def ans_voronoi_3():
    points = np.array([[4,33],[10,27],[15,15],[21,30],[29,12],
                       [34,8],[39,36],[25,20],[7,5],[18,11]])
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor)
    plt.show()

def ans_delaunay_3():
    points = np.array([[4,33],[10,27],[15,15],[21,30],[29,12],
                       [34,8],[39,36],[25,20],[7,5],[18,11]])
    tri = Delaunay(points)
    plt.triplot(points[:,0], points[:,1], tri.simplices)
    plt.show()

def Draw_diagram(input, bound, _list):
    x_list = []
    y_list = []
    for point in input:
        x_list.append(point.x)
        y_list.append(point.y)
    x = np.array(x_list)
    y = np.array(y_list)
    plt.plot([0,bound], [0,0], color="blue")
    plt.plot([0,0], [0,bound], color="blue")
    plt.plot([bound,bound], [0,bound], color="blue")
    plt.plot([0,bound], [bound,bound], color="blue")
    plt.plot(x,y,"ob")
    for edge in _list:
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
    # test1
    # bbox_1 = _Voronoi.Point(0,0)
    # bbox_2 = _Voronoi.Point(30,30)
    # test2
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(20,20)
    # test3
    # bbox_1 = _Voronoi.Point(0,0)
    # bbox_2 = _Voronoi.Point(40,40)

    my_diagram = _Voronoi.Voronoi()
    voronoi = my_diagram.Create_voronoi(list2, bbox_1, bbox_2)
    Draw_diagram(list2, 20, voronoi)
    ans_voronoi_2()
    delaunay = my_diagram.Create_delaunay()
    Draw_diagram(list2, 20, delaunay)
    ans_delaunay_2()



                                    # Backup function!!

# def Draw_diagram_3(_list):
#     x = np.array([4,10,15,21,29,34,39,25,7,18])
#     y = np.array([33,27,15,30,12,8,36,20,5,11])
#     plt.plot([0,40], [0,0], color="blue")
#     plt.plot([0,0], [0,40], color="blue")
#     plt.plot([40,40], [0,40], color="blue")
#     plt.plot([0,40], [40,40], color="blue")
#     plt.plot(x,y,"ob")
#     for edge in _list:
#         start = edge.start
#         end = edge.end
#         p1 = [start.x, end.x]
#         p2 = [start.y, end.y]
#         plt.plot(p1, p2, color="red")
#     plt.show()

# def Draw_diagram_2(_list):
#     x = np.array([5,5,10,10,15,15,5,10])
#     y = np.array([5,10,5,10,5,10,15,15])
#     plt.plot([0,20], [0,0], color="blue")
#     plt.plot([0,0], [0,20], color="blue")
#     plt.plot([20,20], [0,20], color="blue")
#     plt.plot([0,20], [20,20], color="blue")
#     plt.plot(x,y,"ob")
#     for edge in _list:
#         start = edge.start
#         end = edge.end
#         p1 = [start.x, end.x]
#         p2 = [start.y, end.y]
#         plt.plot(p1, p2, color="red")
#     plt.show()

# def Draw_diagram_1(_list):
#     x = np.array([3,9,13,5,18,22,27])
#     y = np.array([23,23,8,16,21,11,18])
#     plt.plot([0,30], [0,0], color="blue")
#     plt.plot([0,0], [0,30], color="blue")
#     plt.plot([30,30], [0,30], color="blue")
#     plt.plot([0,30], [30,30], color="blue")
#     plt.plot(x,y,"ob")
#     for edge in _list:
#         start = edge.start
#         end = edge.end
#         p1 = [start.x, end.x]
#         p2 = [start.y, end.y]
#         plt.plot(p1, p2, color="red")
#     plt.show()
