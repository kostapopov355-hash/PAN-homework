#include <iostream>

class Gyroscope {
private:
    double angularVelocity;
    bool calibrationRequired;

public:
    Gyroscope(double velocity,bool calibration) {
        angularVelocity=velocity;
        calibrationRequired=calibration;
    }

    void calibrate() {
        calibrationRequired=false;
    }

    void printStatus() {
        std::cout << "Скорость: " << angularVelocity << " °/с | ";

        if (calibrationRequired)
        {
            std::cout << "Калибровка требуется" << std::endl;
        }
        else
        {
            std::cout << "Калибровка не требуется" << std::endl;
        }
    }
};

int main() {

    Gyroscope g1(120.5,true);

    g1.printStatus();

    g1.calibrate();

    g1.printStatus();

    return 0;
}
