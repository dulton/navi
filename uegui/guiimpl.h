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
#ifndef _UEGUI_GUIIMPL_H
#define _UEGUI_GUIIMPL_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to IView definition in order to get current hook
#ifndef _UEMAP_VIEW_H
#include "uemap\view.h"
#endif
using namespace UeMap;

// Refer to UeBase packge for ViewSettings
#ifndef _UEBASE_UESETTINGS_H
#include "uebase\uesettings.h"
#endif
using namespace UeBase;

// Declare namespace 
namespace UeGui
{
  /**
  * \brief IGui�ӿڵľ���ʵ����
  */
  class UEGUI_CLASS CGuiImpl
  {
    // Relatives
    friend class IGui;

  public:
    /**
    * \brief ���캯��
    */
    CGuiImpl();

    /**
    * \brief ��������
    */
    virtual ~CGuiImpl();

  public:
    /**
    * ��ʱ��
    **/
    void Timer();

    /*!
    * \brief  ������ӦHooks��״̬���ػ�
    *
    * \param type �������ͣ���ϸö�ٶ���鿴UpdateHookType
    * \param para �������ض�����(�����Ҫ)
    */
    virtual void Update(short type, void *para);

    /*!
    * \brief ��������Hooks֮ǰ��Ҫ������hook����·��
    **/
    virtual void SetHooksPath(TCHAR* path);

    /*!
    * \brief ����Դ�ļ��й�����Ʒ����hook
    */
    virtual void MakeProductActivationHook();

    /*!
    * \brief ����Դ�ļ��й�������Hooks�Ľ���Ԫ��
    */
    virtual void MakeHooks();
    
    /*!
    * \brief ���ý�����������    
    */
    virtual void SetMaxLogonProgress(unsigned short maxProgress);

    /*!
    * \brief ���ƽ�����
    *
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderLogonHook(const CGeoRect<short> &scrExtent, short step = 0);

    /*!
    * \brief ���Ƶ�ǰHook
    *
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderHook(const CGeoRect<short> &scrExtent);

    /*!
    * \brief ��Ⱦ����ͼHook����(�磺·�ڷŴ�ͼ��ӥ��ͼ)
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderSubViewHooks(const CGeoRect<short> &scrExtent);

    /*!
    * \brief �ж�GUI��״̬�Ƿ��ʺ�UeRouteģ������ض��Ĳ�����
    */
    virtual bool IsReadyForPlanning();

    /*!
    * \brief ��ȡ��ǰ��������������������(���ؼ�)��
    * 
    * \param[in] pos ��ͼ����
    * \param[in][out] distName ����������
    */
    virtual bool GetDistrictName(const CGeoPoint<long> &pos, char *distName);

    /*!
    * \brief �ж�GUI�Ƿ��ڵ���ʱ״̬
    */
    virtual bool IsCountDown();

    /**
    * \brief ��ʼ����
    */
    virtual void DoRouteGuidance();

    /*!
    * \brief �ж�GUI�Ƿ���ָ����״̬
    */
    bool IsShowCompass();

    /*!
    * \brief ��ȡ��ǰ�滮��ʽ
    */
    unsigned char GetMultiMethodType();

    /*!
    * \brief ��MapSettingHook��ȡ��ͼ��ʾ������á�
    */
    virtual const ViewSettings &GetMapSettings();

    /*!
    * \brief �ж��Ƿ�Ϊ��Ϣ��ʾ��
    */
    virtual bool IsMsgBox();

    /*!
    * \brief �ж��Ƿ�Ϊ��¼��Ϣ��
    */
    virtual bool IsRecBox();

    /**
    * \brief �жϵ�ǰ�����Ƿ�Ϊ��ͼ����
    */
    virtual bool IsMapHook();

#if __FOR_FPC__
    /**
    * 
    */
    virtual bool IsFPC();

    /**
    * 
    */
    virtual void SetCapScale(int scale);
#endif
  private:
    /**
    * \brief ������Ϣ�Ի���
    */
    void UpdateMessageDialogeHook(short type, void *para);

    /**
    * \brief ����Hook,ע�⣺�÷����ڲ�ʹ�������ڴ棬��Ҫ�ⲿ�����ڴ��ͷ�
    */
    CViewHook *LoadHook(short hookType);
  private:
    //
    IView *m_view;
  };
}

#endif