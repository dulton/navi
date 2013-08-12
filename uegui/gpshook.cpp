#include "gpshook.h"
#include "uebase\timebasic.h"
#include "guisetting.h"
#include "settingwrapper.h"

using namespace UeGui;

CGpsHook::CGpsHook() : m_curLocationNum(0), m_maxSNRWidth(76)
{
  m_strTitle = "�ź�״̬";
  m_vecHookFile.push_back(_T("gpshook.bin"));
}

CGpsHook::~CGpsHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CGpsHook::Load() 
{
  CSettingWrapper &settingWrapper = CSettingWrapper::Get();
  m_timeStatus = settingWrapper.GetIsOpenTimeCalibration();
}

void CGpsHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Background,	"Background"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_DateLabel,	"DateLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Date,	"Date"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_WeekLabel,	"WeekLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Week,	"Week"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_TimeLabel,	"TimeLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Time,	"Time"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SatelliteNumLabel,	"SatelliteNumLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SatelliteNum,	"SatelliteNum"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_LocationNumLabel,	"LocationNumLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_LocationNum,	"LocationNum"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_ReceivingStateLabel,	"ReceivingStateLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_ReceivingState,	"ReceivingState"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SpeedLabel,	"SpeedLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Speed,	"Speed"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_QCodeLabel,	"QCodeLabel"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_QCode,	"QCode"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_EarthMap,	"EarthMap"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_LocateStatus,	"LocateStatus"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNROne,	"SNROne"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRTwo,	"SNRTwo"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRThree,	"SNRThree"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRFour,	"SNRFour"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRFive,	"SNRFive"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRSix,	"SNRSix"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRSeven,	"SNRSeven"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNREight,	"SNREight"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRNine,	"SNRNine"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRTen,	"SNRTen"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNREleven,	"SNREleven"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRTwelve,	"SNRTwelve"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_SNRBack,	"SNRBack"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point1,	"Point1"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point2,	"Point2"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point3,	"Point3"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point4,	"Point4"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point5,	"Point5"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point6,	"Point6"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point7,	"Point7"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point8,	"Point8"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point9,	"Point9"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point10,	"Point10"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point11,	"Point11"));
  m_ctrlNames.insert(GuiName::value_type(GpsHook_Point12,	"Point12"));
}

void CGpsHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_dateCtrl.SetLabelElement(GetGuiElement(GpsHook_Date));  
  m_weekCtrl.SetLabelElement(GetGuiElement(GpsHook_Week));
  m_timeCtrl.SetLabelElement(GetGuiElement(GpsHook_Time));
  m_satelliteNumCtrl.SetLabelElement(GetGuiElement(GpsHook_SatelliteNum));
  m_locationNumCtrl.SetLabelElement(GetGuiElement(GpsHook_LocationNum));
  m_receivingStateCtrl.SetCenterElement(GetGuiElement(GpsHook_ReceivingState));  
  m_receivingStateCtrl.SetEnable(false);
  m_speedCtrl.SetLabelElement(GetGuiElement(GpsHook_Speed));
  m_qCodeCtrl.SetLabelElement(GetGuiElement(GpsHook_QCode));
  m_locateStatusCtrl.SetCenterElement(GetGuiElement(GpsHook_LocateStatus));  
  //�����������ʾ�б�ؼ�
  for (int i=0, j=GpsHook_SNROne; i<12; i++)
  {
    m_sNRCtrl[i].SetCenterElement(GetGuiElement(j++));
  }
  //����ͼ��
  for (int i=0, j=GpsHook_SNROne; i<12; i++)
  {
    m_point[i].SetCenterElement(GetGuiElement(j++));
  }

  GuiElement* guiElement;
  //��ȡ�ź�ǿ�������
  m_maxSNRWidth = 76;

  //��������ͼ����Ⱦ����
  guiElement = GetGuiElement(GpsHook_EarthMap);
  if (guiElement)
  {
    m_earthRadius = guiElement->m_width / 2;
    m_earthCenterX = guiElement->m_startX + guiElement->m_width / 2;
    m_earthCenterY = guiElement->m_startY + guiElement->m_height / 2;
  }
}

short CGpsHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  return CMenuBackgroundHook::MouseDown(scrPoint);
}

short CGpsHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CGpsHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  return CMenuBackgroundHook::MouseUp(scrPoint);
}

void CGpsHook::Update()
{
  if (CViewHook::m_curHookType != DHT_GPSHook && CViewHook::m_curHookType != DHT_MapHook)
  {
    return;
  }

  //���ͣ���ڵ�ͼ������ֻ�������Ǹ���
  if (DHT_MapHook == CViewHook::m_curHookType)
  {
    UpdateLocationSatelliteNum();
    return;
  }

  unsigned int year   = 0;
  unsigned int month  = 0;
  unsigned int day    = 0;
  unsigned int hour   = 0;
  unsigned int minute = 0;
  unsigned int second = 0;
  unsigned int week   = 0;

  char buf[64] = {};

  //��ȡGPS�ź�
  GpsBasic pos;
  m_gps->GetPos(pos, false);
  //////////////////////////////////////////////////////////////////////////
  //��ȡ����ʱ��
  if (m_gps->IsLive() && m_timeStatus == UeBase::OS_ON)
  {
    year = pos.m_localTime.m_year;
    month = pos.m_localTime.m_month;
    day = pos.m_localTime.m_day;
    hour = pos.m_localTime.m_hour;
    minute = pos.m_localTime.m_min;
    second = pos.m_localTime.m_sec;
  }
  else
  {
    CTimeBasic::TimeReport report;
    CTimeBasic timer;
    timer.GetNow(report);

    year = report.m_year;
    month = report.m_month;
    day = report.m_day;
    hour = report.m_hour;
    minute = report.m_minute;
    second = report.m_second;
  }
  //////////////////////////////////////////////////////////////////////////
  /*
  //���������־
  if (m_gps->IsLive())
  {
    LogMessage("GPS is live *******************************");
  }
  else
  {
    LogMessage("GPS is not live !!!!!!!!!!!!!!!!!!!!!!!!!!!");
  }
  ::sprintf(buf, "Date:%02d-%02d-%02d %02d:%02d:%02d Speed:%.0f km/h", year, month, day, hour, minute, second, pos.m_speed);
  LogMessage(buf);
  */
  //////////////////////////////////////////////////////////////////////////
  //����
  ::sprintf(buf, "%02d/%02d/%02d", year, month, day);  
  m_dateCtrl.SetCaption(buf);
  //ʱ��
  ::sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
  m_timeCtrl.SetCaption(buf);
  //����
  week = DateToWeek(year, month, day);
  OutputWeek(week);
  //////////////////////////////////////////////////////////////////////////     
  //�������Ǹ���
  if (pos.m_curSatellite > 0)
  {
    ::sprintf(buf, "%d", pos.m_curSatellite);
  } 
  else
  {
    ::sprintf(buf, "%d", 0);
  }
  m_satelliteNumCtrl.SetCaption(buf);

  //��ʼ������״̬
  InitSatelliteStatus();
  //��������ȼ��㶨λ����  
  int locationNum = 0;
  for (int i = 0; i < pos.m_curSatellite; i++)
  {
    if (pos.m_satellites[i].m_snr > 0)
    {
      locationNum += 1;
      //////////////////////////////////////////////////////////////////////////
      /*
      //������־
      ::sprintf(buf, "SatelliteStatus %d: SatelliteID:%d E:%d A:%d SNR:%d", 
                locationNum, pos.m_satellites[i].m_id, pos.m_satellites[i].m_alt, pos.m_satellites[i].m_azimuth, pos.m_satellites[i].m_snr);
      LogMessage(buf);
      */
      //////////////////////////////////////////////////////////////////////////
      SetSatelliteStatus(locationNum, pos.m_satellites[i].m_snr);
      ShowSatellite(locationNum, pos.m_satellites[i].m_alt, pos.m_satellites[i].m_azimuth);
    }    
  }
  m_curLocationNum = locationNum;
  ::sprintf(buf, "%d", locationNum);
  m_locationNumCtrl.SetCaption(buf);

  //�Ƿ�λ��ͼ��仯
  if (m_gps->IsLive())
  {    
    // ����״̬
    m_receivingStateCtrl.SetEnable(true);
    m_locateStatusCtrl.SetCaption("�Ѷ�λ");

    //��ȡQ��
    double dX;
    double dY;
    int nCode = 9;
    unsigned short pCode[9] = {};
    const GpsCar &carInfo = m_view->GetGpsCar();
    CGeoPoint<double> point;
    point.m_x = carInfo.m_curPos.m_x;
    point.m_y = carInfo.m_curPos.m_y;
    dX = point.m_x / 100000.0;
    dY = point.m_y / 100000.0;
    if (QCode_MapToCode(dX, dY, pCode, nCode))
    {
      ::sprintf(buf, "%c%c%c-%c%c%c-%c%c%c", pCode[0], pCode[1], pCode[2], pCode[3], pCode[4], pCode[5], pCode[6], pCode[7], pCode[8]);
      m_qCodeCtrl.SetCaption(buf);
    }
  }
  else
  {    
    //����״̬
    m_receivingStateCtrl.SetEnable(false);
    m_locateStatusCtrl.SetCaption("δ��λ");
    m_qCodeCtrl.ClearCaption();
  }

  //˲ʱ�ٶ�
  ::sprintf(buf, "%.0f km/h", pos.m_speed);
  m_speedCtrl.SetCaption(buf);

  // ��ʻʱ��

  // ��ʻ����

  if(CViewHook::m_curHookType == CViewHook::DHT_GPSHook)
  {
    m_view->RefreshUI();
  }
}

int CGpsHook::IsLeapYear( int year )
{
  if ( (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) )
  {
    return 1; //����
  } 
  else
  {
    return 0;
  }
}

int CGpsHook::DateToWeek( int year,int month,int day )
{
  long int n;
  // ���㹫Ԫ1��1��1�յ��������ڵ�����
  n = (year -1) * 365L;   //��Ԫ1�굽�������ڵ����������������꣩
  n += (year -1) / 4;      //��������
  n -= (year -1) /100;
  n += (year -1) /400;

  switch(month-1)       //������������1�������������������µ�����
  {
  case 11: n+=30;
  case 10: n+=31;
  case 9:  n+=30;
  case 8:  n+=31;
  case 7:  n+=31;
  case 6:  n+=30;
  case 5:  n+=31;
  case 4:  n+=30;
  case 3:  n+=31;
  case 2:  
    if (IsLeapYear(year))
    {
      n+=29;
    } 
    else
    {
      n+=28;
    }
  case 1:  n+=31;
  }

  n += day;     //���������������µ�����
  n %= 7;       //��������ڼ�����Ϊ0Ϊ������
  return n;
}

void CGpsHook::OutputWeek( int week )
{
  switch(week)
  {
  case 0:
    m_weekCtrl.SetCaption("��");
    break;
  case 1:
    m_weekCtrl.SetCaption("һ");
    break;
  case 2:
    m_weekCtrl.SetCaption("��");
    break;
  case 3:
    m_weekCtrl.SetCaption("��");
    break;
  case 4:
    m_weekCtrl.SetCaption("��");
    break;
  case 5:
    m_weekCtrl.SetCaption("��");
    break;
  case 6:
    m_weekCtrl.SetCaption("��");
    break;
  }
}

void CGpsHook::SetCurLocationNum( int curLocationNum )
{
  m_curLocationNum = curLocationNum;
}

int CGpsHook::GetCurLocationNum()
{
  return m_curLocationNum;
}

void CGpsHook::InitSatelliteStatus()
{
  for (int i=0; i<12; i++)
  {
    m_sNRCtrl[i].SetVisible(false);
    m_point[i].SetVisible(false);
  }
}

int CGpsHook::GetWidth( int snr )
{
  int exSNR = 2 * snr;
  if (exSNR >= kMAXSNR)
  {
    return m_maxSNRWidth;
  }
  else
  {
    return (exSNR * m_maxSNRWidth) / kMAXSNR;
  }
}

void CGpsHook::SetSatelliteStatus( int id, int snr )
{  
  //ע����ø÷���֮ǰ��Ҫ���� InitSatelliteStatus()��ʼ���ź�
  int index = id - 1;
  if (snr <= 0 || index >= 12 || index < 0)
  {
    return;
  }
  int width = GetWidth(snr);
  m_sNRCtrl[index].SetVisible(true);
  m_sNRCtrl[index].SetWidth(width);
}

GuiElement* CGpsHook::GetSatlliteElement( int id )
{
  int index = id - 1;
  if (index >= 12 || index < 0)
  {
    return NULL;
  }
  else
  {
    return m_point[id].GetCenterElement();
  }
}

short CGpsHook::Elv2Rad( short elevation )
{
  double fact = m_earthRadius / 90.;
  return  m_earthRadius - (int) (fact * elevation + 0.5);
}

void CGpsHook::Gps2Scr( short elevation, short azimuth, CGeoPoint<int> &scrPt )
{
  short rad = Elv2Rad(elevation);
  scrPt.m_x = (int)(m_earthCenterX + rad * ::sin(Deg2Rad(azimuth)) + 0.5);
  scrPt.m_y = (int)(m_earthCenterY - rad * ::cos(Deg2Rad(azimuth)) + 0.5);

  //char msgBuf[128] = {0};
  //::sprintf(msgBuf, "Gps2Scr X:%d Y:%d R:%d E:%d A:%d RD:%d", m_earthCenterX, m_earthCenterY, m_earthRadius, elevation, azimuth, rad);
  //LogMessage(msgBuf);
}

void CGpsHook::ShowSatellite( int id, short elevation, short azimuth )
{
  //���Ƿ�λ�Ƿ�Χ0��90��
  if ((elevation >= 0) && (elevation <= 90) && (azimuth >= 0) && (azimuth <= 359))
  {
    CGeoPoint<int> scrPt;
    Gps2Scr(elevation, azimuth, scrPt);
    GuiElement* satelliteElement = GetSatlliteElement(id);
    if (satelliteElement)
    {
      satelliteElement->m_startX = scrPt.m_x - satelliteElement->m_width / 2;
      satelliteElement->m_startY = scrPt.m_y - satelliteElement->m_height / 2;
      satelliteElement->m_isVisible = true;
      //char msgBuf[128] = {0};
      //::sprintf(msgBuf, "ShowSatellite %d: X:%d Y:%d", id, satelliteElement->m_startX, satelliteElement->m_startY);
      //LogMessage(msgBuf);
    }
  }
}

void CGpsHook::UpdateLocationSatelliteNum()
{
  //��ȡGPS�ź�
  GpsBasic pos;
  m_gps->GetPos(pos, false);
  int locationNum = 0;
  for (int i = 0; i < pos.m_curSatellite; i++)
  {
    if (pos.m_satellites[i].m_snr > 0)
    {
      locationNum += 1;
    }    
  }
  m_curLocationNum = locationNum;
}