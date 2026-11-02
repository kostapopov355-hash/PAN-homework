#include <iostream>

class Sensor {
private:
    double signalStrength;
    bool isActive;

public:
    Sensor(double strength) {
        signalStrength=strength;
        isActive=true;
    }

    void activate() {
        isActive=true;
    }

    void deactivate() {
        isActive=false;
    }

    void setSignalStrength(double s) {
        if (s<0)
        {
            s=0;
        }

        signalStrength=s;
    }

    double getSignalStrength() {
        return signalStrength;
    }

    void printStatus() {
        if (isActive)
        {
            std::cout << "Датчик активен";
        }
        else
        {
            std::cout << "Датчик выключен";
        }

        std::cout << " | Сила сигнала: " << signalStrength << " дБ" << std::endl;
    }
};

int main() {

    Sensor s1(45.5);

    s1.printStatus();

    s1.setSignalStrength(-10);
    s1.printStatus();

    s1.deactivate();
    s1.printStatus();

    return 0;
}
