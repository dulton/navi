#ifndef _UEGUI_MOVEUPANDDOWNHOOK_H
#define _UEGUI_MOVEUPANDDOWNHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

namespace UeGui
{
  enum MoveType
  {
    MT_UnKnow,
    MT_Down,
    MT_Up
  };
  //���Ƶ������������Ƶ�����
  enum MoveEndType
  {
    ME_None,
    ME_DownEnd,
    ME_UpEnd
  };

  //·������ѡ��ص��������Ͷ���
  typedef void (*UpwardOrDownwardEvent)(CAggHook* senderHook, MoveType moveType);

  class UEGUI_CLASS CUpwardOrDownwardHook : public CAggHook
  {
  public:
    enum UpwardOrDownwardHookCtrlType
    {
      UpwardOrDownwardHook_Begin = 0,
      UpwardOrDownwardHook_BackGround,
      UpwardOrDownwardHook_UpwardLeft,
      UpwardOrDownwardHook_UpwardCenter,
      UpwardOrDownwardHook_UpwardRight,
      UpwardOrDownwardHook_DownwardLeft,
      UpwardOrDownwardHook_DownwardCenter,
      UpwardOrDownwardHook_DownwardRight,
      UpwardOrDownwardHook_End
    };

    CUpwardOrDownwardHook();

    virtual ~CUpwardOrDownwardHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  public:
    void SetEvent(CViewHook::HookType senderHookType, CAggHook* senderHook, UpwardOrDownwardEvent selectEvent, MoveEndType endType = ME_None);
    //��·��ѡ��hook
    static void ShowHook(CViewHook::HookType senderHookType, CAggHook* senderHook, UpwardOrDownwardEvent selectEvent, MoveEndType endType = ME_None);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    void DoMouseUp(MoveType moveType);
  private:
    CUiButton m_backGroundCtrl;
    //����
    CUiButton m_downwardCtrl;
    //����
    CUiButton m_upwardCtrl;
    //�Ƿ����Ƶ��յ�������Ƶ��յ�
    MoveEndType m_endType;
    //���õ�hook
    CAggHook* m_senderHook;
    //���õ�hook����
    CViewHook::HookType m_senderHookType;
    //·������ѡ���¼�
    UpwardOrDownwardEvent m_selectEvent;
  };
}
#endif
