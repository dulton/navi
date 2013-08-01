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
#ifndef _UEMAP_AGGCANVAS_H
#define _UEMAP_AGGCANVAS_H

//
// Refer to UeMap package
//

// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMAP_BASE_H
#include "uemap.h"
#endif

// Move those struct definition from this class
#ifndef _UEMAP_VIEWHOOK_H
#include "viewhook.h"
#endif

// Refer to its parent
#ifndef _UEMAP_VIEWCANVAS_H
#include "viewcanvas.h"
#endif

//
// Refer to AGG package
//
#ifndef AGG_SCANLINE_P_INCLUDED
#include "agg\include\agg_scanline_p.h"
#endif

#ifndef AGG_PATH_STORAGE_INCLUDED
#include "agg\include\agg_path_storage.h"
#endif

//
#ifndef PIXEL_FORMATS_INCLUDED
#include "agg\include\pixel_formats.h"
#endif

//
#ifndef AGG_RENDERER_BASE_INCLUDED
#include "agg\include\agg_renderer_base.h"
#endif

//
#ifndef AGG_RENDERER_SCANLINE_INCLUDED
#include "agg\include\agg_renderer_scanline.h"
#endif

//
#ifndef AGG_RENDERER_PRIMITIVES_INCLUDED
#include "agg\include\agg_renderer_primitives.h"
#endif

//
#ifndef AGG_RASTERIZER_SCANLINE_AA_INCLUDED
#include "agg\include\agg_rasterizer_scanline_aa.h"
#endif

//
#ifndef AGG_SCANLINE_BIN_INCLUDED
#include "agg\include\agg_scanline_bin.h"
#endif

// Whether directly use FreeType 2 shared by David Turner etc and 
// not using GDI supplied by microsoft
#define FT_FONT 1
#if FT_FONT
#ifndef AGG_FONT_FREETYPE_INCLUDED
#include "agg\include\agg_font_freetype.h"
#endif
#else
// True type for win32
#ifndef AGG_FONT_WIN32_TT_INCLUDED
#include "agg\include\agg_font_win32_tt.h"
#endif
#endif

//
#ifndef AGG_FONT_CACHE_MANAGER_INCLUDED
#include "agg\include\agg_font_cache_manager.h"
#endif

//
#ifndef AGG_TRANS_SINGLE_PATH_INCLUDED
#include "agg\include\agg_trans_single_path.h"
#endif

//
#ifndef AGG_CONV_SEGMENTATOR_INCLUDED
#include "agg\include\agg_conv_segmentator.h"
#endif

//
#ifndef AGG_RASTERIZER_OUTLINE_INCLUDED
#include "agg\include\agg_rasterizer_outline.h"
#endif

//
#ifndef AGG_SPAN_GRADIENT_INCLUDED
#include "agg\include\agg_span_gradient.h"
#endif

//
#ifndef AGG_CONV_DASH_INCLUDED
#include "agg\include\agg_conv_dash.h"
#endif

//
#ifndef AGG_VCGEN_MARKERS_TERM_INCLUDED
#include "agg\include\agg_vcgen_markers_term.h"
#endif

//
#ifndef AGG_ARROWHEAD_INCLUDED
#include "agg\include\agg_arrowhead.h"
#endif

//
#ifndef AGG_CONV_STROKE_INCLUDED
#include "agg\include\agg_conv_stroke.h"
#endif

//
#ifndef AGG_CONV_TRANSFORM_INCLUDED
#include "agg\include\agg_conv_transform.h"
#endif

//
#ifndef AGG_CONV_MARKER_INCLUDED
#include "agg\include\agg_conv_marker.h"
#endif

//
#ifndef AGG_CONV_CONCAT_INCLUDED
#include "agg\include\agg_conv_concat.h"
#endif
using namespace agg;

//
// Refer to UeBase package
//

// Refer to own array definition
#ifndef _UEBASE_MEMVECTOR_H
#include "uebase\memvector.h"
#endif
using namespace UeBase;

#if __FOR_PC__
// directshow
#if __FOR_PC_VEDIO__
#include <dshow.h>
#endif
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>
#endif

//
#pragma warning( push )
#pragma warning( disable: 4275 )  // Deprecated function calling

// Declare namespace
namespace UeMap
{
  // Forward classes
  class CAggStackDC;

  /**
  * brief agg������
  */
  class UEMAP_CLASS CAGGCanvas : public CViewCanvas
  {
    // TODO:
    // Erase below relative in order to get better encapsulation
    friend class CGuidanceView;
    friend class CViewImpl;
    friend class CKeyboardHook;
    friend class CInputHook;

    // Note:
    friend class CAggHook;

    /**
    * AGG line encapsulated
    **/
    struct AGGPath
    {
      // Basic information 
      short m_idx;
      int m_clrIdx;
      agg::rgba8 m_clrFill;
      agg::rgba8 m_clrStroke;
      double m_width;
      bool m_isStroke;
      char m_roadClass;

      // Coordinate information
      agg::path_storage m_path;

      // Initialization
      AGGPath() : m_idx(-1), m_clrIdx(-1), m_clrFill(0, 0, 0), m_roadClass(-1), m_clrStroke(0, 0, 0), m_width(0), m_isStroke(false)
      {
      }
    };

    /**
    * AGG point encapsulated
    **/
    struct AGGPoint
    {
      // Basic information
      short m_idx;
      int m_clrIdx;
      short m_size;
      short m_style;

      // Coordinate information
      CGeoPoint<short> m_pos;
      char m_textName[256];	// TODO: Remove magic number

      //
      AGGPoint() : m_idx(-1), m_clrIdx(-1), m_size(0), m_style(0)
      {
        m_textName[0] = '\0';
      }
    };

    /**
    *
    **/
    class gradient_polymorphic_wrapper_base
    {
    public:
      virtual int calculate(int x, int y, int) const = 0;
    };

    /**
    *
    **/
    template<class GradientF> 
    class gradient_polymorphic_wrapper : public gradient_polymorphic_wrapper_base
    {
    public:
      gradient_polymorphic_wrapper() : m_adaptor(m_gradient) {}

      virtual int calculate(int x, int y, int d) const
      {
        return m_adaptor.calculate(x, y, d);
      }
      GradientF m_gradient;
      agg::gradient_reflect_adaptor<GradientF> m_adaptor;
    };

    /**
    *
    **/
    struct color_function_profile
    {
      color_function_profile() {}
      color_function_profile(const color_type* colors, const agg::int8u* profile) :
      m_colors(colors), m_profile(profile) {}

      static unsigned size() { return 256; }
      const color_type& operator [] (unsigned v) const
      { 
        return m_colors[m_profile[v]]; 
      }

      const color_type* m_colors;
      const agg::int8u* m_profile;
    };

    /**
    *
    **/
    template<class Source> 
    struct dash_stroke_fine_arrow
    {
      typedef agg::conv_dash<Source, agg::vcgen_markers_term>                   dash_type;
      typedef agg::conv_stroke<dash_type>                                       stroke_type;
      typedef agg::conv_marker<typename dash_type::marker_type, agg::arrowhead> marker_type;
      typedef agg::conv_concat<stroke_type, marker_type>                        concat_type;

      dash_type      d;
      stroke_type    s;
      agg::arrowhead ah;
      marker_type    m;
      concat_type    c;

      dash_stroke_fine_arrow(Source& src, 
        double dash_len, double gap_len, double w, short scaleLevel) : 
      d(src),
        s(d),
        ah(),
        m(d.markers(), ah),
        c(s, m)
      {
        d.add_dash(dash_len, gap_len);
        d.dash_start(0.);
        s.width(w);

        double various = (5-scaleLevel) > 0. ? (5-scaleLevel) : 1;
        ah.head(4*various, 0*various, 4*various, 1.5*various);
        d.shorten(w * 2.0);
      }

      void rewind(unsigned path_id) { c.rewind(path_id); }
      unsigned vertex(double* x, double* y) { return c.vertex(x, y); }
    };

    // Containers for all kinds of pathes and they would be differenciated by color idx
    typedef std::map<short, AGGPath> PathMap;
    typedef PathMap::iterator path_itr;
    typedef PathMap::const_iterator path_citr;

    // Containers for all kinds of points and they would be differenciated by color idx
    typedef std::map<short, std::vector<AGGPoint> > PointMap;
    typedef PointMap::iterator point_itr;
    typedef PointMap::const_iterator point_citr;

    // Alias names for types
    typedef agg::renderer_base<pixfmt> renderer_base;
    typedef agg::renderer_scanline_aa_solid<renderer_base> renderer_solid;
    typedef agg::renderer_scanline_bin_solid<renderer_base> renderer_bin;
    typedef agg::renderer_primitives<renderer_base> renderer_primitives;
    typedef agg::rasterizer_outline<renderer_primitives> outline_rasterizer;

    // Fonts
#ifdef FT_FONT
    typedef agg::font_engine_freetype_int16 font_engine_type;
#else
    // Note:
    // Some data type specified by AGG currently not supported by wingdi for CE
    typedef agg::font_engine_win32_tt_int16 font_engine_type;
#endif
    typedef agg::font_cache_manager<font_engine_type> font_manager_type;

    //
    typedef agg::conv_curve<font_manager_type::path_adaptor_type> conv_font_curve_type;
    typedef agg::conv_segmentator<conv_font_curve_type> conv_font_segm_type;
    typedef agg::conv_transform<conv_font_segm_type, agg::trans_single_path> conv_font_trans_type;

  public:
    //
    //
    //
    /**
    * \brief ���캯��
    **/
    CAGGCanvas();

    /**
    * \brief ��������
    **/
    virtual ~CAGGCanvas();

  public:
    //
    //
    virtual void MoveTo(const CGeoPoint<double>& point, bool isRefresh);
    //
    /**
    * \brief ƽ�ƴ���
    * \param deltX X���ƶ�����
    * \param deltY Y���ƶ�����
    **/
    virtual bool MoveForSelection(short deltX, short deltY);

    /**
    * \brief Ϊִ���µ�ʰȡ������׼��.������,��,��,poi,���Ƶȵ�����
    * \param isRelease �Ƿ���Ҫ�ͷ��ڴ�ռ�
    */
    virtual bool PrepareForSelection(bool isRelease = false);

    /**
    * \briefΪ��ͼ��������׼��
    **/
    virtual bool PrepareForZooming();

    /**
    * \brief ������Ⱦ����
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    * \param is3d �Ƿ���Ҫ͸�Ӵ���
    * \param isGradual �Ƿ���Ҫ������Ⱦ����
    * Considering AGG need to firstly collect all primitives then render them
    **/
    virtual void RenderBasic(short scaleLevel, bool isRaster = false, bool is3d = false, bool isGradual = false);

    /**
    * \brief �ı���Ⱦ
    * \param viewDC DC�豸ָ��
    * \param asciiText ascii�ı�ָ��
    * \param position ����
    * \param size ��С
    * \param clr ��ɫ
    * \param type ����
    */
    virtual void RenderText(const CViewDC *viewDC, char *asciiText, const CGeoPoint<short> &position, short size, unsigned int clr, unsigned int type);

    /**
    * \brief ��Ⱦ��
    * \param viewDC DC�豸ָ��
    * \param position ����
    * \param category ���
    * \param nameOffset ����ƫ����
    * \param text �ı�ָ��
    * \param size ��С
    * \param isSym 
    * \param showStyle ��ʾ���
    */
    virtual void RenderPoint(const CViewDC *viewDC, const CGeoPoint<short> &position, int category, long nameOffset = -1, const char *text = 0, short size = 0, bool isSym = true, short showStyle = 0);

    /**
    * \brief ��Ⱦ����
    * \param viewDC DC�豸ָ��
    * \param ptsHead �����б�ָ��
    * \param ptCount ������ʽ
    * \param category ���
    * \param nameOffset ����ƫ����
    * \param roadClass ��·�ȼ�
    */
    virtual void RenderLine(const CViewDC *viewDC, const CGeoPoint<int> *const ptsHead, int ptCount, int category, long nameOffset = -1, short roadClass = -1);

#if __FOR_FPC__
    /**
    * 
    */
    virtual void RenderFPCLine(const CViewDC *viewDC, const CGeoPoint<int> *const ptsHead, int ptCount, int category, short status);
#endif

    /**
    * \brief ��ȾLink
    * \param viewDC DC�豸ָ��
    * \param ptsHead �����б�ָ��
    * \param ptCount ������ʽ
    * \param category ���
    * \param nameOffset ����ƫ����
    * \param roadClass ��·�ȼ�
    * \param level ����
    */
    virtual void RenderLink(const CViewDC *viewDC, const CGeoPoint<int> *const ptsHead, int ptCount, int category, long nameOffset = -1, short roadClass = -1, short level = 0);

    /**
    * \brief ��Ⱦ�����
    * \param viewDC DC�豸ָ��
    * \param ptsHead �����б�ָ��
    * \param ptCount ������ʽ
    * \param category ���
    * \param nameOffset ����ƫ����
    */
    virtual void RenderPolygon(const CViewDC *viewDC, const CGeoPoint<int> *const ptsHead, int ptCount, int category, long nameOffset = -1);

    /**
    * \brief ��Ⱦ�ر�
    * \param viewDC DC�豸ָ��
    * \param position ����
    * \param category ���
    * \param nameOffset ����ƫ����
    * \param text �ı�ָ��
    * \param size ��С
    * \param isSym  
    */
    virtual void RenderLandMark(const CViewDC *viewDC, const CGeoPoint<short> &position, int category, long nameOffset = -1, const char *text = 0, short size = 0, bool isSym = true);

    /**
    * \brief ��Ⱦ��·����
    * \param scaleLevel ������
    * \param is3d �Ƿ���Ҫ͸�Ӵ���
    * \param type ����
    */
    virtual void RenderRoadName(short scaleLevel, bool is3d = false, unsigned int type = NT_Normal);

    /**
    * \brief ��Ⱦ�滮·������
    * \param viewDC DC�豸ָ��
    * \param points ���б�
    * \param clrIdx ��ɫ
    * \param isHistory �Ƿ���ʷ��¼
    */
    virtual void RenderPlan(const CViewDC *viewDC, const CMemVector &points, unsigned char clrIdx, bool isHistory = false);

    /**
    * \brief ��Ⱦ�滮·������
    * \param viewDC DC�豸ָ��
    * \param carInfo ������Ϣ
    */
    virtual void RenderPlan(const CViewDC *viewDC, GuidanceCar &carInfo);

    /**
    * \brief ��Ⱦ��������
    * \param viewDC DC�豸ָ��
    * \param scrExtent ��Ļ��Χ
    * \param type ����
    **/
    virtual void RenderGuidance(const CViewDC *viewDC, const CGeoRect<short> &scrExtent, short type);

    /**
    * \brief ��Ⱦ���
    * \param skyLimit �Ƕȿ���
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    virtual void RenderSky(double skyLimit, bool isRaster = false);

    /**
    * \��Ⱦ����
    * \param viewDC DC�豸ָ��
    * \param skyLimit �Ƕȿ���
    **/
    virtual void RenderAnimations(const CViewDC *viewDC, double skyLimit = 0);

    /**
    * \brief ��Ⱦ�滮·���Ķ˵�
    * \param skyLimit �����Ƕ�����ֵ
    **/
    void RenderFlags(double skyLimit, short scaleLevel, bool isRaster = false, bool is3d = false);

    /**
    * \brief ��Ⱦ������
    * \param viewDC DC�豸ָ��
    * \param skyLimit �Ƕȿ���
    **/
    virtual void RenderProgressBar(const CViewDC *viewDC, double percent);

    /**
    *
    */
    virtual void RenderSelected(void *dc);

    /**
    * \brief ��Ⱦ��ǰHook�¼�
    * \param scrExtent ��Ļ��������
    */
    virtual void RenderHooks(const CGeoRect<short> &scrExtent);

    /**
    * \brief ��Ⱦʰȡ���õ���Ϣ
    * \param dc DC�豸ָ��
    */
    virtual void SetPickPosition(const CGeoPoint<long> &mapPoint, CGeoPoint<short> &scrPoint, bool needMoveTo = true);

    /**
    * \brief ��Ⱦʰȡ���õ���Ϣ-��ˢ��
    * \param dc DC�豸ָ��
    */
    virtual void SetPickPosition_NoRefresh(const CGeoPoint<long> &mapPoint, CGeoPoint<short> &scrPoint, bool needMoveTo = true);

    /**
    * \brief ��Ⱦ����ͼƬ
    * \param indexCode ͼƬ������
    * \param type ͼƬ����
    * \param arrowCode ��ͷ������
    **/
    virtual void RenderSidePicture(short indexCode, short type, short arrowCode = -1);

    /**
    * \brief ��ȡ��ǰ�Ĺ��λ��
    *
    * \param sTextStyle:����������ʽ
    * \param tchWord:Ҫ��ӻ�ɾ��������
    * \param sCurPosX:����ǰ����λ�ã��Լ����������λ��
    * \param bIsDelOp:�Ƿ�Ϊɾ��tchWord����
    */
    void GetCurCursorPos(short sTextStyle,TCHAR tchWord,short &sCurPosX,bool bIsDelOp=false);
    /**
    * \brief ���û�������
    * \param id3d �Ƿ����͸��Ч��
    **/
    bool SetupCanvas(bool is3d = false);

    ////��ʾ������-��UIȥ�����ú�����ʱ����
    void RenderElecEye(bool is3D);
    /**
    * \brief ��Ⱦӥ��ͼ
    */
    virtual void RenderEagle(short scaleLevel, bool isRaster, bool is3d);
  protected:
    //
    //
    //
    /**
    * \brief�ͷŻ���ռ�ÿռ�
    **/
    void ReleaseCanvas();

    /**
    * \brief ����������
    * \param category ���
    * \param isStroke 
    * \param width ���
    **/
    int GetLineCategory(int category, bool &isStroke, int &width);

    /**
    * \brief ���Link���
    * \param category ���
    * \param isStroke 
    * \param width ���
    **/
    int GetLinkCategory(int category, short level, bool &isStroke, int &width);

    /**
    * \brief ��ö�������
    * \param category ���
    * \param isStroke 
    * \param width ���
    **/
    int GetPolyCategory(int category, bool &isStroke);

    /**
    * \brief ��õ����
    * \param category ���
    * \param isStroke 
    * \param width ���
    **/
    int GetPointCategory(int category);

    /**
    * \brief ����ı����
    * \param category ���
    * \param isStroke 
    * \param width ���
    **/
    int GetTextCategory(int category);

    /**
    * \brief ����ı���Ϣ
    * \param str �ַ���ָ��
    * \param info ������Ϣ
    * \param isGray �Ƿ���
    **/
    void GetTextInfo(const TCHAR *str, CGeoPoint<int> &info, bool isGray = false);

    /**
    * \brief Ϊ��,��,��������Ӧ��·��
    **/
    void MakePathes();

    /**
    * \brief �ͷ�dian,��,���·��
    **/
    void FreePathes();

    /**
    * \brief��Ⱦ��·����
    * \param scaleLevel ������
    * \param id3d �Ƿ����͸��Ч��
    */
    void RenderNormalRoadName(short scaleLevel, bool is3d);

    /**
    * \brief ��Ⱦ�����ö���ķ�ʽ�����·����
    */
    void RenderAlignedRoadName(short scaleLevel, bool is3d);

    /**
    * \brief ��ȡ�Զ��ַ����ĳ���
    */
    int GettTextOutLength(TCHAR *text, double charAdvanceWidth = 0, bool isGray= true);

    /**
    * \brief �ı����
    * \param oneText agg����Ϣ
    */
    void TextOut(const AGGPoint &oneText);

    /**
    * \brief �ı����
    * \param text �ı�ָ��
    * \param pos ����
    * \param tCurve ·������������
    * \param fTrans ����ת������
    * \param clr ��ɫ
    * \param charAdvanceWidth �ַ����
    * \param isGray �Ƿ���
    **/
    void TextOut(TCHAR *text, const CGeoPoint<int> &pos, agg::trans_single_path *tCurve, conv_font_trans_type *fTrans, unsigned int clr, double charAdvanceWidth = 0., bool isGray = false);

    /**
    * \brief �ı����
    * \param text �ı�ָ��
    * \param fKey �ı��н�������λ����Ϣ
    * \param pos ����
    * \param tCurve ·������������
    * \param fTrans ����ת������
    * \param clr �ı���ɫ
    * \param focusClr �ı��н����ı���ɫ
    * \param charAdvanceWidth �ַ����
    * \param isGray �Ƿ���
    **/
    void TextOutA(const TCHAR *text, const unsigned char *fKey, const CGeoPoint<int> &pos, agg::trans_single_path *tCurve, conv_font_trans_type *fTrans, unsigned int clr, unsigned int focusClr, double charAdvanceWidth = 0., bool isGray = false);

    /**
    * \brief �жϵ�ǰλ���Ƿ��ǽ�������λ��
    * \param key ��ǰ�ַ�λ������
    * \param fKey ��������λ���б�
    * \�ڽ��������б����򷵻�True
    **/
    bool IsFocusKey(unsigned int keyIndex, const unsigned char* fKey);

    //#if __FOR_FPC__
    /**
    * \brief ��ȡ���λ��
    * \param text �ı�ָ��
    * \param endX X���յ�
    * \param index ������
    */
    void GetCursorPos(const TCHAR *text, short &endX, short &index);

    /**
    * \brief ��ȡ�ı����
    * \param text �ı�ָ��
    */
    short GetTextWidth(const TCHAR *text);

    /**
    * \brief ��ȡ�ַ����
    * \param ch �ַ�
    */
    short GetCharWidth(const TCHAR &ch);

    /**
    * \brief ��ȡ�ı�
    * \param �ı�ָ��
    * \param width ���
    */
    void CutText(TCHAR *text, short width);

    /**
    * \brief ������λ��
    * \param isDeleteChar �Ƿ�ɾ���ַ�
    * \param text �ı�ָ��
    * \param endX X���յ�
    * \param index ������
    */
    void ResetCursorPos(bool isDeleteChar, const TCHAR &text, short &endX, short &index);
    //#endif
    /**
    * \brief ��Ⱦ͸�Ӷ����
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspPolygons(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ͸������
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspLines(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ͸��Link
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspLinks(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ��������
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnPolygons(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ��������
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    * \param isGuidance �Ƿ��ǵ����е�·�ڷŴ�ͼ
    **/
    void RenderAfnLines(short scaleLevel, bool isRaster = false, bool isGuidance = false);

    /**
    * \brief ��Ⱦ����Link
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnLinks(short scaleLevel, bool isRaster = false, bool isGuidance = false);

    /**
    * \brief ��Ⱦ����������·
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderGuidanceLines(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ͸�ӵ�
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspPoints(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ͸���ı�
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspTexts(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ͸�ӵر�
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspLandmark(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ�����
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnPoints(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ�����ı�
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnTexts(short scaleLevel, bool isRaster = false);

    /**
    * \brief ��Ⱦ����ر�
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnLandmark(short scaleLevel, bool isRaster = false);

    /**
    * \brief ���ڽ���͸��Ч����Ⱦ
    * \param ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void GradualPspRendering(short scaleLevel, bool isRaster = false);

    /**
    * \brief ���ڽ��з���Ч����Ⱦ
    * \param ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void GradualAfnRendering(short scaleLevel, bool isRaster = false);

    /**
    * \brief ������
    * \param skyLimit ���ӽǶ�����
    **/
    void Fogging(double skyLimit);

    /**
    * \brief ��Ⱦ͸�ӻ��滮·��
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspRouteLine(AGGPath &onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ���仯�滮·��
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnRouteLine(AGGPath &onePath, short scaleLevel, bool isRaster);

    void RenderAfnRouteLineForGuidance(AGGPath onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ͸�ӻ���ͨ����
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspNormalLine(AGGPath &onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ͸�ӻ���ͨLink
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspNormalLink(AGGPath &onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ���仯��ͨLink
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnNormalLink(AGGPath &onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ���仯��ͨ����
    * \param onePath ·��
    * \param scaleLevel ������
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnNormalLine(AGGPath &onePath, short scaleLevel, bool isRaster);

    void RenderAfnLineForGuidance(AGGPath &onePath, short scaleLevel, bool isRaster);

    /**
    * \brief ��Ⱦ͸�ӻ���·��
    * \param onePath ·��
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderPspRailLine(AGGPath &onePath, bool isRaster);

    /**
    * \brief ��Ⱦ���仯��·��
    * \param onePath ·��
    * \param isRaster �Ƿ���Ҫ��դ����
    **/
    void RenderAfnRailLine(AGGPath &onePath, bool isRaster);

    /**
    * \brief ��ȾGPS��Ϣ
    * \param scaleLevel ������
    **/
    void RenderGpsCar(short scaleLevel);

    /**
    * \brief ���Ƴ����뵱ǰ��ѡλ�õ�������
    * \param carPos ����λ�ö�Ӧ����Ļ����
    */
    void RenderConnectingLine(CGeoPoint<long> &carPos, CViewState *curView);

    /**
    * \brief ����ͼ��
    * \param cX ����ͼ������ƽ���X����
    * \param cY ����ͼ������ƽ���Y����
    * \param carIcon ����ͼ���Ӧ��ͼƬIC
    * \param angle �Ƕ�
    **/
    void RenderCarIcon(int cX, int cY, short carIcon, double angle = 0);

    /**
    * \brief ��Ⱦָ����
    * \param scaleLevel ������
    **/
    void RenderCompassDirection(short scaleLevel);

    /**
    * \brief ��Ⱦ���������е����ڹ滮·���ϵķ����ͷ
    */
    void RenderPspGuidanceArrow(short scaleLevel);

    /**
    * \brief ��Ⱦ���������е����ڹ滮·���ϵķ����ͷ
    */
    void RenderAfnGuidanceArrow(short scaleLevel);

    /**
    * \brief ��Ⱦ���������е����ڹ滮·���ϵķ����ͷ
    */
    void RenderBubble(short scaleLevel);

    /**
    * \brief ʸ��·�ڷŴ�ͼ������
    */
    void RenderBubbleForGuidance();

    /**
    * \brief ��Ⱦ���ٳ���ͼ����ʾ
    * \param dirInfo ·����Ϣ
    */
    void RenderHighwayOutlets(short scaleLevel);

    /**
    * \brief ��Ⱦ�෽��Ϣ
    * \param scaleLevel ������
    **/
    void RenderSideInfo(short scaleLevel);

    /**
    * \brief ��Ⱦ��־��
    * \param dirInfo ·����Ϣ
    **/
    void RenderSignPost(GuidanceStatus &dirInfo);

    /**
    * \brief ��Ⱦ��·��Ϣ
    * \param dirInfo ��·��Ϣ
    **/
    void RenderLaneInfo(GuidanceStatus &dirInfo);

    /**
    * \brief ��Ⱦ��ͨ��־
    * \param dirInfo ��·��Ϣ
    */
    void RenderTrafficSign(GuidanceStatus &dirInfo);

    /**
    * \brief ��Ⱦ���⽻��·��
    * \param dirInfo ��·��Ϣ
    * \param scrExtent ��Ļ��Χ
    */
    bool RenderVirtualCross(GuidanceStatus &dirInfo, const CGeoRect<short> &scrExtent);

    /**
    * \brief ��Ⱦʵ�ʿ��
    * \param dirInfo ��·��Ϣ
    * \param scrExtent ��Ļ��Χ
    */
    bool RenderRealCross(GuidanceStatus &dirInfo, const CGeoRect<short> &scrExtent);

    /**
    * \brief ��Ⱦ��·�ھ��������
    * \param dirInfo ��·��Ϣ
    * \param scrExtent ��Ļ��Χ
    */
    void RenderCrossProgress(GuidanceStatus &dirInfo, const CGeoRect<short> &scrExtent);

    /**
    * \brief ���㳵��Ƕ�
    */
    double CaculateCarAngle();
    /**
    * \brief ���Ұ����ĳ���
    */
    void RenderRightScreenCarIcon();

#if __FOR_PC__
    /**
    * 
    */
    void RenderAdvance(GuidanceStatus &dirInfo);

    /**
    * 
    */
    void PlayAdvVideo(tstring &srcFile);

    /**
    * 
    */
    void CloseAdvVideo();
#endif

    /**
    *
    */
    void RenderSenstiveIndicator(void *dc, int style, CGeoPoint<long> &pos, char *name);

    /**
    * \brief ��Ⱦ������
    */
    void RenderRoutePosition(void *dc, CGeoPoint<long> &pos, char *name);
    /**
    * ��Ⱦʰȡ��
    **/
    void RenderCursor(double skyLimit);

    /**
    * \brief ������������
    * \param fontProp ��������
    * \param faceIdx ����
    * \param renType ��Ⱦ����(glyph_rendering)
    */
    void LoadFont(const MapsFont &fontProp, int faceIdx, int renType);

    //
    // GUI Hooks
    //
    /**
    * \brief ��ȾHook����������
    * \param scrExtent ��Ļ��Χ
    * \param oneElement GUIԪ��
    **/
    void RenderHookCommands(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement, const unsigned char* fKey = NULL, bool needRelesePic = true);

    /**
    * \brief ��ť��Ⱦ
    * \param scrExtent ��Ļ��Χ
    * \param oneElement GUIԪ��
    **/
    void DoRenderHookBtns(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement, bool needRelesePic);

    /**
    * \brief ͼƬ��Ⱦ
    * \param scrExtent ��Ļ��Χ
    * \param oneElement GUIԪ��
    * \param picX ͼƬX������
    * \param picY ͼƬY������
    **/
    void DoRenderHookPics(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement, int &picX, int &picY, bool needRelesePic);

    /**
    * \brief �ı���Ⱦ
    * \param scrExtent ��Ļ��Χ
    * \param oneElement GUIԪ��
    * \param picX �ı�X������
    * \param picY �ı�Y������
    **/
    void DoRenderHookTexts(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement, int picX, int picY, const unsigned char* fKey = NULL);


    /**
    * \brief ���ı���Ⱦ
    * \param scrExtent ��Ļ��Χ
    * \param oneElement GUIԪ��
    **/
    void DoRenderHookMultiTexts(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement);

    /**
    * \brief ��ȡ�������
    * \param width ���
    * \param scaleLevel ����
    **/
    double GetLineWidth(double width, short scaleLevel);

    /**
    * \brief ������Ҫ����
    * \param curLine ��·
    * \param scaleLevel ������
    **/
    bool IsNeededName(const RenderedLine *const curLine, short scaleLevel);

    /**
    * \brief �Ƿ���Ҫ��־
    * \param curText �ı�
    **/
    bool IsNeededPlace(const AGGPoint &curText);

    /**
    * \brief �л����ߴ�����
    * \param scaleLevel ������
    **/
    void SwitchToLineBuffers(short scaleLevel);

    /**
    * \brief ���ڴ���������������������Ϣ
    * \param bufferWidth �ڴ���
    * \param leftRight 
    * \param lineCoords �������б�
    * \param bufCoords �ڴ��������б�
    **/
    bool MakeBufferLine(double bufferWidth, short leftRight, const CMemVector &lineCoords, CMemVector &bufCoords);

    /**
    * \brief ���ڴ��������ı���Ϣ
    * \param uniText �ı�ָ��
    * \param clr ��ɫ
    * \param pos ����
    **/
    void MakeBufferText(TCHAR *uniText, unsigned int clr, CGeoPoint<int> pos);

    /**
    * \brief ��ȡ�����ı�������ͳ����Ϣ
    * \param name �ı�ָ��
    * \param tRows ����
    * \param tCols ����
    * \param tCount ����ͳ����
    **/
    bool GetMultiTextBasic(char *name, int &tRows, int &tCols, int &tCount);

    /**
    * \brief ��Ⱦ�����ı�����
    * \param name �ı�ָ��
    * \param leftTopX ���Ͻ�X����
    * \param leftTopY ���Ͻ�Y����
    * \param height �ı��߶�
    **/
    void RenderMultiTextContent(char *name, int leftTopX, int leftTopY, int height);

    /**
    * \brief ��Ⱦ���ı����򱳾�
    * \param pos ��ͼ����
    * \param width ���
    * \param height �߶�
    * \param tRows ����
    * \param tCols ����
    * \param leftTopX ���Ͻ�X����
    * \param leftTopY ���Ͻ�Y����
    **/
    void RenderMultiTextRectBK(CGeoPoint<long> &pos, int width, int height, int tRows, int tCols, double &leftTopX, double &leftTopY);

    /**
    * \brief ��Ⱦ���ı���������򱳾�
    * \param pos ��ͼ����
    * \param width ���
    * \param height �߶�
    * \param tRows ����
    * \param tCols ����
    * \param leftTopX ���Ͻ�X����
    * \param leftTopY ���Ͻ�Y����
    **/
    void RenderMultiTextPolyBK(CGeoPoint<long> &pos, int width, int height, int tRows, int tCols, double &leftTopX, double &leftTopY);

    /**
    * \brief ͼƬ��Ⱦ
    *
    * \param picture ԴͼƬ��Ϣ
    * \param minX Ŀ���������Ͻ�X����
    * \param minY Ŀ���������Ͻ�Y����
    * \param width Ŀ��������
    * \param height Ŀ������߶�
    * \param angle ��ת�Ƕ�
    * \param isStretch �Ƿ�ͼƬ���쵽Ŀ����
    */
    void RenderPicture(const CPictureBasic::PictureBasic &picture, int minX, int minY, int width, int height, double angle = 0, bool isStretch = false);

    /**
    * \brief ����ͼƬ��ȼ�ÿ�����ص�λ����ȡ��ͼƬ��һ�е�λ��
    *
    * \param width ͼƬ���
    * \param bits_per_pixel ÿ�����ص�λ��
    */
    unsigned int GetStride(unsigned width, unsigned bits_per_pixel);

    /**
    * \brief ��Ⱦ���ͼƬ
    */
    void RenderSkyPic(double skyLimit);

    /**
    * \brief ��Ⱦ��Ϣ���ʶ
    */
    void RenderMarkPic(short scaleLevel, bool is3d);

    /**
    * \brief ��Ⱦ���ɵ��ʶ
    */
    void RenderRouteThroughtPoint(double skyLimit, short scaleLevel);
  private:
    /**
    * \brief ��Ⱦ������ı� �ƺ�������
    */
    void RenderSpecialText(short scaleLevel);

    int GetElementTextWidth(int elementWidth, TCHAR *uniText);
 
  protected:
    //
    INameTable *m_roadNameTable;
    INameTable *m_poiNameTable;
    INameTable *m_bkNameTable;

    // The extent of tolerance for rendering those rects or pois or names
    static CGeoPoint<int> m_drawnTolerance;

    // Memory buffer specified by CAggDC 
    static int m_bufWidth;
    static int m_bufHeight;
    static unsigned char *m_bits;
    static unsigned char **m_rows;

    // Selected step for dynamically rendering
    static short m_dynRadius;
    static short m_dynOrder;

    // TODO:
    // This member variable only for demo no any sense
    static short m_poiDemoOrder;

    // Guidance car info
    static GuidanceCar m_gpsCar;

    // Buffer types and different types when against this buffer
    static renderer_solid *m_renderSolid;
    static renderer_bin *m_renderBin;

    // For quick performance issue in draft rendering way
    static renderer_primitives *m_renderPrim;
    static outline_rasterizer *m_lineRas;

    // Raster methods
    static agg::rasterizer_scanline_aa<> m_scanRas;
    static agg::scanline_p8 m_packedSL;
    static agg::scanline_bin m_binSL;

    // True type fonts
    static font_engine_type m_lineFont;
    static font_manager_type m_lineFace;
    static font_engine_type m_grayFont;
    static font_manager_type m_grayFace;

    // Different path storages
    static PathMap m_linePathes;
    static short m_lineTypes;

    static PathMap m_linkPathes;
    static short m_linkTypes;

    static PathMap m_polyPathes;
    static short m_polyTypes;

    static PointMap m_pointPathes;
    static short m_pointTypes;

    static PointMap m_textPathes;//��Ⱦ����
    static short m_textTypes;

    // Time spaces indicating sunrise, sunset, noon, morning, dawn etc
    static short m_timePhase;

    //
    static bool m_isRenderSides;

  private:
    tstring m_advVideoPath;
    tstring m_preFontFile;
    int m_preFont;
    CGeoPoint<double> m_rightScreenCarPos;

#if __FOR_PC__
    // DirectShow interfaces
#if __FOR_PC_VEDIO__
    IGraphBuilder *m_pGB;
    IMediaControl *m_pMC;
    IMediaEventEx *m_pME;
    IVideoWindow  *m_pVW;
    IBasicAudio   *m_pBA;
    IBasicVideo   *m_pBV;
    IMediaSeeking *m_pMS;
    IMediaPosition *m_pMP;
    IVideoFrameStep *m_pFS;
#endif
#endif
  };
}
#endif
