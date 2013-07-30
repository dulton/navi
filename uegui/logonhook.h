#ifndef _UEGUI_LOGONHOOK_H
#define _UEGUI_LOGONHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

namespace UeGui
{  
  class UEGUI_CLASS CLogonHook : public CAggHook
  {
  public:
    //������Ĭ��������ֵ
    const static unsigned short kMaxProgress = 100;

    enum LogonHookCtrlType
    {
      LogonHook_Begin = 0,
      LogonHook_LogonBackground,
      LogonHook_LogonSetp1,
      LogonHook_LogonSetp2,
      LogonHook_LogonSetp3,
      LogonHook_LogonSetp4,
      LogonHook_LogonSetp5,
      LogonHook_LogonSetp6,
      LogonHook_LogonSetp7,
      LogonHook_LogonSetp8,
      LogonHook_LogonSetp9,
      LogonHook_LogonSetp10,
      LogonHook_LogonSetp11,
      LogonHook_LogonSetp12,
      LogonHook_LogonSetp13,
      LogonHook_LogonSetp14,
      LogonHook_LogonSetp15,
      LogonHook_LogonSetp16,
      LogonHook_LogonSetp17,
      LogonHook_LogonSetp18,
      LogonHook_LogonSetp19,
      LogonHook_LogonSetp20,
      LogonHook_LogonSetp21,
      LogonHook_LogonSetp22,
      LogonHook_LogonSetp23,
      LogonHook_LogonSetp24,
      LogonHook_LogonSetp25,
      LogonHook_LogonSetp26,
      LogonHook_LogonSetp27,
      LogonHook_LogonSetp28,
      LogonHook_LogonSetp29,
      LogonHook_End
    };

    CLogonHook();

    virtual ~CLogonHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    static CLogonHook* GetLogonHook();
  public:
    //GUIԪ���Ƿ�������
    bool GuiElementsLoadDone();
    ///��ս�����
    void ClearProgressBar();
    //���ý���������������Ҳ���ǵ����ȴﵽ����ֵʱ����������
    void SetMaxProgress( unsigned short maxProgress);
    //���ý��������� 0...100 Ĭ��ֵΪ0 �����ֵΪĬ��ֵ������Զ�����1
    void SetProgress(short progress = 0);
    //������ʾ
    void StartDemo();
  protected:
    virtual tstring GetBinaryFileName();
    virtual void MakeNames();
    void MakeControls();
  private:
    void SetPosition(unsigned short position);
    unsigned short GetPosition(short progress);
  private:
    //����Ԫ���Ƿ�������
    bool m_loadGuiElementsDone;
    //��������,Ĭ��Ϊ100
    short m_maxProgress;
    //��һ��ϵͳ����λ��
    unsigned short m_lastProgress;
    //��һ�ν�������λ������Ϊ0-29
    unsigned short m_lastPosition;
    //��һ�ε��ý�����
    bool m_firstSetPosition;
    //��̬����
    static CLogonHook* m_logonHook;
  };
}
#endif
