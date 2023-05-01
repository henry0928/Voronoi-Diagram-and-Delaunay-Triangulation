import _Voronoi
import numpy as np
import matplotlib.pyplot as plt

site_list = []

def setup_list():
    global site_list
    temp_point = _Voronoi.Point(3,13)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(9,13)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(14,8)
    site_list.append(temp_point)
    temp_point = _Voronoi.Point(5,6)
    site_list.append(temp_point)
    # temp_point = _Voronoi.Point(10,5)
    # site_list.append(temp_point)
    # temp_point = _Voronoi.Point(15,10)
    # site_list.append(temp_point)
    # temp_point = _Voronoi.Point(10,15)
    # site_list.append(temp_point)
    # temp_point = _Voronoi.Point(15,15)
    # site_list.append(temp_point)

if __name__== '__main__':
    setup_list()
    bbox_1 = _Voronoi.Point(0,0)
    bbox_2 = _Voronoi.Point(20,20)
    _Voronoi.Voronoi(site_list, bbox_1, bbox_2)
    edge_list = _Voronoi.Output()
    x = np.array([3,9,14,5])
    y = np.array([13,13,8,6])
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
    # Todo use opencv to draw the diagram

    # shape = (20,20,3)
    # origin_img = np.zeros(shape, np.uint8)
    # origin_img.fill(255)
    # point_coler = (0, 0, 255)
    # edge_coler = (230, 216, 173)
    # point_list = [(0,10), (0,20), (10,10), (10,20)]
    # for point in point_list:
    #     cv2.circle(origin_img, point, 1, point_coler, -1)
    # img = origin_img
    # cv2.imshow('image', img)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()
    