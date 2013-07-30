/*
* The UrbanEye PND solution is a collection of packages based on native C++ classes
* that implement the fundamental algorithms & operations required to satisfy one kind
* of mobile or portable devices with competitive qualities being a leading one.
*
* Copyright (C) 2008 Xiujie Sheng
*
* This library isn't a free software, so you cann't take the sourcecode without author's permit.
* Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
* if you illegally got it. 
*
* NOTE: 
* AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
* LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
*
* For more information, contact:
*
* China University of Geoseciences(Wuhan)
* Graduate School
*
* Xiujie Sheng
* smartpoint@sohu.com
*/
#ifndef _UEBASE_SIMPLELRU_H
#define _UEBASE_SIMPLELRU_H

// Note: template class no need below macroes

// Refer STL container: deque
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Erase compiling warning condition
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// UeBase
namespace UeBase
{
  /**
  * \brief �����е����ݵ�Ԫ�Ķ��� 
  */
  template<typename T>
  struct CacheUnit
  {
    /// Merged by gate id and parcel id
    int m_id;  
    /// Basic cache unit
    T *m_unit;   

    //
    // Useful default copy, assignment function implementation
    //
    /**
    * \brief ��ʼ��
    */
    CacheUnit() : m_id(-1), m_unit(0)
    {
    }

    /**
    * \brief �������캯��
    */
    CacheUnit(const CacheUnit& other)
    {
      m_id = other.m_id;
      m_unit = other.m_unit;
    }

    /**
    * \brief ��ֵ������
    */
    const CacheUnit & operator = (const CacheUnit &other)
    {
      if(this == &other)
      {
        return *this;
      }

      m_id = other.m_id;
      m_unit = other.m_unit;

      return *this;
    }
  };

  /**
  * \brief һ���򵥵�LRU�������
  * TODO:Even if it share one general memory cache strategy here, but there still exist one fatal problem:
  * when insering a new memort chache unit and it need to delete the last one memory chache unit, how about if
  * the last one is still being used? One clumsy way is to enlarge the cache size and another root way is to use
  * smart pointer which indicates whether it is also being used.
  */
  template<typename T>
  class CSimpleLru
  {
    /// Cache container
    typedef std::deque< CacheUnit<T> > SimpleCache;

  public:
    //
    //
    //
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    CSimpleLru()
    {
      // Default size of cache
      // Note: this number can be decided by the size of one parcel, for example, this software
      // generally is used in the extent of parcels
      m_unitNumber = 25/*50*/;
    }

    /**
    * \brief ��������
    */
    virtual ~CSimpleLru()
    {
      EraseLRU();
    }

  public:
    //
    //
    //
    /**
    * \brief ���û����С
    *
    * \param size ���������ݵ�Ԫ������
    */
    void SetSize(short size);

    /**
    * \brief ��ȡ�����С
    *
    * \param short ���������ݵ�Ԫ������
    **/
    short GetSize();

    /**
    * \brief ��ȡָ�������ݵ�Ԫ
    * 
    * \param order ���ݵ�Ԫ������
    * \return ���ݵ�Ԫ����ָ��
    */
    T *GetUnit(int order);

    /**
    * \brief ��ȡָ�������ݵ�Ԫ
    * 
    * \param firstID ������ݵ�Ԫ��ʶ��firstID
    * \param secondID ������ݵ�Ԫ��ʶ��secondID
    * \return ���ݵ�Ԫ����ָ��
    */
    T *GetUnit(short firstID, long secondID);

    /**
    * \brief ������ݵ�Ԫ
    *
    * \param firstID ������ݵ�ԪΨһ��ʶ��firstID
    * \param secondID ������ݵ�ԪΨһ��ʶ��secondID
    * \param oneUnit ���ݵ�Ԫָ��
    */
    void AddUnit(short firstID, long secondID, T *oneUnit);

    /**
    * \brief ������ݵ�Ԫ
    *
    * \param unitID ���ݵ�ԪΨһ��ʶ
    * \param oneUnit ���ݵ�Ԫָ��
    */
    void AddUnit(int unitID, T *oneUnit);

    /**
    * \brief ɾ����������tailsΪ��ʼ���������ݵ�Ԫ
    *
    * \param tails ɾ������ʼλ��
    */
    void EraseLRU(int tails = 0);

    /**
    * \brief ɾ��ָ��firstID���������ݵ�Ԫ
    *
    * \param firstID ���ݵ�Ԫ��firstID
    */
    void EraseLRU(short firstID);

    /**
    * \brief ɾ��ָ��firstID��secondID�����ݵ�Ԫ
    *
    * \param firstID ������ݵ�ԪΨһ��ʶ��firstID
    * \param secondID ������ݵ�ԪΨһ��ʶ��secondID
    */
    void EraseLRU(short firstID, long secondID);

    /**
    * \brief ɾ�����б�ʶ������ids�е����ݵ�Ԫ
    *
    * \param ids ���ݵ�Ԫ��ʶ������
    */
    void MakeXOR(std::vector<int> &ids);

  protected:
    /**
    *
    */
    T *MoveFirst(int order);

  public:
    /// The continer of cache
    SimpleCache m_cache;
    /// Maximum number of cache unit and this cache mechansim need the minmum number
    short m_unitNumber;    // The number can be evaluated by how much those parcels take on earth main memory
  };

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::SetSize(short size)
  {
    // Free unneccessary memory
    int count = static_cast<int>(m_cache.size());
    if(count > size)
    {
      int tails = count - size;
      EraseLRU(tails);
    }

    //
    m_unitNumber = size;
  }

  /**
  *
  */
  template<typename T>
  inline short CSimpleLru<T>::GetSize()
  {
    int size = static_cast<int>(m_cache.size());
    return (size < m_unitNumber) ? size : m_unitNumber;
  }

  /**
  *
  */
  template<typename T>
  inline T *CSimpleLru<T>::GetUnit(int order)
  {
    assert(order >= 0 && order < GetSize());
    return m_cache[order].m_unit;
  }

  /**
  *
  */
  template<typename T>
  inline T *CSimpleLru<T>::GetUnit(short firstID, long secondID)
  {
    int unitID = secondID << 9 | firstID;

    // Note: the performance of finding one cache unit is limited to the number of cache
    int  i = 0;
    int count = static_cast<int>(m_cache.size());
    for(; i < count; i++)
    {
      if(unitID == m_cache[i].m_id)
      {
        return MoveFirst(i);
      }
    }

    return 0;
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::AddUnit(int unitID, T *oneUnit)
  {
    assert(oneUnit);
    if(m_unitNumber == 0)
    {
      return;
    }

    // Firstly check whether already exist then move it
    // TODO: Get another quick way to find one element
    CacheUnit<T> oneCache;
    oneCache.m_id = unitID;
    oneCache.m_unit = oneUnit;

    //
    int i = 0;
    int count = static_cast<int>(m_cache.size());
    for(; i < count; i++)
    {
      if(oneCache.m_id == m_cache[i].m_id)
      {
        MoveFirst(i);
        return;
      }
    }

    // Secondly check whether it is already full
    if(count == m_unitNumber)
    {
      m_cache[m_unitNumber-1].m_unit->Delete();
      m_cache.erase(m_cache.begin() + m_unitNumber - 1);
    }

    // Lastly
    m_cache.push_front(oneCache);
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::AddUnit(short firstID, long secondID, T *oneUnit)
  {
    AddUnit(secondID << 9 | firstID, oneUnit);
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::EraseLRU(int tails)
  {
    int count = static_cast<int>(m_cache.size());
    assert(count >= tails);

    if(tails > 0)
    {
      int i = tails;
      for(; i > 0; i--)
      {
        m_cache[count - i].m_unit->Delete();
      }
      m_cache.erase(m_cache.end() - tails, m_cache.end());
    }
    else
    {
      int i = 0;
      for(; i < count; i++)
      {
        m_cache[i].m_unit->Delete();
      }
      m_cache.erase(m_cache.begin(), m_cache.end());
    }
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::EraseLRU(short firstID)
  {
    SimpleCache::iterator itrCacheUnit = m_cache.begin();
    while(itrCacheUnit != m_cache.end())
    {
      if((((*itrCacheUnit).m_id & 0xFF000000) >> 8) == firstID)
      {
        (*itrCacheUnit).m_unit->Delete();
        itrCacheUnit = m_cache.erase(itrCacheUnit);

        continue;
      }

      itrCacheUnit++;
    }
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::EraseLRU(short firstID, long secondID)
  {
    int id = secondID << 9 | firstID;

    int count = static_cast<int>(m_cache.size());
    int i = 0;
    for(; i < count; i++)
    {
      if(m_cache[i].m_id == id)
      {
        m_cache[i].m_unit->Delete();
        m_cache.erase(m_cache.begin() + i);

        return;
      }
    }
  }

  /**
  *
  */
  inline static bool BinaryFunc(const int &first, const int &second)
  {
    return first < second;
  }

  /**
  *
  */
  template<typename T>
  inline void CSimpleLru<T>::MakeXOR(std::vector<int> &ids)
  {
    //
    int i = 0;
    int size = static_cast<int>(m_cache.size());

    //
    SimpleCache::iterator first = m_cache.begin();
    SimpleCache::iterator end = m_cache.end();
    for(; first != end; first++)
    {
      //
      if(!std::binary_search(ids.begin(), ids.end(), m_cache[i].m_id, BinaryFunc))
      {
        (*first).m_unit->Delete();
        m_cache.erase(first);
      }
    }
  }

  /**
  *
  */
  template<typename T>
  inline T *CSimpleLru<T>::MoveFirst(int order)
  {
    assert(order < m_unitNumber);
    if(order)
    {
      CacheUnit<T> tmp = m_cache[order];

      int i = order;
      for(; i > 0; i--)
      {
        m_cache[i] = m_cache[i-1];
      }

      m_cache[0] = tmp;

      // Below code exist one fatal bug: if find order = m_unitNumber is suddenly to be moved to the first one
      // but the first one is being used, OOPS!
      // 
      //CacheUnit<T> tmp = m_cache[order];
      //m_cache[order] = m_cache[0];
      //m_cache[0] = tmp;
    }

    return m_cache[0].m_unit;
  }
}

#endif
