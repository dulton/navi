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
#ifndef _UEBASE_MEMVECTOR_H
#define _UEBASE_MEMVECTOR_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Declare UeBase namespace
namespace UeBase
{

  /**
  * \brief Self-defined implemenation of one arrary which is based on one continuous memory block.
  */
  class UEBASE_CLASS CMemVector
  {
  public:
    //
    // Default constructor and deconstructor
    // 
    /**
    * \brief ���캯��
    * Note: here smart pointer maybe reasonable when need to decide when to release memory
    *
    * \param blockSize ���ݿ��С
    * \param increment ��������ʱ��ÿ�ζ�̬����������Ԫ������
    * \param isReleased �Ƿ��Զ����ٷ�����ڴ�
    */
    CMemVector(int blockSize, int increment = 100, bool isReleased = true);

    /**
    * \brief �������캯��
    *
    * \param other ���е�ĳ��CMemVectorʵ��
    * \param isRelease �Ƿ��Զ����ٷ�����ڴ�
    */
    CMemVector(const CMemVector &other, bool isRelease = true);

    /**
    * \brief ��������
    */
    virtual ~CMemVector();

  public:
    //
    // Methods about vector generation
    //
    /**
    * \brief Not only does it can initialize relative variables when firstly used, but also it clean the 
    * the old memory up for the following usage.
    *
    * \param blockSize the size of one block in continuous memory
    * \param increment the incremented size when reallocating this continuous memory
    */
    void Init(int blockSize, int increment = 100);

    /**
    * \brief ������β����������Ԫ��
    *
    * \param oneBlock Ҫ���������Ԫ��ָ��
    * \return ���ز��������Ԫ�ص�ַ
    */
    void *Add(void *oneBlock);

    /**
    * \brief ��ָ��λ�ò�������Ԫ��
    *
    * \param oneBlock Ҫ���������Ԫ�ص�ָ��
    * \param pos ����λ��
    * \return ����������Ԫ�ص�ָ��
    */
    void *Add(const void *oneBlock, long pos);

    /**
    * \brief ɾ��ָ��λ�õ�����Ԫ��
    *
    * \param pos Ҫɾ��������Ԫ�ص�λ��
    * \return ɾ���ɹ�����1�����򷵻�0.
    */
    short Remove(long pos);

    /**
    * \brief ɾ��һ�������ڵ�����Ԫ��
    *
    * \param ɾ���������ʼλ��
    * \param ɾ���������ֹλ��
    * \return ɾ���ɹ�����1�����򷵻�0.
    */
    short Remove(long startPos, long endPos);

    /**
    * \brief ɾ����������Ԫ��
    * 
    * \param isRelease �Ƿ��Զ����ٷ�����ڴ�
    */
    void RemoveAll(bool isReleae = true);

    /**
    *
    */

    //
    // Access or senior visiting interfaces
    //
    /**
    * \brief ��ȡ����Ԫ������
    * 
    * \return Ԫ�ظ���
    */
    long GetCount() const;

    /**
    * \brief ��ȡָ��������Ԫ��
    *
    * \param curBlock ����Ԫ������
    * \return ָ��λ�õ�����Ԫ��
    */
    void *GetData(long curBlock) const;

    /**
    * \brief ��ȡͷ��������Ԫ��
    * \return ָ������ͷ����ָ��
    */
    void *GetHead() const;

    /**
    * \brief ��ȡ����Ԫ�ش�С
    *
    * \return ����Ԫ�صĴ�С
    */
    int GetBlockSize() const;

    /**
    * \brief ��������
    *
    * \param SortFunc �������ĺ���ָ��
    */
    void QuickSort(int (* SortFunc)(const void *firstBlock, const void *secondBlock)); 

    /**
    * \brief ���ֲ���
    * 
    * \param key ��ֵ
    * \param CompareFunc �ȽϺ����ĺ���ָ��
    * \return ���ҽ��
    */
    void *BinaryFind(const void *key, int (__cdecl *CompareFunc)(const void *firstBlock, const void *secondBlock));

    //
    // Overloading operators
    //
    /**
    * \brief Deprecated function
    */
    const CMemVector& operator = (const CMemVector &other);

    /**
    * \brief Deprecated function since we directly use suffix to position one element after getting one 
    * continuous memory
    *
    * \param pos ����Ԫ�ص�����
    */
    void *operator[](long pos) const;

    //
    //
    //
    /**
    * \brief �������߻�����
    *
    * \param bufferWidth ���������
    * \param leftRight the side in inner or outside: 1 means outside, -1 means inner side
    * \param lineCoords ������״�����꼯��
    * \param bufCoords ��������״�����꼯��
    * \return �ɹ�����true�����򷵻�false
    */
    static bool MakeBufferLine(double bufferWidth, short leftRight, const CMemVector &lineCoords, CMemVector &bufCoords);

  private:
    /**
    *
    */
    void *Alloc();

  private:
    /// Whether automatically to release memory
    bool m_isRelease;
    /// The size of one continuous memory unit
    int m_blockSize;
    /// The number of units in continuous way
    long m_blocks;
    /// The position indicating which unit
    long m_lastBlock;
    /// The size of units needed to be allocated
    int m_increment;
    /// The heading address
    void *m_head;

  };
}

#endif