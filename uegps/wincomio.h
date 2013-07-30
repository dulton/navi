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
#ifndef _UEGPS_COMIO_H
#define _UEGPS_COMIO_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGPS_BASE_H
#include "uegps.h"
#endif

// Refer to its parent
#ifndef _UEGPS_INFOIO_H
#include "infoio.h"
#endif

#include "autocomport.h"

#ifndef _UEBASE_UESETTINGSIO_H
#include "uebase/uesettingio.h"
#endif

//
#pragma warning( push )
#pragma warning( disable: 4996 )  // deprecated functions

//
namespace UeGps
{
  /**
  *
  **/
  class UEGPS_CLASS CWinComIO : public CInfoIO
  {
  public:
    //
    static const int          MAXCONLENGTH   = 64;
    static const unsigned int SIZEOFINQUEUE  = 4096;
    static const unsigned int SIZEOFOUTQUEUE = 1024;
    static const unsigned int MAXPORTNUMBER  = 50;
    static const unsigned int MAXBAUDTIMES   = 20;
  public:
    /**
    *
    */
    CWinComIO(const tstring &strCon, CPosInfo &posExplainer) : CInfoIO(strCon, posExplainer)
    {
      // Overlapped setting for writing operation
      m_wOverlapped.Offset = 0;
      m_wOverlapped.OffsetHigh = 0;
      m_wOverlapped.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
      assert(m_wOverlapped.hEvent != NULL);

      // Overlapped setting for reading operation
      m_rOverlapped.Offset = 0;
      m_rOverlapped.OffsetHigh = 0;
      m_rOverlapped.hEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );
      assert(m_rOverlapped.hEvent != NULL);

      m_needWorking = false;
      m_needSearchCOMPort = false;
      m_isSearchingCOMPort = false;
    }

    /**
    *
    */
    virtual ~CWinComIO()
    {
      //
      if(m_rOverlapped.hEvent)
      {
        ::CloseHandle(m_rOverlapped.hEvent);
      }

      //
      if(m_wOverlapped.hEvent)
      {
        ::CloseHandle(m_wOverlapped.hEvent);
      }

      //
      Close();
    }

  public:
    /**
    *
    */
    virtual bool Prepare();

    /**
    *
    */
    virtual bool Open(const IOSetting &setting);

    /**
    *
    */
    virtual bool Close();

    /**
    *
    */
    virtual int Read(void *content, unsigned int length);

    /**
    *
    */
    virtual int Write(void *content, unsigned int length);

    /**
    * �Ƿ���Ҫ����
    */
    bool NeedWorking();

    /**
    * �Զ����˿� ��mapmatchimpl.cpp��PrepareIO()�����е���
    */
    virtual void AutoCOMPort();

    /**
    * �����Ƿ���Ҫ�Զ������˿�
    */
    void SetIsNeedSearchCOMPort(bool bValue);

    /** 
    * �Ƿ���Ҫ�Զ������˿�
    */
    bool NeedSearchCOMPort();

    /**
    * �Ƿ����������˿�
    */
    bool IsSearchingCOMPort();

    /**
    * ɨ��˿�,ÿ�δ�һ���˿ڣ�ɨ����ɺ�ر�
    */
    void SearchCOMPort();

    /**
    * һ�δ����ж˿ڣ�ɨ����ɺ�ͳһ�رգ����SearchCOMPortB() CloseAllCOMPort()ʹ��
    */
    void OpenAllCOMPort();

    /**
    * ɨ����ɺ�ͳһ�رգ����SearchCOMPortB() OpenAllCOMPort()ʹ��
    */
    void CloseAllCOMPort();

    /**
    * ɨ��˿�,һ�δ����ж˿ڣ�ɨ����ɺ�ͳһ�ر�,���OpenAllCOMPort() CloseAllCOMPort()ʹ��
    */
    void SearchCOMPortB();

    /**
    * �Ƿ��Ѿ��ҵ����õĶ˿�
    */
    bool FindValidCOMPort();

    /**
    * ��ȡ��Ч��COM����Ϣ
    */
    void GetValidCOMPort(IOSetting& setting);

    /**
    * ���ҵ��Ķ˿ڱ��浽�����ļ���
    */
    void SaveValidCOMPortInfo();

    /**
    * ���������Ϣ
    */
    void LogMessage(const char* msg);

    /*
    * ģ�����GPS����
    */
    void TestGPSData();
  private:
    /**
    * ����GPS���
    */
    void MakeCommand(const char *str, char *cmd);
    /**
    * �����߳�
    */
    void StartThread();
    /**
    * �Զ����˿ںͲ�����
    */
    void StartAutoCOMPort();
  private:
    /**
    * �Ƿ���Ҫ����
    */
    bool m_needWorking;
    /**
    * �Ƿ���Ҫ�Զ����COM��
    */
    bool m_needSearchCOMPort;
    /**
    * �Ƿ�����ɨ��COM��
    */
    bool m_isSearchingCOMPort;
    /**
    * ����ӦCOM�ڶ���
    */
    CAutoCOMPort m_autoCOMPort; 

    // Offset of the beginning of the lock range
    OVERLAPPED m_rOverlapped;
    OVERLAPPED m_wOverlapped;
  };
}

#endif
