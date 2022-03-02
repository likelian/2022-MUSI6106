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
    Lfo():
    mSampleRate(0),
    mTableLength(0),
    mTable(0),
    mReadIdx(0),
    mBuffer(0)
    {
        //reset();
        mTableLength = 25000;
        mReadIdx = 0.f;
        mTable = new float[mTableLength];
        
        mSampleRate = 0;
        
        //initial the sine wavetable of one cycle
        for(int i = 0; i < mTableLength; i++){
            mTable[i] = sinf(2.f * i/(float)(mTableLength) * M_PI);
        }
    }
    
    
    //destructor
    ~Lfo()
    {
        delete [] mTable;
        mTable = 0;
        delete [] mBuffer;
        mBuffer = 0;
    }
    
    
    //setSampleRate
    void setSampleRate(int inSampleRate)
    {
        mSampleRate = inSampleRate;
    }
    
    
    //reset
    void reset()
    {
        mReadIdx = 0.f;
        mTable = new float[mTableLength];
    }
    
    
    /*
     inFreq, frequency in Hz
     inAmp, amplitude range from 0. to 1.
     inNumSamplesToRender, the length of output buffer
    
     mBuffer is filled, but not returned
     */
    void process(int inNumSamplesToRender,
                 float inFreq = 440.f,
                 float inAmp  = 0.5f)
    {
        assert(inFreq > 0.f); //negative frequency
        assert(inFreq <= 0.5f * (float) mSampleRate); //alising
        assert(inAmp >= 0.f || inAmp <= 1.f); //amplitude range
        assert(inNumSamplesToRender > 0); //positive buffer size
        
        
        //allocate the output buffer
        mBuffer = new float[inNumSamplesToRender];
        
        //increment in samples
        float increment = inFreq * mTableLength / mSampleRate;
        
        
        for(int i = 0; i < inNumSamplesToRender; i++){
            
            //increment the readIdx by floating point samples
            mReadIdx += increment;
            
            //fraction ratio
            float fraction = mReadIdx-floor(mReadIdx);
            
            //wrap around
            while (mReadIdx >= (float)mTableLength){
                mReadIdx -= (float)mTableLength;
            }
            
            int iReadIdx = (int)mReadIdx;
            
            int iReadIdxLast = iReadIdx + 1;
            
            //wrap around for mReadIdx+1
            if (iReadIdxLast >= mTableLength){
                iReadIdxLast -= mTableLength;
            }
            
            
            //linear interpolation
            float interpolated = (1 - fraction) * mTable[iReadIdx] + fraction * mTable[iReadIdxLast];
            
            mBuffer[i] = inAmp * interpolated; //put value into output buffer
            
        }
    }
    
    
    float* getBuffer()
    {
        return mBuffer;
    }
    
private:
    int mSampleRate;
    int mTableLength;
    float* mTable;
    float mReadIdx;
    float* mBuffer;
};
#endif /* Lfo_h */
