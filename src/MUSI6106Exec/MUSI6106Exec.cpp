
#include <iostream>
#include <ctime>
#include <fstream>

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

    CAudioFileIf            *phAudioFile = 0;
    std::fstream            hOutputFile;
    CAudioFileIf::FileSpec_t stFileSpec;
    

    showClInfo();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    sOutputFilePath = "/Users/likelian/Desktop/Audio_software/Output/filename.txt";
    sInputFilePath = "/Users/likelian/Desktop/Audio_software/Input/sweep.wav";
 
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    CAudioFileIf * pCInstance;
    phAudioFile->create(pCInstance); //only return error
    pCInstance->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    
 
    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    std::ofstream textFile;
    textFile.open(sOutputFilePath, std::ofstream::out | std::ofstream::app);

    
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    float fBuffer_L[kBlockSize];
    float fBuffer_R[kBlockSize];

    
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output text file (one column per channel)
    
    
    long long iLengthInFrames;
    pCInstance->getLength(iLengthInFrames);
    //long long int iNumFrames = iLengthInFrames;
    
    
    long long iNumFrames = 20;

    // allocate ppfAudioData
    int row = 2,col = iNumFrames;
    ppfAudioData = (float **) malloc(row*sizeof(float *));
    for(int i=0;i<iNumFrames;i++)
        ppfAudioData[i] = (float *) malloc(col*sizeof(int));
    
    
    long long iFrame = 0;
    
    cout << iLengthInFrames;
    
    while(iFrame<iLengthInFrames-iFrame){
        
        cout << iFrame << endl;
        
        pCInstance->setPosition(iFrame);
        
        cout << iFrame << endl;
        
        for (int i=0; i<kBlockSize; i++){
                  pCInstance->readData(ppfAudioData, iNumFrames);
                  fBuffer_L[i] = *ppfAudioData[0];
                  fBuffer_R[i] = *ppfAudioData[1];
                  
              }
              
        for (int i=0; i<kBlockSize; i++){
                  textFile << fBuffer_L[i] << ' ' << fBuffer_R[i] << '\n';
        }
        
        pCInstance->getPosition(iFrame);
        
        cout << iFrame << endl;
        
    }
    
   


    //////////////////////////////////////////////////////////////////////////////
    // clean-up (close files and free memory)
    textFile.close();
    pCInstance->reset();
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

