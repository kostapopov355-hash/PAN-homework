#include <iostream>
#include <cmath>

int main() {


      
float po;



    
float h;
std::cout << "Введите необходимую для достижения высоту: ";
std::cin >> h;
std::cout << std::endl;

std::cout << "Введите сопротивление воздуха: ";
std::cin >> po;
std::cout << std::endl;
    
float m[3];
float S[3];
float T[3];
float CD[3];
float CL[3];

    
float V[3];

float L[3];
float D[3];
float a[3];
float t[3];

for (int i = 0; i <3; i++) {
    std::cout << "Введите массу самолёта №" << i+1 << std::endl;
    std::cin >> m[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    std::cout << "Введите скорость самолёта №" << i+1 << std::endl;
    std::cin >> V[i];
    std::cout << std::endl;
}


for (int i = 0; i <3; i++) {
    std::cout << "Введите площадь крыла самолёта №" << i+1 << std::endl;
    std::cin >> S[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    std::cout << "Введите тягу самолёта №" << i+1 << std::endl;    
    std::cin >> T[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    std::cout << "Введите коэффициент сопротивления самолёта №" << i+1 << std::endl;
    std::cin >> CD[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    std::cout << "Введите коэффициент подъёмной силы самолёта №" << i+1 << std::endl;    
    std::cin >> CL[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    L[i] = po*V[i]*S[i]*CL[i]/2;
    std::cout << "Подъёмная сила самолёта №" << i+1 << " = "<< L[i];
    std::cout << std::endl;
}

for (int i = 0; i <3; i++) {
    D[i] = po*V[i]*S[i]*CD[i]/2;
    std::cout << "Сопротивление самолёта №" << i+1 << " = " << D[i];
    std::cout << std::endl;
    }
for (int i = 0; i <3; i++) {
    a[i] = (T[i] - D[i])/m[i];
    std::cout << "Ускорение самолёта №" << i+1 << " = " << a[i];
    std::cout << std::endl;
    }

for (int i = 0; i <3; i++) {
    t[i] = sqrt(2*h/((L[i] - m[i]*9.81)/m[i]));
    std::cout << "Время подъёма на заданную высоту самолёта №" << i+1 << " = " << t[i];
    std::cout << std::endl;
    }

if (t[0]> t[1] and t[0]> t[2])
    {
        std::cout << "Быстрее всех заданную высоту наберёт самолёт №1" << std::endl;
    }

if (t[1]> t[2] and t[1]> t[0])
    {
        std::cout << "Быстрее всех заданную высоту наберёт самолёт №2" << std::endl;
    }
if (t[2]>t[1] and t[2]>t[0])
    {
        std::cout << "Быстрее всех заданную высоту наберёт самолёт №3" << std::endl;
    }
    
    return 0;
}
