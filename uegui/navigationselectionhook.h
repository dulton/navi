#ifndef _UEGUI_NAVIGATIONSELECTIONHOOK_H
#define _UEGUI_NAVIGATIONSELECTIONHOOK_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to its parent
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"

namespace UeGui
{
  class UEGUI_CLASS CNavigationSelectionHook : public CAggHook
  {
  public:
    enum NavigationSelectionHookCtrlType
    {
      NavigationSelectionHook_Begin = 0,
      NavigationSelectionHook_BackGround,
      NavigationSelectionHook_StartNavigationLeft,
      NavigationSelectionHook_StartNavigation,
      NavigationSelectionHook_StartNavigationRight,
      NavigationSelectionHook_SimulationNavigationLeft,
      NavigationSelectionHook_SimulationNavigation,
      NavigationSelectionHook_SimulationNavigationRight,
      NavigationSelectionHook_ViewRouteLeft,
      NavigationSelectionHook_ViewRoute,
      NavigationSelectionHook_ViewRouteRight,
      NavigationSelectionHook_CountdownLabel,
      NavigationSelectionHook_End
    };

    CNavigationSelectionHook();

    virtual ~CNavigationSelectionHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Timer();

    //����ʱ
    void CountDown();
    //��ʼ��ʱ�������ʱ����
    void StartCountDown(int count, bool isRefresh = true);
    //�ж��Ƿ�ʱ���� True���ѽ��� False��δ����
    bool IsCountOver();
    //���ص�ǰ�Ƿ���Ҫ��ʱ True����Ҫ���� False������Ҫ��ʱ
    bool IsNeedCount();

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    //ˢ�¼�ʱ�ؼ�
    void RefreshCountLabel(int interval, bool isRefresh = true);
  private:
    //��ʼ����
    CUiButton m_startNavigation;
    //ģ�⵼��
    CUiButton m_simulationNavigation;
    //�鿴������·
    CUiButton m_viewRoute;
    //����ʱ��ǩ
    CUiLabel m_countDownLabel;
    int m_count;
    bool m_needCount;
  };
}
#endif
