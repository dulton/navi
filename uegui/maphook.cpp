/*
*
*/
#include "gui.h"
#include "maphook.h"
#include "viewwrapper.h"
#include "routewrapper.h"
#include "userdatawrapper.h"
#include "viewwrapper.h"
#include "settingwrapper.h"
#include "messagedialoghook.h"
#include "inputswitchhook.h"
#include "ueroute\routebasic.h"

using namespace UeGui;
//
#define RENDERCAMERABTN 1
#define IS_SCROLL_ON   0

/////////////////////////////////////////////////////////////////////////////////////////////

UeGui::CMapHook::CMapHook() : CAggHook(), m_viewWrapper(CViewWrapper::Get()), m_routeWrapper(CRouteWrapper::Get()),
m_settingWrapper(CSettingWrapper::Get()), m_userDataWrapper(CUserDataWrapper::Get()), m_selectPointObj(NULL), 
m_selectPointEvent(NULL), m_curGuiType(GUI_None), m_preGuiType(GUI_None), m_queryPointIndex(-1), m_planType(Plan_Single),
m_guiTimerInterval(0), m_curPlanmethodType(UeRoute::MT_Max)
{
  m_queryPointList.clear();
  //��ͼ������Ⱦ��ɺ���Ҫ�ͷ�ͼƬ��Դ�����Ч��
  m_needReleasePic = false;
}

UeGui::CMapHook::~CMapHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

bool UeGui::CMapHook::operator()()
{
  return false;
}

void UeGui::CMapHook::DoDraw( const CGeoRect<short> &scrExtent )
{
  //���û�����Ⱦ
  CAggHook::DoDraw(scrExtent);
}

void UeGui::CMapHook::Init()
{
  RefreshSetPointStatus();
  RefreshZoomingInfo();
}

void UeGui::CMapHook::MakeGUI()
{
  //���ø���ӿ�
  CAggHook::MakeGUI();
  //�ǵ�������ʵ����ʱ�˵�
  m_mapMainMenu.MakeGUI();
  m_mapMainMenu.ExpandMenu(false);
  m_mapMainMenu.Show(false);
  m_mapMainMenu.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapMainMenuHook, &m_mapMainMenu);
  //ģ�⵼��ʱ�˵�
  m_mapSimulationMenu.MakeGUI();
  m_mapSimulationMenu.Show(false);
  m_mapSimulationMenu.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapSimulationMenuHook, &m_mapSimulationMenu);
  //·�߼�����ɺ�˵�
  m_mapRouteCalcMenu.MakeGUI();
  m_mapRouteCalcMenu.Show(false);
  m_mapRouteCalcMenu.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapRouteCalcMenuHook, &m_mapRouteCalcMenu);
  //����·�߲˵�
  m_mapOverViewMenu.MakeGUI();
  m_mapOverViewMenu.Show(false);
  m_mapOverViewMenu.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapOverViewMenuHook, &m_mapOverViewMenu);
  //������ͼ�˵�����һ��·�����򿴰塢���̵Ƶ�
  m_mapGuideInfoView.MakeGUI();
  m_mapGuideInfoView.Show(false);
  m_mapGuideInfoView.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapGuideViewMenuHook, &m_mapGuideInfoView);
  //��ѯʱ�˵�
  m_mapQueryMenu.MakeGUI();
  m_mapQueryMenu.Show(false);
  m_mapQueryMenu.SetParentHook(this);
  AddChildHook(CViewHook::DHT_MapQueryViewMenuHook, &m_mapQueryMenu);

  //��ʼ����ͼģʽΪ����״̬
  m_viewWrapper.SetViewOpeMode(VM_Guidance);
  //��ʼ���˵�
  SwitchingGUI(GUI_MapBrowse);
}

tstring UeGui::CMapHook::GetBinaryFileName()
{
  return _T("maphook.bin");
}

void UeGui::CMapHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(MapHook_MiniMizeBack,	"MiniMizeBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_MiniMizeIcon,	"MiniMizeIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_AddElecEyeBack,	"AddElecEyeBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_AddElecEyeIcon,	"AddElecEyeIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_MapAzimuthBack,	"MapAzimuthBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_NorthIcon,	"NorthIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_HeadingIcon,	"HeadingIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_PerspectiveIcon,	"PerspectiveIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_CompassBack,	"CompassBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_CompassIcon,	"CompassIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ZoomInBack,	"ZoomInBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ZoomInIcon,	"ZoomInIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ZoomOutBack,	"ZoomOutBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ZoomOutIcon,	"ZoomOutIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ScaleBack,	"ScaleBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ScaleLabel,	"ScaleLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SoundBack,	"SoundBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SoundIcon,	"SoundIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSBack,	"GPSBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon,	"GPSIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon0,	"GPSIcon0"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon1,	"GPSIcon1"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon2,	"GPSIcon2"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon4,	"GPSIcon4"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon3,	"GPSIcon3"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon5,	"GPSIcon5"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon6,	"GPSIcon6"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon7,	"GPSIcon7"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon8,	"GPSIcon8"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon9,	"GPSIcon9"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon10,	"GPSIcon10"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon11,	"GPSIcon11"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GPSIcon12,	"GPSIcon12"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_ScreenMoadlBack,	"ScreenMoadlBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SingleScreenIcon,	"SingleScreenIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DoubleScreenIcon,	"DoubleScreenIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetStartBack,	"SetStartBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetStartIcon,	"SetStartIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetStartLabel,	"SetStartLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetWayBack,	"SetWayBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetWayIcon,	"SetWayIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetWayLabel,	"SetWayLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetEndBack,	"SetEndBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetEndIcon,	"SetEndIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_SetEndLabel,	"SetEndLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_FixedPostionBack,	"FixedPostionBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_FixedPostionIcon,	"FixedPostionIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_FixedPostionLabel,	"FixedPostionLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_TimerLabel,	"TimerLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailBack1,	"DetailBack1"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailIcon1,	"DetailIcon1"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailLabe1,	"DetailLabe1"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailBack2,	"DetailBack2"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailIcon2,	"DetailIcon2"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_DetailLabe2,	"DetailLabe2"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoLeftBack,	"GuideInfoLeftBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoLeftIcon,	"GuideInfoLeftIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoLeftLabe,	"GuideInfoLeftLabe"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_Delimiter1,	"Delimiter1"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoCenterBack,	"GuideInfoCenterBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoCenterIcon,	"GuideInfoCenterIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoCenterLabe,	"GuideInfoCenterLabe"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_Delimiter2,	"Delimiter2"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoRightBack,	"GuideInfoRightBack"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoRightIcon,	"GuideInfoRightIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_GuideInfoRightLabe,	"GuideInfoRightLabe"));
  m_ctrlNames.insert(GuiName::value_type(MapHook_OtherIcon,	"OtherIcon"));
}

void UeGui::CMapHook::MakeControls()
{
  m_miniMizeBtn.SetCenterElement(GetGuiElement(MapHook_MiniMizeBack));
  m_miniMizeBtn.SetIconElement(GetGuiElement(MapHook_MiniMizeIcon));
  m_addElecEyeBtn.SetCenterElement(GetGuiElement(MapHook_AddElecEyeBack));
  m_addElecEyeBtn.SetIconElement(GetGuiElement(MapHook_AddElecEyeIcon));
  m_mapAzimuthBtn.SetCenterElement(GetGuiElement(MapHook_MapAzimuthBack));
  m_mapAzimuthBtn.SetIconElement(GetGuiElement(MapHook_NorthIcon));
  m_zoomInBtn.SetCenterElement(GetGuiElement(MapHook_ZoomInBack));
  m_zoomInBtn.SetIconElement(GetGuiElement(MapHook_ZoomInIcon));
  m_zoomOutBtn.SetCenterElement(GetGuiElement(MapHook_ZoomOutBack));
  m_zoomOutBtn.SetIconElement(GetGuiElement(MapHook_ZoomOutIcon));
  m_scaleBtn.SetCenterElement(GetGuiElement(MapHook_ScaleBack));
  m_scaleBtn.SetLabelElement(GetGuiElement(MapHook_ScaleLabel));
  m_soundBtn.SetCenterElement(GetGuiElement(MapHook_SoundBack));
  m_soundBtn.SetIconElement(GetGuiElement(MapHook_SoundIcon));
  m_GPSBtn.SetCenterElement(GetGuiElement(MapHook_GPSBack));
  m_GPSBtn.SetIconElement(GetGuiElement(MapHook_GPSIcon));
  m_screenMoadlBtn.SetCenterElement(GetGuiElement(MapHook_ScreenMoadlBack));
  m_screenMoadlBtn.SetIconElement(GetGuiElement(MapHook_SingleScreenIcon));
  m_setStartBtn.SetCenterElement(GetGuiElement(MapHook_SetStartBack));
  m_setStartBtn.SetIconElement(GetGuiElement(MapHook_SetStartIcon));
  m_setStartBtn.SetLabelElement(GetGuiElement(MapHook_SetStartLabel));
  m_setEndBtn.SetCenterElement(GetGuiElement(MapHook_SetEndBack));
  m_setEndBtn.SetIconElement(GetGuiElement(MapHook_SetEndIcon));
  m_setEndBtn.SetLabelElement(GetGuiElement(MapHook_SetEndLabel));
  m_setWayBtn.SetCenterElement(GetGuiElement(MapHook_SetWayBack));
  m_setWayBtn.SetIconElement(GetGuiElement(MapHook_SetWayIcon));
  m_setWayBtn.SetLabelElement(GetGuiElement(MapHook_SetWayLabel));
  m_fixedPostionBtn.SetCenterElement(GetGuiElement(MapHook_FixedPostionBack));
  m_fixedPostionBtn.SetIconElement(GetGuiElement(MapHook_FixedPostionIcon));
  m_fixedPostionBtn.SetLabelElement(GetGuiElement(MapHook_FixedPostionLabel));
  //ϵͳʱ��
  m_timerBtn.SetCenterElement(GetGuiElement(MapHook_TimerLabel));
  //ָ����
  m_compassIcon.SetCenterElement(GetGuiElement(MapHook_CompassBack));  
  m_compassIcon.SetIconElement(GetGuiElement(MapHook_CompassIcon));
  //����
  m_detailBtn1.SetCenterElement(GetGuiElement(MapHook_DetailBack1));
  m_detailBtn1.SetIconElement(GetGuiElement(MapHook_DetailIcon1));
  m_detailBtn1.SetLabelElement(GetGuiElement(MapHook_DetailLabe1));
  m_detailBtn2.SetCenterElement(GetGuiElement(MapHook_DetailBack2));
  m_detailBtn2.SetIconElement(GetGuiElement(MapHook_DetailIcon2));
  m_detailBtn2.SetLabelElement(GetGuiElement(MapHook_DetailLabe2));
  //����
  m_guideInfoLeftBtn.SetCenterElement(GetGuiElement(MapHook_GuideInfoLeftBack));
  m_guideInfoLeftBtn.SetIconElement(GetGuiElement(MapHook_GuideInfoLeftIcon));
  m_guideInfoLeftBtn.SetLabelElement(GetGuiElement(MapHook_GuideInfoLeftLabe));
  m_guideInfoCenterBtn.SetCenterElement(GetGuiElement(MapHook_GuideInfoCenterBack));
  m_guideInfoCenterBtn.SetIconElement(GetGuiElement(MapHook_GuideInfoCenterIcon));
  m_guideInfoCenterBtn.SetLabelElement(GetGuiElement(MapHook_GuideInfoCenterLabe));
  m_guideInfoRightBtn.SetCenterElement(GetGuiElement(MapHook_GuideInfoRightBack));
  m_guideInfoRightBtn.SetIconElement(GetGuiElement(MapHook_GuideInfoRightIcon));
  m_guideInfoRightBtn.SetLabelElement(GetGuiElement(MapHook_GuideInfoRightLabe));
  //�ָ��
  m_delimiter1.SetCenterElement(GetGuiElement(MapHook_Delimiter1));
  m_delimiter2.SetCenterElement(GetGuiElement(MapHook_Delimiter2));

  //����ָ����ͼ��
  CViewHook::GuiElement* guiElement = m_compassIcon.GetCenterElement();
  if (guiElement)
  {
    CGeoPoint<short> scrPoint;
    scrPoint.m_x = guiElement->m_startX + guiElement->m_width/2;
    scrPoint.m_y = guiElement->m_startY + guiElement->m_height/2;
    //����ָ������ʾͼ��
    m_viewWrapper.AddViewIcon(VI_COMPASSICON, guiElement->m_bkNormal);
  }
  guiElement = m_compassIcon.GetIconElement();
  if (guiElement)
  {    
    m_viewWrapper.AddViewIcon(VI_COMPASSINDICATORICON, guiElement->m_bkNormal);
  }

  guiElement = GetGuiElement(MapHook_OtherIcon);
  if (guiElement)
  {
    //����·������ͼ��
    m_viewWrapper.AddViewIcon(VI_BUBBLEICON, guiElement->m_bkNormal);
    //3D�������ͼƬ
    m_viewWrapper.AddViewIcon(VI_SKY_DAY_ICON, guiElement->m_bkFocus);
    //3Dҹ�����ͼƬ
    m_viewWrapper.AddViewIcon(VI_SKY_NIGHT_ICON, guiElement->m_bkDisabled);
  }
}

void UeGui::CMapHook::Timer()
{
  //���涨ʱ�л�
  if (m_guiTimerInterval > 0)
  {
    --m_guiTimerInterval;
    if (0 == m_guiTimerInterval)
    {
      if (UpdateMenu(MUT_Close))
      {
        Refresh();
      }      
    }
  }
  //// ˢ�µ�ǰʱ��
  //if(m_gps->IsLive())
  //{
  //  GpsBasic pos;
  //  m_gps->GetPos(pos, false);
  //  m_mapStatusBarHook.RefreshTime(pos.m_localTime.m_hour, pos.m_localTime.m_min);
  //}
  //else
  //{
  //  CTimeBasic::TimeReport report;
  //  CTimeBasic timer;
  //  timer.GetNow(report);
  //  m_mapStatusBarHook.RefreshTime(report.m_hour, report.m_minute);
  //}
}

void UeGui::CMapHook::Load()
{

}

void UeGui::CMapHook::UnLoad()
{

}

void UeGui::CMapHook::SwitchingGUI( GUIType guiType )
{
  //���浱ǰ�л��Ľ�������
  m_preGuiType = m_curGuiType;
  m_curGuiType = guiType;
  //���ݽ���������ʾ�˵�
  switch (guiType)
  {
  case GUI_MapBrowse:
    {
      m_mapMainMenu.Show();
      m_mapSimulationMenu.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      m_mapQueryMenu.Show(false);
      break;
    }
  case GUI_RouteCalculate:
    {
      m_mapRouteCalcMenu.Show();      
      m_mapMainMenu.Show(false);
      m_mapSimulationMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      m_mapQueryMenu.Show(false);
      CloseGuiTimer();
      break;
    }
  case GUI_DemoGuidance:
    {
      m_mapSimulationMenu.Show();
      m_mapGuideInfoView.Show();
      m_mapMainMenu.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapQueryMenu.Show(false);
      break;
    }
  case GUI_RealGuidance:
    {
      m_mapMainMenu.Show();
      m_mapGuideInfoView.Show();
      m_mapRouteCalcMenu.Show(false);
      m_mapSimulationMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapQueryMenu.Show(false);
      break;
    }
  case GUI_OverviewRoute:
    {
      m_mapOverViewMenu.Show();
      m_mapMainMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapSimulationMenu.Show(false);      
      m_mapQueryMenu.Show(false);
      CloseGuiTimer();
      break;
    }
  case GUI_QueryPoint:
    {
      m_mapQueryMenu.SetMenuType(CMapQueryMenuHook::QMenu_QueryPoint);
      m_mapQueryMenu.Show();
      m_mapMainMenu.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapSimulationMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      break;
    }
  case GUI_SelectPoint:
    {
      m_mapQueryMenu.SetMenuType(CMapQueryMenuHook::QMenu_SelectPoint);
      m_mapQueryMenu.Show();
      m_mapMainMenu.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapSimulationMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      CloseGuiTimer();
      break;
    }
  case GUI_SelectArea:
    {
      m_mapQueryMenu.SetMenuType(CMapQueryMenuHook::QMenu_SelectArea);
      m_mapQueryMenu.Show();
      m_mapMainMenu.Show(false);
      m_mapRouteCalcMenu.Show(false);
      m_mapSimulationMenu.Show(false);
      m_mapOverViewMenu.Show(false);
      m_mapGuideInfoView.Show(false);
      CloseGuiTimer();
      break;
    }
  }
}

void UeGui::CMapHook::ReturnToPrevGUI()
{
  SwitchingGUI(m_preGuiType);
}

bool UeGui::CMapHook::UpdateMenu( MenuUpdateType updateType /*= MUT_Normal*/ )
{
  bool rt = false;
  switch (updateType)
  {
  case MUT_Normal:
    {
      if (m_mapMainMenu.IsShown())
      {
        m_mapMainMenu.Update();
        rt = true;
      }
      if (m_mapSimulationMenu.IsShown())
      {
        m_mapSimulationMenu.Update();
        rt = true;
      }
      if (m_mapGuideInfoView.IsShown())
      {
        m_mapGuideInfoView.Update();
        rt = true;
      }      
      break;
    }
  case MUT_Expand:
    {
      if (m_mapMainMenu.IsShown())
      {
        m_mapMainMenu.ExpandMenu();
        rt = true;
      }
      if (m_mapSimulationMenu.IsShown())
      {
        m_mapSimulationMenu.ExpandMenu();
        rt = true;
      }
      if (m_mapQueryMenu.IsShown())
      {
        m_mapQueryMenu.ExpandMenu();
        rt = true;
      }
      break;
    }
  case MUT_Close:
    {
      if (m_mapMainMenu.IsShown())
      {
        m_mapMainMenu.ExpandMenu(false);
        rt = true;
      }
      if (m_mapSimulationMenu.IsShown())
      {
        m_mapSimulationMenu.ExpandMenu(false);
        rt = true;
      }
      if (m_mapQueryMenu.IsShown())
      {
        m_mapQueryMenu.ExpandMenu(false);
        rt = true;
      }
      break;
    }
  }
  return rt;
}

void UeGui::CMapHook::MapTouch( CGeoPoint<short> &scrPoint )
{
  //�����ģ�⵼��״̬�����������ͼ
  short planState = m_routeWrapper.GetPlanState();
  if (UeRoute::PS_DemoGuidance == planState)
  {
    //չ���˵�
    if (UpdateMenu(MUT_Expand))
    {
      Refresh();
    }
    return;
  }
  //�����ǰ��ͼģʽΪ����״̬���л������״̬
  CViewState* curViewState = m_viewWrapper.GetMainViewState();
  if (curViewState)
  {
    UeMap::ViewOpeMode viewMode = m_viewWrapper.GetViewOpeMode((UeMap::ViewType)curViewState->GetType());
    if (UeMap::VM_Guidance == viewMode)                                    
    {
      //�л���ͼΪ�ɲ���״̬
      m_viewWrapper.SetViewOpeMode(VM_Browse);
      //�������ʵ�������棬���л������״̬
      if (GUI_RealGuidance == m_curGuiType)
      {    
        SwitchingGUI(GUI_MapBrowse);
      }
      //չ���˵�
      if (UpdateMenu(MUT_Expand))
      { 
        Refresh();
      }
    }
  }
  //��ͼѡ��
  CMemVector objects(sizeof(CViewCanvas::RenderedPrimitive), 10);
  m_viewWrapper.Pick(scrPoint, objects, true);
  RefreshLocationInfo();
}

short UeGui::CMapHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(m_downElementType)
  {
  case CT_Unknown:
    {
      return CT_Unknown;
    }
    break;
  case MapHook_MiniMizeBack:
  case MapHook_MiniMizeIcon:
    {
      m_miniMizeBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_AddElecEyeBack:
  case MapHook_AddElecEyeIcon:
    {
      m_addElecEyeBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_MapAzimuthBack:
  case MapHook_NorthIcon:
  case MapHook_PerspectiveIcon:
  case MapHook_HeadingIcon:
    {
      m_mapAzimuthBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_ZoomInBack:
  case MapHook_ZoomInIcon:
    {
      m_zoomInBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_ZoomOutBack:
  case MapHook_ZoomOutIcon:
    {
      m_zoomOutBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_ScaleBack:
  case MapHook_ScaleLabel:
    {
      m_scaleBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_SoundBack:
  case MapHook_SoundIcon:
    {
      m_soundBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_GPSBack:
  case MapHook_GPSIcon:
    {
      m_GPSBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_ScreenMoadlBack:
  case MapHook_SingleScreenIcon:
  case MapHook_DoubleScreenIcon:
    {
      m_screenMoadlBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_SetStartBack:
  case MapHook_SetStartIcon:
  case MapHook_SetStartLabel:
    {
      m_setStartBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_SetEndBack:
  case MapHook_SetEndIcon:
  case MapHook_SetEndLabel:
    {
      m_setEndBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_SetWayBack:
  case MapHook_SetWayIcon:
  case MapHook_SetWayLabel:
    {
      m_setWayBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_FixedPostionBack:
  case MapHook_FixedPostionIcon:
  case MapHook_FixedPostionLabel:
    {
      m_fixedPostionBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_DetailBack1:
  case MapHook_DetailIcon1:
  case MapHook_DetailLabe1:
    {
      m_detailBtn1.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_DetailBack2:
  case MapHook_DetailIcon2:
  case MapHook_DetailLabe2:
    {
      m_detailBtn2.MouseDown();
      needRefresh = true;
    }
    break;
  case MapHook_GuideInfoCenterBack:
  case MapHook_GuideInfoCenterIcon:
  case MapHook_GuideInfoCenterLabe:
    {
      m_guideInfoCenterBtn.MouseDown();
      needRefresh = true;
    }
    break;
  default:
    assert(false);
    break;
  }

  if (needRefresh)
  {
    m_viewWrapper.Refresh();
  }
  return ctrlType;
}

short UeGui::CMapHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short UeGui::CMapHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case CT_Unknown:
    {
      //��������ͼ�¼�
      MapTouch(scrPoint);
    }
    break;
  case MapHook_MiniMizeBack:
  case MapHook_MiniMizeIcon:
    {
      m_miniMizeBtn.MouseUp();
      needRefresh = true;
      MinMize();
    }
    break;
  case MapHook_AddElecEyeBack:
  case MapHook_AddElecEyeIcon:
    {
      m_addElecEyeBtn.MouseUp();
      needRefresh = true;
    }
    break;
  case MapHook_MapAzimuthBack:
  case MapHook_NorthIcon:
  case MapHook_PerspectiveIcon:
  case MapHook_HeadingIcon:
    {
      m_mapAzimuthBtn.MouseUp();
      needRefresh = true;
      ChangeMapAzimuth();
    }
    break;
  case MapHook_ZoomInBack:
  case MapHook_ZoomInIcon:
    {
      m_zoomInBtn.MouseUp();
      if (m_zoomInBtn.IsEnable())
      {
        needRefresh = true;
        ZoomIn();
      }
    }
    break;
  case MapHook_ZoomOutBack:
  case MapHook_ZoomOutIcon:
    {
      m_zoomOutBtn.MouseUp();
      if (m_zoomOutBtn.IsEnable())
      {
        needRefresh = true;
        ZoomOut();
      }
    }
    break;
  case MapHook_ScaleBack:
  case MapHook_ScaleLabel:
    {
      m_scaleBtn.MouseUp();
      needRefresh = true;
    }
    break;
  case MapHook_SoundBack:
  case MapHook_SoundIcon:
    {
      m_soundBtn.MouseUp();
      needRefresh = true;
      //TurnTo(DHT_SoundMenuHook);
    }
    break;
  case MapHook_GPSBack:
  case MapHook_GPSIcon:
    {
      m_GPSBtn.MouseUp();
      needRefresh = true;
      //TurnTo(DHT_GPSHook);
    }
    break;
  case MapHook_ScreenMoadlBack:
  case MapHook_SingleScreenIcon:
  case MapHook_DoubleScreenIcon:
    {
      m_screenMoadlBtn.MouseUp();
      needRefresh = true;
    }
    break;
  case MapHook_SetStartBack:
  case MapHook_SetStartIcon:
  case MapHook_SetStartLabel:
    {
      m_setStartBtn.MouseUp();
      if (m_setStartBtn.IsEnable())
      {
        needRefresh = true;
        SetRouteStart();
      }
    }
    break;
  case MapHook_SetEndBack:
  case MapHook_SetEndIcon:
  case MapHook_SetEndLabel:
    {
      m_setEndBtn.MouseUp();
      if (m_setEndBtn.IsEnable())
      {
        needRefresh = true;
        unsigned int rt = SetRouteEnd();
        if (UeRoute::PEC_Success == rt)
        {
          RoutePlane(Plan_Multiple);
        }
      }
    }
    break;
  case MapHook_SetWayBack:
  case MapHook_SetWayIcon:
  case MapHook_SetWayLabel:
    {
      m_setWayBtn.MouseUp();
      if (m_setWayBtn.IsEnable())
      {
        needRefresh = true;
        SetRouteMiddle();
      }
    }
    break;
  case MapHook_FixedPostionBack:
  case MapHook_FixedPostionIcon:
  case MapHook_FixedPostionLabel:
    {
      m_fixedPostionBtn.MouseUp();
      needRefresh = true;
      MoveToGPS();
    }
    break;
  case MapHook_DetailBack1:
  case MapHook_DetailIcon1:
  case MapHook_DetailLabe1:
    {
      m_detailBtn1.MouseUp();
      needRefresh = true;
    }
    break;
  case MapHook_DetailBack2:
  case MapHook_DetailIcon2:
  case MapHook_DetailLabe2:
    {
      m_detailBtn2.MouseUp();
      needRefresh = true;
    }
    break;
  case MapHook_GuideInfoCenterBack:
  case MapHook_GuideInfoCenterIcon:
  case MapHook_GuideInfoCenterLabe:
    {
      m_guideInfoCenterBtn.MouseUp();
      needRefresh = true;
    }
    break;
  }
 
  if (needRefresh)
  {
    m_viewWrapper.Refresh();
  }
  return ctrlType;
}

void UeGui::CMapHook::HideAllCtrl()
{
  ShowMinimizeBtn(false);
  ShowAddElecEyeBtn(false);
  ShowMapAzimuthBtn(false);
  ShowMapScalingBtn(false);
  ShowSetDestPointBtn(false);
  ShowFixedPostionBtn(false);
  ShowDetailBtn1(false);
  ShowDetailBtn2(false);
  ShowGuideInfoBtn(false);
}

void UeGui::CMapHook::ShowMinimizeBtn( bool show /*= true*/ )
{
  m_miniMizeBtn.SetVisible(show);
  m_soundBtn.SetVisible(show);
  m_GPSBtn.SetVisible(show);
  m_screenMoadlBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowAddElecEyeBtn( bool show /*= true*/ )
{
  m_addElecEyeBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowMapAzimuthBtn( bool show /*= true*/ )
{
  m_mapAzimuthBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowMapScalingBtn( bool show /*= true*/ )
{
  m_zoomInBtn.SetVisible(show);
  m_zoomOutBtn.SetVisible(show);
  m_scaleBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowSetDestPointBtn( bool show /*= true*/ )
{
  m_setStartBtn.SetVisible(show);
  m_setWayBtn.SetVisible(show);
  m_setEndBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowFixedPostionBtn( bool show /*= true*/ )
{
  m_fixedPostionBtn.SetVisible(show);
}

void UeGui::CMapHook::ShowDetailBtn1( bool show /*= true*/ )
{
  m_detailBtn1.SetVisible(show);
}

void UeGui::CMapHook::ShowDetailBtn2( bool show /*= true*/ )
{
  m_detailBtn2.SetVisible(show);
}

void UeGui::CMapHook::ShowGuideInfoBtn( bool show /*= true*/ )
{
  m_guideInfoLeftBtn.SetVisible(show);
  m_guideInfoCenterBtn.SetVisible(show);
  m_guideInfoRightBtn.SetVisible(show);
  m_delimiter1.SetVisible(show);
  m_delimiter2.SetVisible(show);
  if (show)
  {
    RefreshSetPointStatus();
  }
}

void UeGui::CMapHook::ShowTimeBtn( bool show /*= true*/ )
{
  m_timerBtn.SetVisible(show);
}

void UeGui::CMapHook::OpenFunctionMenu()
{
  TurnTo(CViewHook::DHT_MainMenuHook);
}

void UeGui::CMapHook::OpenShortCutMenu()
{
  TurnTo(CViewHook::DHT_FastOperationHook);
}

void UeGui::CMapHook::OpenAroundSearchMenu()
{
  TurnTo(CViewHook::DHT_FastOperationHook);
}

void UeGui::CMapHook::OpenSearchMenu()
{
  CInputSwitchHook *inputHook = (CInputSwitchHook *)m_viewWrapper.GetHook(DHT_InputSwitchHook);
  if (inputHook)
  {
    TurnTo(inputHook->GetCurInputHookType());
  }
}

void UeGui::CMapHook::ChangeMapAzimuth()
{
  m_viewWrapper.NextState();
  RefreshMapAzimuthIcon();
}

void UeGui::CMapHook::ZoomIn()
{
  m_viewWrapper.ZoomIn(1, 0);
  RefreshZoomingInfo();
}

void UeGui::CMapHook::ZoomOut()
{
  m_viewWrapper.ZoomOut(1, 0);
  RefreshZoomingInfo();
}

void UeGui::CMapHook::MinMize()
{
  m_viewWrapper.HideWindow();
}

unsigned int UeGui::CMapHook::SetRouteStart()
{
  return m_routeWrapper.SetRouteStart();
}

unsigned int UeGui::CMapHook::SetRouteMiddle()
{
  unsigned int rt = m_routeWrapper.SetRouteMiddle();
  if (UeRoute::PEC_Success == rt)
  {
    CMessageDialogEvent dialogEvent(this, DHT_MapHook, NULL);
    CMessageDialogHook::ShowMessageDialog(MB_NONE, "�滮�У����Ժ�...", dialogEvent);
    rt = m_routeWrapper.RoutePlan();
    if (UeRoute::PEC_Success == rt)
    {
      Sleep(1000);
      CMessageDialogHook::CloseMessageDialog();
      //�л���·���滮�˵�
      SwitchingGUI(GUI_RouteCalculate);
    }
    else
    {
      m_routeWrapper.RemovePosition();
      CMessageDialogHook::ShowMessageDialog(MB_NONE, "·���滮ʧ��", dialogEvent);
      Sleep(2000);
      CMessageDialogHook::CloseMessageDialog();
    } 
  }
  return rt;
}

unsigned int UeGui::CMapHook::SetRouteEnd()
{  
  unsigned int rt = m_routeWrapper.SetRouteEnd();
  if (UeRoute::PEC_TooShortest == rt)
  {
    CMessageDialogEvent dialogEvent(this, DHT_MapHook, NULL);
    CMessageDialogHook::ShowMessageDialog(MB_NONE, "����Ŀ�ĵؾ���̫��", dialogEvent);
    Sleep(1000);
    CMessageDialogHook::CloseMessageDialog();
  }
  return rt;
}

unsigned int UeGui::CMapHook::RoutePlane( PlanType planType /*= Plan_Single*/ )
{
  CMessageDialogEvent dialogEvent(this, DHT_MapHook, NULL);
  CMessageDialogHook::ShowMessageDialog(MB_NONE, "�滮�У����Ժ�...", dialogEvent);
  unsigned int rt = false;
  if (Plan_Multiple == planType)
  {
    rt = m_routeWrapper.RoutePlan();
    rt = m_routeWrapper.MultiRoutePlan();
    m_planType = Plan_Multiple;
  }
  else
  {
    rt = m_routeWrapper.RoutePlan();
    m_planType = Plan_Single;
  }
  
  if (UeRoute::PEC_Success == rt)
  {
    Sleep(1000);
    CMessageDialogHook::CloseMessageDialog();
    //�л���·���滮�˵�
    SwitchingGUI(GUI_RouteCalculate);
    //������ʷ������
    m_userDataWrapper.AddHistoryPoint(UeRoute::PT_Start);
    //������ʷĿ�ĵ�
    m_userDataWrapper.AddHistoryPoint(UeRoute::PT_End);
    //������ʷ·��
    m_userDataWrapper.AddRecent();
  }
  else
  {
    m_routeWrapper.RemovePosition();
    CMessageDialogHook::ShowMessageDialog(MB_NONE, "·���滮ʧ��", dialogEvent);
    Sleep(1000);
    CMessageDialogHook::CloseMessageDialog();
  } 
  return rt;
}

unsigned char UeGui::CMapHook::GetMultiMethodType()
{
  UeRoute::MethodType methType = MT_Max;
  if (Plan_Single == m_planType)
  {
    methType = MT_Max;
  }
  else
  {
    if (GUI_RouteCalculate == m_curGuiType)
    {
      unsigned int planMethod =  m_routeWrapper.GetMethod();
      if (planMethod & UeRoute::RW_Optimal)
      {
        methType = MT_Optimal;
      }
      else if (planMethod & UeRoute::RW_Short)
      {
        methType = MT_Short;
      }
      else if (planMethod & UeRoute::RW_Fast)
      {
        methType = MT_Fast;
      }
      else if (planMethod & UeRoute::RW_Economic)
      {
        methType = MT_Economic;
      }
    }
    else
    {
      methType = MT_Max;
    }
  }
  return methType;
}

unsigned int UeGui::CMapHook::StartDemo( short speed /*= DEFAULT_DEMOSPEED*/ )
{
  unsigned int rt = m_routeWrapper.StartDemo(speed);
  if (UeRoute::PEC_Success == rt)
  {
    m_viewWrapper.SwitchTo(SCALE_100M, 0);
    m_viewWrapper.SetViewOpeMode(VM_Guidance);
    //��ʼ��ģ�⵼����Ϣ
    m_mapSimulationMenu.ReseSimulation();
    //�л���·���滮�˵�
    SwitchingGUI(GUI_DemoGuidance);
  }
  return rt;
}

unsigned int UeGui::CMapHook::StopDemo()
{
  unsigned int rt = m_routeWrapper.StopDemo();
  m_viewWrapper.SetViewOpeMode(VM_Guidance);
  //�л�������˵�
  SwitchingGUI(GUI_MapBrowse);
  UpdateMenu();
  return rt;
}

unsigned int UeGui::CMapHook::StartGuidance()
{
  m_viewWrapper.SwitchTo(SCALE_100M, 0);
  m_viewWrapper.SetViewOpeMode(VM_Guidance);
  m_viewWrapper.MoveToStart();
  //�л���·���滮�˵�
  SwitchingGUI(GUI_RealGuidance);
  UpdateMenu();
  return m_routeWrapper.StartGuidance();
}

unsigned int UeGui::CMapHook::StopGuidance()
{
  unsigned int rt = m_routeWrapper.StopGuidance();
  //�л������״̬״̬�˵�
  SwitchingGUI(GUI_MapBrowse);
  UpdateMenu();
  return rt;
}

unsigned int UeGui::CMapHook::EraseRoute()
{
  //�жϵ�ǰ�Ƿ��Ѿ��滮��·��
  UeRoute::PlanResultDesc desc;
  if ((m_routeWrapper.GetPlanState() != UeRoute::PS_None) && (m_routeWrapper.GetPlanResultDesc(desc)))
  {
    m_routeWrapper.SetBlock(true);
    m_routeWrapper.Prepare();
  }
  m_viewWrapper.SetViewOpeMode(VM_Guidance);
  //�л������״̬״̬�˵�
  SwitchingGUI(GUI_MapBrowse);
  UpdateMenu();
  return UeRoute::PEC_Success;
}

void UeGui::CMapHook::Cancel()
{
  //�л������״̬״̬�˵�
  SwitchingGUI(GUI_MapBrowse);
}

void UeGui::CMapHook::Select()
{
  if (m_selectPointObj && m_selectPointEvent)
  {
    CGeoPoint<long> pickPos;
    m_view->GetPickPos(pickPos);
    SQLRecord record;
    record.m_x = pickPos.m_x;
    record.m_y = pickPos.m_y;
    m_view->GetPickName(record.m_uniName);
    (*m_selectPointEvent)(m_selectPointObj, &record);
  }
}

void UeGui::CMapHook::SetPickPos( const CGeoPoint<long> &point, const char* name )
{
  RefreshLocationInfo(name);
  CGeoPoint<short> scrPoint;
  m_viewWrapper.SwitchTo(SCALE_200M, 0);  
  RefreshZoomingInfo();
  m_viewWrapper.SetPickPos(point, scrPoint);
}

void UeGui::CMapHook::SetPickPos( PointList pointList, unsigned short posIndex )
{
  ClearQueryPointList();
  if ((posIndex >= 0) && (posIndex < pointList.size()))
  {
    m_queryPointIndex = posIndex;    
    m_queryPointList = pointList;
    m_curPoint = pointList[posIndex];
    SetPickPos(m_curPoint.m_point, m_curPoint.m_name);    
  }
  SwitchingGUI(GUI_QueryPoint);
}

void UeGui::CMapHook::SelectPoint( const CGeoPoint<long> &point, const char* name, void* selectPointObj, SelectPointEvent selectEvent )
{
  m_selectPointObj = selectPointObj;
  m_selectPointEvent = selectEvent;
  SetPickPos(point, name);
  SwitchingGUI(GUI_SelectPoint);  
}

void UeGui::CMapHook::OverviewRoute()
{
  SwitchingGUI(GUI_OverviewRoute);
  m_viewWrapper.AutoScallingMap(true);
}

void UeGui::CMapHook::RefreshLocationInfo( const char* name /*= NULL*/ )
{
  if (NULL == name)
  {
    // ʰȡ��Ϣ
    char pickName[256];
    //sprintf(buff, "%s", m_viewWrapper.GetSelectName());
    m_viewWrapper.GetPickName(pickName);
    if(::strlen(pickName) > 0)
    {
      pickName[::strlen(pickName) - 1] = '\0';
    } 
    else 
    {
      CGeoPoint<long> pickPos;    
      m_viewWrapper.GetPickPos(pickPos);
      IGui* gui = IGui::GetGui();
      if (!gui->GetDistrictName(pickPos, pickName))
      {
        ::memset(pickName, 0, 256);
      }
    }
    m_detailBtn1.SetCaption(pickName);
    m_detailBtn2.SetCaption(pickName);
    m_guideInfoCenterBtn.SetCaption(pickName);
  }
  else
  {
    m_detailBtn1.SetCaption(name);
    m_detailBtn2.SetCaption(name);
    m_guideInfoCenterBtn.SetCaption(name);
  }
}

void UeGui::CMapHook::RefreshMapAzimuthIcon()
{
  CViewState *curState = m_viewWrapper.GetMainViewState();
  m_mapAzimuthBtn.SetVisible(false);
  if (curState)
  {
    switch (curState->GetType())
    {
    case VT_North:
      {
        m_mapAzimuthBtn.SetIconElement(GetGuiElement(MapHook_NorthIcon));
        m_settingWrapper.SetMapDirection(ViewSettings::MD_DueNorth);
      }
      break;
    case VT_Heading:
      {
        m_mapAzimuthBtn.SetIconElement(GetGuiElement(MapHook_HeadingIcon));
        m_settingWrapper.SetMapDirection(ViewSettings::MD_HeadMap);
      }
      break;
    case VT_Perspective:
      {
        m_mapAzimuthBtn.SetIconElement(GetGuiElement(MapHook_PerspectiveIcon));
        m_settingWrapper.SetMapDirection(ViewSettings::MD_25DMap);
      }
      break;
    }
    m_settingWrapper.SaveNaviationSettings();
  }
  m_mapAzimuthBtn.SetVisible(true);
}

void UeGui::CMapHook::RefreshZoomingInfo()
{
  short curLevel = 0;
  int scale = 0;
  m_viewWrapper.GetScale(curLevel, scale);
  int  maxScaleLevel =  m_viewWrapper.GetMaxScaleLevel();

  if (curLevel <= 1)
  {
    // ������С������
    m_zoomInBtn.SetEnable(false);
    if (!m_zoomOutBtn.IsEnable())
    {
      m_zoomOutBtn.SetEnable(true);
    }    
  }
  else if(curLevel >= maxScaleLevel) 
  {
    // ���÷Ŵ󲻿���
    m_zoomOutBtn.SetEnable(false);
    if (!m_zoomInBtn.IsEnable())
    {
      m_zoomInBtn.SetEnable(true);
    }
  }
  else
  {
    if (!m_zoomInBtn.IsEnable())
    {
      m_zoomInBtn.SetEnable(true);
    }
    if (!m_zoomOutBtn.IsEnable())
    {
      m_zoomOutBtn.SetEnable(true);
    }    
  }
  //���±�����
  RefreshScaleLabel(curLevel);
}

void UeGui::CMapHook::RefreshScaleLabel( unsigned short scaleLevel )
{
  char msg[10] = {};
  switch (scaleLevel)
  {
  case SCALE_10M:
    {
      strcpy(msg, "25m");
    }
    break;
  case SCALE_25M:
    {
      strcpy(msg, "25m");
    }
    break;
  case SCALE_50M:
    {
      strcpy(msg, "50m");
    }
    break;
  case SCALE_100M:
    {
      strcpy(msg, "100m");
    }
    break;
  case SCALE_200M:
    {
      strcpy(msg, "200m");
    }
    break;
  case SCALE_500M:
    {
      strcpy(msg, "500m");
    }
    break;
  case SCALE_1KM:
    {
      strcpy(msg, "1km");
    }
    break;
  case SCALE_2KM:
    {
      strcpy(msg, "2km");
    }
    break;
  case SCALE_5KM:
    {
      strcpy(msg, "5km");
    }
    break;
  case SCALE_10KM:
    {
      strcpy(msg, "10km");
    }
    break;
  case SCALE_20KM:
    {
      strcpy(msg, "20km");
    }
    break;
  case SCALE_50KM:
    {
      strcpy(msg, "50km");
    }
    break;
  case SCALE_100KM:
    {
      strcpy(msg, "100km");
    }
    break;
  case SCALE_200KM:
    {
      strcpy(msg, "200km");
    }
    break;
  case SCALE_1000KM:
    {
      strcpy(msg, "1000km");
    }
    break;
  default:
    {
      return;
    }    
  }
  m_scaleBtn.SetCaption(msg);
}

void UeGui::CMapHook::ShowGPSNum( int locationNum )
{
  if (locationNum > 12)
  {
    locationNum = 12;
  }
  GuiElement* guiElement = NULL;
  switch (locationNum)
  {
  case 1:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon1);
      break;
    }
  case 2:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon2);
      break;
    }
  case 3:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon3);
      break;
    }
  case 4:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon4);
      break;
    }
  case 5:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon5);
      break;
    }
  case 6:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon6);
      break;
    }
  case 7:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon7);
      break;
    }
  case 8:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon8);
      break;
    }
  case 9:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon9);
      break;
    }
  case 10:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon10);
      break;
    }
  case 11:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon11);
      break;
    }
  case 12:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon12);
      break;
    }
  default:
    {
      guiElement = GetGuiElement(MapHook_GPSIcon0);
      break;
    }
  }

  if (guiElement)
  {
    GuiElement* gpsElement = GetGuiElement(MapHook_GPSIcon);
    if (gpsElement)
    {
      gpsElement->m_backStyle = guiElement->m_bkNormal;
    }
  }  
}

void UeGui::CMapHook::RefreshSetPointStatus()
{
  //�ж��Ƿ��������յ�
  PlanPosition endPos;
  endPos.m_type = UeRoute::PT_End;
  unsigned int rt = m_routeWrapper.GetPosition(endPos);
  if ((UeRoute::PT_Invalid == endPos.m_type) || (!endPos.IsValid()))
  {
    m_setWayBtn.SetEnable(false);
  }
  else
  {
    m_setWayBtn.SetEnable(true);
  }
}

void UeGui::CMapHook::FillGuidanceInfo()
{
  //���������˵�״̬
  UpdateMenu(MUT_Normal);
}

void UeGui::CMapHook::UpdateGuideInfo( const char* routeName, double speed, double distance )
{
  if (speed < 0)
  {
    speed = 0;
  }
  if (distance < 0)
  {
    distance = 0;
  }
  //������ʻ�ٶ�
  char buf[32] = {};
  ::sprintf(buf, "%0.0f km/h", speed);
  m_guideInfoLeftBtn.SetCaption(buf);
  //��ǰ��ʻ��·����
  m_guideInfoCenterBtn.SetCaption(routeName);
  //�����յ����
  if (distance < 0)
  {
    distance = 0;
  }
  if (distance <= 1000)
  {
    ::sprintf(buf, "%dm", static_cast<int>(distance));
  } 
  else
  {
    ::sprintf(buf, "%.1fkm", distance / 1000.0);
  }
  m_guideInfoRightBtn.SetCaption(buf);
}

void UeGui::CMapHook::MoveToStart()
{
  m_viewWrapper.MoveToStart();
  //���ݵ�ǰ����״̬�л�����˵�
  short planState = m_routeWrapper.GetPlanState();
  if (UeRoute::PS_DemoGuidance == planState)
  {    
    SwitchingGUI(GUI_DemoGuidance);
  }
  if (UeRoute::PS_RealGuidance == planState)
  {
    SwitchingGUI(GUI_RealGuidance);
  }
  else
  {
    SwitchingGUI(GUI_MapBrowse);
  }
  //�����˵�
  UpdateMenu(MUT_Close);
}

void UeGui::CMapHook::MoveToCar()
{
  m_viewWrapper.MoveToCar();
  //���ݵ�ǰ����״̬�л�����˵�
  short planState = m_routeWrapper.GetPlanState();
  if (UeRoute::PS_DemoGuidance == planState)
  {    
    SwitchingGUI(GUI_DemoGuidance);
  }
  if (UeRoute::PS_RealGuidance == planState)
  {
    SwitchingGUI(GUI_RealGuidance);
  }
  else
  {
    SwitchingGUI(GUI_MapBrowse);
  }
  //�����˵�
  UpdateMenu(MUT_Close);
}

void UeGui::CMapHook::MoveToGPS()
{
  m_viewWrapper.MoveToGPS();
  //���ݵ�ǰ����״̬�л�����˵�
  short planState = m_routeWrapper.GetPlanState();
  if (UeRoute::PS_DemoGuidance == planState)
  {    
    SwitchingGUI(GUI_DemoGuidance);
  }
  if (UeRoute::PS_RealGuidance == planState)
  {
    SwitchingGUI(GUI_RealGuidance);
  }
  else
  {
    SwitchingGUI(GUI_MapBrowse);
  }
  //�����˵�
  UpdateMenu(MUT_Close);
}

void UeGui::CMapHook::ClearQueryPointList()
{
  ::memset(&m_curPoint, 0, sizeof(PointInfo));
  m_queryPointIndex = -1;
  m_queryPointList.clear();
}

void UeGui::CMapHook::SetQueryPos( PosType posType )
{
  if (m_queryPointList.empty())
  {
    return;
  }
  if ((m_queryPointIndex >= 0) && (m_queryPointIndex <= m_queryPointList.size() - 1))
  {
    switch (posType)
    {
    case PT_Current:
      {
        //��λ����ǰ������Ҫ����
        break;
      }
    case PT_Previous:
      {
        if (m_queryPointIndex > 0)
        {
          m_queryPointIndex--;
          m_curPoint = m_queryPointList[m_queryPointIndex];
        }
        break;
      }
    case PT_Next:
      {
        if (m_queryPointIndex < m_queryPointList.size() - 1)
        {
          m_queryPointIndex++;
          m_curPoint = m_queryPointList[m_queryPointIndex];
        }
        break;
      }
    }
    if (m_curPoint.m_point.IsValid())
    {
      SetPickPos(m_curPoint.m_point, m_curPoint.m_name);
    } 
  }
}

bool UeGui::CMapHook::HaveNextQueryPoint( PosType posType )
{
  if (m_queryPointList.empty())
  {
    return false;
  }
  bool haveNext = false;
  if ((m_queryPointIndex >= 0) && (m_queryPointIndex <= m_queryPointList.size() - 1))
  {
    switch (posType)
    {
    case PT_Previous:
      {
        if (m_queryPointIndex <= 0)
        {
          haveNext = false;
        }
        else
        {
          haveNext = true;
        }
        break;
      }
    case PT_Next:
      {
        if (m_queryPointIndex >= m_queryPointList.size() - 1)
        {
          haveNext = false;
        }
        else
        {
          haveNext = true;
        }
        break;
      }
    }
  }
  return haveNext;
}

void UeGui::CMapHook::RestarGuiTimer()
{
  m_guiTimerInterval = TIMER_INTERVAL;
}

void UeGui::CMapHook::CloseGuiTimer()
{
  m_guiTimerInterval = 0;
}