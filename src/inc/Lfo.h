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
        mReadIdx = 0.0;
        mTable = new float[mTableLength];
    }
    
    
    /*
     inFreq, frequency in Hz
     inAmp, amplitude range from 0. to 1.
     inNumSamplesToRender, the length of output buffer
    
     mBuffer is filled, but not returned
     */
    void process(float inFreq = 440.f,
                 float inAmp  = .5f,
                 int inNumSamplesToRender)
    {
        assert(inFreq > 0.f); //negative frequency
        assert(inFreq <= 0.5f * (float) mSampleRate); //alising
        assert(inDepth >= 0.f || inDepth <= 1.f); //amplitude range
        assert(inNumSamplesToRender > 0); //positive buffer size
        
        
        //allocate the output buffer
        mBuffer = new float[inNumSamplesToRender];
        
        //increment in samples
        const float increment = inFreq * mTableLength / mSampleRate;
        
        
        for(int i = 0; i < inNumSamplesToRender; i++){
            
            //increment the readIdx by floating point samples
            mReadIdx += increment;
            
            
            const float fTableLength = (float)mTableLength;
            //wrap around
            while (mReadIdx >= fTableLength){
                mReadIdx -= fTableLength;
            }
            //wrap around for mReadIdx+1
            if (mReadIdx+1 >= fTableLength){
                mReadIdx -= fTableLength;
            }
            
            //fraction ratio
            float fraction = mReadIdx-floor(mReadIdx);
            //linear interpolation
            const int iReadIdx = (int)mReadIdx;
            float interpolated = (1 - fraction) * mTable[iReadIdx] + fraction * mTable[iReadIdx+1];
            mBuffer[i] = interpolated; //put value into output buffer
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
    float mReadIdx;
    float* mBuffer;
};
#endif /* Lfo_h */
