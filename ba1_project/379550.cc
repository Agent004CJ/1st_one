// 379550.cc // Carl Johan Traeholt WALDORFF // ver. 21
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

enum SigType {SAWTOOTH, SQUARE, TRIANGLE};

constexpr double EPSIL_DICHO(1e-9);
constexpr double EPSIL_T(1e-13);

struct Vars {
	int nbL;
	size_t nbC;
	int nbN;
	int tLine;			// number of line; time axis
	double deltaT;
	double deltaS;
	double tMin;
	double tMax;
	double aMin;
	double aMax;
	SigType S;
	};

void print_error(string message);
double sawtooth (int terms, double time);
double square (int terms, double time);
double triangle(int terms, double time);
void mapSaw(const Vars &data, vector <vector <char>> &grid);
void mapSquare(const Vars &data, vector <vector <char>> &grid);
void mapTriangle(const Vars &data, vector <vector <char>> &grid);
void mapTime (const Vars &data, vector <vector <char>> &grid);
void mapSignal (const Vars &data, vector <vector <char>> &grid);
void printGrid (const Vars &data, const vector <vector <char>> &grid);
void getData(Vars &data);
void getInterval (const Vars &data, double &inf, double &sup, double &max);
void dicoMax (const int &nbN, double &inf, double &sup, double &max, 
			  double &last_max, int &count, SigType S);


int main() {
	
	Vars data;			//structure of variables
	getData (data);
	
	// initialize  grid
	vector <vector <char>> grid (data.nbL, vector<char> (data.nbC,' '));
	
	mapTime (data, grid);
	
	mapSignal (data, grid);
	
	printGrid (data, grid);
	
	double inf (0);
	double sup (0);
	double max (0);
	
	getInterval (data, inf, sup, max);
	
	double last_max (-1);
	int count (0);
	
	dicoMax (data.nbN, inf, sup, max, last_max, count, data.S);

	cout<< fixed << setprecision(8) << max;
	
	return 0;
	}

void print_error(string message) {
    cout << message;
    cout << endl;
    exit(0);
	}

double sawtooth (int terms, double time){
	
	double res(0);
	for(int k(1); k < terms + 1; ++k) {
	 res = res + ((pow((-1.),k)/k)*sin(2*M_PI*k*time-0.5*2*M_PI*k));
	 }
	 
	 res = (-2./M_PI)*res;
	 
	 return res;
	}


double square (int terms, double time) {
	double res(0);
	
	for(int k(1); k < terms+1; ++k){
		res = res + (sin(2.*M_PI*(2*k-1)*time)/(2*k-1));
	}
	
	res = (4/M_PI)*res;
	
	return res;
	}


double triangle(int terms, double time){
	double res(0);
	
	for(int k(1); k < terms + 1; ++k){
		res = res + ((pow((-1.),k)/pow((2*k-1),2))*sin(2*M_PI*(2*k-1)*(time-0.25)));
		}
		
	res = ((-8)/pow(M_PI,2))*res;
	
	return res;
	}


void mapSaw(const Vars &data, vector <vector <char>> &grid) {
	
	for(size_t c(0); c < data.nbC; ++c) { 				// mapping theoretical values
		double t(c*data.deltaT + data.tMin);
		int l(round(((2*t - 1)-data.aMin)/data.deltaS));
		if (t < 0 + EPSIL_T or t > 1 - EPSIL_T) {l=data.tLine;}
		if(l >= 0 && l < data.nbL) grid[l][c]='+';
		}

	for(size_t c(0); c < data.nbC; ++c) {				// mapping approximated values
		double t (c*data.deltaT + data.tMin);
		int l(round((sawtooth(data.nbN, t) - data.aMin)/data.deltaS));
		if(l >= 0 && l < data.nbL) grid[l][c]='*';
		}
	}


void mapSquare(const Vars &data, vector <vector <char>> &grid) {
	
	for(size_t c(0); c<data.nbC; ++c) {				// mapping theoretical values
		double t(c*data.deltaT + data.tMin);
		int l(round(((1) - data.aMin)/data.deltaS));
		if (t > 0.5) {l=round(((-1)-data.aMin)/data.deltaS);}
		if (t < 0 + EPSIL_T or (t > 0.5-EPSIL_T and t < 0.5 + EPSIL_T) 
			or t > 1 - EPSIL_T) {
			l = data.tLine;
			}
		if(l >= 0 && l < data.nbL) {grid[l][c]='+';}
		}
	
	for(size_t c(0); c < data.nbC; ++c) {			// mapping approximated values
		double t(c*data.deltaT + data.tMin);
		int l(round((square(data.nbN, t) - data.aMin)/data.deltaS));
		if(l >= 0 && l < data.nbL) grid[l][c]='*';
		}
	}


void mapTriangle(const Vars &data, vector <vector <char>> &grid) {
	
	for(size_t c(0); c<data.nbC; ++c) {				// mapping theoretical values
		double t (c*data.deltaT + data.tMin);
		int l (round(((4*t - 1.)-data.aMin)/data.deltaS));
		if (t > 0.5) {l=round(((-4*t + 3)-data.aMin)/data.deltaS);}
		if(l >= 0 && l < data.nbL) grid[l][c]='+';
		}
		
	for(size_t c(0); c<data.nbC; ++c) {				// mapping approximated values
		double t (c*data.deltaT + data.tMin);
		int l(round((triangle(data.nbN,t)-data.aMin)/data.deltaS));
		if(l>=0 && l<data.nbL) grid[l][c]='*';
		}
	}


void mapTime (const Vars &data, vector <vector <char>> &grid) {
	
	 for (size_t i(0); i < grid[data.tLine].size(); ++i) {
		 if(data.tLine >= 0 && data.tLine<=data.nbL) grid[data.tLine][i]='.';
		 }
	
	return;
	}


void mapSignal (const Vars &data, vector <vector <char>> &grid) {
	
	if (data.S == SAWTOOTH){
		mapSaw(data, grid);
		}
	if (data.S == SQUARE) {
		mapSquare(data, grid);
		}
	if (data.S == TRIANGLE) {
		mapTriangle(data, grid);
		}
	
	return;
	}


void printGrid (const Vars &data, const vector <vector <char>> &grid) {
	
	for(size_t i(0); i < data.nbC; ++i) {
		cout << '-';
		}
	cout << endl; 
	
	for(int l (data.nbL-1); l >= 0; --l) {
		for (size_t c(0); c < data.nbC; ++c){
			cout << grid[l][c];
			}
		cout << endl;
		}
		
	for(size_t i(0); i < data.nbC; ++i) {
		cout << '-';
		}
	cout << endl; 
	
	return;
	}


void getData(Vars &data) {
	
	string signal;
	cin >> signal;
	
	//verification signal
	if (!((signal == "SAWTOOTH") or (signal == "SQUARE") or (signal == "TRIANGLE"))){
		const string BAD_SIGNAL("Error: signal type "
			"must be SAWTOOTH, SQUARE or TRIANGLE");
		print_error(BAD_SIGNAL);
	}
	
	if (signal == "SAWTOOTH") {
		data.S = SAWTOOTH;
	} else if (signal == "SQUARE") {
		data.S = SQUARE;
	} else if (signal == "TRIANGLE") {
		data.S = TRIANGLE;
		}
	
	cin >> data.nbN;
	
	if (data.nbN <= 0) {
		const string NBN_TOO_SMALL("Error: the number "
			"of sine terms must be greater than 0");
		print_error(NBN_TOO_SMALL);
		}
	
	cin >> data.tMin;
	cin >> data.tMax;

	//verification tmin tmax
	if (data.tMax<=data.tMin) {
		const string TIME_MIN_MAX("Error: time max is not bigger than min");
		print_error(TIME_MIN_MAX);
		}
	if ((data.tMax>1) or (data.tMin<0)) {
		const string WRONG_TIME_VAL("Error: both time "
		"values must belong to [0., 1.]");
		print_error(WRONG_TIME_VAL);
		}
	
	cin >> data.aMin;
	cin >> data.aMax;
	
	// verification amplitudes
	if (data.aMax <= data.aMin) {
		const string SIGNAL_MIN_MAX("Error: signal max is not bigger than min");
		print_error(SIGNAL_MIN_MAX);
		}
	
	cin >> data.nbL;
	
	//vericication number of lines
	if (data.nbL <= 2) {
		const string NBL_TOO_SMALL("Error: the number "
			"of lines must be greater than 2");
		print_error(NBL_TOO_SMALL);
		}
	if (data.nbL % 2 == 0) {
		const string NBL_NOT_ODD("Error: the number of lines must be odd");
		print_error(NBL_NOT_ODD);
		}
	
	
	data.nbC = 2 * data.nbL - 1;						  // calc nb columns
	data.deltaT = (data.tMax - data.tMin)/(data.nbC - 1); // calc dimensions of cells
	data.deltaS = (data.aMax - data.aMin)/(data.nbL - 1);
	data.tLine = round((0 - data.aMin)/data.deltaS);	  // calc grid timeline
	
	return;
	}



void getInterval (const Vars &data, double &inf, double &sup, double &max) {
	
	if (data.S == SAWTOOTH) {
		inf = 1-1./(2 * data.nbN + 1);
		sup = 1;
		}
	
	if(data.S == SQUARE) {
		inf = 0;
		sup = 1./(2 * data.nbN + 1);
		}
	if (data.S == TRIANGLE) {
		max = triangle(data.nbN, 0.5);
		}
	
	return;
	}

void dicoMax (const int &nbN, double &inf, double &sup, 
		double &max, double &last_max, int &count, SigType S) {
			
		if (S == TRIANGLE) {return;}
		if (sup - inf < EPSIL_DICHO) {count++;} // stop condition
		if (count == 2) {return;}
		
		double a (0);
		double b (0);
		
		
		if(S == SQUARE) {
			a = square(nbN, inf);
			b = square(nbN, sup);
			}
		if(S == SAWTOOTH) {
			a = sawtooth(nbN, inf);
			b = sawtooth(nbN, sup);
			}
		
		last_max = max;
		
		if (a > b) {						// boundary reajustment
			max = a;
			sup = inf + (sup - inf)/2.;
		} else {
			max = b;
			inf = inf + (sup - inf)/2.;
			}

    dicoMax(nbN, inf, sup, max, last_max, count, S);
	}
