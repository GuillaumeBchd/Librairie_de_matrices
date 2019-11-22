#include "CParser.h"

/**
 * \fn int COperationsComplexesMatrices::OCMLectureMot(std::ifstream& fichier, char * pcMot)
 * \brief Fonction nécessaire au bon fonctionnement de OCMLireFichier : Lecture du mot suivant du ifstream & fichier passé en paramètre
 *
 * \param fichier ifstream & : fichier ouvert (au moins en mode lecture),
 * \param pcMot char * : chaine de caractères ou sera stocké
 * \return 0=mot-clé, 1=endOfFile (fichier.oef()) et 5=valeur.
 */
int CParser::PARLectureMot(std::ifstream & fichier, char * pcMot)
{
    char cMyChar;
    unsigned int uiIndice = 0;
    
    //Tant que l'on a pas atteint la fin du fichier, on continue le programme :
    while (!fichier.eof()) {
        fichier.get(cMyChar);
        //Si on lit un caractere qui démarque la séparation d'un mot, arrete de remplir pcMot et on avance jusqu'au prochain mot
        if (cMyChar == ' ' || cMyChar == '\n' || cMyChar == '=') {
            while ((cMyChar == ' ' || cMyChar == '\n' || cMyChar == '=') && !fichier.eof()) {
                if (cMyChar == '=') {
                    pcMot[uiIndice] = '\0';
                    return 5;
                }
                fichier.get(cMyChar);
            }
            pcMot[uiIndice] = '\0';
            if (uiIndice > 0) {
                fichier.unget();
                return 0;
            }
            uiIndice = 0;
        }
        //Dernière ligne du fichier
        if (fichier.eof() || fichier.fail()) {
            pcMot[uiIndice] = '\0';
            return 0;
        }
        pcMot[uiIndice] = cMyChar;
        uiIndice++;
    }
    pcMot[uiIndice] = '\0';
    if (uiIndice > 0) {
        fichier.unget();
        return 0;
    }
    
    return 0;
}

/**
 * \fn int COperationsComplexesMatrices::OCMStringCompare(char * pcString1, const char * pcString2)
 * \brief Fonction nécessaire au bon fonctionnement de OCMLireFichier : On compare si deux chaînes de caractères sont identiques.
 *
 * \param pcString1 char * : Premiere chaine à comparer.
 * \param pcString2 const char * Deuxième chaine (constante) à comparer.
 * \return 0=Les chaines sont différentes et 1=Les chaines sont identiques.
 */
int CParser::PARStringCompare(char * pcString1, const char * pcString2)
{
    char *pcPointeur1 = pcString1;
    const char *pcPointeur2 = pcString2;
    while (*pcPointeur1 == *pcPointeur2) {
        if (*pcPointeur1 == '\0' && *pcPointeur2 == '\0') {
            return 1;
        }
        pcPointeur1++;
        pcPointeur2++;
    }
    return 0;
}

/**
 * \fn int COperationsComplexesMatrices::OCMGetCodeMotCle(char * pcString)
 * \brief Fonction nécessaire au bon fonctionnement de OCMLireFichier : On récupère le numéro d'un mot-clé.
 *
 * \param pcString char * : Mot-clé dont on désire récupérer le code.
 * \return -1=Mot-clé inconnu, sinon code correspondant à la position dans pcMotsCles.
 */
int CParser::PARGetCodeMotCle(char * pcString)
{
    for (int iIndice = 0; iIndice < sizeof(pcMotsCles); iIndice++) {
        if (PARStringCompare(pcString, pcMotsCles[iIndice])) {
            return iIndice;
        }
    }
    
    return -1;
}

/**
 * \fn int COperationsComplexesMatrices::OCMGetCodeValeur(char * pcString)
 * \brief Fonction nécessaire au bon fonctionnement de OCMLireFichier : On récupère le numéro d'une valeur.
 *
 * \param pcString char * : Valeur dont on désire récupérer le code.
 * \return -1=Valeur inconnue, sinon code correspondant à la position dans pcValeurs.
 */
int CParser::PARGetCodeValeur(char * pcString)
{
    for (int iIndice = 0; iIndice < sizeof(pcValeurs); iIndice++) {
        if (PARStringCompare(pcString, pcValeurs[iIndice])) {
            return iIndice;
        }
    }
    
    return -1;
}

/**
 * \fn template <class MType> CMatrice<MType> & COperationsComplexesMatrices::OCMLireFichier(char * pcNomFichier)
 * \brief Fonction qui lit le contenu d'un fichier et crée une nouvelle matrice allouée dynamiquement.
 *
 * \param pcNomFichier char * : Chemin du fichier à lire.
 * \return CMatrice<MType> & : Une nouvelle matrice allouée dynamiquement.
 */
template <class MType> CMatrice<MType> & CParser::PARLireFichier(char * pcNomFichier)
{
    std::ifstream fichier(pcNomFichier, std::ios::in);  // ouvrir le fichier en mode lecture
    
    if (fichier) { // Si on a pu ouvrir
        char pcMotCle[256];
        int iCode = 0;
        
        // Valeurs récupérées pour créer la matrice :
        unsigned int uiNbColonnes;
        unsigned int uiNbLignes;
        unsigned int uiTabSize = 2;
        unsigned int uiNbValeursTrouvee = 0;
        double *pValeursMatrice = (double*)malloc((uiTabSize) * sizeof(double));
        
        while (((iCode = PARLectureMot(fichier, pcMotCle)) != 1) && !fichier.eof() && !fichier.fail()) {
            
            if (iCode == 5) { //On doit forcément commencer par lire un mot-clé, sinon exception
                
                if ((iCode = PARGetCodeMotCle(pcMotCle)) != -1) { //On vérifie ensuite que le mot-clé est connu
                    
                    switch (iCode) {
                        case 0: //TypeMatrice
                            //On s'attend ici à lire une valeur pour TypeMatrice, sinon exception
                            if (((iCode = PARLectureMot(fichier, pcMotCle)) != 1)) {
                                //On vérifie ensuite que le TYPE est bien double :
                                if ((iCode = PARGetCodeValeur(pcMotCle)) == 0) {
                                    //Rien a faire ici, on confirme que c'est bien un double, sinon exception
                                    //puisqu'il n'y a que double
                                }
                                else {
                                    CException EXCUnknownMatrixType(EXC_UnknownMatrixType);
                                    throw EXCUnknownMatrixType;
                                }
                            }
                            else {
                                CException EXCUnexpectedSymbol(EXC_UnexpectedSymbol);
                                throw EXCUnexpectedSymbol;
                            }
                            break;
                            
                        case 1: //NBLignes
                            //On s'attend ici à lire une valeur pour TypeMatrice, sinon exception
                            if (((iCode = PARLectureMot(fichier, pcMotCle)) != 1)) {
                                uiNbLignes = std::atoi(pcMotCle);
                            }
                            else {
                                CException EXCUnexpectedSymbol(EXC_UnexpectedSymbol);
                                throw EXCUnexpectedSymbol;
                            }
                            break;
                            
                        case 2: //NBColonnes
                            //On s'attend ici à lire une valeur pour TypeMatrice, sinon exception
                            if (((iCode = PARLectureMot(fichier, pcMotCle)) != 1)) {
                                uiNbColonnes = std::atoi(pcMotCle);
                            }
                            else {
                                CException EXCUnexpectedSymbol(EXC_UnexpectedSymbol);
                                throw EXCUnexpectedSymbol;
                            }
                            break;
                            
                        case 3: //Matrice
                            if (((iCode = PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle == '[') {
                                int iIndice = 0;
                                while (((iCode = PARLectureMot(fichier, pcMotCle)) != 1) && *pcMotCle != ']') {
                                    if (uiTabSize == iIndice) {
                                        uiTabSize = uiTabSize * 2;
                                        pValeursMatrice = (double *)realloc(pValeursMatrice, (uiTabSize * 2 + 1) * sizeof(double));
                                    }
                                    pValeursMatrice[iIndice] = std::atof(pcMotCle);
                                    iIndice++;
                                    uiNbValeursTrouvee++;
                                }
                            }
                            else {
                                CException EXCUnexpectedKeyWord(EXC_UnexpectedKeyWord);
                                throw EXCUnexpectedKeyWord;
                            }
                            
                            //lecture du ']' de fermeture :
                            if (*pcMotCle != ']') {
                                CException EXCUnexpectedKeyWord(EXC_UnexpectedKeyWord);
                                throw EXCUnexpectedKeyWord;
                            }
                            break;
                            
                        default: //Cas possible pour [ et ] mal placés et si on rajoute des mots clés non gérés dans pcMotsCles
                            CException EXCUnexpectedKeyWord(EXC_UnexpectedKeyWord);
                            throw EXCUnexpectedKeyWord;
                            break;
                    }
                }
                else {
                    CException EXCUnexpectedSymbol(EXC_UnexpectedSymbol);
                    throw EXCUnexpectedSymbol;
                }
            }
            else {
                CException EXCUnexpectedSymbol(EXC_UnexpectedSymbol);
                throw EXCUnexpectedSymbol;
            }
        }
        fichier.close();
        
        //Si le nombre de valeurs lues et la taille de la matrice sont incohérentes, erreur.
        if (uiNbLignes * uiNbColonnes != uiNbValeursTrouvee) {
            CException EXCMatrixParameters(EXC_InvalidMatrixParameters);
            throw EXCMatrixParameters;
        }
        
        //On alloue dynamiquement ici la matrice qui sera renvoyée par notre fonction
        CMatrice<double> *pMatrice = new CMatrice<double>(uiNbLignes, uiNbColonnes);
        
        //Puis on parcourt notre tableau de valeurs pValeursMatrice pour remplir notre nouvelle matrice
        unsigned int uiIndiceTableauValeurs = 0;
        for (unsigned int uiIndiceLigne = 0; uiIndiceLigne < uiNbLignes; uiIndiceLigne++) {
            for (unsigned int uiIndiceColonne = 0; uiIndiceColonne < uiNbColonnes; uiIndiceColonne++) {
                pMatrice->MATModifierElement(pValeursMatrice[uiIndiceTableauValeurs], uiIndiceLigne, uiIndiceColonne);
                uiIndiceTableauValeurs++;
            }
        }
        return *pMatrice;
    }
    else {
        CException EXCOuvertureFichier(EXC_OuvertureFichier);
        throw EXCOuvertureFichier;
    }
    
    //Normalement impossible d'arriver jusqu'ici, mais dans le doute...
    CException EXCUnknownError(EXC_UnknownError);
    throw EXCUnknownError;
}


