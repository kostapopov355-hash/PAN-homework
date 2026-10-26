#include <iostream>
#include <vector>
#include <iomanip>

struct Point {
    double x,y,z;
};

class Rocket {
private:
    double x,y,z;
    double vx,vy,vz;

public:
    Rocket(double x0,double vx0,double vy0,double vz0) {
        x=x0;
        y=0.0;
        z=0.0;
        vx=vx0;
        vy=vy0;
        vz=vz0;
    }

    void updatePosition(double dt) {
        x+=vx*dt;
        y+=vy*dt;
        z+=vz*dt;
    }

    void changeVelocity(double vx_new,double vy_new,double vz_new) {
        vx=vx_new;
        vy=vy_new;
        vz=vz_new;
    }

    Point getPosition() {
        return {x,y,z};
    }
};

int main() {

    double dt=1.0;
    double T=10.0;

    std::vector<Rocket> squad;
    squad.reserve(5);

    squad.emplace_back(1000,10,0,50);
    squad.emplace_back(900,15,-5,40);
    squad.emplace_back(800,20,5,30);
    squad.emplace_back(700,25,-10,20);
    squad.emplace_back(600,30,10,10);

    std::vector<std::vector<Point>> trajectories(5);

    for (double t=0.0;t<=T;t+=dt) {

        for (size_t i=0;i<squad.size();++i) {

            Point p=squad[i].getPosition();
            trajectories[i].push_back(p);

            if (t<T)
            {
                squad[i].updatePosition(dt);
            }
        }
    }

    std::cout << std::fixed << std::setprecision(1);

    std::cout << std::setw(10) << "Ракета"
              << std::setw(15) << "X"
              << std::setw(15) << "Y"
              << std::setw(15) << "Z" << std::endl;

    for (size_t i=0;i<squad.size();++i) {

        Point p=squad[i].getPosition();

        std::cout << std::setw(10) << i+1
                  << std::setw(15) << p.x
                  << std::setw(15) << p.y
                  << std::setw(15) << p.z
                  << std::endl;
    }

    return 0;
}
