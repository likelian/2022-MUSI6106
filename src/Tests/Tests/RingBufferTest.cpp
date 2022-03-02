//
// Created by Nikhil Ravikrishnan on 2/27/22.
//

//#ifdef WITH_TESTS
#include "gtest/gtest.h"
#include "RingBuffer.h"
//namespace audiofile_test {
//    void CHECK_ARRAY_CLOSE(float* buffer1, float* buffer2, int iLength, float fTolerance)
//    {
//        for (int i = 0; i < iLength; i++)
//        {
//            EXPECT_NEAR(buffer1[i], buffer2[i], fTolerance);
//        }
//    }

class RingBufferTest : public testing::Test
{
protected:
    void SetUp() override
    {
        test = new CRingBuffer<float>(buffLengthSamples);
    }

//    void TearDown() override
//    {
//        delete [] test;
//    }

    int buffLengthSamples = 10;
    float Offset;
    CRingBuffer<float>* test;
};

TEST_F(RingBufferTest, checkPositiveOffset)
{
    buffLengthSamples = 10;
    Offset = 2.75;
    test->reset();

    // Setup ring buffer with values from 1 - 10
    for(int i = 0; i < 10; i++)
    {
        test->putPostInc(i+1);
    }

    EXPECT_TRUE(test->get(Offset) == 3.75);

}


TEST_F(RingBufferTest, checkNegativeOffset)
{
    buffLengthSamples = 10;
    Offset = -2.75;
    test->reset();

    // Setup ring buffer with values from 0 - 9
    for(int i = 0; i < 10; i++)
    {
        test->putPostInc(i+1);
    }

    EXPECT_TRUE(test->get(Offset) == 8.25);

}
//#endif //WITH_TESTS