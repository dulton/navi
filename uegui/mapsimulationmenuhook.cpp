#include "mapsimulationmenuhook.h"
#include "maphook.h"

using namespace UeGui;

CMapSimulationMenuHook::CMapSimulationMenuHook() : m_parentHook(NULL), m_routeWrapper(CRouteWrapper::Get()),
 m_speedIndex(0), m_simulationStatus(false), m_expandStatus(false)
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
      //����
      SlowlyDown();
    }
    break;
  case MapSimulationMenuHook_SpeedUpBtn:
  case MapSimulationMenuHook_SpeedUpLabel:
    {
      m_speedUpBtn.MouseUp();
      needRefresh = true;
      //����
      SpeedUp();
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
        m_routeWrapper.PauseDemo();
        m_simulationStatus = false;
        ResetSpeedBtnCaption();
      }
      else
      {
        //����ģ�⵼��
        m_routeWrapper.ResumeDemo(0);
        m_simulationStatus = true;
        ResetSpeedBtnCaption();
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
  m_expandStatus = bExpand;

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
    m_stopSimulation.SetVisible(true);
    //����������ؼ�״̬
    if (m_parentHook)
    {
      CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
      mapHook->ShowMinimizeBtn(true);      
      mapHook->ShowMapAzimuthBtn(true);
      mapHook->ShowMapScalingBtn(true);            
      mapHook->ShowDetailBtn1(true);
      mapHook->ShowDetailBtn2(false);
      mapHook->ShowGuideInfoBtn(false);
      mapHook->ShowAddElecEyeBtn(false); 
      mapHook->ShowSetDestPointBtn(false);
      mapHook->ShowFixedPostionBtn(false);
      //���������л���ʱ��
      mapHook->RestarGuiTimer();
    }  
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
    m_stopSimulation.SetVisible(false);
    //����������ؼ�״̬
    if (m_parentHook)
    {
      CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
      mapHook->ShowMinimizeBtn(false);
      mapHook->ShowAddElecEyeBtn(true);
      mapHook->ShowDetailBtn1(false);
      mapHook->ShowDetailBtn2(false);
      mapHook->ShowGuideInfoBtn(true);
      mapHook->ShowMapAzimuthBtn(false);
      mapHook->ShowMapScalingBtn(false);
      mapHook->ShowSetDestPointBtn(false);
      mapHook->ShowFixedPostionBtn(false);
      //���������л���ʱ��
      mapHook->CloseGuiTimer();
    }
  }
}

void UeGui::CMapSimulationMenuHook::Update()
{

}

void UeGui::CMapSimulationMenuHook::ReseSimulation()
{
  //��ǰ�ٶ�����
  m_speedIndex = 0;
  m_simulationStatus = true;
  ResetSpeedBtnStatus();
  ResetSpeedBtnCaption();
}

void UeGui::CMapSimulationMenuHook::SlowlyDown()
{
  if (m_speedIndex >= 1)
  {
    m_speedIndex--;
    m_routeWrapper.ResumeDemo(-1 * m_speedList[m_speedIndex].m_speed);
    m_speedLevelBtn.SetCaption(m_speedList[m_speedIndex].m_speedText);
    ResetSpeedBtnStatus();
  }
}

void UeGui::CMapSimulationMenuHook::SpeedUp()
{
  if (m_speedIndex < m_speedList.size() - 1)
  {
    m_speedIndex++;
    m_routeWrapper.ResumeDemo(m_speedList[m_speedIndex].m_speed);
    m_speedLevelBtn.SetCaption(m_speedList[m_speedIndex].m_speedText);
    ResetSpeedBtnStatus();
  }
}

void UeGui::CMapSimulationMenuHook::ResetSpeedBtnStatus()
{
  if ((m_speedIndex  > 0) && (m_speedIndex < m_speedList.size() - 1))
  {
    m_slowlyDownBtn.SetEnable(true);
    m_speedUpBtn.SetEnable(true);
    return;
  }

  if (m_speedIndex <= 0)
  {
    m_slowlyDownBtn.SetEnable(false);
  }

  if (m_speedIndex >= m_speedList.size() - 1)
  {
    m_speedUpBtn.SetEnable(false);
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
