#include "mapsimulationmenuhook.h"
#include "maphook.h"

using namespace UeGui;

CMapSimulationMenuHook::CMapSimulationMenuHook() : m_parentHook(NULL), m_routeWrapper(CRouteWrapper::Get()),
m_viewWrapper(CViewWrapper::Get()), m_speedIndex(0), m_simulationStatus(false), m_expandStatus(false)
{
  //��ͼ������Ⱦ��ɺ���Ҫ�ͷ�ͼƬ��Դ�����Ч��
  m_needReleasePic = false;
  //ע�⣺ģ�⵼���ٶ�Ϊ��ǰ������ٶ�ֵ�����ϴδ�����ٶ���Ϊ��ǰģ���ٶ�
  SpeedInfo speedInfo;
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "30 km/h");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "60 km/h");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "90 km/h");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "120 km/h");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "150 km/h");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = INITIAL_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "180 km/h");
  m_speedList.push_back(speedInfo);
}

CMapSimulationMenuHook::~CMapSimulationMenuHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

bool CMapSimulationMenuHook::operator ()()
{
  return false;
}

void UeGui::CMapSimulationMenuHook::Show( bool show /*= true */ )
{
  CAggHook::Show(show);
  if (show)
  {
    ExpandMenu(false);
  }  
}

tstring CMapSimulationMenuHook::GetBinaryFileName()
{
  return _T("mapsimulationmenuhook.bin");
}

void CMapSimulationMenuHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_ExpandBtn,	"ExpandBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_CloseBtn,	"CloseBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SlowlyDownBtn,	"SlowlyDownBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SlowlyDownLabel,	"SlowlyDownLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_Delimiter1,	"Delimiter1"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SpeedLevelBtn,	"SpeedLevelBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SpeedLevelLabel,	"SpeedLevelLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_Delimiter2,	"Delimiter2"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SpeedUpBtn,	"SpeedUpBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_SpeedUpLabel,	"SpeedUpLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_Delimiter3,	"Delimiter3"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_PauseBtn,	"PauseBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_PauseLabel,	"PauseLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_PauseBtnR,	"PauseBtnR"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_StopSimulationBtn,	"StopSimulationBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapSimulationMenuHook_StopSimulationLabel,	"StopSimulationLabel"));
}

void CMapSimulationMenuHook::MakeControls()
{
  //չ���˵���ť
  m_expandBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_ExpandBtn));
  //�رղ˵���ť
  m_closeBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_CloseBtn));
  //����
  m_slowlyDownBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_SlowlyDownBtn));
  m_slowlyDownBtn.SetLabelElement(GetGuiElement(MapSimulationMenuHook_SlowlyDownLabel));
  //��ǰ�ٶ�
  m_speedLevelBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_SpeedLevelBtn));
  m_speedLevelBtn.SetLabelElement(GetGuiElement(MapSimulationMenuHook_SpeedLevelLabel));
  //����
  m_speedUpBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_SpeedUpBtn));
  m_speedUpBtn.SetLabelElement(GetGuiElement(MapSimulationMenuHook_SpeedUpLabel));
  //��ͣ
  m_pauseBtn.SetCenterElement(GetGuiElement(MapSimulationMenuHook_PauseBtn));
  m_pauseBtn.SetRightElement(GetGuiElement(MapSimulationMenuHook_PauseBtnR));
  m_pauseBtn.SetLabelElement(GetGuiElement(MapSimulationMenuHook_PauseLabel));
  //ֹͣģ��
  m_stopSimulation.SetCenterElement(GetGuiElement(MapSimulationMenuHook_StopSimulationBtn));
  m_stopSimulation.SetLabelElement(GetGuiElement(MapSimulationMenuHook_StopSimulationLabel));
  //�ָ��
  m_delimiter1.SetCenterElement(GetGuiElement(MapSimulationMenuHook_Delimiter1));;
  m_delimiter2.SetCenterElement(GetGuiElement(MapSimulationMenuHook_Delimiter2));
  m_delimiter3.SetCenterElement(GetGuiElement(MapSimulationMenuHook_Delimiter3));
}

short CMapSimulationMenuHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case MapSimulationMenuHook_ExpandBtn:
    {
      m_expandBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapSimulationMenuHook_CloseBtn:
    {
      m_closeBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapSimulationMenuHook_SlowlyDownBtn:
  case MapSimulationMenuHook_SlowlyDownLabel:
    {
      m_slowlyDownBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapSimulationMenuHook_SpeedUpBtn:
  case MapSimulationMenuHook_SpeedUpLabel:
    {
      m_speedUpBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapSimulationMenuHook_PauseBtn:
  case MapSimulationMenuHook_PauseBtnR:
  case MapSimulationMenuHook_PauseLabel:
    {
      m_pauseBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapSimulationMenuHook_StopSimulationBtn:
  case MapSimulationMenuHook_StopSimulationLabel:
    {
      m_stopSimulation.MouseDown();
      needRefresh = true;
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

short CMapSimulationMenuHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CMapSimulationMenuHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(ctrlType)
  {
  case MapSimulationMenuHook_ExpandBtn:
    {
      m_expandBtn.MouseUp();
      needRefresh = true;
      ExpandMenu(true);
    }
    break;
  case MapSimulationMenuHook_CloseBtn:
    {
      m_closeBtn.MouseUp();
      needRefresh = true;
      ExpandMenu(false);
    }
    break;
  case MapSimulationMenuHook_SlowlyDownBtn:
  case MapSimulationMenuHook_SlowlyDownLabel:
    {
      m_slowlyDownBtn.MouseUp();
      needRefresh = true;
      if (m_slowlyDownBtn.IsEnable())
      {
        //����
        SlowlyDown();
      }
    }
    break;
  case MapSimulationMenuHook_SpeedUpBtn:
  case MapSimulationMenuHook_SpeedUpLabel:
    {
      m_speedUpBtn.MouseUp();
      needRefresh = true;
      if (m_speedUpBtn.IsEnable())
      {
        //����
        SpeedUp();
      }
    }
    break;
  case MapSimulationMenuHook_PauseBtn:
  case MapSimulationMenuHook_PauseBtnR:
  case MapSimulationMenuHook_PauseLabel:
    {
      m_pauseBtn.MouseUp();
      needRefresh = true;
      if (m_simulationStatus)
      {
        //��ͣģ�⵼��
        if (UeRoute::PEC_Success == m_routeWrapper.PauseDemo())
        {
          m_simulationStatus = false;
          ResetSpeedBtnCaption();
        }
      }
      else
      {
        //����ģ�⵼��
        if (UeRoute::PEC_Success == m_routeWrapper.ResumeDemo(0))
        {
          m_simulationStatus = true;
          ResetSpeedBtnCaption();
        }        
      }
    }
    break;
  case MapSimulationMenuHook_StopSimulationBtn:
  case MapSimulationMenuHook_StopSimulationLabel:
    {
      m_stopSimulation.MouseUp();
      needRefresh = true;
      //ֹͣģ�⵼��
      if (m_parentHook)
      {
        CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
        mapHook->StopDemo();
        m_simulationStatus = false;
      }
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

void UeGui::CMapSimulationMenuHook::SetParentHook( CAggHook* parentHook )
{
  m_parentHook = parentHook;
}

void UeGui::CMapSimulationMenuHook::ExpandMenu( bool bExpand /*= true*/ )
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
  //���浱ǰ�˵�չ��״̬
  m_expandStatus = bExpand;
  //��ȡ��ǰ�滮״̬
  short planState = m_routeWrapper.GetPlanState();
  if (bExpand)
  {    
    //���������л���ʱ��
    mapHook->RestarGuiTimer();
    mapHook->ShowMinimizeBtn();      
    mapHook->ShowMapAzimuthBtn();
    mapHook->ShowMapScalingBtn();
    mapHook->ShowDetailBtn2(false);
    mapHook->ShowGuideInfoBtn(false);
    mapHook->ShowAddElecEyeBtn(false); 
    mapHook->ShowSetDestPointBtn(false);
    mapHook->ShowFixedPostionBtn(false);
    mapHook->ShowCompass(false);
    mapHook->ShowElecEye(false);
    mapHook->RefreshSrcModalBtnStatus();
    
    //�Ƿ��Ƿ���״̬
    if (mapHook->IsSplitScreen())
    {
      //���ز˵���
      ShowMenuBar(false, bExpand);
      mapHook->ShowDetailBtn1(false);
      mapHook->ShowTimeBtn(false);
    }
    else
    {
      //��ʾ�˵���
      ShowMenuBar(true, bExpand);
      mapHook->ShowDetailBtn1();
      if (m_viewWrapper.IsNeedRenderGuidanceView())
      {
        mapHook->ShowTimeBtn(false);
      }
      else
      {
        mapHook->ShowTimeBtn();
      }        
    }
    m_stopSimulation.SetVisible(true);
  }
  else
  {
    //���������л���ʱ��
    mapHook->CloseGuiTimer();
    mapHook->ShowMinimizeBtn(false);
    mapHook->ShowAddElecEyeBtn();
    mapHook->ShowDetailBtn1(false);
    mapHook->ShowDetailBtn2(false);
    mapHook->ShowMapAzimuthBtn(false);
    mapHook->ShowMapScalingBtn(false);
    mapHook->ShowSetDestPointBtn(false);
    mapHook->ShowFixedPostionBtn(false);
    //����Ƿ��е�������ʾ
    if (mapHook->HaveElecEyePrompt())
    {
      mapHook->ShowElecEye();
      mapHook->ShowCompass(false);
    }
    else
    {
      mapHook->ShowElecEye(false);
      mapHook->ShowCompass();
    }      
    //�Ƿ��Ƿ���״̬
    if (mapHook->IsSplitScreen())
    {
      //���ز˵�
      ShowMenuBar(false, bExpand);
      mapHook->ShowGuideInfoBtn(false);
      mapHook->ShowTimeBtn(false);
    }
    else
    {
      //��ʾ�˵���
      ShowMenuBar(true, bExpand);
      mapHook->ShowGuideInfoBtn();
      if (m_viewWrapper.IsNeedRenderGuidanceView())
      {
        mapHook->ShowTimeBtn(false);
      }
      else
      {
        mapHook->ShowTimeBtn();
      }   
    }
    m_stopSimulation.SetVisible(false);
  }
}

void UeGui::CMapSimulationMenuHook::Update( short type )
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
  //��ȡ��ǰ�滮״̬
  short planState = m_routeWrapper.GetPlanState();
  if (m_expandStatus)
  {
    //�Ƿ��Ƿ���״̬
    if (mapHook->IsSplitScreen())
    {
      //���ز˵�
      ShowMenuBar(false, m_expandStatus);
      mapHook->ShowDetailBtn1(false);
      mapHook->ShowTimeBtn(false);
    }
    else
    {
      //��ʾ�˵���
      ShowMenuBar(true, m_expandStatus);
      mapHook->ShowDetailBtn1();
      if (m_viewWrapper.IsNeedRenderGuidanceView())
      {
        mapHook->ShowTimeBtn(false);
      }
      else
      {
        mapHook->ShowTimeBtn();
      } 
    }
    mapHook->RefreshSrcModalBtnStatus();
  }
  else
  {
    //����Ƿ��е�������ʾ
    if (mapHook->HaveElecEyePrompt())
    {
      mapHook->ShowElecEye();
      mapHook->ShowCompass(false);
    }
    else
    {
      mapHook->ShowElecEye(false);
      mapHook->ShowCompass();
    }      
    //�Ƿ��Ƿ���״̬
    if (mapHook->IsSplitScreen())
    {
      //���ز˵�
      ShowMenuBar(false, m_expandStatus);
      mapHook->ShowGuideInfoBtn(false);
      mapHook->ShowTimeBtn(false);
    }
    else
    {
      //��ʾ�˵���
      ShowMenuBar(true, m_expandStatus);
      mapHook->ShowGuideInfoBtn();
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
}

void UeGui::CMapSimulationMenuHook::ShowMenuBar( bool bShow, bool bExpand )
{
  if (bShow)
  {
    if (bExpand)
    {
      //չ���˵�
      m_expandBtn.SetVisible(false);
      m_closeBtn.SetVisible(true);
      m_slowlyDownBtn.SetVisible(true);
      m_speedLevelBtn.SetVisible(true);
      m_speedUpBtn.SetVisible(true);
      m_pauseBtn.SetVisible(true);    
      m_delimiter1.SetVisible(true);
      m_delimiter2.SetVisible(true);
      m_delimiter3.SetVisible(true);
    }
    else
    {
      //�����˵�
      m_expandBtn.SetVisible(true);
      m_closeBtn.SetVisible(false);
      m_slowlyDownBtn.SetVisible(false);
      m_speedLevelBtn.SetVisible(false);
      m_speedUpBtn.SetVisible(false);
      m_pauseBtn.SetVisible(false);    
      m_delimiter1.SetVisible(false);
      m_delimiter2.SetVisible(false);
      m_delimiter3.SetVisible(false);
    }
  }
  else
  {
    //���ز˵�
    m_expandBtn.SetVisible(false);
    m_closeBtn.SetVisible(false);
    m_slowlyDownBtn.SetVisible(false);
    m_speedLevelBtn.SetVisible(false);
    m_speedUpBtn.SetVisible(false);
    m_pauseBtn.SetVisible(false);    
    m_delimiter1.SetVisible(false);
    m_delimiter2.SetVisible(false);
    m_delimiter3.SetVisible(false);
  }
}

void UeGui::CMapSimulationMenuHook::ReseSimulation()
{
  //��ǰ�ٶ�����
  m_speedIndex = 0;
  m_simulationStatus = true;
  RefreshSpeedLabel();
  ResetSpeedBtnStatus();
  ResetSpeedBtnCaption();
}

void UeGui::CMapSimulationMenuHook::SlowlyDown()
{
  if (m_speedIndex >= 1)
  {
    m_speedIndex--;
    m_routeWrapper.ResumeDemo(-1 * m_speedList[m_speedIndex].m_speed);
    if (!m_simulationStatus)
    {
      m_routeWrapper.PauseDemo();
    }
    RefreshSpeedLabel();
    ResetSpeedBtnStatus();
  }
}

void UeGui::CMapSimulationMenuHook::SpeedUp()
{
  if (m_speedIndex < m_speedList.size() - 1)
  {
    m_speedIndex++;
    m_routeWrapper.ResumeDemo(m_speedList[m_speedIndex].m_speed);
    if (!m_simulationStatus)
    {
      m_routeWrapper.PauseDemo();
    }
    RefreshSpeedLabel();
    ResetSpeedBtnStatus();
  }
}

void UeGui::CMapSimulationMenuHook::ResetSpeedBtnStatus()
{
  if (m_speedIndex <= 0)
  {
    m_slowlyDownBtn.SetEnable(false);
  }
  else if (m_speedIndex  > 0)
  {
    m_slowlyDownBtn.SetEnable(true);
  }
 

  if (m_speedIndex >= m_speedList.size() - 1)
  {
    m_speedUpBtn.SetEnable(false);
  }
  else if (m_speedIndex < m_speedList.size() - 1)
  {
    m_speedUpBtn.SetEnable(true);
  }
}

void UeGui::CMapSimulationMenuHook::ResetSpeedBtnCaption()
{
  if (m_simulationStatus)
  {
    m_pauseBtn.SetCaption("��ͣ");
  }
  else
  {
    m_pauseBtn.SetCaption("����");
  }
}

void UeGui::CMapSimulationMenuHook::RefreshSpeedLabel()
{
  if ((m_speedIndex >= 0) && (m_speedIndex <= m_speedList.size() - 1))
  {
    m_speedLevelBtn.SetCaption(m_speedList[m_speedIndex].m_speedText);
  }  
}