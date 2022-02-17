
// standard headers

// project headers
#include "MUSI6106Config.h"

#include "ErrorDef.h"
#include "Util.h"
#include "CombFilterIf.h"
#include "RingBuffer.h"
#include "CombFilter.h"
#include "FIRComb.h"
#include "IIRComb.h"
#include <list>



static const char*  kCMyProjectBuildDate = __DATE__;


CCombFilterIf::CCombFilterIf () :
    m_bIsInitialized(false),
    m_pCCombFilter(0),
    m_fSampleRate(0)
{
    // this should never hurt
    //this->reset ();
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

    //CCombFilterBase *m_pCCombFilter = 0;
    
    pCCombFilter = new CCombFilterIf ();
    //m_pCCombFilter = new CCombFilterBase ();
    
    //CCombFilterBase * something;
    //m_pCCombFilter->create(something); //only return error

    /*
     It is admirable that you check for this, but the new operator (unlike C's malloc()) does not return NULL on failure to allocate; instead it throws an exception (std::bad_alloc).

     */
//    if (!pCCombFilter){
//        return Error_t::kMemError;
//    }
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::destroy (CCombFilterIf*& pCCombFilter)
{
    delete pCCombFilter;
    pCCombFilter = 0;
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::init (CombFilterType_t eFilterType, float fMaxDelayLengthInS, float fSampleRateInHz, int iNumChannels)
{
    
    //call base
    
    if(eFilterType == kCombFIR){
        m_pCCombFilter = new CFIRComb ();
    }
    else if (eFilterType == kCombIIR){
        m_pCCombFilter = new CIIRComb ();
    }
    
    
    Error_t initError = m_pCCombFilter->init(fMaxDelayLengthInS, fSampleRateInHz, iNumChannels);
    
    m_bIsInitialized = true;
    
    return initError;
}

Error_t CCombFilterIf::reset ()
{
    //resets the internal variables (requires new call of init)
    
    m_pCCombFilter->reset();
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    
    if (!m_bIsInitialized){
        return Error_t::kNotInitializedError;
    };
    
    if (!ppfInputBuffer || !ppfOutputBuffer[0] || iNumberOfFrames < 0)
        return Error_t::kFunctionInvalidArgsError;
    
    
    m_pCCombFilter->process(ppfInputBuffer, ppfOutputBuffer, iNumberOfFrames);
    
    
    return Error_t::kNoError;
}

Error_t CCombFilterIf::setParam (FilterParam_t eParam, float fParamValue)
{
    
    m_pCCombFilter->setParam(static_cast<FilterParam_t>(eParam), fParamValue);
    
    return Error_t::kNoError;
}

float CCombFilterIf::getParam (FilterParam_t eParam) const
{
    return m_pCCombFilter->getParam(static_cast<FilterParam_t>(eParam));
}
