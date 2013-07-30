#ifndef _UEGUI_MULTIROUTEPATHOPTIONHOOK_H
#define _UEGUI_MULTIROUTEPATHOPTIONHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uiradiobutton.h"
#include "routesettinghook.h"
#include "ueroute\routebasic.h"

namespace UeGui
{
  class UEGUI_CLASS CMultiRoutePathOptionHook : public CAggHook
  {
  public:
    enum MultiRoutePathOptionHookCtrlType
    {
      MultiRoutePathOptionHook_Begin = 0,
      MultiRoutePathOptionHook_MultPathSelectionBG,
      MultiRoutePathOptionHook_RecommendedRouteLeft,
      MultiRoutePathOptionHook_RecommendedRouteCenter,
      MultiRoutePathOptionHook_RecommendedRouteRight,
      MultiRoutePathOptionHook_RecommendedRouteIcon,
      MultiRoutePathOptionHook_RecommendedRouteArrow,
      MultiRoutePathOptionHook_OrdinaryRdLeft,
      MultiRoutePathOptionHook_OrdinaryRdCenter,
      MultiRoutePathOptionHook_OrdinaryRdRight,
      MultiRoutePathOptionHook_OrdinaryRdIcon,
      MultiRoutePathOptionHook_OrdinaryRdArrow,
      MultiRoutePathOptionHook_HighPriorityLeft,
      MultiRoutePathOptionHook_HighPriorityCenter,
      MultiRoutePathOptionHook_HighPriorityRight,
      MultiRoutePathOptionHook_HighPriorityIcon,
      MultiRoutePathOptionHook_HighPriorityArrow,
      MultiRoutePathOptionHook_FullLabel,
      MultiRoutePathOptionHook_FullText,
      MultiRoutePathOptionHook_HighSpeedLabel,
      MultiRoutePathOptionHook_HighSpeedText,
      MultiRoutePathOptionHook_UsingTimeLabel,
      MultiRoutePathOptionHook_UsingTimeText,
      MultiRoutePathOptionHook_End
    };

    CMultiRoutePathOptionHook();

    virtual ~CMultiRoutePathOptionHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

	  virtual void Load();

    void SaveMultiMethod(unsigned int planMethod);

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

  private:
    /**
    * \brief ��ȡ��·����ǰ�滮��ʽȫ�̾���
    **/
    void GetFullDistance();

    /**
    * \brief ��ȡ��·����ǰ�滮��ʽ���پ���
    **/
    void GetHightWayDistance();

    /**
    * \brief ��ȡ��ʱ
    **/
    void GetUsingTime();

    /**
    * \brief ��ʾ��·��״̬������
    **/
    void ShowMultiStatus();

  private:
    //�Ƽ�·��
    CUiRadioButton m_recommendedRouteCtrl;
    //һ���·
    CUiRadioButton m_ordinaryRdCtrl;
    //��������
    CUiRadioButton m_highPriorityCtrl;
    //ȫ��
    CUiLabel m_fullText;
    //����
    CUiLabel m_highSpeedText;
    //��ʱ
    CUiLabel m_usingTimeText;

    CRouteSettingHook m_RouteSet;
    //����滮��ʽ�����Ի�ȡ�滮��ʽ�Ľ�����ó�����ʱ��ֵ��
    unsigned char PlanType;
  };
}
#endif
