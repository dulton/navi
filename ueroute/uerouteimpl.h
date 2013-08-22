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
#ifndef _UEROUTE_ROUTEIMPL_H
#define _UEROUTE_ROUTEIMPL_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEROUTE_BASE_H
#include "ueplan.h"
#endif

// Refer to STL definition etc
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to geometry basic definition
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Refer to own-specific array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling
#pragma warning( disable: 4996 )  // Deprecated function calling

//
namespace UeRoute
{
  // Forward classes
  class CUeGuider;
  class IRoute;
  class CRouteDecorator;

  /**
  * \brief ·���滮�ӿڵ�ʵ����
  */
  class UEROUTE_CLASS CUeRouteImpl : public CMemoryConsumer
  {
    // Relatives
    friend class IRoute;

  protected:
    //
    typedef std::map<short, CRouteDecorator*> DecoratorMap;
    typedef DecoratorMap::iterator decr_itr;
    typedef DecoratorMap::const_iterator decr_citr;

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    */
    CUeRouteImpl();

    /**
    * \brief ��������
    */
    virtual ~CUeRouteImpl();

  public:
    //
    // Basic one algorithm behaviors
    //
    /**
    * \brief ���ø�����IRoute�ӿ�
    *
    * \param parent ����IRoute�ӿ�
    */
    virtual void SetParent(IRoute *parent) = 0;

    /**
    * \brief ��������������Ϣ�Ķ���
    *
    * \param guider ����������Ϣ���ɵ���CUeGuider�Ķ���ָ��
    */
    virtual void SetGuider(CUeGuider *guider) = 0;

    /**
    * \brief �滮������
    */
    virtual unsigned int DoPlan() = 0;

    /**
    * \brief ƫ���ع滮
    */
    virtual unsigned int RePlan() = 0;

    /**
    * \brief ����PC�˼��鹤�ߵ���־�ӿ�
    */
    virtual void SetPlanLogFile(void *logFile) = 0;

    /**
    * \brief �滮ǰ�ĳ�ʼ������
    *
    * \param isReady ���Ϊtrue����Ϊ�滮����ռ䲢��ʼ���������ͷ���Դ
    */
    virtual unsigned int Prepare(bool isReady = true) = 0;

    //
    // Decorators or different strategies
    //
    /**
    * \brief ͨ�����ָ����װ���������ض���Ϊ
    *
    * \param type �μ�DecoratorType����
    * \param oneDecorator �����װ��������ָ��
    */
    virtual unsigned int AddDecorator(short type, CRouteDecorator *oneDecorator);

    /**
    * \brief ɾ��ָ����װ����
    *
    * \param type �μ�DecoratorType����
    */
    virtual unsigned int RemoveDecorator(short type);

    /**
    * \brief ���ָ��λ�õ�·��
    *
    * \param onePos ָ���ĵ�ͼλ��
    * \param isRemoved ���Ϊtrue�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    virtual unsigned int SetBlock(CGeoPoint<long> &onePos, bool isRemoved = false);

    /**
    * \brief ���ָ����Χ��·��
    *
    * \param oneExtent ָ���ĵ�ͼ���귶Χ
    * \param isRemoved ���Ϊtrue�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    virtual unsigned int SetBlock(CGeoRect<long> &oneExtent, bool isRemoved = false);

    /**
    * \brief ���ָ����·��
    *
    * \param ids Ҫ��ܵ�BlockElement����
    * \param isRemoved ���Ϊtrue�������ָ���Ĺ��·�Σ���������й����ɾ��ָ���Ĺ��·��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    virtual unsigned int SetBlock(CMemVector &ids, bool isRemoved = false);

    /**
    * \brief ɾ�����й��·��
    *
    * \param isRemoved ���Ϊtrue��ɾ�����е����й��·�Σ�����ֱ�ӷ���
    * \return ����PEC_Success
    */
    virtual unsigned int SetBlock(bool isRemoved = false);

    //
    // Inherited from one functor definition
    //
    /**
    * \brief ��Դ����
    */
    virtual bool ForCollegues() = 0;

  protected:
    //
    IRoute *m_parent;

    //
    CUeGuider *m_guider;

    //
    DecoratorMap m_decorators;
  };
}
#endif
