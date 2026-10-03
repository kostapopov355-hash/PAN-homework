#include <iostream>
#include <cmath>

int main() {
    
    float m;
    float L;
    float D;
    float T;
    float a;
    float ay;
    float t;
    std::cout << "Введите m: ";
    std::cin >> m;
    std::cout << "Введите L: ";
    std::cin >> L;
    std::cout << "Введите D: ";    
    std::cin >> D;
    std::cout << "Введите T: ";    
    std::cin >> T;
    a = (T-D)/m;
    ay = (L-m*9.81)/m;

    std::cout << "Ускорение по направлению движения самолёта: " << a << std::endl;
    std::cout << "Вертикальное ускорение самолёта: " << ay << std::endl;

    float h;
    std::cout << "Введите h: ";
    std::cin >> h;
    t = sqrt(2*h/ay);
    std::cout << "Время необоходимое для достижения заданной высоты: " << t << " секунды" << std::endl;
        
    
    return 0;
}
