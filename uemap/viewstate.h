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
#ifndef _UEMAP_VIEWSTATE_H
#define _UEMAP_VIEWSTATE_H

/// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMAP_BASE_H
#include "uemap.h"
#endif

/// Refer to basic definition like ScreenLayout etc
#ifndef _UEMAP_VIEWBASIC_H
#include "viewbasic.h"
#endif

/// Refer to mapping formular
#ifndef _UEMAP_VIEWMAPPING_H
#include "viewmapping.h"
#endif

/// Refer to NavBase package
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif

///
#ifndef _UEBASE_CLIPTOOL_H
#include "UeBase\cliptool.h"
#endif

/// Refer to path basic functions
#ifndef _UEBASE_PATHBASIC_H
#include "uebase\pathbasic.h"
#endif

/// Refer to file basic functions
#ifndef _UEBASE_FILEBASIC_H
#include "uebase\filebasic.h"
#endif

#include "uebase\dbglogger.h"

using namespace UeBase;

/// Declare namespace 
namespace UeMap
{
  /// Forward classes
  class CViewImpl;
  class CViewDC;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  class UEMAP_CLASS CViewState
  {
    /// Relatives
    friend class CNetworkLayer;
    friend class CGroundLayer;
    friend class CPlanLayer;
    friend class CShpLayer;
    friend class CIndexLayer;
    friend class CPlanLogLayer;
    friend class CHistoryPlanLayer;
#if __FOR_FPC__
    friend class CFPCLayer;
#endif

    friend class CViewImpl;
    friend class CWinViewImpl;

    friend class CViewCommand;
    friend class CPanCommand;
    friend class CSelectCommand;
    friend class CTimerCommand;

    friend class CViewCanvas;
    friend class CAGGCanvas;

    friend class CAGGView;
    friend class CImageView;
    friend class CGuidanceView;

    // UeGui package
    friend class CMapHook;
#if __FOR_FPC__
    friend class CCapHook;
#endif

    // Render which layers
    enum RenderingStyle
    {
      RS_Raster,		// Render those geometries in rough way
      RS_All,			// Render those geometries in detailed way
      RS_Existed,		// Directly use last geometry set
      RS_Clipped,
    };

    // Scale level
    typedef std::map<short, int> ScaleLevel;

  protected:
    //
    //
    //
    /**
    *
    */
    CViewState(unsigned short type, bool isLand, CViewImpl *oneView);

    /**
    *
    */
    virtual ~CViewState();

  public:
    //
    // Methods for DC operation belonging to one view state
    //
    /**
    * Note: 
    * Currently this type includes definitions of view types(gui/main/guidance etc) and view 
    * status(heading/north/prespective etc)
    **/
    virtual short GetType()
    {
      return m_type;
    }

    /**
    * 
    */
    virtual CViewDC *AllocateDC();

    /**
    *
    */
    virtual CViewDC *GetDC();

    /**
    *
    */
    virtual bool MouseDown(const CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual bool MouseUp(const CGeoPoint<short> &scrPoint)
    {
      // TODO:
      // ...
      return false;
    }

    /**
    *
    */
    virtual bool MouseMove(const CGeoPoint<short> &scrPoint)
    {
      // TODO:
      // ...
      return false;
    }

    //
    // Methods for map projection belonging to this view state
    //
    /**
    *
    **/
    virtual void SetScrLayout(const ScreenLayout &layout);

    /**
    *
    **/
    virtual const ScreenLayout &GetScrLayout();

    /**
    * ����layout�е�ͼ���Ľ���ƫ�ƴ���ֱ��ʹ�����õ�ֵ
    **/
    virtual void SetMapLayout(const MapLayout &layout);

    /**
    * ��layout�е�ͼ���Ľ���ƫ�ƴ���
    **/
    virtual void SetMapLayoutEx(const MapLayout &layout);

    /**
    * ��ȡ��Ļ��Χ
    **/
    virtual const MapLayout &GetMapLayout();

    /**
    * Note:
    * scrExtent is empty means it will adopt the whole extent of this view state
    **/
    virtual void GetMapExtent(CGeoRect<short> &scrExtent, CGeoRect<long> &mapExtent);

    /**
    *
    */
    virtual bool Scr2Map(const CGeoPoint<short> &scrPoint, CGeoPoint<long> &mapPoint);

    /**
    *
    */
    virtual bool Map2Scr(CGeoPoint<long> &mapPoint, CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual bool Map2Scr(CGeoPoint<long> &mapPoint, CGeoPoint<long> &scrPoint);

    /**
    * For perspective transformation
    */
    virtual void Make3D(CGeoPoint<short> &scrPoint, bool isRect = true);

    /**
    *
    **/
    virtual bool Is3D()
    {
      return false;
    }

    /**
    *
    */
    virtual bool CheckCoords(const CGeoPoint<short> &onePoint);

    /**
    *
    */
    virtual bool CheckCoords(const CGeoRect<short> &mbr);

    //
    // Methods for map operations
    //
    /**
    *
    **/
    virtual void Rotate(double step, bool isDirect = true);

    /**
    * Zoom in current map in continuous way or not continuous way.
    *
    * @param step the scale changes from one scale to another scale. If step = 0, means no any continous changes
    **/
    virtual void ZoomIn(short step = 0);

    /**
    * Zoom in current map in continuous way or not continuous way.
    * @param levelUp the scale changes level
    * @param step the scale changes from one scale to another scale. If step = 0, means no any continous changes
    **/
    virtual void ZoomIn(short levelDown,short step);

    /**
    * Zoom in current map in continuous way or not continuous way.
    *
    * @param step the scale changes from one scale to another scale. If step = 0, means no any continous changes
    **/
    virtual void ZoomOut(short step = 0);

    /**
    * Zoom in current map in continuous way or not continuous way.
    * @param levelUp the scale changes level
    * @param step the scale changes from one scale to another scale. If step = 0, means no any continous changes
    **/
    virtual void ZoomOut(short levelUp, short step);

    /**
    *
    **/
    virtual void Rotating(double step, double from, double to);

    /**
    *
    **/
    virtual void Zooming(bool isZoomIn = true, short step = 5);

    /**
    *
    **/
    virtual void Zooming(short start, short end, short step = 5);

    /**
    *
    **/
    virtual void Transforming(double diff, bool isOnce = false);

    /**
    *
    **/
    virtual void Transforming(double diff, double to);

    /**
    *
    **/
    virtual void SwitchTo(short scaleLevel, double angle);

    /**
    *
    */
    virtual void SwitchTo(const CGeoRect<long> &extent);

    /**
    *
    */
    virtual void GetScale(short &level, int &scale);

    /**
    *
    **/
    virtual void SetScale(short level, int scale);
    virtual int GetMaxScale(){return m_scales.size();};
    /**
    *
    **/
    virtual void EraseScale(short level);

    /**
    *
    */
    virtual bool Pick(const CGeoPoint<short> &scrPoint, CMemVector &objects);

    //
    // Methods of rendering of this view state
    //
    /**
    * Perfect draw
    */
    virtual void OnDraw(short style = RS_All);

    /**
    * Zooming or transforming draw
    */
    virtual void QuickDraw(bool isRaster = true,bool isTransforming = false)
    {
    }

    /**
    *
    **/
    virtual void DirectDraw(short type)
    {
    }

    virtual void DrawProgress(short step = 0)
    {
    }

    /**
    *
    */
    virtual void RenderSelected()
    {
    }

    /**
    * 
    */
    virtual void SetSidePicture(short sidePicCode, short sidePicType, short sideArrowCode = -1, void *wndHandle = 0)
    {
      m_sidePicCode = sidePicCode;
      m_sidePicType = sidePicType;
      m_sideArrowCode = sideArrowCode;
      m_picWndHandle = wndHandle;
    }
    
    /**
    * ���õ�ǰ��ͼ�Ĳ���ģʽ
    */
    virtual void SetViewOpeMode(ViewOpeMode opeMode);

    /**
    * ��ȡ��ǰ��ͼ�Ĳ���ģʽ
    */
    virtual ViewOpeMode GetViewOpeMode();

    /**
    * ������ͼƽ��ƫ����
    * x Ϊx��ƽ�����ر��� 0��ʾ���ƶ� ����ʾ���� ����ʾ����
    * y Ϊy��ƽ�����ر��� 0��ʾ���ƶ� ����ʾ���� ����ʾ����
    */
    virtual void SetViewMoveOffset(float offsetX, float offsetY);

    /**
    * ���õ�ǰ��Ļ���������ĵ㣬��ͼ�泵ת����3D��ͼ�£���ͼ�������ƣ����Է���ʱӦ���Գ���Ϊ���ķ���
    */
    virtual void SetZoomingBase( long x, long y );

    /**
    * ���õ�ǰ��Ļ�����Ƿ�����ƫ��
    */
    virtual void SetTransformStatus(bool value);

    /**
    * �������õ���ͼƽ��ƫ�����Բ��������ƫ��
    */
    virtual void TransformMapPoint(CGeoPoint<long>& mapPoint);

    /**
    * �������õ���ͼƽ��ƫ�����Բ��������ƫ��
    */
    virtual void TransformMapPoint(CGeoPoint<double>& mapPoint);

    /**
    * �������õ���ͼƽ��ƫ�����Բ��������ƫ��
    */
    virtual void TransformMapPoint(CGeoPoint<long>& mapPoint, double headingDegree);

    /**
    * ���ص�ͼ����
    */
    virtual void LoadGridData();

    /**
    * Factory method to get different view state
    **/
    static CViewState *GetState(unsigned short type, bool isLand, CViewImpl *oneView);

    /**
    *
    **/
    static void Release();
    static void TransForm(double *X, double *Y);

    /**
    * \brief �ж�ָ����ͼλ���Ƿ��ڵ�ͼ��Χ��
    */
    static bool IsValidMapPos(const CGeoPoint<long> &mapPoint);

    void LogMsg(const TCHAR *format, ...);
	  /**
    * \brief ������ͼ
    */
	 virtual void ScrollMap();

	  /**
    * \brief �ͷ�ָ���������µĻ�������
    */
   void ForColleguesByScaleLevel(short scaleLevel);
    /*
    * \brief ˢ��ͼ������
    */
   virtual void RefreshLayerData();

   unsigned int GetViewType()
   {
     return m_type;
   }
  protected:
    //
    //
    //
    /**
    *
    */
    virtual void ResetExtent(const CGeoPoint<short> &scrPoint, CGeoRect<long> &mapExtent)
    {
      CGeoPoint<long> mapPoint;
      Scr2Map(scrPoint, mapPoint);

      if(mapExtent.m_minX > mapPoint.m_x)
      {
        mapExtent.m_minX = mapPoint.m_x;
      }

      if(mapExtent.m_maxX < mapPoint.m_x)
      {
        mapExtent.m_maxX = mapPoint.m_x;
      }

      if(mapExtent.m_minY > mapPoint.m_y)   // minY
      {
        mapExtent.m_minY = mapPoint.m_y;
      }

      if(mapExtent.m_maxY < mapPoint.m_y)  // maxY
      {
        mapExtent.m_maxY = mapPoint.m_y;
      }
    }

    /**
    *
    **/
    unsigned int GetDCType();

    /**
    *
    **/
    double GetZoomCoff();

    HDC GetWholeMapDC();
  protected:
    // Belonged view
    CViewImpl *m_viewImpl;

    // Real map extent
    CViewMapping m_mapping;

    // view status
    unsigned int m_type;

    // view style
    short m_style;

    // There exist two types of view: landscape and portrait
    bool m_isLand;

    // Current scale level
    short m_curScaleLevel;

    // Layer levels
    ScaleLevel m_scales;

    // Screen ping point for quickly moving current map
    CGeoPoint<short> m_fixedPt;

    //
    CClipTool m_clipTool;

    // Different view states
    static CViewState *m_headingView;
    static CViewState *m_northView;
    static CViewState *m_perspView;
    static CViewState *m_guidanceView;

    //
    CViewCanvas &m_canvas;

    /// Path basic function
    const CPathBasic &m_pathBasic;
    const CFileBasic &m_fileBasic;

    // Side Picture
    short m_sidePicCode;
    short m_sidePicType;
    short m_sideArrowCode;
    void *m_picWndHandle;

    //��ǰ��ͼ����ģʽ
    ViewOpeMode m_viewOpeMode;

    short m_srcWidth;
    short m_srcHeitht;

    //��Ļ����ƫ�Ʋ���
    float m_offsetX;
    float m_offsetY;
    //��ǰ��Ļ�����Ƿ�����ƫ��
    bool  m_transformStatus;
    //��ͼ����ʱ������λ��
    CGeoPoint<long> m_zoomingBase;

    //��־����
    static CDbgLogger  m_dbgLogger;

    static HDC m_mapDC;
  };
}

#endif