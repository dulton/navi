#include "restoredefaultshook.h"
#include "navisettinghook.h"
#include "settingwrapper.h"
#include "usuallyfile.h"
#include "myjourneyhook.h"
#include "userdatawrapper.h"
#include "systemsettinghook.h"
using namespace UeGui;

CRestoreDefaultshook::CRestoreDefaultshook()
{
}

CRestoreDefaultshook::~CRestoreDefaultshook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CRestoreDefaultshook::Load()
{
  m_addressBookCtrl.SetCheck(false);
  m_historyCtrl.SetCheck(false);
  m_myJourneyCtrl.SetCheck(false);
  m_elecEyeCtrl.SetCheck(false);
  m_textOne.SetCaption("��ʼ����ϵͳ�б���������в�����Ϣ�͸���");
  m_textTwo.SetCaption("���ݽ����������ȷ��Ҫɾ���ĸ�������");
}
void CRestoreDefaultshook::MakeGUI()
{
  FetchWithBinary();
  MakeNames();
  MakeControls();
}

tstring CRestoreDefaultshook::GetBinaryFileName()
{
  return _T("restoredefaultshook.bin");
}

void CRestoreDefaultshook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_HistoricalInfoLabel,	"HistoricalInfoLabel"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_HistoricalInfoCenter,	"HistoricalInfoCenter"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_HistoricalInfoIcon,	"HistoricalInfoIcon"));

  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_AddressBookLabel,	"AddressBookLabel"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_AddressBookCenter,	"AddressBookCenter"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_AddressBookIcon,	"AddressBookIcon"));

  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_MyJourneyLabel,	"MyJourneyLabel"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_MyJourneyCenter,	"MyJourneyCenter"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_MyJourneyIcon,	"MyJourneyIcon"));

  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_ElecEyeLabel,	"ElecEyeLabel"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_ElecEyeCenter,	"ElecEyeCenter"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_ElecEyeIcon,	"ElecEyeIcon"));

  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_TextOne,	"TextOne"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_TextTwo,	"TextTwo"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_TopPic,	"TopPic"));

  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_OnOk,	"OnOk"));
  m_ctrlNames.insert(GuiName::value_type(RestoreDefaultshook_OnCance,	"OnCance"));
}

void CRestoreDefaultshook::MakeControls()
{
  m_historyCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_HistoricalInfoCenter));
  m_historyCtrl.SetIconElement(GetGuiElement(RestoreDefaultshook_HistoricalInfoIcon));
  m_historyLabel.SetLabelElement(GetGuiElement(RestoreDefaultshook_HistoricalInfoLabel));

  m_addressBookCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_AddressBookCenter));
  m_addressBookCtrl.SetIconElement(GetGuiElement(RestoreDefaultshook_AddressBookIcon));
  m_addressBookLabel.SetLabelElement(GetGuiElement(RestoreDefaultshook_AddressBookLabel));

  m_myJourneyCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_MyJourneyCenter));
  m_myJourneyCtrl.SetIconElement(GetGuiElement(RestoreDefaultshook_MyJourneyIcon));
  m_myJourneyLabel.SetLabelElement(GetGuiElement(RestoreDefaultshook_MyJourneyLabel));

  m_elecEyeCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_ElecEyeCenter));
  m_elecEyeCtrl.SetIconElement(GetGuiElement(RestoreDefaultshook_ElecEyeIcon));
  m_elecEyeLabel.SetLabelElement(GetGuiElement(RestoreDefaultshook_ElecEyeLabel));

  m_textTwo.SetLabelElement(GetGuiElement(RestoreDefaultshook_TextTwo));
  m_textOne.SetLabelElement(GetGuiElement(RestoreDefaultshook_TextOne));

  m_onCanceCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_OnCance));
  m_onOkCtrl.SetCenterElement(GetGuiElement(RestoreDefaultshook_OnOk));
}

short CRestoreDefaultshook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case RestoreDefaultshook_HistoricalInfoCenter:
  case RestoreDefaultshook_HistoricalInfoIcon:
  case RestoreDefaultshook_HistoricalInfoLabel:
    {
      m_historyCtrl.MouseDown();
      m_historyLabel.MouseDown();
      AddRenderUiControls(&m_historyCtrl);
      AddRenderUiControls(&m_historyLabel);
    }
    break;
  case RestoreDefaultshook_AddressBookCenter:
  case RestoreDefaultshook_AddressBookIcon:
  case RestoreDefaultshook_AddressBookLabel:
    {
      m_addressBookCtrl.MouseDown();
      m_addressBookLabel.MouseDown();
      AddRenderUiControls(&m_addressBookCtrl);
      AddRenderUiControls(&m_addressBookLabel);
    }
    break;
  case RestoreDefaultshook_MyJourneyCenter:
  case RestoreDefaultshook_MyJourneyIcon:
  case RestoreDefaultshook_MyJourneyLabel:
    {
      m_myJourneyCtrl.MouseDown();
      m_myJourneyLabel.MouseDown();
      AddRenderUiControls(&m_myJourneyCtrl);
      AddRenderUiControls(&m_myJourneyLabel);
    }
    break;
  case RestoreDefaultshook_ElecEyeCenter:
  case RestoreDefaultshook_ElecEyeIcon:
  case RestoreDefaultshook_ElecEyeLabel:
    {
      m_elecEyeCtrl.MouseDown();
      m_elecEyeLabel.MouseDown();
      AddRenderUiControls(&m_elecEyeCtrl);
      AddRenderUiControls(&m_elecEyeLabel);
    }
    break;
  case RestoreDefaultshook_OnCance:
    {
      m_onCanceCtrl.MouseDown();
      AddRenderUiControls(&m_onCanceCtrl);
    }
    break;
  case RestoreDefaultshook_OnOk:
    {
      m_onOkCtrl.MouseDown();
      AddRenderUiControls(&m_onOkCtrl);
    }
    break;
  default:
    m_isNeedRefesh = false;
    assert(false);
    break;
  }
  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

short CRestoreDefaultshook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CRestoreDefaultshook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case RestoreDefaultshook_HistoricalInfoCenter:
  case RestoreDefaultshook_HistoricalInfoIcon:
  case RestoreDefaultshook_HistoricalInfoLabel:
    {
      m_historyCtrl.MouseUp();
      m_historyLabel.MouseUp();
    }
    break;
  case RestoreDefaultshook_AddressBookCenter:
  case RestoreDefaultshook_AddressBookIcon:
  case RestoreDefaultshook_AddressBookLabel:
    {
      m_addressBookCtrl.MouseUp();
      m_addressBookLabel.MouseUp();
    }
    break;
  case RestoreDefaultshook_MyJourneyCenter:
  case RestoreDefaultshook_MyJourneyIcon:
  case RestoreDefaultshook_MyJourneyLabel:
    {
      m_myJourneyCtrl.MouseUp();
      m_myJourneyLabel.MouseUp();
    }
    break;
  case RestoreDefaultshook_ElecEyeCenter:
  case RestoreDefaultshook_ElecEyeIcon:
  case RestoreDefaultshook_ElecEyeLabel:
    {
      m_elecEyeCtrl.MouseUp();
      m_elecEyeLabel.MouseUp();
    }
    break;
  case RestoreDefaultshook_OnCance:
    {
      m_onCanceCtrl.MouseUp();
      Return(false);
      AddRenderUiControls(&m_onCanceCtrl);
    }
    break;
  case RestoreDefaultshook_OnOk:
    {
      m_onOkCtrl.MouseUp();
      UpdateSettings();
      Return(false);
      CSystemSettingHook* systemSetting = (CSystemSettingHook*)(m_view->GetHook(CViewHook::DHT_SystemSettingHook));
      systemSetting->DoReturn();
      AddRenderUiControls(&m_onOkCtrl);
    }
    break;
  default:
    assert(false);
    m_isNeedRefesh = false;
    break;
  }
  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

bool CRestoreDefaultshook::operator ()()
{
  return false;
}
void CRestoreDefaultshook::ClearHistoryData()
{
  const CUserDataWrapper& userWrapper = CUserDataWrapper::Get();
  userWrapper.RemoveAllHistoryRecord();
  //�����ʷ·��
  userWrapper.RemoveAllRecent(); 
}
void CRestoreDefaultshook::ClearAddressBookData()
{
  const CUserDataWrapper& userWrapper = CUserDataWrapper::Get();
  userWrapper.RemoveAllFavorite();
}
void CRestoreDefaultshook::ClearMyJourneyData()
{
  const CUserDataWrapper& userWrapper = CUserDataWrapper::Get();
  userWrapper.RemoveAllJourney();
}
void CRestoreDefaultshook::ClearElecEyeData()
{
  const CUserDataWrapper& userWrapper = CUserDataWrapper::Get();
  userWrapper.DeleteAllUserEEyeData();
  ////������õ���Ϣ
  //CUsuallyFile favorite;
  //favorite.RemoveRecord(RT_HOME);
  //favorite.RemoveRecord(RT_COMPANY);
  //favorite.RemoveRecord(RT_ONE);
  //favorite.RemoveRecord(RT_TWO);
  //favorite.RemoveRecord(RT_THREE);
  /*favorite.RemoveRecord(RT_STARTPOS);*/
}
void CRestoreDefaultshook::Restore()
{
  //CsettingWrapperings* settingWrapper = CsettingWrapperings::GetsettingWrapperings();
  CSettingWrapper& settingWrapper = CSettingWrapper::Get();
    //��ʼ����������
    settingWrapper.Restore();

    MapsHeader header;
    CUeMapsIO mapsIO;
    mapsIO.GetHeader(header);
    GpsCar gpsInfo;
    gpsInfo.m_curPos.m_x = header.m_baseX;
    gpsInfo.m_curPos.m_y = header.m_baseY;
    m_view->SetGpsCar(gpsInfo);
    m_view->SetGpsPosInfo(gpsInfo);
    m_view->SetCarIcon(settingWrapper.GetCarIcon());
}
void CRestoreDefaultshook::UpdateSettings()
{
    if(m_historyCtrl.Checked())
    {
      //�����ʷ��Ϣ
      ClearHistoryData();
    }
    if(m_addressBookCtrl.Checked())
    {
      //�����ַ��
      ClearAddressBookData();
    }
    if (m_myJourneyCtrl.Checked())
    {
      //����ҵ��г�
      ClearMyJourneyData();
    }
    if (m_elecEyeCtrl.Checked())
    {
      //���������
      ClearElecEyeData();
    }
    //��ʼ������
    Restore();
}