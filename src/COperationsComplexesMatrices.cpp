#include "COperationsComplexesMatrices.h"
template <class MType>  CMatrice<MType> & COperationsComplexesMatrices::OCMTransposee(CMatrice<MType> & MATMatrice)
{
    CMatrice<MType> *pMatrice = new CMatrice<MType>(MATMatrice.MATGetNbColonnes(), MATMatrice.MATGetNbLignes());
    
    for (unsigned int iIndiceColonne = 0; iIndiceColonne < MATMatrice.MATGetNbColonnes(); iIndiceColonne++) {
        
        for (unsigned int iIndiceLigne = 0; iIndiceLigne < MATMatrice.MATGetNbLignes(); iIndiceLigne++) {
            pMatrice->MATModifierElement(MATMatrice.MATGetElement(iIndiceLigne, iIndiceColonne), iIndiceColonne, iIndiceLigne);
        }
        
    }
    return *pMatrice;
}

//Les deux matrices doivent être de mêmes dimensions
template <class MType1, class MType2> auto operator+(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2)
{
    if (MATMatrice1.MATGetNbColonnes() != MATMatrice2.MATGetNbColonnes() || MATMatrice1.MATGetNbLignes() != MATMatrice2.MATGetNbLignes()) {
        CException EXCDifferentDimensions(EXC_DifferentDimensions);
        throw EXCDifferentDimensions;
    }
    
    //On trouve automatiquement le type de la nouvelle matrice en regardant le premier élément de chaque matrice et grace ) delctype
    CMatrice<decltype(MATMatrice1.MATGetElement(0, 0) + MATMatrice2.MATGetElement(0, 0))> MATResult(MATMatrice1.MATGetNbLignes(), MATMatrice1.MATGetNbColonnes());
    
    for (unsigned int uiCompteurLignes = 0; uiCompteurLignes < MATMatrice1.MATGetNbLignes(); uiCompteurLignes++) {
        
        for (unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < MATMatrice1.MATGetNbColonnes(); uiCompteurColonnes++) {
            
            MATResult.MATModifierElement(MATMatrice1.MATGetElement(uiCompteurLignes, uiCompteurColonnes) + MATMatrice2.MATGetElement(uiCompteurLignes, uiCompteurColonnes), uiCompteurLignes, uiCompteurColonnes);
            
        }
    }
    return MATResult;
}


//Les deux matrices doivent être de mêmes dimensions
template <class MType1, class MType2> auto operator-(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2)
{
    
    if (MATMatrice1.MATGetNbColonnes() != MATMatrice2.MATGetNbColonnes() || MATMatrice1.MATGetNbLignes() != MATMatrice2.MATGetNbLignes()) {
        CException EXCDifferentDimensions(EXC_DifferentDimensions);
        throw EXCDifferentDimensions;
    }
    
    //On trouve automatiquement le type de la nouvelle matrice en regardant le premier élément de chaque matrice et grace ) delctype
    CMatrice<decltype(MATMatrice1.MATGetElement(0, 0) + MATMatrice2.MATGetElement(0, 0))> MATResult(MATMatrice1.MATGetNbLignes(), MATMatrice1.MATGetNbColonnes());
    
    for (unsigned int uiCompteurLignes = 0; uiCompteurLignes < MATMatrice1.MATGetNbLignes(); uiCompteurLignes++) {
        
        for (unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < MATMatrice1.MATGetNbColonnes(); uiCompteurColonnes++) {
            
            MATResult.MATModifierElement(MATMatrice1.MATGetElement(uiCompteurLignes, uiCompteurColonnes) - MATMatrice2.MATGetElement(uiCompteurLignes, uiCompteurColonnes), uiCompteurLignes, uiCompteurColonnes);
            
        }
    }
    return MATResult;
    
}


// Mat1 doit avoir le même nombre de colonnes que Mat2 a de lignes.
template <class MType1, class MType2> auto operator*(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2)
{
    
    if (MATMatrice1.MATGetNbColonnes() != MATMatrice2.MATGetNbLignes()) {
        CException EXCInvalidDimensions(EXC_InvalidDimensions);
        throw EXCInvalidDimensions;
    }
    
    //On trouve automatiquement le type de la nouvelle matrice en regardant le premier élément de chaque matrice et grace ) delctype
    CMatrice<decltype(MATMatrice1.MATGetElement(0, 0) + MATMatrice2.MATGetElement(0, 0))> MATResult(MATMatrice1.MATGetNbLignes(), MATMatrice2.MATGetNbColonnes());
    
    //On parcourt tout les éléments du result
    for (unsigned int uiCompteurLignes = 0; uiCompteurLignes < MATResult.MATGetNbLignes(); uiCompteurLignes++) {
        
        for (unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < MATResult.MATGetNbColonnes(); uiCompteurColonnes++) {
            
            auto MTPElement = MATMatrice1.MATGetElement(uiCompteurLignes, 0) * MATMatrice2.MATGetElement(uiCompteurColonnes, 0);
            for (unsigned int uiIter = 1; uiIter < MATMatrice1.MATGetNbLignes(); uiIter++) {
                MTPElement = MTPElement + MATMatrice1.MATGetElement(uiCompteurLignes, uiIter) * MATMatrice2.MATGetElement(uiCompteurColonnes, uiIter);
            }
            
            MATResult.MATModifierElement(MTPElement, uiCompteurLignes, uiCompteurColonnes);
        }
    }
    
    
    return MATResult;
}


