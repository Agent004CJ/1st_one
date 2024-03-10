#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// symboles et type pour codes d'erreurs
enum Erreur_lecture {LECTURE_ARG, LECTURE_OUVERTURE, 
					 LECTURE_NB0, LECTURE_LIVREUR,
					 LECTURE_NB1, LECTURE_VEHICULE,
					 LECTURE_NB2, LECTURE_LIVRAISON,
					 LECTURE_FIN, LECTURE_ETAT};
					 								
// prototypes
void lecture(char * nom_fichier);
void decodage_ligne(string line);
void erreur(Erreur_lecture code);

// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	if(argc != 2) erreur(LECTURE_ARG);
	
	lecture(argv[1]);

	return EXIT_SUCCESS;
}

// traite le fichier ligne par ligne.  
void lecture( char * nom_fichier)
{
    string line;
    ifstream fichier(nom_fichier); 
    if(!fichier.fail()) 
    {
        // l’appel de getline filtre aussi les séparateurs
        while(getline(fichier >> ws,line)) 
        {
			// ligne de commentaire à ignorer, on passe à la suivante
			if(line[0]=='#')  continue;  
       
			decodage_ligne(line);
        }
        cout << "fin de la lecture" << endl;
	}
	else erreur(LECTURE_OUVERTURE);
}

// décodage selon l'etat courant d'une ligne lue dans le fichier 
// met à jour l'etat
void decodage_ligne(string line)
{
	istringstream data(line);
  
	// états de l'automate de lecture					 
	enum Etat_lecture {NB0,LIVREUR,NB1,VEHICULE,NB2,LIVRAISON,FIN};
  
	static int etat(NB0); // état initial
	static int i(0), total(0);
	int num(0);
	bool disp(false);
	string name;

	switch(etat) 
	{
	case NB0: 
		if(!(data >> total)) erreur(LECTURE_NB0); 
		else i=0 ;
		if(total==0) etat=NB1; 
		else         etat=LIVREUR ; 
		cout << "Nb de livreurs: " << total << endl; 
	    break;

	case LIVREUR: 
		if(!(data >> name >> disp)) erreur(LECTURE_LIVREUR);
		else ++i;
		if(i == total) etat=NB1 ;
		cout << "Livreur " << i << ": "  << name 
	                              << " disp : "  << disp << endl; 
	    break;

	case NB1: 
		if(!(data >> total)) erreur(LECTURE_NB1); 
		else i=0 ;
		if(total==0) etat=NB2; 
		else         etat=VEHICULE ; 
		cout << "Nb de véhicules: " << total << endl; 
	    break;

	case VEHICULE: 
		if( !(data >> num >> disp)) erreur(LECTURE_VEHICULE);
		else ++i;
		
		if(i == total) etat=NB2 ;
		cout << "Véhicule " << i << ": "  << num
	                               << " disp : "  << disp << endl ;
	     break;

	case NB2: 
		if(!(data >> total)) erreur(LECTURE_NB2); 
		else i=0;
		
		if(total==0) etat=FIN; 
		else         etat=LIVRAISON ; 
		cout << "Nb de livraisons: " << total << endl; 
	     break;

	case LIVRAISON: 
		if( !(data >> name >> num)) erreur(LECTURE_LIVRAISON);
		else ++i;
		
		if(i == total) etat=FIN ;
		cout << "Livraison " << i << ": "  << name
	                                << " véhicule : "  << num << endl; 
	    break;

	case FIN: erreur(LECTURE_FIN) ; 
		break;

	default: erreur(LECTURE_ETAT);
	}	
}

// affiche un message d'erreur puis quitte le programme
void erreur(Erreur_lecture code)
{
	switch(code)
	{
	case LECTURE_ARG : cout << " nom de fichier manquant\n";  break;
	case LECTURE_OUVERTURE: cout << " ouverture impossible\n";break;
	case LECTURE_NB0 : 
	case LECTURE_NB1 : 
	case LECTURE_NB2 : 
	case LECTURE_LIVREUR : 
	case LECTURE_VEHICULE : 
	case LECTURE_LIVRAISON : cout << " lecture impossible \n";
	case LECTURE_FIN : cout << " format non respecté \n";     break;
	case LECTURE_ETAT : cout << " etat inexistant\n";         break;
	default: cout << " erreur inconnue\n";
	}
	exit(EXIT_FAILURE);
}
