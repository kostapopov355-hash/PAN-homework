#include <iostream>
#include <vector>

class DroneFlight {
private:
    std::vector<double> x;
    std::vector<double> y;
    double totalDistance;

public:
    DroneFlight() {
        x.push_back(0);
        y.push_back(0);
        totalDistance=0;
    }

    void addPoint(double newX,double newY) {
        double dx=newX-x.back();
        double dy=newY-y.back();

        totalDistance+=dx*dx+dy*dy;

        x.push_back(newX);
        y.push_back(newY);
    }

    double getTotalDistance() {
        return totalDistance;
    }

    void printPath() {
        std::cout << "Точки маршрута:" << std::endl;

        for(int i=0;i<x.size();i++) {
            std::cout << "(" << x[i] << ", " << y[i] << ")" << std::endl;
        }
    }
};

int main() {

    DroneFlight d;

    d.addPoint(0,0);
    d.addPoint(3,4);
    d.addPoint(6,8);

    d.printPath();

    std::cout << "Пройдено: " << d.getTotalDistance() << "\n";

    return 0;
}
