
#include <iostream>
#include <ctime>
#include <fstream>

#include "MUSI6106Config.h"

#include "AudioFileIf.h"

/* code revised based on https://github.com/alexanderlerch/2022-MUSI6106/blob/exercise_fileread/src/MUSI6106Exec/MUSI6106Exec.cpp
*/

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

    CAudioFileIf            *phAudioFile = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;
    

    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    //Need to change
    sOutputFilePath = "/Users/likelian/Desktop/Audio_software/Output/output.txt";
    //Need to change
    sInputFilePath = "/Users/likelian/Desktop/Audio_software/Input/sweep.wav";
 
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf * pCInstance;
    phAudioFile->create(pCInstance); //only return error
    pCInstance->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    
    if (!pCInstance->isOpen())
    {
        cout << "Wave file open error!";
        phAudioFile->destroy(pCInstance);
        return -1;
    }
    
    pCInstance->getFileSpec(stFileSpec);
 
    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    std::ofstream textFile;
    textFile.open(sOutputFilePath, std::ofstream::out | std::ofstream::app);
    
    if (!textFile.is_open())
    {
        cout << "Text file open error!";
        phAudioFile->destroy(pCInstance);
        return -1;
    }

    
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    
    ppfAudioData = new float*[stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++){
        ppfAudioData[i] = new float[kBlockSize];
    }
    

    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output text file (one column per channel)
    
    while (!pCInstance->isEof())
    {
        // set block length variable
        long long iNumFrames = kBlockSize;

        // read data (iNumOfFrames might be updated!)
        pCInstance->readData(ppfAudioData, iNumFrames);

        cout << "\r" << "reading and writing";

        // write
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                textFile << ppfAudioData[c][i] << "\t";
            }
            textFile << endl;
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    // clean-up (close files and free memory)
    for (int i = 0; i < stFileSpec.iNumChannels; i++){
        delete[] ppfAudioData[i];
    }
    delete[] ppfAudioData;
    
    textFile.close();
    pCInstance->closeFile();
    phAudioFile->destroy(pCInstance);

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

