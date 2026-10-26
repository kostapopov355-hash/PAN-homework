#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<double> heights={0.0,5.2,12.5,8.7,20.0,3.1,15.4};

    auto new_end=std::remove_if(heights.begin(),heights.end(),[](double h){
        return h<10.0;
    });

    heights.erase(new_end,heights.end());

    if (heights.empty())
    {
        std::cout << "Вектор пуст" << std::endl;
        return 0;
    }

    std::cout << "Оставшиеся высоты:" << std::endl;

    for (int i=0;i<heights.size();i++) {
        std::cout << heights[i] << std::endl;
    }

    return 0;
}
