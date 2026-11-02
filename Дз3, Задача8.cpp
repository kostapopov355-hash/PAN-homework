#include <iostream>

class NavigationSystem {
private:
    double x;
    double y;
    double velocityX;
    double velocityY;
    bool gpsAvailable;

public:
    NavigationSystem(double posX,double posY,double vx,double vy,bool gps) {
        x=posX;
        y=posY;
        velocityX=vx;
        velocityY=vy;
        gpsAvailable=gps;
    }

    void integratePosition(double dt) {
        x+=velocityX*dt;
        y+=velocityY*dt;
    }

    void correctGPS(double realX,double realY) {
        if(gpsAvailable==true) {
            x=(x+realX)/2;
            y=(y+realY)/2;
        }
    }

    void printPosition() {
        std::cout << "Скорректированные координаты: ("
                  << x << ", " << y << ")" << std::endl;
    }
};

int main() {

    NavigationSystem nav(0,0,100,50,true);

    nav.integratePosition(1);
    nav.correctGPS(110,60);
    nav.printPosition();

    return 0;
}
