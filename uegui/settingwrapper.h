/*
* ����ӿ� 2012-09-03
*/

#ifndef _UEGUI_SETTINGWRAPPER_H
#define _UEGUI_SETTINGWRAPPER_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "uebase/uemaps.h"
#include "uebase/uemapsio.h"
#include "uebase/uesettingio.h"

using namespace UeBase;

// Declare namespace UeGui
namespace UeGui
{
  class UEGUI_CLASS CSettingWrapper : public UeBase::CUeSettingsIO
  {
  public:
    /**
    * \brief ��������
    */
   ~CSettingWrapper();
		/*!
		* \brief ��ȡ����
		*/
    static CSettingWrapper& Get();
  private:
    /**
    * \brief ���캯��
    */
    CSettingWrapper();
  public:
    /*
    * ��ʼ��
    */
    bool Restore();
    //���ļ��ж�ȡ����
    bool ReadSettings();
    //�����������õ��ļ���
    bool SaveAllSettings();
    //���浼������
    bool SaveNaviationSettings();
    //����ϵͳ����
    bool SaveSystemSettings();
    /**
    * \brief ��ȡ��ͼ����
    * \return ����m_viewSettings������
    */
    const ViewSettings& GetViewSettings();
    //////////////////////////////////////////////////////////////////////////
    //��ȡ��ͼģʽ ����ֵ��鿴����:MapModel
    unsigned char GetMapModel();
    //���õ�ͼģʽ ����vlaueֵΪMapModel����
    void SetMapModel(const unsigned char value);
    //��ȡ��ͼ��� ����ֵ���ͣ�MapStype
    unsigned char GetMapStyle();
    //���õ�ͼ��� ����valueֵΪMapStype����
    void SetMapStype(const unsigned char value);
    //��ȡ������ͼ���� ����ֵ��鿴����:MapDirection
    unsigned char GetMapDirection();
    //���õ�����ͼ����  ����valueֵΪMapDirection����
    void SetMapDirection(const unsigned char value);
    //��ȡ·���Զ��Ŵ���ʾ 0:����ʾ(OS_OFF) 1����ʾ(OS_ON)
    unsigned char GetCrossingAmplify();
    //����·���Զ��Ŵ���ʾ 0:����ʾ(OS_OFF) 1����ʾ(OS_ON)
    void SetCrossingAmplify(const unsigned char value);
    /**
    * \brief ��ȡ����������ʾ
    * \detail ���ؽ�� 0:����ʾ(OS_OFF) 1����ʾ(OS_ON)
    */
    unsigned char GetCompassPrompt();
    /**
    * \brief ���÷���������ʾ
    * \param value 0:����ʾ(OS_OFF) 1����ʾ(OS_ON)
    * \detail
    */
    void SetCompassPrompt(const unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    /**
    * \brief ��ȡ·�ڷŴ�ͼ�Ƿ���
    * \param value 0:����ʾ(OS_OFF) 1����ʾ(OS_ON)
    * \detail
    */
    unsigned char GetIsOpenCrossingMap();
    /**
    * \brief ����·�ڷŴ�ͼ����״̬
    * \param value 0:������(OS_OFF) 1������(OS_ON)
    * \detail
    */
    void SetIsOpenCrossingMap(const unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    /*
    * \brief ��ȡ�Ƿ����õ�������ʾ
    * \return   0:������(OS_OFF) 1������(OS_ON)
    */
    unsigned char GetIsEEyeOpen();
    /*
    * \brief �����Ƿ����õ�������ʾ
    * \return 0:������(OS_OFF) 1������(OS_ON)
    */
    void SetIsEEyeOpen(const unsigned char value);
    /*
    * \brief ��ȡ��������ʾ��ϸ��Ϣ ������ֵ������ElectronicEye�ֱ����������
    * \return ���ؽ��������ElectronicEye������Ԥ�����ж�
    */
    unsigned char GetEEyeType();
    /*
    * \brief ���õ�������ʾ��ϸ��Ϣ ����valueΪ����ѡ�������ElectronicEye����������Ľ��
    * \param value������ElectronicEye��������
    */
    void SetEEyeType(const unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ������ʾ���ͣ����ؽ������ NavigationPromptType ������ʾ ��ϸ��ʾ 
    unsigned char GetNavigationPromptType();
    //���õ�����ʾ ����value����Ϊ NavigationPromptType
    void SetNavigationPromptType(const unsigned char value);
    //��ȡ���������ٶ�, �ٶ�Ϊ0��ʾ������
    unsigned short GetHighWayRemindingSpeed();
    //���ø��������ٶ�, �ٶ�Ϊ0��ʾ������
    void SetHighWayRemindingSpeed(const unsigned short value);
    //��ȡ���������ٶ�, �ٶ�Ϊ0��ʾ������
    unsigned short GetNationalRoadRemindingSpeed();
    //���ù��������ٶ�, �ٶ�Ϊ0��ʾ������
    void SetNationalRoadSpeed(const unsigned short value);
    //��ȡ������·�����ٶ�, �ٶ�Ϊ0��ʾ������
    unsigned short GetOtherRoadRemindingSpeed();
    //����������·�����ٶ�, �ٶ�Ϊ0��ʾ������
    void SetOtherRoadRemindingSpeed(const unsigned short value);
    //////////////////////////////////////////////////////////////////////////
    /*
    * ��ȡ·������ ����ֵ����Ϊ RouteWay (routebasic.h)
    * ע��:��ȡ���ΪRouteSettings::RouteWay Ҫת����UeRoute::RouteWay
    */
    unsigned char GetRouteType();
    /*
    * ����·������ ����value����Ϊ RouteWay
    * ע��:��ȡ���ΪRouteSettings::RouteWay Ҫת����UeRoute::RouteWay
    */
    void SetRouteType(const unsigned char value);
    /*
    * ��ȡ�ر�·������ ����ֵ������RouteAvoidance �ֱ����������õ����
    * ע�⣺��ȡ�Ľ����ʹ��ʱҪת����UeRoute::RouteAvoidance(routebasic.h)
    */
    unsigned int GetAvoidRoute();
    /**
    * detail ���ûر�·������ ����valueΪ����ѡ������� RouteAvoidance ����������Ľ��
    * ע�⣺����ʱҪ�Ƚ�UeRoute::RouteAvoidance(routebasic.h)ת���ɶ�Ӧ��RouteSettings::RouteAvoidance
    */
    void SetAvoidRoute(const unsigned int value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ�켣�ɼ��ܶ� ����ֵ���� CaptureType
    unsigned char GetCaptureDensity();
    //���ù켣�ɼ��ܶ� ����value����Ϊ CaptureType
    void SetCaptureDensity(const unsigned char value);
    //��ȡ�켣�ɼ��ٶ����� ����ֵ���� CaptureType
    unsigned char GetCaptureSpeedLimit();
    //���ù켣�ɼ��ٶ����� ����value����Ϊ CaptureType
    void SetCaptureSpeedLimit(const unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ��ȫ���ÿ���״̬ 0:������(OS_OFF) 1������(OS_ON)
    unsigned char GetSafetySet();
    //���ð�ȫ���ÿ���״̬ 0:������(OS_OFF) 1������(OS_ON)
    void SetSafety(unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ�Ƿ������� True:���� False:�Ǿ���
    bool IsLoudSpeakerMute();
    //�����Ƿ�������  True:���� False:�Ǿ���
    void SetIsLoudSpeakerMute(bool value);
    //��ȡ������С:0-7
    unsigned short GetVoice();
    //����������С:0-7
    void SetVoice(unsigned short value);
    //��ȡ��ʾ����Ϣ ���ؽ����VoiceType����������
    unsigned char GetVoicePrompt();
    //������ʾ����Ϣ ����valueΪ VoiceType ������������
    void SetVoicePrompt(unsigned char value);
    //��ȡ��������
    unsigned char GetLanguage();
    //������������
    void SetLanguage(unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ�Գ�ͼ��
    unsigned short GetCarIcon();
    //�����Գ�ͼ��
    void SetCarIcon(unsigned short value);
    //����3d�Գ�ͼ��
    void Set3DCarIcon(unsigned short carIcon);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ�Ƿ���ʱ��У׼ 0:������(OS_OFF) 1������(OS_ON)
    unsigned char GetIsOpenTimeCalibration();
    //�����Ƿ���ʱ��У׼ 0:������(OS_OFF) 1������(OS_ON)
    void SetIsOpenTimeCalibration(unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ�Ƿ����������� 0:������(OS_OFF) 1������(OS_ON)
    unsigned char GetIsOpenStartStatement();
    //�����Ƿ����������� 0:������(OS_OFF) 1������(OS_ON)
    void SetIsOpenStartStatement(unsigned char value);
    //////////////////////////////////////////////////////////////////////////
    /*
    * ��ȡ�˿�
    * return value 1(COM1) 2(COM2) ......
    */
    unsigned char GetGPSPort();
    /*
    * ���ö˿�
    * param value 1(COM1) 2(COM2) ......
    */
    void SetGPSPort(unsigned char port);
    /*
    * ��ȡ�˿ڲ�����
    * return value 1200,4800,9600 ......
    */
    unsigned int GetGPSBaudRate();
    /*
    * ���ö˿ڲ�����
    * param value 1(COM1) 2(COM2) ......
    */
    void SetGPSBaudRate(unsigned int baudRate);
    /*
    * ��ȡ������ʽ
    * return value 1(COM1) 2(COM2) ......
    */
    unsigned char GetGPSStartMode();
    /*
    * ����������ʽ
    * param value 1(COM1) 2(COM2) ......
    */
    void SetGPSStartMode(unsigned char startMode);
    //////////////////////////////////////////////////////////////////////////
    //��ȡ��ʷ��¼����
    unsigned int GetHistoryRecordCapacity();
    //��ȡ��ʷ·������
    unsigned int GetHistoryRouteCapacity();
    //��ȡ��ʷ�켣����
    unsigned int GetHistoryTrajectoryCapacity();
    //��ȡ��ַ������
    unsigned int GetAddressBookCapacity();
    //��ȡ�ҵ��г�����
    unsigned int GetMyJourneyCapacity();
    //////////////////////////////////////////////////////////////////////////
  private:
    // ��ͼ����
    ViewSettings m_viewSettings;
    // ��������
    VoiceSettings m_voiceSettings;
    // ·������
    RouteSettings m_routeSettings;
    // ϵͳ����
    SystemSettings m_systemSettings;
    // ��ѯ����
    QuerySettings m_querySettings;
    // ��������
    CapacityInfo m_capacityInfo;
  };
}

#endif