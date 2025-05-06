#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
struct Point{
    float x,y,z;
};
struct Point2d{
    float x,y;
};
#include "settings.cpp"
#include "camera.cpp"
#include "objects.cpp"
#include "render.cpp"
#include "upload.cpp"
using namespace std;

sf::RenderWindow window(sf::VideoMode(screen_width, screen_height),"gerNi");

int main() {
    window.setFramerateLimit(fps);
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;

    Object_uploader uploader;
    Render render=Render();
    sf::Vector2i mousePos;
    vector<pair<Point,Point>> object_edges= uploader.upload_obj_edges("C:/Users/Jasiek/CLionProjects/3d-engine-cpp/cat.obj");
    cout<<object_edges.size()<<endl;
    Camera camera(0, 0, 0, camera_width, camera_height, camera_distance,
                   camera_angle_speed, camera_speed);

    vector<Cube> cubes{Cube(0,0,100,20)};
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(200, 200), sf::Color::Red),
        sf::Vertex(sf::Vector2f(400, 300), sf::Color::Red)
    };
    cout<<"start"<<endl;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        cout << "Fps: " << 1.0f/deltaTime << "\n";
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }


        mousePos = sf::Mouse::getPosition(window);
        // camera.handle_input(::isKeyPressed(sf::Keyboard::W) ? sf::Keyboard::W : 0);
        camera.handle_input();
        camera.handle_mouse(mousePos.x,mousePos.y);
        camera.calculate_trigonometric();
        render.reset_render();
        window.clear(sf::Color::Black);
        // render.render_points(window, cubes[0].points, camera);
        // render.render_edges(window,cubes[0].edges, camera);
        render.render_edges(window, object_edges, camera);
        window.display();

        // Measure elapsed time since last frame

        // Calculate FPS
        cout << "FPS: " << static_cast<int>(fps) << '\r' << std::flush;
    }
}