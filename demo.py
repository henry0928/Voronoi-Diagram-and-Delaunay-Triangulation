import _Voronoi
import random
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.spatial import Delaunay

def setup_list(count):
    i = 0
    site_list = []
    while i < count :
        p = input("Point ( Need to be like this form -> \"18 21\" ) :" )
        site_list.append(separate_string_to_point(p))
        i = i + 1 
    return site_list

def random_setup_list(count):
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

def separate_string_to_point(str):
    i = 0
    while i < len(str) :
        if str[i] == ' ':
            x = float(str[:i])
            y = float(str[i+1:])
        i = i + 1
    return _Voronoi.Point(x,y)

def Draw_scipy_voronoi(_list,ax):
    # plt.title('Scipy Voronoi')
    points = np.array(_list)
    vor = Voronoi(points)
    fig = voronoi_plot_2d(vor,ax)

def Draw_scipy_delaunay(_list,ax):
    # plt.title('Scipy Delaunay')
    points = np.array(_list)
    tri = Delaunay(points)
    ax.triplot(points[:,0], points[:,1], tri.simplices)

def Draw_diagram(_input, bound, edge_list, voronoi, ax):
    x_list = []
    y_list = []
    for point in _input:
        x_list.append(point.x)
        y_list.append(point.y)
    x = np.array(x_list)
    y = np.array(y_list)
    ax.plot([0,bound], [0,0], color="black")
    ax.plot([0,0], [0,bound], color="black")
    ax.plot([bound,bound], [0,bound], color="black")
    ax.plot([0,bound], [bound,bound], color="black")
    shader = _Voronoi.Shader()
    pixel_list = shader.Draw_color(_input)
    if voronoi == 1:
        # plt.title('My Voronoi')
        for pixel in pixel_list:
            pixel_x = pixel.p.x
            pixel_y = pixel.p.y
            if pixel.valid == 0:
                if pixel.color % 7 == 0 :
                    ax.plot(pixel_x, pixel_y,".", color='silver')
                elif pixel.color % 7 == 1 :
                    ax.plot(pixel_x, pixel_y,".", color='peachpuff')
                elif pixel.color % 7 == 2 :
                    ax.plot(pixel_x, pixel_y,".", color='lightgreen')
                elif pixel.color % 7 == 3 :
                    ax.plot(pixel_x, pixel_y,".", color='lightyellow')
                elif pixel.color % 7 == 4 :
                    ax.plot(pixel_x, pixel_y,".", color='lightblue')
                elif pixel.color % 7 == 5 :
                    ax.plot(pixel_x, pixel_y,".", color='lightpink')
                else :
                    ax.plot(pixel_x, pixel_y,".", color='mediumpurple')
    # else:
    #     plt.title('My Delaunay')
    ax.plot(x,y,"ok")
    for edge in edge_list:
        start = edge.start
        end = edge.end
        p1 = [start.x, end.x]
        p2 = [start.y, end.y]
        # plt.plot(p1, p2, color="red")
        ax.plot(p1, p2, color="red")

if __name__== '__main__':
    # list1 = setup_list1()
    # list2 = setup_list2()
    # list3 = setup_list3()
    # test1
    # bbox_1 = _Voronoi.Point(0,0)
    # bbox_2 = _Voronoi.Point(30,30)
    # test2
    # bbox_1 = _Voronoi.Point(0,0)
    # bbox_2 = _Voronoi.Point(20,20)
    # test3
    fig = plt.figure()
    ax1 = fig.add_subplot(2,2,1)
    ax2 = fig.add_subplot(2,2,2)
    ax3 = fig.add_subplot(2,2,3)
    ax4 = fig.add_subplot(2,2,4)
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(100,100)
    s = input("random or specify:")
    count = input("Number of site:")
    if s == "random":
        _list, _scipy_list = random_setup_list(int(count))
    else :
        _list = setup_list(int(count))

    my_diagram = _Voronoi.Voronoi()
    voronoi = my_diagram.Create_voronoi(_list, bbox_1, bbox_2)
    Draw_diagram(_list, 100, voronoi, True, ax1)
    Draw_scipy_voronoi(_scipy_list, ax2)
    delaunay = my_diagram.Create_delaunay()
    Draw_diagram(_list, 100, delaunay, False, ax3)
    Draw_scipy_delaunay(_scipy_list, ax4)
    plt.show()


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

# def setup_list1():
#     site_list = []
#     temp_point = _Voronoi.Point(3,23)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(9,23)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(13,8)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(5,16)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(18,21)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(22,11)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(27,18)
#     site_list.append(temp_point)
#     return site_list

# def setup_list2():
#     site_list = []
#     temp_point = _Voronoi.Point(5,5)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(5,10)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(10,5)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(10,10)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(15,5)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(15,10)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(5,15)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(10,15)
#     site_list.append(temp_point)
#     return site_list

# def setup_list3():
#     site_list = []
#     temp_point = _Voronoi.Point(4,33)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(10,27)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(15,15)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(21,30)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(29,12)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(34,8)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(39,36)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(25,20)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(7,5)
#     site_list.append(temp_point)
#     temp_point = _Voronoi.Point(18,11)
#     site_list.append(temp_point)
#     return site_list


# Still have bugs!

# deal on point:  (9,91)
# deal on point:  (10,86)
# deal on point:  (84,82)
# deal on point:  (40,78)
# deal on point:  (44,56)
# deal on point:  (49,55)
# deal on point:  (80,52)
# deal on point:  (71,45)
# deal on point:  (3,41)
# deal on point:  (70,39)
# deal on point:  (92,20)
# deal on point:  (84,17)
# deal on point:  (1,11)
# deal on point:  (7,9)
# deal on point:  (63,5)

# deal on point:  (49,96)
# deal on point:  (65,96)
# deal on point:  (89,90)
# deal on point:  (57,89)
# deal on point:  (7,81)
# deal on point:  (34,69)
# deal on point:  (87,67)
# deal on point:  (48,60)
# deal on point:  (78,56)
# deal on point:  (57,35)
# deal on point:  (31,33)
# deal on point:  (94,28)
# deal on point:  (45,10)
# deal on point:  (8,9)
# deal on point:  (22,6)


# PERFECT with 100*100 15 site

# NO:1

# deal on point:  (77,95)
# deal on point:  (87,88)
# deal on point:  (16,86)
# deal on point:  (66,77)
# deal on point:  (13,75)
# deal on point:  (34,74)
# deal on point:  (22,72)
# deal on point:  (37,66)
# deal on point:  (4,61)
# deal on point:  (82,48)
# deal on point:  (94,42)
# deal on point:  (58,23)
# deal on point:  (93,20)
# deal on point:  (30,10)
# deal on point:  (64,6)

# NO:2

# deal on point:  (49,94)
# deal on point:  (73,93)
# deal on point:  (36,84)
# deal on point:  (68,81)
# deal on point:  (63,70)
# deal on point:  (49,55)
# deal on point:  (91,47)
# deal on point:  (74,47)
# deal on point:  (58,46)
# deal on point:  (28,46)
# deal on point:  (51,40)
# deal on point:  (81,22)
# deal on point:  (20,12)
# deal on point:  (15,10)
# deal on point:  (33,7)

# NO:3

# deal on point:  (65,99)
# deal on point:  (63,96)
# deal on point:  (26,93)
# deal on point:  (41,66)
# deal on point:  (49,60)
# deal on point:  (39,58)
# deal on point:  (55,50)
# deal on point:  (19,50)
# deal on point:  (71,47)
# deal on point:  (83,46)
# deal on point:  (80,45)
# deal on point:  (75,39)
# deal on point:  (28,32)
# deal on point:  (13,10)
# deal on point:  (93,6)

