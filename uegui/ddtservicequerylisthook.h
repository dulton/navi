#ifndef _UEGUI_DDTSERVICEQUERYLISTHOOK_H
#define _UEGUI_DDTSERVICEQUERYLISTHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
#include "uipageturningctrl.h"
#include "uebase\geombasic.h"

namespace UeGui
{
  //���ذ�ť�¼�
  typedef void (*ReturnEvent)();
  //��Ӧ��������¼�
  typedef void (*POIQueryEvent)(const char* keyValue1, const char* keyValue2, const CGeoPoint<long>& point);

  class UEGUI_CLASS CDdtServiceQueryListHook : public CAggHook
  {
  public:
    struct POIInfo
    {
      char m_Value1[45];
      char m_Value2[45];
      CGeoPoint<long> m_point;
      POIInfo()
      {
        memset(m_Value1, 0, sizeof(m_Value1));
        memset(m_Value2, 0, sizeof(m_Value2));
        ::memset((char*)&m_point, 0, sizeof(m_point));
      }
    };
    typedef std::vector<POIInfo> POIList;

    enum RowTag
    {
      kROWBegin = 0,
      kROW1,
      kROW2,
      kROW3,
      kROW4,
      kROW5,
      kROW6,
      kROWEnd
    };

    enum DdtServiceQueryListHookCtrlType
    {
      DdtServiceQueryListHook_Begin = 0,
      DdtServiceQueryListHook_Background,
      DdtServiceQueryListHook_ViewMap,
      DdtServiceQueryListHook_ViewPrevious,
      DdtServiceQueryListHook_NavigationTitle,
      DdtServiceQueryListHook_Row1Left,
      DdtServiceQueryListHook_Row1Center,
      DdtServiceQueryListHook_Row1Right,
      DdtServiceQueryListHook_Row2Left,
      DdtServiceQueryListHook_Row2Center,
      DdtServiceQueryListHook_Row2Right,
      DdtServiceQueryListHook_Row3Left,
      DdtServiceQueryListHook_Row3Center,
      DdtServiceQueryListHook_Row3Right,
      DdtServiceQueryListHook_Row4Left,
      DdtServiceQueryListHook_Row4Center,
      DdtServiceQueryListHook_Row4Right,
      DdtServiceQueryListHook_Row5Left,
      DdtServiceQueryListHook_Row5Center,
      DdtServiceQueryListHook_Row5Right,
      DdtServiceQueryListHook_Row6Left,
      DdtServiceQueryListHook_Row6Center,
      DdtServiceQueryListHook_Row6Right,
      DdtServiceQueryListHook_POI1Name,
      DdtServiceQueryListHook_POI1Separater,
      DdtServiceQueryListHook_POI1Area,
      DdtServiceQueryListHook_POI2Name,
      DdtServiceQueryListHook_POI2Separater,
      DdtServiceQueryListHook_POI2Area,
      DdtServiceQueryListHook_POI3Name,
      DdtServiceQueryListHook_POI3Separater,
      DdtServiceQueryListHook_POI3Area,
      DdtServiceQueryListHook_POI4Name,
      DdtServiceQueryListHook_POI4Separater,
      DdtServiceQueryListHook_POI4Area,
      DdtServiceQueryListHook_POI5Name,
      DdtServiceQueryListHook_POI5Separater,
      DdtServiceQueryListHook_POI5Area,
      DdtServiceQueryListHook_POI6Name,
      DdtServiceQueryListHook_POI6Separater,
      DdtServiceQueryListHook_POI6Area,
      DdtServiceQueryListHook_NextPage,
      DdtServiceQueryListHook_NextPageIcon,
      DdtServiceQueryListHook_PreviousPage,
      DdtServiceQueryListHook_PreviousPageIcon,
      DdtServiceQueryListHook_PageInfo,
      DdtServiceQueryListHook_End
    };

    CDdtServiceQueryListHook();

    virtual ~CDdtServiceQueryListHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  public:
    /// �����¼�����ָ�븳ֵ
    void SetReturnEvent(ReturnEvent returnEvent);
    /// POI����Ϣ��ѯ�¼�����ָ�븳ֵ
    void SetPOIQueryEvent(POIQueryEvent poiOQueryEvent);
    //�����ʾ����
    void Clear();
    //�޸�hook����
    void SetTitle(const char* title);
    //�����ʾ����
    void AddData(const char* value1, const char* value2,const CGeoPoint<long>& point);
    /// ��ʾ����
    void ShowData();
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /// ����
    void DoReturn();

    /// ��갴����Ӧ
    void DoMouseUpEvent(const char* keyValue1, const char* keyValue2,int row);
    //���ı��
    void ClearRow(RowTag tag);
    /// �������������
    void ClearAllRow();
    //�����е���Ч��
    void SetRowEnbale(RowTag tag, bool enable);
    /// ����ǰҳ������ʾ��������
    void DoShowData();
    //��������ʾ��ĳ����
    void DoShowRowData(RowTag tag, const char* value1, const char* value2);
  private:
    ReturnEvent m_ReturnEvent;
    /// POI��Ϣ��ѯ�¼�
    POIQueryEvent m_POIOQueryEvent;
    /// �����б���Ϣ
    POIList m_poiList;
  private:
    //��ҳ������
    CPageController m_pageTurning;
    //hook����
    CUiLabel m_navigationTitleCtrl;
    CUiButton m_viewMapCtrl;
    CUiButton m_viewPreviousCtrl;
    CUiLabel m_pageInfoCtrl;
    //��һҳ
    CUiBitButton m_nextPageCtrl;
    //��һҳ
    CUiBitButton m_previousPageCtrl;

    CUiLabel m_pOI1AreaCtrl;
    CUiLabel m_pOI1NameCtrl;
    CUiButton m_pOI1SeparaterCtrl;

    CUiLabel m_pOI2AreaCtrl;
    CUiLabel m_pOI2NameCtrl;
    CUiButton m_pOI2SeparaterCtrl;

    CUiLabel m_pOI3AreaCtrl;
    CUiLabel m_pOI3NameCtrl;
    CUiButton m_pOI3SeparaterCtrl;

    CUiLabel m_pOI4AreaCtrl;
    CUiLabel m_pOI4NameCtrl;
    CUiButton m_pOI4SeparaterCtrl;

    CUiLabel m_pOI5AreaCtrl;
    CUiLabel m_pOI5NameCtrl;
    CUiButton m_pOI5SeparaterCtrl;

    CUiLabel m_pOI6AreaCtrl;
    CUiLabel m_pOI6NameCtrl;
    CUiButton m_pOI6SeparaterCtrl;

    CUiButton m_row1Ctrl;
    CUiButton m_row2Ctrl;
    CUiButton m_row3Ctrl;
    CUiButton m_row4Ctrl;
    CUiButton m_row5Ctrl;
    CUiButton m_row6Ctrl;
  };
}
#endif
