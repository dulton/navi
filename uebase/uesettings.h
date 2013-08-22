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
#ifndef _UEBASE_UESETTINGS_H
#define _UEBASE_UESETTINGS_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

//
#ifndef _UEBASE_GEOMBASIC_H
#include "geombasic.h"
#endif

//Ĭ�ϳ���
#define DefaultCarIcon 287
#define Default3DCarIcon 297

namespace UeBase
{
#pragma pack(1)
  //����״̬
  enum OnOffStatus
  {
    OS_OFF = 0, //�ر�, ��
    OS_ON  = 1  //��������
  };

  //·�����ͣ���routebasic.h����
  //RW_Fast = 1 ��������
  //RW_Short = 2 һ���·
  //RW_Optimal = 32 �Ƽ�·��

  //////////////////////////////////////////////////////////////////////////
  /**
  * \brief �����ļ����ļ�ͷ
  */
  struct SettingsHeader
  {
    char m_version[24];
  };

  /**
  * \brief ��ͼ��ʾ������ò���
  */
  struct ViewSettings
  {
    //��ͼģʽ����
    enum MapModel
    {
      MM_Atuo,    //�Զ�ģʽ
      MM_DayTime, //����ģʽ
      MM_Night    //ҹ��ģʽ    
    };
    //��ͼ���
    enum MapStype
    {
      MS_Snowy,   //ĺѩ��˪
      MS_Fairily  //���ŵ���
    };
    //������ͼ����
    enum MapDirection
    {
      MD_DueNorth, //�������� �ɣ���Ϊ����
      MD_HeadMap,  //ͼ�泵ת �ɣ���Ϊ����
      MD_25DMap    //���ӵ�ͼ �ɣ����        
    };
    enum ZoomingModel
    {
      ZM_Auto,  //�Զ�
      ZM_Fixed  //�̶�
    };

    //������ʾ����
    enum ContentModel
    {
      NP_Simple   = 0, //��ͼ  
      NP_Normal   = 1, //����
      NP_Detailed = 2 //��ϸ              
    };

    /// Previous coordinates
    CGeoPoint<long> m_prevCoord;		

    /// ��ͼģʽ����鿴����:MapModel 
    unsigned char m_colorModel; 
    unsigned char m_fixedColor;

    ///��ͼ�����鿴����:MapStype
    unsigned char m_mapStyle;
    unsigned char m_fixedStyle;

    /// ������ͼ������鿴����:MapDirection
    unsigned char m_stateModel;	    
    unsigned char m_fixedState;

    /// ·���Զ��Ŵ���ʾ
    unsigned char m_crossingAmplify; //0:���Զ��Ŵ� 1���Զ��Ŵ�
    /// ����������ʾ
    unsigned char m_compassPrompt;  //0������������������ʾ 1����������������ʾ

    ///�Ƿ���·�ڷŴ�ͼ
    unsigned char m_isOpenCrossingImage; //0:�ر� 1������

    /// ContentModel
    /// 0 - Simplified  ��ͼ
    /// 1 - Normal ����
    /// 2 - Detailed ��ϸ
    unsigned char m_contentModel;	
    unsigned char m_fixedContent;

    /// 0 - Auto 
    /// 1 - Fixed
    unsigned char m_zoomingModel;   //���� ZoomingModel
    unsigned char m_fixedZooming;

    //
    unsigned char m_reserved[240];

    /**
    * \brief Ĭ�Ϲ��캯��
    */
    ViewSettings() : m_colorModel(MM_Atuo), m_fixedColor(MM_Atuo) ,m_mapStyle(MS_Snowy), m_fixedStyle(MS_Snowy),
      m_stateModel(MD_DueNorth), m_fixedState(MD_DueNorth), m_crossingAmplify(OS_OFF), m_compassPrompt(OS_OFF),
      m_contentModel(NP_Detailed), m_fixedContent(NP_Detailed), m_zoomingModel(ZM_Auto), m_fixedZooming(ZM_Auto), m_isOpenCrossingImage(OS_ON)     
    {
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }

    /**
    * \brief �ָ�Ĭ������
    */
    void Restore()
    {
      m_colorModel = MM_Atuo;
      m_mapStyle = MS_Snowy;
      m_stateModel = MD_DueNorth;
      m_crossingAmplify = OS_OFF;
      m_compassPrompt = OS_ON;
      m_isOpenCrossingImage = OS_ON;
      m_contentModel = NP_Detailed;
      m_zoomingModel = ZM_Auto;
    }
  };

  /**
  * \brief �滮������·�����ã�������ò���
  */
  struct RouteSettings
  {
    enum VehicleType
    {
      VT_Car,   //�γ�
      VT_Truck  //����
    };

    //�켣�ɼ��ܶ�����
    enum CaptureType
    {
      CT_Lower,  //���ܶ�
      CT_Middle, //���ܶ�
      CT_Hight   //���ܶ�
    };

    enum RouteWay
    {
      /// ����ٶ�
      RW_Fast     = 0x01,
      /// ���·��
      RW_Short    = 0x02,
      /// ���
      RW_Economic = 0x10,
      /// �Ƽ�·��
      RW_Optimal  = 0x20,
      /// �滮��ʽ������
      RW_Max      = 4
    };

    enum RouteAvoidance
    {
      RA_None      = 0x010000,
      /// ��ܸ���
      RA_HighWay   = 0x020000, 
      /// ����ֶ�
      RA_Ferry     = 0x040000, 
      /// ����շ�·
      RA_TollWay   = 0x080000, 
      /// ��ܵ�ͷ·
      RA_UTurn     = 0x100000, 
      /// ��ܵ͵ȼ�·
      RA_Condition = 0x200000, 
      /// ���Σ��·��
      RA_Dangerous = 0x400000, 
      /// ��ܸ߼�
      RA_OverPass  = 0x800000
    };


    unsigned char m_methodType;       //·������ 0:���(��������), 1:���(һ���·), 3:�Ƽ�·��
    unsigned char m_fixedMethod;      //Ĭ��ֵ

    unsigned char m_vehicleType;      //0:�γ�,1:����
    unsigned char m_fixedVehicle;     //Ĭ��ֵ

    unsigned char m_isAvoidHW;        //0:�����߸��� 1�����߸���
    unsigned char m_fixedHW;

    unsigned char m_isAvoidUTurn;     //0�������ߵ�ͷ 1���������ߵ�ͷ
    unsigned char m_fixedUTurn;


    unsigned char m_isAvoidFerry;    //0 �� �����ֶ� 1 �� �������ֶ�
    unsigned char m_fixedFerry;

    unsigned char m_isAvoidToll;      //0�������շ� 1:�����շ�
    unsigned char m_fixedToll;

    unsigned char m_isAvoidCondition; //0:����͵ȼ�· 1:���ߵ͵ȼ�·
    unsigned char m_fixedCondition;   //Ĭ��ֵ

    unsigned char m_isAvoidDangerous; //0:������Σ��·�� 1����������Σ��·��
    unsigned char m_fixedDangerous;   //Ĭ��ֵ

    unsigned char m_isAvoidOverPass;   //0:�����߸߼� 1���������߸߼�
    unsigned char m_fixedOverPass;     //Ĭ��ֵ

    //----------------------
    unsigned char m_captureDensity;    //�켣�ɼ��ܶ�  �� �� ��
    unsigned char m_captureSpeedLimit; //�켣�ɼ��ٶ����� �� �� ��
    unsigned char m_safetySet;         //0:������ 1������ ��ȫ���ó���30���ﲻ����������
    //----------------------
    unsigned char m_reserved[244];
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    RouteSettings() : m_methodType(RW_Fast), m_fixedMethod(RW_Fast), m_vehicleType(VT_Car), m_fixedVehicle(VT_Car),  
      m_isAvoidHW(OS_OFF), m_fixedHW(OS_OFF), m_isAvoidUTurn(OS_OFF), m_fixedUTurn(OS_OFF), m_isAvoidFerry(OS_OFF),
      m_fixedFerry(OS_OFF),m_isAvoidToll(OS_OFF), m_fixedToll(OS_OFF), m_isAvoidCondition(OS_OFF), m_fixedCondition(OS_OFF),
      m_isAvoidDangerous(OS_OFF), m_fixedDangerous(OS_OFF), m_isAvoidOverPass(OS_OFF), m_fixedOverPass(OS_OFF),
      m_captureDensity(CT_Middle), m_captureSpeedLimit(CT_Middle), m_safetySet(OS_ON)
    {
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }

    /**
    * \brief �ָ�Ĭ������
    */
    void Restore()
    {
      m_methodType = RW_Optimal;
      m_vehicleType = VT_Car;
      m_isAvoidHW = OS_OFF;
      m_isAvoidUTurn = OS_OFF;
      m_isAvoidFerry = OS_OFF;
      m_isAvoidToll = OS_OFF;
      m_isAvoidCondition = OS_OFF;
      m_isAvoidDangerous = OS_ON;
      m_isAvoidOverPass = OS_OFF;
      m_captureDensity = CT_Middle;
      m_captureSpeedLimit = CT_Middle;
      m_safetySet = OS_ON;
    }
  };

  /**
  * \brief ��ѯ��ص����ò���
  */
  struct QuerySettings
  {
    unsigned short m_gridKinds;
    unsigned short m_fixedGridKinds;

    unsigned short m_gridDistance; 
    unsigned short m_fixedGridDistance;

    unsigned char m_misses;
    unsigned char m_fixedMisses;

    unsigned char m_reserved[246];

    /**
    * \brief Ĭ�Ϲ��캯��
    */
    QuerySettings() : m_gridKinds(0), m_fixedGridKinds(0), m_gridDistance(1), m_fixedGridDistance(1), m_misses(0), m_fixedMisses(0)
    {
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }

    /**
    * \brief �ָ�Ĭ������
    */
    void Restore()
    {
      m_gridKinds = m_fixedGridKinds;
      m_gridDistance = m_fixedGridDistance;
      m_misses = m_fixedMisses;
    }
  };

  /**
  * \brief ������ص����ò���
  */
  struct VoiceSettings
  {
    //��������ʾ����
    enum ElectronicEye
    {
      EYE_TrafficLight      = 1<<0, //���������
      EYE_Speedding         = 1<<1, //��������
      EYE_IllegalMonitoring = 1<<2, //Υ����
      EYE_RailwayCrossing   = 1<<3  //��·����
    };
    //������ʾ����
    enum VoicePromptType
    {
      VP_Detailed = 0, //��ϸ��ʾ
      VP_Normal   = 1, //������ʾ
      VP_Simple   = 2  //����ʾ    
    };

    unsigned char m_broadcastName; //0:��ϸ 1:���� 2:��
    unsigned char m_fixedBroadcastName;
    unsigned short m_hwSpeed; //��������
    unsigned short m_fixedHwSpeed;
    unsigned short m_mainSpeed; //���ɵ����٣��������٣�
    unsigned short m_fixedMainSpeed;
    unsigned short m_otherSpeed; //��ͨ��·���٣��������٣�
    unsigned short m_fixedOtherSpeed;
    unsigned short m_eEyeOpen; //0:�رյ����� 1:����������
    unsigned short m_fixedeEyeOpen;    
    //-------------------------
    /// ��������
    unsigned char m_eEyeType; //����������,�õ�4λ����ʾ0000 1111����������գ��������գ�Υ���أ���·����
    //-------------------------
    unsigned char m_reserved[246];
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    VoiceSettings() : m_broadcastName(VP_Normal), m_fixedBroadcastName(VP_Normal), m_hwSpeed(120), m_fixedHwSpeed(120), m_mainSpeed(90), 
      m_fixedMainSpeed(100), m_otherSpeed(60), m_fixedOtherSpeed(60), m_eEyeOpen(OS_ON), m_fixedeEyeOpen(OS_ON)
    {
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }

    /**
    * \brief �ָ�Ĭ������
    */
    void Restore()
    {
      m_broadcastName = VP_Normal;
      m_hwSpeed = 120;
      m_mainSpeed = 90;
      m_otherSpeed = 60;
      m_eEyeOpen = OS_ON;
      m_eEyeType = 0;
      m_eEyeType |= VoiceSettings::EYE_TrafficLight;
      m_eEyeType |= VoiceSettings::EYE_Speedding;
      m_eEyeType |= VoiceSettings::EYE_IllegalMonitoring;
      m_eEyeType |= VoiceSettings::EYE_RailwayCrossing;
    }
  };

  /**
  * \brief ϵͳ������ز���
  */
  struct SystemSettings
  {
    //��������
    enum VoiceType
    {
      VT_KeyVoice     = 1<<0, //��������
      VT_DynamicVoice = 1<<1  //��̬����
    };
    enum StartMode
    {
      SM_Invalid = 0,
      SM_Normal,
      SM_Warm,
      SM_Cold            
    };
    unsigned char m_gpsStartMode;     //1:�������� 2:������ 3:������
    unsigned char m_fixedStartMode;

    unsigned char m_gpsPort;          //�˿ں�
    unsigned char m_fixedGpsPort;

    unsigned int m_gpsBaud;           //������
    unsigned int m_fixedGpsBaud;

    //�ò����Ƶ�VoiceSettings����
    unsigned int m_voice;             //����ֵ0-0xFFFFFFFF
    unsigned int m_fixedVoice;    

    //-------------------------
    // �����ֶ�
    unsigned char m_loudspeaker;        //0������ 1���Ǿ���
    unsigned char m_voicePrompt;        //����VoiceType �����ƵͶ�λ����ʾ�����ð����������ö�̬����
    unsigned char m_language;           //��������:��ͨ��-Ů�� ��ͨ��-�У��Ĵ������㶫������������̨�廰��
    unsigned short m_carIcon;           //�Գ�ͼ��
    unsigned short m_3DCarIcon;         //����ͼ���Գ�ͼ��
    unsigned char m_timeCalibration;    //ʱ��У׼ OS_OFF, OS_ON
    unsigned char m_startStatement;     //�Ƿ����������� OS_OFF, OS_ON
    unsigned char m_showShortcutPanel;  //�Ƿ����������� OS_OFF, OS_ON
    //-------------------------
    unsigned char m_reserved[242];
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    SystemSettings() : m_gpsStartMode(SM_Cold), m_fixedStartMode(SM_Cold), m_gpsPort(0), m_fixedGpsPort(0), 
      m_gpsBaud(0), m_fixedGpsBaud(0), m_voice(0x7FFFFFFF), m_fixedVoice(0x7FFFFFFF),
      m_language(0), m_carIcon(DefaultCarIcon), m_3DCarIcon(Default3DCarIcon), m_loudspeaker(1), m_voicePrompt(OS_ON), m_timeCalibration(OS_ON),
      m_startStatement(OS_ON), m_showShortcutPanel(OS_ON)
    {
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }

    /**
    * \brief �ָ�Ĭ������
    */
    void Restore()
    {
      m_gpsStartMode = 3;
      m_gpsPort = 0;
      m_gpsBaud = 0;
      m_voice = 0x7FFFFFFF;
      m_fixedVoice = 0x7FFFFFFF;
      m_loudspeaker = 1;
      m_voicePrompt = OS_ON;
      m_language = 0;
      m_carIcon = DefaultCarIcon;
      m_3DCarIcon = Default3DCarIcon;
      m_timeCalibration = OS_ON;
      m_startStatement = OS_ON;
      m_showShortcutPanel = OS_ON;
      ::memset(m_reserved, 0, sizeof(m_reserved));
    }
  };

  //ϵͳ������Ϣ
  struct CapacityInfo
  {
    unsigned int m_historyRecord;
    unsigned int m_historyRoute;
    unsigned int m_historyTrajectory;
    unsigned int m_addressBook;
    unsigned int m_myJourney;
    CapacityInfo() : m_historyRecord(50), m_historyRoute(25), m_historyTrajectory(10),
      m_addressBook(50), m_myJourney(25)
    {
    }
    void Restore()
    {
      m_historyRecord = 50;
      m_historyRoute = 25;
      m_historyTrajectory = 10;
      m_addressBook = 50;
      m_myJourney = 25;
    }
  };
#pragma pack()

}
#endif