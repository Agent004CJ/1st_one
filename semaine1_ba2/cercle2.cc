#include <iostream> // for cout and endl
#include <cmath> // for M_PI and sqrt()
using namespace std;

class Circle {
public:
void getCenter(double& x_out, double& y_out) const {
x_out = x;
y_out = y;
}
void setCenter(double x_in, double y_in) {
x = x_in;
y = y_in;
}
double getRadius() const {
return radius;
}
void setRadius(double r) {
if (r < 0.0) r = 0.0;
radius = r;
}
double surface() {
    return pow(radius,2)*M_PI;
}
bool isInside(double xp, double yp) {
    if(radius*radius >= pow(xp-x,2)+pow(yp-y,2)) {
        return true;
    } else {
        return false;
    }
}
private:
double radius;
double x; 
double y;
};

int main () {
Circle c1, c2;
c1.setCenter(1.0, 2.0);
c1.setRadius(sqrt(5.0)); // passe par (0, 0)
c2.setCenter(-2.0, 1.0);
c2.setRadius(2.25); // 2.25 > sqrt(5) => inclus le point (0, 0)
cout << "surface of C1 : " << c1.surface() << endl;
cout << "Surface of C2 : " << c2.surface() << endl;

cout << "location of the point (0, 0) : ";
if (c1.isInside(0.0, 0.0)) cout << "inside";
else cout << "outside";
cout << " C1 and ";
if (c2.isInside(0.0, 0.0)) cout << "inside";
else cout << "outside";
cout << " C2." << endl;


return 0;
}
