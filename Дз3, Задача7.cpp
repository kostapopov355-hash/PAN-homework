#include <iostream>
#include <iomanip>

class FlightComputer {
private:
    double altitude;
    double velocity;
    double fuel;
    double thrust;
    double time;

public:
    FlightComputer(double alt,double vel,double f,double T) {
        altitude=alt;
        velocity=vel;
        fuel=f;
        thrust=T;
        time=0.0;
    }

    void simulateStep(double dt) {
        velocity+=(thrust/1000-9.8)*dt;
        altitude+=velocity*dt;
        fuel-=dt*2;
        time+=dt;
    }

    void printStatus() {
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "t=" << time << " с: "
                  << "высота=" << altitude << " м, "
                  << "скорость=" << velocity << " м/с, "
                  << "топливо=" << fuel << std::endl;
    }
};

int main() {

    FlightComputer fc(0,0,100,12000);

    for (int i=0;i<5;i++) {
        fc.simulateStep(0.5);
        fc.printStatus();
    }

    return 0;
}
