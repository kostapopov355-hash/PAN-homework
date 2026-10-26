#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>

int main() {

    double v01=50.0;
    double v02=40.0;
    double g=9.8;
    double dt=1.0;
    double t_max=1000.0;

    std::vector<double> times1;
    std::vector<double> heights1;
    std::vector<double> times2;
    std::vector<double> heights2;

    for (double t=0.0;t<=t_max;t+=dt) {

        double h1=v01*t-0.5*g*t*t;
        double h2=v02*t-0.5*g*t*t;

        times1.push_back(t);
        heights1.push_back(h1);

        times2.push_back(t);
        heights2.push_back(h2);

        if (h1<0&&h2<0)
        {
            break;
        }
    }

    if (heights1.empty()||heights2.empty())
    {
        std::cout << "Нет данных для сравнения" << std::endl;
        return 0;
    }

    auto it1=std::max_element(heights1.begin(),heights1.end());
    auto it2=std::max_element(heights2.begin(),heights2.end());

    size_t idx_max1=std::distance(heights1.begin(),it1);
    size_t idx_max2=std::distance(heights2.begin(),it2);

    double max1=heights1[idx_max1];
    double max2=heights2[idx_max2];

    double t_max1=times1[idx_max1];
    double t_max2=times2[idx_max2];

    auto fall1=std::find_if(heights1.begin(),heights1.end(),[](double h){
        return h<=0.0;
    });

    auto fall2=std::find_if(heights2.begin(),heights2.end(),[](double h){
        return h<=0.0;
    });

    double t_fall1=-1.0;
    double t_fall2=-1.0;

    if (fall1!=heights1.end())
    {
        size_t idx=std::distance(heights1.begin(),fall1);
        t_fall1=times1[idx];
    }

    if (fall2!=heights2.end())
    {
        size_t idx=std::distance(heights2.begin(),fall2);
        t_fall2=times2[idx];
    }

    std::cout << std::fixed << std::setprecision(1);

    std::cout << std::setw(10) << "Ракета"
              << std::setw(30) << "М. высота"
              << std::setw(30) << "Время м"
              << std::setw(25) << "Время п" << std::endl;

    std::cout << std::setw(10) << "1"
              << std::setw(20) << max1
              << std::setw(20) << t_max1
              << std::setw(20);

    if (t_fall1<0)
        std::cout << "В воздухе";
    else
        std::cout << t_fall1;

    std::cout << std::endl;

    std::cout << std::setw(10) << "2"
              << std::setw(20) << max2
              << std::setw(20) << t_max2
              << std::setw(20);

    if (t_fall2<0)
        std::cout << "В воздухе";
    else
        std::cout << t_fall2;

    std::cout << std::endl << std::endl;

    if (max1>max2)
        std::cout << "Выше поднялась ракета 1" << std::endl;
    else if (max2>max1)
        std::cout << "Выше поднялась ракета 2" << std::endl;
    else
        std::cout << "Ракеты поднялись на одинаковую высоту" << std::endl;

    if (t_fall1<0&&t_fall2<0)
        std::cout << "Обе ракеты всё ещё в воздухе" << std::endl;
    else if (t_fall1<0)
        std::cout << "Ракета 1 дольше в воздухе" << std::endl;
    else if (t_fall2<0)
        std::cout << "Ракета 2 дольше в воздухе" << std::endl;
    else if (t_fall1>t_fall2)
        std::cout << "Ракета 1 дольше в воздухе" << std::endl;
    else if (t_fall2>t_fall1)
        std::cout << "Ракета 2 дольше в воздухе" << std::endl;
    else
        std::cout << "Ракеты находились в воздухе одинаковое время" << std::endl;

    return 0;
}
