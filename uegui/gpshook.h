#ifndef _UEGUI_GPSHOOK_H
#define _UEGUI_GPSHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

#ifndef __Q_CODE_H__
#include "QCode.h"
#pragma comment(lib,"QCode.lib")
#endif

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CGpsHook : public CMenuBackgroundHook
  {
  public:
    //��������ֵ
    static const int kMAXSNR = 76;

    enum GpsHookCtrlType
    {
      GpsHook_Begin = MenuBackgroundHook_End,
      GpsHook_Background,
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
      GpsHook_QCodeLabel,
      GpsHook_QCode,
      GpsHook_EarthMap,
      GpsHook_LocateStatus,
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
      GpsHook_SNRBack,
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

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Load();

    virtual void Timer();

    void Gps2Scr(short elevation, short azimuth, CGeoPoint<int> &scrPt);

    short Elv2Rad(short elevation);
    /**
    * \brief ���õ�ǰ��λ����
    **/
    void SetCurLocationNum(int curLocationNum);

    /**
    * \brief ���õ�ͼ�����������
    **/
    int GetCurLocationNum();

  protected:

    virtual void MakeNames();

    void MakeControls();

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
    //Q��
    CUiLabel m_qCodeCtrl;
    //��λ״̬
    CUiButton m_locateStatusCtrl;
    //��¼�ź�
    CUiButton m_markCtrl;
    //�����ź�ǿ��
    CUiButton m_sNRCtrl[12];
    CUiButton m_point[12];
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
