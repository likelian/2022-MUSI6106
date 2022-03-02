#if !defined(__CombFilterIf_hdr__)
#define __CombFilterIf_hdr__

#include "ErrorDef.h"
#include "RingBuffer.h"

//class CCombFilterBase; // in case you intend to add an internal base class that the user doesn't see (not required)

/*! \brief interface class for the comb filter (FIR & IIR)
*/
class CVibrato
{
public:
    /*! version number */
    enum Version_t
    {
        kMajor,             //!< major version number
        kMinor,             //!< minor version number
        kPatch,             //!< patch version number

        kNumVersionInts
    };

    /*! feedforward or recursive comb filter */
//    enum CombFilterType_t
//    {
//        kCombFIR,           //!< finite impulse response filter
//        kCombIIR,           //!< infinite impulse response filter
//
//        kNumFilterTypes
//    };

//    /*! list of parameters for the comb filters */
//    enum FilterParam_t
//    {
//        width,         //!< gain as factor (usually -1...1)
//        delay,        //!< delay in seconds for specification of comb width
//
//        kNumFilterParams
//    };

    /*! returns the current project version
    \param eVersionIdx specifies what version to return (kMajor, kMinor,...)
    \return const int
    */
    static const int  getVersion (const Version_t eVersionIdx);

    /*! returns the date of the build
    \return const char*
    */
    static const char* getBuildDate ();

    /*! creates a new comb filter instance
    \param pCCombFilterIf pointer to the new class
    \return Error_t
    */
    static Error_t create (CVibrato*& pCCombFilterIf);

    /*! destroys a comb filter instance
    \param pCCombFilterIf pointer to the class to be destroyed
    \return Error_t
    */
    static Error_t destroy (CVibrato*& pCCombFilterIf);

    /*! initializes a comb filter instance
    \param eFilterType FIR or IIR
    \param fMaxDelayLengthInS maximum allowed delay in seconds
    \param fSampleRateInHz sample rate in Hz
    \param iNumChannels number of audio channels
    \return Error_t
    */
    Error_t init ( float fWidth, float fDelay, float fSampleRateInHz, int iNumChannels);

    /*! resets the internal variables (requires new call of init)
    \return Error_t
    */
    Error_t reset ();

    /*! sets a comb filter parameter
    \param eParam what parameter (see ::FilterParam_t)
    \param fParamValue value of the parameter
    \return Error_t
    */
    Error_t setDelay (float fDelay);

    /*! return the value of the specified parameter
    \param eParam
    \return float
    */
    float   setWidth (float fWidth) const;

    /*! processes one block of audio
    \param ppfInputBuffer input buffer [numChannels][iNumberOfFrames]
    \param ppfOutputBuffer output buffer [numChannels][iNumberOfFrames]
    \param iNumberOfFrames buffer length (per channel)
    \return Error_t
    */
    Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames);

protected:
    CVibrato ();
    virtual ~CVibrato();

private:
    bool  m_bIsInitialized;   //!< internal bool to check whether the init function has been called
    float m_Delay;
    float m_Width;
    CRingBuffer<float> *m_RingBuffer;
    float           m_fSampleRate;      //!< audio sample rate in Hz
};

#endif // #if !defined(__CombFilterIf_hdr__)


