#ifndef CException_h
#define CException_h

#include <stdio.h>

class CException {

	//Attributs
private:
	unsigned int uiEXCErreur;

	//Méthodes
public:
	CException(unsigned int uiErreur) {
		uiEXCErreur = uiErreur;
	}
	unsigned int EXCLireErreur() {
		return uiEXCErreur;
	}
	void EXCModifierErreur(unsigned int uiErreur) {
		uiEXCErreur = uiErreur;
	}
};

#endif /* CException_h */