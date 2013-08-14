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
#ifndef _UEMAP_VIEWIMPL_H
#define _UEMAP_VIEWIMPL_H

//
// Refer to UeMap package
//
// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMAP_BASE_H
#include "uemap.h"
#endif

// Refer to view basic definitions
#ifndef _UEMAP_VIEWBASIC_H
#include "viewbasic.h"
#endif

// Refer to view hook
#ifndef _UEMAP_VIEWHOOK_H
#include "viewhook.h"
#endif

// Refer to how to load a dynamic library 
#ifndef _UEBASE_DYNLIB_H
#include "uebase\dynlib.h"
#endif

// Refer to own-specific picture definition
#ifndef _UEBASE_UEPICTURE_H
#include "uebase\uepicture.h"
#endif

// Refer to path basic functions
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

// Refer to file basic functions
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

// Refer to string basic functions
#ifndef _UEBASE_STRINGBASIC_H
#include "uebase\stringbasic.h"
#endif
using namespace UeBase;

// Compiler setting
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// Declare namespace
namespace UeMap
{
  // Forward classes
  class CViewState;
  class CViewDC;
  class CViewCommand;
  class CSelectCommand;
  class CPanCommand;
  class CTimerCommand;
  class CViewLayer;

  ////////////////////////////////////////////////////////////////////////////////
  //
  class UEMAP_CLASS CViewImpl
  {
    // Relatives
    friend class IView;

    friend class CViewCommand;
    friend class CSelectCommand;
    friend class CPanCommand;
    friend class CTimerCommand;

    friend class CViewState;
    friend class CAGGView;
    friend class CImageView;
    friend class CGuidanceView;
    friend class CGuiView;

    friend class CViewLayer;
    friend class CGroundLayer;
    friend class CNetworkLayer;
    friend class CPlanLayer;
    //����·���Զ����������ߵĸ�����
    class CCrossAssist
    {
    public:
      static void AdjustScaleWhenCross(CViewState *curView, GuidanceStatus &dirInfo, double angle);
    private:
      //��¼��һ�ε�ת��order
      static short m_lastSndOrder1;
      static short m_lastSndOrder2;
      static short m_lastSndOrder3;
    };

  public:
    // State Vector, namely, it maybe need to render multiple view state at once
    typedef std::vector<CViewState*> ViewVector;

    // Name aliases for memory DCs
    typedef std::map<unsigned int, CViewDC*> DcMap;
    typedef DcMap::iterator dc_itr;
    typedef DcMap::const_iterator dc_citr;

    // Name aliases for view commands
    typedef std::map<short, CViewCommand*> CmdMap;
    typedef CmdMap::iterator cmd_itr;
    typedef CmdMap::const_iterator cmd_citr;

    // Display hooks
    typedef std::map<short, CViewHook*> HookMap;
    typedef HookMap::iterator hook_itr;
    typedef HookMap::const_iterator hook_citr;

    // Rendered layers
    typedef std::vector<CViewLayer*> LayerVector;
    typedef std::map<int, LayerVector> LayerMap;
    typedef LayerMap::iterator layer_itr;
    typedef LayerMap::const_iterator layer_citr;

    // Different types of nav picture
    typedef std::map<short, CUePicture*> PictureMap;
    typedef PictureMap::iterator pic_itr;
    typedef PictureMap::const_iterator pic_citr;

    // �����Ⱦģ����ʹ�õ�ͼƬ��Դ
    typedef std::map<short, short> IconMap;
  protected:
    //
    // Constructor & deconstrucor
    //
    /**
    * This object should only be created by its interface definition, namely IView
    */
    CViewImpl();

    /**
    *
    */
    virtual ~CViewImpl();

  public:
    //
    // Methods for outside specifiation
    //
    /**
    *
    */
    virtual void *GetWndHandle();

    /**
    *
    */
    virtual void *GetResHandle();

    /**
    *
    */
    virtual bool Attach(void *oneWnd, ScreenLayout &scrLayout);

    /**
    *
    */
    virtual void Detach();

    /**
    *
    **/
    virtual void SwitchScrMode();

    /**
    *
    **/
    virtual short GetScrMode();

    //
    // Methods for different view states's schema
    //
    /**
    *
    */
    virtual void NextState();

    /**
    *
    **/
    virtual void SetState(short type);

    /**
    *
    */
    virtual CViewState *GetState(short type);

    /**
    *
    */
    virtual void EraseState(short type);

    /**
    *
    */
    virtual CViewState *MainState();

    /**
    * ������Ļ���ȡ��ǰ�������Ǹ���ͼ��Χ��
    **/
    virtual unsigned int GetSelectedViewType(const CGeoPoint<short> &scrPoint);

    /**
    *
    **/
    virtual bool FocusOn(short type);

    /**
    * ���ݵ���ȷ����ǰѡȡ�����ĸ���ͼ���Ѹ���ͼ�ŵ�������ǰ�棬�����ص�ǰѡ�����ͼ����
    */
    virtual unsigned int FocusOn(const CGeoPoint<short> &scrPoint);

    /**
    *
    **/
    virtual void SetViewPort(CViewState *curView, const MapLayout &mapLayout, short scaleLevel, short schema);

    /**
    *
    */
    virtual short GetLayoutSchema()
    {
      return m_layoutSchema;
    }

    /**
    *
    */
    virtual void SetLayoutSchema(short schema)
    {
      m_layoutSchema = schema;
    }

    //
    // Methods for mapping between screen and map
    //
    /**
    *
    **/
    virtual void SetScrLayout(ScreenLayout &layout, short type = VT_Unknown);

    /**
    *
    **/
    virtual const ScreenLayout &GetScrLayout(short type = VT_Unknown);

    /**
    *
    **/
    virtual void SetMapLayout(const MapLayout &layout, short type = VT_Unknown);

    /**
    *
    **/
    virtual const MapLayout &GetMapLayout(short type = VT_Unknown);

    /**
    *
    */
    virtual void GetScale(short &level, int &scale, short type = VT_Unknown);
    virtual int GetMaxScale();
    /**
    *
    **/
    virtual void SetScale(short level, int scale, short type = VT_Unknown);

    /**
    *
    **/
    virtual void EraseScale(short level, short type = VT_Unknown);

    /**
    *
    */
    virtual bool Scr2Map(const CGeoPoint<short> &scrPoint, CGeoPoint<long> &mapPoint, short type = VT_Unknown);

    /**
    *
    */
    virtual bool Map2Scr(CGeoPoint<long> &mapPoint, CGeoPoint<short> &scrPoint, short type = VT_Unknown);

    /**
    *
    **/
    virtual bool GetScreenCenter(CGeoPoint<long> &mapPt);

    /**
    * 
    */
    void RenderSidePicture(bool isDraw, short picCode = -1, short picType = -1, short arrowCode = -1, void *wndHandle = 0);

    //
    // Methods for map operation
    //
    /**
    *
    */
    virtual void SwitchTo(short scaleLevel, double angle, short type = VT_Unknown);

    /**
    *
    */
    virtual void SwitchTo(const CGeoRect<long> &extent);

    /**
    *
    */
    virtual void ZoomIn();

    /**
    *
    */
    virtual void ZoomOut();

    /**
    *
    **/
    virtual void Rotate(double step, bool isDirect = true);

    /**
    *
    **/
    virtual void Rotating(double step, double from, double to);

    /**
    *
    **/
    virtual void Zooming(bool isZoomIn);

    /**
    *
    **/
    virtual void Zooming(short start, short end, short step);

    /**
    *
    **/
    virtual void Transforming(double diff, bool isOnce = false);

    /**
    *
    **/
    virtual void Transforming(double diff, double to);

    /**
    * �ƶ�����Ļ��ָ���ĵ㣬ˢ�µ�ͼ����ȡ��ѡ�����Ϣ��
    */
    virtual bool Pick(const CGeoPoint<short> &scrPoint, CMemVector &objects, bool isRendered = false);

    /**
    *
    */
    virtual void RenderSelected();

    /**
    *
    **/
    virtual void GetPickPos(CGeoPoint<long> &pickPos);
    virtual void GetPickName(char *pickName);

    /**
    *
    **/
    virtual void SetPickPos(const CGeoPoint<long> &pickPos, CGeoPoint<short> &scrPoint);
    /**
    *
    **/
    virtual void SetPickPos_NoRefresh(const CGeoPoint<long> &pickPos, CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual CViewCommand* GetCommand(short type);

    /**
    * ��ȡ��ǰ��������λ������
    **/
    virtual const GpsCar &GetGpsCar();

    /**
    * ���õ�ǰ��������λ������
    **/
    virtual void SetGpsCar(const GpsCar &carInfo);

    /**
    * ��ȡ��ǰGPS����λ������
    **/
    virtual const GpsCar &GetGpsPosInfo();

    /**
    * ���õ�ǰGPS����λ������
    **/
    virtual void SetGpsPosInfo(const GpsCar &gpsInfo);

    /**
    * 
    */
    void SetPlanLogInfo(tstring &version, long sampleID);

    /**
    * 
    */
    void GetPlanLogInfo(tstring &version, long &sampleID);

    /**
    * 
    */
    bool IsDrawPlanLayer();

    /**
    * 
    */
    void SetDrawPlanLayer(bool isDraw);

    //
    //
    //
    /**
    * 
    */
    void SetRenderSetting(const RenderSettings &settings);

    /**
    * 
    */
    void GetRenderSetting(RenderSettings &settings);

    //
    // Standard methods for OS' APIs
    //
    /**
    *
    */
    virtual bool MouseDown(const CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual bool MouseMove(const CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual bool MouseUp(const CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual void Refresh();

    /**
    *
    */
    virtual void RefreshUI(short type);

    /**
    *
    */
    virtual bool UpFlash(const CGeoPoint<short> &start, const CGeoPoint<short> &end) = 0;

    /**
    *
    */
    virtual bool PanFlash(const CGeoPoint<short> &start, const CGeoPoint<short> &end) = 0;

    /**
    *
    */
    virtual void OnPaint() = 0;

    /**
    *
    **/
    virtual void SetIdleOP(unsigned int operations);

    /**
    *
    **/
    virtual unsigned int GetIdleOP(); 

    /**
    *
    **/
    virtual void OnIdle();

    /**
    * Deprecated function, here it only give outside warning that u shouldn't igonre this message
    */
    virtual void EraseBkGnd() = 0;

    /**
    *
    **/
    virtual void ExcludeRegions(void *dc, short curType, CGeoRect<short> &excludeExtent);

    /**
    *
    **/
    virtual void IsReadyForOperation(bool isReady)
    {
      m_isReadyForOperation = isReady;
    }

    //
    // Methods for data organization
    //
    /**
    *
    */
    unsigned long GetMapSchema();

    /**
    *
    */
    void SetMapSchema(unsigned long schema);

    /**
    *
    */
    virtual bool LoadMap(unsigned long schema, const tstring &file, short scaleLevel = 0, double angle = 0);

    /**
    *
    */
    virtual bool AddLayer(int scale, LayerVector &oneLayer);

    /**
    *
    */
    virtual bool AddLayer(int scale, CViewLayer *oneLayer);

    /**
    *
    */
    virtual bool RemoveLayer(int scale);

    /*
    *
    **/
    virtual CViewLayer *GetLayer(int scale, int type);
    
    /**
    * \brief ��ȡ��Ӧ�������µ�layer
    * \param ������
    * \param index
    */
    CViewLayer *GetLayer(int scale, unsigned int index);

    /**
    *
    */
    virtual bool RemoveLayer(int scale, const tstring &layerName);

    /**
    *
    */
    virtual void SortLayer();

    /**
    *
    **/
    virtual bool SetUePicture(short type, CUePicture *navPicture);

    /**
    *
    **/
    virtual const CUePicture *GetUePicture(short type);

    //
    // Methods for letting outside have chance to extend view's functionalities
    //
    /**
    *
    */
    virtual bool AddDC(unsigned int type, CViewDC *oneDC = 0) = 0;

    /**
    *
    */
    virtual CViewDC *GetDC(unsigned int type);

    /**
    *
    **/
    virtual void EraseDC(unsigned int type);

    /**
    *
    */
    virtual bool AddHook(short type, CViewHook *oneHook);

    /**
    *
    */
    virtual CViewHook *GetHook(short type);

    //
    // Methods for its parent CObsever and communication with other collegues
    //
    /**
    *
    */
    virtual void Update(short type);

    /**
    * ���½���������
    */
    virtual void UpdateProgress(short step = 0);

    /**
    * \brief ��ͼ���ĵ��Ƿ��Ѿ����ƶ�
    */
    bool HasMovedMapCenter();

    /**
    * \brief ���õ�ͼ���ĵ㱻�ƶ���־
    */
    void SetMapCenterMoveFlag(bool hasMoved);

    /**
    * �����Գ�ͼ��
    */
    void SetCarIcon(short carIcon);

    /**
    * ����3D�Գ�ͼ��
    */
    void Set3DCarIcon(unsigned short carIcon);

    /**
    * ��ȡ3D�Գ�ͼ��
    */
    unsigned short Get3DCarIcon();

    /**
    * ��ȡ�Գ�ͼ��
    */
    short GetCarIcon();

    /**
    * ���÷�����������Ļ����ʾ��λ����Ϣ
    * param scrPoint ����������ʾ����Ļ����λ�� 
    */
    void SetCompassIconPos(const CGeoPoint<short> &scrPoint);

    /**
    * ��ȡ������������Ļ����ʾ��λ����Ϣ
    * param scrPoint ���ط���������ʾ����Ļ����λ�� 
    */
    void GetCompassIconPos(CGeoPoint<short> &scrPoint);

    /**
    * ���ó�����Ϣ����Ļ����ʾ��λ����Ϣ
    * param scrPoint ������Ϣ��ʾ����Ļ����λ�� 
    */
    void SetLanePos(CGeoPoint<short> &scrPoint, short width, short height);

    /**
    * ��ȡ������Ϣ����Ļ����ʾ��λ����Ϣ
    * param scrPoint ������Ϣ��ʾ����Ļ����λ�� 
    */
    void GetLanePos(CGeoPoint<short> &scrPoint, short &width, short &height);

    /**
    * param ��ǰ�Ƿ���Ҫ��Ⱦ·�ڷŴ�ͼ
    */
    bool IsNeedRenderGuidanceView();

    /**
    * param ·�ڷŴ�ͼ�Ƿ���ʾ
    */
    bool IsGuidanceViewShown();

    /**
    * param �ر�·�ڷŴ�ͼ
    */
    void CloseGuidanceView();

    /**
    * param ��ʾ·�ڷŴ�ͼ
    */
    void ShowGuidanceView();

    /**
    * \brief ͼ���Ƿ����仯
    */
    bool IsMapLayoutChange();

    /**
    * ���õ�ǰ��ͼ�Ĳ���ģʽ
    */
    void SetViewOpeMode(ViewOpeMode opeMode, ViewType type = VT_Unknown);

    /**
    * ��ȡ��ǰ��ͼ�Ĳ���ģʽ
    */
    ViewOpeMode GetViewOpeMode(ViewType type = VT_Unknown);

    /**
    * ��ӵ�ͼ��ԴͼƬ�ӿ�
    */
    bool AddViewIcon(ViewIconType iconType, short icon);

    /**
    * ��ȡ��ͼ��ԴͼƬ�ӿ�
    */
    short GetViewIcon(ViewIconType iconType);

    /**
    * ��������յ��λ���Զ����ŵ�ͼ�����ʱ�����
    * \param isLock ����ʱ�Ƿ��������Զ��Ŵ�
    */
    bool AutoScallingMap(bool isLock = false);

    /**
    * ����·�ڷŴ�                                                                
    */
    void UnLockScalling();
    /**
    * \brief �����ӦscaleLevel�µ�Layer�ĸ���
    */
    unsigned int GetLayerSize(short scaleLevel);

    void SetEagleState(bool isEagleOn);

    CViewState *GetMapView();
  protected:
    /**
    * ��ʼ��ʾϵͳ���ؽ���
    */
    void StartProgress();

    void DrawGui();

  private:
    /**
    *
    */
    bool SetupCommands();

    /**
    *
    **/
    bool LoadImages(TCHAR* path);

    /**
    *
    **/
    void RedrawMapHook();

    //
    // For PC version, namely UeTool
    //
    /**
    *
    **/
    bool LoadIndexLayer(const tstring &file, short scaleLevel, double angle);

    /**
    *
    **/
    bool LoadShapeLayer(const tstring &file, short scaleLevel, double angle);

    /**
    *
    **/
    void ZoomInCross(short type, CViewState *curView, GuidanceStatus &dirInfo, unsigned int rt);

    /**
    *
    **/
    CViewState *ZoomInFull(CViewState *curView, GuidanceStatus &dirInfo);
    //**
    //* ����Ƿ�����ʵ·�ڷŴ�ͼ��ԴͼƬ
    //**/
    bool HaveRealCrossPic();

    //**
    //* ����Ƿ�������·�ڷŴ�ͼ��ԴͼƬ
    //**/
    bool HaveVirtualCrossPic();

    /**
    *   ��̽�Ƿ���·�ڷŴ�ͼ��Դ���������������ʾ·�ڷŴ�ͼ��û�����������
    **/
    bool EnableToSplit();

    /**
    *   �Ƿ�滮��·�߶�����Ļ��
    **/
    bool IsAllPlanLineInScreen(IRoute *route, CViewState *view);
    /**
    *   ��ȡ�滮·�ߵ�����
    **/
    unsigned int GetPlanMethodType();

    bool IsRoundAbout(GuidanceStatus &dirInfo);

    bool GetCurRoundAboutCenter(GuidanceStatus &dirInfo, CGeoPoint<long> &pos);
    /**
    * \brief ��ʼ��ScreenLayout
    * \param scrLayout ��Ļ�ֱ���
    **/
    void InitSrcLayout(ScreenLayout &scrLayout);  
    /**
    * \brief ���÷ֱ���
    **/
    void InitResolutionRatio();
    /**
    * \brief ��ʼ����ͼ״̬
    **/
    void InitState();
    /**
    * \brief �Ƿ���Ҫ��ʾӥ��ͼ
    */
    bool IsNeedShowEagle();

    void EraseGuidanceView();

    void InitGuidanceView(const CViewState *curView);

    ScreenLayout GetHalfScreenLayout(bool isPerspective);

    void ShowEagle(CViewState *curView, const short renderType);

    void ChangeViewPort(CViewState *curView, const short renderType);

    void SetFullViewPort(CViewState *curView);

    
    void InitGuiState();
  protected:
    // Belonged window
    void *m_wnd;
    // Screen layout
    ScreenLayout m_scrLayout;
    // Map layout
    MapLayout m_mapLayout;
    // Picture categories
    PictureMap m_pictures;

    // Current view state
    // Note: The first one of those views would be the main view port by default which gives responses to 
    // outside's events, for example, pick etc. Of course, u can move one of other elements to the first position
    // during the running time
    unsigned short m_vType;
    ViewVector m_views;
    // Memory DCs corresponding to different view states
    DcMap m_memDCs;

    // Operation commands
    CmdMap m_commands;

    // Display hooks
    HookMap m_hooks;

    // Rendered layers
    LayerMap m_layers;
    // Current car information
    //�Գ�ͼ��λ��
    GpsCar m_carInfo;
    //�����ź�λ��
    GpsCar m_gpsInfo;

    //��ǰ�Գ�ͼ��
    short m_carIcon;

    //��ǰ3D�Գ�ͼ��
    unsigned short m_3DCarIcon;

    // Handle to resource Dll
    CDynamicLibrary m_resModule;

    // Layout schema
    short m_layoutSchema;

    // Idle operation types
    unsigned int m_idleOP;

    // Schema of how to load maps
    unsigned long m_mapSchema;

    // In order to kick out repeated WM_XXX messages for quick response
    bool m_isReadyForOperation;

    // What canvas will be used
    // Note:
    // When constructing this object, namely, CViewImpl, it seems the static variables specified by
    // CViewCanvas seems not be initialized yet. so, it would cause the singletion of CViewCanvas can't 
    // play role
    // ...
    // CViewCanvas &m_canvas;

    // Path & file basic
    const CPathBasic &m_pathBasic;
    const CFileBasic &m_fileBasic;
    const CStringBasic &m_stringBasic;

    // Side Picture
    short m_sidePicCode;
    short m_sidePicType;
    short m_sideArrowCode;
    bool m_isDrawSidePic;
    void *m_picWndHandle;

    //
    tstring m_planLogVersion;
    long m_sampleID;

    bool m_isDrawPlanLayer;
    //
    RenderSettings m_renderSettings;
    //��ʶ��ͼ���ĵ��Ƿ��Ѿ����ƶ�
    bool m_isHasMoved;    
    //ָ���뱳��ͼ��
    short m_compassIcon;
    //ָ����ָ��ͼ��
    short m_compassIndicatorIcon;
    //ָ����λ��
    CGeoPoint<short> m_compassPoint;
    //��ǰϵͳ�Ƿ񼤻�
    bool m_isProductActivation;
    //�Ƿ�������ʾ·�ڷŴ�ͼ������û��Լ��ر���·�ڷŴ�ͼ��
    //��ǰ·�ڷŴ�ͼ������ʾ��ֱ����һ��·�ڷŴ�ͼʱ��������ʾ
    bool m_needShowGuidanceView;
    //�Ƿ���Ҫ��Ⱦ·�ڷŴ�ͼ
    bool m_needRenderGuidanceView;
    //����ͼ�ꡢ
    short m_bubbleIcon;
    //������Ϣ����Ļ�ϵ�λ��
    CGeoPoint<short> m_lanePosInfo;
    //������Ϣ�Ŀ��
    short m_laneWidth;
    //������Ϣ�ĸ߶�
    short m_laneHeight;
    //
    short m_overViewScale;
  private:
    //ͼ���Ƿ�仯
    bool m_isMapLayoutChange;
    //���ͼƬ��Դ
    IconMap m_iconMap;
    //����·���������Զ��Ŵ�
    bool m_isScallingMapLock;
    //��ͼ����
    UeBase::ViewSettings m_viewSettings;
    //ӥ��ͼ״̬�Ƿ��
    bool m_isEagleOn;

    MapLayout m_eagleLayout;

    CViewState *m_guiView;
  };
}

#endif
