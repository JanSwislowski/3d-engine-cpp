#include <SFML/Graphics.hpp>
#include <vector>

class Render {
public:
    int point_radius;
    vector<sf::Vertex> vertices;
    sf::Color lineColor = sf::Color::Red;
    Render(int point_radius = 5) : point_radius(point_radius) {}
    void render_points(sf::RenderWindow& window, vector<Point> points, Camera camera) {
        for (Point point : points) {
            render_point(window, point, camera);
        }
    }
    void reset_render() {
        vertices.clear();
        // vertices.reserve(100000 * 2);
    }
    void render_point(sf::RenderWindow& window, Point point, Camera camera) {
        Point2d screen_point = camera.blit_point(point);
        if (screen_point.x == -1 && screen_point.y == -1) {
            return; // Skip points that are not visible
        }
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(screen_point.x, screen_point.y);
        window.draw(circle);
    }
    void render_edges(sf::RenderWindow& window, vector<pair<Point,Point>> edges, Camera camera) {
        for (pair<Point,Point> edge : edges) {
            render_edge(window, edge, camera);
        }
        window.draw(&vertices[0], vertices.size(), sf::Lines);
    }
    void render_edge(sf::RenderWindow& window, pair<Point,Point> edge, Camera camera) {
        Point point1=edge.first;
        Point point2=edge.second;
        Point2d screen_point1 = camera.blit_point(point1);
        Point2d screen_point2 = camera.blit_point(point2);
        if ((screen_point1.x == -1 && screen_point1.y == -1) or (screen_point2.x == -1 && screen_point2.y == -1)) {
            return; // Skip points that are not visible
        }
        if (screen_point1.x<0 or screen_point1.x>screen_width or screen_point1.y<0 or screen_point1.y>screen_height) {
            if (screen_point2.x<0 or screen_point2.x>screen_width or screen_point2.y<0 or screen_point2.y>screen_height) {
                return; // Skip points that are not visible
            }
        }
        vertices.push_back(sf::Vertex(sf::Vector2f((int)screen_point1.x, (int)screen_point1.y), lineColor));
        vertices.push_back(sf::Vertex(sf::Vector2f((int)screen_point2.x, (int)screen_point2.y), lineColor));
        };
};