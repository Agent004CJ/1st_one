// ex_semaine_1.cc // Carl Johan Traeholt WALDORFF // ver. 1
#include<iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

struct Point {
	double x;
	double y;
};

class Circle
{
private:
	double radius;
	Point center;

public:
	Point getCenter() {
		return center;
	}
	
	void setCenter(double& x_,double& y_) const {
		center.x = x_;
		center.x = y_;
	}

	double surface() {
		return M_PI * pow(radius,2);
	}

	bool isInside(double x_,double y_) const {
		if ((pow(x_,2))+(pow(y_,2)) <= radius) {
			return true;
		} else {
			return false;
		}

	}
};

int main() {
// definitions et affectations
	Circle C1;
	C1.setCenter(3, 2);
	cout << C1.center.x << endl;
	cout << endl;


	cout << "hej med dig" << endl;

	return 0;
};