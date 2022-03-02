
#include "Vibrato.h"

Error_t CVibrato::create(CVibrato *&pcVibrato) {

    pcVibrato = new CVibrato();
}

Error_t CVibrato::destroy(CVibrato *&pCCombFilterIf) {



}

Error_t CVibrato::init(float fWidth, float fDelay, float fSampleRateInHz, int iNumChannels) {

    m_bIsInitialized = 1;
    this->setDelay(fDelay*fSampleRateInHz);
    this->setWidth(fWidth*fSampleRateInHz);

    m_RingBuffer = new CRingBuffer<float>*[iNumChannels];
    for (int i = 0; i < iNumChannels; i++)
    {
        m_RingBuffer[i] = new CRingBuffer<float>(m_Delay  + m_Width + 2);

        for (int j = 0; j < m_Delay  + m_Width + 2; j++)
        {
            m_RingBuffer[i]->putPostInc(0);
        }
        m_RingBuffer[i]->setReadIdx(0);
        m_RingBuffer[i]->setWriteIdx(m_Delay);
    }
    lfo->process(16000);
    this->sineBuffer = lfo->getBuffer();

}

Error_t CVibrato::reset() {
   if (m_bIsInitialized)
   {
       delete m_RingBuffer;
       delete sineBuffer;
   }

       this->setDelay(0);
       this->setWidth(0);
       m_RingBuffer = 0;
       sineBuffer = 0;

       m_bIsInitialized = false;

}

Error_t CVibrato::setDelay(float fDelay) {
    m_Delay = fDelay;
}

float CVibrato::setWidth(float fWidth) {
    m_Width = fWidth;
}

Error_t CVibrato::process(float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames) {

    for (int c = 0; c < m_iNumChannels; c++) {
        for (int i = 0; i < iNumberOfFrames; i++) {
            m_RingBuffer[c][i].putPostInc(ppfInputBuffer[c][i]);


        }

    }

}

CVibrato::CVibrato() {
    m_fSampleRate = 0;
    m_Delay = 0;
    m_RingBuffer = 0;
    m_Width = 0;
}

CVibrato::~CVibrato() {

}

const int CVibrato::getVersion(const CVibrato::Version_t eVersionIdx) {
    return 0;
}

const char *CVibrato::getBuildDate() {
    return NULL;
}


