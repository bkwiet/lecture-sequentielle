/******************************************************************************
	Fichier			:		fichiers.cpp

	Bibliothèque	:		Fichiers

	Auteur			:		CRECEL Xavier

	Utilité			:		Implémentation des fonctions de la bibliothèque.
******************************************************************************/
#include "fichiers.h"
#include "utilitaires.h"
#include <fstream>
#include <string>

#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif

using namespace std;

/******************************************************************************
	La fonction GetNbLignes (...) prend en paramètre le nom d'un fichier,
	permet de compter et de retourner le nombre de lignes se trouvant dans 
	ce fichier.
******************************************************************************/
int GetNbLignes (const char * szFichierSrc)
{
	fstream ficJoueurs;
	int iCpt = 0;
	int iCar;

	ficJoueurs.open(szFichierSrc,ios ::in | ios :: binary );
	if(!ficJoueurs.fail())
	{
		//	Parcours du fichier jusqu'à sa fin.
		while (! ficJoueurs.eof())
		{
			iCar = ficJoueurs.get();
			if((char)iCar == '\n')
				iCpt++;
		}

		ficJoueurs.close();
	}
	return iCpt;
}

/******************************************************************************
	La fonction RemplirVecteur (...) permet de creer de nouveaux objets
	CJoueurs à partir d'un fichier dont le nom est reçu en paramètre et de les
	stocker dans le vecteur reçu en parmètre, la fonction retourne vrai si
	l'opération a réussit ou faux dans le cas contraire.
******************************************************************************/
bool RemplirVecteur ( CJoueur ** ppLesJoueurs, const char * szFichierSrc)
{
	fstream ficJoueurs;

	ficJoueurs.open(szFichierSrc,ios ::in | ios :: binary );
	if(ficJoueurs.fail())
	{
		return false;
	}
	else
	{
		unsigned int uiIndice = 0;
		string strLigne;
		
		string vsJoueur [9];

		//Parcours du fichier jusqu'à sa fin.
		while (! ficJoueurs.eof())
		{
			getline(ficJoueurs,strLigne);
			
			if(! ficJoueurs.eof())
			{
				/*================================================
				Récupération de chaque champ definissant un joueur
				================================================*/

				int iPosCurDebut = 0;
				int iPosCurFin= -1;
				int iIterateur;

				for( iIterateur =0 ; iIterateur < 9 ; iIterateur++)
				{
					iPosCurDebut = iPosCurFin + 1;

					if(iIterateur == 8)
						iPosCurFin = strLigne.find('\n', iPosCurDebut);
					else
						iPosCurFin = strLigne.find(';', iPosCurDebut);

					vsJoueur[iIterateur] = 
						strLigne.substr(iPosCurDebut,
						iPosCurFin -(iPosCurDebut));
					
				}

				/*====================================================
				Verification de la taille des champs avant l'attribution.
				=====================================================*/

				// rang du joueur
				if(GetLongueurChaine(vsJoueur[0].c_str()) > 3)
					return false;

				// nom du joueur
				if(GetLongueurChaine(vsJoueur[1].c_str()) > 30)
					return false;

				// equipe du joueur
				if(GetLongueurChaine(vsJoueur[2].c_str()) > 3)
					return false;

				// position du joueur
				if(GetLongueurChaine(vsJoueur[3].c_str()) > 1)
					return false;

				// nombre de parties du joueur
				if(GetLongueurChaine(vsJoueur[4].c_str()) > 5)
					return false;

				// nombre de buts du joueur
				if(GetLongueurChaine(vsJoueur[5].c_str()) > 5)
					return false;

				// nombre de passes du joueur
				if(GetLongueurChaine(vsJoueur[6].c_str()) > 5)
					return false;

				// differentiel du joueur
				if(GetLongueurChaine(vsJoueur[7].c_str()) > 5)
					return false;

				// minutes de punition du joueur
				if(GetLongueurChaine(vsJoueur[8].c_str()) > 5)
					return false;

				

				/*================================================
				Creation d'un nouveau objet CJoueur et attribution 
				des champs respectifs dans le constructeur.
				================================================*/

				ppLesJoueurs[uiIndice] = 
					new CJoueur(
					vsJoueur[0].c_str(),
					vsJoueur[1].c_str(),
					vsJoueur[2].c_str(),
					vsJoueur[3][0],
					(unsigned short) atoi (vsJoueur[4].c_str()),
					(unsigned short) atoi (vsJoueur[5].c_str()),
					(unsigned short) atoi (vsJoueur[6].c_str()),
					(short) atoi (vsJoueur[7].c_str()),
					(unsigned short) atoi (vsJoueur[8].c_str()));

				uiIndice++;
			}
		}

		ficJoueurs.close();
	}
	return true;
}

/******************************************************************************
	La fonction CreerFichierDirect (...) permet de creer un fichier à accés 
	direct dont le nom est reçu en paramètre à partir du vecteur reçu en 
	paramètre, la fonction retourne vrai si l'opération a réussit ou faux dans 
	le cas contraire.
******************************************************************************/
bool CreerFichierDirect ( const char * szFichierDest, CJoueur ** ppLesJoueurs,
	int iNbJoueurs)
{
	fstream ficJoueursDest;
	
	// Ouverture du fichier
	ficJoueursDest.open(szFichierDest, ios::in |ios::out |
		ios::trunc | ios::binary );
	if(! ficJoueursDest.fail())
	{
		
		char szEnregistrement [TAILLE_ENREGISTREMENT+1];
		int iIterateur;
		int iPosOcup;
		unsigned int uiDiviseur ;
		unsigned int uiZoneDeb;
		unsigned int uiPosCJoueur;

		// Calcul du diviseur
		uiDiviseur = (unsigned int)(1.25 * iNbJoueurs);

		while(! EstPremier(uiDiviseur))
		{
			uiDiviseur++;
		}

		// Calcul de la zone de debordement
		uiZoneDeb = uiDiviseur * TAILLE_ENREGISTREMENT;

		// Creation d'un enregistrement pour chaque CJoueur
		// present dans le vecteur
		for(iIterateur = 0; iIterateur < iNbJoueurs; iIterateur++)
		{
			 // Calcul de la position du CJoueur dans le fichier
			unsigned int uiLongueurNom = 
				GetLongueurChaine(ppLesJoueurs[iIterateur] ->GetNom());

			uiPosCJoueur = 
				(int)
				ppLesJoueurs[iIterateur] ->GetNom()[0] * 
				(int)
				ppLesJoueurs[iIterateur] ->GetNom()[uiLongueurNom - 1] *
				((int)
				ppLesJoueurs[iIterateur] ->GetEquipe()[0]) % uiDiviseur *
				TAILLE_ENREGISTREMENT;

			// Deplacement de la tete de lecture a la
			// position d'ecriture du joueur
			ficJoueursDest.seekg(uiPosCJoueur,ios::beg);

			// Si la position est deja prise
			iPosOcup = ficJoueursDest.peek();

			if( iPosOcup > 0)
			{	
				char szPosSuivant [9];
				unsigned int uiPosSuivant;

				// Tant qu'un suivant existe on deplace la
				// tete de lecture vers l'enregistrement
				// suivant
				do
				{					
					// Lecture
					ficJoueursDest.seekg(TAILLE_ENREGISTREMENT - 8,ios::cur);
					ficJoueursDest.read(szPosSuivant,8);

					uiPosSuivant = atoi (szPosSuivant);
					
					if(uiPosSuivant > 0)
					{ 
						uiPosCJoueur = uiPosSuivant;
						ficJoueursDest.seekg(uiPosCJoueur,ios::beg);
					}
				}
				while(uiPosSuivant > 0);

				// Ecriture de la position actuelle
				// de la zone de debordement a la suite
				// de l'enregistrement
				
				ficJoueursDest.seekp(uiPosCJoueur+62,ios::beg);				  
				sprintf(szPosSuivant,"%8d",uiZoneDeb);
				ficJoueursDest.write(szPosSuivant,8);

				
				// Deplacement de la tete de lecture vers
				// la zone de debordement
				ficJoueursDest.clear();
				ficJoueursDest.seekp(uiZoneDeb,ios::beg);

				// Incrémentation de la position de la
				// zone de débordement
				uiZoneDeb += TAILLE_ENREGISTREMENT;
			}
			else
			{
				// Deplacement de la tete de lecture vers la 
				// position calcule precedemment
				ficJoueursDest.clear();
				ficJoueursDest.seekg(uiPosCJoueur,ios::beg);
			}
			
			// Formatage du nouvelle enregistrement
			sprintf(szEnregistrement,"%3s%-30s%3s%c%5d%5d%5d%5d%5d%8d",
				ppLesJoueurs[iIterateur] ->GetRang(),
				ppLesJoueurs[iIterateur] ->GetNom(),
				ppLesJoueurs[iIterateur] ->GetEquipe(),
				ppLesJoueurs[iIterateur] ->GetPosition(),
				ppLesJoueurs[iIterateur] ->GetNbParties(),
				ppLesJoueurs[iIterateur] ->GetNbButs(),
				ppLesJoueurs[iIterateur] ->GetNbPasses(),
				ppLesJoueurs[iIterateur] ->GetNbMinutesPunition(),
				ppLesJoueurs[iIterateur] ->GetDifferentiel(),
				0);

			// Ecriture du nouvelle enregistrement dans le
			// fichier a acces direct
			ficJoueursDest.write(szEnregistrement,TAILLE_ENREGISTREMENT);
		}

		ficJoueursDest.close();
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************
	La fonction ChercherJoueurDirect (...) permet de chercher dans le fichier
	dont le nom est reçu en paramètre, le joueur dont le nom et l'équipe sont 
	reçus en paramètres et retourne un objet représentant le joueur si il est 
	trouvé, sinon lance une exeception "Enregistrement inexistant" si le joueur
	est inexistant.
******************************************************************************/
CJoueur ChercherJoueurDirect ( const char * szFichierSrc, int iNbJoueurs,
	const char * szNom, const char * szEquipe)
{
	fstream ficJoueurs;

	// Ouverture du fichier a acces direct
	ficJoueurs.open(szFichierSrc,ios ::in | ios :: binary );
	if(ficJoueurs.fail())
	{
		throw "Fichier invalide.";
	}
	else
	{

		unsigned int uiDiviseur ;
		unsigned int uiPosCJoueur = 0;
		
		char szRang [4] ;
		char szNomEnrTemp [31] = "";
		char szNomEnr [31] = "";
		char szEquipeEnr [4] = "";
		char szPositionEnr [2] = "";
		char szNbPartiesEnr [5] = "" ;
		char szNbButsEnr [5] = "";
		char szNbPassesEnr [5] = "";
		char szDifferentielEnr [5] = "";
		char szNbMinutesPunitionEnr [5] = "";
						 
		// Calcul du diviseur
		uiDiviseur = (unsigned int)(1.25 * iNbJoueurs);

		while(! EstPremier(uiDiviseur))
		{
			uiDiviseur++;
		}
		
		// Calcul de la position de l'enregistrement 
		// du CJoueur dans le fichier
		unsigned int uiLongueurNom = GetLongueurChaine(szNom);

		uiPosCJoueur = 
			(int)szNom[0] * 
			(int)szNom[uiLongueurNom - 1] *
			(int)szEquipe[0] % uiDiviseur *
			TAILLE_ENREGISTREMENT;

		// Recherche du joueur dans le fichier
		do
		{
			// Deplacement de la tete de lecture a la
			// position de l'enregistrement du joueur
			ficJoueurs.seekg(uiPosCJoueur+3,ios::beg);
			
			ficJoueurs.read(szNomEnrTemp,30);

			ficJoueurs.read(szEquipeEnr,3);

			CopierChaine(szNomEnr,szNomEnrTemp,GetLongueurChaine(szNom));

			if(ComparerChaines(szNomEnr,szNom) == 0 || 
			ComparerChaines(szEquipeEnr,szEquipe) == 0)
			{
				char szZoneDeb [8] ;
				// Lire la valeur de la position du joueur dans
				// la zone de debordement
				ficJoueurs.seekg(uiPosCJoueur+62,ios::beg);
				ficJoueurs.read(szZoneDeb,8);

				uiPosCJoueur = (int) atoi (szZoneDeb);
			}
			
		}
		while(ComparerChaines(szNomEnr,szNom) == 0 || 
			ComparerChaines(szEquipeEnr,szEquipe) == 0 &&
			uiPosCJoueur > 0);

		// Verifier que le joueur est valide apres la fin de la recherche
		if(ComparerChaines(szNomEnr,szNom) == 0 || 
			ComparerChaines(szEquipeEnr,szEquipe) == 0)
			{
				ficJoueurs.close();
				throw "Enregistrement inexistant.";
			}

		// Deplacement de la tete de lecture a la position
		// de l'enregistrement du joueur
		ficJoueurs.seekg(uiPosCJoueur,ios::beg);

		// Lecture de chaque attributs du joueur dans l'enregistrement
		ficJoueurs.read(szRang,3);
		ficJoueurs.seekg(33,ios::cur);
		ficJoueurs.read(szPositionEnr,1);
		ficJoueurs.read(szNbPartiesEnr,5);
		ficJoueurs.read(szNbButsEnr,5);
		ficJoueurs.read(szNbPassesEnr,5);
		ficJoueurs.read(szDifferentielEnr,5);
		ficJoueurs.read(szNbMinutesPunitionEnr,5);

		// Creation de l'objet CJoueur
		CJoueur unJoueur(
					szRang,
					szNomEnr,
					szEquipeEnr,
					szPositionEnr[0],
					(unsigned short) atoi ( szNbPartiesEnr),
					(unsigned short) atoi (szNbButsEnr),
					(unsigned short) atoi ( szNbPassesEnr),
					(short) atoi (szDifferentielEnr),
					(unsigned short) atoi (szNbMinutesPunitionEnr));			
		
		ficJoueurs.close();
		return unJoueur;
	}
	
}