
#include <iostream>
#include <ctime>
#include "Vibrato.h"

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    static const int        kBlockSize = 1024;

    clock_t                 time = 0;

    float                   **ppfAudioData = 0;
    float                   **ppfOutputData = 0;

    float                   delay = 0;
    float                   width = 0;

    CAudioFileIf            *phAudioFile = 0;
    CAudioFileIf            *phOutputFile = 0;

    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    CVibrato                *vibrato;

    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    if (argc < 4)
    {
        cout << "Missing audio input path!";
        return -1;
    }
    else
    {
        sInputFilePath = argv[1];
        sOutputFilePath = argv[2];

        delay = atof(argv[3]);
        width = atof(argv[4]);

    }

    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        CAudioFileIf::destroy(phAudioFile);
        return -1;
    }
    phAudioFile->getFileSpec(stFileSpec);
    
    
    //////////////////////////////////////////////////////////////////////////////
    // vibrato initualization
    float fAmp = 1.;
    float fLFOFrequency = 10.;
    
    CVibrato::create(vibrato);
    vibrato->reset();
    vibrato->init(width, stFileSpec.fSampleRateInHz, fAmp, fLFOFrequency, stFileSpec.iNumChannels);
    vibrato->setDelay(width);
    

    //////////////////////////////////////////////////////////////////////////////


    CAudioFileIf::create(phOutputFile);
    phOutputFile->openFile(sOutputFilePath, CAudioFileIf::kFileWrite, &stFileSpec);
    if (!phOutputFile->isOpen())
    {
        cout << "Wave file open error!";
        CAudioFileIf::destroy(phOutputFile);
        return -1;
    }


    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    ppfOutputData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++) {
        ppfAudioData[i] = new float[kBlockSize];
        ppfOutputData[i] = new float[kBlockSize];
    }

    if (ppfAudioData == 0)
    {
        CAudioFileIf::destroy(phAudioFile);
        CVibrato::destroy(vibrato);
        hOutputFile.close();
        return -1;
    }
    if (ppfAudioData[0] == 0)
    {
        CAudioFileIf::destroy(phAudioFile);
        CVibrato::destroy(vibrato);
        hOutputFile.close();
        return -1;
    }

    time = clock();

    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output text file (one column per channel)
    while (!phAudioFile->isEof())
    {
        // set block length variable
        long long iNumFrames = kBlockSize;

        // read data (iNumOfFrames might be updated!)
        phAudioFile->readData(ppfAudioData, iNumFrames);
        vibrato->process(ppfAudioData, ppfOutputData, iNumFrames);
        phOutputFile->writeData(ppfOutputData, iNumFrames);

        cout << "\r" << "reading and writing";

        // write
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }
    }

    cout << "\nreading/writing done in: \t" << (clock() - time) * 1.F / CLOCKS_PER_SEC << " seconds." << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up (close files and free memory)
    CAudioFileIf::destroy(phAudioFile);
    CAudioFileIf::destroy(phOutputFile);
    CVibrato::destroy(vibrato);
    hOutputFile.close();

    for (int i = 0; i < stFileSpec.iNumChannels; i++) {
        delete[] ppfAudioData[i];
        delete[] ppfOutputData[i];
    }
    delete[] ppfAudioData;
    delete[] ppfOutputData;
    ppfAudioData = 0;
    ppfOutputData = 0;

    // all done
    return 0;

}


void     showClInfo()
{
    cout << "MUSI6106 Assignment Executable" << endl;
    cout << "(c) 2014-2022 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}
