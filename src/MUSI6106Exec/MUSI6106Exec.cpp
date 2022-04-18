
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "Vibrato.h"
#include "portaudio.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo();

typedef struct paTestData
{
    CAudioFileIf* phAudioFile = 0;
    CVibrato* pCVibrato = 0;
    float** ppfInputAudio = 0;
    float** ppfOutputAudio = 0;
    long long iNumFrames;
    int iNumChannels;
} paTestData;

// This routine will be called by the PortAudio engine when audio is needed.
static int patestCallback ( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    
    (void) inputBuffer;
    (void) statusFlags;
    (void) timeInfo;

    // processing
    if (!data->phAudioFile->isEof())
    {
        data->phAudioFile->readData(data->ppfInputAudio, data->iNumFrames);
        data->pCVibrato->process(data->ppfInputAudio, data->ppfOutputAudio, data->iNumFrames);

        // fill in PortAudio output with Vibrato output.
        for (int i = 0; i < data->iNumFrames; i++) {
            for (int c = 0; c < data->iNumChannels; c++) {
                *out++ = data->ppfOutputAudio[c][i];
            }
        }

        // fill in remainder of frames for empty audio output.
        for (int i = data->iNumFrames; i < framesPerBuffer; i++) {
            for (int c = 0; c < data->iNumChannels; c++) {
                *out++ = 0.f;
            }
        }
    } else {
        // fill PortAudio output with empty audio output (end of file).
        for (int i = 0; i < framesPerBuffer; i++) {
            for (int c = 0; c < data->iNumChannels; c++) {
                *out++ = 0.f;
            }
        }
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{

    std::string             sInputFilePath,                 //!< file paths
        sOutputFilePath;

    static const int            kBlockSize = 1024;

    float                       fModFrequencyInHz;
    float                       fModWidthInSec;

    clock_t                     time = 0;

    CAudioFileIf::FileSpec_t    stFileSpec;

    showClInfo();
    
    PaStream *stream;
    PaStreamParameters outputParameters;
    PaError err;
    paTestData data;

    // command line args
    if (argc < 5)
    {
        fModWidthInSec = 0.f;
        if (argc < 3) {
            fModFrequencyInHz = 0.f;
        }
        if (argc < 2) {
            sInputFilePath = "input.wav";
        }
    } else {
        sInputFilePath = argv[1];
        fModFrequencyInHz = atof(argv[2]);
        fModWidthInSec = atof(argv[3]);
    }

    ///////////////////////////////////////////////////////////////////////////
    
    CAudioFileIf::create(data.phAudioFile);

    data.phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    data.phAudioFile->getFileSpec(stFileSpec);
    data.iNumChannels = stFileSpec.iNumChannels;
    
    if (!data.phAudioFile->isOpen())
    {
        cout << "Input file open error!";

        CAudioFileIf::destroy(data.phAudioFile);
        return -1;
    }
    
    data.iNumFrames = kBlockSize;
    
    ////////////////////////////////////////////////////////////////////////////
    CVibrato::create(data.pCVibrato);
    data.pCVibrato->init(fModWidthInSec, stFileSpec.fSampleRateInHz, data.iNumChannels);

    // allocate memory
    data.ppfInputAudio = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        data.ppfInputAudio[i] = new float[kBlockSize];

    data.ppfOutputAudio = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        data.ppfOutputAudio[i] = new float[kBlockSize];

    // Set parameters of vibrato
    data.pCVibrato->setParam(CVibrato::kParamModFreqInHz, fModFrequencyInHz);
    data.pCVibrato->setParam(CVibrato::kParamModWidthInS, fModWidthInSec);
    
    ////////////////////////////////////////////////////////////////////////////
    
    // initialize PortAudio
    err = Pa_Initialize();
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    // setup audio output
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    outputParameters.channelCount = stFileSpec.iNumChannels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    
    // setup stream
    err = Pa_OpenStream(&stream, NULL, &outputParameters, stFileSpec.fSampleRateInHz, kBlockSize, paClipOff, patestCallback, &data);

    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    err = Pa_StartStream( stream );
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
    
    /* Sleep for several seconds. */
    Pa_Sleep(5*1000);

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    CAudioFileIf::destroy(data.phAudioFile);
    CVibrato::destroy(data.pCVibrato);

    for (int i = 0; i < stFileSpec.iNumChannels; i++)
    {
        delete[] data.ppfInputAudio[i];
        delete[] data.ppfOutputAudio[i];
    }
    delete[] data.ppfInputAudio;
    delete[] data.ppfOutputAudio;
    data.ppfInputAudio = 0;
    data.ppfOutputAudio = 0;
    
    err = Pa_StopStream( stream );
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
    
    err = Pa_CloseStream( stream );
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }
    
    err = Pa_Terminate();
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    // all done
    return 0;

}


void     showClInfo()
{
    cout << "MUSI6106 Assignment Executable" << endl;
    cout << "(c) 2014-2022 by Alexander Lerch" << endl;
    cout << endl;

    return;
}

