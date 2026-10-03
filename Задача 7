#include <iostream>




int main() {

    float m;
    float T;
    float L;
    float D;
    float a;

    std::cout << "Введите массу самолёта: ";
    std::cin >> m;
    std::cout << std::endl;

    std::cout << "Введите тягу: ";
    std::cin >> T;
    std::cout << std::endl;

    std::cout << "Введите сопротивление: ";
    std::cin >> D;
    std::cout << std::endl;

    a = (T-D)/m;

    std::cout << "Ускорение самолёта = " << a << " м/с^2" << std::endl;
    if (a > 0.5)
    {
        std::cout << "Режим полёта: набор высоты";
    }
    else if (a >= 0 and a <= 0.5)
    {
        std::cout << "Режим полёта: горизонтальный полёт";
    }
    else
    {
        std::cout << "Режим полёта: снижение";
    }

    return 0;
}
