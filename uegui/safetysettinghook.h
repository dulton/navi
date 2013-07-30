#ifndef _UEGUI_SAFETY_SETTING_HOOK_H
#define _UEGUI_SAFETY_SETTING_HOOK_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to its parent
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
#include "uiradiobutton.h"

namespace UeGui
{
  /**
  * \brief ��ȫ���ý���
  */
  class UEGUI_CLASS CSafetySettingHook : public CAggHook
  {
  public:
    enum SafetySettingCtrlType
    {
      SafetySettingHook_Begin,

      SafetySettingHook_Back,

      SafetySettingHook_Map,
      SafetySettingHook_Previous,

      SafetySettingHook_TopText,

      SafetySettingHook_EnableLeft,
      SafetySettingHook_Enable,
      SafetySettingHook_EnableRight,
      SafetySettingHook_EnableIcon,

      SafetySettingHook_DisableLeft,
      SafetySettingHook_Disable,
      SafetySettingHook_DisableRight,
      SafetySettingHook_DisableIcon,
      
      SafetySettingHook_End
    };

  public:
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    CSafetySettingHook();

    /**
    * \brief ��������
    */
    virtual ~CSafetySettingHook();

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
    //
    void MakeControls();

  private:

    void SaveSetting();
    // Top Button
    CUiButton m_mapCtrl;
    CUiButton m_previousCtrl;

    CUiRadioButton m_enableCtrl;
    CUiRadioButton m_disableCtrl;
  };
}

#endif