#ifndef CMatrice_h
#define CMatrice_h

#include <stdio.h>
#include <stdlib.h>
#include "CException.h"
#include "COperationsComplexesMatrices.h"

//Codes d'erreur : ˆ partir de 100 pour cette classe
#define EXC_OutOfBounds 100
#define EXC_MallocError 101
#define EXC_DivisionByZero 102

template <class MType> class CMatrice
{
    //Attributs
private:
    MType **pMATMatrice;
    unsigned int uiMATLignes;
    unsigned int uiMATColonnes;
    
    //Constructeurs/Destructeurs
public:
    CMatrice<MType>();
    CMatrice<MType>(CMatrice<MType> & MATMatrice);
    CMatrice<MType>(CMatrice<MType> && MATMatrice); // CMatrice<MType> c = a+b;
    CMatrice<MType>(unsigned int uiLigne, unsigned int uiColonne);
    ~CMatrice<MType>();
    
    //Methodes
public:
    MType MATGetElement(unsigned int uiLigne, unsigned int uiColonne);
    unsigned int MATGetNbLignes();
    unsigned int MATGetNbColonnes();
    void MATModifierElement(MType MTPElement, unsigned int uiLigne, unsigned int uiColonne);
    void MATAfficherMatrice();
    CMatrice & operator=(CMatrice & MATMatrice); // a + b = c
    CMatrice & operator=(CMatrice && MATMatrice); // c = a + b
    CMatrice operator*(double dNombre);
    CMatrice operator/(double dNombre);
};

#include "CMatrice.cpp"

#endif /* CMatrice_h */


