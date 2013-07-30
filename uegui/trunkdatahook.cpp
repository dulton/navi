#include "trunkdatahook.h"
#include "ddtservicequeryhook.h"
#include "maphook.h"
#include "uemap\viewhook.h"
#include "QCodeQueryHook.h"
#include "messagedialoghook.h"


using namespace UeGui;

void CTrunkDataHook::ShowData(short type)
{
  switch(type)
  {
  case CViewHook::DHT_ViewPickingStationHook :
    OpenPickingStation();
    break;
  case CViewHook::DHT_ViewLogisticsCenterHook:
    OpenLogisticsCenter();
    break;
  case CViewHook::DHT_ViewWaterStationsHook:
    OpenWaterStation();
    break;
  case CViewHook::DHT_ViewParkingHook :
    OpenParking();
    break;
  default:
    assert(false);
    break;
  }
}


void CTrunkDataHook::OpenLogisticsCenter()
{
  CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_DdtServiceQueryHook;
  IView* view = IView::GetView();
  CDdtServiceQueryHook* serviceQueryHook = dynamic_cast<CDdtServiceQueryHook*>(view->GetHook(CViewHook::DHT_DdtServiceQueryHook));
  serviceQueryHook->Clear();
  serviceQueryHook->SetTitle("�鿴��������");
  serviceQueryHook->SetQueryArea("��ɽ��");
  serviceQueryHook->SetTypeContent("����������");
  serviceQueryHook->SetServiceListQueryEvent(GoToMap);

  CGeoPoint<long> point(11324011,2284118);
  serviceQueryHook->AddServiceData("˳������������", "˳����", point);

  point.m_x = 11310654;
  point.m_y = 2324080;
  serviceQueryHook->AddServiceData("�����������", "˳����", point);

  point.m_x = 11328100;
  point.m_y = 2274769;
  serviceQueryHook->AddServiceData("�·���������", "˳����", point);


  point.m_x = 11327151;
  point.m_y = 2273872;
  serviceQueryHook->AddServiceData("ϸ����������", "˳����", point);

  point.m_x = 11305860;
  point.m_y = 2287338;
  serviceQueryHook->AddServiceData("������������", "˳����", point);

  point.m_x = 11310458;
  point.m_y = 2306613;
  serviceQueryHook->AddServiceData("�°���������", "˳����", point);

  serviceQueryHook->ShowData();
}

void CTrunkDataHook::OpenPickingStation()
{
  CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_DdtServiceQueryHook;
  IView* view = IView::GetView();
  CDdtServiceQueryHook* serviceQueryHook = dynamic_cast<CDdtServiceQueryHook*>(view->GetHook(CViewHook::DHT_DdtServiceQueryHook));
  serviceQueryHook->Clear();
  serviceQueryHook->SetTitle("�鿴���վ");
  serviceQueryHook->SetQueryArea("��ɽ��");
  serviceQueryHook->SetTypeContent("�����վ");
  serviceQueryHook->SetServiceListQueryEvent(GoToMap);

  CGeoPoint<long> point(11321322,2288346);
  serviceQueryHook->AddServiceData("˳���������������޹�˾�����Ϣ��", "˳����", point);
  point.m_x = 11316997;
  point.m_y = 2302317;
  serviceQueryHook->AddServiceData("��ԼҾ�ó�׹�˾�����Ϣ��", "˳����", point);

  point.m_x = 11308714;
  point.m_y = 2295917;
  serviceQueryHook->AddServiceData("�˰����������Ϣ��", "˳����", point);

  point.m_x = 11325120;
  point.m_y = 2284695;
  serviceQueryHook->AddServiceData("��˳���������Ϣ��", "˳����", point);

  point.m_x = 11311545;
  point.m_y = 2301336;
  serviceQueryHook->AddServiceData("��ɽ��¡������Ͻ����޹�˾�����Ϣ��", "˳����", point);

  point.m_x = 11321569;
  point.m_y = 2287218;
  serviceQueryHook->AddServiceData("���ƹ�˾�����Ϣ��", "˳����", point);

  point.m_x = 11321302;
  point.m_y = 2287218;
  serviceQueryHook->AddServiceData("��˳�ز������Ϣ��", "˳����", point);

  point.m_x = 11320443;
  point.m_y = 2290184;
  serviceQueryHook->AddServiceData("������������Ϣ��", "˳����", point);

  point.m_x = 11325079;
  point.m_y = 2285079;
  serviceQueryHook->AddServiceData("��ӯ�Ƶ������Ϣ��", "˳����", point);
  serviceQueryHook->ShowData();
}

void CTrunkDataHook::OpenWaterStation()
{
  CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_DdtServiceQueryHook;
  IView* view = IView::GetView();
  CDdtServiceQueryHook* serviceQueryHook = dynamic_cast<CDdtServiceQueryHook*>(view->GetHook(CViewHook::DHT_DdtServiceQueryHook));
  serviceQueryHook->Clear();
  serviceQueryHook->SetTitle("�鿴��������");
  serviceQueryHook->SetQueryArea("��ɽ��");
  serviceQueryHook->SetTypeContent("�ķ�������");
  serviceQueryHook->SetServiceListQueryEvent(GoToMap);

  CGeoPoint<long> point(11327008,2282780);
  serviceQueryHook->AddServiceData("˳��ΰ����̥������������", "˳����", point);

  point.m_x = 11325920;
  point.m_y = 2281439;
  serviceQueryHook->AddServiceData("·��������������", "˳����", point);

  point.m_x = 11328069;
  point.m_y = 2276125;
  serviceQueryHook->AddServiceData("�ý�������������", "˳����", point);

  point.m_x = 11325600;
  point.m_y = 2275250;
  serviceQueryHook->AddServiceData("����������������", "˳����", point);

  point.m_x = 11323892;
  point.m_y = 2281893;
  serviceQueryHook->AddServiceData("Ө��������������", "˳����", point);

  point.m_x = 11323458;
  point.m_y = 2285304;
  serviceQueryHook->AddServiceData("˳���Ƿ������ۺ��������", "˳����", point);

  serviceQueryHook->ShowData();
}


void CTrunkDataHook::OpenParking()
{
  CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_DdtServiceQueryHook;
  IView* view = IView::GetView();
  CDdtServiceQueryHook* serviceQueryHook = dynamic_cast<CDdtServiceQueryHook*>(view->GetHook(CViewHook::DHT_DdtServiceQueryHook));
  serviceQueryHook->Clear();
  serviceQueryHook->SetTitle("�鿴ͣ����");
  serviceQueryHook->SetQueryArea("��ɽ��");
  serviceQueryHook->SetTypeContent("��ͣ����");
  serviceQueryHook->SetServiceListQueryEvent(GoToMap);
  CGeoPoint<long> point(11325064,2285087);
  serviceQueryHook->AddServiceData("��ӯ�Ƶ�ͣ����", "˳����", point);

  point.m_x = 11325103;
  point.m_y = 2284685;
  serviceQueryHook->AddServiceData("������ҵ����ͣ����", "˳����", point);

  point.m_x = 11311660;
  point.m_y = 2310957;
  serviceQueryHook->AddServiceData("�ﶫ����ͣ����", "˳����", point);

  point.m_x = 11315019;
  point.m_y = 2311067;
  serviceQueryHook->AddServiceData("�ƹ����ͣ����", "˳����", point);

  point.m_x = 11301366;
  point.m_y = 2298218;
  serviceQueryHook->AddServiceData("Ѹ������ͣ����", "˳����", point);

  point.m_x = 11301560;
  point.m_y = 2296254;
  serviceQueryHook->AddServiceData("�մɳ�������������ͣ����", "˳����", point);

  point.m_x = 11308523;
  point.m_y = 2301199;
  serviceQueryHook->AddServiceData("���ǻ���ͣ����", "˳����", point);

  serviceQueryHook->ShowData();
}


void CTrunkDataHook::GoToMap(const char* keyValue1, const char* keyValue2, const CGeoPoint<long>& point)
{
  ShowMapByPick(point, keyValue1);
}


void CTrunkDataHook::ShowMapByPick(const CGeoPoint<long> &point ,const char* addrName)
{
  CViewHook::m_prevHookType = CViewHook::m_curHookType;
  CViewHook::m_curHookType = CViewHook::DHT_MapHook;
  IView* view = IView::GetView();
  CMapHook* mapHook = dynamic_cast<CMapHook*>(view->GetHook(CViewHook::DHT_MapHook));
  mapHook->SetPickPos(point, addrName);
}
