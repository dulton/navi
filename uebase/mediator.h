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
#ifndef _UEBASE_MEDIATOR_H
#define _UEBASE_MEDIATOR_H


// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEBASE_DEF_H
#include "uebase.h"
#endif

// Refer to geom basic definitions
#ifndef _UEBASE_GEOMBASIC_H
#include "geombasic.h"
#endif

// Refer to ViewSettings
#ifndef _UEBASE_UESETTINGS_H
#include "uebase\uesettings.h"
#endif

// UeBase namespace
namespace UeBase
{
  // Forward class
  class CObserver;

  // Following the definition of OBERSVER & MEDIATOR patterns, there should have some obvious different semantics:
  // For OBSERVER pattern, it generllay maintain the message communication bewteen one object (CObservable) with those
  // objects (CObservers) interested by it. However, MEDIATOR is simply to decouple the unneccessary relationships among
  // some objects, namely, they shouldn't seen each other in order to let them development in more easiy way etc.
  // 
  // Here, both patterns supply an indirect calling to other objects, so it is possible to let those interfaces exposed by
  // those packeges can be envolved independently.
  //
  // But when mixing below interface defintion with one interface specified by one package, namely using multi-inherit way
  // we should care about its compiling error when against different C++ compiles and its memory layout.
  //
  /*! \class CObservable
  * \brief Obersvale object is to notify its changes to those interesting observers.
  */
  class CObservable
  {
  public:
    //
    //
    //
    /**
    * \brief ��������
    */
    virtual ~CObservable(){}

    //
    //
    //
    /**
    * \brief �����й۲��߷���֪ͨ����������Update�ӿڡ�
    * Let sub-class have its specified event types
    * 
    * \param type ��Ϣ���ͣ����嶨��ο�����ʵ��
    */
    virtual void Notify(short type) = 0;

    /**
    * \brief ע��۲���
    *
    * \param oneObserver ����Ĺ۲���
    */
    virtual void Register(CObserver *oneObserver) = 0;
  };

  /*! \class CObserver
  * \brief �۲��߽ӿڶ���
  */
  class CObserver
  {
  public:
    //
    //
    //
    /**
    * \brief ��������
    */
    virtual ~CObserver(){}

    //
    //
    //
    /**
    * \brief ���յ����۲�����notify֪ͨ�����״̬
    * 
    * \param type ��Ϣ����
    * \param para �������ض�����(�����Ҫ)
    */
    virtual void Update(short type = 0, void *para = 0) = 0;
  };

  /**
  * \brief In order to throughly decouple the relationships between each package of UrbanEye PND, it had better to 
  * specify the funtion prototype here representing those kinds of relationship as suitable as possible.
  */
  class CMediator
  {
  public:
    //
    //
    //
    /**
    * \brief ��������
    */
    virtual ~CMediator()
    {
    }

  public:
    //
    // Decouple relationships among different packages as more as possible.
    //
    /**
    * \brief ����UeRoute��UeGPS����ģ���Ľ���ɲο�UeRouteģ���IsPassing�ӿڻ�ø���ϸ����Ϣ
    *
    * \param parcelIdx parcel��Ψһ��ʶ��
    * \param linkIdx ָ��parcel��link��Ψһ��ʶ��
    */
    virtual bool IsPassing(long parcelIdx, long linkIdx) = 0;

    /**
    * \brief TODO:δʹ��
    */
    virtual short RenderingLayer() = 0;

    /**
    * \brief TODO:δʹ��
    */
    virtual void RenderingLayer(short curLayer) = 0;

    /*!
    * \brief �ж�UeRouteģ���Ƿ��ڹ滮״̬��
    * TODO:δʹ�õĽӿ�
    */
    virtual bool IsPlanning() = 0;

    /**
    * \brief ����UeRouteģ���Ƿ��ڹ滮״̬
    * TODO:δʹ�õĽӿ�
    */
    virtual void IsPlanning(bool isPlanning) = 0;

    /*!
    * \brief ��ȡ��ǰ����������������Ψһ��ʶ����
    * ��Ҫ����UeRoute��UeMap����ģ���Ľ����ֹUeRouteģ���UeMapģ������������ο�UeMapģ���GetDistrictIdx��øýӿ���ϸ��Ϣ
    *
    * \param pos ��ͼ����
    */
    virtual int GetDistrictIdx(const CGeoPoint<long> &pos) = 0;

    /*!
    * \brief ��ȡ��ǰ��������������������(���ؼ�)��
    * 
    * \param[in] pos ��ͼ����
    * \param[in][out] distName ����������
    */
    virtual void GetDistrictName(const CGeoPoint<long> &pos, char *distName) = 0;

    /**
    * \brief ��ȡ��ǰ�滮��ʽ����·��״̬��
    */
    virtual unsigned char GetMultiMethodType() = 0;

    /**
    * \brief �Ƿ���ָ����״̬
    */
    virtual bool IsShowCompass() = 0;

    /**
    * \brief Decouple UeRoute & UeMap in order to let Re-route calling reasonably
    */
    virtual bool IsReadyForPlanning() = 0;

    /*!
    * \brief ��������Hooks֮ǰ��Ҫ������hook����·��
    **/
    virtual void SetHooksPath(TCHAR* path) = 0;

    /*!
    * \brief ���ز�Ʒ����hook
    **/
    virtual void LoadProductActivationHook() = 0;

    /*!
    * \brief ע����ܼ���ϵ�к���
    */
    virtual bool RegisterActiveFunc(void *getuuid, void *checkIsActive, void *checkActiveID, void *saveActiveFile) = 0;

    /**
    * \brief ��ȡΨһʶ����
    */
    virtual unsigned long LsGetUUID(char *path,char *uuid) = 0;

    /**
    * \brief ��֤�Ƿ��Ѿ�����
    */
    virtual unsigned long LsCheckIsActive(char *path,char *uuid) = 0;

    /**
    * \brief ��֤�������Ƿ�Ϸ�
    */
    virtual unsigned long LsCheckActiveID(char *uuid,char* activeid) = 0;

    /**
    * \brief ��֤ͨ����,���漤���ļ�
    */
    virtual unsigned long LsSaveActiveFile(char *path,char *uuid,char* activeid) = 0;

    /*!
    * \brief ��������Hooks֮ǰ��Ҫ������hook����·��
    **/
    virtual void LoadHooks() = 0;

    /*!
    * \brief ��Ⱦ����ͼHook����
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderHooks(const CGeoRect<short> &scrExtent) = 0;

    /*!
    * \brief ��Ⱦ����ͼHook����(�磺·�ڷŴ�ͼ��ӥ��ͼ)
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderSubViewHooks(const CGeoRect<short> &scrExtent) = 0;

    /*!
    * \brief ��Ⱦ��¼������Hook
    *
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderLogonHooks(const CGeoRect<short> &scrExtent, short step) = 0;

    /*!
    * \brief  ������ӦHooks��״̬���ػ�
    *
    * \param type �������ͣ���ϸö�ٶ���鿴UpdateHookType
    * \param para �������ض�����(�����Ҫ)
    */
    virtual void UpdateHooks(short type, void *para = 0) = 0;

    /*!
    * \brief ��õ�ͼ��ʾ����
    */
    virtual const ViewSettings &GetMapSettings() = 0;

    /*!
    * \brief �ж��Ƿ�Ϊ��Ϣ��ʾ��
    */
    virtual bool IsMsgBox() = 0;

    /*!
    * \brief �ж��Ƿ�Ϊ��¼��Ϣ��
    */
    virtual bool IsRecBox() = 0;

    /**
    * \brief �жϵ�ǰ�����Ƿ�Ϊ��ͼ����
    */
    virtual bool IsMapHook() = 0;

    /**
    * \brief �ж��豸�ڴ�״̬
    *
    * \return �����ڴ��Ƿ����޵�״̬��trueΪ���ڴ档
    */
    virtual bool IsMemoryLimited() = 0;

    /**
    * \brief �����ڴ�״̬
    */
    virtual void SetMemoryStatus(bool isMemoryLimited) = 0;
  };
}

#endif