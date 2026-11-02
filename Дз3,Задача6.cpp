#include <iostream>

class RocketStage {
private:
    double thrust;
    double burnTime;
    double mass;

public:
    RocketStage(double T,double time,double m) {
        thrust=T;
        burnTime=time;
        mass=m;
    }

    double getDeltaV() {
        return thrust*burnTime/mass;
    }

    void printInfo() {
        std::cout << "Тяга: " << thrust << " Н"
                  << " | Время работы: " << burnTime << " с"
                  << " | Масса: " << mass << " кг"
                  << " | Приращение скорости: " << getDeltaV() << " м/с" << std::endl;
    }
};

int main() {

    RocketStage stage1(50000,60,10000);
    RocketStage stage2(30000,40,5000);
    RocketStage stage3(15000,30,2000);

    double totalDeltaV=stage1.getDeltaV()+stage2.getDeltaV()+stage3.getDeltaV();

    stage1.printInfo();
    stage2.printInfo();
    stage3.printInfo();

    std::cout << std::endl;
    std::cout << "Итоговая скорость ракеты: " << totalDeltaV << " м/с" << std::endl;

    return 0;
}
