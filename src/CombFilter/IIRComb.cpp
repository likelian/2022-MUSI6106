//
//  IIRComb.cpp
//  MUSI6106
//
//  Created by 李克镰 on 2/10/22.
//

#include "IIRComb.h"


Error_t CIIRComb::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{
    
    for (int i = 0; i < iNumberOfFrames; i++){
        for (int c = 0; c < m_iNumberOfChannels; c++)
        {

            ppfOutputBuffer[c][i] = ppfInputBuffer[c][i] +
                                           m_ParamGain * pCRingBuff[c]->getPostInc();
            
            pCRingBuff[c]->putPostInc(ppfOutputBuffer[c][i]);
            
        }
        
    }
    
    return Error_t::kNoError;
}


