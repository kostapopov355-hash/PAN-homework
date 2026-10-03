#include <iostream>
#include <cmath>



int main() {

    float m;
    float S;
    float V;
    float po;
    float CL;
    float h;
    float T_min;
    float T_max;
    float dT;
    float ay;
    float t;
    float mint = 100000000000;
    float optimalT = 0;
    float L;


    

    std::cout << "Введите массу самолёта: ";
    std::cin >> m;
    std::cout << std::endl;

    std::cout << "Введите площадь крыла: ";
    std::cin >> S;
    std::cout << std::endl;

    std::cout << "Введите скорость самолёта: ";
    std::cin >> V;
    std::cout << std::endl;

    std::cout << "Введите плотность воздуха: ";
    std::cin >> po;
    std::cout << std::endl;

    std::cout << "Введите коэффициент подъёмной силы: ";
    std::cin >> CL;
    std::cout << std::endl;

    std::cout << "Введите заданную высоту: ";
    std::cin >> h;
    std::cout << std::endl;

    std::cout << "Введите минимальную тягу: ";
    std::cin >> T_min;
    std::cout << std::endl;

    std::cout << "Введите максимальную тягу: ";
    std::cin >> T_max;
    std::cout << std::endl;

    std::cout << "Введите дельту тяги: ";
    std::cin >> dT;
    std::cout << std::endl;

    L = po*V*V*S*CL/2;

    for (float T = T_min; T <= T_max; T = T + dT)
        {
        ay = (L-m*9.81)/m;
        t = sqrt(2*h/ay);
        std::cout << "Тяга = " << T;
        std::cout << ", вертикальное ускорение = " << ay;
        std::cout << ", время = " << t << " секунд";
        std::cout << std::endl;

        if (t < mint)
        {
            mint = t;
            optimalT = T;
        }
        }

    std::cout << std::endl;
    std::cout << "Оптимальная тяга = " << optimalT << std::endl;
    std::cout << "Минимальное время набора высоты = " << mint << " секунд" << std::endl;

    return 0;
}
