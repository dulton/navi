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
#ifndef _UEFACADE_WRAPPERIMPL_H
#define _UEFACADE_WRAPPERIMPL_H

// Refer to EXPORT & IMPORT macro definition
#ifndef _UEFACADE_BASE_H
#include "uefacade.h"
#endif

// Refer to tstring etc basic definition
#ifndef _PORTABILITY_DEF_H
#include "portability.h"
#endif

// Refer to memory garbage
#ifndef _UEBASE_MEMGARBAGE_H
#include "uebase\garbage.h"
#endif

// Refer to mediator
#ifndef _UEBASE_MEDIATOR_H
#include "uebase\mediator.h"
#endif

// Refer to path basic functions
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

// Refer to geo index mechansim
#ifndef _UEINDEX_INDEX_H
#include "ueindex\geoindex.h"
#endif
using namespace UeIndex;

// Refer to road network definition
#ifndef _UEMODEL_ROADNETWORK_H
#include "uemodel\network.h"
#endif
using namespace UeModel;

// Refer to view definition
#ifndef _UEMAP_VIEW_H
#include "uemap\view.h"
#endif
using namespace UeMap;

// Refer to map match definition
#ifndef _UEGPS_MAPMATCH_H
#include "uegps\mapmatch.h"
#endif
using namespace UeGps;

// Refer to UeRoute definition
#ifndef _UEROUTE_ROUTE_H
#include "ueroute\route.h"
#endif
using namespace UeRoute;

// Refer to UeQuery definition
#ifndef _UEQUERY_QUERY_H
#include "uequery\query.h"
#endif
using namespace UeQuery;

// Refer to UeGui definition
#ifndef _UEGUI_GUI_H
#include "uegui\gui.h"
#endif
using namespace UeGui;

// Declare namespace
namespace UeFacade
{
  /*! \class CUeWrapperImpl
  * \brief IUeWrapper�ӿڵ�ʵ����
  */
  class UEFACADE_CLASS CUeWrapperImpl
  {
    /// Relatives
    friend class CUeMediator;

    /// The max length of current path for execute module
    const static int MAX_PATHLEN = 256;
    /// ϵͳ��������
    const static unsigned short MAX_PROGRESS = 10;

    /*! \enum UeSystemStatue
    * \brief Warning types
    */
    enum UeSystemStatus
    {
      USS_HAS_SD						= 0x0001,
      USS_NO_SD						= 0x0010,
      USS_POWER_NORMAL		= 0x0100,
      USS_POWER_CRITICAL		= 0x1000,
    };

  public:
    //
    // ����&����
    //
    /*!
    * \brief ���캯��
    */
    CUeWrapperImpl();

    /*!
    * \brief ��������
    */
    virtual ~CUeWrapperImpl();

  public:
    //
    // Basic methods for constructing one navigation solution
    //
    /*!
    * \brief ���ظ���ģ�����Դ����Ϊ��Ӧģ��ע��mediator����Դ��������
    *
    * \param oneSchema According to schema definition, we can load different modules or specify special behaviors of one module
    */
    virtual unsigned int Load(short oneSchema);

    /*!
    * \brief �ͷŸ���ģ�����Դ
    */
    virtual unsigned int UnLoad();

    /*!
    * \brief ��ȡָ��ģ�����ӿڣ����ģ����δ���أ������֮��
    *
    * \param ģ���Ӧ��ö��ֵ��ö�ٶ���鿴PackageDefinition
    */
    virtual void *GetModel(short type);

    /*!
    * \brief ������ͼ�Ĵ��ھ������С
    *
    * \param handle ���ھ��
    * \param width ���ڿ��
    * \param height ���ڸ߶�
    */
    virtual bool Attach(void *handle, int width, int height);

    /*!
    * \brief Ԥ�ȼ��ص�ͼ
    *
    * \param schema ���ص�ͼ�ķ�ʽ��ö�ٶ�����鿴LayerSchema��
    * ʾ����UeMap::LSH_Shape | UeMap::LSH_Index | LSH_Network | UeMap::LSH_RoutePlan | LSH_BackGround
    *
    * \param fileName shp�ļ���(�������)������Ϊ���ַ���
    * \param scaleLevel ��ͼ���ڱ����ߵȼ�
    * \param angle ��ͼ��ת�Ƕ�
    */
    virtual bool Prepare(short schema, const tstring &fileName, short scaleLevel = 1, double angle = 0.);

    /*!
    * \brief TODO: ������
    */
    virtual bool CreateIndex(short scaleLevels, int scaleGroups, const CGeoRect<double> &mapExtent, double gridWidth, double gridHeight);

    //
    //
    //
    /*!
    * \brief ��Ӧ�ػ�����
    */
    virtual void OnPaint();

    /*!
    * \brief ��Ӧ���ڴ�С�仯
    *
    * \param width �ı��Ĵ��ڿ��
    * \param height �ı��Ĵ��ڸ߶�
    */
    virtual void OnSize(int width, int height);

    /*!
    * \brief ��Ӧ������/��갴�²���
    *
    * \param scrPoint �������Ļ����
    */
    virtual void MouseDown(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��Ӧ����ƶ�����
    *
    * \param scrPoint ��Ļ����
    */
    virtual void MouseMove(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��Ӧ���ſ�����
    *
    * \param scrPoint ��Ļ����
    */
    virtual void MouseUp(CGeoPoint<short> &scrPoint);

    /*!
    * \brief ��ʱ���������
    */
    virtual void TimerProc();

    /*!
    * \brief ���д������
    */
    virtual void IdleProc();

    /*!
    * \brief ���SD��
    **/
    virtual bool DetectSDCard();

    /**
    * TODO: ������
    **/
    virtual bool DetectPowerStatus();

    /*!
    * \brief ע����ܺ���
    *
    * \param func ���ܺ����ĺ���ָ��
    */
    virtual bool RegisterDecryptFunc(void *func);

    /*!
    * \brief ע����ܼ���ϵ�к���
    */
    bool RegisterActiveFunc(void *getuuid, void *checkIsActive, void *checkActiveID, void *saveActiveFile);

  private:
    //
    //
    //
    /**
    *
    **/
    IRoadNetwork *LoadNetwork();

    /**
    *
    **/
    IView *LoadMap();

    /**
    *
    **/
    IMapMatch *LoadGps();

    /**
    *
    **/
    IRoute *LoadRoute();

    /**
    *
    **/
    IQuery *LoadQuery();

    /**
    *
    **/
    IGeoIndex *LoadIndex();

    /**
    *
    **/
    IGui *LoadGui();

    /**
    *
    **/
    bool DoWarning();

  protected:
    //
    unsigned char m_schema;

    //
    CMemoryGarbage *m_garbage;
    CMediator *m_mediator;

    // Package definitions
    tstring m_modulePath;
    IRoadNetwork *m_network;
    IView *m_view;
    IMapMatch *m_gps;
    IRoute *m_route;
    IQuery *m_query;
    IGeoIndex *m_index;
    IGui *m_gui;

    //
    const CPathBasic &m_pathBasic;

    //
    unsigned short m_status;
    ScreenLayout m_scrLayout;
    void *m_wndHandle;
  };
}
#endif