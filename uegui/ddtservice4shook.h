#ifndef _UEGUI_DDTSERVICE4SHOOK_H
#define _UEGUI_DDTSERVICE4SHOOK_H

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
#include "foursshopmgr.h"

namespace UeGui
{
  typedef void (*CarListQueryEvent) (const unsigned int distCode, FourSCarType type);

  class CDdtService4SHook : public CAggHook
  {
  public:
    struct CarTypeInfo
    {
      char m_carName[128];
      FourSCarType m_type;
      CarTypeInfo()
      {
        ::memset(m_carName, 0, sizeof(m_carName));
        m_type = FourSCarType_Toyota;
      }
    };
    typedef std::vector<CarTypeInfo> CarTypeList;

    enum RowTag
    {
      kROWBegin = 0,
      kROW1,
      kROW2,
      kROW3,
      kROW4,
      kROW5,
      kROWEnd
    };

    enum DdtService4SHookCtrlType
    {
      DdtService4SHook_Begin = 0,
      DdtService4SHook_Background,
      DdtService4SHook_ViewMap,
      DdtService4SHook_ViewPrevious,
      DdtService4SHook_NavigationTitle,
      DdtService4SHook_QueryAreaLeft,
      DdtService4SHook_QueryAreaCenter,
      DdtService4SHook_QueryAreaRight,
      DdtService4SHook_Row1Left,
      DdtService4SHook_Row1Center,
      DdtService4SHook_Row1Right,
      DdtService4SHook_Row2Left,
      DdtService4SHook_Row2Center,
      DdtService4SHook_Row2Right,
      DdtService4SHook_Row3Left,
      DdtService4SHook_Row3Center,
      DdtService4SHook_Row3Right,
      DdtService4SHook_Row4Left,
      DdtService4SHook_Row4Center,
      DdtService4SHook_Row4Right,
      DdtService4SHook_Row5Left,
      DdtService4SHook_Row5Center,
      DdtService4SHook_Row5Right,
      DdtService4SHook_QueryAreaLabel1,
      DdtService4SHook_QueryAreaName,
      DdtService4SHook_QueryAreaLabel2,
      DdtService4SHook_POI1Name,
      DdtService4SHook_POI2Name,
      DdtService4SHook_POI3Name,
      DdtService4SHook_POI4Name,
      DdtService4SHook_POI5Name,
      DdtService4SHook_NextPage,
      DdtService4SHook_NextPageIcon,
      DdtService4SHook_PreviousPage,
      DdtService4SHook_PreviousPageIcon,
      DdtService4SHook_PageInfo,
      DdtService4SHook_End
    };

    CDdtService4SHook();

    virtual ~CDdtService4SHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  public:
    //�����ʾ����
    void Clear();
    //�޸�hook����
    void SetTitle(const char* title);
    //���ò�ѯ����
    void SetQueryArea(const char* area);
    //���ò�ѯ���ݷ���˵��
    void SetTypeContent(const char* content);
    //���������Ӧ�¼�
    void SetCarListQueryEvent(CarListQueryEvent serviceListQueryEvent);
    //�����ʾ����
    void AddServiceData(const char* carName, FourSCarType type);
    //��ʾ����
    void ShowData();
    //���ò�ѯ�������
    void SetQueryAreaCode(unsigned int code) 
    {
      m_addrCode = code;
    }
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    void DoMouseUpEvent(const unsigned int codee, int row);
    //���ı��
    void ClearRow(RowTag tag);
    //�����ʾ��Ϣ
    void ClearAllRow();
    //�����е���Ч��
    void SetRowEnbale(RowTag tag, bool enable);
    //���������ʾ����
    void DoShowData();
    //��������ʾ��ĳ����
    void DoShowRowData(RowTag tag, const char* carName, FourSCarType type);
  private:

    static void DoDistSwitchCallBack(void *pDoCallBackObj,const SQLRecord *pResult);
    //��ҳ������
    CPageTurning m_pageTurning;
    //�����Ӧ�¼���4S���б��ѯ�¼�
    CarListQueryEvent m_carListQueryEvent;
    //�����б�
    //ServiceList m_serviceList;
    CarTypeList m_carTypeList;

    unsigned int m_addrCode;
  private:
    CUiLabel m_navigationTitleCtrl;
    CUiButton m_viewMapCtrl;
    CUiButton m_viewPreviousCtrl;    
    CUiLabel m_pageInfoCtrl;
    CUiBitButton m_nextPageCtrl;
    CUiBitButton m_previousPageCtrl;

    CUiButton m_queryAreaLabel1Ctrl;
    CUiButton m_queryAreaLabel2Ctrl;
    CUiButton m_queryAreaCtrl;
    CUiButton m_queryAreaNameCtrl;

    CUiLabel m_pOI1NameCtrl;

    
    CUiLabel m_pOI2NameCtrl;

    CUiLabel m_pOI3NameCtrl;

    CUiLabel m_pOI4NameCtrl;

    CUiLabel m_pOI5NameCtrl;
    CUiButton m_row1Ctrl;
    CUiButton m_row2Ctrl;
    CUiButton m_row3Ctrl;
    CUiButton m_row4Ctrl;
    CUiButton m_row5Ctrl;
  };
}
#endif
