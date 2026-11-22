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
// ВТОРАЯ ЧАСТЬ

// Аэродинамическая модель самолета ТУ-154 (крейсерская конфигурация)
class AeroModelTU154 {
private:
    double wingArea;        // Площадь крыла S, м^2
    double liftZeroAlpha;   // Коэффициент подъемной силы при alpha = 0 (Cy0)
    double liftSlope;       // Производная подъемной силы по углу атаки (Cy^alpha), 1/град
    double maxLiftCoeff;    // Максимально допустимый коэффициент Cy_max
    double critAlpha;       // Критический угол атаки alpha_кр, град
    double zeroLiftDrag;    // Коэффициент лобового сопротивления при Cy = 0 (Cx0)
    double inducedFactor;   // Коэффициент индуктивного сопротивления (A)

public:
    AeroModelTU154()
        : wingArea(201.0), liftZeroAlpha(-0.22), liftSlope(0.10),
          maxLiftCoeff(1.30), critAlpha(20.0), zeroLiftDrag(0.025), inducedFactor(0.043) {}

    // Требуемый коэффициент Cy для горизонтального полета (Y = m * g)
    double getRequiredCy(double weightN, double density, double velocity) const {
        return weightN / (0.5 * density * velocity * velocity * wingArea);
    }

    // Коэффициент лобового сопротивления по параболе поляры: Cx = Cx0 + A * Cy^2
    double getCx(double cy) const {
        return zeroLiftDrag + inducedFactor * cy * cy;
    }

    // Сила лобового сопротивления X, Н
    double getDragForce(double cy, double density, double velocity) const {
        return getCx(cy) * 0.5 * density * velocity * velocity * wingArea;
    }

    // Угол атаки alpha (в градусах), соответствующий текущему Cy
    double getAlphaDeg(double cy) const {
        return (cy - liftZeroAlpha) / liftSlope;
    }

    // Проверка выхода на режим срыва потока
    bool checkStall(double cy) const {
        return (cy > maxLiftCoeff) || (getAlphaDeg(cy) > critAlpha);
    }
};

// ТРЕТЬЯ ЧАСТЬ


// Силовая установка ТУ-154: 3 х НК-8-2
class EngineModelNK8 {
private:
    double thrustPercent;   // Процент тяги от номинала по варианту (110%)
    double gravityAcc;      // Ускорение свободного падения g0, м/с^2

public:
    EngineModelNK8(double maxThrustPercent)
        : thrustPercent(maxThrustPercent), gravityAcc(9.80665) {}

    // Суммарная тяга трех двигателей в Ньютонах на высоте H и числе Маха M
    double getThrustNewton(double H, double M) const {
        // Опорная линейная зависимость номинальной тяги (3 двигателя) на H = 0 м
        double thrustGround = 265500.0 - 156810.0 * M;

        // Опорная линейная зависимость номинальной тяги (3 двигателя) на H = 11000 м
        double thrustTropo = 96600.0 - 7080.0 * M;

        // Линейная интерполяция тяги по высоте H
        double nominalThrust = thrustGround + (thrustTropo - thrustGround) * (H / 11000.0);

        return nominalThrust * (thrustPercent / 100.0);
    }

    // Удельный расход топлива Cp, кг топл. / (кгс * ч)
    double getSpecificFuel(double M) const {
        return 0.56 + 0.28 * M;
    }

    // Секундный расход топлива всеми тремя двигателями, кг/с
    double getFuelFlowRate(double H, double M) const {
        double thrustKgf = getThrustNewton(H, M) / gravityAcc;
        return thrustKgf * getSpecificFuel(M) / 3600.0;
    }
};



// ЧЕТВЁРТАЯ ЧАСТЬ

// Данные об одном элементарном участке траектории между двумя узлами сетки
struct ElementaryArc {
    bool isPossible = false;
    double deltaTime = 0.0;     // Время прохождения участка, с
    double deltaFuel = 0.0;     // Затраченное топливо, кг
    double deltaDist = 0.0;     // Горизонтальная дальность, м
    double alphaDeg = 0.0;      // Угол атаки на участке, град
    double thetaDeg = 0.0;      // Угол наклона траектории, град
};

// Класс оптимизации траектории методом динамического программирования
class TrajectoryOptimizer {
private:
    double aircraftMass;
    double g0;
    StandardAtmosphere atm;
    AeroModelTU154 aero;
    EngineModelNK8 engine;

    // Расчет параметров одного участка (0 - разгон, 1 - подъем, 2 - подъем-разгон)
    ElementaryArc calcElementaryArc(int mode, double V1, double H1, double V2, double H2) const {
        ElementaryArc arc;

        double V_mid = 0.5 * (V1 + V2);
        double H_mid = 0.5 * (H1 + H2);

        double rho = atm.calcDensity(H_mid);
        double sound = atm.calcSoundSpeed(H_mid);
        double mach = V_mid / sound;
        double thrust = engine.getThrustNewton(H_mid, mach);

        double weight = aircraftMass * g0;
        double cy = aero.getRequiredCy(weight, rho, V_mid);
        if (aero.checkStall(cy)) return arc;

        double drag = aero.getDragForce(cy, rho, V_mid);
        double sinTheta = 0.0;

        if (mode == 0) {
            // Горизонтальный разгон (H = const)
            double excessThrust = thrust - drag;
            if (excessThrust <= 0.0) return arc;
            arc.deltaTime = aircraftMass * (V2 - V1) / excessThrust;
            sinTheta = 0.0;
        } else if (mode == 1) {
            // Подъем на постоянной скорости (V = const)
            double excessThrust = thrust - drag;
            if (excessThrust <= 0.0) return arc;
            sinTheta = excessThrust / weight;
            if (sinTheta >= 1.0) return arc;
            arc.deltaTime = (H2 - H1) / (V_mid * sinTheta);
        } else {
            // Совмещенный подъем с разгоном
            double K = (H2 - H1) / (V2 - V1);
            sinTheta = K * (thrust - drag) / (aircraftMass * (V_mid + K * g0));
            if (sinTheta <= 0.0 || sinTheta >= 1.0) return arc;
            double excessThrust = thrust - drag - weight * sinTheta;
            if (excessThrust <= 0.0) return arc;
            arc.deltaTime = aircraftMass * (V2 - V1) / excessThrust;
        }

        double cosTheta = sqrt(max(0.0, 1.0 - sinTheta * sinTheta));
        arc.deltaFuel = engine.getFuelFlowRate(H_mid, mach) * arc.deltaTime;
        arc.deltaDist = V_mid * cosTheta * arc.deltaTime;
        arc.alphaDeg = aero.getAlphaDeg(cy);
        arc.thetaDeg = asin(sinTheta) * 180.0 / 3.141592653589793;
        arc.isPossible = true;

        return arc;
    }

public:
    TrajectoryOptimizer(double massKg, double maxThrustPercent)
        : aircraftMass(massKg), g0(9.80665), engine(maxThrustPercent) {}

    void runOptimization(int gridN, double V0, double H0, double Vk, double Hk,
                         bool byFuel, const string& csvFilename) const {
        vector<double> V_nodes(gridN + 1), H_nodes(gridN + 1);
        for (int i = 0; i <= gridN; ++i) {
            V_nodes[i] = V0 + i * (Vk - V0) / gridN;
            H_nodes[i] = H0 + i * (Hk - H0) / gridN;
        }

        // Предварительный расчет всех возможных переходов по сетке
        vector<vector<ElementaryArc>> arcAccel(gridN + 1, vector<ElementaryArc>(gridN + 1));
        vector<vector<ElementaryArc>> arcClimb(gridN + 1, vector<ElementaryArc>(gridN + 1));
        vector<vector<ElementaryArc>> arcDiag(gridN + 1, vector<ElementaryArc>(gridN + 1));

        for (int i = 0; i <= gridN; ++i) {
            for (int j = 0; j <= gridN; ++j) {
                if (i < gridN) arcAccel[i][j] = calcElementaryArc(0, V_nodes[i], H_nodes[j], V_nodes[i + 1], H_nodes[j]);
                if (j < gridN) arcClimb[i][j] = calcElementaryArc(1, V_nodes[i], H_nodes[j], V_nodes[i], H_nodes[j + 1]);
                if (i < gridN && j < gridN) arcDiag[i][j] = calcElementaryArc(2, V_nodes[i], H_nodes[j], V_nodes[i + 1], H_nodes[j + 1]);
            }
        }

        const double INF = numeric_limits<double>::infinity();
        vector<vector<double>> bellmanCost(gridN + 1, vector<double>(gridN + 1, INF));
        vector<vector<int>> optimalDir(gridN + 1, vector<int>(gridN + 1, -1));
        bellmanCost[gridN][gridN] = 0.0;

        // Обратный ход метода динамического программирования (от финиша к старту)
        for (int diag = 2 * gridN - 1; diag >= 0; --diag) {
            int iMin = max(0, diag - gridN);
            int iMax = min(gridN, diag);
            for (int i = iMin; i <= iMax; ++i) {
                int j = diag - i;
                double bestVal = INF;
                int bestMode = -1;

                if (i < gridN && arcAccel[i][j].isPossible) {
                    double cost = (byFuel ? arcAccel[i][j].deltaFuel : arcAccel[i][j].deltaTime) + bellmanCost[i + 1][j];
                    if (cost < bestVal) { bestVal = cost; bestMode = 0; }
                }
                if (j < gridN && arcClimb[i][j].isPossible) {
                    double cost = (byFuel ? arcClimb[i][j].deltaFuel : arcClimb[i][j].deltaTime) + bellmanCost[i][j + 1];
                    if (cost < bestVal) { bestVal = cost; bestMode = 1; }
                }
                if (i < gridN && j < gridN && arcDiag[i][j].isPossible) {
                    double cost = (byFuel ? arcDiag[i][j].deltaFuel : arcDiag[i][j].deltaTime) + bellmanCost[i + 1][j + 1];
                    if (cost < bestVal) { bestVal = cost; bestMode = 2; }
                }

                bellmanCost[i][j] = bestVal;
                optimalDir[i][j] = bestMode;
            }
        }

        // Прямой проход: восстановление оптимальной траектории и вывод результатов
        ofstream csv(csvFilename);
        csv << "Step;Mode;V_kmh;H_m;Time_s;Fuel_kg;Dist_km;Alpha_deg;Theta_deg\n";
        csv << "0;Start;" << fixed << setprecision(2) << V0 * 3.6 << ";" << H0 << ";0.00;0.00;0.00;0.00;0.00\n";

        cout << "\n=====================================================================\n";
        cout << (byFuel ? "РЕЗУЛЬТАТ: МИНИМАЛЬНЫЙ РАСХОД ТОПЛИВА (lambda = 1)"
                        : "РЕЗУЛЬТАТ: МИНИМАЛЬНОЕ ВРЕМЯ ПОЛЕТА (lambda = 0)") << "\n";
        cout << "=====================================================================\n";
        cout << setw(4) << "Шаг" << setw(15) << "Манёвр" << setw(10) << "V, км/ч"
             << setw(9) << "H, м" << setw(10) << "t, с" << setw(11) << "Gт, кг"
             << setw(10) << "L, км" << setw(9) << "alpha" << "\n";

        int i = 0, j = 0, step = 0;
        double sumTime = 0.0, sumFuel = 0.0, sumDist = 0.0;

        while (i < gridN || j < gridN) {
            int dir = optimalDir[i][j];
            if (dir == -1) {
                cout << "Траектория не найдена из узла (" << i << ", " << j << ")\n";
                return;
            }

            ElementaryArc chosenArc;
            string name;
            if (dir == 0) {
                chosenArc = arcAccel[i][j];
                i++;
                name = "Разгон";
            } else if (dir == 1) {
                chosenArc = arcClimb[i][j];
                j++;
                name = "Подъем";
            } else {
                chosenArc = arcDiag[i][j];
                i++;
                j++;
                name = "Подъем-разгон";
            }

            step++;
            sumTime += chosenArc.deltaTime;
            sumFuel += chosenArc.deltaFuel;
            sumDist += chosenArc.deltaDist;

            cout << setw(4) << step << setw(15) << name
                 << setw(10) << fixed << setprecision(1) << V_nodes[i] * 3.6
                 << setw(9) << setprecision(0) << H_nodes[j]
                 << setw(10) << setprecision(1) << sumTime
                 << setw(11) << setprecision(1) << sumFuel
                 << setw(10) << setprecision(2) << sumDist / 1000.0
                 << setw(9) << setprecision(2) << chosenArc.alphaDeg << "\n";

            csv << step << ";" << name << ";"
                << fixed << setprecision(2) << V_nodes[i] * 3.6 << ";"
                << H_nodes[j] << ";" << sumTime << ";"
                << sumFuel << ";" << sumDist / 1000.0 << ";"
                << chosenArc.alphaDeg << ";" << chosenArc.thetaDeg << "\n";
        }

        csv.close();
        cout << "---------------------------------------------------------------------\n";
        cout << "ИТОГО: Время = " << fixed << setprecision(1) << sumTime << " с, "
             << "Топливо = " << sumFuel << " кг, "
             << "Дальность = " << setprecision(2) << sumDist / 1000.0 << " км\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Исходные данные Варианта 11: ТУ-154, Max P = 110%
    double massTU154 = 98000.0;
    double maxThrustPct = 110.0;
    double V0 = 330.0 / 3.6;    // 330 км/ч -> м/с
    double H0 = 500.0;          // 500 м
    double Vk = 900.0 / 3.6;    // 900 км/ч -> м/с
    double Hk = 8000.0;         // 8000 м
    int N = 15;                 // Число разбиений сетки (шаг dH = 500 м)

    TrajectoryOptimizer solver(massTU154, maxThrustPct);

    // 1. Оптимизация по минимальному времени (lambda = 0)
    solver.runOptimization(N, V0, H0, Vk, Hk, false, "var11_min_time.csv");

    // 2. Оптимизация по минимальному расходу топлива (lambda = 1)
    solver.runOptimization(N, V0, H0, Vk, Hk, true, "var11_min_fuel.csv");

    return 0;
}

