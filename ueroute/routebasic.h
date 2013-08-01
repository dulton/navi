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
#ifndef _UEROUTE_ROUTEBASIC_H
#define _UEROUTE_ROUTEBASIC_H

// Refer to traffic direction definition
#ifndef _UEMODEL_UEBASIC_H
#include "uemodel\netbasic.h"
#endif
using namespace UeModel;

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4996 )  // Deprecated function calling

//
namespace UeRoute
{
  // Different heuristic extent 
  const static double HEURISTIC20   = 20000. * 20000.;
  const static double HEURISTIC200	= 200000. * 200000.;
  const static double HEURISTIC500	= 500000. * 500000.;
  const static double HEURISTIC1000	= 1000000. * 1000000.;
  const static double HEURISTIC2000	= 2000000. * 2000000.;

  /**
  * \brief Different types of SNDs for special voice guidance
  */
  enum SpecialVoices
  {
    SV_ForGuidanceBegin = 0,
    SV_ForGuidanceProcess,
    SV_ForDestination,
    SV_ForWayPoint,
    SV_ForCalculation,
    SV_ForReRoute,
    SV_Max
  };

  enum UETTS_Role
  {
    /// ��ͨ��-Ů
    Role_Chinese_Female = 0,
    /// ��ͨ��-��
    Role_Chinese_Male,
    /// �Ĵ���
    Role_Chinese_Szechwan,
    /// �㶫��
    Role_Cantonese,
    /// ������
    Role_Chinese_Northeast,
    /// ̨�廰
    Role_Chinese_Taiwan,
  };

  /**
  * \brief Different prepare status for nav guider
  */
  enum GuiderPreparation
  {
    GP_FreeAll = 0,
    GP_FreePart,	// Here two scenes: one is to only release those belong to one plan method, another is to release changed positions belong to one plan method
    GP_Allocate,
    GP_ReadyForGuidance,
    GP_Max
  };

  /**
  * \brief ��ͬ��Decorator����
  */
  enum DecoratorType
  {
    DT_Unknown = 0,
    DT_Mrt,
    DT_Time,
    DT_Blocked,
    DT_Tmc,
    DT_Cyclic,
    DT_Max
  };

  /**
  * \brief Status of once route plan
  */
  enum PlanState
  {
    PS_None = 0,
    PS_Plan,
    PS_Ready,
    PS_DemoGuidance,
    PS_RealGuidance
  };

  /**
  * \brief Different kinds of subjects for different observers' usage
  */
  enum SubjectType
  {
    ST_RenderCalculation	= 0x0001,
    ST_RenderPathes				= 0x0002,
    ST_RenderGuidance			= 0x0004,
    ST_RenderLatest				= 0x0008,
    ST_RenderRouteList		= 0x0010,
    ST_RenderQueryList		= 0x0020,
    ST_RenderMapHook			= 0x0040,
    ST_RenderGpsHook			= 0x0080,
    ST_RenderFull					= 0x0100,
    ST_RenderCountDown    = 0x0200,
#if __FOR_FPC__
    ST_RenderGpsTrack     = 0x0400,
#endif
  };

  /**
  * \brief �滮��ʽ
  */
  enum MethodType
  {
    MT_Fast = 0,
    MT_Short = 1,
    MT_Economic = 2,
    MT_Optimal = 3,
    MT_Max = 4
  };

  /** 
  * \brief Ways of route plan
  */
  enum RouteWay
  {
    /// ����ٶ�
    RW_Fast = 0x01,
    /// ���·��
    RW_Short = 0x02,
    /// ���
    RW_Economic = 0x10,
    /// �Ƽ�·��
    RW_Optimal = 0x20,
    /// �滮��ʽ������
    RW_Max = 4
  };

  /** 
  * \brief Avoidances for once route plan
  */
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

  /** 
  * \brief Position type
  */
  enum PositionType
  {
    PT_Invalid = -1,
    /// ���
    PT_Start,
    /// �յ�
    PT_End,
    /// ���ɵ�
    PT_Middle,
    PT_General
  };

  /**
  * \brief Turn direction
  */
  enum TurnDirection
  {
    TD_Intersection = 0,
    TD_Left,
    TD_Right,
    TD_Uturn
  };

  /**
  *
  */
  enum TurnType
  {
    TT_UnKnown = -1,
    TT_Slip2Slip,
    TT_SlipInOut,
    TT_General
  };

  /**
  *
  **/
  enum VelocityType
  {
    VT_Normal = 0x01,
    VT_Violation = 0x02
  };

  /**
  * \brief Distance type
  */
  enum DistType
  {
    /// < 5km
    DT_Short = 0,   
    /// 5km ~ 15km
    DT_Middle,      
    /// > 15km
    DT_Long         
  };

  enum SpecialIntersectionPrompt
  {
    SIP_UnKnown = 0,

    SIP_EnterMain,
    SIP_ExitMain,

    SIP_EnterHighway,
    SIP_ExitHighway,

    SIP_LeftOverPass,
    SIP_MiddleOverPass,
    SIP_RightOverPass,

    SIP_LeftSideThree,
    SIP_MiddleSideThree,
    SIP_RightSideThree,

    SIP_LeftSideTwo,
    SIP_RightSideTwo,
    SIP_RightRoad,
    SIP_UTurn,
  };

  /**
  *
  **/
  struct GuidanceStatus
  {
    int m_curPair;
    int m_curIndicator;
    short m_curVtx;
    CGeoPoint<long> m_curPos;
    int m_curDistForSnd;
    short m_curOrderForSnd;
    unsigned int m_curSndCode;

    int m_nextDistForSnd;
    short m_nextOrderForSnd;
    unsigned int m_nextSndCode;

    /**
    *
    **/
    GuidanceStatus() : m_curPair(-1), m_curIndicator(-1), m_curVtx(-1), m_curDistForSnd(0), m_curOrderForSnd(0), m_curSndCode(0),
      m_nextOrderForSnd(0), m_nextSndCode(0), m_nextDistForSnd(0)
    {
    }
  };


  //
  const static short MAXPOSNUM = 10;

  /** 
  * \brief Position description for route plan
  */
  struct PlanPosition
  {
    //
    CGeoPoint<long> m_pos;
    PositionType m_type;
    double m_timeStamp;	// As one part of favorited points, needed to be ordered according to time

    //
    bool m_isPOI;
    bool m_isGPS;

    //
    long m_parcelIdx;
    long m_linkIdx;
    TrafficFlowDirection m_direction;

    // TODO:
    // Remove magic number
    int m_nameOffset;
    char m_name[128];

    //
    PlanPosition() : m_type(PT_Invalid), m_isPOI(false), m_isGPS(false), m_parcelIdx(-1), m_linkIdx(-1), 
      m_direction(TFD_Close), m_timeStamp(0)
    {
      ::memset(m_name, 0x00, 128);
    }

    //
    const PlanPosition &operator =(const PlanPosition &other)
    {
      if(this == &other)
      {
        return *this;
      }

      //
      m_pos = other.m_pos;
      m_type = other.m_type;

      //
      m_timeStamp = other.m_timeStamp;

      //
      m_isPOI = other.m_isPOI;
      m_isGPS = other.m_isGPS;

      //
      m_parcelIdx = other.m_parcelIdx;
      m_linkIdx = other.m_linkIdx;
      m_direction = other.m_direction;
      m_nameOffset = other.m_nameOffset;
      ::strcpy(m_name, other.m_name);

      //
      return *this;
    }

    /**
    *
    */
    bool IsValid()
    {
      return (m_type != PT_Invalid && m_pos.IsValid());
    }

    /**
    *
    */
    bool IsSame(const PlanPosition &other)
    {
      return (::abs(m_pos.m_x - other.m_pos.m_x) < 10 && ::abs(m_pos.m_y - other.m_pos.m_y) < 10);
    }
  };

  /** 
  * \brief Plan error code
  */
  enum PlanErrorCode
  {
    // Zero means success
    PEC_Success                     = 0,

    // Error categories
    PEC_SetError                    = 0x01000000,
    PEC_PlanError                   = 0x02000000,
    PEC_GuideError                  = 0x04000000,
    PEC_VoiceError                  = 0x08000000,
    PEC_OtherError                  = 0x10000000,

    // Setting errors
    PEC_InvalidPos                  = 0x01000001,
    PEC_NotExistedPos               = 0x01000002,
    PEC_NotSetStartPos              = 0x01000003,
    PEC_NoEndPos                    = 0x01000004,
    PEC_NoMidPos                    = 0x01000005,
    PEC_TooShortest                 = 0x01000006,
    PEC_TooFarest                   = 0x01000007,
    PEC_OverPosLimitation           = 0x01000008,
    PEC_CanntBlocked                = 0x01000009,
    PEC_SetBlocked                  = 0x01000010,

    // Planning errors
    PEC_NotSpecifyMethod            = 0x02000001,
    PEC_NotSpecifyVehicle           = 0x02000002,
    PEC_NotEnoughMemoryForPlan      = 0x02000003,
    PEC_NotPositionGPS              = 0x02000004,
    PEC_NotPositionStart            = 0x02000005,
    PEC_NotPositionEnd              = 0x02000006,
    PEC_IsAloneLink                 = 0x02000007,
    PEC_NotDirectlyMeet             = 0x02000008,
    PEC_NotRoughlyMeet              = 0x02000009,
    PEC_NotCurSELink                = 0x0200000A,
    PEC_SwitchLayer                 = 0x0200000B,
    PEC_NotSENext                   = 0x0200000C,
    PEC_NotCurESLink                = 0x0200000D,
    PEC_NotESNext                   = 0x0200000F,
    PEC_OverMaxLoopNum              = 0x02000010,
    PEC_DelayToUpLayer              = 0x02000011,
    PEC_WaitOtherDirection          = 0x02000012,
    PEC_ExistCyclic                 = 0x02000013,
    PEC_InvalidDecorator            = 0x02000014,
    PEC_NotHaveBlockDecorator       = 0x02000015,

    // Guidance erros
    PEC_NotEnoughMemoryForGuidance  = 0x04000001,
    PEC_NotFindIndicator            = 0x04000002,
    PEC_MeetLastIndicator           = 0x04000003,
    PEC_NotHaveSndPrompt            = 0x04000004,

    // Voice errors
    PEC_HaveNextSnd                 = 0x08000001,
    PEC_TooShortPlay                = 0x08000002,
    PEC_TooLongPlay                 = 0x08000003,
    PEC_NoValidSnd                  = 0x08000004,
    PEC_NoSndFile                   = 0x08000005,
    PEC_InvalidSndFile              = 0x08000006,
    PEC_NoMemForSnd                 = 0x08000007,
    PEC_NoThreadForSnd              = 0x08000008,
    PEC_RepeatedSnd                 = 0x08000009,
    PEC_NoTTS                       = 0x080000010,
    PEC_GuidanceStart               = 0x080000011,
    PEC_GuidanceOver                = 0x08000012,
    PEC_WayPointOver                = 0x08000013,
    PEC_IgnoreSnd                   = 0x08000014,
    PEC_InvalidString               = 0x08000015,
    PEC_NoFollowSnd                 = 0x08000016,


    // Thread or other errors
    PEC_NotActivateThread           = 0x10000001,
    PEC_ReRoutePlan                 = 0x10000002,
    PEC_NotHaveIndicator            = 0x10000003
  };

  /**
  * \brief �����Ϣ
  */
  struct BlockElement
  {
    // Note:
    // In future, maybe it also need direction defintion
    long m_parcelIdx;
    long m_linkIdx;

    /**
    * \brief ��ʼ��
    */
    BlockElement() : m_parcelIdx(0), m_linkIdx(0)
    {
    }

    /**
    * \brief ��ֵ������
    */
    const BlockElement &operator = (const BlockElement &other)
    {
      //
      if(this == &other)
      {
        return *this;
      }

      //
      m_parcelIdx = other.m_parcelIdx;
      m_linkIdx = other.m_linkIdx;

      return *this;
    }

    /**
    * \brief �߼���Ȳ�����
    */
    bool operator ==(const BlockElement &other)
    {
      return (m_parcelIdx == other.m_parcelIdx && m_linkIdx == other.m_linkIdx);
    }
  };

  /**
  *
  */
  enum MeetStandard
  {
    MS_Unknown = -1,
    MS_Meet,
    MS_SameLink,
    MS_NotSE,
    MS_NotES
  };

  /** 
  * \brief Setting for once route plan
  */
  struct PlanSetting
  {
    //
    double m_minDistance;
    double m_maxDistance;

    //
    int m_maxLoopNum;
    int m_maxTableSize;

    // TODO:
    // Not portable when changing the network definition
    short m_GLayerNum;
    short m_SLayerNum;
    short m_MLayerNum;

    // Note:
    // Consider the overflow issue
    unsigned long m_GLayerDist;
    unsigned long m_SLayerDist;
    unsigned long m_MLayerDist;

    // Whether record the whole calculation process
    bool m_isLogAll;

    //
    double m_toCoff;

    //
    bool m_isUseMrt;

    // Note:
    // When directly using real network to calculate against PC version, the maximum number of loop and table size should be enlarged
#if __FOR_DEVICE__
    PlanSetting() : m_minDistance(50), m_maxDistance(5000000), m_maxLoopNum(20000), m_maxTableSize(1024 * 16), m_GLayerNum(30), m_SLayerNum(20), m_MLayerNum(10),
      m_GLayerDist(20000), m_SLayerDist(80000), m_MLayerDist(200000), m_isLogAll(false), m_toCoff(1.), m_isUseMrt(false)
#else
    PlanSetting() : m_minDistance(50), m_maxDistance(6000000), m_maxLoopNum(35000), m_maxTableSize(1024 * 31), m_GLayerNum(30), m_SLayerNum(20), m_MLayerNum(10),
      m_GLayerDist(50000), m_SLayerDist(200000), m_MLayerDist(500000), m_isLogAll(false), m_toCoff(1.), m_isUseMrt(false)
#endif
    {
    }

    /**
    *
    */
    const PlanSetting &operator=(const PlanSetting &other)
    {
      if(this == &other)
      {
        return *this;
      }

      m_minDistance = other.m_minDistance;
      m_maxDistance = other.m_maxDistance;

      m_maxLoopNum = other.m_maxLoopNum;
      m_maxTableSize = other.m_maxTableSize;

      m_GLayerNum = other.m_GLayerNum;
      m_SLayerNum = other.m_SLayerNum;
      m_MLayerNum = other.m_MLayerNum;

      m_GLayerDist = other.m_GLayerDist;
      m_SLayerDist = other.m_SLayerDist;
      m_MLayerDist = other.m_MLayerDist;

      m_isLogAll = other.m_isLogAll;
      m_toCoff = other.m_toCoff;

      m_isUseMrt = other.m_isUseMrt;

      return *this;
    }
  };

#pragma pack(1)
  /**
  * \brief Side properties including SGP, Lane, electric eye etc, below is its definition of Index
  */
  struct eSideIndex
  {
    /// District or parcel idx
    int m_code;
    /// eEye numbers
    short m_count;
    /// Content offset
    unsigned int m_offset;

    /**
    * \brief ��ʼ��
    */
    eSideIndex() : m_code(0), m_count(0), m_offset(0)
    {
    };

    /**
    * \brief ��ֵ������
    */
    const eSideIndex &operator=(const eSideIndex &other)
    {
      if(this == &other)
      {
        return *this;
      }

      m_code = other.m_code;
      m_count = other.m_count;
      m_offset = other.m_offset;

      return *this;
    }
  };

  struct eSideEntry
  {
    const static int MAXSIDEPROPLENGTH = 128;

    /// Ҫ������
    unsigned char m_type;

    /// ���Ҫ��Ϊ���򿴰塢·�ڷŴ�ͼ����������·�ε�ID
    /// ���Ҫ��Ϊ��ͨ���桢������Ϣ������������·��ID
    int m_xCoord;

    /// ���Ҫ��Ϊ���򿴰塢·�ڷŴ�ͼ��������˳�·�ε�ID
    /// ���Ҫ��Ϊ������Ϣ�������ͨ������ȡֵ1��0���ֱ�������������
    /// ���Ҫ��Ϊ��ͨ���棬�����ͨ������ȡֵ1��4���ֱ����������˫�򡢲�ͨ��
    int m_yCoord;

    /// ��ǰ��¼��Ӧ�������ݵ�ƫ����
    /// ͨ����ǰ��¼�Ķ�Ӧoffset����һ��¼��offset���ɻ���������ݵĳ���
    unsigned int m_offset;

    /**
    * \brief ��ʼ��
    */
    eSideEntry() : m_xCoord(0), m_yCoord(0), m_type(0), m_offset(0)
    {
    };

    /**
    * \brief ��ֵ������
    */
    const eSideEntry &operator=(const eSideEntry &other)
    {
      if(this == &other)
      {
        return *this;
      }

      m_xCoord = other.m_xCoord;
      m_yCoord = other.m_yCoord;
      m_type = other.m_type;
      m_offset = other.m_offset;

      return *this;
    }
  };

  struct EEyeProp
  {
    /// ����������
    unsigned short m_type;

    /// ����������ֵ
    unsigned short m_speed;

    // ������λ��
    unsigned int m_x;
    unsigned int m_y;

    EEyeProp() : m_type(0), m_speed(0), m_x(0), m_y(0)
    {
    }

    bool operator ==(const EEyeProp &other)
    {
      if(this == &other)
      {
        return true;
      }

      return (m_x == other.m_x && m_y == other.m_y 
        && m_type == other.m_type && m_speed == other.m_speed);
    }

    bool operator !=(const EEyeProp &other)
    {
      return (m_x != other.m_x || m_y != other.m_y 
        || m_type != other.m_type || m_speed != other.m_speed);
    }

    void Invalid()
    {
      m_type = 0;
      m_speed = 0;
      m_x = 0;
      m_y = 0;
    }

    bool IsValid()
    {
      return m_type != 0 && m_x != 0 && m_y != 0;
    }

  };

  ///**
  //*
  //*/
  //struct eSideEntry
  //{
  //  // Note:
  //  const static int MAXSIDEPROPLENGTH = 128;

  //  // Coords or in-out link definition
  //  int m_xCoord;
  //  int m_yCoord;

  //  /// Prop content
  //  unsigned char m_content[MAXSIDEPROPLENGTH];

  //  /**
  //  * \brief ��ʼ��
  //  */
  //  eSideEntry() : m_xCoord(0), m_yCoord(0)
  //  {
  //    ::memset(m_content, 0x00, MAXSIDEPROPLENGTH);
  //  }

  //  /**
  //  * \brief ��ֵ������
  //  */
  //  const eSideEntry &operator=(const eSideEntry &other)
  //  {
  //    if(this == &other)
  //    {
  //      return *this;
  //    }

  //    m_xCoord = other.m_xCoord;
  //    m_yCoord = other.m_yCoord;
  //    ::memcpy(m_content, other.m_content, MAXSIDEPROPLENGTH);

  //    return *this;
  //  }
  //};

  /**
  * \brief �����е�Ԫ�ض���
  */
  struct PlannedLink
  {
    // Road network info
    unsigned short m_parcelIdx;
    unsigned short m_linkIdx;
    unsigned short m_nodeIdx;

    //
    short m_nextAngle;
    unsigned char m_direction;
    unsigned char m_turnType;

    //
    unsigned char m_layerType;
    unsigned char m_isPaid;
    char m_isClosed;         // Differenciate elements belonging to open and close tables
    unsigned char m_roadClass;
    unsigned char m_roadType;
    unsigned char m_roadForm;
    unsigned char m_routeLevel;
    unsigned char m_isCrossAdmin;
    unsigned char m_isRGLightFlag;
    int m_nameOffset;

    // Costs
    float m_passCost;
    float m_toCost;
    float m_totalCost;

    // List description
    short m_prevOrder;
    short m_nextOrder;
    short m_depth;
    float m_length;
    float m_totalLength;

    /// Inidcate the type of positions for planning, start, end or middle
    unsigned char m_orderType;

    /**
    * \brief ��ʼ��
    */
    PlannedLink() : m_parcelIdx(-1), m_linkIdx(-1), m_nodeIdx(-1), m_nextAngle(0), m_direction(-1), m_turnType(0), m_length(0), m_totalLength(0),
      m_layerType(0), m_roadClass(-1), m_roadType(-1), m_roadForm(0), m_routeLevel(-1), m_isCrossAdmin(0), m_isRGLightFlag(0), m_nameOffset(0), m_passCost(0), m_toCost(0), m_totalCost(0),
      m_isClosed(0), m_prevOrder(-1), m_nextOrder(-1), m_depth(-1), m_orderType(PT_General), m_isPaid(0)
    {
    }

    bool operator ==(const PlannedLink &other)
    {
      if(this == &other)
      {
        return true;
      }

      return (m_layerType == other.m_layerType && 
        m_parcelIdx == other.m_parcelIdx &&
        m_linkIdx == other.m_linkIdx && 
        m_direction == other.m_direction);
    }

    bool IsSameWith(const PlannedLink &other)
    {
      if(this == &other)
      {
        return true;
      }

      return (m_layerType == other.m_layerType) && (m_parcelIdx == other.m_parcelIdx) && (m_linkIdx == other.m_linkIdx);
    }

    /**
    *
    */
    bool IsValid()
    {
      return (m_parcelIdx >= 0 && m_linkIdx >= 0 && m_nodeIdx >= 0 && m_orderType != PT_Invalid);
    }

    /**
    *
    */
    void Empty()
    {
      m_parcelIdx = -1;
      m_linkIdx = -1;
      m_nodeIdx = -1;
      m_orderType = PT_Invalid;
    }

    /**
    *
    */
    const PlannedLink &operator = (const PlannedLink &other)
    {
      //
      if(this == &other)
      {
        return *this;
      }

      //
      m_parcelIdx = other.m_parcelIdx;
      m_linkIdx = other.m_linkIdx;
      m_nodeIdx = other.m_nodeIdx;

      //
      m_nextAngle = other.m_nextAngle;
      m_direction = other.m_direction;
      m_turnType = other.m_turnType;

      //
      m_layerType = other.m_layerType;
      m_roadClass = other.m_roadClass;
      m_roadType = other.m_roadType;
      m_roadForm = other.m_roadForm;
      m_routeLevel = other.m_routeLevel;
      m_isCrossAdmin = other.m_isCrossAdmin;
      m_isRGLightFlag = other.m_isRGLightFlag;
      m_isPaid = other.m_isPaid;
      m_nameOffset = other.m_nameOffset;

      // Costs
      m_passCost = other.m_passCost;
      m_toCost = other.m_toCost;
      m_totalCost = other.m_totalCost;

      //
      m_isClosed = other.m_isClosed;

      //
      m_prevOrder = other.m_prevOrder;
      m_nextOrder = other.m_nextOrder;
      m_depth = other.m_depth;
      m_totalLength = other.m_totalLength;
      m_length = other.m_length;

      //
      m_orderType = other.m_orderType;

      //
      return *this;
    }
  };
#pragma pack()

  /**
  * \brief �ձ��е�Ԫ�ض���
  */
  struct ElementIndex
  {
    //
    long m_hashCode;
    unsigned char m_layer;
    unsigned short m_order;
    double m_cost;

    //
    ElementIndex() : m_layer(0), m_order(0), m_cost(0.), m_hashCode(0)
    {
    }
  };

  /**
  * \brief �����������������
  * Note:
  * The maximum of InfoVoiceType & eSideVoiceType should be little than 256
  */
  enum DirVoiceType
  {
    DVT_Unknown,
    /// ֱ��
    DVT_DirectGo,		
    /// ����
    DVT_MiddleGo,		
    /// ����ֱ��
    DVT_RightDirect,
    /// ����ֱ��
    DVT_LeftDirect,
    /// ����
    DVT_Right,			
    /// ����
    DVT_Left,
    /// ��·������
    DVT_ForkRight,
    /// ��·������
    DVT_ForkLeft,
    /// ��ͷ
    DVT_UTurn,			
    /// ��ת
    DVT_RTurn,			
    /// ��ת
    DVT_LTurn,			
    DVT_Maximum
  };

  /**
  * \brief ����������Ϣ������
  */
  enum InfoVoiceType
  {
    IVT_Unknown	 = DVT_Maximum,
    /// ǰ��
    IVT_Forward,								
    /// ����������ʼ
    IVT_StartGuidance,						
    /// ���¿�ʼ����
    IVT_ReRoute,							
    /// ��ʼ·������
    IVT_Route,								
    /// ���ﾭ�ɵ�
    IVT_MeetMiddle,						
    /// ����Ŀ�ĵ�
    IVT_MeetDestination,					
    /// �������
    IVT_EnterTunnel,				
    /// �ӽ��ֶ�
    IVT_EnterFerry,		
    /// ��������·
    IVT_EnterSlowLane,					
    /// �������·
    IVT_EnterFastLane,					
    /// �������
    IVT_EnterHW,							
    /// �뿪����
    IVT_ExitHW,								
    /// �з�����
    IVT_EnterSA,								
    /// ���շ�վ
    IVT_EnterToll,							
    /// ����
    IVT_EnterBridge,						
    /// �ϸ߼�
    IVT_EnterOverPass,					
    /// �ѵ�
    IVT_EnterSlipRoad,							
    /// �ѵ�	
    IVT_EnterIC,											
    /// �ѵ�
    IVT_EnterJC,								
    /// ���뻷��
    IVT_EnterRoundAbout,				
    /// �뿪����
    IVT_ExitRoundAbout,					
    /// ��תת�õ�
    IVT_EnterLeftCross,					
    /// ��תת�õ�
    IVT_EnterRightCross,
    /// ���������
    IVT_RemindSlowDown,
    /// ��ע��任����
    IVT_RemindShiftLane,
    /// GPS�źŶ�λ
    IVT_GetGps,								
    /// ʧȥGPS�ź�
    IVT_LostGps,								
    IVT_2KM,
    IVT_1KM,
    IVT_600M,
    IVT_500M,
    IVT_400M,
    IVT_300M,
    IVT_200M,
    IVT_100M,
    IVT_50M,
    IVT_Zero,
    IVT_One,
    IVT_Two,
    IVT_Three,
    IVT_Four,
    IVT_Five,
    IVT_Six,
    IVT_Seven,
    IVT_Eight,
    IVT_Nine,
    /// Ȼ��
    IVT_Next,							
    /// ������
    IVT_WaitNext	,					
    /// TTS
    IVT_TTS,		
    /// ������·
    IVT_EnterMain,
    /// ���븨·
    IVT_EnterAux,
    /// ��������
    IVT_CrossAdmin,
    IVT_SideInfo,
    IVT_Maximum
  };

  /**
  * \brief Kinds of electric eyes
  */
  enum eSideKind
  {
    SVT_Unknown = 0,
    /// ���򿴰�
    SVT_SignPost = 1 << 1,
    /// ������Ϣ
    SVT_LaneInfo = 1 << 2,
    /// ��ͨ��ʩ
    SVT_TrafficSign = 1 << 3,
    /// ����·�ڷŴ�ͼ
    SVT_VirtualCross = 1 << 4,
    /// ��ʵ·�ڷŴ�ͼ
    SVT_RealCross = 1 << 5,
    /// ��沥����
    SVT_Advance = 1 << 6,
    /// ������
    SVT_EEye = 1 << 7,
  };

  /**
  * \brief ��ͨ��ʾ������������
  *
  * \detail ö��ֵ�����ڽ�����ʽ�е�����ֵ��
  * ���������ʽ������ֵ���巢���仯����Ӧ��ö�ٶ���Ҳ��Ҫ�޸ġ�
  */
  enum TrafficVoiceType
  {
    TVT_Begin = 100,
    /// ��ת��
    TVT_SharpTurn = 102,
    /// ����ת��
    TVT_ReverseTurn = 103,
    /// ������·
    TVT_WindingRoad = 104,
    /// ����
    TVT_SteepRamp  = 105,
    /// TODO:�׻�·�� 115
    /// ��·����
    TVT_RailwayCross = 124,
    /// �¹��׷�·��
    TVT_AccidentRoad = 126,
    /// ע��Σ��
    TVT_RiskRoad = 130,
    /// ע���·����
    TVT_RoadConflux = 137,

    /// ���������
    TVT_TrafficLights = 201,
    /// ��������
    TVT_SpeedLimit = 202,
    /// �������
    TVT_NormalCamera = 203,
    /// ���������
    TVT_InTunnel = 204,
    /// ������������
    TVT_TunnelPort = 205,
  };

  /**
  * 
  */
  struct SndPrompt
  {
    // Distance(s) for playing
    unsigned char m_dirCode;
    unsigned char m_infoCode;
    unsigned char m_sideCode;		// Indicate which kind of side properties like SGP, lane or electric eyes

    /**
    *
    */
    SndPrompt() : m_dirCode(0), m_infoCode(0), m_sideCode(0/*-1*/)
    {
    }

    /**
    *
    */
    bool IsValid()
    {
      return (m_dirCode > 0 || m_infoCode > 0 || m_sideCode > 0);
    }

    /**
    *
    */
    const SndPrompt &operator =(const SndPrompt &other)
    {
      //
      if(this == &other)
      {
        return *this;
      }

      //
      m_dirCode = other.m_dirCode;
      m_infoCode = other.m_infoCode;
      m_sideCode = other.m_sideCode;

      //
      return *this;
    }
  };

  struct PlanResultDesc
  {
    // (m)
    double totalLength;

    // 
    double highwayLen;

    //
    double normalLen;

    // (min)
    double costTime;

    PlanResultDesc() : totalLength(0.), highwayLen(0.), normalLen(0.), costTime(0.)
    {
    }
  };

#pragma pack(1)
  /**
  *
  */
  struct GuidanceIndicator
  {
    //
    unsigned short m_parcelIdx;
    unsigned short m_linkIdx;

    // Simple TOPO description
    unsigned char m_clinks;
    unsigned char m_turnOrder;

    //
    unsigned char m_direction;
    unsigned char m_roadClass;
    unsigned char m_roadType;
    unsigned char m_roadForm;
    unsigned char m_isPaid;

    //
    CGeoRect<long> m_mbr;

    //
    float m_curDist;
    float m_leftDist;
    int m_nameOffset;

    //
    SndPrompt m_snd;

#ifdef _DEBUG
    unsigned char m_isGotFromES;
#endif

    //
    unsigned short m_vtxNum;
    CGeoPoint<long> *m_vtxs;

    /**
    *
    */
    GuidanceIndicator() : m_parcelIdx(-1), m_linkIdx(-1), m_direction(-1), m_clinks(0), m_turnOrder(-1), 
      m_roadClass(0), m_roadForm(-1),m_roadType(-1),
      m_curDist(0), m_leftDist(0), m_vtxNum(0), m_nameOffset(0), m_vtxs(0), m_isPaid(0)
    {
#ifdef _DEBUG
      m_isGotFromES = 0;
#endif
    }

    /**
    *
    **/
    ~GuidanceIndicator()
    {
      //
      if(m_vtxs)
      {
        ::free(m_vtxs);
        m_vtxs = 0;
      }
    }
  };
#pragma pack()

  /**
  *
  */
  struct IndicatorIndex
  {
    //
    long m_parcelIdx;
    long m_linkIdx;
    long m_order;

    //
    IndicatorIndex() : m_parcelIdx(-1), m_linkIdx(-1)
    {
    }
  };


  /**
  * Kinds of side properties
  */
  enum SideKind
  {
    SK_SGP, // Sign post
    SK_ElectricEye,
  };

#pragma pack (2)
  /**
  *
  */
  struct UeSound
  {
    // Settings
    static const int CodeMaximum = 15;
    static const int StrMaximum = 128;

    // Fields
    int m_count;
    unsigned int m_codeTbl[CodeMaximum];
    char m_strTbl[CodeMaximum][StrMaximum];
    unsigned char m_priority;

    //
    UeSound()
    {
      ::memset(this, 0, sizeof(UeSound));
    }

    //
    bool Add(int code)
    {
      if(m_count < (CodeMaximum - 1))
      {
        m_codeTbl[m_count++] = code;
        return true;
      }

      return false;
    }

    //
    bool Add(const char *str, int code)
    {
      if(m_count >= (CodeMaximum -1))
      {
        return false;
      }

      m_codeTbl[m_count] = code;
      m_strTbl[m_count][0] = '\0';
      ::strncat(m_strTbl[m_count], str, 128);
      m_count++;

      return true;
    }

    //
    bool Add(const char *str, int len, int code)
    {
      if(m_count >= (CodeMaximum -1) || len >= (StrMaximum - 1))
      {
        return false;
      }

      m_codeTbl[m_count] = code;
      m_strTbl[m_count][0] = '\0';
      ::strncat(m_strTbl[m_count], str, len);
      m_count++;

      return true;
    }

    //
    int Prev()
    {
      return (m_count > 0) ? m_codeTbl[m_count - 1] : -1;
    }

    //
    int Prev(int cur)
    {
      return (cur > 0 && cur < m_count) ? m_codeTbl[cur - 1] : -1;
    }
  };

  /**
  *
  */
  struct SndIndex
  {
    //
    unsigned long m_code;
    unsigned short m_level;
    unsigned long m_offset;
    unsigned long m_size;
    unsigned short m_reserved;

    //
    SndIndex() : m_code(0), m_level(0), m_offset(0), m_size(0), m_reserved(0)
    {
    }
  };
#pragma pack ()
}
#endif