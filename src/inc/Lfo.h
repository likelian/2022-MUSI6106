//
//  Lfo.h
//  TestExec
//
//  Created by 李克镰 on 2/26/22.
//
#ifndef Lfo_h
#define Lfo_h
#include <math.h>
#pragma once
class Lfo
{
    
public:
    //constructor
    Lfo()
    {
        reset();
        
        mTableLength = 25000;
 
        //initial the sine wavetable
        for(int i = 0; i < mTableLength; i++){
            mTable[i] = sinf(2. * i/(float)mTableLength * M_PI);
        }
    }
    
    
    //destructor
    ~Lfo()
    {
        delete [] mTable;
        delete [] mBuffer;
    }
    
    
    //setSampleRate
    void setSampleRate(float inSampleRate)
    {
        mSampleRate = inSampleRate;
    }
    
    
    //reset
    void reset()
    {
        mPhase = 0.0;
        mTable = new float[mTableLength];
    }
    
    
    
    /*
     inRate in Hz
     inDepth in amplitude
     inNumSamplesToRender in int
     */
    void process(float inRate,
                 float inDepth,
                 int inNumSamplesToRender)
    {
        assert(inRate > 0.f);
        assert(inDepth > 0.f || inDepth < 1.f);
        assert(inNumSamplesToRender > 0);
        
        std::cout << "mTableLength" << mTableLength << std::endl;
        std::cout << "mTable[10]" << mTable[10] << std::endl;
        
        //allocate the output buffer
        mBuffer = new float[inNumSamplesToRender];
        
        const float increment = inRate / mSampleRate;
        
        for(int i = 0; i < inNumSamplesToRender; i++){
            
            mPhase += increment;
            
            if(mPhase > 1.f){
                mPhase = mPhase - 1.f;
            }
            
            //float tableIdx = mPhase * mTableLength;
            int tableIdx = (int)(mPhase * mTableLength);
            mBuffer[i] = mTable[tableIdx]; //lookup the wavetable
        }
    }
    
    
    float* getBuffer()
    {
        return mBuffer;
    }
    
private:
    float mSampleRate;
    int mTableLength;
    float* mTable;
    float mPhase;
    float* mBuffer;
};
#endif /* Lfo_h */
