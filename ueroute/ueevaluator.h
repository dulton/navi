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
#ifndef _UEROUTE_EVALUATOR_H
#define _UEROUTE_EVALUATOR_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to route basic definition
#ifndef _UEROUTE_ROUTEBASIC_H
#include "routebasic.h"
#endif

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling
#pragma warning( disable: 4251 )  // Deprecated function calling

//
namespace UeRoute
{
  /**
  * \brief ����ֵ����
  */
  class UEROUTE_CLASS CUeEvaluator
  {
    // Relatives
    friend class CAStarRoute;

  public:
    //
    //
    //
    /**
    * \brief Ĭ�Ϲ��캯��
    */
    CUeEvaluator();

    /**
    * \brief ��������
    */
    virtual ~CUeEvaluator();

  protected:
    //
    //
    //
    /**
    * \brief ȡ�ù滮��ز�����Ϊ������׼����
    */
    void Prepare();

    /**
    * \brief ����ָ��·�εĹ���ֵ
    */
    void GetCost(PlannedLink *oneLink);

    /**
    * \brief ����ͨ�й���ֵ
    */
    void GetCost(PlannedLink *prevLink, PlannedLink *curLink, PlannedLink *nextLink, short cLinks, double directDist = 0, bool isSE = true);

    /**
    * \brief ���ݽǶȻ��ת��
    * 
    * \param turnAngle ת��Ƕ�
    * \param turnType �μ�TurnType����
    * \return ת��ö��ֵ���μ�TurnDirection����
    */
    short GetTurnDirection(short turnAngle, short turnType);

    /**
    * \brief ���ݾ����þ�������
    *
    * \param length ·�γ���
    * \return �μ�DistType����
    */
    short GetDistType(double length);

    /**
    * \brief ��������ͨ�й���ֵ
    */
    void GetSECost(PlannedLink *prevLink, PlannedLink *curLink, PlannedLink *nextLink, short cLinks, double directDist = 0);

    /**
    * \brief ���㷴��ͨ�й���ֵ
    */
    void GetESCost(PlannedLink *prevLink, PlannedLink *curLink, PlannedLink *nextLink, short cLinks, double directDist = 0);

    /**
    * \brief �����շ���Ϣ����Ȩֵϵ��
    */
    void AdjustCost(short &rtCost);

    /**
    * \brief �ж�ָ��·���Ƿ�ΪRamp
    */
    bool IsRamp(const PlannedLink *const curLink);

    /**
    * \brief �ж�ָ��·���Ƿ�Ϊ�߼�·
    */
    bool IsVirtual(const PlannedLink *const curLink);

    /**
    * \brief �ж�ָ��·���Ƿ�Ϊ����
    */
    bool IsRoundAbout(const PlannedLink *const curLink);

    /**
    * \brief �ж�ָ��·���Ƿ�Ϊ������
    */
    bool IsSA(const PlannedLink *const curLink);

    /**
    * \brief �ж�ָ��·���Ƿ�Ϊ���е�
    */
    bool IsWalkway(const PlannedLink *const curLink);
  private:
    //
    short m_methodType;
    PlanSetting m_setting;

    /// Cost for different road types
    static short m_rtCost[4][3][4][15];
    //
    static short m_toCost[4][3][4];
    //
    static short m_turnCost[4][4];
  };
}

#endif
