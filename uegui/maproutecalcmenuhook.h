#ifndef _UEGUI_MAPROUTECALCMENUHOOK_H
#define _UEGUI_MAPROUTECALCMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

//#include "uilabel.h"
#include "uibutton.h"
#include "uiradiobutton.h"
#include "routewrapper.h"
#include "settingwrapper.h"
#include "viewwrapper.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CMapRouteCalcMenuHook : public CAggHook
  {
  public:
    enum MapRouteCalcMenuHookCtrlType
    {
      MapRouteCalcMenuHook_Begin = 0,
      MapRouteCalcMenuHook_Button1Left,
      MapRouteCalcMenuHook_Button1,
      MapRouteCalcMenuHook_Button1Label,
      MapRouteCalcMenuHook_Delimiter1,
      MapRouteCalcMenuHook_Button2,
      MapRouteCalcMenuHook_Button2Label,
      MapRouteCalcMenuHook_Delimiter2,
      MapRouteCalcMenuHook_Button3,
      MapRouteCalcMenuHook_Button3Label,
      MapRouteCalcMenuHook_Delimiter3,
      MapRouteCalcMenuHook_Button4,
      MapRouteCalcMenuHook_Button4Label,
      MapRouteCalcMenuHook_Button4Right,
      MapRouteCalcMenuHook_DestInfoBtn,
      MapRouteCalcMenuHook_DestLabel,
      MapRouteCalcMenuHook_DestContentLabel,
      MapRouteCalcMenuHook_DistInfoBtn,
      MapRouteCalcMenuHook_DistInfoIcon,
      MapRouteCalcMenuHook_DistInfoLabel,
      MapRouteCalcMenuHook_StartGuidanceBtn,
      MapRouteCalcMenuHook_MultiRouteBack,
      MapRouteCalcMenuHook_RadioBtn1,
      MapRouteCalcMenuHook_RouteTypeLabel1,
      MapRouteCalcMenuHook_RouteDistLabel1,
      MapRouteCalcMenuHook_RadioBtn2,
      MapRouteCalcMenuHook_RouteTypeLabel2,
      MapRouteCalcMenuHook_RouteDistLabel2,
      MapRouteCalcMenuHook_RadioBtn3,
      MapRouteCalcMenuHook_RouteTypeLabel3,
      MapRouteCalcMenuHook_RouteDistLabel3,
      MapRouteCalcMenuHook_RadioBtn4,
      MapRouteCalcMenuHook_RouteTypeLabel4,
      MapRouteCalcMenuHook_RouteDistLabel4,
      MapRouteCalcMenuHook_End
    };
    enum RadioButtonIndex
    {
      RB_00,
      RB_01,
      RB_02,
      RB_03,
      RB_04
    };
  public:
    CMapRouteCalcMenuHook();

    virtual ~CMapRouteCalcMenuHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * ��ʱ��
    **/
    virtual void Timer();
    /**
    * \���õ�ǰhook�Ƿ���ʾ
    */
    virtual void Show( bool show = true );
    /*
    * ���ø���hook
    */
    void SetParentHook(CAggHook* parentHook);
    /*
    * ���²˵�
    */
    void Update();
  protected:
    /**
    * \brief ����Ƥ�������ļ�����
    */
    virtual tstring GetBinaryFileName();
    /**
    * \brief ���ɿؼ�����
    */
    virtual void MakeNames();
    /**
    * \brief ���ɿؼ�
    */
    void MakeControls();
  private:
    /**
    * \brief �ı�滮��ʽ
    */
    void ChangePlanMethod(UeRoute::MethodType methType);
    /**
    * \brief ��ȡ�滮���
    */
    void GetPlanResult();
    /**
    * \brief RedioButton��ѡ�񷽷�
    */
    void RadioBtnCheck(RadioButtonIndex radioBtnIndex);
    /**
    * \brief ��ʾ�滮���
    */
    void ShowPlanResult();
    /**
    * \brief ��ʾ��Ŀ�ĵؾ������ʱ����ǩ��
    */
    void ShowDestInfo(UeRoute::MethodType methType);
    /**
    * \brief ��ʾ������Ϣ����ǩ��
    */
    void ShowDistLabel(double dist, CUiLabel& label);
    /**
    * \brief ��ʼ����
    */
    void StartGuidance();
    /**
    * \brief ����ʱˢ��
    */
    void TimerRefresh();
  private:
    //�˵���ť
    CUiBitButton m_button1;
    CUiBitButton m_button2;
    CUiBitButton m_button3;
    CUiBitButton m_button4;
    //Ŀ�ĵ�����
    CUiLabel m_destInfoLabel;
    //����Ŀ�ĵؾ���
    CUiLabel m_distInfoLabel;
    //��·��ѡ��
    CUiRadioButton m_radioBtn1;
    CUiRadioButton m_radioBtn2;
    CUiRadioButton m_radioBtn3;
    CUiRadioButton m_radioBtn4;
    CUiLabel m_routeDistLabel1;
    CUiLabel m_routeDistLabel2;
    CUiLabel m_routeDistLabel3;
    CUiLabel m_routeDistLabel4;
    //��ʼ����
    CUiButton m_startGuidanceBtn;
    CUiButton m_multiRouteBack;
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
    CUiButton m_delimiter3;
  private:
    // ��hook
    CAggHook* m_parentHook;
    //·�߲����ӿ�
    CRouteWrapper& m_routeWrapper;
    //��ͼ�����ӿ�
    CViewWrapper& m_viewWrapper;
    //��·���滮���
    UeRoute::PlanResultDesc m_planResult[UeRoute::MT_Max];
    //�Զ���ʼ��������ʱ
    short m_autoGuidanceTimerInterval;
    //��ʼ������ť����
    char m_guidanceCaption[MAX_NAME_LENGTH];
  };
}
#endif
