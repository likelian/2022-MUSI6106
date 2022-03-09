
#include "Vibrato.h"

Error_t CVibrato::create(CVibrato *&pcVibrato) {

    pcVibrato = new CVibrato();
}

Error_t CVibrato::destroy(CVibrato *&pcVibrato) {

    pcVibrato->reset ();

    delete pcVibrato;
    pcVibrato = 0;

}
// TODO: Clean up init()
Error_t CVibrato::init(float fWidth, float fSampleRateInHz, float LFOAmplitude, float LFOFrequency,  int iNumChannels) {


    assert(fWidth > 0);
    assert(fSampleRateInHz > 0);
    assert(LFOAmplitude >= 0);
    assert(LFOFrequency < 0.5*fSampleRateInHz);
    assert(iNumChannels > 0);

    m_bIsInitialized = 1;
    this->setDelay(fWidth*fSampleRateInHz);
    this->setWidth(fWidth*fSampleRateInHz);
    this->m_iNumChannels = iNumChannels;
    m_DelayLine = new CRingBuffer<float>*[iNumChannels];

    for (int i = 0; i < iNumChannels; i++) {
        m_DelayLine[i] = new CRingBuffer<float>(m_Delay + m_Width*2 + 2);
    }


    for (int i = 0; i < m_Delay + m_Width + 2 ; i++) {
            for (int j = 0; j < iNumChannels; j++) {
                m_DelayLine[j]->putPostInc(0);
            }
        }


    for (int i = 0; i < iNumChannels; i++) {
            m_DelayLine[i]->setReadIdx(0);
            m_DelayLine[i]->setWriteIdx(m_Delay);
        }
// Creating LFO for given frequency
    lfo = new Lfo();
    lfo->setSampleRate(fSampleRateInHz);
    lfo->process(fSampleRateInHz,LFOFrequency, LFOAmplitude);

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

            m_DelayLine[c]->putPostInc(ppfInputBuffer[c][i]);
            float offset = 1 + m_Delay + m_Width*m_sineBuffer->getPostInc(0);
            ppfOutputBuffer[c][i] = m_DelayLine[c]->getPostInc(offset);
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


