#include "mapmenuhook.h"
#include "maphook.h"
//#include "mainmenuhook.h"
//#include "DistAndTypeHook.h"

using namespace UeGui;

CMapMenuHook::CMapMenuHook() : CAggHook()
{
  //�˵����ڵ�ͼ������Ⱦ��ɺ���Ҫ�ͷ�ͼƬ��Դ�����Ч��
  m_needReleasePic = false;

  m_menuType = MT_None;
  m_mapHook = NULL;
  m_route = NULL;
  MakeGUI();
  MakeMapMenu(MT_Default);

  //��ǰģ������
  m_demoSpeedIndex = 1;
  //ע�⣺ģ�⵼���ٶ�Ϊ��ǰ������ٶ�ֵ�����ϴδ�����ٶ���Ϊ��ǰģ���ٶ�
  DemoSpeedInfo speedInfo;
  speedInfo.m_speed = 0;
  ::strcpy(speedInfo.m_speedText, "��ͣ");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = -(5 * DEFAULT_DEMOSPEED);
  ::strcpy(speedInfo.m_speedText, "1X");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = DEFAULT_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "2X");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = 2 * DEFAULT_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "4X");
  m_speedList.push_back(speedInfo);
  speedInfo.m_speed = 2 * DEFAULT_DEMOSPEED;
  ::strcpy(speedInfo.m_speedText, "6X");
  m_speedList.push_back(speedInfo);
}

CMapMenuHook::~CMapMenuHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

tstring CMapMenuHook::GetBinaryFileName()
{
  return _T("mapmenuhook.bin");
}

bool CMapMenuHook::operator ()()
{
  return false;
}

void CMapMenuHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation1Left,	"Operation1Left"));  
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation1,	"Operation1"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation1Right,	"Operation1Right"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Delimiter1,	"Delimiter1"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation2,	"Operation2"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Delimiter2,	"Delimiter2"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation3,	"Operation3"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Delimiter3,	"Delimiter3"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation4,	"Operation4"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Delimiter4,	"Delimiter4"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation5,	"Operation5"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Delimiter5,	"Delimiter5"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation6,	"Operation6"));
  m_ctrlNames.insert(GuiName::value_type(MapMenuHook_Operation6Right,	"Operation6Right"));
}

void CMapMenuHook::MakeControls()
{
  m_delimiter1Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Delimiter1));
  m_delimiter2Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Delimiter2));
  m_delimiter3Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Delimiter3));
  m_delimiter4Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Delimiter4));
  m_delimiter5Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Delimiter5));

  m_operation1Ctrl.SetLeftElement(GetGuiElement(MapMenuHook_Operation1Left));
  m_operation1Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation1));
  m_operation1RightCtrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation1Right));
  m_operation2Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation2));
  m_operation3Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation3));
  m_operation4Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation4));
  m_operation5Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation5));
  m_operation6Ctrl.SetCenterElement(GetGuiElement(MapMenuHook_Operation6));
  m_operation6Ctrl.SetRightElement(GetGuiElement(MapMenuHook_Operation6Right));
}

void UeGui::CMapMenuHook::SetMapHook( CAggHook* mapHook )
{
  m_mapHook = mapHook;
}

void UeGui::CMapMenuHook::SetRoute( IRoute *route )
{
  m_route = route;
}

void UeGui::CMapMenuHook::InitOperationCtrls()
{
  m_operation1Ctrl.SetVisible(true);
  m_operation1Ctrl.SetEnable(false);

  m_operation1RightCtrl.SetVisible(false);
  m_operation1RightCtrl.SetEnable(false);

  m_operation2Ctrl.SetVisible(true);
  m_operation2Ctrl.SetEnable(false);

  m_operation3Ctrl.SetVisible(true);
  m_operation3Ctrl.SetEnable(false);

  m_operation4Ctrl.SetVisible(true);
  m_operation4Ctrl.SetEnable(false);

  m_operation5Ctrl.SetVisible(true);
  m_operation5Ctrl.SetEnable(false);

  m_operation6Ctrl.SetVisible(true);
  m_operation6Ctrl.SetEnable(false);

  m_delimiter1Ctrl.SetVisible(true);
  m_delimiter2Ctrl.SetVisible(true);
  m_delimiter3Ctrl.SetVisible(true);
  m_delimiter4Ctrl.SetVisible(true);
  m_delimiter5Ctrl.SetVisible(true);
}

void UeGui::CMapMenuHook::MakeMapMenu( MapMenuType menuType )
{
  //��ʼ���ؼ�״̬
  InitOperationCtrls();

  m_menuType = menuType;

  switch (menuType)
  {
  case MT_None:
    {
      //�޲����˵�����
      m_operation1Ctrl.ClearCaption();
      m_operation1 = MO_None;

      m_operation2Ctrl.ClearCaption();
      m_operation2 = MO_None;

      m_operation3Ctrl.ClearCaption();
      m_operation3 = MO_None;

      m_operation4Ctrl.ClearCaption();
      m_operation4 = MO_None;

      m_operation5Ctrl.ClearCaption();
      m_operation5 = MO_None;

      m_operation6Ctrl.ClearCaption();
      m_operation6 = MO_None;
      break;
    }
  case MT_Browse:
    {
      //Ĭ�ϲ˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(false);
      m_operation3Ctrl.SetCaption("");      
      m_operation3 = MO_None;

      m_operation4Ctrl.SetEnable(false);
      m_operation4Ctrl.SetCaption("");      
      m_operation4 = MO_None;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("�����");
      m_operation5 = MO_SetStartingPoint;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("�����");
      m_operation6 = MO_FindPlaceName;
      break;
    }
  case MT_Default:
    {
      //Ĭ�ϲ˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetCaption("");
      m_operation3 = MO_None;

      m_operation4Ctrl.SetEnable(true);
      m_operation4Ctrl.SetCaption("��Ŀ�ĵ�");
      m_operation4 = MO_SetDestinationPoint;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("�����");
      m_operation5 = MO_SetStartingPoint;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("�����");
      m_operation6 = MO_FindPlaceName;
      break;
    }
  case MT_RouteReady:
    {
      //����ѡ��˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("��ʼ����");
      m_operation2 = MO_StartRealGuidance;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      m_operation4Ctrl.SetCaption("��·��");
      m_operation4 = MO_MultiPath;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ģ�⵼��");
      m_operation5 = MO_StartDemoGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("ȡ��");
      m_operation6 = MO_Cancel;
      break;
    }
  case MT_RealGuidance:
    {
      //��ʼ�����˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      //m_operation4Ctrl.SetCaption("ӥ��ͼ");
      m_operation4Ctrl.SetCaption("");
      m_operation4 = MO_HawkEyeMap;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ֹͣ����");
      m_operation5 = MO_StopRealGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("�����");
      m_operation6 = MO_FindPlaceName;
      break;
    }
  case MT_RealGuidanceOpe:
    {
      //��ʼ�����˵�,�ɲ�����ͼ
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      m_operation4Ctrl.SetCaption("��Ŀ�ĵ�");
      m_operation4 = MO_SetDestinationPoint;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ֹͣ����");
      m_operation5 = MO_StopRealGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("�����");
      m_operation6 = MO_FindPlaceName;
      break;
    }
  case MT_DemoGuidance:
    {
      //ģ�⵼���˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      //m_operation4Ctrl.SetCaption("ӥ��ͼ");
      m_operation4Ctrl.SetCaption("");
      m_operation4 = MO_HawkEyeMap;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ֹͣģ��");
      m_operation5 = MO_StopDemoGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption(m_speedList[m_demoSpeedIndex].m_speedText);
      m_operation6 = MO_DemoSpeed;
      break;
    }
  case MT_DemoGuidanceOpe:
    {
      //ģ�⵼���˵����ɲ�����ͼ
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      m_operation4Ctrl.SetCaption("��Ŀ�ĵ�");
      m_operation4 = MO_SetDestinationPoint;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ֹͣģ��");
      m_operation5 = MO_StopDemoGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption(m_speedList[m_demoSpeedIndex].m_speedText);
      m_operation6 = MO_DemoSpeed;
      break;
    }
  case MT_MultiRoute:
    {
      //��·���鿴�˵�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("��ʼ����");
      m_operation2 = MO_StartRealGuidance;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetCaption("");
      m_operation4 = MO_None;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("ģ�⵼��");
      m_operation5 = MO_StartDemoGuidance;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("ȡ��");
      m_operation6 = MO_Cancel;
      break;
    }
  case MT_ResetRoute:
    {
      //����·�߲˵����Ѿ��滮��·�ߣ���������������͵���·�ߣ�
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.SetEnable(true);
      m_operation2Ctrl.SetCaption("�ܱ���Ϣ");
      m_operation2 = MO_SurroundInfo;

      m_operation3Ctrl.SetEnable(true);
      m_operation3Ctrl.SetCaption("·�߲���");
      m_operation3 = MO_RouteOperation;

      m_operation4Ctrl.SetEnable(true);
      m_operation4Ctrl.SetCaption("��Ŀ�ĵ�");
      m_operation4 = MO_SetDestinationPoint;

      m_operation5Ctrl.SetEnable(true);
      m_operation5Ctrl.SetCaption("�����");
      m_operation5 = MO_SetStartingPoint;

      m_operation6Ctrl.SetEnable(true);
      m_operation6Ctrl.SetCaption("�����");
      m_operation6 = MO_FindPlaceName;
      
      //������ڵ����������������Ͳ����
      if (m_route)
      {
        short planState = m_route->GetPlanState();
        if (UeRoute::PS_RealGuidance == planState)
        {
          //m_operation5Ctrl.SetEnable(false);
          m_operation5Ctrl.SetCaption("ֹͣ����");
          m_operation5 = MO_StopRealGuidance;
          //m_operation6Ctrl.SetEnable(false);
        }
        else if (UeRoute::PS_DemoGuidance == planState)
        {
          m_operation5Ctrl.SetCaption("ֹͣģ��");
          m_operation5 = MO_StopDemoGuidance;
        }
      }
      break;
    }
  case MT_OnlyMenu:
    {
      //ֻ�в˵���ť
      m_operation1Ctrl.SetEnable(true);
      m_operation1Ctrl.SetCaption("�˵�");
      m_operation1RightCtrl.SetVisible(true);
      m_operation1RightCtrl.SetEnable(true);
      m_operation1 = MO_OpenMenu;

      m_operation2Ctrl.ClearCaption();
      m_operation2Ctrl.SetVisible(false);
      m_operation2 = MO_None;

      m_operation3Ctrl.ClearCaption();
      m_operation3Ctrl.SetVisible(false);
      m_operation3 = MO_None;

      m_operation4Ctrl.ClearCaption();
      m_operation4Ctrl.SetVisible(false);
      m_operation4 = MO_None;

      m_operation5Ctrl.ClearCaption();
      m_operation5Ctrl.SetVisible(false);
      m_operation5 = MO_None;

      m_operation6Ctrl.ClearCaption();
      m_operation6Ctrl.SetVisible(false);
      m_operation6 = MO_None;

      m_delimiter1Ctrl.SetVisible(false);
      m_delimiter2Ctrl.SetVisible(false);
      m_delimiter3Ctrl.SetVisible(false);
      m_delimiter4Ctrl.SetVisible(false);
      m_delimiter5Ctrl.SetVisible(false);
      break;
    }
  }
}

short CMapMenuHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseDown(scrPoint);

  CMapHook* mapHook = dynamic_cast<CMapHook*>(m_mapHook);
  if (mapHook->InterfaceNotOperable())
  {
    return ctrlType;
  }

  switch(ctrlType)
  {
  case MapMenuHook_Operation1:
  case MapMenuHook_Operation1Left:
  case MapMenuHook_Operation1Right:
    {
      needRefresh = m_operation1Ctrl.IsEnable();
      m_operation1Ctrl.MouseDown();
      m_operation1RightCtrl.MouseDown();
    }
    break;
  case MapMenuHook_Operation2:
    {
      needRefresh = m_operation2Ctrl.IsEnable();
      m_operation2Ctrl.MouseDown();
    }
    break;
  case MapMenuHook_Operation3:
    {
      needRefresh = m_operation3Ctrl.IsEnable();
      m_operation3Ctrl.MouseDown();
    }
    break;
  case MapMenuHook_Operation4:
    {
      needRefresh = m_operation4Ctrl.IsEnable();
      m_operation4Ctrl.MouseDown();
    }
    break;
  case MapMenuHook_Operation5:
    {
      needRefresh = m_operation5Ctrl.IsEnable();
      m_operation5Ctrl.MouseDown();
    }
    break;
  case MapMenuHook_Operation6:
  case MapMenuHook_Operation6Right:
    {
      needRefresh = m_operation6Ctrl.IsEnable();
      m_operation6Ctrl.MouseDown();
    }
    break;
  default:
    assert(false);
    break;
  }
  if (needRefresh)
  {
    Refresh();
  }
  return ctrlType;
}

short CMapMenuHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CMapMenuHook::MouseUp(CGeoPoint<short> &scrPoint)
{  
  short ctrlType = CAggHook::MouseUp(scrPoint);

  CMapHook* mapHook = dynamic_cast<CMapHook*>(m_mapHook);
  if (mapHook->InterfaceNotOperable())
  {
    return ctrlType;
  }

  bool needRefresh = false;
  //�������ȥ�ĺ͵���İ�ťʱͬһ�����������
  bool needDo = ctrlType == m_downElementType;
  MapMenuOperation opeType = MO_None;

  switch(m_downElementType)
  {
  case MapMenuHook_Operation1:
  case MapMenuHook_Operation1Left:
  case MapMenuHook_Operation1Right:
    {
      needRefresh = m_operation1Ctrl.IsEnable();
      m_operation1Ctrl.MouseUp();
      m_operation1RightCtrl.MouseUp();
      if (needDo && m_operation1Ctrl.IsEnable())
      {
        opeType = m_operation1;
      }
    }
    break;
  case MapMenuHook_Operation2:
    {
      needRefresh = m_operation2Ctrl.IsEnable();
      m_operation2Ctrl.MouseUp();
      if (needDo && m_operation2Ctrl.IsEnable())
      {
        opeType = m_operation2;        
      }
    }
    break;
  case MapMenuHook_Operation3:
    {
      needRefresh = m_operation3Ctrl.IsEnable();
      m_operation3Ctrl.MouseUp();
      if (needDo && m_operation3Ctrl.IsEnable())
      {        
        opeType = m_operation3;
      }
    }
    break;
  case MapMenuHook_Operation4:
    {
      needRefresh = m_operation4Ctrl.IsEnable();
      m_operation4Ctrl.MouseUp();
      if (needDo && m_operation4Ctrl.IsEnable())
      {        
        opeType = m_operation4;
      }
    }
    break;
  case MapMenuHook_Operation5:
    {
      needRefresh = m_operation5Ctrl.IsEnable();
      m_operation5Ctrl.MouseUp();
      if (needDo && m_operation5Ctrl.IsEnable())
      {        
        opeType = m_operation5;
      }
    }
    break;
  case MapMenuHook_Operation6:
  case MapMenuHook_Operation6Right:
    {
      needRefresh = m_operation6Ctrl.IsEnable();
      m_operation6Ctrl.MouseUp();
      if (needDo && m_operation6Ctrl.IsEnable())
      {
        if (MT_DemoGuidance == m_menuType)
        {
          UpdateDemoGuidanceSpeed();
        }        
        opeType = m_operation6;
      }
    }
    break;
  default:
    assert(false);
    break;
  }

  //�Ƿ��������
  if(opeType == MO_SetStartingPoint)
  {
    UeRoute::PlanResultDesc desc;
    //����Ѿ��滮��·�ߣ���ˢ�µ�ͼȥ��·�ߺۼ�
    if (m_route->GetPlanState() != UeRoute::PS_None && m_route->GetPlanResultDesc(desc))
    {
      //����ѡ�������ִ�в���
      DoOperation(opeType);
      m_view->Refresh();
      return ctrlType;
    }
  }
  else if (opeType == MO_MultiPath)
  {
    DoOperation(opeType);
    m_view->Refresh();
    return ctrlType;
  }

  //����ѡ�������ִ�в���
  DoOperation(opeType);
  //��ˢ�½��棬��ִ�в�������Ϊִ�в��������п��ܻ�ˢ�½��棬���絯���Ի����
  //�����DoOperation������ܻ����ִ����ɺ���ˢ��һ�ν���
  if (needRefresh)
  {
    Refresh();
  }
  return ctrlType;
}

void UeGui::CMapMenuHook::DoOperation( MapMenuOperation operation )
{
  if (NULL == m_mapHook)
  {
    return;
  }

  CMapHook* mapHook = dynamic_cast<CMapHook*>(m_mapHook);

  switch (operation)
  {
  case MO_OpenMenu:
    {
      //�򿪲˵�
      mapHook->OpenMainMenu();
      break;
    }
  case MO_SurroundInfo:
    {
      //�ܱ���Ϣ
      mapHook->OpenGridQuery();
      break;
    }
  case MO_RouteOperation:
    {
      //·�߲���
      mapHook->RouteOperation();
      break;
    }
  case MO_MultiPath:
    {
      //��·��
      mapHook->OpenMultiRoutePath();
      MakeMapMenu(MT_MultiRoute);
      break;
    }
  case MO_SetStartingPoint:
    {
      //�����
      mapHook->SetRouteStart();
      break;
    }
  case MO_SetDestinationPoint:
    {
      //��Ŀ�ĵ�

      mapHook->SetRouteEndB();    
      break;
    }
  case MO_StartRealGuidance:
    {
      //��ʼ����
      mapHook->DoRouteGuidance();
      break;
    }
  case MO_StopRealGuidance:
    {
      //ֹͣ����
      mapHook->DoRouteStopGuidance();
      break;
    }
  case MO_StartDemoGuidance:
    {
      //ģ�⵼��
      mapHook->DoDemoStart();
      break;
    }
  case MO_StopDemoGuidance:
    {
      //ֹͣģ��
      mapHook->DoDemoStop(); 
      break;
    }
  case MO_DemoSpeed:
    {
      //ģ�⵼���ٶ�ѡ��:1X,2X,3X,4X,,6X,��ͣ
      mapHook->SetDemoGuidanceSpeed(m_speedList[m_demoSpeedIndex].m_speed);
      break;
    }
  case MO_HawkEyeMap:
    {
      //ӥ��ͼ ��ʱȥ��
      //mapHook->HawkEyeMap();
      break;
    }
  case MO_FindPlaceName:
    {
      //�ҵط�
      mapHook->FindPlaceName();
      break;
    }
  case MO_Cancel:
    {
      //ȡ��
      mapHook->DoRouteCancel();
      break;
    }
  }
}

void UeGui::CMapMenuHook::UpdateDemoGuidanceSpeed()
{
  if (m_demoSpeedIndex < m_speedList.size() - 1)
  {
    ++m_demoSpeedIndex;
  }
  else
  {
    m_demoSpeedIndex = 0;
  }
  m_operation6Ctrl.SetCaption(m_speedList[m_demoSpeedIndex].m_speedText);
}

void UeGui::CMapMenuHook::InitDemoSpeed()
{
  m_demoSpeedIndex = 1;
}
