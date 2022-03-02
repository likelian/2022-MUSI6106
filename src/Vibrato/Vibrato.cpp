
#include "Vibrato.h"

Error_t CVibrato::create(CVibrato *&pcVibrato) {

    pcVibrato = new CVibrato();
}

Error_t CVibrato::destroy(CVibrato *&pcVibrato) {

    pcVibrato->reset ();

    delete pcVibrato;
    pcVibrato = 0;

}

Error_t CVibrato::init(float fWidth, float fDelay, float fSampleRateInHz, int iNumChannels) {

    m_bIsInitialized = 1;
    this->setDelay(fDelay*fSampleRateInHz);
    this->setWidth(fWidth*fSampleRateInHz);
    this->m_iNumChannels = iNumChannels;
    m_DelayLine = new CRingBuffer<float>*[iNumChannels];
    for (int i = 0; i < iNumChannels; i++)
    {
        m_DelayLine[i] = new CRingBuffer<float>(m_Delay + m_Width + 2);

        for (int j = 0; j < m_Delay  + m_Width + 2; j++)
        {
            m_DelayLine[i]->putPostInc(0);
        }
        m_DelayLine[i]->setReadIdx(0);
        m_DelayLine[i]->setWriteIdx(m_Delay);
    }

    lfo->process(16000);
    m_sineBuffer = lfo->getRingBuffer();


}

Error_t CVibrato::reset() {
   if (m_bIsInitialized)
   {
       delete m_DelayLine;
       delete m_sineBuffer;
   }

       this->setDelay(0);
       this->setWidth(0);
    m_DelayLine = 0;
       m_sineBuffer = 0;

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
            m_DelayLine[c][i].putPostInc(ppfInputBuffer[c][i]);
            ppfOutputBuffer[c][i] = ppfInputBuffer[c][i] + m_DelayLine[c]->getPostInc(m_sineBuffer->getPostInc(0));

        }

    }

}

CVibrato::CVibrato() {
    m_fSampleRate = 0;
    m_Delay = 0;
    m_DelayLine = 0;
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


