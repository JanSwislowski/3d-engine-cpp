#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
struct Point{
    float x,y,z;
};
class Cube {
public:
    float x, y, z, a;
    vector<Point> points;
    vector<pair<Point,Point>> edges;
    Cube(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {
        points = {
            {x-a/2, y-a/2, z-a/2},
            {x+a/2, y-a/2, z-a/2},
            {x+a/2, y+a/2, z-a/2},
            {x-a/2, y+a/2, z-a/2},
            {x-a/2, y-a/2, z+a/2},
            {x+a/2, y-a/2, z+a/2},
            {x+a/2, y+a/2, z+a/2},
            {x-a/2, y+a/2, z+a/2}
        };
        edges={
            {points[0], points[1]},
            {points[1], points[2]},
            {points[2], points[3]},
            {points[3], points[0]},
            {points[4], points[5]},
            {points[5], points[6]},
            {points[6], points[7]},
            {points[7], points[4]},
            {points[0], points[4]},
            {points[1], points[5]},
            {points[2], points[6]},
            {points[3], points[7]}
        };
    }

};
