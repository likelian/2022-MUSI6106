
#include "Vector.h"
#include "Util.h"
#include <algorithm>

#include "Dtw.h"


CDtw::CDtw( void ) :
    m_bIsInitialized(false)
{
    reset();
}

CDtw::~CDtw( void )
{
    reset();
}

Error_t CDtw::init( int iNumRows, int iNumCols )
{

    //allocate a direction matrix
    ppiDirectMatrix = new int*[iNumRows];
    for(int i = 0; i < iNumRows; i++)
    {
      ppiDirectMatrix[i] = new int [iNumCols];
    }
    
    mNumRows = iNumRows;
    mNumCols = iNumCols;
    
    m_bIsInitialized = true;
    return Error_t::kNoError;
}

Error_t CDtw::reset()
{
    m_bIsInitialized    = false;

    return Error_t::kNoError;
}

Error_t CDtw::process(float **ppfDistanceMatrix)
{
    if (!m_bIsInitialized)
        return Error_t::kNotInitializedError;

    if (!ppfDistanceMatrix)
        return Error_t::kFunctionInvalidArgsError;
    
    
    //https://github.com/alexanderlerch/pyACA/blob/master/pyACA/ToolSimpleDtw.py
    
//    DeltaP[0, :] = 2  # (0,-1)
//    DeltaP[:, 0] = 1  # (-1,0)
//    DeltaP[0, 0] = 0  # (-1,-1)
    

    
    for(int r = 1; r < mNumRows; r++)
    {
        for(int c = 1; c < mNumCols; c++){

//            int myints[] = {ppfDistanceMatrix[r - 1][c - 1], ppfDistanceMatrix[r -1][c], ppfDistanceMatrix[r][c - 1]};
//
//            std::vector<int> inVec {ppfDistanceMatrix[r - 1][c - 1], ppfDistanceMatrix[r -1][c], ppfDistanceMatrix[r][c - 1]};
//
//            ppiDirectMatrix[r][c] = *std::min_element(myints, myints+3);
            
            //std::min_element only works above C++17
            //https://en.cppreference.com/w/cpp/algorithm/min_element
//
            

            
            
            
            
            
            
        }
    }


    return Error_t::kNoError;
}

int CDtw::getPathLength()
{
    return -1;
}

float CDtw::getPathCost() const
{
    return -1.F;
}

Error_t CDtw::getPath( int **ppiPathResult ) const
{

    return Error_t::kNoError;
}

