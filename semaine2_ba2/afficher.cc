#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
    ifstream fichier("texte.txt");
    if(fichier.fail()) {
        cout << "le fichier file texte est absent" << endl;
        return EXIT_FAILURE;
    }
    char octet;
    while(octet = fichier.get() !=EOF) {
        cout.put(octet);
    }

    fichier.close();

    cout << "\nFin du fichier texte" << endl;

    return EXIT_SUCCESS;

}