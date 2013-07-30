#ifndef _UEGUI_DIALOGEHOOK_H
#define _UEGUI_DIALOGEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

//CViewHook::DHT_MessageDialogeHook

namespace UeGui
{

  typedef void (*MessageDialogEvent)(CAggHook* sender, ModalResultType modalResult);

  class CMessageDialogEvent
  {
  public:
    CMessageDialogEvent() :  m_senderHook(NULL), m_senderHookType(CViewHook::CT_Unknown), 
      m_messageDialogEvent(NULL)
    {

    }
    CMessageDialogEvent(CAggHook* senderHook, short senderHookType, MessageDialogEvent messageDialogEvent = NULL) 
      : m_senderHook(senderHook), m_senderHookType(senderHookType), m_messageDialogEvent(messageDialogEvent)
    {

    }
    virtual ~CMessageDialogEvent(){}

    const CMessageDialogEvent& operator = (const CMessageDialogEvent& other)
    {
      if (this == &other)
      {
        return *this;
      }
      m_senderHook = other.m_senderHook;
      m_senderHookType = other.m_senderHookType;
      m_messageDialogEvent = other.m_messageDialogEvent;
      return *this;
    }  
  public:
    CAggHook* m_senderHook;
    unsigned short m_senderHookType;
    MessageDialogEvent m_messageDialogEvent;
  };

  class UEGUI_CLASS CMessageDialogHook : public CAggHook
  {
  public:
    //Ĭ�ϴ��ڶ�ʱ�ر�ʱ�� ��λ����
    static const unsigned short kNormalInterval = 10;

    enum DialogeHookCtrlType
    {
      MessageDialogHook_Begin = 0,
      MessageDialogHook_Background,
      MessageDialogHook_DialogeBackground,
      MessageDialogHook_DialogeIcon,
      MessageDialogHook_DialogeText,
      MessageDialogHook_AffirmButtonLeft,
      MessageDialogHook_AffirmButtonCenter,
      MessageDialogHook_AffirmLabel,
      MessageDialogHook_Delimiter,
      MessageDialogHook_CancelButtonCenter,
      MessageDialogHook_CancelLabel,
      MessageDialogHook_CancelButtonRight,
      MessageDialogHook_AffirmButton2Left,
      MessageDialogHook_AffirmButton2Center,
      MessageDialogHook_AffirmButton2Right,
      MessageDialogHook_AffirmLabel2,
      MessageDialogHook_End
    };

    CMessageDialogHook();

    virtual ~CMessageDialogHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Init();
    /**
    * ��ʱ��
    **/
    virtual void Timer();
  public:
    /**
    * \brief �Ƿ���Ҫ��ʱ�ر�
    */
    bool NeedCountDown();
    /**
    * \brief ���¶�ʱ�ر�
    */
    void UpdateCountDown();
    /**
    * \brief ������Ϣ�Ի������ͣ���ʾ���ֺʹ����¼�
    */
    void SetMessageDialogInfo(MessageBoxType type, const char* caption,const CMessageDialogEvent& dialogEvent, unsigned short interval = 0);
    /**
    * \brief �򿪲���ʾ�Ի���
    * ������type ��Ϣ�Ի�������
    * ������caption �Ի�������ʾ����
    * ������dialogEvent �Ի����¼�
    * ������interval �Ի���ʱ�ر�ʱ����,Ĭ��Ϊ0 ����ʱ�ر� ��λ����
    */
    static void ShowMessageDialog(MessageBoxType type, const char* caption, const CMessageDialogEvent& dialogEvent, unsigned short interval = 0);
    /**
    * \brief �رնԻ���
    */
    static void CloseMessageDialog(unsigned short senderHookType = CViewHook::DHT_Unknown);

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    void DoMouseUp(ModalResultType resultType);
  private:
    //�Ի���ʱ�ر�ʱ�� ��λ����
    unsigned short m_interval;
    CMessageDialogEvent m_messageDialogEvent;

    CUiLabel m_dialogText;
    CUiButton m_dialogeIcon;
    CUiBitButton m_affirmButton;
    CUiBitButton m_cancelButton;
    CUiBitButton m_affirmButton2;
    CUiButton m_delimiter;
  };
}
#endif
