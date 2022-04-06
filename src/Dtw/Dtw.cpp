
#include "Vector.h"
#include "Util.h"

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
    
    
    for(int r = 0; r < mNumRows; r++)
    {
        for(int c = 0; c < mNumCols; c++){
            //fill the ppiDirectMatrix[r][c] = ?
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

