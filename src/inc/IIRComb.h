//
//  IIRComb.hpp
//  MUSI6106
//
//  Created by 李克镰 on 2/10/22.
//

#ifndef IIRComb_h
#define IIRComb_h

#include <stdio.h>
#include <CombFilter.h>




class CIIRComb: public CCombFilterBase
{
public:
    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) override;
    
protected:
            
private:
    
};


#endif /* IIRComb_h */
