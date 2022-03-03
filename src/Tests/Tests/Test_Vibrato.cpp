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

TEST_F(Vibrato, sanityCheck)
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







//namespace vibrato_test {
//    void CHECK_ARRAY_CLOSE(float* buffer1, float* buffer2, int iLength, float fTolerance)
//    {
//        for (int i = 0; i < iLength; i++)
//        {
//            EXPECT_NEAR(buffer1[i], buffer2[i], fTolerance);
//        }
//    }
//
//}

#endif //WITH_TESTS
