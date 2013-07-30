#include "basicfunctionhook.h"

using namespace UeGui;

CBasicFunctionHook::CBasicFunctionHook()
{
}

CBasicFunctionHook::~CBasicFunctionHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CBasicFunctionHook::MakeGUI()
{
  FetchWithBinary();
  MakeNames();
  MakeControls();
  ConfigInit();
  HelpPicMark=1;
  MSGBoxMark=false;
}

tstring CBasicFunctionHook::GetBinaryFileName()
{
  return _T("basicfunctionhook.bin");
}

void CBasicFunctionHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_BackGround,	"BackGround"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_BackGroundText,	"BackGroundText"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_GotoMapBtn,	"GotoMapBtn"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_BackButton,	"BackButton"));

  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_LeftBtnCenter,	"LeftBtnCenter"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_LeftBtnLeft,	"LeftBtnLeft"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_LeftBtnRight,	"LeftBtnRight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_LeftBtnIcon,	"LeftBtnIcon"));

  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_RightBtnCenter,	"RightBtnCenter"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_RightBtnLeft,	"RightBtnLeft"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_RightBtnRight,	"RightBtnRight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_RightBtnIcon,	"RightBtnIcon"));

  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicGoMap,	"HelpPicGoMap"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicGoBack,	"HelpPicGoBack"));

  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicOne,	"HelpPicOne"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnThree,	"PicOneBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnFour,	"PicOneBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnFive,	"PicOneBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnSix,	"PicOneBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnSeven,	"PicOneBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicOneBtnEight,	"PicOneBtnEight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicTwo,	"HelpPicTwo"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnThree,	"PicTwoBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnFour,	"PicTwoBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnFive,	"PicTwoBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnSix,	"PicTwoBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnSeven,	"PicTwoBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnEight,	"PicTwoBtnEight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnNine,	"PicTwoBtnNine"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnTen,	"PicTwoBtnTen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnEleven,	"PicTwoBtnEleven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnTwelve,	"PicTwoBtnTwelve"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnThirteen,	"PicTwoBtnThirteen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnFourteen,	"PicTwoBtnFourteen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicTwoBtnFifTeen,	"PicTwoBtnFifTeen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicThree,	"HelpPicThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicThreeBtnThree,	"PicThreeBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicThreeBtnFour,	"PicThreeBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicThreeBtnFive,	"PicThreeBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicThreeBtnSix,	"PicThreeBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicThreeBtnSeven,	"PicThreeBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicFour,	"HelpPicFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnThree,	"PicFourBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnFour,	"PicFourBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnFive,	"PicFourBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnSix,	"PicFourBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnSeven,	"PicFourBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnEight,	"PicFourBtnEight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnNine,	"PicFourBtnNine"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFourBtnTen,	"PicFourBtnTen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicFive,	"HelpPicFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnThree,	"PicFiveBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnFour,	"PicFiveBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnFive,	"PicFiveBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnSix,	"PicFiveBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnSeven,	"PicFiveBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicFiveBtnEight,	"PicFiveBtnEight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicSix,	"HelpPicSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnThree,	"PicSixBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnFour,	"PicSixBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnFive,	"PicSixBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnSix,	"PicSixBtnSix"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnSeven,	"PicSixBtnSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnEight,	"PicSixBtnEight"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnNine,	"PicSixBtnNine"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSixBtnTen,	"PicSixBtnTen"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpPicSeven,	"HelpPicSeven"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSevenBtnThree,	"PicSevenBtnThree"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSevenBtnFour,	"PicSevenBtnFour"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSevenBtnFive,	"PicSevenBtnFive"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_PicSevenBtnSix,	"PicSevenBtnSix"));

  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_helpMessageBoxBtn,	"helpMessageBoxBtn"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpMessageUpLabel,	"HelpMessageUpLabel"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpMessageCenterLabel,	"HelpMessageCenterLabel"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_HelpMessageDownLabel,	"HelpMessageDownLabel"));
  m_ctrlNames.insert(GuiName::value_type(BasicFunctionHook_IconTip,	"IconTip"));
}

void CBasicFunctionHook::MakeControls()
{
  m_backButtonCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_BackButton));
  m_gotoMapBtnCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_GotoMapBtn));
  //��һ��
  m_leftBtnCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_LeftBtnCenter));
  m_leftBtnCtrl.SetIconElement(GetGuiElement(BasicFunctionHook_LeftBtnIcon));
  m_leftBtnCtrl.SetLeftElement(GetGuiElement(BasicFunctionHook_LeftBtnLeft));
  m_leftBtnCtrl.SetRightElement(GetGuiElement(BasicFunctionHook_LeftBtnRight));
  //��һ��
  m_rightBtnCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_RightBtnCenter));
  m_rightBtnCtrl.SetIconElement(GetGuiElement(BasicFunctionHook_RightBtnIcon));
  m_rightBtnCtrl.SetLeftElement(GetGuiElement(BasicFunctionHook_RightBtnLeft));
  m_rightBtnCtrl.SetRightElement(GetGuiElement(BasicFunctionHook_RightBtnRight));
  //����ͼƬ�з��ص�ͼ����
  m_helpPicGoMapCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicGoMap));
  //����ͼƬ�з�����һ��������
  m_helpPicGoBackCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicGoBack));
  //������Ϣ��ʾ��
  m_helpMessageBoxBtnCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_helpMessageBoxBtn));
  m_helpMessageBoxBtnCtrl.SetIconElement(GetGuiElement(BasicFunctionHook_IconTip));
  m_helpMessageUpLabel.SetLabelElement(GetGuiElement(BasicFunctionHook_HelpMessageUpLabel));
  m_helpMessageCenterLabel.SetLabelElement(GetGuiElement(BasicFunctionHook_HelpMessageCenterLabel));
  m_helpMessageDownLabel.SetLabelElement(GetGuiElement(BasicFunctionHook_HelpMessageDownLabel));
  //����ͼƬ1--�˵�
  m_helpPicOneCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicOne));
  //�˵�--�ҵط�
  m_findPlce.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnThree));
  //�˵�--·�߲���
  m_routeOperation.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnFour));
  //�˵�--����ͨ����
  m_DDTService.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnFive));
  //�˵�--�ҵ���Ϣ
  m_myInformation.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnSix));
  //�˵�--��������
  m_naviSetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnSeven));
  //�˵�--ϵͳ����
  m_sysSetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicOneBtnEight));

  //����ͼƬ2--�ҵط�
  m_helpPicTwoCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicTwo));
  m_searchPlce.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnThree));
  m_searchRoute.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnFour));
  m_sortting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnFive));
  m_searchHistory.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnSix));
  m_searchAdd.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnSeven));
  m_searchAround.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnEight));
  m_searchQCode.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnNine));
  m_searchArea.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnTen));
  m_goHome.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnEleven));
  m_goCompany.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnTwelve));
  m_commonPoint1.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnThirteen));
  m_commonPoint2.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnFourteen));
  m_commonPoint3.SetCenterElement(GetGuiElement(BasicFunctionHook_PicTwoBtnFifTeen));

  //����ͼƬ3--�ҵ���Ϣ
  m_helpPicThreeCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicThree));
  m_historyInfo.SetCenterElement(GetGuiElement(BasicFunctionHook_PicThreeBtnThree));
  m_AddInfo.SetCenterElement(GetGuiElement(BasicFunctionHook_PicThreeBtnFour));
  m_myJourney.SetCenterElement(GetGuiElement(BasicFunctionHook_PicThreeBtnFive));
  m_commonPoint.SetCenterElement(GetGuiElement(BasicFunctionHook_PicThreeBtnSix));
  m_capacityInfo.SetCenterElement(GetGuiElement(BasicFunctionHook_PicThreeBtnSeven));

  //����ͼƬ4--��������
  m_helpPicFourCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicFour));
  m_mapDisplay.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnThree));
  m_intersectionZoomIn.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnFour));
  m_electronicEye.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnFive));
  m_promptSetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnSix));
  m_routeSetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnSeven));
  m_trajectorySetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnEight));
  m_safetySetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnNine));
  m_init.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFourBtnTen));

  //����ͼƬ5--ϵͳ����
  m_helpPicFiveCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicFive));
  m_voiceSetting.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnThree));
  m_carIcon.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnFour));
  m_timeCalibration.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnFive));
  m_startStatement.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnSix));
  m_editonInfo.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnSeven));
  m_exitSys.SetCenterElement(GetGuiElement(BasicFunctionHook_PicFiveBtnEight));

  //����ͼƬ6--��ѡ���·�ߵĲ���
  m_helpPicSixCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicSix));
  m_stopNavi.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnThree));
  m_passRoute.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnFour));
  m_adjustRoute.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnFive));
  m_detourPlan.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnSix));
  m_nextDestination.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnSeven));
  m_generalizationRoute.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnEight));
  m_demoNavi.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnNine));
  m_delRoute.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSixBtnTen));

  //����ͼƬ7--����ͨ����
  m_helpPicSevenCtrl.SetCenterElement(GetGuiElement(BasicFunctionHook_HelpPicSeven));
  m_4S.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSevenBtnThree));
  m_viewSearch.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSevenBtnFour));
  m_operationHelp.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSevenBtnFive));
  m_updateService.SetCenterElement(GetGuiElement(BasicFunctionHook_PicSevenBtnSix));
}

short CBasicFunctionHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case BasicFunctionHook_BackButton:
    {
      if (MSGBoxMark)
        break;
      m_backButtonCtrl.MouseDown();
    }
    break;
  case BasicFunctionHook_GotoMapBtn:
    {
      if (MSGBoxMark)
        break;
      m_gotoMapBtnCtrl.MouseDown();
    }
    break;
  case BasicFunctionHook_LeftBtnCenter:
  case BasicFunctionHook_LeftBtnIcon:
  case BasicFunctionHook_LeftBtnLeft:
  case BasicFunctionHook_LeftBtnRight:
    {
      if (MSGBoxMark)
        break;
      m_leftBtnCtrl.MouseDown();
    }
    break;
  case BasicFunctionHook_RightBtnCenter:
  case BasicFunctionHook_RightBtnIcon:
  case BasicFunctionHook_RightBtnLeft:
  case BasicFunctionHook_RightBtnRight:
    {
      if (MSGBoxMark)
        break;
      m_rightBtnCtrl.MouseDown();
    }
    break;
  default:
    m_isNeedRefesh = false;
    assert(false);
    break;
  }
/*  if (m_isNeedRefesh)
  {
    Refresh();
  }*/
  m_isNeedRefesh = true;
  return ctrlType;
}

short CBasicFunctionHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CBasicFunctionHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
    case BasicFunctionHook_BackGround:
    case BasicFunctionHook_BackGroundText:
    case BasicFunctionHook_HelpPicOne:
    case BasicFunctionHook_HelpPicTwo:
    case BasicFunctionHook_HelpPicThree:
    case BasicFunctionHook_HelpPicFour:  
    case BasicFunctionHook_HelpPicFive:
    case BasicFunctionHook_HelpPicSix:
    case BasicFunctionHook_HelpPicSeven:
    case BasicFunctionHook_IconTip:
    case BasicFunctionHook_helpMessageBoxBtn:
    case BasicFunctionHook_HelpMessageUpLabel:
    case BasicFunctionHook_HelpMessageCenterLabel:
    case BasicFunctionHook_HelpMessageDownLabel:
      {
        if(MSGBoxMark)
        {
          Message(false);
          break;
        }
        break;
      }
  case BasicFunctionHook_BackButton:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      if(ctrlType == m_downElementType)
      {
        /*CViewHook::m_prevHookType = CViewHook::DHT_BasicFunctionHook;
        CViewHook::m_curHookType = CViewHook::DHT_OperationHelpHook;*/
        CAggHook::Return();
      }
      m_backButtonCtrl.MouseUp();
    }
    break;
  case BasicFunctionHook_GotoMapBtn:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      if(ctrlType == m_downElementType)
      {
        /*CViewHook::m_prevHookType=CViewHook::m_curHookType;
        CViewHook::m_curHookType=CViewHook::DHT_MapHook;*/
        CAggHook::GoToMapHook();
        ((CAggHook *)m_view->GetHook(CViewHook::DHT_MapHook))->ComeBack();
      }
      m_gotoMapBtnCtrl.MouseUp();
    }
    break;
  case BasicFunctionHook_LeftBtnCenter:
  case BasicFunctionHook_LeftBtnIcon:
  case BasicFunctionHook_LeftBtnLeft:
  case BasicFunctionHook_LeftBtnRight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      if(HelpPicMark<1&&HelpPicMark>7)
        break;
      m_leftBtnCtrl.MouseUp();
      if(HelpPicMark>1&&HelpPicMark<=7)
      {
        HelpPicMark--;
        ShowPicture(HelpPicMark);
      }
    }
    break;
  case BasicFunctionHook_RightBtnCenter:
  case BasicFunctionHook_RightBtnIcon:
  case BasicFunctionHook_RightBtnLeft:
  case BasicFunctionHook_RightBtnRight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      if(HelpPicMark<1||HelpPicMark>7)
        break;
      m_rightBtnCtrl.MouseUp();     
      if(HelpPicMark>=1&&HelpPicMark<7)
      {
        HelpPicMark++;
        ShowPicture(HelpPicMark);
      }
    }
    break;
  case BasicFunctionHook_HelpPicGoMap:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դӵ�ǰ������ٷ�");
      m_helpMessageCenterLabel.SetCaption("�ص�ͼ����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_HelpPicGoBack:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetVisible(false);
      m_helpMessageCenterLabel.SetCaption("�������Է�����һ��������");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;

    //����ͼƬ1
  case BasicFunctionHook_PicOneBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪲�ѯ��ʽѡ��");
      m_helpMessageCenterLabel.SetCaption("����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicOneBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪶Ե�ǰ·�ߵ�");
      m_helpMessageCenterLabel.SetCaption("����ѡ�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicOneBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪵���ͨ����");
      m_helpMessageCenterLabel.SetCaption("��ѡ�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicOneBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪶��û����ݹ�");
      m_helpMessageCenterLabel.SetCaption("��Ĳ���ѡ�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicOneBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪶Ե������ܵ�");
      m_helpMessageCenterLabel.SetCaption("���Ի�����ѡ�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicOneBtnEight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪶Ի������ܵ�");
      m_helpMessageCenterLabel.SetCaption("���Ի�����ѡ�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;

    //����ͼƬ2
  case BasicFunctionHook_PicTwoBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ������������ѯ");
      m_helpMessageCenterLabel.SetCaption("��ͼ���ݿ�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��������·����");
      m_helpMessageCenterLabel.SetCaption("ѯ��ͼ���ݿ�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ���ѡ��һ������");
      m_helpMessageCenterLabel.SetCaption("����ѯ��ͼ���ݿ�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ�ѯ�������");
      m_helpMessageCenterLabel.SetCaption("�������б������ʷ��Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ�ѯ�������");
      m_helpMessageCenterLabel.SetCaption("��ַ����¼");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnEight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹����趨һ���ο�λ��");
      m_helpMessageCenterLabel.SetCaption("�ڴ�λ�ø�����ѯ��ͼ����");
      m_helpMessageDownLabel.SetCaption("��");
    }
    break;
  case BasicFunctionHook_PicTwoBtnNine:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ�������λ��Q����");
      m_helpMessageCenterLabel.SetCaption("��ѯ��ͼ���ݿ�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnTen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ���������������");
      m_helpMessageCenterLabel.SetCaption("��ѯ��ͼ���ݿ�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnEleven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("����������û����õļ�ΪĿ");
      m_helpMessageCenterLabel.SetCaption("�ĵؿ��ٿ�ʼ����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnTwelve:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("����������û����õĵ�λΪ");
      m_helpMessageCenterLabel.SetCaption("Ŀ�ĵؿ��ٿ�ʼ����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnThirteen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("������ﶨλ���û����õĳ�");
      m_helpMessageCenterLabel.SetCaption("�õ�1λ��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnFourteen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("������ﶨλ���û����õĳ�");
      m_helpMessageCenterLabel.SetCaption("�õ�2λ��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicTwoBtnFifTeen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("������ﶨλ���û����õĳ�");
      m_helpMessageCenterLabel.SetCaption("�õ�3λ��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
    //����ͼƬ3
  case BasicFunctionHook_PicThreeBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Թ�����ʷ��Ϣ");
      m_helpMessageCenterLabel.SetCaption("��¼");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicThreeBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Թ����ַ����");
      m_helpMessageCenterLabel.SetCaption("¼");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicThreeBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Թ����г�");
      m_helpMessageCenterLabel.SetCaption("��¼");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicThreeBtnSix:
    {
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Թ����õ�");
      m_helpMessageCenterLabel.SetCaption("��Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicThreeBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ鿴�ҵ���");
      m_helpMessageCenterLabel.SetCaption("Ϣ�и����û����ݵĴ洢��");
      m_helpMessageDownLabel.SetCaption("��");
    }
    break;
    //����ͼƬ4
  case BasicFunctionHook_PicFourBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Խ��е�ͼ��ʾ");
      m_helpMessageCenterLabel.SetCaption("�ĸ��Ի�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFourBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ�������·�ڷŴ�");
      m_helpMessageCenterLabel.SetCaption("ͼ����ʾ/����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFourBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��԰������۵ķ�");
      m_helpMessageCenterLabel.SetCaption("�����õ������Ƿ���ʾ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFourBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��ԶԵ���������");
      m_helpMessageCenterLabel.SetCaption("����ʾ���и��Ի�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFourBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ�������ϵͳ����");
      m_helpMessageCenterLabel.SetCaption("·��ʱ��·������");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
//   case BasicFunctionHook_PicFourBtnEight:
//     {
//       if(MSGBoxMark)
//       {
//         Message(false);
//         break;
//       }
//       Message(true);
//       m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ������ü�¼�켣");
//       m_helpMessageCenterLabel.SetCaption("�ļ�¼����");
//       m_helpMessageDownLabel.SetVisible(false);
//     }
//     break;
//   case BasicFunctionHook_PicFourBtnNine:
//     {
//       if(MSGBoxMark)
//       {
//         Message(false);
//         break;
//       }
//       Message(true);
//       m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ������ü�ʻ����");
//       m_helpMessageCenterLabel.SetCaption("�еİ�ȫ�����Ƿ���");
//       m_helpMessageDownLabel.SetVisible(false);
//     }
//     break;
  case BasicFunctionHook_PicFourBtnTen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Խ�����������");
      m_helpMessageCenterLabel.SetCaption("��ϵͳ�����еĸ����������");
      m_helpMessageDownLabel.SetCaption("������ʼ״̬");
    }
    break;
    //����ͼƬ5
  case BasicFunctionHook_PicFiveBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Խ����й�����");
      m_helpMessageCenterLabel.SetCaption("�ĸ��Ի�����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFiveBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ����޸ĵ�������");
      m_helpMessageCenterLabel.SetCaption("�е�ͼ����ʾ���Գ�ͼ��");
    }
    break;
  case BasicFunctionHook_PicFiveBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��������Ƿ�ͨ��");
      m_helpMessageCenterLabel.SetCaption("GPSʱ��У׼ϵͳʱ��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFiveBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��������������");
      m_helpMessageCenterLabel.SetCaption("�Ƿ���ʾ��������");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFiveBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ鿴����İ�");
      m_helpMessageCenterLabel.SetCaption("����Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicFiveBtnEight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetVisible(false);
      m_helpMessageCenterLabel.SetCaption("ͨ���˹��ܿ����˳����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
    //����ͼƬ6
  case BasicFunctionHook_PicSixBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Կ�ʼ/ֹͣ�Ե�ǰ·");
      m_helpMessageCenterLabel.SetCaption("�ߵĵ���");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Դ򿪹滮·�߾���");
      m_helpMessageCenterLabel.SetCaption("�ĵ�·�б�");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��ԶԵ�ǰ·�߽�");
      m_helpMessageCenterLabel.SetCaption("�е���");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("���������ƹ���ǰ·�߲���");
      m_helpMessageCenterLabel.SetCaption("��һ���µ�·��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnSeven:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("��ѡ���ڶ�Ŀ�ĵ�·��״̬��");
      m_helpMessageCenterLabel.SetCaption("��Ч����������������ǰĿ");
      m_helpMessageDownLabel.SetCaption("�ĵ����滮��·��");
    }
    break;
  case BasicFunctionHook_PicSixBtnEight:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("����������ʾ��ǰ·�ߵĸ�");
      m_helpMessageCenterLabel.SetCaption("����ͼ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnNine:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("�������Կ�ʼ/ֹͣ�Ե�ǰ·");
      m_helpMessageCenterLabel.SetCaption("�ߵ�ģ�⵼��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSixBtnTen:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetVisible(false);
      m_helpMessageCenterLabel.SetCaption("��������ɾ����ǰ·��");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
    //����ͼƬ7
  case BasicFunctionHook_PicSevenBtnThree:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ�ѯ4S��ר��");
      m_helpMessageCenterLabel.SetCaption("��Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSevenBtnFour:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ�ѯ���ξ���");
      m_helpMessageCenterLabel.SetCaption("ר����Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;
  case BasicFunctionHook_PicSevenBtnFive:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ鿴�������");
      m_helpMessageCenterLabel.SetCaption("����");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;  
  case BasicFunctionHook_PicSevenBtnSix:
    {
      if(MSGBoxMark)
      {
        Message(false);
        break;
      }
      Message(true);
      m_helpMessageUpLabel.SetCaption("ͨ���˹��ܿ��Բ鿴��������");
      m_helpMessageCenterLabel.SetCaption("�����Ϣ");
      m_helpMessageDownLabel.SetVisible(false);
    }
    break;

  default:
    m_isNeedRefesh = false;
    assert(false);
    break;
  }
  if (m_isNeedRefesh)
  {
    this->Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

bool CBasicFunctionHook::operator ()()
{
  return false;
}

void CBasicFunctionHook::PicOneVisble(bool value)
{
  m_helpPicOneCtrl.SetVisible(value);
  m_findPlce.SetVisible(value);
  m_routeOperation.SetVisible(value);
  m_DDTService.SetVisible(value);
  m_myInformation.SetVisible(value);
  m_naviSetting.SetVisible(value);
  m_sysSetting.SetVisible(value);

  m_leftBtnCtrl.SetEnable(false);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicTwoVisble(bool value)
{
  m_helpPicTwoCtrl.SetVisible(value);
  m_searchPlce.SetVisible(value);
  m_searchRoute.SetVisible(value);
  m_sortting.SetVisible(value);
  m_searchHistory.SetVisible(value);
  m_searchAdd.SetVisible(value);
  m_searchAround.SetVisible(value);
  m_searchQCode.SetVisible(value);
  m_searchArea.SetVisible(value);
  m_goHome.SetVisible(value);
  m_goCompany.SetVisible(value);
  m_commonPoint1.SetVisible(value);
  m_commonPoint2.SetVisible(value);
  m_commonPoint3.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicThreeVisble(bool value)
{
  m_helpPicThreeCtrl.SetVisible(value);
  m_historyInfo.SetVisible(value);
  m_AddInfo.SetVisible(value);
  m_myJourney.SetVisible(value);
  m_commonPoint.SetVisible(value);
  m_capacityInfo.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicFourVisble(bool value)
{
  m_helpPicFourCtrl.SetVisible(value);
  m_mapDisplay.SetVisible(value);
  m_intersectionZoomIn.SetVisible(value);
  m_electronicEye.SetVisible(value);
  m_promptSetting.SetVisible(value);
  m_routeSetting.SetVisible(value);
  m_trajectorySetting.SetVisible(value);
  m_safetySetting.SetVisible(value);
  m_init.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicFiveVisble(bool value)
{
  m_helpPicFiveCtrl.SetVisible(value);
  m_voiceSetting.SetVisible(value);
  m_carIcon.SetVisible(value);
  m_timeCalibration.SetVisible(value);
  m_startStatement.SetVisible(value);
  m_editonInfo.SetVisible(value);
  m_exitSys.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicSixVisble(bool value)
{
  m_helpPicSixCtrl.SetVisible(value);
  m_stopNavi.SetVisible(value);
  m_passRoute.SetVisible(value);
  m_adjustRoute.SetVisible(value);
  m_detourPlan.SetVisible(value);
  m_nextDestination.SetVisible(value);
  m_generalizationRoute.SetVisible(value);
  m_demoNavi.SetVisible(value);
  m_delRoute.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(true);
  MSGBoxMark=false;
}

void CBasicFunctionHook::PicSevenVisble(bool value)
{
  m_helpPicSevenCtrl.SetVisible(value);
  m_4S.SetVisible(value);
  m_viewSearch.SetVisible(value);
  m_operationHelp.SetVisible(value);
  m_updateService.SetVisible(value);

  m_leftBtnCtrl.SetEnable(true);
  m_rightBtnCtrl.SetEnable(false);
  MSGBoxMark=false;
}

void CBasicFunctionHook::ConfigInit()
{
  m_leftBtnCtrl.SetEnable(false);
}

void CBasicFunctionHook::ShowPicture(int value)
{
  switch (value)
  {
  case 1:
    {
      PicTwoVisble(false);
      PicThreeVisble(false);
      PicFourVisble(false);
      PicFiveVisble(false);
      PicSixVisble(false);
      PicSevenVisble(false);
      PicOneVisble(true);
      break;
    }
  case 2:
    {
      PicOneVisble(false);
      PicThreeVisble(false);
      PicFourVisble(false);
      PicFiveVisble(false);
      PicSixVisble(false);
      PicSevenVisble(false);
      PicTwoVisble(true);
      break;
    }
  case 3:
    {
      PicOneVisble(false);
      PicTwoVisble(false);
      PicFourVisble(false);
      PicFiveVisble(false);
      PicSixVisble(false);
      PicSevenVisble(false);
      PicThreeVisble(true);
      break;
    }
  case 4:
    {
      PicOneVisble(false);
      PicTwoVisble(false);
      PicThreeVisble(false);
      PicFiveVisble(false);
      PicSixVisble(false);
      PicSevenVisble(false);
      PicFourVisble(true);
      break;
    }
  case 5:
    {
      PicOneVisble(false);
      PicTwoVisble(false);
      PicThreeVisble(false);
      PicFourVisble(false);
      PicSixVisble(false);
      PicSevenVisble(false);
      PicFiveVisble(true);
      break;
    }
  case 6:
    {
      PicOneVisble(false);
      PicTwoVisble(false);
      PicThreeVisble(false);
      PicFourVisble(false);
      PicFiveVisble(false);
      PicSevenVisble(false);
      PicSixVisble(true);
      break;
    }
  case 7:
    {
      PicOneVisble(false);
      PicTwoVisble(false);
      PicThreeVisble(false);
      PicFourVisble(false);
      PicFiveVisble(false);
      PicSixVisble(false);
      PicSevenVisble(true);
      break;
    }
  default:
    break;
  }
}

void CBasicFunctionHook::Message(bool value)
{
  m_helpMessageBoxBtnCtrl.SetVisible(value);
  m_helpMessageUpLabel.SetVisible(value);
  m_helpMessageCenterLabel.SetVisible(value);
  m_helpMessageDownLabel.SetVisible(value);

  MSGBoxMark = value;
}

void CBasicFunctionHook::Init()
{
  ShowPicture(1);
  HelpPicMark=1;
}