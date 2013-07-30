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
#ifndef _UEGUI_GUI_H
#define _UEGUI_GUI_H

// Refer to EXPORT & IMPORT macroes
#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

// Refer to basic definition
#ifndef _UEGUI_GUIBASIC_H
#include "guibasic.h"
#endif

// Refer to its parent CObserver
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif

// Refer to UeBase packge for ViewSettings
#ifndef _UEBASE_UESETTINGS_H
#include "uebase\uesettings.h"
#endif

// Refer to memory mediator for uniform memory management
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif
using namespace UeBase;

// Declare namespace
namespace UeGui
{
  // Forward classes
  class CGuiImpl;

  /**
  * \brief UeGuiģ�����ӿڶ���
  */
  class UEGUI_CLASS IGui : public CObserver
  {
  public:
    /**
    * \brief ���캯��
    */
    IGui(CGuiImpl *oneImpl);

  private:
    /**
    * Only be as a singleton
    */
    ~IGui();

  public:
    //
    // Methods for singleton
    //
    /**
    * \brief ���ض�̬�Ⲣȡ��IGui�ӿ�
    */
    static IGui *GetGui();

    /**
    * \brief ȡ��IGui�ӿ�
    */
    static IGui *GetGui(CGuiImpl *oneImpl);

    /**
    * \brief �ͷ���Դ
    */
    void Delete();

    /*!
    * \brief ��������Hooks֮ǰ��Ҫ������hook����·��
    **/
    void SetHooksPath(TCHAR* path);

    /*!
    * \brief ����Դ�ļ��й�������Hooks�Ľ���Ԫ��
    */
    void MakeProductActivationHook();

    /*!
    * \brief ����Դ�ļ��й�������Hooks�Ľ���Ԫ��
    */
    void MakeHooks();

    /*!
    * \brief ��Ⱦ����ͼHook����
    * \param scrExtent ��Ļ��������
    */
    void RenderHook(const CGeoRect<short> &scrExtent);

    /*!
    * \brief ��Ⱦ����ͼHook����(�磺·�ڷŴ�ͼ��ӥ��ͼ)
    * \param scrExtent ��Ļ��������
    */
    void RenderSubViewHooks(const CGeoRect<short> &scrExtent);

    /*!
    * \brief ���ý�����������    
    */
    void SetMaxLogonProgress(unsigned short maxProgress);

    /*!
    * \brief ���ƽ�����Hook
    *
    * \param scrExtent ��Ļ��������
    */
    void RenderLogonHook(const CGeoRect<short> &scrExtent, short step = 0);
    //
    // Methods for working with other collegues
    //

    /**
    * ��ʱ��
    **/
    void Timer();

    /*!
    * \brief  ������ӦHooks��״̬���ػ�
    *
    * \detail As an observer, it maybe directly notified by its subjects like UeGps & UeRoute packages following
    * the type convention
    *
    * \param type �������ͣ���ϸö�ٶ���鿴UpdateHookType
    * \param para �������ض�����(�����Ҫ)
    */
    void Update(short type = 0, void *para = 0);

    /*!
    * \brief �ж�GUI��״̬�Ƿ��ʺ�UeRouteģ������ض��Ĳ�����
    */
    bool IsReadyForPlanning();

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
    bool IsCountDown();

    /**
    * \brief ��ʼ����
    */
    void DoRouteGuidance();

    /*!
    * \brief �ж�GUI�Ƿ��ڵ���ʱ״̬
    */
    bool IsShowCompass();

    /*!
    * \brief ��ȡ��ǰ�滮��ʽ
    */
    unsigned char GetMultiMethodType();

    /*!
    * \brief �ж��Ƿ�Ϊ��Ϣ��ʾ��
    */
    bool IsMsgBox();

    /*!
    * \brief �ж��Ƿ�Ϊ��¼��Ϣ��
    */
    bool IsRecBox();

    /**
    * \brief �жϵ�ǰ�����Ƿ�Ϊ��ͼ����
    */
    virtual bool IsMapHook();

#if __FOR_FPC__
    /**
    * 
    */
    bool IsFPC();

    /**
    * 
    */
    void SetCapScale(int scale);
#endif
    /*!
    * \brief ��MapSettingHook��ȡ��ͼ��ʾ������á�
    */
    const ViewSettings &GetMapSettings();

    //
    //
    //
    /**
    * \brief ע����Դ������ 
    */
    void RegisterGarbage(CMemoryGarbage *garbage);

    /**
    * \brief �����Դ������
    */
    CMemoryGarbage *GetGarbage();

    /**
    * \brief ע���н��� 
    */
    void RegisterMediator(CMediator *mediator);

    /**
    * \brief ȡ���н���
    */
    CMediator *GetMediator();

  private:
    /// one view implementation against different OS(s)
    CGuiImpl *m_guiImpl;

    /// Memory collector working with other packages and
    /// mediator decoupling the relationship among different packages
    CMemoryGarbage *m_garbage;

    //
    CMediator *m_mediator;

    /// View as singletion
    static IGui *m_gui;
  };
}

#endif