#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstring>

/*! \brief implement a circular buffer of type T
*/
template <class T>

class CRingBuffer
{
public:
    explicit CRingBuffer(int iBufferLengthInSamples) :
        m_iBuffLength(iBufferLengthInSamples),
        m_iReadPtr(0),
        m_iWritePtr(0),
        m_PtRingBuff(0)
        
    {
        assert(iBufferLengthInSamples > 0);

        m_PtRingBuff = new T[m_iBuffLength];

        // allocate and init
    }

    virtual ~CRingBuffer()
    {
        // free memory
        delete [] m_PtRingBuff;
    }

    /*! add a new value of type T to write index and increment write index
    \param tNewValue the new value
    \return void
    */
    void putPostInc (T tNewValue)
    {
        put(tNewValue);
        if (++m_iWritePtr >= m_iBuffLength){
            m_iWritePtr = 0;
        }
    }

    /*! add a new value of type T to write index
    \param tNewValue the new value
    \return void
    */
    void put(T tNewValue)
    {
        m_PtRingBuff[m_iWritePtr] = tNewValue;
    }
    
    /*! return the value at the current read index and increment the read pointer
    \return float the value from the read index
    */
    T getPostInc()
    {
        T output = get();
        
        if (++m_iReadPtr >= m_iBuffLength){
            m_iReadPtr = 0;
        }
        
        return output;
    }

    /*! return the value at the current read index
    \return float the value from the read index
    */
    T get() const
    {
        return m_PtRingBuff[m_iReadPtr];
    }
    
    /*! set buffer content and indices to 0
    \return void
    */
    void reset()
    {
        m_iReadPtr = 0;
        m_iWritePtr = 0;
        m_PtRingBuff = new T[m_iBuffLength];
    }

    /*! return the current index for writing/put
    \return int
    */
    int getWriteIdx() const
    {
        return m_iWritePtr;
    }

    /*! move the write index to a new position
    \param iNewWriteIdx: new position
    \return void
    */
    void setWriteIdx(int iNewWriteIdx)
    {
        m_iWritePtr = iNewWriteIdx;
    }

    /*! return the current index for reading/get
    \return int
    */
    int getReadIdx() const
    {
        return m_iReadPtr;
    }

    /*! move the read index to a new position
    \param iNewReadIdx: new position
    \return void
    */
    void setReadIdx(int iNewReadIdx)
    {
        m_iReadPtr = iNewReadIdx;
    }

    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer() const
    {
        return -1;
    }

    /*! returns the length of the internal buffer
    \return int
    */
    int getLength() const
    {
        return -1;
    }
private:
    CRingBuffer();
    CRingBuffer(const CRingBuffer& that);

    int m_iBuffLength;              //!< length of the internal buffer
    int m_iReadPtr;
    int m_iWritePtr;
    T* m_PtRingBuff;
};
#endif // __RingBuffer_hdr__