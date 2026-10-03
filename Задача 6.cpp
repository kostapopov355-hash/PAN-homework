#include <iostream>



int main() {

    float V[5];
    float po[5];
    float S;
    float CL;
    float L[5];

    std::cout << "Введите площадь крыла: ";
    std::cin >> S;
    std::cout << std::endl;

    std::cout << "Введите коэффициент подъёмной силы: ";
    std::cin >> CL;
    std::cout << std::endl;


    for (int i = 0; i < 5; i++) {
        std::cout << "Введите скорость самолёта на шаге №" << i+1 << std::endl;
        std::cin >> V[i];
        std::cout << std::endl;
    }


    for (int i = 0; i < 5; i++) {
        std::cout << "Введите плотность воздуха на шаге №" << i+1 << std::endl;
        std::cin >> po[i];
        std::cout << std::endl;
    }


    for (int i = 0; i < 5; i++) {
        L[i] = po[i]*V[i]*V[i]*S*CL/2;
    }


    std::cout << "Шаг\tСкорость\tПлотность\tПодъёмная сила" << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << i+1 << "\t";
        std::cout << V[i] << "\t\t\t";
        std::cout << po[i] << "\t\t\t";
        std::cout << L[i] << std::endl;
    }


    return 0;
}
