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
#ifndef _UEFACADE_UEMEDIATOR_H
#define _UEFACADE_UEMEDIATOR_H

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEFACADE_BASE_H
#include "uefacade.h"
#endif

// Refer to its parent
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif

// Refer to geom basic definitions
#ifndef _UEBASE_GEOMBASIC_H
#include "uebase\geombasic.h"
#endif

// Refer to UeBase packge for ViewSettings
#ifndef _UEBASE_UESETTINGS_H
#include "uebase\uesettings.h"
#endif
using namespace UeBase;

//
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z

//
namespace UeFacade
{
  // Forward class
  class CUeWrapperImpl;

  /*! \class CUeMediator
  *
  * \brief ���н��߽ӿ�CMediator��ʵ�֣���Ը�ģ�����Ϣ�����ṩ�н�(����)��mediator���ģʽ��
  */
  class UEFACADE_CLASS CUeMediator : public CMediator
  {
  public:
    //
    //
    //
    /*!
    * \brief ���캯��
    */
    CUeMediator(CUeWrapperImpl *wrapper);

    /*!
    * \brief ��������
    */
    virtual ~CUeMediator();

  public:
    //
    //
    //
    /**
    * \brief ����UeRoute��UeGPS����ģ���Ľ���ɲο�UeRouteģ���IsPassing�ӿڻ�ø���ϸ����Ϣ
    *
    * \param parcelIdx parcel��Ψһ��ʶ��
    * \param linkIdx ָ��parcel��link��Ψһ��ʶ��
    */
    virtual bool IsPassing(long parcelIdx, long linkIdx);

    /**
    * \brief TODO:δʹ��
    */
    virtual short RenderingLayer();

    /**
    * \brief TODO:δʹ��
    */
    virtual void RenderingLayer(short curLayer);

    /*!
    * \brief �ж�UeRouteģ���Ƿ��ڹ滮״̬��
    * TODO:��������״̬�Ľӿڴ�δʹ�ã���ÿ�η��ض�Ϊfalse��
    */
    virtual bool IsPlanning();

    /*!
    * \brief ����UeRouteģ���Ƿ��ڹ滮״̬��
    * TODO:δʹ�õĽӿ�
    */
    virtual void IsPlanning(bool isPlanning);

    /*!
    * \brief ��ȡ��������Ψһ��ʶ����
    * ��Ҫ����UeRoute��UeMap����ģ���Ľ����ֹUeRouteģ���UeMapģ������������ο�UeMapģ���GetDistrictIdx��øýӿ���ϸ��Ϣ
    *
    * \param pos ��ͼ����
    */
    virtual int GetDistrictIdx(const CGeoPoint<long> &pos);

    /*!
    * \brief ��ȡ��ǰ��������������������(���ؼ�)��
    * 
    * \param[in] pos ��ͼ����
    * \param[in][out] distName ����������
    */
    virtual void GetDistrictName(const CGeoPoint<long> &pos, char *distName);

    
    /**
    * \brief ��ȡ��ǰ�滮��ʽ����·��״̬��
    */
    virtual unsigned char GetMultiMethodType();

    /**
    * \brief �Ƿ���ָ����״̬
    */
    virtual bool IsShowCompass();

    /*!
    * \brief �ж�GUI��״̬�Ƿ��ʺ�UeRouteģ������ض��Ĳ�����
    * ��Ҫ����UeRoute��UeGui����ģ���Ľ����ֹUeRouteģ���UeGuiģ������������ο�UeGuiģ���IsReadyForPlanning��øýӿ���ϸ��Ϣ
    */
    virtual bool IsReadyForPlanning();

    /*!
    * \brief ��������Hooks֮ǰ��Ҫ������hook����·��
    **/
    virtual void SetHooksPath(TCHAR* path);

    /*!
    * \brief ���ز�Ʒ����hook
    **/
    virtual void LoadProductActivationHook();

    /*!
    * \brief ע����ܼ���ϵ�к���
    */
    virtual bool RegisterActiveFunc(void *getuuid, void *checkIsActive, void *checkActiveID, void *saveActiveFile);

    /**
    * \brief ��ȡΨһʶ����
    */
    virtual unsigned long LsGetUUID(char *path,char *uuid);

    /**
    * \brief ��֤�Ƿ��Ѿ�����
    */
    virtual unsigned long LsCheckIsActive(char *path,char *uuid);

    /**
    * \brief ��֤�������Ƿ�Ϸ�
    */
    virtual unsigned long LsCheckActiveID(char *uuid,char* activeid);

    /**
    * \brief ��֤ͨ����,���漤���ļ�
    */
    virtual unsigned long LsSaveActiveFile(char *path,char *uuid,char* activeid);

    /*!
    * \brief ��������Hooks��
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���MakeHooks��øýӿ���ϸ��Ϣ
    */
    virtual void LoadHooks();

    /*!
    * \brief ��Ⱦ����ͼHook����    
    * \param scrExtent ��Ļ��������
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���RenderHook��øýӿ���ϸ��Ϣ
    */
    virtual void RenderHooks(const CGeoRect<short> &scrExtent);
    
    /*!
    * \brief ��Ⱦ����ͼHook����(�磺·�ڷŴ�ͼ��ӥ��ͼ)
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderSubViewHooks(const CGeoRect<short> &scrExtent);

    /*!
    * \brief ��Ⱦ������Hook��
    *
    *
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderLogonHooks(const CGeoRect<short> &scrExtent, short step = 0);

    /*!
    * \brief  ������ӦHooks��״̬���ػ档
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���Update��øýӿ���ϸ��Ϣ
    * 
    * \param type �������ͣ���ϸö�ٶ���鿴UpdateHookType
    * \param para �������ض�����(�����Ҫ)
    */
    virtual void UpdateHooks(short type, void *para = 0);

    /*!
    * \brief ��MapSettingHook��ȡ��ͼ��ʾ������á�
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���GetMapSettings��øýӿ���ϸ��Ϣ
    */
    virtual const ViewSettings &GetMapSettings();

    /*!
    * \brief �Ƿ�Ϊ��Ϣ��ʾ��
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���IsMsgBox��øýӿ���ϸ��Ϣ
    */
    virtual bool IsMsgBox();

    /*!
    * \brief �Ƿ�Ϊ��¼��ʾ��
    * ��Ҫ����UeMap��UeGui����ģ���Ľ����ֹUeMapģ���UeGuiģ������������ο�UeGuiģ���IsRecBox��øýӿ���ϸ��Ϣ
    */
    virtual bool IsRecBox();

    /**
    * \brief �жϵ�ǰ�����Ƿ�Ϊ��ͼ����
    */
    virtual bool IsMapHook();

    /**
    * \brief �ж��豸�ڴ�״̬
    *
    * \return �����ڴ��Ƿ����޵�״̬��trueΪ���ڴ档
    */
    virtual bool IsMemoryLimited();

    /**
    * \brief �����ڴ�״̬
    */
    virtual void SetMemoryStatus(bool isMemoryLimited);
  private:
    //
    short m_renderingLayer;

    //
    bool m_isPlanning;

    /// ��ʼ�ڴ�״̬
    bool m_memoryStatus;

    //
    CUeWrapperImpl *m_wrapperImpl;

    // ���ܼ���ӿ�
    typedef unsigned long (*LsGetUUIDFunc)(char *path,char *uuid);
    typedef unsigned long (*LsCheckIsActiveFunc)(char *path,char *uuid);
    typedef unsigned long (*LsCheckActiveIDFunc)(char *uuid,char* activeid);
    typedef unsigned long (*LsSaveActiveFileFunc)(char *path,char *uuid,char* activeid);
    LsGetUUIDFunc m_getuuid;
    LsCheckIsActiveFunc m_checkIsActive;
    LsCheckActiveIDFunc m_checkActiveID;
    LsSaveActiveFileFunc m_saveActiveFile;
  };
}
#endif
