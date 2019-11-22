#include <stdio.h>
#include <iostream>
#include <cmath>
#include "CMatrice.h"
#include "COperationsComplexesMatrices.h"
#include "CParser.h"

int main(int argc, char *argv[])
{
    //Pour chaque nom de fichier passé en paramètre, lire le fichier et créer la matrice associée :
    if (argc > 1) {
        
        unsigned int uiNbMatrices = argc - 1;
        
        CMatrice<double> **pMATTableauMatricesFichier = (CMatrice<double>**)malloc((uiNbMatrices) * sizeof(CMatrice<double>*));
        
        for (unsigned int uiIndice = 0; uiIndice < uiNbMatrices; uiIndice++) {
            try {
                pMATTableauMatricesFichier[uiIndice] = & CParser::PARLireFichier<double>(argv[uiIndice+1]);
            }
            catch (CException EXCLevee) {
                printf("Code d'erreur levee = %d\n", EXCLevee.EXCLireErreur());
                return 1;
            }
        }
        
        //On affiche les matrices ainsi crees :
        for (unsigned int uiIndice = 0; uiIndice < uiNbMatrices; uiIndice++) {
            std::cout << "M" << uiIndice+1 << " cree en lisant un fichier :" << std::endl;
            pMATTableauMatricesFichier[uiIndice]->MATAfficherMatrice();
        }
        
        int c;
        std::cout << "Veuillez entrer un entier : ";
        std::cin >> c;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Caractère non reconnu\n";
            std::cin >> c;
        }
        
        std::cout <<"Vous avez ecrit : " << c << std::endl;
        
        for (unsigned int uiIndice = 0; uiIndice < uiNbMatrices; uiIndice++) {
            std::cout << "Resultat de " << c << " * M" << uiIndice+1 << " :" << std::endl;
            (*pMATTableauMatricesFichier[uiIndice] * c).MATAfficherMatrice();
        }
        
        //Si on a au moins 2 matrices, on calcule leur somme (normale puis alternée avec soustraction) et leur produit :
        if (uiNbMatrices >= 2) {
            
            CMatrice<double> pMATResultat(*pMATTableauMatricesFichier[0]);
            
            std::cout << "Resultat de M1";
            for (unsigned int uiIndice = 1; uiIndice < uiNbMatrices; uiIndice++) {
                std::cout << " + M"<<uiIndice+1;
                //pMATResultat = pMATResultat + *pMATTableauMatricesFichier[uiIndice];
            }
            std::cout << " : " <<std::endl;
            pMATResultat.MATAfficherMatrice();
            
            pMATResultat = *pMATTableauMatricesFichier[0];
            
            std::cout << "Resultat de M1";
            int iOperation;
            for (unsigned int uiIndice = 1; uiIndice < uiNbMatrices; uiIndice++) {
                iOperation = (int)pow(-1, uiIndice+1);
                std::cout << " + ("<< iOperation << ")*M" << uiIndice+1;
                //pMATResultat = pMATResultat + iOperation  * (*pMATTableauMatricesFichier[uiIndice]);
            }
            std::cout << " : " << std::endl;
            pMATResultat.MATAfficherMatrice();
            
            std::cout << "Resultat de M1";
            for (unsigned int uiIndice = 1; uiIndice < uiNbMatrices; uiIndice++) {
                std::cout << " * M" << uiIndice + 1;
                //pMATResultat = pMATResultat * (*pMATTableauMatricesFichier[uiIndice]);
            }
            std::cout << " : " << std::endl;
            pMATResultat.MATAfficherMatrice();
        }
    }
    
    
    CMatrice<int> a(1,1);
    CMatrice<int> b(1,1);
    a.MATModifierElement(1, 0, 0);
    b.MATModifierElement(1, 0, 0);
    ((a + b)/2).MATAfficherMatrice();
    
    CMatrice<int> c = a+b;
    c = a + b;
    
    
    system("pause");
    return 0;
}


