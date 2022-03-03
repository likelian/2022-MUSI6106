//
//  LfoTest.cpp
//  TestExec
//
//  Created by 李克镰 on 2/27/22.
//

#include <stdio.h>


//#ifdef WITH_TESTS
#include <math.h>
#include <fstream>
#include "gtest/gtest.h"
#include "Lfo.h"



class LfoTest : public testing::Test
{
protected:

    void SetUp() override
    {
        cLfo = new Lfo();
    }

    void TearDown() override
    {
        delete cLfo;
    }
    Lfo* cLfo;
};

TEST_F(LfoTest, checkLfoFreq)
{
    int mSampleRate = 44100;
    cLfo->setSampleRate(mSampleRate);

    int inNumSamplesToRender = 88200;
    float freq = 10;
    float depth = 0.5;
    
    
    /*
     buffer created by wavetable
     */
    cLfo->process(inNumSamplesToRender, freq, depth); //default frequency and amplitude
    CRingBuffer<float>* buffer = cLfo->getRingBuffer();
    
    
    /*
     buffer created by direct sinf computation
     */
    float* sineBuffer = new float[inNumSamplesToRender];
    
    for (int i = 0; i < inNumSamplesToRender; i++){
        
        float mPhase = mPhase + (freq / mSampleRate);
        
        if (mPhase >= 1.0f){
            mPhase = mPhase - 1.0f;
        }

        sineBuffer[i] = sinf(2.f * mPhase * M_PI) * depth;
    }
    
    float fTolerance = 0.01;

    std::ofstream outFile;
    outFile.open("sineOutNikhil.txt");
    
    for (int i = 0; i < inNumSamplesToRender; i++) {

        outFile << buffer->getPostInc(0)<<"\n";
      
//      EXPECT_NEAR(buffer[i], sineBuffer[i], fTolerance) << "Vectors buffer and sineBuffer differ at index " << i;
    }

    
}







//#endif //WITH_TESTS
