//
//  IIRComb.hpp
//  MUSI6106
//
//  Created by 李克镰 on 2/10/22.
//

#ifndef FIRComb_h
#define FIRComb_h

#include <stdio.h>
#include <CombFilter.h>




class CFIRComb: public::CCombFilterBase
{
public:
    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) override;
            
protected:
            
private:
    
};


#endif /* FIRComb_h */
