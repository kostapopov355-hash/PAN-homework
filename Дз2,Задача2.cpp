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

    std::cout << std::setw(0) << "Время"
              << std::setw(25) << "Высота" << std::endl;

    for (int i = 0; i < times.size(); i++) {

        std::cout << std::fixed << std::setprecision(1)
                  << std::setw(10) << times[i]
                  << std::setw(30) << heights[i]
                  << std::endl;
    }

    if (heights.empty())
    {
        std::cout << "Данных нет" << std::endl;
        return 0;
    }

    size_t idx_max = 0;

    for (size_t i=1; i<heights.size(); ++i) {

        if (heights[i]>heights[idx_max])
        {
            idx_max=i;
        }
    }

    std::cout << std::endl;
    std::cout << "Максимальная высота: " << heights[idx_max] << std::endl;
    std::cout << "Время достижения максимальной высоты: " << times[idx_max] << " с" << std::endl;

    return 0;
}
