#ifndef _UEGUI_DDTSERVICEHOOK_H
#define _UEGUI_DDTSERVICEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"
#include "uebase\geombasic.h"

namespace UeGui
{
  class UEGUI_CLASS CDdtServiceHook : public CAggHook
  {
  public:
    enum DdtServiceHookCtrlType
    {
      DdtServiceHook_Begin = 0,
      DdtServiceHook_DdtserviceBackGround,
      DdtServiceHook_DdtserviceText,
      DdtServiceHook_GotoMapBtn,
      DdtServiceHook_BackButton,
      DdtServiceHook_Position4SBtn,
      DdtServiceHook_Position4SText,
      DdtServiceHook_SceneryBtn,
      DdtServiceHook_SceneryText,
      DdtServiceHook_HelpBtn,
      DdtServiceHook_HelpText,
      DdtServiceHook_UpdateBtn,
      DdtServiceHook_UpdateText,
      DdtServiceHook_End
    };

    CDdtServiceHook();

    virtual ~CDdtServiceHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Init();

    virtual void Load();

    virtual bool operator ()();
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    //��4S��
    void Open4SShopeHook();
    //�򿪾����ѯ
    void OpenViewSpotHook();

    //4S��hook��괥���¼�
    static void On4SShopListQuery(const char* keyValue1, const char* keyValue2,  const CGeoPoint<long>& point);
    //���ξ���hook�����¼�
    static void OnViewSpotListQuery(const char* keyValue1, const char* keyValue2, const CGeoPoint<long>& point);
    //4S���ѯ����б�hook�ķ����¼�
    static void On4SShopListHookReturn();
    //4S���ѯ����б�hook�ľ���ѡ���¼�
    static void On4SShopListHookPOISelect(const char* keyValue1, const char* keyValue2,const CGeoPoint<long>& point);
  private:
    CUiButton m_gotoMapBtnCtrl;
    CUiButton m_backButtonCtrl;
    
    CUiBitButton m_helpBtnCtrl;

    CUiBitButton m_position4SBtnCtrl;

    CUiBitButton m_sceneryBtnCtrl;

    CUiBitButton m_updateBtnCtrl;
  };
}
#endif
