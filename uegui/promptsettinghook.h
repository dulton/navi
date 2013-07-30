#ifndef _UEGUI_PROMPT_SETTING_HOOK_H
#define _UEGUI_PROMPT_SETTING_HOOK_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to its parent
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

//
#ifndef _UEBASE_UESETTINGSIO_H
#include "uebase\uesettingio.h"
#endif
using namespace UeBase;

#include "uibutton.h"
#include "uilabel.h"
#include "uiradiobutton.h"

namespace UeGui
{
  /**
  * \brief ��ʾ���ý���
  */
  class UEGUI_CLASS CPromptSettingHook : public CAggHook
  {
  public:
    enum PromptSettingCtrlType
    {
      PromptSettingHook_Begin,

      PromptSettingHook_Back,

      PromptSettingHook_Map,
      PromptSettingHook_Previous,

      PromptSettingHook_TopText,

      PromptSettingHook_BriefLeft,
      PromptSettingHook_Brief,
      PromptSettingHook_BriefRight,
      PromptSettingHook_BriefIcon,

      PromptSettingHook_DetailLeft,
      PromptSettingHook_Detail,
      PromptSettingHook_DetailRight,
      PromptSettingHook_DetailIcon,

      PromptSettingHook_HighWay,
      PromptSettingHook_HighWayLeft,
      PromptSettingHook_HighWayLeftIcon,
      PromptSettingHook_HighWayLeftIconBack,
      PromptSettingHook_HighWayLeftIconGray,
      PromptSettingHook_HighWayRight,
      PromptSettingHook_HighWayRightIcon,
      PromptSettingHook_HighWayRightIconBack,
      PromptSettingHook_HighWayRightIconGray,

      PromptSettingHook_NationalWay,
      PromptSettingHook_NationalWayLeft,
      PromptSettingHook_NationalWayLeftIcon,
      PromptSettingHook_NationalWayLeftIconBack,
      PromptSettingHook_NationalWayLeftIconGray,
      PromptSettingHook_NationalWayRight,
      PromptSettingHook_NationalWayRightIcon,
      PromptSettingHook_NationalWayRightIconBack,
      PromptSettingHook_NationalWayRightIconGray,

      PromptSettingHook_Other,
      PromptSettingHook_OtherLeft,
      PromptSettingHook_OtherLeftIcon,
      PromptSettingHook_OtherLeftIconBack,
      PromptSettingHook_OtherLeftIconGray,
      PromptSettingHook_OtherRight,
      PromptSettingHook_OtherRightIcon,
      PromptSettingHook_OtherRightIconBack,
      PromptSettingHook_OtherRightIconGray,

      PromptSettingHook_End
    };

  public:
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    CPromptSettingHook();

    /**
    * \brief ��������
    */
    virtual ~CPromptSettingHook();

  public:
    /**
    *
    */
    virtual void MakeGUI();

    /**
    *
    */
    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual bool operator ()();

    /**
    *
    */
    virtual void Init();

    /**
    *
    */
    virtual void Load();

  protected:
    /**
    *
    */
    virtual tstring GetBinaryFileName();

    /**
    *
    */
    virtual void MakeNames();

  private:

		void SwitchHWSpeed(bool isAdd = true);

		void SwitchMainSpeed(bool isAdd = true);

		void SwitchOtherSpeed(bool isAdd = true);

    //���ø����ٶ�ѡ��ť״̬
    void SetHwSpeedBtnStatus();
    //���ù����ٶ�ѡ��ť״̬
    void SetMainSpeedBtnStatus();
    //����������·�ٶ�ѡ��ť״̬
    void SetOtherSpeedBtnStatus();
    //��ʼ����ť
    void MakeControls();
    //�����ٶȻ�ȡ�ٶ�����
    short GetSpeedIndex(const unsigned short speed);
    //�����ٶ���Ϣ
    void SetSpeedInfo(CUiLabel& label, unsigned short speed);
    //��������
    void SaveSetting();
  private:
    //
    UeBase::VoiceSettings m_settings;

    //�ٶ��б�
    std::vector<int> m_speedList;
    //�ٶ��ٶ�����
    short m_hwSpeedIndex;
    //�����ٶ�����
    short m_mainSpeedIndex;
    //�����ٶ�����
    short m_otherSpeedIndex;

    // Top Button
    CUiButton m_mapCtrl;
    CUiButton m_previousCtrl;

    CUiRadioButton m_briefCtrl;
    CUiRadioButton m_detailCtrl;

    CUiLabel m_highwaySpeenCtrl;
    CUiButton m_highwayLeftCtrl;
    CUiButton m_highwayRightCtrl;

    CUiLabel m_nationalWaySpeenCtrl;
    CUiButton m_nationalWayLeftCtrl;
    CUiButton m_nationalWayRightCtrl;

    CUiLabel m_otherSpeenCtrl;
    CUiButton m_otherLeftCtrl;
    CUiButton m_otherRightCtrl;
  };
}

#endif