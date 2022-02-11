//
//  CombFilter.h
//  sndlib
//
//  Created by 李克镰 on 2/8/22.
//

#ifndef CombFilter_h
#define CombFilter_h
//#include <CombFilterIf.h>
#include "ErrorDef.h"
#include <RingBuffer.h>
//#include <IIRComb.h>



class CCombFilterBase
{
public:

    /*! feedforward or recursive comb filter */
    enum CombFilterType_t
    {
        kCombFIR,           //!< finite impulse response filter
        kCombIIR,           //!< infinite impulse response filter

        kNumFilterTypes
    };

    /*! list of parameters for the comb filters */
    enum FilterParam_t
    {
        kParamGain,         //!< gain as factor (usually -1...1)
        kParamDelay,        //!< delay in seconds for specification of comb width

        kNumFilterParams
    };


    /*! creates a new comb filter instance
    \param pCCombFilter  pointer to the new class
    \return Error_t
    */
    Error_t create (CCombFilterBase*& pCCombFilter);
    
    /*! destroys a comb filter instance
    \param pCCombFilter pointer to the class to be destroyed
    \return Error_t
    */
    Error_t destroy (CCombFilterBase*& pCCombFilter);
    
    /*! initializes a comb filter instance
    \param eFilterType FIR or IIR
    \param fMaxDelayLengthInS maximum allowed delay in seconds
    \param fSampleRateInHz sample rate in Hz
    \param iNumChannels number of audio channels
    \return Error_t
    */
    Error_t init (float fMaxDelayLengthInS, float fSampleRateInHz, int iNumChannels);
    
    /*! resets the internal variables (requires new call of init)
    \return Error_t
    */
    Error_t reset ();

    /*! sets a comb filter parameter
    \param eParam what parameter (see ::FilterParam_t)
    \param fParamValue value of the parameter
    \return Error_t
    */
    Error_t setParam (int iParam, float fParamValue);
    
    /*! return the value of the specified parameter
    \param eParam
    \return float
    */
    float   getParam (int iParam) const;
    
    /*! processes one block of audio
    \param ppfInputBuffer input buffer [numChannels][iNumberOfFrames]
    \param ppfOutputBuffer output buffer [numChannels][iNumberOfFrames]
    \param iNumberOfFrames buffer length (per channel)
    \return Error_t
    */
    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

    CCombFilterBase ();
    virtual ~CCombFilterBase ();
    
protected:

private:
    bool            m_bIsInitialized;   //!< internal bool to check whether the init function has been called
    //CCombFilterBase *m_pCCombFilter;    //!< handle of the comb filter

    float           m_fSampleRate;      //!< audio sample rate in Hz
    int             m_iNumberOfChannels;//!< number of chaneels in int
    
    float           m_ParamGain;         //!< gain as factor (usually -1...1)
    float           M_ParamDelay;        //!< delay in seconds for specification of comb width
    
    CRingBuffer<float> **pCRingBuff;
    
};


#endif /* CombFilter_h */
