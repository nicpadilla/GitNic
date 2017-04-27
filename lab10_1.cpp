#include <cstdlib>
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

#define PI 3.14159265

class ABC {
protected:
    double x;
    double y;
public:
    ABC(double x0 =0, double y0 =0): x(x0), y(y0) {};
    virtual ~ABC(){}
    void Move(double nx, double ny){x=nx; y=ny;}
    virtual double Area() const = 0; //pure virtual function
    virtual void Resize() = 0; //pvf
    virtual void Display() = 0;
    virtual void coordCheck(double, double){}
    virtual void verLoc(){}
    virtual void Rotate(double){}
};
//***********************************************************
class Ellipse : public ABC {
private:
    double a; //semi-major axis
    double b; //semi-minor axis
    double angle = 0; //orientation angle
    
public:
    Ellipse(double a0, double b0) {a = a0; b = b0;}
    double Area() const override {return 3.14159*a*b;}
    void Resize() override;
    void Display() override;
    void Rotate(double nang) {angle += nang;}
    void vertLoc(); //calculate locations of vertices
    ~Ellipse(){}
    
};

void Ellipse::Resize() {
    double a0, b0;
    cout << "Enter new semi-major and semi-minor axis: " << endl;
    cin >> a0 >> b0;
    a = a0;
    b = b0;
}

void Ellipse::Display() {
    cout << "Ellipse Information: \n"
            "x: " << x << "\ny: " << y << "\nsemi-major axis: " << a << "\nsemi-minor axis: "
            << b << "\nArea: " << Area() << "\nAngle: " << angle << "\n" << endl;
    vertLoc();
}

void Ellipse::vertLoc() {
    //assume a is along x axis
    double x1, x2;
    x1 = a*cos(angle);
    x2 = -a*cos(angle);
    cout << "Vertices Location: (" << x1 << ',' << x2 << ')' << endl;
}

//***********************************************************
class Circle : public ABC {
private:
    double r; //radius
    
public:
    Circle(double r0) {r = r0;}
    ~Circle(){}
    double Area() const override {return 3.14159*r*r;}
    void Resize() override;
    void Display() override;
    void coordCheck(double, double);
};

void Circle::Resize() {
    double r0;
    cout << "Enter new radius for circle: " << endl;
    cin >> r0;
    r = r0;
}

void Circle::Display() {
    cout << "Circle information: "
            << "\nx: " << x << "\ny: " << y << "\nradius: " << r << "\narea: " << Area() << endl;
}

void Circle::coordCheck(double x0, double y0) {
    double d;
    if(sqrt(pow(x0-x,2)+pow(y0-y,2)) <= r) {
        cout << "Point (" << x0 << "," << y0 << ") is within the circle." << endl;
    }
    else cout << "Point (" << x0 << "," << y0 << ") is NOT within the circle." << endl;
}

int main(int argc, char** argv) {
    Circle circ(2);
    Ellipse ell(1, 2);
    ABC* abc = &circ;
    abc->Display();
    abc->Resize();
    abc->Display();
    abc->Move(3, 4);
    abc->Display();
    abc->coordCheck(20, 4);
    return 0;
}

