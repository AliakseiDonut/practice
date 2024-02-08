#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Polygon {
public:
    Polygon(const std::vector<std::pair<double, double>>& vertices)
        : vertices(vertices) {}

    virtual double area() = 0;

    void printVertices() const {
        std::cout << "Vertices: ";
        for (const auto& vertex : vertices) {
            std::cout << "(" << vertex.first << ", " << vertex.second << ") ";
        }
        std::cout << std::endl;
    }

protected:
    std::vector<std::pair<double, double>> vertices;
};

class Triangle : public Polygon {
public:
    Triangle(const std::vector<std::pair<double, double>>& vertices)
        : Polygon(vertices) {}

    double area() override {
        return 0.5 * std::abs(vertices[0].first * (vertices[1].second - vertices[2].second) +
            vertices[1].first * (vertices[2].second - vertices[0].second) +
            vertices[2].first * (vertices[0].second - vertices[1].second));
    }
};

class NGon : public Polygon {
public:
    NGon(const std::vector<std::pair<double, double>>& vertices)
        : Polygon(vertices) {}

    double area() override {
        double area = 0;
        for (int i = 0; i < vertices.size(); i++) {
            int j = (i + 1) % vertices.size();
            area += vertices[i].first * vertices[j].second - vertices[j].first * vertices[i].second;
        }
        return 0.5 * std::abs(area);
    }
};

int main() {
    srand(time(0));
    int numPolygons;
    std::cout << "Enter the number of polygons: ";
    std::cin >> numPolygons;

    std::vector<Polygon*> polygons;
    for (int p = 0; p < numPolygons; p++) {
        int numSides = rand() % 4 + 3;
        std::vector<std::pair<double, double>> vertices;
        for (int s = 0; s < numSides; s++) {
            double x = rand() % 10;
            double y = rand() % 10;
            vertices.push_back(std::make_pair(x, y));
        }
        if (numSides == 3) {
            polygons.push_back(new Triangle(vertices));
        }
        else {
            polygons.push_back(new NGon(vertices));
        }
    }

    double maxArea = 0;
    int maxAreaIndex = -1;

    for (int i = 0; i < numPolygons; i++) {
        std::cout << "Polygon " << i + 1 << ":" << std::endl;
        polygons[i]->printVertices();
        double currentArea = polygons[i]->area();
        std::cout << "Area: " << currentArea << std::endl;
        if (currentArea > maxArea) {
            maxArea = currentArea;
            maxAreaIndex = i;
        }
        std::cout << std::endl;
    }

    if (maxAreaIndex != -1) {
        std::cout << "Polygon with the largest area is polygon " << maxAreaIndex + 1 << std::endl;
    }
    else {
        std::cout << "No polygons were entered." << std::endl;
    }

    for (int i = 0; i < numPolygons; i++) {
        delete polygons[i];
    }

    return 0;
}