#include <iostream>
#include <cmath>
using namespace std;

class Apero {
    public:
       Apero() { // constructor
        cout << "L'heure de l'apero a sonne !" << endl;
        return;
       }
       void bis() { // method ordinary
           cout << "Encore une?" << endl;
           return;
       }
       ~Apero () { // destructor
           cout << "a table !" << endl;
       }
};

int main() {
Apero bic;
cout << "Super !" << endl;
bic.bis();
cout << "Non merci." << endl;
return 0;
}
