#include "MUSI6106Config.h"
#ifdef WITH_TESTS
#include "Vector.h"
#include "Vibrato.h"
#include <fstream>
#include "gtest/gtest.h"


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
    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < numSamples; j++)
        {
            inputBuffer[i][j] = 1;
        }
    }
    vibrato->init(0.01, 16000, 1,10, 2);
    vibrato->process(inputBuffer,outputBuffer,numSamples);
    float edges = outputBuffer[0][0] - outputBuffer[0][numSamples-1];
    for (int c = 0; c < numChannels; c++) {
        outputBuffer[c][0] = edges;
        outputBuffer[c][numSamples - 1] = edges;
    }
    for (int c = 0; c < numChannels; c++) {
        for (int i = 1; i < numSamples-1; i++) {
            EXPECT_TRUE(outputBuffer[c][i] - outputBuffer[c][i-1] == 0);
        }
    }
}


/*
 Output equals delayed input when modulation amplitude is 0.
 */
TEST_F(Vibrato, checkZeroAmp)
{
    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < numSamples; j++)
        {
            inputBuffer[i][j] = 0;
        }
        inputBuffer[i][0] = 1;
    }



    float fSampleRateInHz = 16000.;
    float fAmp = 0.;
    float fWidth = 0.1;
    vibrato->init(fWidth, fSampleRateInHz, fAmp, 1., 2);


    //set delay to 0.1s
    vibrato->process(inputBuffer, outputBuffer, numSamples);

    int iDelayInSamples = (int)(fWidth * fSampleRateInHz);

    EXPECT_TRUE(inputBuffer[0][0] == outputBuffer[0][iDelayInSamples]);
    }

/*
 Varying input block size.
 */
TEST_F(Vibrato, checkBlock)
{
    float fSampleRateInHz = 16000.;
    float fAmp = 0.;
    float fWidth = 0.1;
    vibrato->init(fWidth, fSampleRateInHz, fAmp, 1., 2);

    int blockSizes [] = {1024, 1025, 3, -1, 2222};
    for (int i = 0; i < sizeof(blockSizes)/sizeof(blockSizes[0]); i++)
    {
        //set delay to 0.1s
        vibrato->process(inputBuffer, outputBuffer, numSamples);


    }

    

    

    
}



/*
Zero input signal.
 */
TEST_F(Vibrato, checkZeroInput) {



    //put 0. into inputBuffer
    for (int c = 0; c < numChannels; c++) {
        for (int i = 0; i < numSamples; i++) {
            inputBuffer[c][i] = 0.;
        }

        vibrato->init(0.01, 16000, 1, 10, 2);
        vibrato->process(inputBuffer, outputBuffer, numSamples);

        for (int c = 0; c < numChannels; c++) {
            for (int i = 0; i < numSamples; i++) {
                EXPECT_TRUE(outputBuffer[c][i] == 0);
            }
        }


    }
}

/*
 One or more additional test(s) to verify other expected behaviors.
 */
TEST_F(Vibrato, OneMoreTest)
{


    
}





#endif //WITH_TESTS
