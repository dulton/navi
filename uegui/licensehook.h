/*
*
* Copyright (C) 2012-06-20 By Hejd
* licensehook_new.h
*
*/

#ifndef _UEGUI_LICENSEHOOK_NEW_H
#define _UEGUI_LICENSEHOOK_NEW_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to its parent
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
#include "uicheckbutton.h"

// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z

using namespace UeGui;

namespace UeGui
{
  class UEGUI_CLASS CLicenseHook : public CAggHook
  {
  public:
    CLicenseHook() : CAggHook()
    {
    }
    virtual ~CLicenseHook() 
    {
      // Note: ...
      // Release all GUI elements in children considering there maybe using special APIs limited to OS
      m_elements.clear();
      m_ctrlNames.clear();
      m_imageNames.clear();
    }
  public:
    /**
    *
    **/
    enum LicenseElementType
    {
      // Splash operations
      LicenseHook_Begin = 0,
      LicenseHook_AcceptBtn,
      LicenseHook_AlwaysAcceptBtn,
      LicenseHook_RejectBtn,
      LicenseHook_LicenseCtrl,
      LicenseHook_End
    };
  public:

    virtual void MakeGUI();

    virtual void Init();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

  protected:
    /*
    * ��ȡ�������ļ����ƣ�������·������:licensehook.bin
    * �÷��������ฺ��ʵ�֣��������, �ұ���ʵ�֣���Ҫ��Ϊ��ͳһ��ȡ�������ļ�����
    */
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

  private:
    void SetButtonInfo();
    void OpenMapHook();
    void CloseSys();
    void SaveCheckSetting(bool isAlways);
  private:
    CGeoPoint<short> m_startpoint;

    CUiButton m_acceptBtn;
    CUiButton m_rejectBtn;
    CUiButton m_alwaysAcceptBtn;
  };
}
#endif