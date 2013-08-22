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
#ifndef _UEROUTE_ASTAR_H
#define _UEROUTE_ASTAR_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to its parent
#ifndef _UEROUTE_ROUTEIMPL_H
#include "uerouteimpl.h"
#endif

// Refer to route basic defintions
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

// Refer to road network defintions
#ifndef _UEMODEL_ROADNETWORK_H
#include "uemodel\network.h"
#endif

// Refer to net parcel defintions
#ifndef _UEMODEL_NETPARCEL_H
#include "uemodel\netparcel.h"
#endif

// Refer to net link definitions
#ifndef _UEMODEL_ROADLINK_H
#include "uemodel\netlink.h"
#endif
using namespace UeModel;

// Refer to memory basic operations
#ifndef _UEBASE_MEMBASIC_H
#include "uebase\membasic.h"
#endif

// Refer to running loger
#ifndef _UEBASE_DBGTRACER_H
#include "uebase\dbglogger.h"
#endif

// Refer to mathematical basic
#ifndef _UEBASE_MATHBASIC_H
#include "uebase\mathbasic.h"
#endif
using namespace UeBase;

// Log macro
#if __LOG_RUNNING__
#define ASTARLOGGER 1
#endif

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling

//
namespace UeRoute
{
  // Relatives
  class CUeEvaluator;
  class IRoute;

  /**
  * \brief A���㷨ʵ�ֵ�·���滮����
  */
  class UEROUTE_CLASS CAStarRoute : public CUeRouteImpl
  {
  public:
    /// Indice for open and close tables
    typedef std::vector<ElementIndex> IndexVector;
    typedef std::multimap<long, ElementIndex> IndexMap; 

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CAStarRoute();

    /**
    * \brief ��������
    */
    virtual ~CAStarRoute();

  public:
    //
    //
    //
    /**
    * \brief ���ø�����IRoute�ӿ�
    *
    * \param parent ����IRoute�ӿ�
    */
    virtual void SetParent(IRoute *parent);

    /**
    * \brief ��������������Ϣ�Ķ���
    *
    * \param guider ����������Ϣ���ɵ���CUeGuider�Ķ���ָ��
    */
    virtual void SetGuider(CUeGuider *guider);

    /**
    * \brief �滮ǰ�ĳ�ʼ������
    *
    * \param isReady ���Ϊtrue����Ϊ�滮����ռ䲢��ʼ���������ͷ���Դ
    */
    virtual unsigned int Prepare(bool isReady = true);

    /**
    * \brief �滮������
    */
    virtual unsigned int DoPlan();

    /**
    * \brief ƫ���ع滮
    */
    virtual unsigned int RePlan();

    /**
    * \brief ����PC�˼��鹤�ߵ���־�ӿ�
    */
    virtual void SetPlanLogFile(void *logFile);

    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues();

    //
    //
    //
#if ASTARLOGGER
    /**
    * \brief ȡ��A���㷨·���滮����־�ļ���
    */
    static const tstring &GetLogFile()
    {
      return m_logAll.GetLogFile();
    }
#endif

  protected:
    //
    //
    //
    /**
    * \brief ��SE����ĵ�ǰ·�ν�����չ
    */
    unsigned int NextSELink();

    /**
    * \brief ��ES����ĵ�ǰ·�ν�����չ
    */
    unsigned int NextESLink();

    /**
    * \brief ����������׼
    */
    unsigned int SetMeetStandard();

    /**
    * \brief ȡ�ÿ����е����·�Σ�Ȼ�󽫸�·�δӿ�����ɾ��������ձ�
    *
    * \param isSE ture��ʾSE����,false��ʾES����
    */
    unsigned int GetCurLink(bool isSE = true);

    //
    //
    //
    /**
    * 
    */
    int GetChildrenIdxes(PlannedLink *oneLink, CMemVector &children);

    /**
    * 
    */
    void WritePlanLog(PlannedLink *oneLink, bool isSE);

    //
    //
    //
    /**
    * \brief ��ʼ�������յ㼰��ƥ���·����Ϣ
    */
    unsigned int InitPosition(PlanPosition &startPos, PlanPosition &endPos, short orderType);

    /**
    * \brief �ж�SE�����ES����������Ƿ�����
    */
    unsigned int IsMeetWith(bool isSE = true);

    /**
    * \brief ���ָ��·���ڿ��ձ��ж������ڣ�����·�����뿪��(SE����)�����Կ����������
    *        ���ָ��·���ڿ������Ѿ����ڣ��Ƚ���Ȩ�أ����ָ��·����Ȩ�ؽ�С�����滻���������Ѵ��ڵĶ�Ӧ·����
    */
    unsigned int SetSEOpenTable(PlannedLink *prevLink, PlannedLink *curLink, PlannedLink *nextLink);

    /**
    * \brief ���ָ��·���ڿ��ձ��ж������ڣ�����·�μ��뿪��(ES����)�����Կ����������
    *        ���ָ��·���ڿ������Ѿ����ڣ��Ƚ���Ȩ�أ����ָ��·�ε�Ȩ�ؽ�С�����滻���������Ѵ��ڵĶ�Ӧ·�Σ�
    */
    unsigned int SetESOpenTable(PlannedLink *prevLink, PlannedLink *curLink, PlannedLink *nextLink);

    /**
    * \brief ��ָ�����ѷ���·�μ���ձ�(SE����)
    */
    unsigned int SetSECloseTable(const ElementIndex &oneIndex);

    /**
    * \brief ��ָ�����ѷ���·�μ���ձ�(ES����)
    */
    unsigned int SetESCloseTable(const ElementIndex &oneIndex);

    /**
    * \brief �Ƿ���Ҫ�л�·�����������
    *
    * \param isSE ture��ʾSE����,false��ʾES����
    */
    unsigned int IsSwitchLayer(bool isSE = true);

    /**
    * \brief ���ɹ滮��·��
    */
    unsigned int MakePrompts(int pair);

    /**
    * \brief �����ǰ·�ε�ָ����·�ο�ͨ�У���������ֵ����������뿪��(SE����)
    *
    * \param oneParcel ��ǰ����
    * \param oneLink ָ����link
    * \param parcelIdx �����ʶ
    * \param linkIdx link��ʶ
    * \param nodeIdx ����ʶ
    * \param layerType ���ڵ�·����
    * \param clinks ��ǰ·�����ӵ�·����
    * \param isMrt �Ƿ�ʹ�ù���
    * \return ���ָ��·��Ϊ��ͨ�е�·�β��ɹ����뿪���򷵻�true�����򷵻ش������
    */
    unsigned int GetSENext(INetParcel *oneParcel, INetLink *oneLink, long parcelIdx, long linkIdx, long nodeIdx, short layerType, short clinks, bool isMrt = true, bool isMainNode = false);

    /**
    * \brief �����ǰ·�ε�ָ����·�ο�ͨ�У���������ֵ����������뿪��(ES����)
    *
    * \param oneParcel ��ǰ����
    * \param oneLink ָ����link
    * \param parcelIdx �����ʶ
    * \param linkIdx link��ʶ
    * \param nodeIdx ����ʶ
    * \param layerType ���ڵ�·����
    * \param clinks ��ǰ·�����ӵ�·����
    * \param isMrt �Ƿ�ʹ�ù���
    * \return ���ָ��·��Ϊ��ͨ�е�·�β��ɹ����뿪���򷵻�true�����򷵻ش������
    */
    unsigned int GetESNext(INetParcel *oneParcel, INetLink *oneLink, long parcelIdx, long linkIdx, long nodeIdx, short layerType, short clinks, bool isMrt = true, bool isMainNode = false);

    /**
    * \brief �����ǰ���Ϊ����߽��㣬ȡ�������ӵĿ�ͨ�е�·�β����뿪��(GetSENext/GetESNext)
    *
    * \param curParcel ��ǰ����
    * \param curNodeIdx ��ǰ����ʶ
    * \param isSE ture��ʾSE����,false��ʾES����
    */
    bool FollowAdjacent(INetParcel *curParcel, long curNodeIdx, bool isSE = true);

    /**
    * \brief �����ǰ���Ϊ�ϲ��㣬ȡ�������ӵĿ�ͨ�е�·�β����뿪��(GetSENext/GetESNext)
    *
    * \param curParcel ��ǰ����
    * \param curNodeIdx ��ǰ����ʶ
    * \param isSE ture��ʾSE����,false��ʾES����
    * \param isMainNode ���ϲ����Ƿ�Ϊ�����
    */
    bool FollowUpper(INetParcel *curParcel, long curNodeIdx, bool isSE = true, bool isMainNode = false);

    /**
    * \brief �����ǰ���Ϊ����㣬ȡ�������ӵĿ�ͨ�е�·�β����뿪��(GetSENext/GetESNext)
    *
    * \param curParcel ��ǰ����
    * \param curNodeIdx ��ǰ����ʶ
    * \param isSE ture��ʾSE����,false��ʾES����
    */
    bool FollowMain(INetParcel *curParcel, long curNodeIdx, bool isSE = true);

    /**
    * \brief �����ǰ���Ϊ��ͨ��㣬ȡ�������ӵĿ�ͨ�е�·�β����뿪��(GetSENext/GetESNext)
    *
    * \param curParcel ��ǰ����
    * \param curNodeIdx ��ǰ����ʶ
    * \param isSE ture��ʾSE����,false��ʾES����
    */
    bool FollowNormal(INetParcel *curParcel, long curNodeIdx, bool isSE = true, bool isMainNode = false);

    /**
    * \brief �ж�ָ��·���Ƿ��Ǳ���ܵ�����
    *
    * \param oneLink ָ����·��
    * \param curLink ��ǰ·����Ϣ
    */
    bool IsPermitted(INetLink *oneLink, const PlannedLink *curLink = 0);

    /**
    * \brief ������ʼ·����Ϣ
    */
    void GenerateStart(INetParcel *oneParcel, INetLink *oneLink, short orderType, short isSE = 1);

    /**
    * \brief ������ֹ·����Ϣ
    */
    void GenerateEnd(INetParcel *oneParcel, INetLink *oneLink, short orderType, short isSE = 1);

    /**
    * \brief �Ƿ�ʹ���ϲ�·��
    */
    bool IsUseUpLayer(bool isSE = true);

    /**
    *
    * \brief �Ƿ��л���Global·����
    */
    bool IsUpGLayer(bool isSE = true);

    /**
    * \brief �Ƿ��л���Speed·����
    */
    bool IsUpSLayer(bool isSE = true);

    /**
    * \brief �Ƿ��л���Mre·����
    */
    bool IsUpMLayer(bool isSE = true);

    /**
    * \brief �жϵ�ǰ�����link�Ƿ������ջ�(�Ѿ��ڱձ��д���)������ᵼ�±ջ����򲻽���link���뿪��
    */
    bool IsSECyclic(PlannedLink *nextLink);

    /**
    * \brief �жϵ�ǰ�����link�Ƿ������ջ�(�Ѿ��ڱձ��д���)������ᵼ�±ջ����򲻽���link���뿪��
    */
    bool IsESCyclic(PlannedLink *nextLink);

    /**
    * \brief �ж�����·���Ƿ���ڹ��Ƶ����޷�ͨ��
    */
    bool IsMrtNot(PlannedLink *oneLink, bool isSE);

    /**
    * \brief �Ƿ�Ϊ�������·��(��ͨ��)
    */
    bool IsSenseLink(INetLink *curLink);

    /**
    * \brief �����Ƿ������ж�ʱ�������ǰ·������Ϊ�ض����ͣ�����Ϊ������
    */
    bool IsSpecialRoadForm(const PlannedLink *const curLink);

  private:
    // The distance to start and end in both directions
    double m_maxSEDist;
    double m_maxESDist;
    double m_directDist;

    // TODO:
    // Remove those specified member variables since it face the layers
    // in variation
    bool m_isUseGLayer;
    bool m_isUseSLayer;
    bool m_isUseMLayer;

    /// Record current calculation loop number in order to efficiently prune search tree
    unsigned int m_loopNumber;

    // Positions for planning
    NetPosition m_startNetPos;
    NetPosition m_endNetPos;

    /// The standards for the same link meet
    MeetStandard m_meetStandard;

    // Tables for both directions
    PlannedLink *m_seLinks;
    PlannedLink *m_esLinks;
    int m_seNum;
    int m_esNum;

    // Current link respectively in both directions
    PlannedLink *m_seCurLink;
    PlannedLink *m_esCurLink;

    // Indices for above tables
    IndexVector m_seOpenTable;
    IndexVector m_esOpenTable;
    IndexMap m_seCloseTable;
    IndexMap m_esCloseTable;

    //
    short m_prevSize;

    // TODO: Flag to swith layer
    // Remove those specified member variables since it face the layers
    // in variation
    short m_seGPoints;
    short m_seSPoints;
    short m_seMPoints;
    short m_esGPoints;
    short m_esSPoints;
    short m_esMPoints;

    //
    IRoadNetwork *m_network;

    /// Fix memory fragaments caused by lower CE versions
    CMemBasic m_memBasic;

    //
    const CMathBasic &m_mathBasic;

    /// Weight evaluation
    static CUeEvaluator *m_evaluator;

    //
#if ASTARLOGGER
    static CDbgLogger m_logAll;
#endif

    /// ����PC���鹤�ߵ���־�ļ�
    void *m_planLogFile;
    unsigned char m_logType;

  public:
    // For STL function reference
    static short m_seCurLayer;
    static short m_esCurLayer;
  };
}

#endif