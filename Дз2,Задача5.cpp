#include <iostream>
#include <vector>
#include <iomanip>

struct Point {
    double x,y,z;
};

int main() {

    double vx=30.0;
    double vy=20.0;
    double vz=40.0;
    double dt=1.0;
    double t_max=10.0;

    double x=0.0;
    double y=0.0;
    double z=0.0;

    std::vector<Point> traj;
    traj.reserve((int)(t_max/dt)+1);

    for (double t=0.0;t<=t_max;t+=dt) {

        x=vx*t;
        y=vy*t;
        z=vz*t;

        traj.push_back({x,y,z});
    }

    std::cout << std::setw(10) << "Время"
              << std::setw(15) << "X"
              << std::setw(15) << "Y"
              << std::setw(15) << "Z" << std::endl;

    for (int i=0;i<traj.size();i++) {

        std::cout << std::fixed << std::setprecision(1)
                  << std::setw(10) << i*dt
                  << std::setw(15) << traj[i].x
                  << std::setw(15) << traj[i].y
                  << std::setw(15) << traj[i].z
                  << std::endl;
    }

    return 0;
}
