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
#ifndef _UEBASE_WINSYNOBJECT_H
#define _UEBASE_WINSYNOBJECT_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to its parent
#ifndef _UEBASE_SYNOBJECT_H
#include "synobject.h"
#endif

// UeBase namespace
namespace UeBase
{
  /**
  * \brief ���windowsϵͳ��ͬ������ʵ��(ʹ�ùؼ���ʵ��)
  */
  class UEBASE_CLASS CWinSynObject : public CSynObject
  {
  public:
    //
    //
    //
    /**
    * \brief ���캯������ʼ���ؼ��Ρ�
    */
    CWinSynObject()
    {
      ::memset(&m_cs, 0, sizeof(CRITICAL_SECTION));
      ::InitializeCriticalSection(&m_cs);
    }

    /**
    * \brief ��������
    */
    virtual ~CWinSynObject(void)
    {
    }

  public:
    //
    //
    //
    /**
    * \brief ����ؼ���(����)
    */
    virtual void Lock()
    {
      ::EnterCriticalSection ((LPCRITICAL_SECTION)&m_cs);
    }

    /**
    * \brief �뿪�ؼ���(����)
    */
    virtual void UnLock()
    {
      ::LeaveCriticalSection ((LPCRITICAL_SECTION)&m_cs);
    }

  private:
    /// �ؼ���
    CRITICAL_SECTION m_cs;
  };
}

#endif