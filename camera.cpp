#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;
class Camera {
public:
    // Members to represent the position and size of the rectangle
    float x, y, z;
    int width, height,distance;
    float scale_x, scale_y,angle_x,angle_y,angle_speed,speed;
    float sin_x,sin_y,cos_x,cos_y;
    // Constructor to initialize the rectangle
    Camera(float x, float y,float z, int width, int height,int distance,float angle_speed=1,float speed=1)
        : x(x), y(y),z(z), width(width), height(height),distance(distance),angle_speed(angle_speed),speed(speed) {
        scale_x=float(screen_width)/float(width);
        scale_y=float(screen_height)/float(height);
        angle_x=0;
        angle_y=0;
    }
    void calculate_trigonometric() {
        sin_x=sin(angle_x);
        sin_y=sin(angle_y);
        cos_x=cos(angle_x);
        cos_y=cos(angle_y);
    }
    //     return (x*self.scale_x, y*self.scale_y)
    Point rotate_point(const Point point) {
        float x1=point.x-x;
        float y1=point.y-y;
        float z1=point.z-z;

        float x_rotated=x1*cos_x-z1*sin_x;
        float z_rotated=x1*sin_x+z1*cos_x;

        float y_rotated=y1*cos_y-z_rotated*sin_y;
        z_rotated=y1*sin_y+z_rotated*cos_y;
        return {x_rotated, y_rotated, z_rotated};
    }
    Point2d blit_point(const Point point) {
        Point rotated_point=rotate_point(point);
        float x1=rotated_point.x;
        float y1=rotated_point.y;
        float z1=rotated_point.z;
        if (z1<=0) {
            return Point2d{-1,-1};
        }
        float dz=distance/z1;
        float x2=width/2+x1*dz;
        float y2=height/2 + y1*dz;
        // cout<<x2<<" "<<y2<<endl;
        return Point2d{x2*scale_x,y2*scale_y};
    }
    void handle_input() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            Point point=rotate_point({x,y,z+speed});
            x-=point.x;
            y-=point.y;
            z+=point.z;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            Point point=rotate_point({x,y,z+speed});
            x+=point.x;
            y+=point.y;
            z-=point.z;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x-=speed*cos_x;
            z+=speed*sin_x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x+=speed*cos_x;
            z-=speed*sin_x;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            y+=speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            y-=speed;
        }
    }
    void handle_mouse(float mx,float my) {
        angle_x=(mx-screen_width/2)/screen_width*M_PI*angle_speed;
        angle_y=(my-screen_height/2)/screen_width*M_PI*angle_speed;
        if (angle_x>2*M_PI) {
            angle_x-=2*M_PI;
        }
        if (angle_x<0) {
            angle_x+=2*M_PI;
        }
        if (angle_y>2*M_PI) {
            angle_y-=2*M_PI;
        }
        if (angle_y<0) {
            angle_y+=2*M_PI;
        }
    }
    void print() const {
        std::cout << "Pos x=" << x << ", y=" << y<< " z=" << z
                  << "\nwidth=" << width << ", height=" << height << ")\n";
    }
};