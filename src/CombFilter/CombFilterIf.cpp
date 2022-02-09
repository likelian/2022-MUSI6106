
// standard headers

// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"
#include "Util.h"
#include "CombFilterIf.h"
#include "RingBuffer.h"
#include "CombFilter.cpp"
#include <list>


static const char*  kCMyProjectBuildDate = __DATE__;


CCombFilterIf::CCombFilterIf () :
    m_bIsInitialized(false),
    m_pCCombFilter(0),
    m_fSampleRate(0)
{
    // this should never hurt
    this->reset ();
}


CCombFilterIf::~CCombFilterIf ()
{
    this->reset ();
}

const int  CCombFilterIf::getVersion (const Version_t eVersionIdx)
{
    int iVersion = 0;

    switch (eVersionIdx)
    {
    case kMajor:
        iVersion    = MUSI6106_VERSION_MAJOR; 
        break;
    case kMinor:
        iVersion    = MUSI6106_VERSION_MINOR; 
        break;
    case kPatch:
        iVersion    = MUSI6106_VERSION_PATCH; 
        break;
    case kNumVersionInts:
        iVersion    = -1;
        break;
    }

    return iVersion;
}
const char*  CCombFilterIf::getBuildDate ()
{
    return kCMyProjectBuildDate;
}

Error_t CCombFilterIf::create (CCombFilterIf*& pCCombFilter)
{
    
    pCCombFilter = new CCombFilterBase ();
    
    if (!pCCombFilter)
        return Error_t::kMemError;
  
    return Error_t::kNoError;
}

Error_t CCombFilterIf::destroy (CCombFilterIf*& pCCombFilter)
{
    delete pCCombFilter;
    pCCombFilter  = 0;
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::init (CombFilterType_t eFilterType, float fMaxDelayLengthInS, float fSampleRateInHz, int iNumChannels)
{

    if (eFilterType == kCombFIR){
        m_pCCombFilter = new CCombFIR ();
    }
    else if (eFilterType == kCombIIR){
        m_pCCombFilter = new CCombIIR ();
    }else{
        return Error_t::kUnknownError;
    }
    
    m_iNumberOfChannels = iNumChannels;
    
    static const int kBlockSize = (int)(fMaxDelayLengthInS * fSampleRateInHz);
    
    CRingBuffer<float> *pCRingBuff[iNumChannels];

    for(int i = 0; i < iNumChannels; i++){
        pCRingBuff[i] = new CRingBuffer<float>(kBlockSize);
    }
    
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::reset ()
{
    //resets the internal variables (requires new call of init)
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    
    for (int i = 0; i < iNumberOfFrames; i++){
        for (int c = 0; c < m_iNumberOfChannels; c++)
        {
            float a = ppfInputBuffer[c][i];
            ppfOutputBuffer[c][i] = a;
        }
        
    }
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::setParam (FilterParam_t eParam, float fParamValue)
{
    return Error_t::kNoError;
}

float CCombFilterIf::getParam (FilterParam_t eParam) const
{
    return 0;
}
