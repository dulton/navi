#ifndef _UEGUI_NAVIGATIONLEFTHOOK_H
#define _UEGUI_NAVIGATIONLEFTHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class CNaviMapSettingHook;
  class CPromptSettingHook;
  class CRouteSettingHook;

  class UEGUI_CLASS CNavigationLeftHook : public CAggHook
  {
    //ֻ������ΪCSystemSettingHook����hook
    friend class CSystemSettingHook;

    CNavigationLeftHook();

    virtual ~CNavigationLeftHook();

    void SwitchTabPage(unsigned short type);

    void Reset();
  public:
    enum navigationlefthookCtrlType
    {
      navigationlefthook_Begin = 0,
      navigationlefthook_MapNavigationBtn,
      navigationlefthook_PromptSettingBtn,
      navigationlefthook_RouteSettingBtn,
      navigationlefthook_UnUsed2Btn,
      navigationlefthook_UnUsedBtn,
      navigationlefthook_UnUsed1Btn,
      navigationlefthook_End
    };

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Init();

    void DoReturn();

  protected:
    void SetTabStatus(navigationlefthookCtrlType, bool);
    
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

  private:
    navigationlefthookCtrlType m_active;

    CNaviMapSettingHook* m_naviMapSetting;
    CPromptSettingHook* m_promptSetting;
    CRouteSettingHook* m_routeSetting;

    CUiButton m_mapNavigationBtnCtrl;
    CUiButton m_promptSettingBtnCtrl;
    CUiButton m_routeSettingBtnCtrl;
  };
}
#endif
