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
        
        reset();

        // allocate and init
    }
    

    virtual ~CRingBuffer()
    {
        // free memory
        delete [] m_PtRingBuff;
        m_PtRingBuff = 0;
    }
    
    void setReadPtr(int iDelayInSamples){
        m_iReadPtr = m_iBuffLength - iDelayInSamples;
    }

    /*! add a new value of type T to write index and increment write index
    \param tNewValue the new value
    \return void
    */
    void putPostInc (T tNewValue)
    {
        put(tNewValue);
        incIdx(m_iWritePtr);
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
        
        incIdx(m_iReadPtr);
        
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
        //  std::memset reset an array
        std::memset (m_PtRingBuff, 0, sizeof(T)*m_iBuffLength);
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
        incIdx(m_iWritePtr, iNewWriteIdx - m_iWritePtr);
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
        incIdx(m_iReadPtr, iNewReadIdx - m_iReadPtr);
    }

    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer() const
    {
        return  (m_iWritePtr - m_iReadPtr + m_iBuffLength) % m_iBuffLength;
    }

    /*! returns the length of the internal buffer
    \return int
    */
    int getLength() const
    {
        return m_iBuffLength;
    }
private:
    CRingBuffer();
    CRingBuffer(const CRingBuffer& that);
    
    
    void incIdx(int& iIdx, int iOffset = 1)
       {
           while ((iIdx + iOffset) < 0)
           {
               // avoid negative buffer indices
               iOffset += m_iBuffLength;
           }
           iIdx = (iIdx + iOffset) % m_iBuffLength;
       };
    

    int m_iBuffLength;              //!< length of the internal buffer
    int m_iReadPtr;
    int m_iWritePtr;
    T* m_PtRingBuff;
};



#endif // __RingBuffer_hdr__
