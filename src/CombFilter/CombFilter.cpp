//
//  CombFilter.cpp
//  AudioFileIO
//
//  Created by 李克镰 on 2/8/22.
//
#include <iostream>
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
    m_fSampleRate(0),
    m_iNumberOfChannels(0),
    m_ParamGain(0),
    m_ParamDelay(0)
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

    m_fSampleRate = fSampleRateInHz;

    m_iNumberOfChannels = iNumChannels;
    
    m_fMaxDelayLengthInS = fMaxDelayLengthInS;
    
    static const int kBlockSize = (int)(fMaxDelayLengthInS * m_fSampleRate);
    
    pCRingBuff = new CRingBuffer<float> *[iNumChannels];
    for (int i = 0; i < iNumChannels; i++){
        pCRingBuff[i] = new CRingBuffer<float>(kBlockSize);
    }
    
    
    m_bIsInitialized = true;
    
    return Error_t::kNoError;
}

Error_t CCombFilterBase::reset ()
{
    //resets the internal variables (requires new call of init)
    
    
    for(int i = 0; i < m_iNumberOfChannels; i++){
        delete pCRingBuff[i];
    }
    
    m_fSampleRate = 0;
    m_iNumberOfChannels = 0;
    m_ParamGain = 0.;
    m_ParamDelay = 0.;
    
    m_bIsInitialized = false;
    
    
    return Error_t::kNoError;
}

Error_t CCombFilterBase::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    
    for (int i = 0; i < iNumberOfFrames; i++){
        for (int c = 0; c < m_iNumberOfChannels; c++)
        {

            ppfOutputBuffer[c][i] = pCRingBuff[c]->getPostInc();
            pCRingBuff[c]->putPostInc(ppfInputBuffer[c][i]);
            
        }
        
    }
    
    return Error_t::kNoError;
}

Error_t CCombFilterBase::setParam (int iParam, float fParamValue)
{
    FilterParam_t eParam = (FilterParam_t)iParam;
        
    switch(eParam){
        case FilterParam_t::kParamGain:
            if (fParamValue < -1. || fParamValue > 1.){
                return Error_t::kFunctionInvalidArgsError;
            }
            m_ParamGain = fParamValue;
            
        case FilterParam_t::kParamDelay:
            if (fParamValue < 0. || fParamValue >= m_fMaxDelayLengthInS){
                return Error_t::kFunctionInvalidArgsError;
            }
            
            m_ParamDelay = fParamValue;
            m_iDelayinSamples = (int) (m_ParamDelay * m_fSampleRate);
            for (int c = 0; c < m_iNumberOfChannels; c++){
                pCRingBuff[c]->setReadPtr(m_iDelayinSamples);
            }
            
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
            return m_ParamDelay;
            
        case kNumFilterParams:kNumFilterParams:
            break;
    }
    
}
