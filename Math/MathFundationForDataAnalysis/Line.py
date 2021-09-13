import math
from sys import maxsize

"""
Line represented by slope and intercept.
"""
class Line:
    def __init__(self, slope, intercept):
        self.slope = slope
        self.intercept = intercept

    
    
        

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
    When two line are perpendicular, than 
    """
    def midperpendicular(self) -> Line:
        
        # set slope to maxsize when the line is parrallel to x-axis.
        if (abs(self.p2.y - self.p1.y) <= 0.0000000001) :
            return Line(slope = maxsize, intercept = (self.p1.x + self.p2.x)/2)
        
        centerPoint = (self.p1.x / 2 + self.p2.x /2, self.p1.y + self.p2.y / 2)
        slope = (self.p2.y - self.p1.y) / (self.p1.x - self.p2.x)
        intercept = centerPoint[1] - slope * centerPoint[0]

        return Line(slope=slope, intercept = intercept)

