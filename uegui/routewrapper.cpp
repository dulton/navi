#include "routewrapper.h"
#include "gui.h"

using namespace UeGui;

UeGui::CRouteWrapper::CRouteWrapper() : m_view(IView::GetView()), m_route(IRoute::GetRoute()),
  m_query(IQuery::GetQuery()), m_net(IRoadNetwork::GetNetwork()), m_gps(IMapMatch::GetMapMatch())
{
}

UeGui::CRouteWrapper::~CRouteWrapper()
{

}

CRouteWrapper& UeGui::CRouteWrapper::Get()
{
  static CRouteWrapper m_routeWrapper;
  return m_routeWrapper;
}

unsigned int UeGui::CRouteWrapper::GetCurrent( GuidanceStatus &dirInfo )
{
  if (m_route)
  {
    return m_route->GetCurrent(dirInfo);
  }
  return PEC_NotFindIndicator;
}

void UeGui::CRouteWrapper::GetPassedRouteList( RouteList& routeList )
{
  routeList.clear();
  if (m_route)
  {
    GuidanceStatus dirInfo;
    //��ȡ��ǰ����λ�õĵ�����Ϣ
    m_route->GetCurrent(dirInfo);
    int curPair = dirInfo.m_curPair;
    //�ж�����ɵ㣬���ж��
    int totalPairs = m_route->GetPairs();
    for (; curPair < totalPairs; curPair++)
    {
      int total = (curPair == dirInfo.m_curPair) ? dirInfo.m_curIndicator : (m_route->GetIndicatorNum(curPair) - 1);
      for (int i = total; i >= 0; i--)
      {
        UeRoute::GuidanceIndicator *curIndicator = NULL;

        curIndicator = m_route->GetRoute()->GetIndicator(curPair, i);
        if (curIndicator)
        {
          RouteInfo routeInfo;
          if (i == total)  //��һ��ȡʣ�µ�·�̡�
          {
            routeInfo.m_mileages = GetCurIndicatorLeftDist(dirInfo);
          }
          else
          {
            routeInfo.m_mileages = curIndicator->m_curDist;
          }
          routeInfo.m_direction = curIndicator->m_snd.m_dirCode;
          routeInfo.m_parcelIdx = curIndicator->m_parcelIdx;
          routeInfo.m_linkIdx = curIndicator->m_linkIdx;
          routeInfo.m_begin = i;
          routeInfo.m_end = i;
          if (curIndicator->m_vtxs)
          {
            routeInfo.m_point.m_x = curIndicator->m_vtxs[0].m_x;
            routeInfo.m_point.m_y = curIndicator->m_vtxs[0].m_y;
          }
          //��ȡ��·����
          char* name = 0;
          short length = 0;      
          if(curIndicator->m_nameOffset > 0)
          {
            if (m_net)
            {
              m_net->GetNetwork()->GetNameTable(UeModel::UNT_Network)->GetContent(curIndicator->m_nameOffset, &name, length);
            }
            // ����ʾ����
            unsigned char chLen = name[0];
            name++;
            name[chLen] = 0;   
          }
          else
          {
            //һ���·
            name = "һ���·";
          } 
          ::strcpy(routeInfo.m_routeName, name);
          routeList.push_back(routeInfo);
        }
      }
    }
  }
}

float UeGui::CRouteWrapper::GetCurIndicatorLeftDist( const GuidanceStatus& dirInfo )
{
  float returnValue = 0;
  if (m_route)
  {
    if (dirInfo.m_curOrderForSnd == dirInfo.m_curIndicator)
    {
      UeRoute::GuidanceIndicator *curIndicator = m_route->GetRoute()->GetIndicator(dirInfo.m_curPair, dirInfo.m_curIndicator);
      if (curIndicator)
      {
        returnValue = curIndicator->m_curDist;
      }
    }
    else
    {
      returnValue = dirInfo.m_curDistForSnd;
      for (int i = dirInfo.m_curIndicator - 1; i >= dirInfo.m_curOrderForSnd; --i)
      {
        UeRoute::GuidanceIndicator *curIndicator = m_route->GetRoute()->GetIndicator(dirInfo.m_curPair, i);
        if (curIndicator)
        {
          returnValue -= curIndicator->m_curDist;
        }
      }
    }
  }
  return returnValue; 
}

void UeGui::CRouteWrapper::MergeRoad(RouteList& routeList)
{
  RouteListItr first = routeList.begin();
  for (; first != routeList.end(); ++first)
  {
    RouteListItr nextDiff = std::find_if(first, routeList.end(), DifferentNameRoad(*first));
    if ((first + 1) != nextDiff)
    {
      float mileages = 0;
      //����ͬ�ĵ�·�������
      std::for_each(first, nextDiff, SumMileages(&mileages));
      //��¼��ͬ·�����һ��·
      RouteListItr lastPos  = nextDiff - 1;
      //��¼��ͬ·���һ������Ϣ��
      first->m_direction = lastPos->m_direction;
      first->m_end = lastPos->m_end;    
      first->m_parcelIdx = lastPos->m_parcelIdx;
      first->m_linkIdx = lastPos->m_linkIdx;
      first->m_point = lastPos->m_point;
      //��ͬ��·�ĳ��Ⱥ�
      first->m_mileages = mileages;
      //�Ѻϲ����Ƴ���ͬ�ĵ�·
      routeList.erase(first + 1, nextDiff);  
    }
  }
}

int UeGui::CRouteWrapper::GetIndicatorNum( int curPair )
{
  if (m_route)
  {
    return m_route->GetIndicatorNum(curPair);
  }
  return 0;
}

int UeGui::CRouteWrapper::GetIndicatorNum( unsigned char curPlan, int curPair )
{
  if (m_route)
  {
    return m_route->GetIndicatorNum(curPlan, curPair);
  }
  return 0;
}

GuidanceIndicator * UeGui::CRouteWrapper::GetIndicator( int curPair, int idx )
{
  if (m_route)
  {
    return m_route->GetIndicator(curPair, idx);
  }
  return NULL;
}

GuidanceIndicator * UeGui::CRouteWrapper::GetIndicator( unsigned char curPlan, int curPair, int idx )
{
  if (m_route)
  {
    return m_route->GetIndicator(curPlan, curPair, idx);
  }
  return NULL;
}

unsigned int UeGui::CRouteWrapper::SetBlock( CGeoPoint<long> &onePos, bool isRemoved /*= false*/ )
{
  if (m_route)
  {
    return m_route->SetBlock(onePos, isRemoved);
  }
  return PEC_NotHaveBlockDecorator;
}

unsigned int UeGui::CRouteWrapper::SetBlock( CGeoRect<long> &oneExtent, bool isRemoved /*= false*/ )
{
  if (m_route)
  {
    return m_route->SetBlock(oneExtent, isRemoved);
  }
  return PEC_NotHaveBlockDecorator;
}

unsigned int UeGui::CRouteWrapper::SetBlock( CMemVector &ids, bool isRemoved /*= false*/ )
{
  if (m_route)
  {
    return m_route->SetBlock(ids, isRemoved);
  }
  return PEC_NotHaveBlockDecorator;
}

unsigned int UeGui::CRouteWrapper::SetBlock( bool isRemoved /*= false*/ )
{
  if (m_route)
  {
    return m_route->SetBlock(isRemoved);
  }
  return PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::Prepare()
{
  if (m_route)
  {
    return m_route->Prepare();
  }
  return PEC_OtherError;
}

void UeGui::CRouteWrapper::SetPlanState( short state )
{
  if (m_route)
  {
    m_route->SetPlanState(state);
  }
}

unsigned int UeGui::CRouteWrapper::RoutePlan()
{
  if (m_route)
  {
    return m_route->RoutePlan();
  }
  return PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::RoutePlan( bool isPlayVoice )
{
  if (m_route)
  {
    return m_route->RoutePlan(isPlayVoice);
  }
  return PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::MultiRoutePlan()
{
  if (m_route)
  {
    return m_route->MultiRoutePlan();
  }
  return PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::SetMethod( unsigned int method )
{
  if (m_route)
  {
    return m_route->SetMethod(method);
  }
  return PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::GetMethod()
{
  if (m_route)
  {
    return m_route->GetMethod();
  }
  return MT_Max;
}

bool UeGui::CRouteWrapper::GetPlanResultDesc( PlanResultDesc &desc )
{
  if (m_route)
  {
    return m_route->GetPlanResultDesc(desc);
  }
  return false;
}

bool UeGui::CRouteWrapper::GetPlanResultDesc( unsigned char curPlan, PlanResultDesc &desc )
{
  if (m_route)
  {
    return m_route->GetPlanResultDesc(curPlan, desc);
  }
  return false;
}

int UeGui::CRouteWrapper::GetPairs()
{
  if (m_route)
  {
    return m_route->GetPairs();
  }
  return 0;
}

short UeGui::CRouteWrapper::GetPlanState()
{
  if (m_route)
  {
    return m_route->GetPlanState();
  }
  return PS_None;
}

void UeGui::CRouteWrapper::GetPlanPositionList( PlanPositionList& positionList )
{
  positionList.clear();
  //��ȡ���
  UeRoute::PlanPosition startPos;
  startPos.m_type = UeRoute::PT_Start;
  m_route->GetPosition(startPos);
  if(startPos.m_type != UeRoute::PT_Invalid)
  {
    positionList.push_back(startPos);
  }
  //��ȡ�м侭�ɵ�
  int posCount = m_route->GetPosCount();
  if(posCount > 2)
  {
    UeRoute::PlanPosition midPos;
    midPos.m_type = UeRoute::PT_Middle;
    for(int i = 1; i < posCount - 1; i++)
    {
      m_route->GetPosition(midPos, i);
      if(midPos.m_type != UeRoute::PT_Invalid)
      {
        positionList.push_back(midPos);
      }
    }
  }
  //��ȡ�յ�
  UeRoute::PlanPosition endPos;
  endPos.m_type = UeRoute::PT_End;
  m_route->GetPosition(endPos);
  if(endPos.m_type != UeRoute::PT_Invalid)
  {
    positionList.push_back(endPos);
  }
}

unsigned int UeGui::CRouteWrapper::SetRouteStart()
{
  return SetPosition(PT_Start);
}

unsigned int UeGui::CRouteWrapper::SetRouteMiddle()
{
  return SetPosition(PT_Middle);
}

unsigned int UeGui::CRouteWrapper::SetRouteEnd()
{
  return SetPosition(PT_End);
}

unsigned int UeGui::CRouteWrapper::SetPosition( PositionType posType )
{
  if (!m_route)
  {
    return UeRoute::PEC_SetError;
  }

  if (PT_End == posType)
  {
    //������Ŀ�ĵأ�ȥ��ԭ�ȹ�ܵ�Ӱ��
    m_route->SetBlock(true);
    //�ж��Ƿ����������
    PlanPosition startPos;
    startPos.m_type = UeRoute::PT_Start;
    m_route->GetPosition(startPos);
    //�ж��Ƿ���������㣬û�����Ե�ǰ����λ��Ϊ���
    if ((UeRoute::PT_Invalid == startPos.m_type) || (!startPos.IsValid())) 
    {
      const GpsCar &carInfo = m_view->GetGpsCar();
      startPos.m_type = UeRoute::PT_Start;
      startPos.m_pos.m_x = carInfo.m_curPos.m_x;
      startPos.m_pos.m_y = carInfo.m_curPos.m_y;
      unsigned int rt = m_route->SetPosition(startPos);
      if (UeRoute::PEC_Success != rt)
      {
        return rt;
      }
    }
  }

  //��ǰѡ���������Ŀ�ĵ�
  CGeoPoint<long> pickPos;
  m_view->GetPickPos(pickPos);
  PlanPosition position;
  position.m_type = posType;
  position.m_pos = pickPos;
  position.m_isGPS = false;
  m_view->GetPickName(position.m_name);

  if (::strlen(position.m_name) <= 0)
  {
    IGui* gui = IGui::GetGui();
    gui->GetDistrictName(pickPos, position.m_name);
    int len = strlen(position.m_name);
    if (position.m_name[len] != '\n')
    {
      position.m_name[len] = '\n';
    }
  }
  return m_route->SetPosition(position);
}

unsigned int UeGui::CRouteWrapper::RemovePosition( bool isReserved /*= false*/ )
{
  if (m_route)
  {
    return m_route->RemovePosition(isReserved);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::SetPosition( PlanPosition &pos )
{
  if (m_route)
  {
    return m_route->SetPosition(pos);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::GetPosition( PlanPosition &pos ) const
{
  if (m_route)
  {
    return m_route->GetPosition(pos);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::GetPosition( PlanPosition &pos, CGeoRect<long> &mbr ) const
{
  if (m_route)
  {
    return m_route->GetPosition(pos, mbr);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::GetPosition( PlanPosition &pos, unsigned short idx ) const
{
  if (m_route)
  {
    return m_route->GetPosition(pos, idx);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::StartDemo( short speed )
{
  if (m_route)
  {
    return m_route->StartDemo(speed);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::PauseDemo()
{
  if (m_route)
  {
    return m_route->PauseDemo();
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::ResumeDemo( short speed )
{
  if (m_route)
  {
    return m_route->ResumeDemo(speed);
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::StopDemo()
{
  if (m_route)
  {
    return m_route->StopDemo();
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::StartGuidance()
{
  if (m_route)
  {
    return m_route->StartGuidance();
  }
  return UeRoute::PEC_OtherError;
}

unsigned int UeGui::CRouteWrapper::StopGuidance()
{
  if (m_route)
  {
    return m_route->StopGuidance();
  }
  return UeRoute::PEC_OtherError;
}

bool UeGui::CRouteWrapper::GetCurElecEye( EEyeProp &elecEye, double& distance )
{
  bool rt = false;
  if (m_route)
  {

    rt = m_route->GetCurElecEye(elecEye);
    if (rt)
    {
      //distance = m_route->GetCurElecEyeDist();
    }
    else
    {
      distance = 0.0;
    }
  }
  else
  {
    distance = 0.0;
  }
  return rt;
}