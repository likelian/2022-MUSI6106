//
//  CombFilter.h
//  sndlib
//
//  Created by 李克镰 on 2/8/22.
//

#ifndef CombFilter_h
#define CombFilter_h
#include <CombFilterIf.h>
#include <RingBuffer.h>





class CCombFilterBase: public CCombFilterIf
{
public:
    //CCombFilterBase ();
    //~CCombFilterBase ();
};


class CCombFIR: public CCombFilterBase
{
public:
    //CIIRCombFilter ();
    //~CIIRCombFilter ();
        
protected:
        
private:
    

};

class CCombIIR: public::CCombFilterBase
{
public:
            
protected:
            
private:
    
};




#endif /* CombFilter_h */
