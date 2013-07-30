/*
* ·���滮ģ��ӿ��ṩ
*
*/
#ifndef _UEGUI_ROUTEWRAPPER_H
#define _UEGUI_ROUTEWRAPPER_H

#include "uegui.h"
#include "ueroute/routebasic.h"
#include "ueroute/route.h"
#include "uemodel/network.h"
#include "uemodel/netnametable.h"
#include "uemap/view.h"
#include "uegps/mapmatch.h"
#include "uequery/query.h"

using namespace UeMap;
using namespace UeModel;
using namespace UeRoute;
using namespace UeQuery;

namespace UeGui
{
  struct RouteInfo
  {
    char m_routeName[128];            //��·����
    UeBase::CGeoPoint<long> m_point;  //��·����
    float m_mileages;                 //��·���
    unsigned char m_direction;        //����
    unsigned short m_parcelIdx;       //��·�ڵ�ͼ�еĿ�����
    unsigned short m_linkIdx;         //��·�ڵ�ͼ�е�ID
    short m_begin;  //���ĸ�λ�ÿ�ʼ
    short m_end;   //���ĸ�λ�ý���������ͬ��·λ�á�����Ϊ[m_begin,m_end)
    bool m_dodge;  //�Ƿ���
    RouteInfo()
    {
      ::memset(m_routeName, 0, sizeof(m_routeName));
      m_mileages = 0.0;
      m_direction = 0;
      m_parcelIdx = 0;
      m_linkIdx = 0;
      m_begin = 0;
      m_end = 0;
      m_dodge = false;
    }
    const RouteInfo &operator =(const RouteInfo &other)
    {
      if(this == &other)
      {
        return *this;
      }
      ::memcpy(m_routeName, other.m_routeName, sizeof(m_routeName));
      m_mileages = other.m_mileages;
      m_direction = other.m_direction;
      m_point = other.m_point;
      m_parcelIdx = other.m_parcelIdx;
      m_linkIdx = other.m_linkIdx;
      m_begin = other.m_begin;
      m_end = other.m_end;
      return *this;
    }
  };
  //·���б�
  typedef std::vector<RouteInfo> RouteList;
  typedef RouteList::iterator RouteListItr;

  typedef std::vector<UeRoute::PlanPosition> PlanPositionList;

  class CRouteWrapper
  {
  public:
    /**
    * \brief ��������
    */
    virtual ~CRouteWrapper();
  private:
    /**
    * \brief ���캯��
    */
    CRouteWrapper();
  public:
    /*
    * ��ȡ����
    */
    static CRouteWrapper& Get();

    /**
    * \brief �������
    */
    unsigned int SetRouteStart();

    /**
    * \brief ���þ�����
    */
    unsigned int SetRouteMiddle();

    /**
    * \brief �����յ�
    */
    unsigned int SetRouteEnd();

    /**
    * \brief ɾ��������㡢�յ���ɵ�
    *
    * \param isReserved ���Ϊtrue��������λ�ã�ֻ����ΪPT_Invalid������ֱ��ɾ��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int RemovePosition(bool isReserved = false);

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

    /**
    * \brief �滮ǰ�ĳ�ʼ��
    */
    unsigned int Prepare();

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
    * \brief ���ù滮��ʽ
    */
    unsigned int SetMethod(unsigned int method);

    /**
    * \brief ��ȡ��ǰ�Ĺ滮��ʽ
    */
    unsigned int GetMethod();

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
    * \brief ��ʼ����
    */
    unsigned int StartGuidance();

    /**
    * \brief ֹͣ����
    */
    unsigned int StopGuidance();

    /**
    * \brief ȡ�ù滮����ķֶ��������ݾ��ɵ㻮�֣�
    */
    int GetPairs();

    /**
    * \brief ��õ�ǰ�滮״̬
    */
    short GetPlanState();

    /**
    * \brief ���ù滮״̬
    */
    void SetPlanState(short state);

    /*
    * ��ȡ������·�б�
    */
    void GetPassedRouteList(RouteList& routeList);

    /*
    * ��ȡ���ɵ��б�
    */
    void GetPlanPositionList(PlanPositionList& positionList);
    
    /*
    * ��ȡ����λ�õ���ǰIndicatorʣ�µľ���
    */
    float GetCurIndicatorLeftDist(const GuidanceStatus& dirInfo);    

    /*
    * �ϲ���ͬ��·
    */
    void MergeRoad(RouteList& routeList);

    /**
    * \brief ȡ�õ�ǰ�貥���ĵ�������Ϣ
    */
    bool GetCurElecEye(EEyeProp &elecEye);
  private:
    /*
    * �����������յ���߾�����
    */
    unsigned int SetPosition(PositionType posType);
  private:
    //�������������㷨���ж��Ƿ�Ϊ��ͬ��·��ֻ��ֱ�е�·�����ж�
    class DifferentRoad 
    {
    public:
      explicit DifferentRoad(const RouteInfo& info) : m_info(info) {}
      bool operator() (const RouteInfo& rhs) 
      {
        if (IsSimilarDirection(rhs.m_direction) && IsSimilarDirection(m_info.m_direction) &&
          ((::strcmp(m_info.m_routeName, rhs.m_routeName) == 0) || 
          ::strcmp(rhs.m_routeName, "һ���·") == 0))
        {
          return false;
        }
        return true;
      }

      bool IsSimilarDirection(unsigned char direction) 
      {
        if ((UeRoute::DVT_DirectGo == direction) ||
          (UeRoute::DVT_MiddleGo == direction) ||
          (UeRoute::DVT_RightDirect == direction) ||
          (UeRoute::DVT_LeftDirect == direction) ||
          (UeRoute::DVT_Unknown == direction))
        {
          return true;
        }
        return false;
      }
    private:
      const RouteInfo& m_info;
    };

    class DifferentNameRoad
    {
    public:
      explicit DifferentNameRoad(const RouteInfo& info) : m_info(info) {}
      bool operator() (const RouteInfo& rhs)
      {
        if (::strcmp(m_info.m_routeName, rhs.m_routeName) == 0 
          || ::strcmp(rhs.m_routeName, "һ���·") == 0)
        {
          return false;
        }
        return true;
      }
    private:
      const RouteInfo& m_info;
    };

    //�����������ڼ����·����֮�͡�
    class SumMileages 
    {
    public:
      explicit SumMileages(float* valueAddr) : m_sumValueAddr(valueAddr) {}
      void operator() (const RouteInfo& rhs) 
      {
        if (m_sumValueAddr)
        {
          (*m_sumValueAddr) += rhs.m_mileages;
        }
      }
    private:
      float* m_sumValueAddr;
    };
  private:
    IRoadNetwork *m_net;
    IView *m_view;
    IRoute *m_route;
    IMapMatch *m_gps;
    IQuery *m_query;
  };
}
#endif