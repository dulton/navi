#include "mapmainmenuhook.h"
#include "maphook.h"

using namespace UeGui;

CMapMainMenuHook::CMapMainMenuHook() : m_parentHook(NULL), m_viewWrapper(CViewWrapper::Get()),
 m_routeWrapper(CRouteWrapper::Get()), m_expandStatus(false)
{
  //地图界面渲染完成后不需要释放图片资源，提高效率
  m_needReleasePic = false;
}

CMapMainMenuHook::~CMapMainMenuHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

bool CMapMainMenuHook::operator ()()
{
  return false;
}

void UeGui::CMapMainMenuHook::Show( bool show /*= true */ )
{
  CAggHook::Show(show);
  if (show)
  {
    ExpandMenu(false);
  }  
}

tstring CMapMainMenuHook::GetBinaryFileName()
{
  return _T("mapmainmenuhook.bin");
}

void CMapMainMenuHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_ExpandBtn,	"ExpandBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_CloseBtn,	"CloseBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_FunctionBtn,	"FunctionBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_FunctionLabel,	"FunctionLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_Delimiter1,	"Delimiter1"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_ShortcutBtn,	"ShortcutBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_ShortcutLabel,	"ShortcutLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_Delimiter2,	"Delimiter2"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_AroundBtn,	"AroundBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_AroundLabel,	"AroundLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_Delimiter3,	"Delimiter3"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_SearchBtn,	"SearchBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_SearchIcon,	"SearchIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_SearchLabel,	"SearchLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_SearchBtnR,	"SearchBtnR"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_StopGuideBtn,	"StopGuideBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_StopGuideLabel,	"StopGuideLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_RouteBtn,	"RouteBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapMainMenuHook_RouteLabel,	"RouteLabel"));
}

void CMapMainMenuHook::MakeControls()
{
  //展开菜单按钮
  m_expandBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_ExpandBtn));
  //关闭菜单按钮
  m_closeBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_CloseBtn));
  //功能
  m_functionBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_FunctionBtn));
  m_functionBtn.SetLabelElement(GetGuiElement(MapMainMenuHook_FunctionLabel));
  //快捷
  m_shortcutBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_ShortcutBtn));
  m_shortcutBtn.SetLabelElement(GetGuiElement(MapMainMenuHook_ShortcutLabel));
  //周边
  m_aroundBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_AroundBtn));
  m_aroundBtn.SetLabelElement(GetGuiElement(MapMainMenuHook_AroundLabel));
  //搜索
  m_searchBtn.SetCenterElement(GetGuiElement(MapMainMenuHook_SearchBtn));
  m_searchBtn.SetRightElement(GetGuiElement(MapMainMenuHook_SearchBtnR));
  m_searchBtn.SetIconElement(GetGuiElement(MapMainMenuHook_SearchIcon));
  m_searchBtn.SetLabelElement(GetGuiElement(MapMainMenuHook_SearchLabel));
  //停止导航
  m_stopGuide.SetCenterElement(GetGuiElement(MapMainMenuHook_StopGuideBtn));
  m_stopGuide.SetLabelElement(GetGuiElement(MapMainMenuHook_StopGuideLabel));
  //路线操作
  m_routeOpe.SetCenterElement(GetGuiElement(MapMainMenuHook_RouteBtn));
  m_routeOpe.SetLabelElement(GetGuiElement(MapMainMenuHook_RouteLabel));
  //分割符
  m_delimiter1.SetCenterElement(GetGuiElement(MapMainMenuHook_Delimiter1));
  m_delimiter2.SetCenterElement(GetGuiElement(MapMainMenuHook_Delimiter2));
  m_delimiter3.SetCenterElement(GetGuiElement(MapMainMenuHook_Delimiter3));
}

void UeGui::CMapMainMenuHook::SetParentHook( CAggHook* parentHook )
{
  m_parentHook = parentHook;
}

short CMapMainMenuHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  //是否需要刷新
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case MapMainMenuHook_ExpandBtn:
    {
      needRefresh = true;
      m_expandBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_CloseBtn:
    {
      needRefresh = true;
      m_closeBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_FunctionBtn:
  case MapMainMenuHook_FunctionLabel:
    {
      needRefresh = true;
      m_functionBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_ShortcutBtn:
  case MapMainMenuHook_ShortcutLabel:
    {
      needRefresh = true;
      m_shortcutBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_AroundBtn:
  case MapMainMenuHook_AroundLabel:
    {
      needRefresh = true;
      m_aroundBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_SearchBtn:
  case MapMainMenuHook_SearchBtnR:
  case MapMainMenuHook_SearchIcon:
  case MapMainMenuHook_SearchLabel:
    {
      needRefresh = true;
      m_searchBtn.MouseDown();
    }
    break;
  case MapMainMenuHook_StopGuideBtn:
  case MapMainMenuHook_StopGuideLabel:
    {
      needRefresh = true;
      m_stopGuide.MouseDown();
    }
    break;
  case MapMainMenuHook_RouteBtn:
  case MapMainMenuHook_RouteLabel:
    {
      needRefresh = true;
      m_routeOpe.MouseDown();
    }
    break;
  default:
    assert(false);
    break;
  }

  if (needRefresh)
  {
    this->Refresh();
  }
  return ctrlType;
}

short CMapMainMenuHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CMapMainMenuHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  //是否需要刷新
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(ctrlType)
  {
  case MapMainMenuHook_ExpandBtn:
    {
      needRefresh = true;
      m_expandBtn.MouseUp();
      ExpandMenu();
    }
    break;
  case MapMainMenuHook_CloseBtn:
    {
      needRefresh = true;
      m_closeBtn.MouseUp();
      ExpandMenu(false);
    }
    break;
  case MapMainMenuHook_FunctionBtn:
  case MapMainMenuHook_FunctionLabel:
    {
      m_functionBtn.MouseUp();
      needRefresh = true;
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->OpenFunctionMenu();
      }
    }
    break;
  case MapMainMenuHook_ShortcutBtn:
  case MapMainMenuHook_ShortcutLabel:
    {
      needRefresh = true;
      m_shortcutBtn.MouseUp();
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->OpenShortCutMenu();
      }
    }
    break;
  case MapMainMenuHook_AroundBtn:
  case MapMainMenuHook_AroundLabel:
    {
      needRefresh = true;
      m_aroundBtn.MouseUp();
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->OpenAroundSearchMenu();
      }
    }
    break;
  case MapMainMenuHook_SearchBtn:
  case MapMainMenuHook_SearchBtnR:
  case MapMainMenuHook_SearchIcon:
  case MapMainMenuHook_SearchLabel:
    {
      needRefresh = true;
      m_searchBtn.MouseUp();
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->OpenSearchMenu();
      }
    }
    break;
  case MapMainMenuHook_StopGuideBtn:
  case MapMainMenuHook_StopGuideLabel:
    {
      needRefresh = false;
      m_stopGuide.MouseUp();
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->StopGuidance();
      }
    }
    break;
  case MapMainMenuHook_RouteBtn:
  case MapMainMenuHook_RouteLabel:
    {
      needRefresh = true;
      m_routeOpe.MouseUp();
      TurnTo(DHT_RouteOperationHook);
    }
    break;
  default:
    assert(false);
    break;
  }
  if (needRefresh)
  {
    this->Refresh();
  }
  return ctrlType;
}

void UeGui::CMapMainMenuHook::ExpandMenu( bool bExpand /*= true*/ )
{
  CMapHook* mapHook = NULL;
  if (m_parentHook)
  {
    mapHook = dynamic_cast<CMapHook*>(m_parentHook);
  }
  if (NULL == mapHook)
  {
    return;
  }
  //保存当前菜单展开状态
  m_expandStatus = bExpand;
  //读取当前地图操作模式
  UeMap::ViewOpeMode viewMode = UeMap::VM_Unknown;
  CViewState* curViewState = m_viewWrapper.GetMainViewState();
  if (curViewState)
  {
    viewMode = m_viewWrapper.GetViewOpeMode((UeMap::ViewType)curViewState->GetType());
  }
  //读取当前规划状态
  short planState = m_routeWrapper.GetPlanState();

  //执行展开或者收缩
  if (bExpand)
  {
    //显示菜单栏
    ShowMenuBar(true, bExpand);
    //重新开启界面切换定时器
    mapHook->RestarGuiTimer();    
    mapHook->ShowMinimizeBtn();      
    mapHook->ShowMapAzimuthBtn();
    mapHook->ShowMapScalingBtn();
    mapHook->ShowDetailBtn1();
    mapHook->ShowDetailBtn2(false);
    mapHook->ShowGuideInfoBtn(false);
    mapHook->ShowCompass(false);
    mapHook->ShowElecEye(false);
    mapHook->RefreshSrcModalBtnStatus();

    if ((UeRoute::PS_RealGuidance == planState) && (UeMap::VM_Guidance == viewMode))
    {
      m_stopGuide.SetVisible(true);
      mapHook->ShowAddElecEyeBtn(false);        
    }
    else
    {
      m_stopGuide.SetVisible(false);
      mapHook->ShowAddElecEyeBtn();        
    }
    if (UeMap::VM_Guidance == viewMode)
    {
      mapHook->ShowSetDestPointBtn(false);
      mapHook->ShowFixedPostionBtn(false);
    }
    else
    {
      mapHook->ShowSetDestPointBtn();
      mapHook->ShowFixedPostionBtn();
    }

    //是否显示路线按钮
    if ((UeRoute::PS_RealGuidance == planState) || (UeRoute::PS_Ready == planState))
    {
      m_routeOpe.SetVisible(true);
    }
    else
    {
      m_routeOpe.SetVisible(false);
    }
  }
  else
  {
    //显示菜单栏
    ShowMenuBar(true, bExpand);
    //关闭界面切换定时器
    mapHook->CloseGuiTimer();
    mapHook->ShowMinimizeBtn(false);
    mapHook->ShowAddElecEyeBtn();
    mapHook->ShowDetailBtn1(false);

    if (VM_Browse == viewMode)
    {
      mapHook->ShowMapAzimuthBtn();
      mapHook->ShowMapScalingBtn();
      mapHook->ShowSetDestPointBtn();
      mapHook->ShowFixedPostionBtn();
      mapHook->ShowDetailBtn2();
    }
    else
    {
      mapHook->ShowMapAzimuthBtn(false);
      mapHook->ShowMapScalingBtn(false);
      mapHook->ShowSetDestPointBtn(false);
      mapHook->ShowFixedPostionBtn(false);
      mapHook->ShowDetailBtn2(false);
    }
    m_stopGuide.SetVisible(false);
    m_routeOpe.SetVisible(false);
  }

  //动态更新界面
  DynamicUpdate(bExpand, planState, viewMode);
}

void UeGui::CMapMainMenuHook::Update( short type )
{
  //读取当前地图操作模式
  UeMap::ViewOpeMode viewMode = UeMap::VM_Unknown;
  CViewState* curViewState = m_viewWrapper.GetMainViewState();
  if (curViewState)
  {
    viewMode = m_viewWrapper.GetViewOpeMode((UeMap::ViewType)curViewState->GetType());
  }
  //读取当前规划状态
  short planState = m_routeWrapper.GetPlanState();
  //动态更新界面
  DynamicUpdate(m_expandStatus, planState, viewMode);
}

void UeGui::CMapMainMenuHook::DynamicUpdate( bool bExpand, short planState, UeMap::ViewOpeMode viewMode )
{
  CMapHook* mapHook = NULL;
  if (m_parentHook)
  {
    mapHook = dynamic_cast<CMapHook*>(m_parentHook);
  }
  if (NULL == mapHook)
  {
    return;
  }

  //执行展开或者收缩
  if (bExpand)
  {
    //更新切换屏幕模式按钮状态
    mapHook->RefreshSrcModalBtnStatus();
  }
  else
  {
    if (VM_Guidance == viewMode)
    {
      if (mapHook->HaveElecEyePrompt())
      {
        mapHook->ShowCompass(false);
        mapHook->ShowElecEye();
      }
      else
      {
        mapHook->ShowCompass();
        mapHook->ShowElecEye(false);
      }
    }

    //如果显示路口放大图
    if (m_viewWrapper.IsGuidanceViewShown())
    {
      //隐藏菜单栏
      ShowMenuBar(false, bExpand);
      mapHook->ShowGuideInfoBtn(false);
    }
    else
    {
      //显示菜单栏
      ShowMenuBar(true, bExpand);
      if (VM_Browse == viewMode)
      {
        mapHook->ShowGuideInfoBtn(false);
      }
      else
      {
        mapHook->ShowGuideInfoBtn();
      }
    }
  }

  //判断是否要显示时间按钮
  if (m_viewWrapper.IsGuidanceViewShown())
  {
    mapHook->ShowTimeBtn(false);
  }
  else
  {
    if (m_viewWrapper.IsNeedRenderGuidanceView())
    {
      mapHook->ShowTimeBtn(false);
    }
    else
    {
      mapHook->ShowTimeBtn();
    }
  }
}

void UeGui::CMapMainMenuHook::ShowMenuBar( bool bShow, bool bExpand )
{
  if (bShow)
  {
    if (bExpand)
    {
      m_expandBtn.SetVisible(false);
      m_closeBtn.SetVisible(true);
      m_functionBtn.SetVisible(true);
      m_shortcutBtn.SetVisible(true);
      m_aroundBtn.SetVisible(true);
      m_searchBtn.SetVisible(true);
      m_delimiter1.SetVisible(true);
      m_delimiter2.SetVisible(true);
      m_delimiter3.SetVisible(true);
    }
    else
    {
      m_expandBtn.SetVisible(true);
      m_closeBtn.SetVisible(false);
      m_functionBtn.SetVisible(false);
      m_shortcutBtn.SetVisible(false);
      m_aroundBtn.SetVisible(false);
      m_searchBtn.SetVisible(false);
      m_delimiter1.SetVisible(false);
      m_delimiter2.SetVisible(false);
      m_delimiter3.SetVisible(false);
    }
  }
  else
  {
    m_expandBtn.SetVisible(false);
    m_closeBtn.SetVisible(false);
    m_functionBtn.SetVisible(false);
    m_shortcutBtn.SetVisible(false);
    m_aroundBtn.SetVisible(false);
    m_searchBtn.SetVisible(false);
    m_delimiter1.SetVisible(false);
    m_delimiter2.SetVisible(false);
    m_delimiter3.SetVisible(false);
  }
}