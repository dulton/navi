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
#ifndef _UEROUTE_ROUTE_H
#define _UEROUTE_ROUTE_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to route basic
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif

// Refer to own-specific array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

// Refer to memory garbage
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to mediator
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif

// Refer to running loger
#ifndef _UEBASE_DBGTRACER_H
#include "uebase\dbglogger.h"
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

// Refer to map match interface definition
#ifndef _UEGPS_MAPMATCH_H
#include "uegps\mapmatch.h"
#endif
using namespace UeGps;

// Log macro
#if __LOG_RUNNING__
#define VARIANTLOGGER 1
#endif

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling

//
namespace UeRoute
{
  // Forward classes
  class CUeRouteImpl;
  class CUeGuider;
  class CRouteHook;
  class CUeSimulator;
  class CFavoredNetwork;

  /**
  * \brief ·���滮�ӿ�
  */
  class UEROUTE_CLASS IRoute : public CObservable
  {
    // Relatives
    friend class CUeEvaluator;
    friend class CUeGuider;
    friend class CUeVoice;
    friend class CAStarRoute;

    //
    typedef std::vector<CObserver*> ObserverVector;

    //
    //
    //
    /**
    * \brief ��ʼ��
    *
    * \param oneImpl ·���滮�ӿڵľ���ʵ����Ķ����ָ��
    */
    IRoute(CUeRouteImpl *oneImpl);

    /**
    * \brief ��Դ�ͷ�
    */
    ~IRoute();

  public:
    /**
    * 
    */
    enum LogPlayState
    {
      LPS_Pause = 0,
      LPS_Play,
      LPS_Stop,
      LPS_Front,
      LPS_Back,

      LPS_ES,
      LPS_LayerType,
      LPS_LogType,
    };

    //
    //
    //
    /**
    * \brief ȡ��·���滮�ӿ�
    *
    * \param oneImpl ·���滮�ӿڵľ���ʵ����Ķ����ָ��
    */
    static IRoute *GetRoute(CUeRouteImpl *oneImpl);

    /**
    * \brief ����UeRouteģ�飬ȡ��·���滮�ӿ�
    */
    static IRoute *GetRoute();

    /**
    * \brief ��Դ�ͷ�
    */
    void Delete();

    //
    //
    //
    /**
    * \brief �滮ǰ�ĳ�ʼ��
    */
    unsigned int Prepare();

    /**
    * \brief ���ù滮��ʽ
    */
    unsigned int SetMethod(unsigned int method);

    /**
    * \brief ��ȡ��ǰ�Ĺ滮��ʽ
    */
    unsigned int GetMethod();

    /**
    * \brief �ж�ָ���Ĺ����Ϣ�Ƿ���Ч
    *
    * \param oneKind �μ�RouteAvoidance����
    * \return ������ڸ����͵Ĺ���򷵻�true�����򷵻�false
    */
    bool IsAvoid(unsigned int oneKind);

    /**
    * \brief �ж��Ƿ�����Ա㿪ʼ·���滮
    */
    unsigned int IsReadyForPlanning();

    /**
    * \brief TODO:δʹ�õĽӿ�
    */
    unsigned int AdoptMethod(short method);

    /**
    * \brief ����·���滮
    *
    * \return �滮�ɹ�����PEC_Success�����򷵻ش�����룬�μ�PlanErrorCode����
    */
    unsigned int RoutePlan();

    /**
    * \brief ����·���滮
    *
    * \param isPlayVoice �滮��Ϻ��Ƿ񲥱�������ʼ��ʾ����
    * TODO:�˲���Ŀǰ�Ѿ�ʧЧ�����ǵ�����ģ�����е��ã���ʱ������������Ҫȥ����
    *
    * \return �滮�ɹ�����PEC_Success�����򷵻ش�����룬�μ�PlanErrorCode����
    */
    unsigned int RoutePlan(bool isPlayVoice);

    /**
    * \brief ��·���滮
    */
    unsigned int MultiRoutePlan();

    /**
    * \brief ȡ�ù滮���������Ϣ
    */
    bool GetPlanResultDesc(PlanResultDesc &desc);

    /**
    * \brief ȡ��ָ���滮��ʽ�Ĺ滮���������Ϣ�����ڶ�·���滮��
    * 
    * \param[in] curPlan �滮��ʽ���μ�MethodType��
    * \param[out] desc ���صĹ滮���������
    */
    bool GetPlanResultDesc(unsigned char curPlan, PlanResultDesc &desc);

    /**
    * \brief ��ʼ����
    */
    unsigned int StartGuidance();

    /**
    * \brief ֹͣ����
    */
    unsigned int StopGuidance();

    /**
    * \brief ��ù滮�Ľ�����Ϣ
    */
    double GetProgressInfo();

    //
    // ����PC�˹滮���鹤�ߵĽӿ�
    //
    /**
    * 
    */
    void SetPlanLogFile(void *logFile);

    /**
    * 
    */
    void SetLogPlayState(short state);

    /**
    * 
    */
    short GetLogPlayState()
    {
      return m_logPlayState;
    }

    //
    // Note:
    // When implementing below functions, should consider the start or end link which shouldn't be blocked
    //
    /**
    * \brief ���ָ��λ�õ�·��
    *
    * \param onePos ָ���ĵ�ͼλ��
    * \param isRemoved ���Ϊtrue�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int SetBlock(CGeoPoint<long> &onePos, bool isRemoved = false);

    /**
    * \brief ���ָ����Χ��·��
    *
    * \param oneExtent ָ���ĵ�ͼ���귶Χ
    * \param isRemoved ���Ϊfalse�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int SetBlock(CGeoRect<long> &oneExtent, bool isRemoved = false);

    /**
    * \brief ���ָ����·��
    *
    * \param ids Ҫ��ܵ�BlockElement����
    * \param isRemoved ���Ϊfalse�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int SetBlock(CMemVector &ids, bool isRemoved = false);

    /**
    * \brief ɾ�����й��·��
    *
    * \param isRemoved ���Ϊtrue��ɾ�����е����й��·�Σ�����ֱ�ӷ���
    * \return ����PEC_Success
    */
    unsigned int SetBlock(bool isRemoved = false);

    //
    //
    //
    /**
    * \brief ����ʱ���
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int SyncPositionTime(bool isSame = true);

    /**
    * \brief ����ָ��λ��Ϊ��㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int SetPosition(PlanPosition &pos);

    /**
    * \brief ���ĳ����㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int GetPosition(PlanPosition &pos) const;

    /**
    * \brief ���ָ����Χ�ڵ���㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int GetPosition(PlanPosition &pos, CGeoRect<long> &mbr) const;

    /**
    * \brief ���ĳ����㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \param idx ����
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int GetPosition(PlanPosition &pos, unsigned short idx) const;

    /**
    * \brief ɾ��ָ����Χ�ڵ���㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \param mbr ���η�Χ
    * \param isReserved ���Ϊtrue��������λ�ã�ֻ����Ϊ��Ч������ֱ��ɾ��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int RemovePosition(short type, CGeoRect<long> &mbr, bool isReserved = false);

    /**
    * \brief ɾ��ĳ����㡢�յ���ɵ�
    *
    * \param pos λ����Ϣ
    * \param idx ����
    * \param isReserved ���Ϊtrue��������λ�ã�ֻ����ΪPT_Invalid������ֱ��ɾ��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int RemovePosition(short type, unsigned short idx, bool isReserved = false);

    /**
    * \brief ɾ��������㡢�յ���ɵ�
    *
    * \param isReserved ���Ϊtrue��������λ�ã�ֻ����ΪPT_Invalid������ֱ��ɾ��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int RemovePosition(bool isReserved = false);

    /**
    * \brief ���������㡢�յ���ɵ����Ŀ
    *
    * \return ��㡢�յ���ɵ������
    */
    unsigned int GetPosCount();

    //
    // The process of simulation
    //
    /**
    * \brief ��ʼģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int StartDemo(short speed);

    /**
    * \brief ��ͣģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int PauseDemo();

    /**
    * \brief �����жϵ�ģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int ResumeDemo(short speed);

    /**
    * \brief ֹͣģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int StopDemo();

    /**
    * \brief ��ȡ��һ��ģ���λ��
    *
    * \param result ��һģ���λ��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int DemoPos(MatchResult &result);

    /**
    * \brief ȡ��ģ���ٶ�
    */
    short GetDemoSpeed();

    //
    //
    //
    /**
    * \brief ����������Ϣ
    */
    unsigned int PlayIndicator(const MatchResult &curPos);

    /**
    * \brief ������������ʾ�������ڷ�����״̬��ʹ�á�
    */
    void PlayElecEye(const MatchResult &curPos);

    /**
    * \brief ȡ�ù滮����ķֶ��������ݾ��ɵ㻮�֣�
    */
    int GetPairs()
    {
      return m_positions.GetCount() - 1;
    }

    /**
    * \brief ȡ��ĳ���ֶ��ڵ�����·������
    */
    int GetIndicatorNum(int curPair);

    /**
    * \brief ��ù滮�����ָ��������·��
    */
    GuidanceIndicator *GetIndicator(int curPair, int idx);

    /**
    * \brief ���ָ���滮��ʽ�Ĺ滮���������·���������ڶ�·���Ĺ滮�����ȡ��
    *
    * \param curPlan ָ���Ĺ滮��ʽ���μ�MethodType
    * \param curPair ָ���ķֶ�
    */
    int GetIndicatorNum(unsigned char curPlan, int curPair);

    /**
    * \brief ���ָ���滮��ʽ�Ĺ滮�����ָ��������·�Σ����ڶ�·���Ĺ滮�����ȡ��
    *
    * \param curPlan ָ���Ĺ滮��ʽ���μ�MethodType
    * \param curPair ָ���ķֶ�
    */
    GuidanceIndicator *GetIndicator(unsigned char curPlan, int curPair, int idx);

    /**
    * \brief ȡ�õ�ǰ������״̬
    */
    unsigned int GetCurrent(GuidanceStatus &dirInfo);

    /**
    * \brief ��ȡ��ǰ�����⽻�����ʾ
    */
    unsigned int GetSpecialIntersection();

    /**
    * \brief ȡ�õ�ǰ�貥���ĵ�������Ϣ
    */
    bool GetCurElecEye(EEyeProp &elecEye);

    /**
    * \brief ȡ�þ��뵱ǰ�貥���ĵ�����
    */
    double GetCurElecEyeDist();

    /**
    * \brief ������յ�ľ��η�Χ
    */
    void GetExtent(CGeoRect<long> &curExtent);

    /**
    * \brief �жϹ滮������Ƿ����ָ����·��
    *
    * \param parcelIdx parcel��Ψһ��ʶ��
    * \param linkIdx ָ��parcel��link��Ψһ��ʶ��
    */
    bool IsPassing(long parcelIdx, long linkIdx);

    /**
    * \brief �жϵ�ǰ�Ƿ��ڹ滮״̬
    * Deprecated function: If we don't adopt thread for route plan, it seems no obvious sense
    */
    bool IsPlanning()
    {
      return m_planState == PS_Plan;
    }

    /**
    * \brief ��õ�ǰ�滮״̬
    */
    short GetPlanState()
    {
      return m_planState;
    }

    /**
    * \brief ���ù滮״̬
    */
    void SetPlanState(short state)
    {
      m_planState = (PlanState)state;
    }

    /**
    * \brief ȡ�õ�ǰ�Ĺ滮����
    *
    * \return �滮����
    */
    const PlanSetting &GetPlanParas()
    {
      return m_setting;
    }

    /**
    * \brief ���ù滮����
    *
    * \param setting �滮����
    */
    void SetPlanParas(const PlanSetting &setting);

    //
    // Methods for its components
    //
    /**
    * \brief ȡ��CUeGuider�����ָ��
    */
    CUeGuider *GetGuider()
    {
      assert(m_guider);
      return m_guider;
    }

    /**
    * \brief ȡ�þ���ʵ����Ķ����ָ��
    */
    CUeRouteImpl *GetImpl()
    {
      assert(m_impl);
      return m_impl;
    }

    //
    //
    //
    /**
    * \brief TODO:δʹ�õĽӿ�
    * Let outside have a chance to know the detail when running once route plan
    */
    void SetHook(CRouteHook *oneHook);

    /**
    * \brief TODO:δʹ�õĽӿ�
    */
    CRouteHook *GetHook();

    /**
    * \brief ֪ͨ�۲���
    */
    virtual void Notify(short type);

    /**
    * \brief ע��۲���
    */
    virtual void Register(CObserver *oneObserver);

    /**
    * \brief ע����Դ������
    */
    void RegisterGarbage(CMemoryGarbage *garbage);

    /**
    * \brief ȡ����Դ������
    */
    CMemoryGarbage *GetGarbage() const;

    /**
    * \brief ע���н��� 
    */
    void RegisterMediator(CMediator *mediator);

    /**
    * \brief ȡ���н���
    */
    CMediator *GetMediator() const;

    //
    //
    //
    /**
    * \brief ����������������
    */
    void SetVoiceSettings(const UeBase::VoiceSettings &settings);

    /**
    * \brief ����TTS�������ɫ
    */
    unsigned int SetRole(UETTS_Role role);

    //
    //
    //
    /**
    * \brief ȡ��·�ι�����Ϣ
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
    * \param infoCode ��Ϣ��
    * \param dirCode ת��
    * \param distForSnd ����ת��ľ���
    */
    void RePlayVoice(unsigned char infoCode,unsigned char dirCode, int distForSnd);

    //
    //
    //
#if VARIANTLOGGER
    /**
    *
    */
    static const tstring &GetLogFile()
    {
      return m_log.GetLogFile();
    }
#endif

  private:
    //
    //
    //
    /**
    *
    */
    unsigned int IsValidPositions();

    /**
    *
    */
    unsigned int IsValidMethod();

  protected:
    /// One way of route plan
    CUeRouteImpl *m_impl;

    /// Voice guider
    CUeGuider *m_guider;

    /// Simulator
    CUeSimulator *m_simulator;

    //
    IMapMatch *m_gps;

    // Positions for route plan
    // Planned distance for some decisions
    CMemVector m_positions;
    int m_maxPosNum;

    // Hints for calculation process compared to m_plannedDist
    const static int MAXPROGRESSLEVEL = 5;
    const static int PROGRESSLEVEL = 100 / MAXPROGRESSLEVEL;
    double m_plannedDist;
    double m_processDist;
    bool  m_isRendered[MAXPROGRESSLEVEL];
    short m_curProcessLevel;

    /// Setting for once route plan
    PlanSetting m_setting;

    // Specification for once route plan
    unsigned int m_method;
    unsigned char m_prevPlan;
    unsigned char m_curPlan;

    // Plan hook 
    // Observers for waiting the planning results
    CRouteHook *m_hook;
    ObserverVector m_observers;

    /// Let outside get a decision
    PlanState m_planState;

    /// Memory collector
    CMemoryGarbage *m_garbage;

    /// Favored links
    CFavoredNetwork *m_favors;

    /// Mediator
    CMediator *m_mediator;

#if VARIANTLOGGER
    static CDbgLogger m_log;
    static int m_runTimes;
#endif


  private:
    /// Singletion for NavPlan package
    static IRoute *m_route;

    //
    short m_logPlayState;
  };
}

#endif