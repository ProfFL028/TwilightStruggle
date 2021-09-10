import numpy as np

"""
triangle represented by three point.
"""
class Triangle:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
        pass

    """
    check if point(x, y) is in triangle's circum circle.
    """
    def circumCircleContains(self, x, y):
        return True