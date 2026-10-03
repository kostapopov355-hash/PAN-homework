#include <iostream>
#include <cmath>



struct Aircraft
{
    float m;
    float T;
    float CL;
    float CD;
    float V;
    float S;
    float L;
    float D;
    float ay;
    float t;
};

int main() {

    float po;
    float h;
    Aircraft beep;
    std::cout << "Введите плотность воздуха: ";
    std::cin >> po;
    std::cout << std::endl;

    std::cout << "Введите заданную высоту: ";
    std::cin >> h;
    std::cout << std::endl;

    Aircraft aircraft[3];

    for (int i = 0; i < 3; i++) 
    {

        std::cout << "Введите массу самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].m;
        std::cout << std::endl;

        std::cout << "Введите тягу самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].T;
        std::cout << std::endl;

        std::cout << "Введите коэффициент подъёмной силы самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].CL;
        std::cout << std::endl;

        std::cout << "Введите коэффициент сопротивления самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].CD;
        std::cout << std::endl;

        std::cout << "Введите скорость самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].V;
        std::cout << std::endl;

        std::cout << "Введите площадь крыла самолёта №" << i + 1 << ": ";
        std::cin >> aircraft[i].S;
        std::cout << std::endl;
    }

    for (int i = 0; i < 3; i++)
        {
        aircraft[i].L = po * aircraft[i].V * aircraft[i].V *
                        aircraft[i].S * aircraft[i].CL / 2;

        aircraft[i].D = po * aircraft[i].V * aircraft[i].V *
                        aircraft[i].S * aircraft[i].CD / 2;

        aircraft[i].ay = (aircraft[i].L - aircraft[i].m * 9.81)
                        / aircraft[i].m;

        aircraft[i].t = sqrt(2 * h / aircraft[i].ay);
    }
    
    for (int i = 0; i < 3; i++) 
    {
        for (int j = i + 1; j < 3; j++) 
        {

            if (aircraft[i].t > aircraft[j].t) 
            {
                beep = aircraft[i];
                aircraft[i] = aircraft[j];
                aircraft[j] = beep;
            }
        }
    }

    std::cout << "Результаты по времени набора высоты:" << std::endl;

    for (int i = 0; i < 3; i++) 
    {
        std::cout << "Самолёт №" << i + 1;
        std::cout << ": вертикальное ускорение = ";
        std::cout << aircraft[i].ay;
        std::cout << std::endl;
        std::cout << " время набора = ";
        std::cout << aircraft[i].t;
        std::cout << " секунд";
        std::cout << std::endl;
    }

    return 0;
}
