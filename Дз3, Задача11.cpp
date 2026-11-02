#include <iostream>
#include <iomanip>

class Engine {
private:
    double thrust;
    double fuelFlow;
    double fuel;

public:
    Engine(double T,double flow,double f) {
        thrust=T;
        fuelFlow=flow;
        fuel=f;
    }

    double getThrust() {
        return thrust;
    }

    bool hasFuel() {
        return fuel>0;
    }

    void burn(double dt) {
        if(fuel>0) {
            fuel-=fuelFlow*dt;

            if(fuel<0) {
                fuel=0;
            }
        }
    }

    double getFuel() {
        return fuel;
    }
};

class Navigation {
private:
    double altitude;
    double velocity;
    double acceleration;
    double mass;

public:
    Navigation(double h,double v,double m) {
        altitude=h;
        velocity=v;
        mass=m;
        acceleration=0;
    }

    void update(double thrust,double dt) {
        acceleration=thrust/mass-9.81;
        velocity+=acceleration*dt;
        altitude+=velocity*dt;
    }

    void printStatus(double time) {
        std::cout << "t=" << time << "с | "
                  << "h=" << altitude << "м | "
                  << "v=" << velocity << "м/с | "
                  << "a=" << acceleration << "м/с²"
                  << std::endl;
    }

    double getAltitude() {
        return altitude;
    }
};

class AutonomousFlightSystem {
private:
    Engine engine;
    Navigation nav;
    double time;

public:
    AutonomousFlightSystem(Engine e,Navigation n)
        : engine(e),nav(n) {
        time=0;
    }

    void simulate(double dt,double totalTime) {
        std::cout << std::fixed << std::setprecision(2);

        while(time<totalTime && engine.hasFuel()==true) {
            engine.burn(dt);
            nav.update(engine.getThrust(),dt);
            nav.printStatus(time);
            time+=dt;
        }
    }

    void printSummary() {
        std::cout << "\n--- Полет завершен ---" << std::endl;
        std::cout << "Итоговая высота: " << nav.getAltitude() << " м" << std::endl;
        std::cout << "Оставшееся топливо: " << engine.getFuel() << " кг" << std::endl;
    }
};

int main() {

    Engine engine(20000,10,50);
    Navigation nav(0,0,1000);

    AutonomousFlightSystem flight(engine,nav);

    flight.simulate(1.0,10.0);
    flight.printSummary();

    return 0;
}
