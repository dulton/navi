#ifndef _UEGUI_BASICFUNCTIONHOOK_H
#define _UEGUI_BASICFUNCTIONHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CBasicFunctionHook : public CAggHook
  {
  public:
    enum BasicFunctionHookCtrlType
    {
      BasicFunctionHook_Begin = 0,
      BasicFunctionHook_BackGround,
      BasicFunctionHook_BackGroundText,
      BasicFunctionHook_GotoMapBtn,
      BasicFunctionHook_BackButton,
      BasicFunctionHook_LeftBtnCenter,
      BasicFunctionHook_LeftBtnLeft,
      BasicFunctionHook_LeftBtnRight,
      BasicFunctionHook_LeftBtnIcon,
      BasicFunctionHook_RightBtnCenter,
      BasicFunctionHook_RightBtnLeft,
      BasicFunctionHook_RightBtnRight,
      BasicFunctionHook_RightBtnIcon,
      BasicFunctionHook_HelpPicOne,
      BasicFunctionHook_HelpPicGoMap,
      BasicFunctionHook_HelpPicGoBack,
      BasicFunctionHook_PicOneBtnThree,
      BasicFunctionHook_PicOneBtnFour,
      BasicFunctionHook_PicOneBtnFive,
      BasicFunctionHook_PicOneBtnSix,
      BasicFunctionHook_PicOneBtnSeven,
      BasicFunctionHook_PicOneBtnEight,
      BasicFunctionHook_HelpPicTwo,
      BasicFunctionHook_PicTwoBtnThree,
      BasicFunctionHook_PicTwoBtnFour,
      BasicFunctionHook_PicTwoBtnFive,
      BasicFunctionHook_PicTwoBtnSix,
      BasicFunctionHook_PicTwoBtnSeven,
      BasicFunctionHook_PicTwoBtnEight,
      BasicFunctionHook_PicTwoBtnNine,
      BasicFunctionHook_PicTwoBtnTen,
      BasicFunctionHook_PicTwoBtnEleven,
      BasicFunctionHook_PicTwoBtnTwelve,
      BasicFunctionHook_PicTwoBtnThirteen,
      BasicFunctionHook_PicTwoBtnFourteen,
      BasicFunctionHook_PicTwoBtnFifTeen,
      BasicFunctionHook_HelpPicThree,
      BasicFunctionHook_PicThreeBtnThree,
      BasicFunctionHook_PicThreeBtnFour,
      BasicFunctionHook_PicThreeBtnFive,
      BasicFunctionHook_PicThreeBtnSix,
      BasicFunctionHook_PicThreeBtnSeven,
      BasicFunctionHook_HelpPicFour,
      BasicFunctionHook_PicFourBtnThree,
      BasicFunctionHook_PicFourBtnFour,
      BasicFunctionHook_PicFourBtnFive,
      BasicFunctionHook_PicFourBtnSix,
      BasicFunctionHook_PicFourBtnSeven,
      BasicFunctionHook_PicFourBtnEight,
      BasicFunctionHook_PicFourBtnNine,
      BasicFunctionHook_PicFourBtnTen,
      BasicFunctionHook_HelpPicFive,
      BasicFunctionHook_PicFiveBtnThree,
      BasicFunctionHook_PicFiveBtnFour,
      BasicFunctionHook_PicFiveBtnFive,
      BasicFunctionHook_PicFiveBtnSix,
      BasicFunctionHook_PicFiveBtnSeven,
      BasicFunctionHook_PicFiveBtnEight,
      BasicFunctionHook_HelpPicSix,
      BasicFunctionHook_PicSixBtnThree,
      BasicFunctionHook_PicSixBtnFour,
      BasicFunctionHook_PicSixBtnFive,
      BasicFunctionHook_PicSixBtnSix,
      BasicFunctionHook_PicSixBtnSeven,
      BasicFunctionHook_PicSixBtnEight,
      BasicFunctionHook_PicSixBtnNine,
      BasicFunctionHook_PicSixBtnTen,
      BasicFunctionHook_HelpPicSeven,
      BasicFunctionHook_PicSevenBtnThree,
      BasicFunctionHook_PicSevenBtnFour,
      BasicFunctionHook_PicSevenBtnFive,
      BasicFunctionHook_PicSevenBtnSix,
      BasicFunctionHook_helpMessageBoxBtn,
      BasicFunctionHook_IconTip,
      BasicFunctionHook_HelpMessageUpLabel,
      BasicFunctionHook_HelpMessageCenterLabel,
      BasicFunctionHook_HelpMessageDownLabel,
      BasicFunctionHook_End
    };

    CBasicFunctionHook();

    virtual ~CBasicFunctionHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    void Init();

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

    void PicOneVisble(bool value);

    void PicTwoVisble(bool value);

    void PicThreeVisble(bool value);

    void PicFourVisble(bool value);

    void PicFiveVisble(bool value);

    void PicSixVisble(bool value);

    void PicSevenVisble(bool value);

    void ShowPicture(int value);

    void ConfigInit();

    void Message(bool value);


  private:
    CUiButton m_backButtonCtrl;
    CUiButton m_gotoMapBtnCtrl;
    //��һ��
    CUiBitButton m_leftBtnCtrl;
    //��һ��
    CUiBitButton m_rightBtnCtrl;
    //����ͼƬ�з��ص�ͼ����
    CUiButton m_helpPicGoMapCtrl;
    //����ͼƬ�з�����һ��������
    CUiButton m_helpPicGoBackCtrl;

    //����ͼƬ1--�˵�
    CUiButton m_helpPicOneCtrl;
    //�˵�--�ҵط�
    CUiButton m_findPlce;
    //�˵�--·�߲���
    CUiButton m_routeOperation;
    //�˵�--����ͨ����
    CUiButton m_DDTService;
    //�˵�--�ҵ���Ϣ
    CUiButton m_myInformation;
    //�˵�--��������
    CUiButton m_naviSetting;
    //�˵�--ϵͳ����
    CUiButton m_sysSetting;

    //����ͼƬ2--�ҵط�
    CUiButton m_helpPicTwoCtrl;
    //�ҵط�--�����
    CUiButton m_searchPlce;
    //�ҵط�--���·
    CUiButton m_searchRoute;
    //�ҵط�--�������
    CUiButton m_sortting;
    //�ҵط�--����ʷ
    CUiButton m_searchHistory;
    //�ҵط�--���ַ��
    CUiButton m_searchAdd;
    //�ҵط�--���ܱ�
    CUiButton m_searchAround;
    //�ҵط�--��Q��
    CUiButton m_searchQCode;
    //�ҵط�--������
    CUiButton m_searchArea;
    //�ҵط�--�ؼ�
    CUiButton m_goHome;
    //�ҵط�--�ص�λ
    CUiButton m_goCompany;
    //�ҵط�--���õ�1
    CUiButton m_commonPoint1;
    //�ҵط�--���õ�2
    CUiButton m_commonPoint2;
    //�ҵط�--���õ�3
    CUiButton m_commonPoint3;

    //����ͼƬ3--�ҵ���Ϣ
    CUiButton m_helpPicThreeCtrl;
    //�ҵ���Ϣ--��ʷ��Ϣ
    CUiButton m_historyInfo;
    //�ҵ���Ϣ--��ַ��
    CUiButton m_AddInfo;
    //�ҵ���Ϣ--�ҵ��г�
    CUiButton m_myJourney;
    //�ҵ���Ϣ--���õ�
    CUiButton m_commonPoint;
    //�ҵ���Ϣ--������Ϣ
    CUiButton m_capacityInfo;

    //����ͼƬ4--��������
    CUiButton m_helpPicFourCtrl;
    //��������--��ͼ��ʾ
    CUiButton m_mapDisplay;
    //��������--·�ڷŴ�ͼ
    CUiButton m_intersectionZoomIn;
    //��������--������
    CUiButton m_electronicEye;
    //��������--��ʾ����
    CUiButton m_promptSetting;
    //��������--·������
    CUiButton m_routeSetting;
    //��������--�켣����
    CUiButton m_trajectorySetting;
    //��������--��ȫ����
    CUiButton m_safetySetting;
    //��������--��ʼ��
    CUiButton m_init;

    //����ͼƬ5--ϵͳ����
    CUiButton m_helpPicFiveCtrl;
    //ϵͳ����--��������
    CUiButton m_voiceSetting;
    //ϵͳ����--�Գ�ͼ��
    CUiButton m_carIcon;
    //ϵͳ����--ʱ��У׼
    CUiButton m_timeCalibration;
    //ϵͳ����--��������
    CUiButton m_startStatement;
    //ϵͳ����--�汾��Ϣ
    CUiButton m_editonInfo;
    //ϵͳ����--�˳�ϵͳ
    CUiButton m_exitSys;

    //����ͼƬ6--��ѡ���·�ߵĲ���
    CUiButton m_helpPicSixCtrl;
    //·�߲���--ֹͣ����
    CUiButton m_stopNavi;
    //·�߲���--������·
    CUiButton m_passRoute;
    //·�߲���--����·��
    CUiButton m_adjustRoute;
    //·�߲���--��·�滮
    CUiButton m_detourPlan;
    //·�߲���--��һĿ�ĵ�
    CUiButton m_nextDestination;
    //·�߲���--����·��
    CUiButton m_generalizationRoute;
    //·�߲���--ģ�⵼��
    CUiButton m_demoNavi;
    //·�߲���--ɾ��·��
    CUiButton m_delRoute;

    //����ͼƬ7--����ͨ����
    CUiButton m_helpPicSevenCtrl;
    //����ͨ����--4S��
    CUiButton m_4S;
    //����ͨ����--�����ѯ
    CUiButton m_viewSearch;
    //����ͨ����--��������
    CUiButton m_operationHelp;
    //����ͨ����--��������
    CUiButton m_updateService;

    //������Ϣ��ʾ��
    CUiBitButton m_helpMessageBoxBtnCtrl;
    CUiLabel m_helpMessageUpLabel;
    CUiLabel m_helpMessageCenterLabel;
    CUiLabel m_helpMessageDownLabel;

    int HelpPicMark;
    bool MSGBoxMark;
  };
}
#endif
