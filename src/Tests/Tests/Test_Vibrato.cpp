#include "MUSI6106Config.h"
#ifdef WITH_TESTS
#include "Vector.h"
#include "Vibrato.h"
#include <fstream>
#include "gtest/gtest.h"


namespace vibrato_test {
    void CHECK_ARRAY_CLOSE(float* buffer1, float* buffer2, int iLength, float fTolerance)
    {
        for (int i = 0; i < iLength; i++)
        {
            EXPECT_NEAR(buffer1[i], buffer2[i], fTolerance);
        }
    }
}


class Vibrato : public testing::Test
{

protected:
    void SetUp() override
    {
        CVibrato::create(vibrato);


            inputBuffer = new float* [numChannels];
            outputBuffer = new float* [numChannels];

        for (int i = 0; i < numChannels; i++) {
            inputBuffer[i] = new float[numSamples];
            outputBuffer[i] = new float[numSamples];
        }

        for (int i = 0; i < numChannels; i++)
        {
            for (int j = 0; j < numSamples; j++)
            {
                inputBuffer[i][j] = 1;
            }
        }


    }

    void TearDown() override
    {
        for (int c = 0; c < numChannels; c++)
        {
            delete [] inputBuffer[c];
            delete [] outputBuffer[c];
        }

        delete [] inputBuffer;
        delete [] outputBuffer;

        CVibrato::destroy(vibrato);
    }



    float** inputBuffer = 0;
    float** outputBuffer = 0;
    int numChannels = 2;
    int numSamples = 48000;
    CVibrato* vibrato;


};

TEST_F(Vibrato, DCCheck)
{
    std::ofstream fOutput("CheckSineBuffer.txt");

    vibrato->init(0.01, 16000, 1,10, 2);
    vibrato->process(inputBuffer,outputBuffer,numSamples);

    for (int c = 0; c < numChannels; c++) {
        for (int i = 0; i < numSamples; i++) {
            fOutput << inputBuffer[c][i] << "\t" << outputBuffer[c][i] << "\n";
        }
    }

    fOutput.close();

}


/*
 Output equals delayed input when modulation amplitude is 0.
 */
TEST_F(Vibrato, checkZeroAmp)
{
    
    //put 0. into inputBuffer
    for (int c = 0; c < numChannels; c++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            inputBuffer[c][i] = 0.;
        }
        
        //put 1. in the first sample
        inputBuffer[c][0] = 1.;
    }
    
    
    /*
    init(float fWidth, float fSampleRateInHz, float LFOAmplitude, float LFOFrequency,  int iNumChannels)
     */
    float fSampleRateInHz = 16000.;
    float fAmp = 0.;
    float fDelayTime = 0.1;
    float fWidth = 0.;
    vibrato->init(fWidth, fSampleRateInHz, fAmp, 1., 2);
    
    
    //set delay to 0.1s
    vibrato->setDelay(fDelayTime);
    vibrato->process(inputBuffer, outputBuffer, numSamples);

    int iDelayInSamples = (int)(fDelayTime * fSampleRateInHz);
    
    for (int c = 0; c < numChannels; c++) {
        for (int i = 0; i < numSamples; i++){
            if (outputBuffer[c][i] == 1.){
                std::cout << i << std::endl;
                std::cout << iDelayInSamples << std::endl;
            }
        }
        
    }

}


/*
 DC input stays DC ouput regardless of parametrization.
 */
TEST_F(Vibrato, checkDC)
{
    
    //CHECK_ARRAY_CLOSE(buffer1, buffer2, iLength, fTolerance);
}


/*
 Varying input block size.
 */
TEST_F(Vibrato, checkBlock)
{
    int iBlockLength_1 = 1024;
    int iBlockLength_2 = 1025;
    int iBlockLength_3 = 3;
    int iBlockLength_4 = 7;
    int iBlockLength_5 = 22223;
    int iBlockLength_6 = 511;
    
    //filled buffer1 with some real numbers
    
    /*
     do the vibrato and write into buffer2
     */
    
}



/*
Zero input signal.
 */
TEST_F(Vibrato, checkZeroInput)
{

    
    float fDCVal = 0.f;
    
//    for (i=0; i<iLength; i++){
//        buffer1[i] = fDCVal;
//    }
    
}


/*
 One or more additional test(s) to verify other expected behaviors.
 */
TEST_F(Vibrato, OneMoreTest)
{
    
}





#endif //WITH_TESTS
