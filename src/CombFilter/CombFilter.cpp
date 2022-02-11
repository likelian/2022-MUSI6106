//
//  CombFilter.cpp
//  AudioFileIO
//
//  Created by 李克镰 on 2/8/22.
//
#include <string>
#include <fstream>
#include <algorithm>
#include "ErrorDef.h"

#include "CombFilter.h"

#include <IIRComb.h>
#include <FIRComb.h>




CCombFilterBase::CCombFilterBase () :
    m_bIsInitialized(false),
    //m_pCCombFilter(0),
    m_fSampleRate(0)
{
    // this should never hurt
    this->reset ();
}


CCombFilterBase::~CCombFilterBase ()
{
    this->reset ();
}


Error_t CCombFilterBase::create(CCombFilterBase *&pCCombFilter)
{
    
    return Error_t::kNoError;
}


Error_t CCombFilterBase::destroy(CCombFilterBase *&pCCombFilter)
{
    
    return Error_t::kNoError;
}


Error_t CCombFilterBase::init (float fMaxDelayLengthInS, float fSampleRateInHz, int iNumChannels)
{


    m_iNumberOfChannels = iNumChannels;
    
    static const int kBlockSize = (int)(fMaxDelayLengthInS * fSampleRateInHz);
    
    CRingBuffer<float> *pCRingBuff[iNumChannels];

    for(int i = 0; i < iNumChannels; i++){
        pCRingBuff[i] = new CRingBuffer<float>(kBlockSize);
    }
    
    
    return Error_t::kNoError;
}

Error_t CCombFilterBase::reset ()
{
    //resets the internal variables (requires new call of init)
    
    return Error_t::kNoError;
}

Error_t CCombFilterBase::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
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

Error_t CCombFilterBase::setParam (int iParam, float fParamValue)
{
    FilterParam_t eParam = (FilterParam_t)iParam;
        
    switch(eParam){
        case FilterParam_t::kParamGain:
            if (fParamValue<-1. || fParamValue>1.){
                return Error_t::kFunctionInvalidArgsError;
            }
            m_ParamGain = fParamValue;
            
        case FilterParam_t::kParamDelay:
            M_ParamDelay = fParamValue;
            
        case kNumFilterParams:kNumFilterParams:
            break;
    }
    
    return Error_t::kNoError;
}

float CCombFilterBase::getParam (int iParam) const
{
    FilterParam_t eParam = (FilterParam_t)iParam;
        
    switch(eParam){
        case FilterParam_t::kParamGain:
            return m_ParamGain;
            
        case FilterParam_t::kParamDelay:
            return M_ParamDelay;
            
        case kNumFilterParams:kNumFilterParams:
            break;
    }
    
}
