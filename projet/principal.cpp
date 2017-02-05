/******************************************************************************
	Fichier:	principal.cpp

	Auteur:		CRECEL Xavier

	Utilité:	Permet de creer un fichier a acces direct ".dat" avec un fichier 
				source ".txt" et d'afficher les informations contenu dans ce
				fichier cree par le biais des fonctions de la bibliotheque
				"Fichier"
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "fichiers.h"
#include "utilitaires.h"

using namespace std;

#ifdef _WIN32
const char EFFACER_ECRAN [] = "cls";
#else
const char EFFACER_ECRAN [] = "clear";
#endif

int main()
{
	string strFichierTxt = "./joueurs.txt";	
	int nbLignes;
	CJoueur ** ppLesJoueurs; 
	
	// Obtention du nombre de lignes dans le fichier source
	// ====================================================

	cout << "Obtention du nombre de lignes dans le fichier source ("
		 << strFichierTxt.substr(2,strFichierTxt.find('\0')) <<")..." <<endl;

	nbLignes = GetNbLignes(strFichierTxt.c_str());

	// Affichage du nombre de lignes obtenues dans le fichier source
	// =============================================================
	cout << "Nombre de lignes obtenues : " << nbLignes 
		 << " [ != -1 -> OK :)] \n" << endl;

	if(nbLignes > -1)
	{
		// Creation d'un vecteur dynamique de Pointeurs d'objets
		// initialise avec le nombre de lignes obtenues
		// =====================================================
		cout << "Creation d'un vecteur dynamique de "
			 << nbLignes << " pointeurs d'objets CJoueur...\n"
			 << endl;

		ppLesJoueurs = new CJoueur * [nbLignes];
		
		// Remplissage du vecteur a partir du fichier source
		// ====================================================
		cout << "Remplissage du vecteur a partir du fichier source ("
		     << strFichierTxt.substr(2,strFichierTxt.find('\0')) 
			 <<")..." <<endl;
		
		if(RemplirVecteur(ppLesJoueurs,strFichierTxt.c_str()))
		{
			cout << "Objets CJoueur places en memoire (sur le tas)"
				 << " avec succes!\n" << endl;

			
			// Creation du fichier a acces direct
			// ===================================
			string strFichierDat = "./joueurs.dat";

			cout << "Creation du fichier a acces direct ("
		         << strFichierDat.substr(2,strFichierDat.find('\0'))
				 <<")..." <<endl;

			if(CreerFichierDirect(strFichierDat.c_str(),ppLesJoueurs,nbLignes))
			{
				cout << "Fichier ("
		             << strFichierDat.substr(2,strFichierDat.find('\0'))
					 <<") cree avec succes! \n" <<endl;

				// Recherche et affichage des joueurs a partir du fichier
				// a acces direct.
				// ======================================================
				cout << "Appuyez sur (Entree) pour lancer la recherche et "
					 << "l'affichage \ndes joueurs a partir du fichier ("
		             << strFichierDat.substr(2,strFichierDat.find('\0'))
					 <<")..." << flush;

				while(cin.get() != '\n');

				int iIterateur;
				int nbJoueursAffiches = 0 ;

				// Affichage de tous les joueurs contenus dans
				// le fichier par tranche de 20 joueurs 
				for(iIterateur=0;iIterateur < nbLignes; iIterateur++)
				{
					
					CJoueur unJoueur(ChercherJoueurDirect(
						strFichierDat.c_str(),
						nbLignes,
						ppLesJoueurs[iIterateur]->GetNom(),
						ppLesJoueurs[iIterateur]->GetEquipe()
						));

					cout << "Rang \t\t: " << unJoueur.GetRang() << endl;
					cout << "Nom \t\t: " << unJoueur.GetNom() << endl;
					cout << "Equipe \t\t: " << unJoueur.GetEquipe() << endl;
					cout << "Position \t: " << unJoueur.GetPosition() << endl;
					cout << "Parties \t: " << unJoueur.GetNbParties() << endl;
					cout << "Buts \t\t: " << unJoueur.GetNbButs() << endl;
					cout << "Passes \t\t: " << unJoueur.GetNbPasses() << endl;
					cout << "Differentiel \t: " 
						 << unJoueur.GetDifferentiel() << endl;
					cout << "Punitions \t: " 
						 << unJoueur.GetNbMinutesPunition() << endl << endl;

					nbJoueursAffiches++;

					if(nbJoueursAffiches == 20)
					{
						nbJoueursAffiches = 0;

						cout << "Appuyez sur (Entree) pour continuer..."
							 << flush;

						while(cin.get() != '\n');

						cout << endl;
					}
					
				
				}
			}
			else
			{
				cout << "La creation du fichier ("
		             << strFichierDat.substr(2,strFichierDat.find('\0'))
					 <<") a echoue! \n" <<endl;
			}			

		}
		else
		{
			cout << "Le remplissage du vecteur a echoue! \n" << endl;
		}
	}
	
	// Liberation de la memoire , Destruction de chaque objets
	// CJoueur attribue dans le vecteur et destruction du vecteur
	// ==========================================================
	cout << "Appuyez sur (Entree) pour retirer un a un tous "
		 << "les objets \nCJoueur de la memoire ..."<< flush; 			 
	while(cin.get() != '\n');

	int iIterateur;

	for(iIterateur = 0; iIterateur < nbLignes; iIterateur++)
	{
		delete ppLesJoueurs[iIterateur];
	}

	cout << endl;

	cout << "Appuyez sur (Entree) pour retirer le vecteur de la "
			<< "memoire ..." << flush;

	while(cin.get() != '\n');

	delete [] ppLesJoueurs;

	cout << endl;

	// Quitter le programmme
	cout << "Appuyez sur (Entree) pour quitter ..." << flush;

	while(cin.get() != '\n');

	return 0;
}