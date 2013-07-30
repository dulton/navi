/*
* The UrbanEye PND solution is a collection of packages based on native C++ classes
* that implement the fundamental algorithms & operations required to satisfy one kind
* of mobile or portable devices with competitive qualities being a leading one.
*
* Copyright (C) 2008 Xiujie Sheng
*
* This library isn't a free software, so you cann't take the sourcecode without author's permit.
* Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
* if you illegally got it. 
*
* NOTE: 
* AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
* LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
*
* For more information, contact:
*
* China University of Geoseciences(Wuhan)
* Graduate School
*
* Xiujie Sheng
* smartpoint@sohu.com
*/
#include "guiimpl.h"
#include "licensehook.h"
//#include "queryhook.h"
//#include "listhook.h"
//#include "keyboardhook.h"
//#include "messagehook.h"
#include "maphook.h"
//#include "favorhook.h"
#include "gpshook.h"
//#include "settinghook.h"
#include "mapsettinghook.h"
#include "routesettinghook.h"
//#include "querysettinghook.h"
#include "voicesettinghook.h"
//#include "querycrosshook.h"
#include "userinfohook.h"
#include "navisettinghook.h"
#include "crosspicsettinghook.h"
#include "eeyesettinghook.h"
#include "promptsettinghook.h"
#include "safetysettinghook.h"
#include "tracksettinghook.h"
#include "systemsettinghook.h"
#include "mapscanhook.h"
#include "carsettinghook.h"
#include "timesettinghook.h"
#include "declaresettinghook.h"
#include "editionhook.h"
#include "detailmessagehook.h"
#include "detailedithook.h"
//#include "ddtservicehook.h"
#include "operationhelphook.h"
#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "uequery/codeindexctrl.h"
#endif

#include "routeoperationhook.h"
#include "passedroutehook.h"
#include "mapscanhook.h"
#include "adjustroutehook.h"
#include "mapnavigationhook.h"
#include "basicfunctionhook.h"
#include "ddtservicehelphook.h"
//#include "ddtservicequeryhook.h"
#include "ddtservicequerylisthook.h"
#include "fasthandlehelphook.h"
#include "Demonstration3Dhook.h"
#include "city3Dhook.h"
#include "myinformationhook.h"
#include "capacityinformationhook.h"
#include "messagedialoghook.h"
#include "myjourneyhook.h"
#include "myaddressbookhook.h"
#include "historyinformationhook.h"
#include "markeredithook.h"
#include "routetypeselecthook.h"
#include "upwardordownwardhook.h"
#include "logonhook.h"
#include "uebase\dbgmacro.h"
#include "guisetting.h"
#include "navigationselectionhook.h"
#include "ddtupdateservicehook.h"
#include "guidanceviewhook.h"
#include "districtselectionhook.h"
#include "typeindistselectionhook.h"

#include "inputswitchhook.h"
#include "inputspellinghook.h"
#include "inputacronymhook.h"
#include "inputcharhook.h"
#include "inputhandhook.h"
#include "poiquerylisthook.h"
#include "roadquerylisthook.h"
#include "crossquerylisthook.h"
#include "distquerylisthook.h"
#include "mainmenuhook.h"
#include "querymenuhook.h"
#include "routetypeswitchhook.h"
#include "usuallyhook.h"
#include "typeindistquerylisthook.h"
#include "fastoperationhook.h"

#if __FOR_FPC__
#include "caphook.h"
#include "poipropertyhook.h"
#include "trafficpropertyhook.h"
#include "trackpropertyhook.h"
#include "buspropertyhook.h"
#endif
using namespace UeGui;

// Refer to UeMap package
#include "uemap\view.h"
using namespace UeMap;

// Refer to UeModel package
#include "uemodel\network.h"
using namespace UeModel;

// Refer to UeRoute package
#include "ueroute\route.h"
using namespace UeRoute;

// Refer to UeQuery package
#include "uequery\query.h"
using namespace UeQuery;

#include "guisetting.h"
#include "guioperationright.h"
#include "comportsettinghook.h"
#include "productactivationhook.h"
//#include "ddtservice4shook.h"
#include "RestoreDefaultshook.h"
#include "settingwrapper.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
/**
*
*/
CGuiImpl::CGuiImpl() : m_view(0)
{
}

/**
*
*/
CGuiImpl::~CGuiImpl()
{
  //�ͷ����ù������
  CGuiSettings* guiSettings = CGuiSettings::GetGuiSettings();
  if (guiSettings)
  {
    guiSettings->Delete();
  }
  //�ͷŲ���Ȩ�޹������
  CGuiOperationRight::Delete();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

void UeGui::CGuiImpl::Timer()
{
  CAggHook* aggHook = (CAggHook *)m_view->GetHook(CViewHook::m_curHookType);
  if (aggHook)
  {
    aggHook->Timer();
  }
}

/**
*
*/
void CGuiImpl::Update(short type, void *para)
{
  CMapHook *mapHook = (CMapHook *)(m_view->GetHook(CViewHook::DHT_MapHook));
  switch(type)
  {
  case CViewHook::UHT_SwitchTo2D:
    {
      mapHook->SwitchState(false);
    }
    break;
  case CViewHook::UHT_SwitchTo3D:
    {
      mapHook->SwitchState(true);
    }
    break;
  case CViewHook::UHT_FillGpsInfo:
    {
      //mapHook->FillGpsInfo();
    }
    break;
  case CViewHook::UHT_ForRealGuidance:
    {
      mapHook->MoveToRealGuidanceGUI();
    }
    break;
  case CViewHook::UHT_ForDemoGuidance:
    {
      mapHook->MoveToDemoGuidanceGUI();
    }
    break;
  case CViewHook::UHT_FillGuidanceInfo:
    {
      mapHook->FillGuidanceInfo();
    }
    break;
  case CViewHook::UHT_UpdateGPSHook:
    {
      ((CGpsHook*)(m_view->GetHook(CViewHook::DHT_GPSHook)))->Update();
    }
    break;
  case CViewHook::UHT_UpdateMapHook:
    {
      ((CMapHook*)(m_view->GetHook(CViewHook::DHT_MapHook)))->MoveToFullGui();
    }
    break;
  case CViewHook::UHT_SplitMapHook:
    {
      ((CMapHook*)(m_view->GetHook(CViewHook::DHT_MapHook)))->MoveToSplitGui();
    }
    break;
  case CViewHook::UHT_UpdateCountDown:
    {
      ((CMapHook*)(m_view->GetHook(CViewHook::DHT_MapHook)))->UpdateCountDown();
    }
    break;
  case CViewHook::UHT_UpdateKeyboardHook:
    {
      int curTime = ::GetTickCount();
#if __FOR_FPC__
      ((CKeyboardHook *)m_view->GetHook(CViewHook::DHT_KeyboardHook))->DoCursorRendering(curTime);
#endif
      //hnc?????????
      //((CKeyboardHook *)m_view->GetHook(CViewHook::DHT_KeyboardHook))->DoHandWriting(curTime);
      ((CInputHandHook *)m_view->GetHook(CViewHook::m_curHookType))->DoHandWriting(curTime);
    }
    break;
  case CViewHook::UHT_UpdateLocationMapHook:
    {
      mapHook->RefershLocationInfo();
    }
    break;
  case CViewHook::UHT_ForBlockCmd:
    {
      //GuidanceIndicator *curIndicator = (GuidanceIndicator *)para;
      //CGeoPoint<long> curPos;
      //curPos.m_x = curIndicator->m_vtxs[0].m_x;
      //curPos.m_y = curIndicator->m_vtxs[0].m_y;
      ////Mario
      ///*CViewHook::m_curHookType = CViewHook::DHT_MessageHook;
      //CViewHook::m_prevHookType = CViewHook::DHT_MapHook;*/
      //CViewHook::m_curHookType = CViewHook::DHT_MapHook;
      //CViewHook::SkipToHook(CViewHook::DHT_MessageHook);
      //((CMessageHook *)m_view->GetHook(CViewHook::DHT_MessageHook))->SetPosition(curPos);
      //((CMessageHook *)m_view->GetHook(CViewHook::DHT_MessageHook))->SetBlockedLink(curIndicator->m_parcelIdx, curIndicator->m_linkIdx);
      //((CMessageHook *)m_view->GetHook(CViewHook::DHT_MessageHook))->AsDecisionBox(CMessageHook::DT_Block, CViewHook::DHT_MapHook, CViewHook::DHT_MainMenuHook);
    }
    break;
#if __FOR_FPC__
  case CViewHook::UHT_UpdatePickPos:
    {
      ((CCapHook *)m_view->GetHook(CViewHook::DHT_CapHook))->UpdatePickPos();
    }
    break;
#endif
  default:
    {
      assert(false);
    }
    break;
  }
}

/**
*
**/
bool CGuiImpl::IsReadyForPlanning()
{
  if (CViewHook::m_curHookType == CViewHook::DHT_MapHook)
  {
    CMapHook *mapHook = ((CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook));
    if (mapHook)
    {
      return mapHook->IsReadyForPlanning();
    }
    
  }
  return false;
}

inline bool CGuiImpl::GetDistrictName(const CGeoPoint<long> &pos, char *distName)
{
	unsigned int distIdx = CCodeIndexCtrl::GetDistCode(pos.m_x, pos.m_y);
	return CCodeIndexCtrl::GetDistCodeCtrl().GetItemNameByCode(distIdx,distName);
}

inline bool CGuiImpl::IsCountDown()
{
  CMapHook *mapHook = ((CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook));
  return mapHook->IsCountDown();
}

inline void CGuiImpl::DoRouteGuidance()
{
  CMapHook *mapHook = ((CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook));
  if(mapHook != NULL)
  {
    mapHook->DoRouteGuidance();
  }
}

/**
*
**/
bool CGuiImpl::IsMsgBox()
{
  return  /*(CViewHook::m_curHookType == CViewHook::DHT_MessageHook && CMessageHook::m_msgHookType == CMessageHook::MB_Info)
    ||*/(CViewHook::m_curHookType == CViewHook::DHT_DetailMessageHook);
}

/**
*
**/
bool CGuiImpl::IsRecBox()
{
  return false;/*CViewHook::m_curHookType == CViewHook::DHT_MessageHook &&
    CMessageHook::m_msgHookType == CMessageHook::MB_Record;*/
}

bool CGuiImpl::IsMapHook()
{
  return CViewHook::m_curHookType == CViewHook::DHT_MapHook;
}

#if __FOR_FPC__
/**
* 
*/
bool CGuiImpl::IsFPC()
{
  CMainMenuHook *mainMenuHook = (CMainMenuHook *)(m_view->GetHook(CViewHook::DHT_MainMenuHook));
  assert(mainMenuHook);

  return mainMenuHook->m_isFPC;
}

/**
* 
*/
void CGuiImpl::SetCapScale(int scale)
{
  CCapHook* capHook = (CCapHook *)(m_view->GetHook(CViewHook::DHT_CapHook));
  capHook->SetScaleName(scale);
  assert(capHook);
}
#endif

/*!
*
**/
const ViewSettings &CGuiImpl::GetMapSettings()
{
  CSettingWrapper &settingWraper = CSettingWrapper::Get();
  assert(ueSettings);
  return settingWraper.GetViewSettings();
}

void UeGui::CGuiImpl::SetHooksPath( TCHAR* path )
{
  CAggHook::SetPath(path);
}


void UeGui::CGuiImpl::MakeProductActivationHook()
{
  //��Ʒ����     
  IView *view = m_view = IView::GetView();
  CViewHook *viewHook = new CProduceActivationHook();  
  viewHook->SetHelpers(NULL, view, NULL, NULL, NULL);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_ProduceActivationHook, viewHook);

  //ͨ�öԻ���
  viewHook = new CMessageDialogHook();
  viewHook->SetHelpers(NULL, view, NULL, NULL, NULL);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MessageDialogeHook,viewHook);

  CViewHook::m_curHookType = CViewHook::DHT_ProduceActivationHook;
}

/*!
*
**/
void CGuiImpl::MakeHooks()
{
  TIME_STAT;
  // Which is beginning hook
  // Get helpers for convinient usage
  IRoadNetwork *net = IRoadNetwork::GetNetwork();
  assert(net);

  IView *view = m_view = IView::GetView();
  assert(view);
  CViewHook::m_hookExtent = view->GetScrLayout().m_extent;

  IRoute *route = IRoute::GetRoute();
  assert(route);

  IMapMatch *gps = IMapMatch::GetMapMatch();
  assert(gps);

  IQuery *query = IQuery::GetQuery();
  assert(query);

  // Initialize hooks
  CViewHook *viewHook = NULL;

#if __FOR_PC__
  CViewHook::m_curHookType = CViewHook::DHT_MapHook;
#else
  //Ĭ�Ͽ�����������
  bool isShowLicenseHook = true;
  CGuiSettings* ueSettings = CGuiSettings::GetGuiSettings();
  if (ueSettings)
  {
    if (UeBase::OS_OFF == ueSettings->GetIsOpenStartStatement())
    {
      isShowLicenseHook= false;
    }
  }
  if (isShowLicenseHook)
  {
    CViewHook::m_curHookType = CViewHook::DHT_LicenseHook;
    //���ѡ��������������أ����򲻼���
    viewHook = new CLicenseHook();
    viewHook->SetHelpers(net, view, route, gps, query);
    viewHook->LoadGUI();
    view->AddHook(CViewHook::DHT_LicenseHook, viewHook);
  }
  else
  {
    CViewHook::m_curHookType = CViewHook::DHT_MapHook;
  }
#endif

  //��ͼ����
  viewHook = new CMapHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_MapHook, viewHook);
  //����ѡ�����
  viewHook = new CDistrictSelectionHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_DistrictSelectionHook, viewHook);
  //����ѡ�����
  viewHook = new CTypeInDistSelectionHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_TypeInDistSelectionHook, viewHook);
  //���˵�����
  viewHook = new CMainMenuHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_MainMenuHook, viewHook);

  //·�߲�����·��ѡ�����
  viewHook = new CRouteTypeSwitchHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_RouteTypeSwitchHook, viewHook);

  //��ݲ���
  viewHook = new CFastOperationHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_FastOperationHook, viewHook);

  //���õ�
  viewHook = new CUsuallyHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_UsuallyHook, viewHook);
  ////��Hook��Ҫ�Ƴ���
  ////��ַ��&��ʷ��¼���ƽ���
  //viewHook = new CFavorHook();
  //viewHook->SetHelpers(net, view, route, gps, query);
  //viewHook->LoadGUI();  
  //view->AddHook(CViewHook::DHT_FavorHook, viewHook);

  //ˢ�½�����
  view->UpdateProgress();

  //���ǽ���
  viewHook = new CGpsHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_GPSHook, viewHook);

  ////��Hook��Ҫ�Ƴ���
  //viewHook = new CSettingHook();
  //viewHook->SetHelpers(net, view, route, gps, query);
  //viewHook->LoadGUI();  
  //view->AddHook(CViewHook::DHT_SettingHook, viewHook);

  //�������ý�����ĵ�ͼ��ʾ����
  //viewHook = new CMapSettingHook();
  //viewHook->SetHelpers(net, view, route, gps, query);
  //viewHook->LoadGUI();  
  //view->AddHook(CViewHook::DHT_MapSettingHook, viewHook);

  //�ҵ���Ϣ����
  viewHook = new CUserInfoHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_UserInfoHook, viewHook);

  //�������ý���
  viewHook = new CNaviSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_NaviSettingHook, viewHook);
  
  //�������ý������·�ڷŴ�ͼ����
  viewHook = new CCrossPicSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  //�л�����ʱ�ٶ�̬����
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_CrossPicSettingHook, viewHook);

  //�������ý�����ĵ����۽���
  viewHook = new CEEyeSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_EEyeSettingHook, viewHook);

  //�������ý��������ʾ���ý���
  viewHook = new CPromptSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_PromptSettingHook, viewHook);

  //�������ý�����İ�ȫ���ý���
  viewHook = new CSafetySettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_SafetySettingHook, viewHook);
  
  //�������ý������·�����ý���
  viewHook = new CRouteSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);  
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_RouteSettingHook, viewHook);

  //�������ý�����Ĺ켣���ý���
  viewHook = new CTrackSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_TrackSettingHook, viewHook);

  ////��Hook��Ҫ�Ƴ���
  //viewHook = new CQuerySettingHook();
  //viewHook->SetHelpers(net, view, route, gps, query);
  //viewHook->LoadGUI();  
  //view->AddHook(CViewHook::DHT_QuerySettingHook, viewHook);

  //ˢ�½�����
  view->UpdateProgress();

  //ϵͳ���ý�������������ý���
  viewHook = new CVoiceSettingHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_VoiceSettingHook, viewHook);

  ////��Hook��Ҫ�Ƴ���
  //viewHook = new CQueryCrossHook();
  //viewHook->SetHelpers(net, view, route, gps, query);
  //viewHook->LoadGUI();  
  //view->AddHook(CViewHook::DHT_QueryCrossHook, viewHook);
  
  //ϵͳ���ý���
  viewHook = new CSystemSettingHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_SystemSettingHook,viewHook);

  //ϵͳ���ý�������Գ�ͼ�����
  viewHook = new CCarSettingHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_CarSettingHook,viewHook);

  //ϵͳ���ý������ʱ��У׼����
  viewHook = new CTimeSettingHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_TimeSettingHook,viewHook);

  //ϵͳ���ý������������������
  viewHook = new CDeclareSettingHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_DeclareSettingHook,viewHook);

  //ϵͳ���ý�����İ汾��Ϣ����
  viewHook = new CEditionHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_EditionHook,viewHook);

  //��ͼ����(maphook)��������Ϣ(����������鰴ť�����)
  viewHook = new CDetailMessageHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_DetailMessageHook, viewHook);

  //������Ϣ�����ı༭��Ϣ(������水ť�����)
  viewHook = new CDetailEditHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_DetailEditHook, viewHook);

  //ˢ�½�����
  view->UpdateProgress();

  //maphook����mainmenu�����·�߲�������
  viewHook = new CRouteOperationHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_RouteOperationHook,viewHook);

  //·�߲��������еľ�����·
  viewHook = new CPassedRouteHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();  
  view->AddHook(CViewHook::DHT_PassedRouteHook,viewHook);

  //·�߲��������еĵ���·��
  viewHook = new CAdjustRouteHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_AdjustRouteHook,viewHook);

  //·������ѡ��
  viewHook = new CRouteTypeSelectHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_RouteTypeSelectHook,viewHook);

  //�����ƶ�ѡ��
  viewHook = new CUpwardOrDownwardHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_UpwardOrDownwardHook,viewHook);

  //����ͨ�����ѯ��4S�� �����ѯ��
  viewHook = new CDdtServiceQueryListHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_DdtServiceQueryListHook, viewHook);

  //ͨ�öԻ���
  viewHook = new CMessageDialogHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MessageDialogeHook,viewHook);

  //��������
  viewHook = new COperationHelpHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_OperationHelpHook,viewHook);

  //��ͼ�������
  viewHook = new CMapScanHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MapScanHook,viewHook);

  //��ͼ��������
  viewHook = new CMapNavigationHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MapNavigationHook,viewHook);

  //�������ܰ���
  viewHook = new CBasicFunctionHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_BasicFunctionHook,viewHook);

  //����ͨ�������
  viewHook = new CDdtServiceHelpHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_DdtServiceHelpHook,viewHook);

  //�������ְ���
  viewHook = new CFastHandleHelpHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_FastHandleHelpHook,viewHook);

  //3D��ʾ����
  viewHook = new CDemonstration3DHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_Demonstration3DHook,viewHook);

  //3D������ʾ����
  viewHook = new CCity3DHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_City3DHook,viewHook);

  //ˢ�½�����
  view->UpdateProgress();

  viewHook = new CQueryMenuHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_QueryMenuHook,viewHook);

  viewHook = new CInputSwitchHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_InputSwitchHook,viewHook);

  viewHook = new CInputSpellingHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_InputSpellingHook,viewHook);

  viewHook = new CInputCharHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_InputCharHook,viewHook);

  viewHook = new CInputAcronymHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_InputAcronymHook,viewHook);

  viewHook = new CInputHandHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_InputHandHook,viewHook);

  viewHook = new CPoiQueryListHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_PoiQueryListHook,viewHook);

  viewHook = new CRoadQueryListHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_RoadQueryListHook,viewHook);

  viewHook = new CCrossQueryListHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_CrossQueryListHook,viewHook);

  viewHook = new CDistQueryListHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_DistQueryListHook,viewHook);

  viewHook = new CTypeInDistQueryListHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_TypeInDistQueryListHook,viewHook);

  //��ַ��
  viewHook = new CMyAddressBookHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MyAddressBookHook,viewHook);

  //�ҵ���Ϣ
  viewHook = new CMyInformationHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MyInformationHook,viewHook);

  //������Ϣ
  viewHook = new CCapacityInformationHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_CapacityInformationHook,viewHook);


  //�ҵ��г�
  viewHook = new CMyJourneyHook();
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MyJourneyHook,viewHook);

  //��ʷ��Ϣ
  viewHook = new CHistoryInformationHook();  
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_HistoryInformationHook,viewHook);

  //�༭��־
  viewHook = new CMarkerEditHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_MarkerEditHook,viewHook);

  //��������
  viewHook = new CDdtUpdateServiceHook();  
  viewHook->SetHelpers(net, view, route, gps, query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_DdtUpdateServiceHook,viewHook);

  //�˿�����
  viewHook = new CCOMPortSettingHook();  
  viewHook->SetHelpers(net, view, route, gps, query);
  //�л�����ʱ�ٶ�̬����
  //viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_COMPortSettingHook,viewHook);

  //����ѡ��Ի���
  viewHook = new CNavigationSelectionHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_NavigationSelectionHook, viewHook);

  //·�ڷŴ�ͼ����
  viewHook = new CGuidanceViewHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_GuidanceViewHook, viewHook);

  //��ʼ������
  viewHook = new CRestoreDefaultshook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_RestoreDefaultshook, viewHook);

#if __FOR_TRUCK__
  //��������
  viewHook = new CTruckMainMenuHook();  
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_TruckMainMenuHook,viewHook);

  //������Ϣ
  viewHook=new CCarInfoHook;
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_VehicleInformationHook,viewHook);
  //��Դ����
  viewHook=new CGoodsSourceHook;
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_ViewSupplyHook,viewHook);
  //��������
  viewHook=new CGoodsDetailsHook;
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_GoodsDetailsHook,viewHook);
  //��������
  viewHook=new CLogisticsTrackHook;
  viewHook->SetHelpers(net,view,route,gps,query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_LogisticsTrackingHook,viewHook);

  //���ӹ���
  viewHook = new CFleetManagementhook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_FleetManagementHook, viewHook);

  //�����б�
  viewHook = new Cteammemberlisthook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_TeamMemberListHook, viewHook);
#endif

#if __FOR_FPC__
  viewHook = new CCapHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_CapHook, viewHook);

  viewHook = new CPOIPropertyHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_POIPropertyHook, viewHook);

  viewHook = new CTrafficPropertyHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_TrafficPropertyHook, viewHook);

  viewHook = new CTrackPropertyHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_TrackPropertyHook, viewHook);

  viewHook = new CBusPropertyHook();
  viewHook->SetHelpers(net, view, route, gps, query);
  viewHook->LoadGUI();
  view->AddHook(CViewHook::DHT_BusPropertyHook, viewHook);
#endif
  //ˢ�½�����
  view->UpdateProgress();
}

/*!
*
**/
void CGuiImpl::RenderHook(const CGeoRect<short> &scrExtent)
{
  CAggHook *curHook = (CAggHook *)(m_view->GetHook(CViewHook::m_curHookType));
  assert(curHook);

  if(curHook)
  {
    curHook->DoDraw(scrExtent);
  }
}

void UeGui::CGuiImpl::RenderSubViewHooks( const CGeoRect<short> &scrExtent )
{
  //���ݵ�ǰ������ʾ�������ж�Ҫ�������ĸ�����
  //unsigned int viewType = 
  CAggHook *curHook = (CAggHook *)(m_view->GetHook(CViewHook::DHT_GuidanceViewHook));
  if(curHook)
  {
    curHook->DoDraw(scrExtent);
  }
}

void CGuiImpl::RenderLogonHook( const CGeoRect<short> &scrExtent, short step )
{
  CLogonHook* logonHook = CLogonHook::GetLogonHook();
  if(logonHook)
  {
    if (!logonHook->GuiElementsLoadDone())
    {
      logonHook->MakeGUI();
    }
    logonHook->SetProgress(step);
    logonHook->DoDraw(scrExtent);
  }
}

void CGuiImpl::SetMaxLogonProgress( unsigned short maxProgress)
{
  CLogonHook* logonHook = CLogonHook::GetLogonHook();  
  if(logonHook)
  {
    logonHook->SetMaxProgress(maxProgress);
  }
}

void UeGui::CGuiImpl::UpdateMessageDialogeHook( short type, void *para )
{
  CMessageDialogHook *messageDialogHook = (CMessageDialogHook *)(m_view->GetHook(CViewHook::DHT_MessageDialogeHook));
  if ((messageDialogHook) && (messageDialogHook->NeedCountDown()))
  {
    messageDialogHook->UpdateCountDown();
  }
}

unsigned char UeGui::CGuiImpl::GetMultiMethodType()
{
  CMapHook *mapHook = ((CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook));
  if (mapHook)
  {
    return mapHook->GetMultiMethodType();
  }
  return false;
}

bool UeGui::CGuiImpl::IsShowCompass()
{
  CMapHook *mapHook = ((CMapHook*)m_view->GetHook(CViewHook::DHT_MapHook));
  if (mapHook)
  {
    return mapHook->IsShowCompass();
  }
  return false;
}
