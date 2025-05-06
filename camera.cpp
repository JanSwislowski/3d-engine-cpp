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
    // Constructor to initialize the rectangle
    Camera(float x, float y,float z, int width, int height,int distance,float angle_speed=1,float speed=1)
        : x(x), y(y),z(z), width(width), height(height),distance(distance),angle_speed(angle_speed),speed(speed) {
        scale_x=float(screen_width)/float(width);
        scale_y=float(screen_height)/float(height);
        angle_x=0;
        angle_y=0;
    }

    //     return (x*self.scale_x, y*self.scale_y)
    vector<float> rotate_point(vector<float> point) {
        float x1=point[0]-x;
        float y1=point[1]-y;
        float z1=point[2]-z;

        float x_rotated=x1*cos(angle_x)-z1*sin(angle_x);
        float z_rotated=x1*sin(angle_x)+z1*cos(angle_x);

        float y_rotated=y1*cos(angle_y)-z_rotated*sin(angle_y);
        z_rotated=y1*sin(angle_y)+z_rotated*cos(angle_y);
        return {x_rotated, y_rotated, z_rotated};
    }
    vector <float> blit_point(vector<float> point) {
        point=rotate_point(point);
        float x1=point[0];
        float y1=point[1];
        float z1=point[2];
        if (z1<=0) {
            return vector<float>{-1,-1};
        }
        float x2=width/2+x1*distance/z1;
        float y2=height/2 + y1*distance/z1;
        // cout<<x2<<" "<<y2<<endl;
        return vector<float>{x2*scale_x,y2*scale_y};
    }
    void handle_input() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            z+=speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            z-=speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x-=speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x+=speed;
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