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
#include "uebase\dbgmacro.h"
using namespace UeBase;

// Refer to UeGps
#include "nmeapro.h"
using namespace UeGps;

// Initialization
const double CNmeaPro::KNOT2KM = 1.8519998;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/**
*
*/
bool CNmeaPro::Parse(const char *str, PosBasic *pos)
{
  // Exceptions
  GpsBasic *gpsPos = reinterpret_cast<GpsBasic *>(pos);
  assert(gpsPos != 0);
  if(!gpsPos)
  {
    return false;
  }

  // Conventions at the beginning of one sentence
  if((*str != '$') || (*(str+1) != 'G') || (*(str+2) != 'P'))
  {
    return false;
  }

  // Validation check with checksum
  const char *checkSum = ::strchr(str, '*');
  if(!checkSum)
  {
    return false;
  }
  checkSum++;

  char tmp[32] = {0, };
  ::sprintf(tmp, "%02X", GetCheckSum(str, 1));
  if(*checkSum != *tmp || *(checkSum + 1) != *(tmp + 1))
  {
    return false;
  }

  // Move to content
  str += 3;
  gpsPos->m_receiveCount = GPSRECVCOUNT;

  if(IsSentence(str, "GGA"))
  {
    ParseGGA(str, gpsPos);
  }
  else if(IsSentence(str, "RMC"))
  {
    ParseRMC(str, gpsPos);
  }
  else if(IsSentence(str, "GSA"))
  {
    ParseGSA(str, gpsPos);
  }
  else if(IsSentence(str, "GSV"))
  {
    ParseGSV(str,gpsPos);
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/**
*
*/
inline unsigned char CNmeaPro::GetCheckSum(const char *str, short skip)
{
  // Check sum
  unsigned char checkSum = 0;
  char *buf = const_cast<char *>(str) + skip;
  while(*buf && (*buf != '*') && (*buf != 0x0D) && (*buf != 0x0A))
  {
    checkSum ^= *buf;
    buf++;
  };

  return checkSum;
}

/**
*
*/
inline bool CNmeaPro::IsSentence(const char *str, const char *flag)
{
  return ((*str == *flag) && (*(str+1) == *(flag + 1)) && (*(str+2) == *(flag+2)));
}


/**
*
*/
void CNmeaPro::ParseGGA(const char *str, GpsBasic *gpsPos)
{
  /*
  ** GGA - Global Positioning System Fix Data --ȫ��λ����
  ** Time, Position and fix related data fora GPS receiver.
  **
  **                                                      11
  **        1         2       3 4        5 6 7  8   9  10 |  12 13  14   15
  **        |         |       | |        | | |  |   |   | |   | |   |    |
  ** $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
  **
  ** Field Number: 
  **  1) Universal Time Coordinated (UTC) - UTCʱ��
  **  2) Latitude  -ά��
  **  3) N or S (North or South)  -ά�ȷ��� N��S ��γ����γ
  **  4) Longitude  -����
  **  5) E or W (East or West) -���ȷ��� E��W ����������
  **  6) GPS Quality Indicator, -��λָʾ
  **     0 - fix not available, -��λ��Ч
  **     1 - GPS fix,  -GPS,SPSģʽ ��λ��Ч
  **     2 - Differential GPS fix  -��GPS,SPSģʽ ��λ��Ч
  **     3 - GPS PPSģʽ ��λ��Ч
  **  7) Satellites Used, -��ǰʹ�õ��������� ��Χ��00-12
  **  8) Horizontal Dilution of precision ˮƽ����
  **  9) Antenna Altitude above/below mean-sea-level (geoid)  -��ƽ��߶�
  ** 10) Units of antenna altitude, meters  �߶ȵ�λ
  ** 11) Geoidal separation, the difference between the WGS-84 earth
  **     ellipsoid and mean-sea-level (geoid), "-" means mean-sea-level
  **     below ellipsoid  -�����������Ժ�ƽ��ĸ߶�
  ** 12) Units of geoidal separation, meters  -��λ��
  ** 13) Age of differential GPS data, time in seconds since last SC104
  **     type 1 or 9 update, null field when DGPS is not used  -���GPS��������
  ** 14) Differential reference station ID, 0000-1023  -��ֻ�վID
  ** 15) Checksum  -У���
  */

  //
  m_isSameGroup = true;

  //
  if (m_token.Trim(str, 20) < 15)
  {
    return;
  }

  //
  GetGpsTime(0, m_token[1], gpsPos);
  GetLocalTime(gpsPos);

  //
  if (*m_token[6])
  {
    gpsPos->m_qualityIndicator = ::atoi(m_token[6]);
  }

  if (*m_token[7])
  {
    gpsPos->m_satelliteNum = ::atoi(m_token[7]);
  }

  if (*m_token[8])
  {
    gpsPos->m_HDOP = ::atof(m_token[8]);
  }

  // Only get the useful altitude
  if (*m_token[9] && gpsPos->m_qualityIndicator)
  {
    gpsPos->m_alt = ::atof(m_token[9]);
  }
}

/**
*
*/
void CNmeaPro::ParseRMC(const char *str, GpsBasic *gpsPos)
{
  /*
  ** RMC - Recommended Minimum Navigation Information  ���䶨λ����
  **                                                            12
  **        1         2 3       4 5        6 7   8   9    10  11|
  **        |         | |       | |        | |   |   |    |   | |
  ** $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a*hh<CR><LF>
  **
  ** Field Number: 
  **  1) UTC Time  -��λʱUTCʱ�� hhmmss��ʽ
  **  2) Status, V = Navigation receiver warning  -״̬ A=��λ V=��Ч��λ
  **  3) Latitude  -ά��
  **  4) N or S  -ά�ȷ��� N��S ��γ����γ
  **  5) Longitude  -����
  **  6) E or W  -���ȷ��� E����W ����������
  **  7) Speed over ground, knots  -��������
  **  8) Track made good, degrees true  -���溽��
  **  9) Date, ddmmyy  -UTC���� ddmmyy�������꣩
  ** 10) Magnetic Variation, degrees  -��ƫ��
  ** 11) E or W  -ģʽָʾ(��NMEA0183 3.00�汾���)
  ** 12) Checksum  -У���
  */

  //
  m_isSameGroup = true;

  //
  if(m_token.Trim(str, 20) < 12)
  {
    return;
  }

  //
  GetGpsTime(m_token[9], m_token[1], gpsPos);
  GetLocalTime(gpsPos);

  //�жϾ���ά���Ƿ���Ч
  if (m_token[3][0] && m_token[5][0])
  {
    gpsPos->m_lat = GetGpsAngle(m_token[3], gpsPos);
    gpsPos->m_isNorth = (*m_token[4] == 'N');

    gpsPos->m_lon = GetGpsAngle(m_token[5], gpsPos, false);
    gpsPos->m_isEast = (*m_token[6] == 'E');

    if(*m_token[2] != 'A')
    {
      gpsPos->m_isActive = 0;
    }
    else
    {
      if((gpsPos->m_lon > 0) && (gpsPos->m_lon < 180) &&
        (gpsPos->m_lat > 0) && (gpsPos->m_lat < 90))
      {
        gpsPos->m_isActive = 10;
      }
      else
      {
        gpsPos->m_isActive = 1;
      }

      //gpsPos->m_isActive = 10;
    }
  }
  else
  {
    gpsPos->m_isActive = 0;
  }

  //
  gpsPos->m_speed = ::atof(m_token[7]) * KNOT2KM;
  gpsPos->m_gpsDegree = ::atof(m_token[8]);

  //
  if(gpsPos->m_isActive != 0)
  {
    if(gpsPos->m_sndCount < GPSSNDCOUNT)
    {
      gpsPos->m_sndCount++;
    }

    gpsPos->m_liveCount = GPSLIVECOUNT;
  }
}

/**
*
*/
void CNmeaPro::ParseGSA(const char *str, GpsBasic *gpsPos)
{
  /*
  ** GSA- GNSS DOP and Active Satellites  ����PRN����
  **
  **        1 2 3 4 5        14 15  16  17   18
  **        | | | | |         |  |   |   |   |
  ** $--GSA,x,x,x,x,x,,,,,,,,,x,x.x,x.x,x.x*hh<CR><LF> 
  ** $--GSA,A,2,22,25,03,,,,,,,,,,2.5,2.3,1.0*30 
  **
  ** Field Number: 
  **  1) Mode1   A = Automatic- allowed to automatically switch 2D/3D  -�Զ�
  **             M = Manual-forced to operate in 2D OR 3d mode  -�ֶ�
  **  2) Mode2   0 = Fix not available  -δ��λ
  **             1 = 2D
  **             2 = 3D
  **  3) Sv Channel 1  -��1�ŵ�����ʹ�õ�����PRN��α��������룩���� 01-32 ���ɽ���12��������Ϣ
  **  4) Sv Channel 2  -��2�ŵ�����ʹ�õ�����PRN��α��������룩����
  **  ...... 5-3, 6-4, 7-5, 8-6, 9-7, 10-8, 11-9, 12-10, 13-11
  **  14) Sv Channel 12  -��12�ŵ�����ʹ�õ�����PRN��α��������룩����
  **  15) PDOP - Position Dilution of Precision  -�ۺ�λ�þ�������(0.5-99.9)
  **  16) HDOP - Horizontal Dilution of Precision  -ˮƽ��������(0.5-99.9)
  **  17) VDOP - Vertical Dilution of Precision  -��ֱ��������(0.5-99.9)
  **  18) Checksum  -У���
  */
  //
  if(m_token.Trim(str, 20) < 18)
  {
    return;
  }

  //
  if(*m_token[15] && *m_token[16] && *m_token[17])
  {
    gpsPos->m_PDOP = ::atof(m_token[15]);
    gpsPos->m_HDOP = ::atof(m_token[16]);
    gpsPos->m_VDOP = ::atof(m_token[17]);
  }
}

/**
*
*/
void CNmeaPro::ParseGSV(const char *str, GpsBasic *gpsPos)
{
  /*
  ** GSV- GNSS GPS Satellites in View ����״̬��Ϣ
  **
  **        1 2 3 4 5 6 7 8      12      16       20
  **        | | | | | | | |       |       |        | 
  ** $--GSV,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x*hh<CR><LF>
  ** $--GSV,2,1,08,22,68,011,30,03,55,196,35,25,45,120,34,18,41,282,*72 
  ** $--GSV,2,2,08,13,24,311,,19,16,308,,17,16,076,,31,14,211,*77 
  ** $--GSV,3,3,09,28,12,176,*49 
  **
  ** Field Number: 
  **  1) Number of Messages (Range 1 to 3)  �ܵ�GSV��������
  **  2) Message Number (Range 1 to 3)  ��ǰGSV���ID
  **  3) Satellite in View  ������������
  **  4) Satellite ID (Channel 1 - Range 1 to 32) -���Ǳ��(Satellite ID)  ��Χ1-32
  **  5) Elevation    (Channel 1 - Maximum 90) - degree  -��������(Elevation)  ���90��
  **  6) Azimuth      (Channel 1 - True, Range 0 to 359) - degree  -���Ƿ�λ��(Azimuth)  0-359
  **  7) SNR (C/No)   (Channel 1 - Range 0 to 99, null when not tracking) - dBHz  -SNR -����� ��Χ0-99
  **  8) Satellite ID (Channel 2 - Range 1 to 32)  -���Ǳ��
  **  9) Elevation    (Channel 2 - Maximum 90) - degree -��������
  **  10) Azimuth     (Channel 2 - True, Range 0 to 359) - degree -���Ƿ�λ��
  **  11) SNR (C/No)  (Channel 2 - Range 0 to 99, null when not tracking) - dBHz -�����
  **  12) Satellite ID(Channel 3 - Range 1 to 32)  -���Ǳ��
  **  13) Elevation   (Channel 3 - Maximum 90) - degree  -��������
  **  14) Azimuth     (Channel 3 - True, Range 0 to 359) - degree  -���Ƿ�λ��
  **  15) SNR (C/No)  (Channel 3 - Range 0 to 99, null when not tracking) - dBHz -�����
  **  16) Satellite ID(Channel 4 - Range 1 to 32)  -���Ǳ��
  **  17) Elevation   (Channel 4 - Maximum 90) - degree  -��������
  **  18) Azimuth     (Channel 4 - True, Range 0 to 359) - degree  -���Ƿ�λ��
  **  19) SNR (C/No)  (Channel 4 - Range 0 to 99, null when not tracking) - dBHz -�����
  **  20) Checksum  -У���
  */
  // Get four satellite description
  int order = m_token.Trim(str, 20);

  //����GPV�����ܻ����1-3����ÿ�����4�����ǣ����Կ��ܳ��ֲ���4�ŵ������
  //������ﲻ�ܸ���20�����ж��Ƿ��˳�
  //if (order < 20)
  //{
  //  return;
  //}

  if (order > 19)
  {
    int id = ::atoi(m_token[16]);
    if(id)
    {
      GetSatellite(1, id, ::atoi(m_token[17]), ::atoi(m_token[18]), atoi(m_token[19]), gpsPos);
    }
  }

  if (order > 15)
  {
    int id = ::atoi(m_token[12]);
    if(id)
    {
      GetSatellite(1, id, ::atoi(m_token[13]), ::atoi(m_token[14]), atoi(m_token[15]), gpsPos);
    }
  }

  if (order > 11)
  {
    int id = ::atoi(m_token[8]);
    if(id)
    {
      GetSatellite(1, id, ::atoi(m_token[9]), ::atoi(m_token[10]), atoi(m_token[11]), gpsPos);
    }
  }

  if (order > 7)
  {
    int id = ::atoi(m_token[4]);
    if(id)
    {
      GetSatellite(1, id, ::atoi(m_token[5]), ::atoi(m_token[6]), atoi(m_token[7]), gpsPos);
    }
  }
}

/**
*
*/
void CNmeaPro::GetGpsTime(const char *strDate, const char *strTime, GpsBasic *gpsPos)
{
  assert(gpsPos);

  //
  char tmp[3];
  tmp[2] = 0;

  //
  if(strDate)
  {
    if(::strlen(strDate) < 6)
    {
      return;
    }

    // Get day
    tmp[0] = strDate[0];
    tmp[1] = strDate[1];
    gpsPos->m_gpsTime.m_day = ::atoi(tmp);

    // Get month
    tmp[0] = strDate[2];
    tmp[1] = strDate[3];
    gpsPos->m_gpsTime.m_month = ::atoi(tmp);

    // Get year
    tmp[0] = strDate[4];
    tmp[1] = strDate[5];
    gpsPos->m_gpsTime.m_year = ::atoi(tmp);

    // Note:
    // Below code give it lifetime implicitly, woops!
    if(gpsPos->m_gpsTime.m_year < 80)
    {
      gpsPos->m_gpsTime.m_year += 2000;
    }
    else if(gpsPos->m_gpsTime.m_year >= 75)
    {
      gpsPos->m_gpsTime.m_year += 1900;
    }
  }

  //
  if(::strlen(strTime) < 6)
  {
    return;
  }

  // Get hour
  tmp[0] = strTime[0];
  tmp[1] = strTime[1];
  gpsPos->m_gpsTime.m_hour = ::atoi(tmp);

  // Get miniute
  tmp[0] = strTime[2];
  tmp[1] = strTime[3];
  gpsPos->m_gpsTime.m_min = ::atoi(tmp);

  // Get second
  tmp[0] = strTime[4];
  tmp[1] = strTime[5];
  gpsPos->m_gpsTime.m_sec = ::atoi(tmp);

  // Get milli second
  gpsPos->m_gpsTime.m_mSec = 0;
  if(strTime[6] == '.')
  {
    gpsPos->m_gpsTime.m_mSec = ::atoi(strTime + 7);
  }
}

/**
* Note: The execution of this function should be moved to struct PosBasic since it is only a simple conversion
*/
void CNmeaPro::GetLocalTime(GpsBasic *gpsPos)
{
  // Exceptions
  assert(gpsPos);

  //
  gpsPos->m_localTime = gpsPos->m_gpsTime;
  if(gpsPos->m_localTime.m_month < 1 || gpsPos->m_localTime.m_month > 12)
  {
    return;
  }

  // Switch to miniutes
  long local = gpsPos->m_localTime.m_hour * 60 + gpsPos->m_localTime.m_min - gpsPos->m_timeBias;
  int dayShift = 0;
  if(local < 0)
  {
    local += (24 * 60);
    dayShift = -1;
  }
  else if(local > (24 * 60))
  {
    local -= (24 * 60);
    dayShift = +1;
  }

  // Miniute, hour, day
  gpsPos->m_localTime.m_hour = static_cast<unsigned short>((local/60) % 24);
  gpsPos->m_localTime.m_min = static_cast<unsigned short>(local % 60);
  gpsPos->m_localTime.m_day += dayShift;

  // Month
  int days[] = {0, 31,29,31,30,31,30,31,31,30,31,30,31};
  int oneMonth = 28;

  if(gpsPos->m_localTime.m_month == 2)
  {
    if((gpsPos->m_localTime.m_year % 4) == 0 && (gpsPos->m_localTime.m_year % 4) != 100)
    {
      oneMonth = 29;
    }
  }
  else
  {
    oneMonth = days[gpsPos->m_localTime.m_month];
  }

  //
  if(gpsPos->m_localTime.m_day > oneMonth)
  {
    gpsPos->m_localTime.m_day = 1;
    gpsPos->m_localTime.m_month++;

    //
    if(gpsPos->m_localTime.m_month > 12)
    {
      gpsPos->m_localTime.m_year++;
      gpsPos->m_localTime.m_month = 1;
    }
  }
}

/**
*
*/
double CNmeaPro::GetGpsAngle(const char *str, GpsBasic *gpsPos, bool isLat)
{
  assert(gpsPos);

  //
  const char *pt = ::strchr(str, '.');
  if(!pt)
  {
    return 0.;
  }

  // 
  int miniute = ::atoi(str);
  PosAngle &oneAngle = (isLat) ? gpsPos->m_latAngle : gpsPos->m_lonAngle;

  //
  oneAngle.m_degree = miniute/100;
  oneAngle.m_min = miniute - oneAngle.m_degree * 100;

  //
  double fVal = ::atof(pt);
  double fSec = fVal * 60;
  oneAngle.m_sec = static_cast<int>(fSec);
  oneAngle.m_mSec = static_cast<int>((fSec - static_cast<double>(oneAngle.m_sec)) * 1000. + .5);

  //
  return static_cast<double>(oneAngle.m_degree) + static_cast<double>(oneAngle.m_min/60.) + fVal/60.;
}

/**
*
*/
void CNmeaPro::GetSatellite(int isSeen, int id, int alt, int azimuth, int snr, GpsBasic *gpsPos)
{
  assert(gpsPos);

  //
  if (m_isSameGroup)
  {
    m_isSameGroup = false;
    gpsPos->m_curSatellite = 0;
  }
  else if(gpsPos->m_curSatellite >= 24)
  {
    return;
  }

  //
  if(gpsPos->m_minSnr > snr)
  {
    gpsPos->m_minSnr = (snr/10) * 10;
  }

  if(gpsPos->m_maxSnr < snr)
  {
    gpsPos->m_maxSnr = (snr/10 + 1) * 10;
  }

  if(gpsPos->m_maxSnr < 50)
  {
    gpsPos->m_maxSnr = 50;
  }

  //
  gpsPos->m_satellites[gpsPos->m_curSatellite].m_id = id;
  gpsPos->m_satellites[gpsPos->m_curSatellite].m_isSeen = isSeen;
  //ע���ֵ��С�����ķ�Χ��0-90�ȣ�����������ܴ�������ֵalt������65136����m_alt���з���short��������������Խ�磬����Ӱ��.
  gpsPos->m_satellites[gpsPos->m_curSatellite].m_alt = alt; 
  gpsPos->m_satellites[gpsPos->m_curSatellite].m_azimuth = azimuth;
  gpsPos->m_satellites[gpsPos->m_curSatellite].m_snr = snr;
  gpsPos->m_curSatellite++;
}
