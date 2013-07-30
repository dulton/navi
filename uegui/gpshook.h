#ifndef _UEGUI_GPSHOOK_H
#define _UEGUI_GPSHOOK_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to its parent
#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

// Qcode
#ifndef __Q_CODE_H__
#include "QCode.h"
#pragma comment(lib,"QCode.lib")
#endif

#include "uibutton.h"
#include "uilabel.h"


// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z

namespace UeGui
{
  class UEGUI_CLASS CGpsHook : public CAggHook
  {
  public:
    //��������ֵ
    static const int kMAXSNR = 99;

    enum GpsCtrlType
    {
      GpsHook_Begin = 0,
      GpsHook_Background,
      GpsHook_Title,
      GpsHook_GoToMapButton,
      GpsHook_ReturnButton,
      GpsHook_DateLabel,
      GpsHook_Date,
      GpsHook_WeekLabel,
      GpsHook_Week,
      GpsHook_TimeLabel,
      GpsHook_Time,
      GpsHook_SatelliteNumLabel,
      GpsHook_SatelliteNum,
      GpsHook_LocationNumLabel,
      GpsHook_LocationNum,
      GpsHook_ReceivingStateLabel,
      GpsHook_ReceivingState,
      GpsHook_SpeedLabel,
      GpsHook_Speed,
      GpsHook_TravelTimeLabel,
      GpsHook_TravelTime,
      GpsHook_RunningDistanceLabel,
      GpsHook_RunningDistance,
      GpsHook_QCodeLabel,
      GpsHook_QCode,
      GpsHook_EarthMap,
      GpsHook_LocateStatus,
      GpsHook_MarkCtrlLeft,
      GpsHook_MarkCtrlCenter,
      GpsHook_MarkCtrlRight,
      GpsHook_SNROne,
      GpsHook_SNRTwo,
      GpsHook_SNRThree,
      GpsHook_SNRFour,
      GpsHook_SNRFive,
      GpsHook_SNRSix,
      GpsHook_SNRSeven,
      GpsHook_SNREight,
      GpsHook_SNRNine,
      GpsHook_SNRTen,
      GpsHook_SNREleven,
      GpsHook_SNRTwelve,
      GpsHook_SNROneBack,
      GpsHook_SNRTwoBack,
      GpsHook_SNRThreeBack,
      GpsHook_SNRFourBack,
      GpsHook_SNRFiveBack,
      GpsHook_SNRSixBack,
      GpsHook_SNRSevenBack,
      GpsHook_SNREightBack,
      GpsHook_SNRNineBack,
      GpsHook_SNRTenBack,
      GpsHook_SNRElevenBack,
      GpsHook_SNRTwelveBack,
      GpsHook_Point1,
      GpsHook_Point2,
      GpsHook_Point3,
      GpsHook_Point4,
      GpsHook_Point5,
      GpsHook_Point6,
      GpsHook_Point7,
      GpsHook_Point8,
      GpsHook_Point9,
      GpsHook_Point10,
      GpsHook_Point11,
      GpsHook_Point12,
      GpsHook_End
    };

    CGpsHook();

    virtual ~CGpsHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Load();

    void Update();


  public:
    void Gps2Scr(short elevation, short azimuth, CGeoPoint<int> &scrPt);

    short Elv2Rad(short elevation);

  protected:

    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

  public:
    /**
    * \brief ���õ�ǰ��λ����
    **/
    void SetCurLocationNum(int curLocationNum);

    /**
    * \brief ���õ�ͼ�����������
    **/
    int GetCurLocationNum();

  private:
    /**
    * �ж��Ƿ�����
    */
    int IsLeapYear(int year);
    /**
    * ��������ת��������
    */
    int DateToWeek(int year,int month, int day);
    /**
    * ��ʾ������
    */
    void OutputWeek(int week);
    /**
    * ��ʼ�����ǵĽ����ź�ǿ��
    */
    void InitSatelliteStatus();
    /**
    * ��������ID���ø������ǵĽ����ź�ǿ��
    */
    void SetSatelliteStatus(int id, int snr);
    /**
    * ��������Ȼ�ȡ�ؼ���ʾ����
    */
    int GetWidth(int snr);
    /**
    * ��������λ���ڵ���ͼ������ʾ����
    * parm elevation ���Ƿ�λ��
    * parm azimuth ��������
    */
    void ShowSatellite(int id, short elevation, short azimuth);
    /**
    * ��ȡ����ͼ��Ԫ��
    */
    GuiElement* GetSatlliteElement(int id);
    /**
    * �����¶�λ���Ǹ���
    */
    void UpdateLocationSatelliteNum();
  private:
    //�򿪵�ͼ
    CUiButton m_goToMapButtonCtrl;
    //����
    CUiButton m_returnButtonCtrl;
    //����
    CUiLabel m_dateCtrl;
    //����
    CUiLabel m_weekCtrl;
    //ʱ��
    CUiLabel m_timeCtrl;
    //���Ǹ���
    CUiLabel m_satelliteNumCtrl;
    //��λ����
    CUiLabel m_locationNumCtrl;
    //����״̬
    CUiButton m_receivingStateCtrl;
    //˲ʱ�ٶ�
    CUiLabel m_speedCtrl;
    //��ʻʱ��
    CUiLabel m_travelTimeCtrl;
    //��ʻ����
    CUiLabel m_runningDistanceCtrl;
    //Q��
    CUiLabel m_qCodeCtrl;
    //��λ״̬
    CUiButton m_locateStatusCtrl;
    //��¼�ź�
    CUiButton m_markCtrl;
    //�����ź�ǿ��
    CUiButton m_sNROneCtrl;
    CUiButton m_sNRTwoCtrl;
    CUiButton m_sNRThreeCtrl;
    CUiButton m_sNRFourCtrl;
    CUiButton m_sNRFiveCtrl;
    CUiButton m_sNRSixCtrl;
    CUiButton m_sNRSevenCtrl;
    CUiButton m_sNREightCtrl;
    CUiButton m_sNRNineCtrl;
    CUiButton m_sNRTenCtrl;
    CUiButton m_sNRElevenCtrl;
    CUiButton m_sNRTwelveCtrl;
    CUiButton m_point1;
    CUiButton m_point2;
    CUiButton m_point3;
    CUiButton m_point4;
    CUiButton m_point5;
    CUiButton m_point6;
    CUiButton m_point7;
    CUiButton m_point8;
    CUiButton m_point9;
    CUiButton m_point10;
    CUiButton m_point11;
    CUiButton m_point12;
  private:        
    //��ǰ���ǵĸ���
    int m_curLocationNum;
    //����ͼ��뾶
    int m_earthRadius;
    //����X������
    int m_earthCenterX;
    //����Y������
    int m_earthCenterY;
    //�����������ʾ�ؼ��Ŀ��
    unsigned int m_maxSNRWidth;

    unsigned char m_timeStatus;
  };
}
#endif
