/**
 * \file CMatrice.cpp
 * \brief Fichier de méthodes de la classe CMatrice.
 * \author Guillaume.Bouchard Colin.Troisemaine
 * \version 0.1
 * \date 30 avril 2019
 *
 * Fichier de méthodes d'une classe template et donc inclus à la fin du .h, exclure ce cpp du projet pour
 * le bon fonctionnement de celui-ci.
 *
 */


/***
 Constructeurs
 ***/

/**
 * \fn  template<class MType> CMatrice<MType>::CMatrice()
 * \brief Constructeur par défault de la classe CMatrice
 *
 */
template<class MType> CMatrice<MType>::CMatrice()
{
    pMATMatrice = NULL;
    uiMATLignes = 0;
    uiMATColonnes = 0;
}


/**
 * \fn template<class MType> CMatrice<MType>::CMatrice(unsigned int uiLigne, unsigned int uiColonne)
 * \brief Constructeur de confort de la classe CMatrice
 *
 * \param sz Chaîne à stocker dans l'objet Str_t, ne peut être NULL.
 * \return Instance nouvellement allouée d'un objet de type Str_t ou NULL.
 */
template<class MType> CMatrice<MType>::CMatrice(unsigned int uiLigne, unsigned int uiColonne)
{
    uiMATLignes = uiLigne;
    uiMATColonnes = uiColonne;
    
    if (uiMATLignes > 0 && uiMATColonnes > 0) {
        pMATMatrice = new MType*[uiLigne];
        if (pMATMatrice == NULL) {
            CException EXCMallocFail(EXC_MallocError);
            throw EXCMallocFail;
        }
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < uiLigne; uiCompteurLigne++) {
            pMATMatrice[uiCompteurLigne] = new MType[uiColonne];
            if (pMATMatrice[uiCompteurLigne] == NULL) {
                CException EXCMallocFail(EXC_MallocError);
                throw EXCMallocFail;
            }
        }
    }
}

template<class MType> CMatrice<MType>::CMatrice(CMatrice<MType> && MATMatrice)
{
    uiMATLignes = MATMatrice.uiMATLignes;
    uiMATColonnes = MATMatrice.uiMATColonnes;
    
    if (uiMATLignes > 0 && uiMATColonnes > 0) {
        pMATMatrice = new MType*[uiMATLignes];
        //pMATMatrice = (MType**)malloc(sizeof(MType*)* uiMATLignes);
        if (pMATMatrice == NULL) {
            CException EXCMallocFail(EXC_MallocError);
            throw EXCMallocFail;
        }
        
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            pMATMatrice[uiCompteurLigne] = new MType[uiMATColonnes];
            //pMATMatrice[uiCompteurLigne] = (MType*)malloc(sizeof(MType) *uiMATColonnes);
            if (pMATMatrice[uiCompteurLigne] == NULL) {
                CException EXCMallocFail(EXC_MallocError);
                throw EXCMallocFail;
            }
        }
        
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            for (unsigned int uiCompteurColonne = 0; uiCompteurColonne < MATMatrice.uiMATColonnes; uiCompteurColonne++) {
                pMATMatrice[uiCompteurLigne][uiCompteurColonne] = MATMatrice.pMATMatrice[uiCompteurLigne][uiCompteurColonne];
            }
        }
        
        uiMATLignes = MATMatrice.uiMATLignes;
        uiMATColonnes = MATMatrice.uiMATColonnes;
    }
}

template<class MType> CMatrice<MType>::CMatrice(CMatrice<MType> & MATMatrice)
{
    uiMATLignes = MATMatrice.uiMATLignes;
    uiMATColonnes = MATMatrice.uiMATColonnes;
    
    if (uiMATLignes > 0 && uiMATColonnes > 0) {
        pMATMatrice = new MType*[uiMATLignes];
        //pMATMatrice = (MType**)malloc(sizeof(MType*)* uiMATLignes);
        if (pMATMatrice == NULL) {
            CException EXCMallocFail(EXC_MallocError);
            throw EXCMallocFail;
        }
        
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            pMATMatrice[uiCompteurLigne] = new MType[uiMATColonnes];
            //pMATMatrice[uiCompteurLigne] = (MType*)malloc(sizeof(MType) *uiMATColonnes);
            if (pMATMatrice[uiCompteurLigne] == NULL) {
                CException EXCMallocFail(EXC_MallocError);
                throw EXCMallocFail;
            }
        }
        
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            for (unsigned int uiCompteurColonne = 0; uiCompteurColonne < MATMatrice.uiMATColonnes; uiCompteurColonne++) {
                pMATMatrice[uiCompteurLigne][uiCompteurColonne] = MATMatrice.pMATMatrice[uiCompteurLigne][uiCompteurColonne];
            }
        }
        
        uiMATLignes = MATMatrice.uiMATLignes;
        uiMATColonnes = MATMatrice.uiMATColonnes;
    }
}

/***
 Destructeurs
 ***/

template<class MType> CMatrice<MType>::~CMatrice()
{
    if (pMATMatrice != NULL) {
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < uiMATLignes; uiCompteurLigne++) {
            delete(pMATMatrice[uiCompteurLigne]);
            pMATMatrice[uiCompteurLigne] = NULL;
        }
        delete(pMATMatrice);
        pMATMatrice = NULL;
    }
}


/***
 Méthodes
 ***/


template<class MType> MType CMatrice<MType>::MATGetElement(unsigned int uiLigne, unsigned int uiColonne)
{
    if (uiLigne >= uiMATLignes || uiColonne >= uiMATColonnes) {
        CException EXCOutOfBounds(EXC_OutOfBounds);
        throw EXCOutOfBounds;
    }
    
    return pMATMatrice[uiLigne][uiColonne];
}

template<class MType> unsigned int CMatrice<MType>::MATGetNbLignes()
{
    return uiMATLignes;
}

template<class MType> unsigned int CMatrice<MType>::MATGetNbColonnes()
{
    return uiMATColonnes;
}

template<class MType> void CMatrice<MType>::MATModifierElement(MType MTPElement, unsigned int uiLigne, unsigned int uiColonne)
{
    if (uiLigne >= uiMATLignes || uiColonne >= uiMATColonnes) {
        CException EXCOutOfBounds(EXC_OutOfBounds);
        throw EXCOutOfBounds;
    }
    
    pMATMatrice[uiLigne][uiColonne] = MTPElement;
}

template<class MType> void CMatrice<MType>::MATAfficherMatrice()
{
    for (unsigned int iIndiceLigne = 0; iIndiceLigne < uiMATLignes; iIndiceLigne++) {
        for (unsigned int iIndiceColonne = 0; iIndiceColonne < uiMATColonnes; iIndiceColonne++) {
            std::cout << MATGetElement(iIndiceLigne, iIndiceColonne) << " ";
        }
        std::cout << std::endl;
    }
}



//Surcharge operateur simple

template<class MType> CMatrice<MType> & CMatrice<MType>::operator=(CMatrice<MType> & MATMatrice)
{
    if (MATMatrice.uiMATLignes > 0 && MATMatrice.uiMATColonnes > 0) {
        
        //Si la matrice n'est pas vide et possède déjà un tableau 2D alloué, on libère ce tableau (les éléments ne sont pas libérés).
        if(pMATMatrice != NULL){
            for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
                delete(pMATMatrice[uiCompteurLigne]);
                pMATMatrice[uiCompteurLigne] = NULL;
            }
            delete(pMATMatrice);
            pMATMatrice = NULL;
        }
        
        //On affecte les nouvelles valeurs nbDeLignes et nbDeColonnes
        uiMATLignes = MATMatrice.uiMATLignes;
        uiMATColonnes = MATMatrice.uiMATColonnes;
        
        //On crée le tableau 2D
        pMATMatrice = new MType*[uiMATLignes];
        if (pMATMatrice == NULL) {
            CException EXCMallocFail(EXC_MallocError);
            throw EXCMallocFail;
        }
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            pMATMatrice[uiCompteurLigne] = new MType[uiMATColonnes];
            if (pMATMatrice[uiCompteurLigne] == NULL) {
                CException EXCMallocFail(EXC_MallocError);
                throw EXCMallocFail;
            }
        }
        
        //On remplit la matrice.
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            for (unsigned int uiCompteurColonne = 0; uiCompteurColonne < MATMatrice.uiMATColonnes; uiCompteurColonne++) {
                pMATMatrice[uiCompteurLigne][uiCompteurColonne] = MATMatrice.pMATMatrice[uiCompteurLigne][uiCompteurColonne];
            }
        }
        
    }
    
    return *this;
}

template<class MType> CMatrice<MType> & CMatrice<MType>::operator=(CMatrice && MATMatrice)
{
    if (MATMatrice.uiMATLignes > 0 && MATMatrice.uiMATColonnes > 0) {
        
        //Si la matrice n'est pas vide et possède déjà un tableau 2D alloué, on libère ce tableau (les éléments ne sont pas libérés).
        if (pMATMatrice != NULL) {
            for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
                delete(pMATMatrice[uiCompteurLigne]);
                pMATMatrice[uiCompteurLigne] = NULL;
            }
            delete(pMATMatrice);
            pMATMatrice = NULL;
        }
        
        //On affecte les nouvelles valeurs nbDeLignes et nbDeColonnes
        uiMATLignes = MATMatrice.uiMATLignes;
        uiMATColonnes = MATMatrice.uiMATColonnes;
        
        //On crée le tableau 2D
        pMATMatrice = new MType*[uiMATLignes];
        if (pMATMatrice == NULL) {
            CException EXCMallocFail(EXC_MallocError);
            throw EXCMallocFail;
        }
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            pMATMatrice[uiCompteurLigne] = new MType[uiMATColonnes];
            if (pMATMatrice[uiCompteurLigne] == NULL) {
                CException EXCMallocFail(EXC_MallocError);
                throw EXCMallocFail;
            }
        }
        
        //On remplit la matrice.
        for (unsigned int uiCompteurLigne = 0; uiCompteurLigne < MATMatrice.uiMATLignes; uiCompteurLigne++) {
            for (unsigned int uiCompteurColonne = 0; uiCompteurColonne < MATMatrice.uiMATColonnes; uiCompteurColonne++) {
                pMATMatrice[uiCompteurLigne][uiCompteurColonne] = MATMatrice.pMATMatrice[uiCompteurLigne][uiCompteurColonne];
            }
        }
        
    }
    
    return *this;
}

template<class MType> CMatrice<MType> CMatrice<MType>::operator*(double dNombre)
{
    
    if(uiMATColonnes == 0 || uiMATLignes == 0){
        CException EXCInvalidDimensions(EXC_InvalidDimensions);
        throw EXCInvalidDimensions;
    }
    
    CMatrice<MType> MATResult(uiMATLignes, uiMATColonnes);
    
    if (MATResult.pMATMatrice == NULL) {
        CException EXCMallocFail(EXC_MallocError);
        throw EXCMallocFail;
    }
    
    
    //On parcourt tous les éléments du result
    for(unsigned int uiCompteurLignes = 0; uiCompteurLignes < uiMATLignes; uiCompteurLignes++){
        for(unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < uiMATColonnes; uiCompteurColonnes++){
            
            MATResult.pMATMatrice[uiCompteurLignes][uiCompteurColonnes] = pMATMatrice[uiCompteurLignes][uiCompteurColonnes] * dNombre;
            
        }
    }
    
    return MATResult;
}

template<class MType> CMatrice<MType> operator*(double dNombre, CMatrice<MType> & MATMatrice)
{
    
    if(MATMatrice.MATGetNbColonnes() == 0 || MATMatrice.MATGetNbLignes() == 0){
        CException EXCInvalidDimensions(EXC_InvalidDimensions);
        throw EXCInvalidDimensions;
    }
    
    CMatrice<MType> MATResult(MATMatrice.MATGetNbLignes(), MATMatrice.MATGetNbColonnes());
    
    if (MATResult.pMATMatrice == NULL) {
        CException EXCMallocFail(EXC_MallocError);
        throw EXCMallocFail;
    }
    
    
    //On parcourt tout les éléments du result
    for(unsigned int uiCompteurLignes = 0; uiCompteurLignes < MATMatrice.MATGetNbLignes(); uiCompteurLignes++){
        for(unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < MATMatrice.MATGetNbColonnes(); uiCompteurColonnes++){
            
            MType MTPElement = MATMatrice.MATGetElement(uiCompteurLignes, uiCompteurColonnes) * dNombre;
            //
            //
            // CHOISIR E*d ou d*E
            //
            //
            
            
            MATResult.MATModifierElement(MTPElement, uiCompteurLignes, uiCompteurColonnes);
            
        }
    }
    
    return MATResult;
}


template<class MType> CMatrice<MType> CMatrice<MType>::operator/(double dNombre)
{
    if(uiMATColonnes == 0 || uiMATLignes == 0){
        CException EXCInvalidDimensions(EXC_InvalidDimensions);
        throw EXCInvalidDimensions;
    }
    
    if(dNombre == 0){
        CException EXCDivisionByZero(EXC_DivisionByZero);
        throw(EXCDivisionByZero);
    }
    
    CMatrice<MType> MATResult(uiMATLignes, uiMATColonnes);
    
    if (MATResult.pMATMatrice == NULL) {
        CException EXCMallocFail(EXC_MallocError);
        throw EXCMallocFail;
    }
    
    //On parcourt tout les éléments du result
    for(unsigned int uiCompteurLignes = 0; uiCompteurLignes < uiMATLignes; uiCompteurLignes++){
        for(unsigned int uiCompteurColonnes = 0; uiCompteurColonnes < uiMATColonnes; uiCompteurColonnes++){
            
            MATResult.pMATMatrice[uiCompteurLignes][uiCompteurColonnes] = pMATMatrice[uiCompteurLignes][uiCompteurColonnes] / dNombre;
            
        }
    }
    
    return MATResult;
}
