#ifndef _UEGUI_MAPSTATUSBARHOOK_H
#define _UEGUI_MAPSTATUSBARHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"

namespace UeGui
{
  class UEGUI_CLASS CMapStatusBarHook : public CAggHook
  {
  public:
    enum MapStatusBarHookCtrlType
    {
      MapStatusBarHook_Begin = 0,
      MapStatusBarHook_NaviStatuBarLeft,
      MapStatusBarHook_NaviStatuBarCenter1,
      MapStatusBarHook_NaviStatuBarCenter2,
      MapStatusBarHook_NaviStatuBarRight,
      MapStatusBarHook_Interval1,
      MapStatusBarHook_Interval2,
      MapStatusBarHook_Interval3,
      MapStatusBarHook_SpeedMeterIcon,
      MapStatusBarHook_SpeedLabel,
      MapStatusBarHook_LocationLabel,
      MapStatusBarHook_ClockIcon,
      MapStatusBarHook_ClockLabel,
      MapStatusBarHook_DestinationIcon,
      MapStatusBarHook_RemainingTimeLabel,
      MapStatusBarHook_End
    };

    CMapStatusBarHook();

    virtual ~CMapStatusBarHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  public:
    /*
    * ��ʾ״̬����
    * \param speed ��ǰ��ʻ�ٶ�
    * \param content ��ʾ���ݵ�·����
    * \param timeStr ��ǰϵͳʱ���ַ���
    * \param remainingTimeStr ����Ŀ�ĵ�ʣ��ʱ��
    */
    void ShowStatusInfo(double speed, const char* content, const char* timeStr, const char* remainingTimeStr);
    /*
    * ˢ�µ�ǰ��ʻ�ٶ���Ϣ
    */
    void RefreshSpeed(double speed);
    /*
    * ˢ�µ�ǰ��ʻ��·��Ϣ
    */
    void RefreshContent(const char* content);
    /*
    * ˢ�µ�ǰϵͳʱ����Ϣ
    */
    void RefreshTime(short hour, short minute);
    /*
    * ˢ�µ�ǰ��ʻʣ��ʱ����Ϣ
    */
    void RefreshRemainingTime(short hour, short minute);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    virtual void MakeControls();

  private:
    //��ǰ��ʻ�ٶ�
    CUiLabel m_speedLabelCtrl;
    //��ǰλ����Ϣ
    CUiLabel m_locationLabelCtrl;
    //��ǰϵͳʱ��
    CUiLabel m_clockLabelCtrl;
    //ʣ�����ʱ��
    CUiLabel m_remainingTimeLabelCtrl;   
  };
}
#endif
