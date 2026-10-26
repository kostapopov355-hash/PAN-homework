#include <iostream>
#include <vector>
#include <iomanip>

int main() {

    std::vector<double> h={0.0,5.2,11.5,9.7,21.0,18.1,30.4,28.6};

    size_t n=h.size();

    std::vector<double> smoothed(h.size());

    if (h.empty())
    {
        std::cout << "Вектор пуст" << std::endl;
        return 0;
    }

    smoothed[0]=h[0];
    smoothed[n-1]=h[n-1];

    for (size_t i=1;i+1<n;++i) {
        smoothed[i]=(h[i-1]+h[i]+h[i+1])/3.0;
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::setw(15) << "Исходная"
              << std::setw(30) << "Сглаженная" << std::endl;

    for (size_t i=0;i<n;++i) {
        std::cout << std::setw(10) << h[i]
                  << std::setw(20) << smoothed[i]
                  << std::endl;
    }

    return 0;
}
