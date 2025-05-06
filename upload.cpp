#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

struct Vec3 { float x, y, z; };
class Object_uploader {
public:
    Object_uploader() {
        // Constructor
    };
    vector<pair<Point,Point>> upload_obj_edges(string filename) {
        std::ifstream file(filename);
        std::string line;
        vector<Point> vertices;
        vector<pair<Point,Point>> edges;
        std::unordered_set<std::string> unique_edges;
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return edges;
        }
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                Point v;
                iss >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            }
            else if (prefix == "f") {
                vector<int> face;
                string vertex;
                while (iss >> vertex) {
                    stringstream vs(vertex);
                    string index;
                    getline(vs, index, '/'); // only vertex index
                    face.push_back(stoi(index));
                }
                for (int i=0; i < face.size(); i++) {
                    int v1 = face[i]-1;
                    int v2 = face[(i + 1) % face.size()] - 1;
                    if (unique_edges.count(to_string(v1)+"/"+to_string(v2)) == 0) {
                        unique_edges.insert(to_string(v1)+"/"+to_string(v2));
                        unique_edges.insert(to_string(v2)+"/"+to_string(v1));
                    } else {
                        continue;
                    }
                    Point p1 = {vertices[v1].y, -vertices[v1].z, vertices[v1].x};
                    Point p2 = {vertices[v2].y, -vertices[v2].z, vertices[v2].x};
                    edges.push_back({p1, p2});
                }
            }
        }
        return edges;
    };

};