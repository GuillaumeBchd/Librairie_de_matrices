#ifndef COperationsComplexesMatrices_h
#define COperationsComplexesMatrices_h

//#include "CMatrice.h"
template <class MType> class CMatrice;

#include "CException.h"

#define EXC_DifferentDimensions 206
#define EXC_InvalidDimensions 207

class COperationsComplexesMatrices
{
    //MŽthodes
public:
    template <class MType> static CMatrice<MType> & OCMTransposee(CMatrice<MType> & MATMatrice);
};

template <class MType1, class MType2> static auto operator+(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2);
template <class MType1, class MType2> static auto operator-(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2);
template <class MType1, class MType2> static auto operator*(CMatrice<MType1> & MATMatrice1, CMatrice<MType2> & MATMatrice2);

#include "COperationsComplexesMatrices.cpp"

#endif /* COperationsComplexesMatrices_h */


