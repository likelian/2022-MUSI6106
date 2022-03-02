#include "MUSI6106Config.h"

#ifdef WITH_TESTS
#include "Vector.h"
#include "Vibrato.h"

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


class Test_Vibrato : public testing::Test
{
protected:
    
    Cvibrato* CvibratoTest;
    float* buffer1;
    float* buffer2;
    float fTolerance;
    
    void SetUp() override
    {
        
        CvibratoTest = new Cvibrato();
        fTolerance = 0.001f;
        
    }

    void TearDown() override
    {
        delete CvibratoTest;
    }
};


/*
 Output equals delayed input when modulation amplitude is 0.
 */
TEST_F(Test_Vibrato, checkZeroAmp)
{
    int iLength = 88200;
    buffer1 = new float[iLength];
    buffer2 = new float[iLength];
    
    float fModAmp = 0.f;
    
    /filled buffer1 with some real numbers
    
    /*
    do the vibrato and write into buffer2
    */
    
    
    float modulation = 0.f;
}


/*
 DC input stays DC ouput regardless of parametrization.
 */
TEST_F(Test_Vibrato, checkDC)
{
    int iLength = 88200;
    buffer1 = new float[iLength];
    buffer2 = new float[iLength];
    
    float fDCVal = 0.1f;
    
    for (i=0; i<iLength; i++){
        buffer1[i] = fDCVal;
    }
    
    /*
     do the vibrato and write into buffer2
     */
    
    CHECK_ARRAY_CLOSE(buffer1, buffer2, iLength, fTolerance);
}


/*
 Varying input block size.
 */
TEST_F(Test_Vibrato, checkBlock)
{
    int iLength = 88200;
    buffer1 = new float[iLength];
    buffer2 = new float[iLength];
    
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
    
    CHECK_ARRAY_CLOSE(buffer1, buffer2, iLength, fTolerance);
    
}



/*
Zero input signal.
 */
TEST_F(Test_Vibrato, checkZeroInput)
{
    int iLength = 88200;
    buffer1 = new float[iLength];
    buffer2 = new float[iLength];
    
    float fDCVal = 0.f;
    
    for (i=0; i<iLength; i++){
        buffer1[i] = fDCVal;
    }
    
    /*
     do the vibrato and write into buffer2
     */
    
    CHECK_ARRAY_CLOSE(buffer1, buffer2, iLength, fTolerance);
    
}


/*
 One or more additional test(s) to verify other expected behaviors.
 */
TEST_F(Test_Vibrato, OneMoreTest)
{
    
}


#endif //WITH_TESTS
