#ifndef CParser_h
#define CParser_h

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "CException.h"
#include "CMatrice.h"

//Codes d'erreur : à partir de 300 pour cette classe
#define EXC_OuvertureFichier 300
#define EXC_UnexpectedSymbol 301
#define EXC_UnexpectedKeyWord 302
#define EXC_DuplicateLine 303
#define EXC_UnknownError 304
#define EXC_InvalidMatrixParameters 305
#define EXC_UnknownMatrixType 306

const char *pcMotsCles[] = { "TypeMatrice", "NBLignes", "NBColonnes", "Matrice", "[", "]" };
const char *pcValeurs[] = { "double" };

class CParser {
    
public:
    template <class MType> static CMatrice<MType> & PARLireFichier(char * pcNomFichier);
    
private:
    static int PARLectureMot(std::ifstream& fichier, char * pcMot);
    static int PARStringCompare(char *pcString1, const char * pcString2);
    static int PARGetCodeMotCle(char *pcString);
    static int PARGetCodeValeur(char *pcString);
};

#include "CParser.cpp"

#endif /* CParser_h */


