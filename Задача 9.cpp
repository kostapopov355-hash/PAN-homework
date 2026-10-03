#include <iostream>
\


struct Aircraft 
{
    float m;
    float S;
    float T;
    float V;
    float po;
    float CL;
    float CD;
    float L;
    float D;
    float a;
};

int main() {

    int N;
    std::cout << "Введите количество самолётов: ";
    std::cin >> N;
    std::cout << std::endl;

    Aircraft aircraft[10000];

    for (int i = 0; i < N; i++) 
    {
        std::cout << "Введите массу самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].m;
        std::cout << std::endl;
        
        std::cout << "Введите площадь крыла самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].S;
        std::cout << std::endl;
        
        std::cout << "Введите тягу самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].T;
        std::cout << std::endl;
        
        std::cout << "Введите скорость самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].V;
        std::cout << std::endl;
        
        std::cout << "Введите плотность воздуха для самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].po;
        std::cout << std::endl;
        
        std::cout << "Введите коэффициент подъёмной силы самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].CL;
        std::cout << std::endl;
        
        std::cout << "Введите коэффициент сопротивления самолёта №" << i+1 << ": ";
        std::cin >> aircraft[i].CD;
        
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++)
    {

        aircraft[i].L = aircraft[i].po * aircraft[i].V * aircraft[i].V *
                        aircraft[i].S * aircraft[i].CL/2;

        aircraft[i].D = aircraft[i].po * aircraft[i].V * aircraft[i].V *
                        aircraft[i].S * aircraft[i].CD/2;

        aircraft[i].a = (aircraft[i].T - aircraft[i].D)/aircraft[i].m;

        std::cout << "Самолёт №" << i+1 << std::endl;
        std::cout << "Подъёмная сила = " << aircraft[i].L << std::endl;
        std::cout << "Сопротивление = " << aircraft[i].D << std::endl;
        std::cout << "Ускорение = " << aircraft[i].a << std::endl;
    }
    int best = 0;
    for (int i = 1; i < N; i++) 
    {
        if (aircraft[i].a > aircraft[best].a)
        {
            best = i;
        }
    }

    std::cout << "Наибольшее ускорение имеет самолёт №"
              << best+1 << std::endl;

    return 0;
}
