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
#ifndef _UEMAP_PLANLAYER_H
#define _UEMAP_PLANLAYER_H

/// Refer to EXPORT & IMPORT macro definitions
#ifndef _UEMAP_BASE_H
#include "uemap.h"
#endif

/// Refer to its parent
#ifndef _UEMAP_VIEWLAYER_H
#include "viewlayer.h"
#endif

// Refer to UeRoute
#ifndef _UEROUTE_ROUTE_H
#include "ueroute\route.h"
#endif
using namespace UeRoute;

///
namespace UeMap
{
  /// Forward classes
  class CViewImpl;

  /**
  *
  */
  class UEMAP_CLASS CPlanLayer : public CViewLayer
  {
    CPlanLayer(const CPlanLayer &other);
    const CPlanLayer &operator=(const CPlanLayer &other);

  public:
    /**
    *
    */
    CPlanLayer(int scale, CViewImpl *view);

    /**
    *
    */
    virtual ~CPlanLayer();
  public:
    /**
    *
    */
    virtual bool Prepare(bool isMapExtent = false);

    /**
    *
    */
    virtual void Draw(short type, const CViewDC *viewDC, CGeoRect<short> &scrExtent, const CGeoRect<short> &clipBox, bool isRotated = 0, bool is3d = 0);

    /*!
    * \brief ����ǰ������·��
    **/
    virtual void DrawGuidanceRoute(const CViewDC *viewDC, short type, CViewState *curView, UeRoute::GuidanceStatus &dirInfo, CMemVector &coords,
      CGeoRect<long> &mapExtent,  CGeoRect<int> &clipExtent, unsigned char colorIndex, bool is3d = false);

    /*!
    * \brief ���ݹ滮���ͻ���·��
    **/
    virtual void DrawRouteByPlanType(const CViewDC *viewDC, CViewState *curView, unsigned char curPlanType, CMemVector &coords,
      CGeoRect<long> &mapExtent,  CGeoRect<int> &clipExtent, unsigned char colorIndex, bool is3d = false);

    /**
    *
    **/
    virtual bool ForCollegues();
  private:
    /**
    * ��ȡ��ǰ·�߹滮��ʽ
    **/
    unsigned int GetPlanMethodType();

    /**
    * �жϵ�ǰ�Ƿ��Ƕ�·���滮��ʽ
    **/
    bool IsMultiRoutePlan();

    /**
    * ����·�߹滮��ʽ��ȡ�滮·����ɫ����ֵ
    * para planMethodType ·�߹滮��ʽ
    * para isFocusRoute �Ƿ���ѡ�е�·��
    **/
    unsigned char GetRouteColorIndex(unsigned char planMethodType, bool isFocusRoute);
  private:
    /// Route singleton
    IRoute *m_route;
    std::vector<unsigned char> m_planTypeList;
  };
}

#endif