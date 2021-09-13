import math
from sys import maxsize

from Point import Point


PERCISION = 0.0000000001
"""
Line represented by slope and intercept.
"""
class Line:
    def __init__(self, slope, intercept):
        self.slope = slope
        self.intercept = intercept

    """
    compute two line's intersection.
    """
    def intersection(self, line):
        # Same slope of two lines refers to parrallel, and they don't have intersection.
        if (abs(self.slope - line.slope)<=PERCISION):
            return None
        
        x = (line.intercept - self.intercept) / (self.slope - line.slope)
        y = self.slope * x + self.intercept
        
        return Point(x, y)
        
        

"""
LineSegment represented by two points.
"""
class LineSegment:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    """
    calculate middle perpendiduclar
    If linesegment is parrallel to x-axis, set the slope to the maxsize(sys.maxsize) to avoid divide by 0 problem.
    When two line are perpendicular, mutliple of these slope equals to -1, which can be used to simplify the computation.
    The midperpendicular must come through centerpoint of two points, and we can use it to calculate the intercept.
    """
    def midperpendicular(self) -> Line:
        # set slope to maxsize when the line is parrallel to x-axis.
        if (abs(self.p2.y - self.p1.y) <= PERCISION) :
            return Line(slope = maxsize, intercept = (self.p1.x + self.p2.x)/2)
        
        centerPoint = (self.p1.x / 2 + self.p2.x /2, self.p1.y + self.p2.y / 2)
        slope = (self.p2.y - self.p1.y) / (self.p1.x - self.p2.x)
        intercept = centerPoint[1] - slope * centerPoint[0]

        return Line(slope=slope, intercept = intercept)

