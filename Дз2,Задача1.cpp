#include <iostream>
#include <vector>
#include <iomanip>

int main() {

    double v0=50.0;
    double g=9.8;
    double dt=1.0;

    if (v0<=0)
    {
        std::cout << "Ошибка: начальная скорость должна быть больше нуля";
        return 0;
    }

    std::vector<double> times;
    std::vector<double> heights;

    times.reserve((int)(v0*2/g/dt));
    heights.reserve((int)(v0*2/g/dt));

    for (double t=0.0; t<=1000; t+=dt) {

        double h=v0*t-0.5*g*t*t;

        if (h<0)
        {
            break;
        }

        times.push_back(t);
        heights.push_back(h);
    }

    std::cout << std::setw(10) << "Время"
              << std::setw(30) << "Высота" << std::endl;

    for (int i=0; i<times.size(); i++) {

        std::cout << std::fixed << std::setprecision(1)
                  << std::setw(0) << times[i]
                  << std::setw(25) << heights[i]
                  << std::endl;
    }

    return 0;
}
