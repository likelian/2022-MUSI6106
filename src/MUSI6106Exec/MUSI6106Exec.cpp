
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"
#include "CombFilterIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string sInputFilePath,                 //!< file paths
                sOutputFilePath,
                audioOuputFilePath;

    static const int kBlockSize = 1024;

    clock_t time = 0;

    float **ppfAudioData = 0;
    float **ppfOutputBuffer = 0;

    CAudioFileIf *phAudioFile = 0;
    CAudioFileIf *phAudioWriteFile = 0;
    std::fstream hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;

    showClInfo();
    

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    if (argc < 2)
    {
        cout << "Missing audio input path!";
        return -1;
    }
    else
    {
        sInputFilePath = argv[1];
        sOutputFilePath = sInputFilePath + ".txt";
        audioOuputFilePath = argv[2];
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
    

    CAudioFileIf::create(phAudioWriteFile);
    phAudioWriteFile->openFile(audioOuputFilePath, CAudioFileIf::kFileWrite, &stFileSpec);
    if (!phAudioWriteFile->isOpen())
    {
        cout << "Wave file open error!";
        CAudioFileIf::destroy(phAudioWriteFile);
        return -1;
    }

    
    
    ///////////////////Comb
    
    CCombFilterIf *pCCombFilter = 0;
    CCombFilterIf::create(pCCombFilter);
    
    
    pCCombFilter->init(CCombFilterIf::kCombFIR, 0.1, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
    
    pCCombFilter->setParam(CCombFilterIf::FilterParam_t::kParamGain, std::atof(argv[4]));
    pCCombFilter->setParam(CCombFilterIf::FilterParam_t::kParamDelay, std::atof(argv[6]));
    
    
    float gain = pCCombFilter->getParam(CCombFilterIf::FilterParam_t::kParamGain);
    float delay = pCCombFilter->getParam(CCombFilterIf::FilterParam_t::kParamDelay);
    
    cout << "gain: " << gain << endl;
    cout << "delay: " << delay << endl;
    
    
    
    pCCombFilter->reset();
    
    pCCombFilter->init(CCombFilterIf::kCombIIR, 0.2, stFileSpec.fSampleRateInHz, stFileSpec.iNumChannels);
    
    pCCombFilter->setParam(CCombFilterIf::FilterParam_t::kParamGain, 0.9);
    pCCombFilter->setParam(CCombFilterIf::FilterParam_t::kParamDelay, 2.);
    
    
    float gain_two = pCCombFilter->getParam(CCombFilterIf::FilterParam_t::kParamGain);
    float delay_two = pCCombFilter->getParam(CCombFilterIf::FilterParam_t::kParamDelay);
    
    cout << "gain_two: " << gain << endl;
    cout << "delay_two: " << delay << endl;
    
    
    ///////////////////Comb
    

    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    hOutputFile.open(sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        CAudioFileIf::destroy(phAudioFile);
        return -1;
    }

    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    ppfOutputBuffer = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++){
        ppfAudioData[i] = new float[kBlockSize];
        ppfOutputBuffer[i] = new float[kBlockSize];
    }
    

    if (ppfAudioData == 0)
    {
        CAudioFileIf::destroy(phAudioFile);
        hOutputFile.close();
        return -1;
    }
    if (ppfAudioData[0] == 0)
    {
        CAudioFileIf::destroy(phAudioFile);
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
        
        
        pCCombFilter->process(ppfAudioData, ppfOutputBuffer, iNumFrames);
        

        cout << "\r" << "reading and writing";
        
        phAudioWriteFile->writeData(ppfOutputBuffer, iNumFrames);

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
    CCombFilterIf::destroy(pCCombFilter);
    CAudioFileIf::destroy(phAudioFile);
    CAudioFileIf::destroy(phAudioWriteFile);
    
    hOutputFile.close();

    for (int i = 0; i < stFileSpec.iNumChannels; i++){
        delete[] ppfAudioData[i];
        delete[] ppfOutputBuffer[i];
    }
    delete[] ppfAudioData;
    delete[] ppfOutputBuffer;
    
    ppfAudioData = 0;
    ppfOutputBuffer = 0;

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

