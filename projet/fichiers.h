/******************************************************************************
	Fichier			:		fichiers.h

	Bibliothèque	:		Fichiers

	Auteur			:		CRECEL Xavier

	Utilité			:		Bibliothèque.
******************************************************************************/

#ifndef __FICHIERS_H
#define __FICHIERS_H

#include "joueur.h"

const int TAILLE_ENREGISTREMENT = 70;
int GetNbLignes (const char * szFichierSrc);
bool RemplirVecteur ( CJoueur ** ppLesJoueurs, const char * szFichierSrc);
bool CreerFichierDirect ( const char * szFichierDest, CJoueur ** ppLesJoueurs,
	int iNbJoueurs);
CJoueur ChercherJoueurDirect ( const char * szFichierSrc, int iNbJoueurs,
	const char * szNom, const char * szEquipe);

#endif