#include <SFML/Graphics.hpp>
#include <vector>

class Render {
public:
    int point_radius;
    Render(int point_radius = 5) : point_radius(point_radius) {}
    void render_points(sf::RenderWindow& window, vector<Point> points, Camera camera) {
        for (Point point : points) {
            render_point(window, point, camera);
        }
    }
    void render_point(sf::RenderWindow& window, Point point, Camera camera) {
        vector<float> screen_point = camera.blit_point({point.x, point.y, point.z});
        if (screen_point[0] == -1 && screen_point[1] == -1) {
            return; // Skip points that are not visible
        }
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(screen_point[0], screen_point[1]);
        window.draw(circle);
    }
    void render_edges(sf::RenderWindow& window, vector<pair<Point,Point>> edges, Camera camera) {
        for (pair<Point,Point> edge : edges) {
            render_edge(window, edge, camera);
        }
    }
    void render_edge(sf::RenderWindow& window, pair<Point,Point> edge, Camera camera) {
        Point point1=edge.first;
        Point point2=edge.second;
        vector<float> screen_point1 = camera.blit_point({point1.x, point1.y, point1.z});
        vector<float> screen_point2 = camera.blit_point({point2.x, point2.y, point2.z});
        if ((screen_point1[0] == -1 && screen_point1[1] == -1) or (screen_point2[0] == -1 && screen_point2[1] == -1)) {
            return; // Skip points that are not visible
        }
        if (screen_point1[0]<0 or screen_point1[0]>screen_width or screen_point1[1]<0 or screen_point1[1]>screen_height) {
            if (screen_point2[0]<0 or screen_point2[0]>screen_width or screen_point2[1]<0 or screen_point2[1]>screen_height) {
                return; // Skip points that are not visible
            }
        }
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f((int)screen_point1[0], (int)screen_point1[1]), sf::Color::Red),
            sf::Vertex(sf::Vector2f((int)screen_point2[0], (int)screen_point2[1]), sf::Color::Red)
        };
        cout<<line[0].position.x<<" "<<line[0].position.y<<" "<<line[1].position.x<<" "<<line[1].position.y<<endl;
        window.draw(line, 2, sf::Lines);
    }
};