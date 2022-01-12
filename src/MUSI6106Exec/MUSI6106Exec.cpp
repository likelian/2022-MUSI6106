
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
    //sInputFilePath = "";
 
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file

    //phAudioFile->openFile(sInputFilePath, FileIoType_t);
 
    //////////////////////////////////////////////////////////////////////////////
    // open the output text file
    std::ofstream textFile(sOutputFilePath);

    
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    float* buffer_ptr;
    buffer_ptr = new float[kBlockSize];

    
    //////////////////////////////////////////////////////////////////////////////
    // get audio data and write it to the output text file (one column per channel)
    for (int i=0; i<=kBlockSize; i++){
        buffer_ptr[i] = (float)i;
    }
    
    for (int i=0; i<=kBlockSize; i++){
        textFile << buffer_ptr[i] << '\n';
    }


    //////////////////////////////////////////////////////////////////////////////
    // clean-up (close files and free memory)
    
    //phAudioFile->closeFile();
    delete[] buffer_ptr;
    textFile.close();

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

