import math
import numpy as np
import pandas as pd

'''
Read input file to get (x,y) coordinates of points. After the data is read from the file, it should return the data points
as a list of tuples.Each data point is denoted with a tuple (x,y) where "x" denotes the x-coordinate and "y" denotes 
the y-coordinate.
'''


def read_input_file(input_file_name):
    # TODO: DONE!
    input_file = open(input_file_name, "r")
    if input_file.mode == 'r':
        input_file = input_file.read().splitlines()
        points = []
        for line in input_file:
            line = line[1:-1].split(",")
            points.append((float(line[0]), float(line[1])))
        return points
    return []


class AgglomerativeClustering:
    LINKAGE = {
        'MIN': 0,
        'MAX': 1,
        'GROUP_AVG': 2
    }

    def __init__(self, input_data):
        self.data = input_data
        self.clusters_current = []
        # Add your member variables(if any here)
        self.proximity_matrix = []

    # This method is added in order to calculate proximity matrix
    def calculate_proximity_matrix(self, linkage):
        matrix = []
        size = len(self.clusters_current)
        for i in range(size):
            cluster1 = self.clusters_current[i]
            lst = []
            for j in range(size):
                cluster2 = self.clusters_current[j]
                if linkage == AgglomerativeClustering.LINKAGE['MIN']:
                    curr_val = np.finfo(np.float).max
                else:
                    curr_val = 0
                if (i == j) and (linkage == AgglomerativeClustering.LINKAGE['MIN']):
                    lst.append(0.00)
                else:
                    for ele1 in cluster1:
                        ele1 = np.array(ele1)
                        for ele2 in cluster2:
                            ele2 = np.array(ele2)
                            temp_val = np.linalg.norm(ele1 - ele2)
                            if (linkage == AgglomerativeClustering.LINKAGE['MIN']) and (temp_val < curr_val):
                                curr_val = temp_val
                            elif (linkage == AgglomerativeClustering.LINKAGE['MAX']) and (temp_val > curr_val):
                                curr_val = temp_val
                            elif linkage == AgglomerativeClustering.LINKAGE['GROUP_AVG']:
                                curr_val += temp_val
                    if linkage == AgglomerativeClustering.LINKAGE['GROUP_AVG']:
                        lst.append(round(curr_val/len(cluster1)*len(cluster2), 2))
                    else:
                        lst.append(round(curr_val, 2))
            matrix.append(lst)
        return matrix

    # This method is added in order to merge two closest clusters
    def merge_closest(self):
        size = len(self.proximity_matrix)
        min_value = np.finfo(np.float).max
        min_ele1 = 0
        min_ele2 = 0
        for row in range(size):
            row_ele = self.proximity_matrix[row]
            for col in range(size):
                ele = row_ele[col]
                if (ele < min_value) and (row != col):
                    min_value = ele
                    min_ele1 = row
                    min_ele2 = col
        self.clusters_current[min_ele1] += self.clusters_current[min_ele2]
        del self.clusters_current[min_ele2]

    '''
    Explanations for AgglomerativeClustering class members:

    data:                   list of tuples including input 2-D data points. 
                            Each data point is denoted with a tuple (x,y) where "x" denotes the x-coordinate and 
                            "y" denotes the y-coordinate. Ex:[(1,2),(3,4),(100,101),....]
    clusters_current:       list of lists which includes the current elements of each cluster as tuples in a list and
                            where each data point is a member of one of the clusters. 
                            Ex:[[(1,2),(3,4),..],[(100,101),(100,102),....]]

    
    *** Make sure you keep template structure that is given to you. 
    *** YOU CAN ADD TO THE template STRUCTURE, BUT CAN NOT REMOVE FROM IT. ***
    '''

    '''
    This method is the first step of the algorithm: Initialize all "n" different data points to "n" different clusters.
    This "n" clusters are kept as list of lists. This method will convert each element of self.clusters_current attribute
    into a separate list and assign the new list into self.clusters_current attribute.
    Ex:  Before this method is invoked, self.clusters_current=[(1,2),(3,4),(5,6),(7,8)]
         After this method is invoked, self.clusters_current= [[(1,2)],[(3,4)],[(5,6)],[(7,8)]]
    '''

    def initialize_clustering(self):
        # TODO: DONE!
        self.clusters_current = [[element] for element in self.data]
        return self.clusters_current

    '''This method returns the resultant clusters as the result of the clustering given the linkage. The method should
    exit the loop of the algorithm and return the resultant clusters when the number of clusters is equal the given 
    number_of_clusters argument. In order to clarify, the following example is given: Assume input data consists of 100 data points,
    number_of_clusters=3 and linkage is "MIN". Then "fit_predict" should return a list of lists where each list denotes an 
    independent cluster and includes the data points(a tuple with x,y coordinates) inside each cluster.
    Ex: [[(0,2),(1,3),...],[(10,20),(11,21),(12,22),...],[(100,100),(101,100),(102,100),...]]
    '''

    def fit_predict(self, number_of_clusters, linkage):
        # TODO: DONE!
        self.proximity_matrix = AgglomerativeClustering.calculate_proximity_matrix(self, linkage)
        while len(self.clusters_current) != number_of_clusters:
            AgglomerativeClustering.merge_closest(self)
            self.proximity_matrix = AgglomerativeClustering.calculate_proximity_matrix(self, linkage)
        return self.clusters_current
