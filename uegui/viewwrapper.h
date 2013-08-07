/*
* 
*/

#ifndef _UEGUI_WIEWWRAPPER_H
#define _UEGUI_WIEWWRAPPER_H

#include "uegui.h"
#include "uemap/view.h"
#include "uegps/mapmatch.h"
#include "uequery/query.h"
#include "ueroute/route.h"
#include "uemodel/network.h"
#include "uemap/viewstate.h"
#include "uemap/viewcommand.h"

using namespace UeMap;
using namespace UeModel;
using namespace UeRoute;
using namespace UeQuery;

namespace UeGui
{
  class CViewWrapper
  {
  public:
    /**
    * \brief ��������
    */
    virtual ~CViewWrapper();
  private:
    /**
    * \brief ���캯��
    */
    CViewWrapper();
  public:
    /*
    * \brief ��ȡ����ӿ�
    */
    static CViewWrapper& Get();
    /*
    * \brief ���ش���
    */
    void HideWindow();

    /**
    * \brief ��ȡ����ͼ��ͼ
    */
    CViewState* GetMainViewState();

    /**
    * �л���ͼ����
    **/
    void NextState();

    /**
    * \brief ����ͼ�Ƶ����λ��,���û�������ص�GPS�źŴ�
    */
    void MoveToStart();

    /**
    * \brief ����ͼ�Ƶ�����λ��
    */
    void MoveToCar();

    /**
    * \brief �������Ƶ�GPS�źŴ�
    */
    void MoveToGPS();

    /**
    * ��ȡ��ǰ����ͼ�ı�����
    */
    void GetScale(short &level, int &scale);

    /**
    * ��ȡ��ǰ�������߼���
    */
    unsigned short GetMaxScaleLevel();

    /**
    * ��ȡ��ǰ��������λ������
    **/
    const GpsCar &GetGpsCar();

    /**
    * ���õ�ǰ��������λ��
    **/
    void SetGpsCar(const GpsCar &gpsCar);

    /**
    * ��ȡ��ǰGPS����λ������
    **/
    const GpsCar &GetGpsPosInfo();

    /**
    * ���õ�ǰGPS����λ������
    **/
    void SetGpsPosInfo(const GpsCar &gpsInfo);

    /**
    * ��ȡHook
    **/
    CViewHook *GetHook(short type);

    /**
    * ˢ�´���
    **/
    void Refresh();

    /**
    * ˢ��GUI
    **/
    void RefreshUI(short type = VT_Unknown);

    /**
    * ���õ�ǰ��ͼ�Ĳ���ģʽ
    */
    void SetViewOpeMode(ViewOpeMode opeMode, ViewType type = VT_Unknown);

    /**
    * ��ȡ��ǰ��ͼ�Ĳ���ģʽ
    */
    ViewOpeMode GetViewOpeMode(ViewType type = VT_Unknown);

    /**
    * ѡ��
    **/
    bool Pick(const CGeoPoint<short> &scrPoint, CMemVector &objects, bool isRendered = false);

    /**
    * ѡ��
    **/
    void SetPickPos(const CGeoPoint<long> &pickPos, CGeoPoint<short> &scrPoint, bool refresh = true);

    /**
    *   ��ȡ��ǰѡ��ĵ�
    **/
    void GetPickPos(CGeoPoint<long> &pickPos);

    /**
    * \��ȡѡ��������
    **/
    void GetPickName(char *pickName);

    /**
    * \��ȡѡ��������
    **/
    char* GetSelectName();

    /**
    * ��ȡ��Ļ����
    **/
    bool GetScreenCenter(CGeoPoint<long> &mapPt);

    /**
    * \�Ŵ��ͼ
    **/
    void ZoomIn(short levelDown, short step);

    /**
    * \��С��ͼ
    **/
    void ZoomOut(short levelUp, short step);

    /**
    * \��������յ��Ŀ�ĵ�
    **/
    unsigned int SetPosition(); 
    /**
    * ��������յ��λ���Զ����ŵ�ͼ�����ʱ�����
    * \param isLock ����ʱ�Ƿ��������Զ��Ŵ�
    */
    bool AutoScallingMap(bool isLock = false);

    /**
    * �л���ָ��������
    */
    void SwitchTo(short scaleLevel, double angle, short type = VT_Unknown);

    /**
    * ����ָ����Χ�л�������
    */
    void SwitchTo(const CGeoRect<long> &extent);

    /**
    * ���÷�����������Ļ����ʾ��λ����Ϣ
    * param scrPoint ����������ʾ����Ļ����λ�� 
    */
    void SetCompassIconPos(const CGeoPoint<short> &scrPoint);

    /**
    * ���ó�����Ϣ����Ļ����ʾ��λ����Ϣ
    * param scrPoint ������Ϣ��ʾ����Ļ����λ�� 
    */
    void SetLanePos(CGeoPoint<short> &scrPoint, short width, short height);

    /**
    * param ��ǰ�Ƿ���Ҫ��Ⱦ·�ڷŴ�ͼ
    */
    bool IsNeedRenderGuidanceView();

    /**
    * param ·�ڷŴ�ͼ�Ƿ���ʾ
    */
    bool IsGuidanceViewShown();

    /**
    * param ��ʾ·�ڷŴ�ͼ
    */
    void ShowGuidanceView();

    /**
    * param ��ʾӥ��ͼ
    */
    void ShowEagleView(bool show = true);
  public:
    /**
    * ��ӵ�ͼ��ԴͼƬ�ӿ�
    */
    bool AddViewIcon(ViewIconType iconType, short icon);
  private:
    IRoadNetwork *m_net;
    IView *m_view;
    IRoute *m_route;
    IMapMatch *m_gps;
    IQuery *m_query;
  };
}

#endif