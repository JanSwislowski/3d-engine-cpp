#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "settings.cpp"
#include "camera.cpp"
#include "objects.cpp"
#include "render.cpp"
using namespace std;
sf::RenderWindow window(sf::VideoMode(screen_width, screen_height),"gerNi");

int main() {
    window.setFramerateLimit(fps);

    Camera camera(0, 0, 0, camera_width, camera_height, camera_distance,
                   camera_angle_speed, camera_speed);
    vector<Cube> cubes{Cube(0,0,100,20)};

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(200, 200), sf::Color::Red),
        sf::Vertex(sf::Vector2f(400, 300), sf::Color::Red)
    };
    Render render=Render();
    sf::Vector2i mousePos;
    while (window.isOpen())
    {
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

        window.clear(sf::Color::Black);
        render.render_points(window, cubes[0].points, camera);
        render.render_edges(window,cubes[0].edges, camera);
        window.display();
    }
}