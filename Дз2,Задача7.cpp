#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

int main() {

    double v0=50.0;
    double g=9.8;
    double dt=1.0;

    std::vector<double> times;
    std::vector<double> heights;

    for (double t=0.0;t<=1000;t+=dt) {

        double h=v0*t-0.5*g*t*t;

        times.push_back(t);
        heights.push_back(h);

        if (h<0)
        {
            break;
        }
    }

    auto it=std::find_if(heights.begin(),heights.end(),[](double h){
        return h<=0.0;
    });

    if (it==heights.end())
    {
        std::cout << "Падения не было в заданном диапазоне" << std::endl;
    }
    else
    {
        size_t idx=std::distance(heights.begin(),it);
        double t_fall=times[idx];

        std::cout << std::fixed << std::setprecision(1);
        std::cout << "Момент падения: " << t_fall << " с" << std::endl;
        std::cout << "Высота: " << heights[idx] << " м" << std::endl;
    }

    return 0;
}
