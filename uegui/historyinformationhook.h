#ifndef _UEGUI_HISTORYINFORMATIONHOOK_H
#define _UEGUI_HISTORYINFORMATIONHOOK_H

#include "uegui.h"
#include "agghook.h"
#include "uilabel.h"
#include "uibutton.h"
#include "uipageturningctrl.h"
#include "messagedialoghook.h"
#include "ueroute\routebasic.h"
#include "menubackgroundhook.h"

namespace UeGui
{
  //Forward class
  class CUserDataWrapper;

  class UEGUI_CLASS CHistoryInformationHook : public CMenuBackgroundHook
  {
  public:
    struct PageInfo
    {
      short PageIndex; //��ǰҳ������
      int StartPosition; //��ǰҳ����ʼλ��
      int EndPosition; //��ǰҳ�Ľ���λ��
      PageInfo() : PageIndex(-1), StartPosition(-1), EndPosition(-1) {}           
    };
    enum PageTag
    {
      kPageNone = 0,
      kPageHisRecord,     //��ʷ��¼  
      kPageHisTrajectory, //��ʷ�켣
      kPageHisRoute,      //��ʷ·��
      kPageEnd
    };
    enum TabStatus
    {
      kTabNormal, //����״̬
      kTabFocus   //���ڽ���״̬
    };
    enum RowTag
    {
      kROWNone = 0,
      kROW1,
      kROW2,
      kROW3,
      kROW4,
      kROW5,
      kROWEnd
    };

    enum HistoryInformationHookCtrlType
    {
      HistoryInformationHook_Begin = MenuBackgroundHook_End,

      HistoryInformationHook_HistoryRecord,
      HistoryInformationHook_HistoryTrajectory,
      HistoryInformationHook_HistoryRoute,

      HistoryInformationHook_Row1Center,
      HistoryInformationHook_DeletePOI1Back,
      HistoryInformationHook_DeletePOI1Icon,
      HistoryInformationHook_OperatePOI1Center,
      HistoryInformationHook_OperatePOI1Icon,

      HistoryInformationHook_Row2Center,
      HistoryInformationHook_DeletePOI2Back,
      HistoryInformationHook_DeletePOI2Icon,
      HistoryInformationHook_OperatePOI2Center,
      HistoryInformationHook_OperatePOI2Icon,
 
      HistoryInformationHook_Row3Center,
      HistoryInformationHook_DeletePOI3Back,
      HistoryInformationHook_DeletePOI3Icon,
      HistoryInformationHook_OperatePOI3Center,
      HistoryInformationHook_OperatePOI3Icon,

      HistoryInformationHook_Row4Center,
      HistoryInformationHook_DeletePOI4Back,
      HistoryInformationHook_DeletePOI4Icon,
      HistoryInformationHook_OperatePOI4Center,
      HistoryInformationHook_OperatePOI4Icon,

      HistoryInformationHook_Row5Center,
      HistoryInformationHook_DeletePOI5Back,
      HistoryInformationHook_DeletePOI5Icon,
      HistoryInformationHook_OperatePOI5Center,
      HistoryInformationHook_OperatePOI5Icon,

      HistoryInformationHook_POI1Name,
      HistoryInformationHook_POI2Name,
      HistoryInformationHook_POI3Name,
      HistoryInformationHook_POI4Name,
      HistoryInformationHook_POI5Name,

      HistoryInformationHook_separator1,
      HistoryInformationHook_separator2,
      HistoryInformationHook_separator3,
      HistoryInformationHook_separator4,
      HistoryInformationHook_separator5,

      HistoryInformationHook_PreviousPage,
      HistoryInformationHook_PreviousPageIcon,
      HistoryInformationHook_NextPage,
      HistoryInformationHook_NextPageIcon,
      HistoryInformationHook_CurrentPageInfor,
      HistoryInformationHook_TotalPageInfor,

      HistoryInformationHook_BottomBack,
      HistoryInformationHook_PageCenter,
      HistoryInformationHook_LabelBack,
      HistoryInformationHook_LabelSeparator1,
      HistoryInformationHook_LabelSeparator2,

      HistoryInformationHook_ClearCenter,
      HistoryInformationHook_End
    };

    CHistoryInformationHook();

    virtual ~CHistoryInformationHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Load();

  protected:
    virtual void MakeNames();

    void MakeControls();

  public:
    void EditRecord(const char* recordName);
    //���ⲿ���õ�ɾ�����ݽӿ�
    void DeleteRecord();
    //���ⲿ���õ�������ݽӿ�
    void DeleteAllRecord();
    //ѡ����ʷ·��
    void SelectHistoryRoute();
  private:
    //����ɾ���켣�¼�
    static void OnDeleteRecord(CAggHook* sender, ModalResultType modalResult);
    //������������¼�
    static void OnDeleteAllRecord(CAggHook* sender, ModalResultType modalResult);
    //��ȡ·������
    static void OnGetRouteName(void* sender, const UeQuery::SQLRecord * data);
    //ѡ����ʷ·��
    static void OnSelectHistoryRoute(CAggHook* sender, ModalResultType modalResult);

    //ѡ������
    void DoSelectRecord(RowTag row);
    //�༭��ʷ��Ϣ��ť
    void DoEditRecord(RowTag row);
    //ɾ��ĳ�����ݲ�������Ϣ����û�ѡ���Ƿ�ɾ��
    void DoDeleteRecord(RowTag row);
    //ɾ����������
    void DoClearAllRecord(PageTag page);
    //������ʷ·�߹滮
    void DoPlanHistoryRoute();
    //����ҳ��
    void ActivatePage(PageTag page);
    //����Tab״̬
    void SetTabStatus(PageTag page, TabStatus status);
    //����Tabҳ�޸İ�ťͼ��(���棬�༭)
    void ChangeOperatorCtrlIcon(PageTag page);
    //�ı�ؼ�ͼƬ
    void ChangeCtrlIcon(GuiElement* destElement, GuiElement* sorcElement);    
    //���ı��
    void ClearRow(RowTag row);
    /// �������������
    void ClearAllRow();
    //�����е���Ч��
    void SetRowEnbale(RowTag row, bool enable);
    //��������ʾ��ĳ����
    void DoShowRowData(RowTag row, const char* value);
  private:
    //��ȡҪɾ�������ݵ�����
    int GetDataIndex(RowTag& row);
    //ɾ��ĳҳ��ָ��������
    void DeleteData(PageTag page, RowTag row);
    //���ݷ�ҳ������÷�ҳ��ť״̬
    void SetNavigatorStatus();
    //����ҳ����ʾ����
    void ShowHistoryData(PageTag page);
    //�����ʷ��Ϣ�Ƿ������ݣ�������ʷ��¼����ʷ�켣����ʷ·�ߣ�
    void CheckHistoryInfoData();
    //������ʷ��¼ҳ
    void SetHistoryPointPageInfo();
    //��ȡ����ʾ��ʷ��¼
    void ShowHistoryPointData();
    //ɾ����ʷ��¼����
    bool DeleteHistoryPointData(int index);
    //ɾ�����е���ʷ��¼����
    bool DeleteAllHistoryPointData();
    //������ʷ�켣ҳ
    void SetHistoryTrajectoryPageInfo();
    //��ȡ����ʾ��ʷ�켣����
    void ShowHistoryTrajectoryData();
    //ɾ����ʷ�켣����
    bool DeleteHistoryTrajectoryData(int index);
    //ɾ��������ʷ�켣����
    bool DeleteAllHistoryTrajectoryData();
  private:
    //��ʾҳ��Ϣ
    void ShowPageInfo();
    //������ʷ·��ҳ��Ϣ
    void SetHistoryRoutePageInfo();
    //��ȡ����ʾ��ʷ·������
    void ShowHistoryRouteData();
    //�޸���ʷ·������
    void EditHistoryRouteData(int index, const char* routeName);
    //ɾ����ʷ·������
    bool DeleteHistoryRouteData(int index);
    //ɾ��������ʷ·������
    bool DeleteAllHistoryRouteData();
    //�Ƚ����������������Ƿ����
    short DecimalCompare(const double value1, const double value2);
  private:
    //��ҳ������
    CPageController m_pageTurning;
    //��ʷ��¼ Page
    CUiButton m_historyRecordPageCtrl;
    //��ʷ·�� Page
    CUiButton m_historyRoutePageCtrl;
    //��ʷ�켣 Page
    CUiButton m_historyTrajectoryPageCtrl;
    //��һҳ
    CUiBitButton m_nextPageCtrl;
    //ǰһҳ
    CUiBitButton m_previousPageCtrl;

    CUiButton m_currentPageInforCtrl;
    CUiButton m_totalPageInforCtrl;
    //�������
    CUiButton m_clearCtrl;
    //POI������Ϣ
    CUiButton m_pOI1NameCtrl;
    CUiButton m_pOI2NameCtrl;
    CUiButton m_pOI3NameCtrl;
    CUiButton m_pOI4NameCtrl;
    CUiButton m_pOI5NameCtrl;
    //ɾ����ť
    CUiBitButton m_deletePOI1BackCtrl;
    CUiBitButton m_deletePOI2BackCtrl;
    CUiBitButton m_deletePOI3BackCtrl;
    CUiBitButton m_deletePOI4BackCtrl;
    CUiBitButton m_deletePOI5BackCtrl;
    //������ť������ͱ༭ʹ��ͬһ����ť
    CUiBitButton m_operatePOI1Ctrl;
    CUiBitButton m_operatePOI2Ctrl;
    CUiBitButton m_operatePOI3Ctrl;
    CUiBitButton m_operatePOI4Ctrl;
    CUiBitButton m_operatePOI5Ctrl;
    //�пؼ�
    CUiButton m_row1Ctrl;
    CUiButton m_row2Ctrl;
    CUiButton m_row3Ctrl;
    CUiButton m_row4Ctrl;
    CUiButton m_row5Ctrl;
    //��¼��ǰѡ����к�
    RowTag m_selectRow;
    //��ǰ�ҳ
    PageTag m_avtivePageIndex;
    //��ʷ��¼ҳ������Ϣ
    PageInfo m_historyRecordPage;
    //��ʷ�켣ҳ������Ϣ
    PageInfo m_historyTrajectoryPage;
    //��ʷ·��ҳ������Ϣ
    PageInfo m_historyRoutePage;
    //��Ϣ�Ի���
    CMessageDialogHook messageHook;
    //�Ƿ����������ʷ��¼
    bool m_canOpeHistoryRecrd;
    //�Ƿ����������ʷ�켣
    bool m_canOpeHistoryTrajectory;
    //�Ƿ����������ʷ·��
    bool m_canOpeHistoryRoute;

    const CUserDataWrapper& m_userWrapper;
  };
}
#endif
