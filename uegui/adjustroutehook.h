#ifndef _UEGUI_ADJUSTROUTEHOOK_H
#define _UEGUI_ADJUSTROUTEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
#include "ueroute/routebasic.h"
#include "uequery/querybasic.h"
#include "routetypeselecthook.h"
#include "upwardordownwardhook.h"

namespace UeGui
{
  class UEGUI_CLASS CAdjustRouteHook : public CAggHook
  { 
  public:    
    const static int kMAXNAME = 128;
    typedef UeRoute::PlanPosition POIItem;
    typedef std::vector<POIItem> POIDataList;

    typedef void (*EditRouteEvent)(CAggHook* sender, const char *journeyName, 
      const unsigned int routeType,
      const POIDataList &poiList);

    //������ʾģʽ
    enum WindowModel
    {
      WDefaultModel, //Ĭ��ģʽ��WAppendModalģʽ
      WAppendModel,  //�����г�ģʽ
      WEditModel,    //�༭�г�ģʽ
      WBrowseModel   //����г�ģʽ
    };

    enum AdjustRouteHookCtrlType
    {
      AdjustRouteHook_Begin = 0,
      AdjustRouteHook_Background,
      AdjustRouteHook_ViewMap,
      AdjustRouteHook_ViewPrevious,
      AdjustRouteHook_NavigationTitle,
      AdjustRouteHook_Line1Left,
      AdjustRouteHook_Line1Center,      
      AdjustRouteHook_Line1Right,
      AdjustRouteHook_Line2Left,
      AdjustRouteHook_Line2Center,      
      AdjustRouteHook_Line2Right,
      AdjustRouteHook_Line3Left,
      AdjustRouteHook_Line3Center,      
      AdjustRouteHook_Line3Right,
      AdjustRouteHook_Line4Left,
      AdjustRouteHook_Line4Center,      
      AdjustRouteHook_Line4Right,
      AdjustRouteHook_Line5Left,
      AdjustRouteHook_Line5Center,      
      AdjustRouteHook_Line5Right,
      AdjustRouteHook_Line6Left,
      AdjustRouteHook_Line6Center,      
      AdjustRouteHook_Line6Right,
      AdjustRouteHook_AddPOI1,
      AdjustRouteHook_AddPOI1Icon,
      AdjustRouteHook_AddPOI2,
      AdjustRouteHook_AddPOI2Icon,
      AdjustRouteHook_AddPOI3,
      AdjustRouteHook_AddPOI3Icon,
      AdjustRouteHook_AddPOI4,
      AdjustRouteHook_AddPOI4Icon,
      AdjustRouteHook_AddPOI5,
      AdjustRouteHook_AddPOI5Icon,
      AdjustRouteHook_POI1Icon,
      AdjustRouteHook_POI1Name,
      AdjustRouteHook_POI1DeleteBack,
      AdjustRouteHook_POI1DeleteIcon,
      AdjustRouteHook_POI2Icon,
      AdjustRouteHook_POI2Name,
      AdjustRouteHook_POI2DeleteBack,
      AdjustRouteHook_POI2DeleteIcon,
      AdjustRouteHook_POI4Icon,
      AdjustRouteHook_POI3Name,
      AdjustRouteHook_POI3DeleteBack,
      AdjustRouteHook_POI3DeleteIcon,
      AdjustRouteHook_POI3Icon,
      AdjustRouteHook_POI4Name,
      AdjustRouteHook_POI4DeleteBack,
      AdjustRouteHook_POI4DeleteIcon,
      AdjustRouteHook_POI5Icon,
      AdjustRouteHook_POI5Name,
      AdjustRouteHook_POI5DeleteBack,
      AdjustRouteHook_POI5DeleteIcon,
      AdjustRouteHook_POI6Icon,
      AdjustRouteHook_POI6Name,
      AdjustRouteHook_POI6EditStartBack,
      AdjustRouteHook_POI6EditStartIcon,
      AdjustRouteHook_ClearLineLeft,
      AdjustRouteHook_ClearLineCenter,
      AdjustRouteHook_ClearLineRight,
      AdjustRouteHook_SaveLineLeft,
      AdjustRouteHook_SaveLineCenter,
      AdjustRouteHook_SaveLineRight,
      AdjustRouteHook_RouteType1,
      AdjustRouteHook_RouteType2,
      AdjustRouteHook_RouteType3,
      AdjustRouteHook_RouteType4,
      AdjustRouteHook_RouteTypeLeft,
      AdjustRouteHook_RouteTypeCenter,
      AdjustRouteHook_RouteTypeRight,
      AdjustRouteHook_RouteTypeLabel,
      AdjustRouteHook_RouteTypeIcon,
      AdjustRouteHook_PlainLineLeft,
      AdjustRouteHook_PlainLineCenter,
      AdjustRouteHook_PlainLineRight,
      AdjustRouteHook_EditLineLeft,
      AdjustRouteHook_EditLineCenter,
      AdjustRouteHook_EditLineRight,
      AdjustRouteHook_AcceptLineLeft,
      AdjustRouteHook_AcceptLineCenter,
      AdjustRouteHook_AcceptLineRight,
      AdjustRouteHook_End
    };

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

    CAdjustRouteHook();

    virtual ~CAdjustRouteHook();

    virtual void Init();

    virtual void MakeGUI();

    virtual void DynamicShow();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  
    //����ִ�з�ʽ��ʾ����
    void SpecialShow(WindowModel model = WDefaultModel);
    //ɾ��POI
    void DeletePOI();
    //�������POI
    void ClearAll();
    //��վ��ɵ�
    void ClearPOIList();
    //��Ӿ��ɵ�
    void AddPOIData(const POIItem& poi);
    void AddPOIData(const POIDataList& poiList);
    //��Ӿ��ɵ�
    void InsertPOIData(int position, const UeQuery::SQLRecord* data);
    //��ȡҪ��ӵ�POIλ��,�±��0��ʼ
    unsigned int GetInsertPosition();
    //�����г�����
    void SetJourneyName(const char *journeyName);
    //ѡ�����õ�·������:�Ƽ�·��,��������,���·��,����·��
    void SetSelectRouteType(unsigned int routeType);
    //����·�����ͣ�������Ͳ�ֻ�����������ȣ��Ƽ�����̣��������������
    void SetRouteType(unsigned int routeType);
    //���������ƶ��¼�
    void DataMove(MoveType moveType);
    //��ʾ���е�����
    void ShowRouteData();
    //�����г�����
    void SaveJourneyData(const char* journeyName);
    //���ñ༭�г��¼�
    void SetEditEvent(HookType senderHookType, CAggHook* sender, const char *journeyName, 
      const unsigned int routeType, EditRouteEvent editRouteEvent);
    //���¹滮·��
    void PlanRoute();
  public:
    //����ɾ��ָ��POI
    static void OnDeletePOI(CAggHook* sender, ModalResultType modalResult);
    //�������POI
    static void OnClearAll(CAggHook* sender, ModalResultType modalResult);
    //���POI
    static void OnInsertPOIData(void* sender, const UeQuery::SQLRecord * data);
    //·������ѡ��
    static void OnRouteTypeSelect(CAggHook* sender, unsigned int routeType);
    //���������ƶ��¼�
    static void OnDataMove(CAggHook* sender, MoveType moveType);
    //��ȡ·������
    static void OnGetRouteName(void* sender, const UeQuery::SQLRecord * data);
    //�滮·��ѡ����ʾ
    static void OnPlanRouteQuestion(CAggHook* sender, ModalResultType modalResult);

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    //���ô�����ʾģʽ
    void SetWindowModel(WindowModel model);
    //��ȡ�б������������
    unsigned int MaxPOIListSize();
    //�����кŻ�ȡ�����±�
    unsigned int GetDataIndex(RowTag row);
    //ɾ��POI
    void DoDeletePOI(RowTag row);
    // �������POI
    void DoClearAll();
    //���POI�ڵ�
    void DoAddPOI(RowTag row);
    //���������ƶ��¼�
    void DoDataMove(RowTag row);
    //�������¼�
    void DoSaveNewData();
    //����༭�����¼�
    void DoSaveEditData();
    //���������
    void ClearRow(RowTag row);
    //�������������
    void ClearAllRow();
    //��������Ч��
    void SetRowEnbale( RowTag row, bool enable);
    //��������ʾ��ĳ����
    void ShowRowData(RowTag row, const char* value);
    //��ȡ·������
    void GetRouteData();
    //�����±�ɾ������
    void DeleteRouteData(int dataIndex);
    //�滮·��
    void DoPlanRoute();
    //ȷ��
    void DoAcceptSave();
    //

  private:
    //�鿴��ͼ
    CUiButton m_viewMapCtrl;
    //����
    CUiButton m_viewPreviousCtrl;
    //��Ӿ��ɵ�
    CUiBitButton m_addPOI1Ctrl;
    CUiBitButton m_addPOI2Ctrl;
    CUiBitButton m_addPOI3Ctrl;
    CUiBitButton m_addPOI4Ctrl;
    CUiBitButton m_addPOI5Ctrl;
    //��һ�пؼ�
    CUiButton m_line1Ctrl;
    CUiLabel m_pOI1NameCtrl;
    CUiBitButton m_pOI1IconCtrl;
    CUiBitButton m_pOI1DeleteCtrl;
    //�ڶ��пؼ�
    CUiButton m_line2Ctrl;
    CUiLabel m_pOI2NameCtrl;
    CUiBitButton m_pOI2IconCtrl;
    CUiBitButton m_pOI2DeleteCtrl;        
    //�����пؼ�
    CUiButton m_line3Ctrl;
    CUiLabel m_pOI3NameCtrl;
    CUiBitButton m_pOI3IconCtrl;
    CUiBitButton m_pOI3DeleteCtrl;    
    //�����пؼ�
    CUiButton m_line4Ctrl;
    CUiLabel m_pOI4NameCtrl;
    CUiBitButton m_pOI4IconCtrl;
    CUiBitButton m_pOI4DeleteCtrl;      
    //�����пؼ�
    CUiButton m_line5Ctrl;
    CUiLabel m_pOI5NameCtrl;
    CUiBitButton m_pOI5IconCtrl;    
    CUiBitButton m_pOI5DeleteCtrl;
    //�����пؼ�
    CUiButton m_line6Ctrl;
    CUiLabel m_pOI6NameCtrl;
    CUiBitButton m_pOI6IconCtrl;
    CUiBitButton m_pOI6EditStartCtrl;
    //���·��
    CUiButton m_clearCtrl;
    //�����г�
    CUiButton m_saveLineCtrl;
    //·������
    CUiBitButton m_routeTypeCtrl;
    //�滮·��
    CUiButton m_plainLineCtrl;
    //�༭����·��
    CUiButton m_editLineCtrl;
    //ȷ��
    CUiButton m_acceptLineCtrl;

    //��¼Ҫɾ�����к�
    RowTag m_selectRowTag;
    //��¼Ҫ������ݵ��к�
    RowTag m_addRowTag;
    //·������1-��������
    CUiLabel m_routeType1;
    //·������2-���·��
    CUiLabel m_routeType2;
    //·������3-����·��
    CUiLabel m_routeType3;
    //·������4-�Ƽ�·��
    CUiLabel m_routeType4;

    //��ǰ���ڵ���ʾģʽ
    WindowModel m_windowModel;
    //���뵱ǰhook��ǰһ��hook
    unsigned int m_enterHookType;
    //�г�����
    char m_JourneyName[kMAXNAME];
    //·������:�Ƽ�·��,��������,���·��,����·��
    unsigned int m_routeType;
    //·�ߵľ��ɵ��±�0Ϊ��㣬Ŀǰ���������յ��ܹ�������6�����ɵ㡣
    POIDataList m_POIList;

    //�༭�г��¼������ⲿ����
    unsigned int m_senderHookType;
    CAggHook* m_senderHook;
    EditRouteEvent m_editRouteEvent;

  };
}
#endif
