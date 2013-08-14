#include "mapguideinfoviewhook.h"
#include "maphook.h"
#include "ueroute\routebasic.h"
#include "uebase\vectop.h"

using namespace UeGui;

CMapGuideInfoViewHook::CMapGuideInfoViewHook() : m_parentHook(NULL), m_routeWrapper(CRouteWrapper::Get()),
m_viewWrapper(CViewWrapper::Get()), m_isShowRouteGuideList(false), m_isShowHightSpeedBoard(false)
{
  //��ͼ������Ⱦ��ɺ���Ҫ�ͷ�ͼƬ��Դ�����Ч��
  m_needReleasePic = false;
}

CMapGuideInfoViewHook::~CMapGuideInfoViewHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

tstring CMapGuideInfoViewHook::GetBinaryFileName()
{
  return _T("mapguideinfoviewhook.bin");
}

bool CMapGuideInfoViewHook::operator ()()
{
  return false;
}

void UeGui::CMapGuideInfoViewHook::Show( bool show /*= true */ )
{
  CAggHook::Show(show);
  if (show)
  {
    Update(0);
  }
}

void CMapGuideInfoViewHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteInfoBtn,	"RouteInfoBtn"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteInfoIcon,	"RouteInfoIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteInfoLabel,	"RouteInfoLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_CurDirectionBoard,	"CurDirectionBoard"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_CurDirectionBoardIcon,	"CurDirectionBoardIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_DistInfoLabel,	"DistInfoLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_NextDirectionBoard,	"NextDirectionBoard"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_NextDirectionBoardIcon,	"NextDirectionBoardIcon"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardBack1,	"HighSpeedBoardBack1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardNameLabel1,	"HighSpeedBoardNameLabel1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardTypeLabel1,	"HighSpeedBoardTypeLabel1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardDistLabel1,	"HighSpeedBoardDistLabel1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardBack2,	"HighSpeedBoardBack2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardNameLabel2,	"HighSpeedBoardNameLabel2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardTypeLabel2,	"HighSpeedBoardTypeLabel2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardDistLabel2,	"HighSpeedBoardDistLabel2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardBack3,	"HighSpeedBoardBack3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardNameLabel3,	"HighSpeedBoardNameLabel3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardTypeLabel3,	"HighSpeedBoardTypeLabel3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_HighSpeedBoardDistLabel3,	"HighSpeedBoardDistLabel3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_ShowGuideViewBack,	"ShowGuideViewBack"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_ShowGuideViewLabel,	"ShowGuideViewLabel"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideBack,	"RouteGuideBack"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideCurName,	"RouteGuideCurName"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideIcon1,	"RouteGuideIcon1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideIcon2,	"RouteGuideIcon2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideIcon3,	"RouteGuideIcon3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideIcon4,	"RouteGuideIcon4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideName1,	"RouteGuideName1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideName2,	"RouteGuideName2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideName3,	"RouteGuideName3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideName4,	"RouteGuideName4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideDist1,	"RouteGuideDist1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideDist2,	"RouteGuideDist2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideDist3,	"RouteGuideDist3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_RouteGuideDist4,	"RouteGuideDist4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType1_1,	"IconType1_1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType1_2,	"IconType1_2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType1_3,	"IconType1_3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType1_4,	"IconType1_4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType1_5,	"IconType1_5"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_1,	"IconType2_1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_2,	"IconType2_2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_3,	"IconType2_3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_4,	"IconType2_4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_5,	"IconType2_5"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_6,	"IconType2_6"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_7,	"IconType2_7"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_8,	"IconType2_8"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_9,	"IconType2_9"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_10,	"IconType2_10"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_11,	"IconType2_11"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_12,	"IconType2_12"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_13,	"IconType2_13"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_14,	"IconType2_14"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_15,	"IconType2_15"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_16,	"IconType2_16"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_17,	"IconType2_17"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_18,	"IconType2_18"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_19,	"IconType2_19"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_20,	"IconType2_20"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_21,	"IconType2_21"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_22,	"IconType2_22"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_23,	"IconType2_23"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_24,	"IconType2_24"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_25,	"IconType2_25"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_26,	"IconType2_26"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_27,	"IconType2_27"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType2_28,	"IconType2_28"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType3_1,	"IconType3_1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType3_2,	"IconType3_2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType3_3,	"IconType3_3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType3_4,	"IconType3_4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType3_5,	"IconType3_5"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_1,	"IconType4_1"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_2,	"IconType4_2"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_3,	"IconType4_3"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_4,	"IconType4_4"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_5,	"IconType4_5"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_6,	"IconType4_6"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_7,	"IconType4_7"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_8,	"IconType4_8"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_9,	"IconType4_9"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_10,	"IconType4_10"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_11,	"IconType4_11"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_12,	"IconType4_12"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_13,	"IconType4_13"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_14,	"IconType4_14"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_15,	"IconType4_15"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_16,	"IconType4_16"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_17,	"IconType4_17"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_18,	"IconType4_18"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_19,	"IconType4_19"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_20,	"IconType4_20"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_21,	"IconType4_21"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_22,	"IconType4_22"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_23,	"IconType4_23"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_24,	"IconType4_24"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_25,	"IconType4_25"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_26,	"IconType4_26"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_27,	"IconType4_27"));
  m_ctrlNames.insert(GuiName::value_type(MapGuideInfoViewHook_IconType4_28,	"IconType4_28"));
}

void CMapGuideInfoViewHook::MakeControls()
{
  m_routeInfoBtn.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteInfoBtn));
  m_routeInfoBtn.SetIconElement(GetGuiElement(MapGuideInfoViewHook_RouteInfoIcon));
  m_routeInfoBtn.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteInfoLabel));
  m_curDirectionBoard.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_CurDirectionBoard));
  m_curDirectionBoard.SetIconElement(GetGuiElement(MapGuideInfoViewHook_CurDirectionBoardIcon));
  m_curDirectionBoard.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_DistInfoLabel));
  m_nextDirectionBoard.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_NextDirectionBoard));
  m_nextDirectionBoard.SetIconElement(GetGuiElement(MapGuideInfoViewHook_NextDirectionBoardIcon));
  //���ٿ���
  m_highSpeedBoard1.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardBack1));
  m_highSpeedBoard1.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardNameLabel1));
  m_highSpeedBoard2.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardBack2));
  m_highSpeedBoard2.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardNameLabel2));
  m_highSpeedBoard3.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardBack3));
  m_highSpeedBoard3.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardNameLabel3));
  m_highSpeedBoardTypeLabel1.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardTypeLabel1));
  m_highSpeedBoardTypeLabel2.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardTypeLabel2));
  m_highSpeedBoardTypeLabel3.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardTypeLabel3));
  m_highSpeedBoardDistLabel1.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardDistLabel1));
  m_highSpeedBoardDistLabel2.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardDistLabel2));
  m_highSpeedBoardDistLabel3.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_HighSpeedBoardDistLabel3));
  //��ʾ����·�ڷŴ�ͼ
  m_shwoGuideViewBtn.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_ShowGuideViewBack));
  m_shwoGuideViewBtn.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_ShowGuideViewLabel));
  //����·��
  m_routeGuideBack.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideBack));
  m_routeGuideCurName.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideCurName));
  m_routeGuideName1.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideName1));
  m_routeGuideName2.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideName2));
  m_routeGuideName3.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideName3));
  m_routeGuideName4.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideName4));
  m_routeGuideDist1.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideDist1));
  m_routeGuideDist2.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideDist2));
  m_routeGuideDist3.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideDist3));
  m_routeGuideDist4.SetLabelElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideDist4));
  m_routeGuideIcon1.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideIcon1));
  m_routeGuideIcon2.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideIcon2));
  m_routeGuideIcon3.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideIcon3));
  m_routeGuideIcon4.SetCenterElement(GetGuiElement(MapGuideInfoViewHook_RouteGuideIcon4));
}

void UeGui::CMapGuideInfoViewHook::SetParentHook( CAggHook* parentHook )
{
  m_parentHook = parentHook;
}

void UeGui::CMapGuideInfoViewHook::SetIsShowRouteGuideList( bool show )
{
  m_isShowRouteGuideList = show;
}

void UeGui::CMapGuideInfoViewHook::SetIsShowHightSpeedBoard( bool show )
{
  m_isShowHightSpeedBoard = show;
}

short CMapGuideInfoViewHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case MapGuideInfoViewHook_RouteInfoBtn:
  case MapGuideInfoViewHook_RouteInfoIcon:
  case MapGuideInfoViewHook_RouteInfoLabel:
    {
      //��һ��·����
      m_routeInfoBtn.MouseDown();
      needRefresh = true;
    }
    break;
  case MapGuideInfoViewHook_CurDirectionBoard:
  case MapGuideInfoViewHook_CurDirectionBoardIcon:
  case MapGuideInfoViewHook_DistInfoLabel:
    {
      needRefresh = true;
      //m_curDirectionBoard.MouseDown();
    }
    break;
  case MapGuideInfoViewHook_ShowGuideViewBack:
  case MapGuideInfoViewHook_ShowGuideViewLabel:
    {
      m_shwoGuideViewBtn.MouseDown();
      needRefresh = true;
    }
    break;
  }
  if (needRefresh)
  {
    this->Refresh();
  }
  return ctrlType;
}

short CMapGuideInfoViewHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CMapGuideInfoViewHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  //�Ƿ���Ҫˢ��
  bool needRefresh = false;
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(ctrlType)
  {
  case MapGuideInfoViewHook_RouteInfoBtn:
  case MapGuideInfoViewHook_RouteInfoIcon:
  case MapGuideInfoViewHook_RouteInfoLabel:
    {
      //��һ��·����
      m_routeInfoBtn.MouseUp();
      needRefresh = true;
      TurnTo(DHT_PassedRouteHook);
    }
    break;
  case MapGuideInfoViewHook_CurDirectionBoard:
  case MapGuideInfoViewHook_CurDirectionBoardIcon:
  case MapGuideInfoViewHook_DistInfoLabel:
    {
      needRefresh = true;
      //m_curDirectionBoard.MouseUp();
    }
    break;
  case MapGuideInfoViewHook_ShowGuideViewBack:
  case MapGuideInfoViewHook_ShowGuideViewLabel:
    {
      m_shwoGuideViewBtn.MouseUp();
      needRefresh = true;
      ShowGuideView();
    }
    break;
  }

  if (needRefresh)
  {
    this->Refresh();
  }
  return ctrlType;
}

void UeGui::CMapGuideInfoViewHook::Update( short type )
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
  //���ݵ���״̬���µ�ǰ����ͼ�����ʾ
  GuidanceStatus dirInfo;
  if (UeRoute::PEC_Success != m_routeWrapper.GetCurrent(dirInfo))
  {
    HideAllCtrl();
    return;
  }
  
  //�����ʾ·�ڷŴ�ͼ
  if (m_viewWrapper.IsGuidanceViewShown())
  {
    //����Ƿ���ģʽ(ӥ��ͼ����·�ڷŴ�ͼ)
    m_routeInfoBtn.SetVisible(false);
    ShowCurGuidanceIcon(false);
    ShowNextGuidanceIcon(false);
  }
  else if (m_isShowRouteGuideList)
  {
    //�����ʾ����·��
    m_routeInfoBtn.SetVisible(false);
    ShowCurGuidanceIcon(false);
    ShowNextGuidanceIcon(false);

    UpdateRouteGuideInfo(dirInfo);
    ShowRouteGuideList(true);
  }
  else if (m_isShowHightSpeedBoard)
  {
    //�����ʾ���ٿ���
    //������һ��·��Ϣ
    UpdateNextRouteInfo(dirInfo);
    //���·��򿴰�
    UpdateDirectionBoardInfo(dirInfo);
    ShowNextGuidanceIcon(false);
    UpdateHighSpeedBoard();
  }
  else
  {
    //���µײ�״̬����ǰ������Ϣ
    UpdateGuideInfo(dirInfo);
    //������һ��·��Ϣ
    UpdateNextRouteInfo(dirInfo);
    //���·��򿴰�
    UpdateDirectionBoardInfo(dirInfo);

    //���ط��򿴰�
    ShowRouteGuideList(false);
    //���ظ��ٿ���
    HideHightSpeedBoard();
  }

  //�Ƿ���״̬��Ҫ�ж��Ƿ���ʾ����ʾ·�ڷŴ�ͼ����ť
  if (!m_viewWrapper.IsGuidanceViewShown() && m_viewWrapper.IsNeedRenderGuidanceView())
  {
    m_shwoGuideViewBtn.SetVisible(true);
  }
  else
  {
    m_shwoGuideViewBtn.SetVisible(false);
  }
}

void UeGui::CMapGuideInfoViewHook::UpdateGuideInfo( const GuidanceStatus& dirInfo )
{
  //��ǰ��·��Ϣ �ײ�״̬����ʾ��ǰ��·��Ϣ
  GuidanceIndicator *curRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator);
  //����·����ȡ��һ��·
  if (curRoad->m_roadType == RT_Virtual)
  {
    curRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curOrderForSnd - 1);
  }

  if (curRoad)
  {
    //��ʾ��ǰ��·��
    char *roadName = NULL;
    short length = 0;
    if (curRoad->m_nameOffset)
    {
      m_net->GetNameTable(UeModel::UNT_Network)->GetContent(curRoad->m_nameOffset, &roadName, length);
      if (roadName)
      {
        unsigned char chLen = roadName[0];
        roadName++;
        roadName[chLen] = 0;
      }
    }
    else
    {
      roadName = "һ���·";
    }

    CMapHook* mapHook = NULL;
    if (m_parentHook)
    {
      mapHook = dynamic_cast<CMapHook*>(m_parentHook);
    }
    if (mapHook)
    {
      GpsCar gpsCar = m_viewWrapper.GetGpsCar();
      double leftDist = curRoad->m_leftDist;
      if (leftDist < 0)
      {
        leftDist = 0;
      }
      mapHook->UpdateGuideInfo(roadName, gpsCar.m_speed, leftDist);
    }
  }
}

void UeGui::CMapGuideInfoViewHook::UpdateNextRouteInfo( const GuidanceStatus& dirInfo )
{
  //����״̬����ʾ��һ����·��Ϣ
  char *roadName = NULL;
  //��Ŀ�ĵصľ��룬��ʼ��Ϊȫ�̵ĳ���
  UeRoute::PlanResultDesc desc;
  m_routeWrapper.GetPlanResultDesc(desc);
  int leftDist = desc.totalLength;
  if ((dirInfo.m_curIndicator - 1) >= 0)
  { 
    GuidanceIndicator *nextRoad = NULL;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //  ����ȡ�þ����յ����
    //  nextRoad = m_viewWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator - 1);
    //  leftDist = nextRoad->m_leftDist;
    //  ȡ��һ�������Ƶ��Һ͵�ǰ��·���Ʋ�ͬ�ĵ�·
    //  int count = 1;        
    //  while ((nextRoad = m_viewWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator - count)) && 
    //       (nextRoad->m_nameOffset == 0 || nextRoad->m_nameOffset == curRoad->m_nameOffset))
    //  {
    //    //һֱѭ������һ����·����û���µ�·��ʱ����һ����·����ȡ��һ���·��
    //    if(dirInfo.m_curIndicator == count)
    //    {
    //      nextRoad->m_nameOffset = 0;
    //      break;
    //    }
    //    count++;
    //  }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //�տ�ʼ����ʱ���������Ϊ0�����
    if (dirInfo.m_curPos.m_x != 0 && dirInfo.m_curPos.m_y != 0) 
    {
      //���㳵����ǰ·��β�ľ���
      GuidanceIndicator *curRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator);
      leftDist = CVectOP<long>::Mag(curRoad->m_vtxs[0], dirInfo.m_curPos);
    }
    nextRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator - 1);
    if (nextRoad)
    {     
      if (dirInfo.m_curPos.m_x != 0 && dirInfo.m_curPos.m_y != 0)
      {
        leftDist += nextRoad->m_leftDist;
        if (::abs(leftDist - dirInfo.m_curDistForSnd) <= 1)  //����쵽�յ�ʱ����ͼ���ϵ���ʾ��һ��
        {
          leftDist = dirInfo.m_curDistForSnd;
        }
      }

      if (nextRoad->m_roadType == RT_Virtual)   //����·����ȡ��һ��·
      {
        nextRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator - 2);
      }
      if (nextRoad && nextRoad->m_nameOffset)
      { 
        short length = 0;
        m_net->GetNameTable(UeModel::UNT_Network)->GetContent(nextRoad->m_nameOffset, &roadName, length);
        if (roadName)
        {
          unsigned char chLen = roadName[0];
          roadName++;
          roadName[chLen] = 0;
        }
      }
      else
      {
        roadName = "һ���·";
      }
    }
  }
  else
  {
    UeRoute::PlanPosition endPos;
    endPos.m_type = PT_End;
    m_routeWrapper.GetPosition(endPos);
    if (dirInfo.m_curPos.m_x != 0 && dirInfo.m_curPos.m_y != 0)
    {
      leftDist = CVectOP<long>::Mag(endPos.m_pos, dirInfo.m_curPos);
    }
    roadName = "�ӽ�Ŀ�ĵ�";
  }

  m_routeInfoBtn.SetCaption(roadName);
  m_routeInfoBtn.SetVisible(true);
}

void UeGui::CMapGuideInfoViewHook::UpdateDirectionBoardInfo( const GuidanceStatus& dirInfo )
{
  // ��ʾ·�ڷŴ�ͼ��ָ��ͼ��
  // ��ǰ·��
  GuidanceIndicator *curRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curOrderForSnd);
  int sndCode = (dirInfo.m_curSndCode <= 0) ? curRoad->m_snd.m_dirCode : dirInfo.m_curSndCode;
  //��ʾ��ǰ·�ڷ��򿴰�
  ShowCurGuidanceIcon(true, sndCode, curRoad->m_snd.m_infoCode, dirInfo.m_curPair);
  char buf[10] = {};
  if (dirInfo.m_curIndicator > 0)
  {
    if(dirInfo.m_curDistForSnd > 1000.)
    {
      ::sprintf(buf, "%.1fkm", dirInfo.m_curDistForSnd / 1000.);
    }
    else
    {       
      ::sprintf(buf, "%dm", (dirInfo.m_curDistForSnd <= 0) ? 0 : dirInfo.m_curDistForSnd);
    }
  }
  else
  {
    UeRoute::PlanPosition endPos;
    endPos.m_type = PT_End;
    m_routeWrapper.GetPosition(endPos);
    int turnDist = CVectOP<long>::Mag(endPos.m_pos, dirInfo.m_curPos);
    if (turnDist < 0)
    {
      turnDist = 0;
    }
    if(turnDist > 1000)
    {
      ::sprintf(buf, "%dkm", turnDist / 1000);
    }
    else
    {       
      ::sprintf(buf, "%dm", turnDist);
    }
  }
  m_curDirectionBoard.SetCaption(buf);
  //��ʾ��һ·�ڷ��򿴰�
  if(dirInfo.m_nextOrderForSnd <= 0 || dirInfo.m_nextOrderForSnd >= m_routeWrapper.GetIndicatorNum(dirInfo.m_curPair))
  {
    ShowNextGuidanceIcon(false);
  }
  else
  {
    //��һ·��
    curRoad = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_nextOrderForSnd);
    sndCode = ((int)(dirInfo.m_nextSndCode) <= 0) ? curRoad->m_snd.m_dirCode : dirInfo.m_nextSndCode;
    //ͼ����ʾ
    ShowNextGuidanceIcon(true, sndCode);
  }
}

void UeGui::CMapGuideInfoViewHook::UpdateRouteGuideInfo( const GuidanceStatus& dirInfo )
{
  //��ʾ��ǰ��·����
  UeRoute::GuidanceIndicator *curIndicator = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator);
  if (curIndicator)
  {
    //����·����ȡ��һ��·
    if (curIndicator->m_roadType == RT_Virtual)
    {
      curIndicator = m_routeWrapper.GetIndicator(dirInfo.m_curPair, dirInfo.m_curOrderForSnd - 1);
    }

    //��ʾ��ǰ��·��
    char roadName[MAX_NAME_LENGTH];
    if (curIndicator)
    {
      ::memset(roadName, 0, MAX_NAME_LENGTH);
      bool rt = m_routeWrapper.GetRoadName(curIndicator->m_nameOffset, roadName);
      m_routeGuideCurName.SetCaption(roadName);
    }

    int dataIndex = -1;
    int curPair = dirInfo.m_curPair;
    int totalPairs = m_routeWrapper.GetPairs();
    float totalDist = dirInfo.m_curDistForSnd;
    for (; curPair < totalPairs; ++curPair)
    {
      int indicatorIndex = (curPair == dirInfo.m_curPair) ? (dirInfo.m_curIndicator - 1) : (m_route->GetIndicatorNum(curPair) - 1);
      for (int i = indicatorIndex; i >= 0; i--)
      {
        curIndicator = m_route->GetRoute()->GetIndicator(curPair, i);
        if (curIndicator)
        {
          if ((UeRoute::DVT_Unknown == curIndicator->m_snd.m_dirCode) ||
              (UeRoute::DVT_DirectGo == curIndicator->m_snd.m_dirCode) ||
              (UeRoute::DVT_MiddleGo == curIndicator->m_snd.m_dirCode) ||
              (UeRoute::DVT_LeftDirect == curIndicator->m_snd.m_dirCode) ||
              (UeRoute::DVT_RightDirect == curIndicator->m_snd.m_dirCode))
          {
            totalDist += curIndicator->m_curDist;
          }
          else
          {
            ::memset(roadName, 0, MAX_NAME_LENGTH);
            bool rt = m_routeWrapper.GetRoadName(curIndicator->m_nameOffset, roadName);
            ++dataIndex;
            ShowRouteGuideData((RowItem)dataIndex, curIndicator->m_snd.m_dirCode, roadName, totalDist);
            if (dataIndex >= ROW4)
            {
              break;
            }
          }
        }
      }
    }
    //���û�����ݵ���
    for (int i = dataIndex + 1; i <= ROW4; ++i)
    {
      ClearRouteGuideRow((RowItem)i);
    }
  }
}

void UeGui::CMapGuideInfoViewHook::HideAllCtrl()
{
  m_routeInfoBtn.SetVisible(false);
  m_curDirectionBoard.SetVisible(false);
  m_nextDirectionBoard.SetVisible(false);
  m_highSpeedBoard1.SetVisible(false);
  m_highSpeedBoard1.SetVisible(false);
  m_highSpeedBoardTypeLabel1.SetVisible(false);
  m_highSpeedBoardDistLabel1.SetVisible(false);
  m_highSpeedBoard2.SetVisible(false);
  m_highSpeedBoardTypeLabel2.SetVisible(false);
  m_highSpeedBoardDistLabel2.SetVisible(false);
  m_highSpeedBoard3.SetVisible(false);
  m_highSpeedBoardTypeLabel3.SetVisible(false);
  m_highSpeedBoardDistLabel3.SetVisible(false);
  m_shwoGuideViewBtn.SetVisible(false);
  ShowRouteGuideList(false);
  HideHightSpeedBoard();
}

bool UeGui::CMapGuideInfoViewHook::ChangeElementIcon( GuiElement* destElement, GuiElement* srcElement )
{
  if (destElement && srcElement)
  {
    destElement->m_backStyle = srcElement->m_backStyle;
    return true;
  }
  return false;
}

void UeGui::CMapGuideInfoViewHook::ShowGuidanceIconCtrl( CUiBitButton &iconCtrl, bool isShown /*= true*/ )
{
  if (isShown)
  {
    //���ͼƬ�Ƿ���Ч,���û��ͼƬ����ʾ
    GuiElement* guiElement = iconCtrl.GetIconElement();
    if (guiElement)
    {
      if (guiElement->m_backStyle > 0)
      {
        iconCtrl.SetVisible(true);
        return;
      }
    }
    iconCtrl.SetVisible(false);
  }
  else
  {
    iconCtrl.SetVisible(false);
  }
}

void UeGui::CMapGuideInfoViewHook::ShowCurGuidanceIcon( bool isShow, int sndCode /*= 0*/, unsigned char infoCode /*= 0*/, int curPair /*= -1*/ )
{
  if (isShow)
  {
    bool rt = false;
    if ((UeRoute::DVT_DirectGo == sndCode) ||
        (UeRoute::DVT_MiddleGo == sndCode) ||
        (UeRoute::IVT_MeetMiddle == infoCode) ||
        (UeRoute::IVT_EnterToll == infoCode) ||
        (UeRoute::IVT_EnterTunnel == infoCode))
    {
      /// ֱ��,����
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_1));
      if (IVT_MeetDestination == infoCode)
      {
        /// ����Ŀ�ĵ�
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType1_1));
      }
      else if (UeRoute::IVT_MeetMiddle == infoCode)
      {
        /// ���ﾭ�ɵ�
        switch(curPair)
        {
        case 0:
          {
            rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(),GetGuiElement(MapGuideInfoViewHook_IconType1_2));
            break;
          }
        case 1:
          {
            rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(),GetGuiElement(MapGuideInfoViewHook_IconType1_3));
            break;
          }
        case 2:
          {
            rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(),GetGuiElement(MapGuideInfoViewHook_IconType1_4));
            break;
          }
        case 3:
          {
            rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(),GetGuiElement(MapGuideInfoViewHook_IconType1_5));
            break;
          }
        }
      }
      else if (IVT_EnterTunnel == infoCode)
      {
        /// �������
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_23));
      }
      else if (IVT_EnterFerry == infoCode)
      {
        /// �ӽ��ֶ�
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_28));
      }
      else if (IVT_EnterFerry == infoCode)
      {
        /// ��������·
        rt = false;
      }
      else if (IVT_EnterFastLane == infoCode)
      {
        /// �������·
        rt = false;
      }
      else if (IVT_EnterHW == infoCode)
      {
        /// �������
        rt = false;
      }
      else if (IVT_ExitHW == infoCode)
      {
        /// �뿪����
        rt = false;
      }
      else if (IVT_EnterSA == infoCode)
      {
        /// �з�����
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_25));
      }
      else if (IVT_EnterToll == infoCode)
      {
        /// ���շ�վ
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_24));
      }
      else if (IVT_EnterBridge == infoCode)
      {
        /// ����
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_26));
      }
      else if (IVT_EnterOverPass == infoCode)
      {
        /// �ϸ߼�
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_26));
      }
      else if (IVT_EnterRoundAbout == infoCode)
      {
        /// ���뻷��
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_22));
      }
      else if (IVT_EnterRoundAbout == infoCode)
      {
        /// �뿪����
        rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_22));
      }
    }
    else if (UeRoute::DVT_RightDirect == sndCode)
    { 
      /// ����ֱ��
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_11));
    }
    else if (UeRoute::DVT_LeftDirect == sndCode)
    {
      /// ����ֱ��
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_10));
    }
    else if (UeRoute::DVT_Right == sndCode)
    {
      /// ����
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_5));
    }
    else if (UeRoute::DVT_Left == sndCode)
    {
      /// ����
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_2));
    }
    else if (UeRoute::DVT_ForkRight == sndCode)
    {
      /// ��·������
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_10));
    }
    else if (UeRoute::DVT_ForkLeft == sndCode)
    {
      /// ��·������
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_11));
    }
    else if (UeRoute::DVT_UTurn == sndCode)
    {
      /// ��ͷ
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_9));
    }
    else if (UeRoute::DVT_RTurn == sndCode)
    {
      /// ��ת
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_6));
    }
    else if (UeRoute::DVT_LTurn == sndCode)
    {
      /// ��ת
      rt = ChangeElementIcon(m_curDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_3));
    }
    else
    {
      rt = false;
    }

    if (rt)
    {
      ShowGuidanceIconCtrl(m_curDirectionBoard);
    }
    else
    {
      ShowGuidanceIconCtrl(m_curDirectionBoard, false);
    }
  }
  else
  {
    ShowGuidanceIconCtrl(m_curDirectionBoard, false);
  }
}

void UeGui::CMapGuideInfoViewHook::ShowNextGuidanceIcon( bool isShow, int sndCode /*= 0*/ )
{
  if (isShow)
  {
    bool rt = false;
    if ((UeRoute::DVT_DirectGo == sndCode) || (UeRoute::DVT_MiddleGo == sndCode))
    {
      /// ֱ��,����
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_1));
    }
    else if (UeRoute::DVT_RightDirect == sndCode)
    { 
      /// ����ֱ��
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_12));
    }
    else if (UeRoute::DVT_LeftDirect == sndCode)
    {
      /// ����ֱ��
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_13));
    }
    else if (UeRoute::DVT_Right == sndCode)
    {
      /// ����
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_5));
    }
    else if (UeRoute::DVT_Left == sndCode)
    {
      /// ����
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_2));
    }
    else if (UeRoute::DVT_ForkRight == sndCode)
    {
      /// ��·������
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_10));
    }
    else if (UeRoute::DVT_ForkLeft == sndCode)
    {
      /// ��·������
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_11));
    }
    else if (UeRoute::DVT_UTurn == sndCode)
    {
      /// ��ͷ
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_9));
    }
    else if (UeRoute::DVT_RTurn == sndCode)
    {
      /// ��ת
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_6));
    }
    else if (UeRoute::DVT_LTurn == sndCode)
    {
      /// ��ת
      rt = ChangeElementIcon(m_nextDirectionBoard.GetIconElement(), GetGuiElement(MapGuideInfoViewHook_IconType2_3));
    }
    else
    {
      rt = false;
    }

    if (rt)
    {
      ShowGuidanceIconCtrl(m_nextDirectionBoard);
    }
    else
    {
      ShowGuidanceIconCtrl(m_nextDirectionBoard, false);
    }
  }
  else
  {
    ShowGuidanceIconCtrl(m_nextDirectionBoard, false);
  }
}

void UeGui::CMapGuideInfoViewHook::ShowGuideView()
{
  if (m_parentHook)
  {
    CMapHook* mapHook = dynamic_cast<CMapHook*>(m_parentHook);
    mapHook->ShowGuideView();
  }
}

void UeGui::CMapGuideInfoViewHook::ShowRouteGuideList( bool isShow /*= true*/ )
{
  m_routeGuideBack.SetVisible(isShow);
  m_routeGuideCurName.SetVisible(isShow);
  m_routeGuideName1.SetVisible(isShow);
  m_routeGuideName2.SetVisible(isShow);
  m_routeGuideName3.SetVisible(isShow);
  m_routeGuideName4.SetVisible(isShow);
  m_routeGuideDist1.SetVisible(isShow);
  m_routeGuideDist2.SetVisible(isShow);
  m_routeGuideDist3.SetVisible(isShow);
  m_routeGuideDist4.SetVisible(isShow);
  m_routeGuideIcon1.SetVisible(isShow);
  m_routeGuideIcon2.SetVisible(isShow);
  m_routeGuideIcon3.SetVisible(isShow);
  m_routeGuideIcon4.SetVisible(isShow);
}

void UeGui::CMapGuideInfoViewHook::ClearElementIcon( GuiElement* element )
{
  if (element)
  {
    element->m_backStyle = -1;
  }
}

void UeGui::CMapGuideInfoViewHook::ClearRouteGuideRow( RowItem row )
{
  switch (row)
  {
  case ROW1:
    {
      ClearElementIcon(m_routeGuideIcon4.GetCenterElement());
      m_routeGuideName4.ClearCaption();
      m_routeGuideDist4.ClearCaption();
      break;
    }
  case ROW2:
    {
      ClearElementIcon(m_routeGuideIcon3.GetCenterElement());
      m_routeGuideName3.ClearCaption();
      m_routeGuideDist3.ClearCaption();
      break;
    }
  case ROW3:
    {
      ClearElementIcon(m_routeGuideIcon2.GetCenterElement());
      m_routeGuideName2.ClearCaption();
      m_routeGuideDist2.ClearCaption();
      break;
    }
  case ROW4:
    {
      ClearElementIcon(m_routeGuideIcon1.GetCenterElement());
      m_routeGuideName1.ClearCaption();
      m_routeGuideDist1.ClearCaption();
      break;
    }
  }
}

void UeGui::CMapGuideInfoViewHook::ShowRouteGuideData( RowItem row, int sndCode, const char* roadName, double dist )
{
  char buf[128] = {};  
  if (dist > 1000)
  {
    //::sprintf(buf, "%.1f km", dist / 1000);
    ::sprintf(buf, "%dkm", static_cast<int>(dist / 1000));
  }
  else
  {
    if (dist < 0)
    {
      dist = 0;
    }
    ::sprintf(buf, "%dm", static_cast<int>(dist));
  }

  switch (row)
  {
  case ROW1:
    {
      ChangeCrossingIcon(m_routeGuideIcon4, sndCode);
      m_routeGuideName4.SetCaption(roadName);
      m_routeGuideDist4.SetCaption(buf);
      break;
    }
  case ROW2:
    {
      ChangeCrossingIcon(m_routeGuideIcon3, sndCode);
      m_routeGuideName3.SetCaption(roadName);
      m_routeGuideDist3.SetCaption(buf);
      break;
    }
  case ROW3:
    {
      ChangeCrossingIcon(m_routeGuideIcon2, sndCode);
      m_routeGuideName2.SetCaption(roadName);
      m_routeGuideDist2.SetCaption(buf);
      break;
    }
  case ROW4:
    {
      ChangeCrossingIcon(m_routeGuideIcon1, sndCode);
      m_routeGuideName1.SetCaption(roadName);
      m_routeGuideDist1.SetCaption(buf);
      break;
    }
  }
}

bool UeGui::CMapGuideInfoViewHook::ChangeCrossingIcon( CUiButton &IconButton, const int sndCode )
{
  bool rt = false;
  if ((UeRoute::DVT_DirectGo == sndCode) ||(UeRoute::DVT_Maximum==sndCode)||
      (UeRoute::DVT_MiddleGo == sndCode) ||(UeRoute::DVT_Unknown==sndCode)||
      (UeRoute::DVT_RightDirect == sndCode) || (UeRoute::DVT_LeftDirect == sndCode))
  {
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_1));
  }
  else if (UeRoute::DVT_RightDirect == sndCode)
  { 
    // ����ֱ��
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_11));
  }
  else if (UeRoute::DVT_LeftDirect == sndCode)
  {
    // ����ֱ��
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_10));
  }
  else if (UeRoute::DVT_Right == sndCode)
  {
    // ����
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_5));
  }
  else if (UeRoute::DVT_Left == sndCode)
  {
    /// ����
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_2));
  }
  else if (UeRoute::DVT_ForkRight == sndCode)
  {
    /// ��·������
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_10));
  }
  else if (UeRoute::DVT_ForkLeft == sndCode)
  {
    /// ��·������
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_11));
  }
  else if (UeRoute::DVT_UTurn == sndCode)
  {
    /// ��ͷ
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_9));
  }
  else if (UeRoute::DVT_RTurn == sndCode)
  {
    /// ��ת
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_6));
  }
  else if (UeRoute::DVT_LTurn == sndCode)
  {
    /// ��ת
    rt = ChangeElementIcon(IconButton.GetCenterElement(), GetGuiElement(MapGuideInfoViewHook_IconType4_3));
  }
  else
  {
    rt = false;
  }
  return rt;
}

void UeGui::CMapGuideInfoViewHook::HideHightSpeedBoard()
{
  ShowHightSpeedBoard(HB_One, false);
  ShowHightSpeedBoard(HB_Two, false);
  ShowHightSpeedBoard(HB_Three, false);
}

void UeGui::CMapGuideInfoViewHook::ShowHightSpeedBoard( HighSpeedBoardIndex boardIndex, bool isShow /*= true*/ )
{
  switch (boardIndex)
  {
  case HB_One:
    {
      m_highSpeedBoard1.SetVisible(isShow);
      m_highSpeedBoardTypeLabel1.SetVisible(isShow);
      m_highSpeedBoardDistLabel1.SetVisible(isShow);
      break;
    }
  case HB_Two:
    {
      m_highSpeedBoard2.SetVisible(isShow);
      m_highSpeedBoardTypeLabel2.SetVisible(isShow);
      m_highSpeedBoardDistLabel2.SetVisible(isShow);
      break;
    }
  case HB_Three:
    {
      m_highSpeedBoard3.SetVisible(isShow);
      m_highSpeedBoardTypeLabel3.SetVisible(isShow);
      m_highSpeedBoardDistLabel3.SetVisible(isShow);
      break;
    }
  }
}

void UeGui::CMapGuideInfoViewHook::UpdateHighSpeedBoard()
{
  HighwayOutletList dataList;
  if (m_routeWrapper.GetHighwayOutlets(dataList))
  {
    for (unsigned short i = HB_One; i < HB_End; ++i)
    {
      if (i < dataList.size())
      {
        RefreshHighSpeedBoardData((HighSpeedBoardIndex)i, dataList[i]);
        ShowHightSpeedBoard((HighSpeedBoardIndex)i, true);
      }
      else
      {
        ShowHightSpeedBoard((HighSpeedBoardIndex)i, false);
      }
    }
  }
  else
  {
    HideHightSpeedBoard();
  }
}

void UeGui::CMapGuideInfoViewHook::RefreshHighSpeedBoardData( HighSpeedBoardIndex boardIndex, const HighwayOutlet& data )
{
  char buf[32] = {};
  double distance = data.m_distance;
  if (distance < 0)
  {
    distance = 0;
  }
  if(data.m_distance > 1000)
  {
    ::sprintf(buf, "%dkm", distance / 1000);
  }
  else
  {       
    ::sprintf(buf, "%dm", distance);
  }

  switch (boardIndex)
  {
  case HB_One:
    {
      m_highSpeedBoard1.SetCaption(data.m_name);
      m_highSpeedBoardTypeLabel1.SetCaption(data.m_typeName);
      m_highSpeedBoardDistLabel1.SetCaption(buf);
      break;
    }
  case HB_Two:
    {
      m_highSpeedBoard2.SetCaption(data.m_name);
      m_highSpeedBoardTypeLabel2.SetCaption(data.m_typeName);
      m_highSpeedBoardDistLabel2.SetCaption(buf);
      break;
    }
  case HB_Three:
    {
      m_highSpeedBoard3.SetCaption(data.m_name);
      m_highSpeedBoardTypeLabel3.SetCaption(data.m_typeName);
      m_highSpeedBoardDistLabel3.SetCaption(buf);
      break;
    }
  }
}