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
#ifndef _UEMODEL_NETALLOCATOR_H
#define _UEMODEL_NETALLOCATOR_H

// Refer to EXPORT & IMPORT macro defintions
#ifndef _UEMODEL_BASE_H
#include "uemodel.h"
#endif

// Declare namespace
namespace UeModel
{
  /**
  * \brief Implicitly encapsulate different unique mechansims how to generate one unique ID as a LONG number. LONG value at least
  * can uniquely indicate one node or one link in a specified parcel.
  */
  class UEMODEL_CLASS INetAllocator
  {
    ///
    friend class IRoadNetwork;

  protected:
    ///
    /// Constructor & deconstructor: Here is only be called by its descendants
    ///
    /**
    * \brief Only directly used by inner side
    */
    virtual ~INetAllocator()
    {
    }

  public:
    /**
    * \brief ����������Ҫ�ص�unique ID��ȡ������λ��
    *
    * \param eleType Ҫ������
    * \param eleOrder Ҫ��ID
    * \param curParcel �洢��Ҫ�ص���������ָ��
    * \param isLink ��Ҫ����·�λ��ǽ��
    * \param Ҫ�ص�����λ��
    */
    virtual long ID2Long(long eleType, long eleOrder, INetParcel *curParcel = 0, bool isLink = true) = 0;

    /**
    * \brief ��������Ҫ�ص�����ת��Ϊunique ID��ʾ
    *
    * \param idx Ҫ�ص�����λ��
    * \param curParcel �洢��Ҫ�ص���������ָ��
    * \param isLink ��Ҫ����·�λ��ǽ��
    */
    virtual void Long2ID(long idx, INetParcel *curParcel = 0, bool isLink = true) = 0;
  };
}

#endif
