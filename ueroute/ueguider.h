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
#ifndef _UEROUTE_GUIDER_H
#define _UEROUTE_GUIDER_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to STL definitions
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to route basic definition
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to own-specific array
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to memory basic definitions
#ifndef _UEBASE_MEMBASIC_H
#include "uebase\membasic.h"
#endif

//
#ifndef _UEBASE_UESETTINGS_H
#include "uebase\uesettings.h"
#endif
using namespace UeBase;

// Refer to gps basic definition
#ifndef _UEGPS_GPSBASIC_H
#include "uegps\gpsbasic.h"
#endif
using namespace UeGps;

// Refer to road network definitions
#ifndef _UEMODEL_ROADNETWORK_H
#include "uemodel\network.h"
#endif

// Refer to road network definitions
#ifndef _UEMODEL_NETPARCEL_H
#include "uemodel\netparcel.h"
#endif

// Refer to road network definitions
#ifndef _UEMODEL_ROADLINK_H
#include "uemodel\netlink.h"
#endif
using namespace UeModel;

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4251 )  // Deprecated function calling

//
namespace UeRoute
{
  // Forward classes
  class CUeVoice;
  class IRoute;

  /**
  * \brief �滮���������ָ������
  */
  class UEROUTE_CLASS CUeGuider : public CMemoryConsumer
  {
    // Relatives
    friend class CUeVoice;
    friend class CAStarRoute;
    friend class CUeSimulator;
    friend class IRoute;

    /// Indices
    typedef std::vector<IndicatorIndex> IndicatorVector;

    // Different turn angles
    static const int DIRECTANGLE = 20;
    static const int TURNANGLE = 45;
    static const int UTURNANGLE = 160;

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeGuider(IRoute *route);

    /**
    * \brief ��������
    */
    ~CUeGuider();

  public:
    //
    //
    //
    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues();

    //
    //
    //
    /**
    * \brief ���ݲ�ͬ��״̬������Դ������ͷŵȳ�ʼ����
    *
    * \param status �ο�GuiderPreparation����
    */
    unsigned int Prepare(short status, int order = 0);

    /**
    * \brief ��������������Ϣ
    */
    unsigned int MakePrompts(PlannedLink *curES, PlannedLink *curSE, PlannedLink *esLinks, PlannedLink *seLinks, const NetPosition &startPos, const NetPosition &endPos, int pair);

    /**
    * \brief Ԥ��������Ϣ��ƫ���ع滮��
    */
    unsigned int ReservePrompts(int pair, GuidanceIndicator **indicators);

    /**
    * \brief �ϲ�������Ϣ��ƫ���ع滮��
    */
    unsigned int MergePrompts(GuidanceIndicator **indicators, int indicatorNum, int startOrder);

    /**
    * \brief ��һ������ָ��
    */
    unsigned int FirstIndicator();

    /**
    * \brief ��һ������ָ��
    */
    unsigned int NextIndicator(const MatchResult &curPos);

    /**
    * \brief ����������Ϣ
    */
    unsigned int PlayPrompt(const MatchResult &curPos);

    /**
    * \brief ������������ʾ�������ڷ�����״̬��ʹ�á�
    */
    void PlayElecEye(const MatchResult &curPos);

    /**
    * \brief ����ָ��������
    */
    unsigned int PlayVoice(UeSound &snd);

    /**
    * \brife ����ָ����ָ��
    *
    * \param type ָ������
    * \param speed ��ǰ�г��ٶ�
    * \param distForSnd ����ִ��ָ��λ�õľ���
    */
    unsigned int PlayVoice(short type, double speed, double distForSnd);

    /**
    * \brief �жϹ滮������Ƿ����ָ����·��
    *
    * \param parcelIdx ����ID
    * \param linkIdx ·��ID
    */
    long IsExist(long parcelIdx, long linkIdx);

    /**
    * \brief ����������������
    *
    * \param settings ������Ϣ
    */
    void SetVoiceSettings(const UeBase::VoiceSettings &settings);

    /**
    * \brief ����TTS�������ɫ
    */
    unsigned int SetRole(UETTS_Role role);

    /**
    * \brief ȡ��·�ι�����Ϣ
    *
    * \param type ������Ϣ����
    * \param code ·�����������
    * \param xCoord ��ǰ·��ID(��X����)
    * \param yCoord ����·��ID(��Y����)
    * \param prop ���صĹ�����Ϣ
    */
    unsigned char GetSideProp(unsigned char type, int code, int xCoord, int yCoord, char *prop);

    /**
    * \brief Get current prop
    */
    const char *GetSideProp(unsigned char type);

    /**
    * \brief ���ٳ�����Ϣ
    */
    bool GetHighwayOutlets(CMemVector &outlets);

    /**
    * \brief �����ظ�����
    * \param infoCode  ��Ϣ��
    * \param dirCode ת��
    * \param distForSnd ����ת��ľ���
    */
    void ReplayVoice(unsigned char infoCode, unsigned char dirCode, int distForSnd);

  protected:
    //
    //
    //
    /**
    *
    */
    void GetChildren(PlannedLink *curLink, CMemVector& links, CMemVector &children);

    /**
    *
    */
    void GetHigherChildren(PlannedLink *curLink, CMemVector& links, CMemVector &children);

    /**
    *
    */
    void GenerateIndicator(CMemVector& curLinks, CMemVector& nextLinks, bool isCurReady = true);

    /**
    *
    */
    unsigned int PushIndicator(PlannedLink &curLink, PlannedLink &nextLink);

    /**
    *
    */
    unsigned int CreateIndicator(const PlannedLink &curLink, const CMemVector &vtxs, short cLinks, short turnOrder, short dirCode, short infoCode);

    /**
    *
    */
    double GetDistance(const CMemVector &vtxs, CGeoRect<long> &mbr);

    /**
    *
    */
    void GetSndCode(PlannedLink &curLink, PlannedLink &nextLink, short gapAngle, short &dirCode, short &infoCode);

    /**
    *
    */
    void GetTopoDesc(INetParcel *oneParcel, INetLink *curRoad, PlannedLink &curLink, PlannedLink &nextLink, short &turnAngle, short &cLinks, short &turnOrder, short &infoCode);

    /**
    *
    */
    void ForSpecials();

    /**
    *
    **/
    bool IsConnected(GuidanceIndicator *prevIndicator, GuidanceIndicator *nextIndicator);

    /**
    *
    **/
    bool IsException(GuidanceIndicator *prevIndicator, GuidanceIndicator *curIndicator);

    /**
    *
    **/
    short RegetDirCode(GuidanceIndicator *prevIndicator, GuidanceIndicator *nextIndicator);

    /**
    *
    */
    short GetDirCode(short gapAngle);

    /**
    *
    */
    bool IsNotPassed(INetParcel *oneParcel, INetLink *oneLink, PlannedLink &curLink, long nodeIdx, long linkIdx, short &noPass, short &infoCode);

    /**
    *
    */
    void GetTopoDetail(INetParcel *oneParcel, INetLink *oneLink, PlannedLink &curLink, long nodeIdx, long linkIdx, short cLinks, short outAngle, short &turnAngle, short &turnOrder, short &noPass, bool &isExist);

    /**
    *
    **/
    void EraseCyclicLink();

    /**
    *
    **/
    void EraseShortLink();

    /**
    * \brief ��õ�ǰ�滮���������·����
    */
    int GetIndicatorNum(int curPair);

    /**
    * \brief ��õ�ǰ�滮�����ָ��������·��
    */
    GuidanceIndicator *GetIndicator(int curPair, int idx);

    /**
    * \brief ���ָ���滮��ʽ�Ĺ滮���������·���������ڶ�·���Ĺ滮�����ȡ��
    */
    int GetIndicatorNum(unsigned char curPlan, int curPair);

    /**
    * \brief ���ָ���滮��ʽ�Ĺ滮�����ָ��������·�Σ����ڶ�·���Ĺ滮�����ȡ��
    */
    GuidanceIndicator *GetIndicator(unsigned char curPlan, int curPair, int idx);

    /**
    * \brief ��ȡ��ǰ������״̬
    */
    unsigned int GetCurrent(GuidanceStatus &dirInfo);

    /**
    * \brief ȡ�õ�ǰ�貥���ĵ�������Ϣ
    */
    bool GetCurElecEye(EEyeProp &elecEye);

    /**
    * \brief ȡ�þ��뵱ǰ�貥���ĵ�����
    */
    double GetCurElecEyeDist();

    /**
    *
    **/
    unsigned char GetEyeCode(const GuidanceIndicator *const curIndicator);

  protected:
    // SND player
    CUeVoice *m_voicer;
    IRoute *m_parent;

    // Definition of prompts and its index
    // Note:
    // Below magic number follow the definition of enum type: RouteWay
    unsigned char m_curPlan;
    double m_plannedDist;
    GuidanceIndicator **m_indicators[MT_Max][MAXPOSNUM-1];
    int m_indicatorNum[MT_Max][MAXPOSNUM-1];
    int m_increment;
    int m_capacity;
    MatchResult m_carInfo;

    // Indice
    IndicatorVector m_indice;

    // The total distance for passing
    double m_leftDist;

    // Iterators
    int m_curPair;
    int m_curIndicator;
    int m_curVtx;
    CGeoPoint<long> m_curPos;

    // Remember current start and end position just planned
    NetPosition m_startPos;
    NetPosition m_endPos;

    // Remember one middle position as start position
    PlannedLink m_firstLink;

    // TODO:
    // After getting NavFacade, decouple this relationship under the help of 
    // that package as a mediator
    IRoadNetwork *m_network;

    // Flags for re-route plan
    unsigned char m_offDelays;
    long m_offDistance;
    CGeoPoint<double> m_offCoord;

    // If it is still in the same link, it no need to re-route again
    long m_offParcelIdx;
    long m_offLinkIdx;
    short m_offDirection;
    short m_offTry;

    // For log usage when recording the road name
    long m_prevOffset;

    // Fix memory fragamentation caused by current lower CE version
    CMemBasic m_memBasic;

    // To calculate complex cross
    int m_prevAngle;
  };
}

#endif