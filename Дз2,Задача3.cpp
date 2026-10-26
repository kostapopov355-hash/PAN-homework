#include <iostream>
#include <vector>
#include <iomanip>

int main() {

    double v0=50.0;
    double g=9.8;
    double dt=1.0;
    double t_max=v0*2/g;

    if (v0<=0)
    {
        std::cout << "Ошибка: начальная скорость должна быть больше нуля";
        return 0;
    }

    std::vector<double> times;
    std::vector<double> velocities;

    for (double t=0.0; t<=t_max; t+=dt) {

        double v=v0-g*t;

        times.push_back(t);
        velocities.push_back(v);
    }

    std::cout << std::setw(10) << "Время"
              << std::setw(30) << "Скорость" << std::endl;

    for (int i=0; i<times.size(); i++) {

        std::cout << std::fixed << std::setprecision(1)
                  << std::setw(0) << times[i]
                  << std::setw(20) << velocities[i]
                  << std::endl;
    }

    return 0;
}
