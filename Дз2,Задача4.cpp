#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

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

    if (velocities.empty())
    {
        std::cout << "Данных нет" << std::endl;
        return 0;
    }

    double sum=std::accumulate(velocities.begin(),velocities.end(),0.0);
    double avg=sum/velocities.size();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Средняя скорость: " << avg << " м/с" << std::endl;

    return 0;
}
