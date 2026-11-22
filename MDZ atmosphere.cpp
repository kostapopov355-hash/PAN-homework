#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Модель стандартной атмосферы по ГОСТ 4401-81 (тропосфера, H <= 11000 м)
class StandardAtmosphere {
private:
    double tempSeaLevel;      // Температура на уровне моря T0, К
    double pressSeaLevel;     // Давление на уровне моря p0, Па
    double gravityAcc;        // Ускорение свободного падения g0, м/с^2
    double tempGradient;      // Температурный градиент L, К/м
    double gasConst;          // Удельная газовая постоянная воздуха R, Дж/(кг*К)
    double adiabaticIndex;    // Показатель адиабаты k

public:
    StandardAtmosphere()
        : tempSeaLevel(288.15), pressSeaLevel(101325.0), gravityAcc(9.80665),
          tempGradient(0.0065), gasConst(287.05287), adiabaticIndex(1.4) {}

    // Температура воздуха на высоте H, К
    double calcTemperature(double H) const {
        return tempSeaLevel - tempGradient * H;
    }

    // Атмосферное давление на высоте H, Па
    double calcPressure(double H) const {
        double T = calcTemperature(H);
        return pressSeaLevel * pow(T / tempSeaLevel, gravityAcc / (tempGradient * gasConst));
    }

    // Плотность воздуха на высоте H, кг/м^3
    double calcDensity(double H) const {
        return calcPressure(H) / (gasConst * calcTemperature(H));
    }

    // Местная скорость звука на высоте H, м/с
    double calcSoundSpeed(double H) const {
        return sqrt(adiabaticIndex * gasConst * calcTemperature(H));
    }
};
