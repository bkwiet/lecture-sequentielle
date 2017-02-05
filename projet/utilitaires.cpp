/******************************************************************************
	Fichier:		utilitaires.cpp

	Biblioth�que:	Utilitaires

	Auteur:			Jos� Consola

	Utilit�:		Impl�mentation des fonctions de la biblioth�que.
******************************************************************************/
#include "utilitaires.h"


/******************************************************************************
	La fonction EstPremier (...) prend en param�tre un entier non-sign�,
	v�rifie si ce nombre est un nombre premier et retourne vrai si c'est le
	cas ou faux dans le cas contraire.
******************************************************************************/
bool EstPremier (unsigned int uiNombre)
{
	unsigned int uiDiviseur;
	bool bEstPremier;

	uiDiviseur = 2;
	bEstPremier = true;
	while (uiDiviseur <= uiNombre / 2 && bEstPremier)
	{
		if (uiNombre % uiDiviseur == 0)
		{
			bEstPremier = false;
		}
		uiDiviseur++;
	}
	return bEstPremier;
}


/******************************************************************************
	La fonction CopierChaine (...) permet de copier, un � un, les caract�res
	de la chaine source dans la chaine de destination.
******************************************************************************/
void CopierChaine (char * szDest, const char * szSource,
				   unsigned int uiNbCars)
{
	unsigned int iCpt;

	iCpt = 0;
	while (szSource [iCpt] != '\0' && iCpt < uiNbCars)
	{
		szDest [iCpt] = szSource [iCpt];
		iCpt++;
	}
	szDest [iCpt] = '\0';
}


/******************************************************************************
	La fonction ComparerChaines (...) permet de v�rifier si les deux chaines
	de caract�res re�ues en param�tre sont identiques. Dans ce cas, la fonction
	retourne 1. Dans le cas o� les chaines sont diff�rentes l'une de l'autre,
	la fonction retourne 0.
******************************************************************************/
int ComparerChaines (const char * szChaine1, const char * szChaine2)
{
	int iIndice = 0;

	while ((szChaine1 [iIndice] != '\0' || szChaine2 [iIndice] != '\0')
		&& szChaine1 [iIndice] == szChaine2 [iIndice])
	{
		iIndice++;
	}
	if (szChaine1 [iIndice] == szChaine2 [iIndice])
	{
		return 1;
	}
	return 0;
}


/******************************************************************************
	La fonction GetLongueurChaine (...) permet de compter le nombres de
	caract�res contenus dans le vecteur re�u en param�tre.
******************************************************************************/
unsigned int GetLongueurChaine (const char * szSource)
{
	unsigned int iCpt = 0;

	while (szSource [iCpt] != '\0')
	{
		iCpt++;
	}
	return iCpt;
}