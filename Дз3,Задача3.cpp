#include <iostream>
#include <iomanip>

class Engine {
private:
    double thrust;
    double fuelFlow;

public:
    Engine(double T,double F) {
        thrust=T;
        fuelFlow=F;
    }

    double getSpecificImpulse() {
        return thrust/(fuelFlow*9.81);
    }

    void printInfo() {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Тяга: " << thrust << " Н"
                  << " | Расход: " << fuelFlow << " кг/с"
                  << " | Удельный импульс: " << getSpecificImpulse() << " с" << std::endl;
    }
};

int main() {

    Engine e1(5000,2.5);

    e1.printInfo();

    return 0;
}
