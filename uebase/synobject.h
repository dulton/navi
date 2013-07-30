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
#ifndef _UEBASE_SYNOBJECT_H
#define _UEBASE_SYNOBJECT_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// UeBase namespace
namespace UeBase
{
  /**
  * \brief ������Դͬ�����ԵĽӿڶ���
  */
  class UEBASE_CLASS CSynObject
  {
  public:
    //
    // ����&����
    //
    /*!
    * \brief Ĭ�Ϲ��캯��
    */
    CSynObject()
    {
    }

    /*!
    * \brief ��������
    */
    virtual ~CSynObject()
    {
    }

  public:
    //
    //
    //
    /**
    * \brief �Թ�����Դ����
    */
    virtual void Lock() = 0;

    /**
    * \brief �Թ�����Դ����
    */
    virtual void UnLock() = 0;
  };

  /**
  * \brief ������Դͬ�����ԵĽӿ�ί��
  */
  class UEBASE_CLASS CSynGuard : public CSynObject
  {
  public:
    //
    //
    //
    /*!
    * \brief ���캯��
    */
    CSynGuard(CSynObject *synObject = 0, bool isAuto = false);

    /*!
    * \brief ��������
    */
    ~CSynGuard();

    /**
    * \brief �Թ�����Դ����
    */
    virtual void Lock()
    {
      m_synObject->Lock();
    }

    /**
    * \brief �Թ�����Դ����
    */
    virtual void UnLock()
    {
      m_synObject->UnLock();
    }

  private:
    //
    CSynObject *m_synObject;

    // 
    bool m_isAuto;
  };
}

#endif