#ifndef _UEGUI_ADJUSTROUTEHOOK_H
#define _UEGUI_ADJUSTROUTEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CAdjustRouteHook : public CMenuBackgroundHook
  {
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

    enum DataFrom
    {
      kFromRoute,
      kFromOutside
    };
    static const int kMaxPOIListCount = 6;

  public:
    enum adjustroutehookCtrlType
    {
      adjustroutehook_Begin = MenuBackgroundHook_End,
      adjustroutehook_POI1Btn,
      adjustroutehook_POI1BtnIcon,
      adjustroutehook_POI1Name,
      adjustroutehook_POI2Btn,
      adjustroutehook_POI2BtnIcon,
      adjustroutehook_POI2Name,
      adjustroutehook_POI3Btn,
      adjustroutehook_POI3BtnIcon,
      adjustroutehook_POI3Name,
      adjustroutehook_POI4Btn,
      adjustroutehook_POI4BtnIcon,
      adjustroutehook_POI4Name,
      adjustroutehook_POI5Btn,
      adjustroutehook_POI5BtnIcon,
      adjustroutehook_POI5Name,
      adjustroutehook_POI6Btn,
      adjustroutehook_POI6BtnIcon,
      adjustroutehook_POI6Name,
      adjustroutehook_AddPOI1,
      adjustroutehook_AddPOI1Icon,
      adjustroutehook_AddPOI2,
      adjustroutehook_AddPOI2Icon,
      adjustroutehook_AddPOI3,
      adjustroutehook_AddPOI3Icon,
      adjustroutehook_AddPOI4,
      adjustroutehook_AddPOI4Icon,
      adjustroutehook_AddPOI5,
      adjustroutehook_AddPOI5Icon,
      adjustroutehook_AddPOI6,
      adjustroutehook_AddPOI6Icon,
      adjustroutehook_POI1Gps,
      adjustroutehook_POI1GpsIcon,
      adjustroutehook_POI2Delete,
      adjustroutehook_POI2DeleteIcon,
      adjustroutehook_POI3DeleteIcon,
      adjustroutehook_POI3Delete,
      adjustroutehook_POI4Delete,
      adjustroutehook_POI4DeleteIcon,
      adjustroutehook_POI5Delete,
      adjustroutehook_POI5DeleteIcon,
      adjustroutehook_POI6Delete,
      adjustroutehook_POI6DeleteIcon,
      adjustroutehook_StartGuidanceBtn,
      adjustroutehook_BottomBack,
      adjustroutehook_DemoGuidanceBtn,
      adjustroutehook_HSeparator,
      adjustroutehook_Separator1,
      adjustroutehook_Separator2,
      adjustroutehook_Separator3,
      adjustroutehook_Separator4,
      adjustroutehook_SaveLineBtn,
      adjustroutehook_Separator5,
      adjustroutehook_Separator6,
      adjustroutehook_RouteTypeBtn,
      adjustroutehook_RouteTypeLabel,
      adjustroutehook_RouteTypeBtnIcon,
      adjustroutehook_PlainLineBtn,
      adjustroutehook_AddPOIIconBak,
      adjustroutehook_End
    };

    CAdjustRouteHook();

    virtual ~CAdjustRouteHook();

    virtual void Init();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Load();
    //���õ���·�ߵ��б������ҵ��г̵Ľ��롣
    void SetPOIDataList(const POIDataList& poiList, const int dataIndex);
  protected:

    virtual void MakeNames();

    void MakeControls();
  private:
    //��վ��ɵ�
    void ClearPOIList();
    //��Ӿ��ɵ�
    void AddPOIData(const POIItem& poi);
    //��Ӿ��ɵ�
    void InsertPOIData(int position, const UeQuery::SQLRecord* data);
    //��ȡҪ��ӵ�POIλ��,�±��0��ʼ
    unsigned int GetInsertPosition();
    //��ʾ���е�����
    void ShowRouteData();

    void DoDeletePOI( RowTag row );

    void DeleteRouteData( RowTag row );

    void PlanRoute();

    void SetPosition();

    void StartGuidance();

    void StartDemo();

    static void OnSaveJourneyData(void *pDoCallBackObj, const char* journeyName);

    void DoSaveJourneyData(const char *journeyName);
  private:
    
    //����ɾ��ָ��POI
    static void OnDeletePOI(CAggHook* sender, ModalResultType modalResult);
    //�������POI
    static void OnClearAll(CAggHook* sender, ModalResultType modalResult);
    //���POI
    static void OnInsertPOIData(void* sender, const UeQuery::SQLRecord * data);
    //·������ѡ��
    static void OnRouteTypeSelect(CAggHook *sender, unsigned int routeType);

  private:
    void SetRouteTypeCaption(unsigned int routeType);
    //�������������
    void ClearAllRow();

    void ClearRow( RowTag row );
    
    void SetRowEnbale( RowTag row, bool enable );

    void ChangeButotnIcon(bool isEdit, CUiBitButton &button);

    void GetRouteData();

    //��������ʾ��ĳ����
    void ShowRowData(RowTag row, const char* value);

    //�����кŻ�ȡ�����±�
    unsigned int GetDataIndex(RowTag row);

    //ɾ��POI
    void DeletePOI();
    //�������POI
    void ClearAll();

    void EditPOIData(RowTag row, const POIItem &item);

    void SetGpsPos();

    void GetGpsItem(POIItem &item);

    static void SelectPointEvent(void *callBackObj, const UeQuery::SQLRecord* data);

    void DoEditOrAddPoi(RowTag row);
    //��ʼ����ť��״̬
    void InitButtonState();
  private:

    //·�ߵľ��ɵ��±�0Ϊ��㣬Ŀǰ���������յ��ܹ�������6�����ɵ㡣
    POIDataList m_POIList;

    //��¼ѡ�е��к�
    RowTag m_selectRowTag;

    unsigned int m_planMethod;

    bool m_isFormRouteTypeSwitch;

    DataFrom m_dataFrom;

    int m_dataIndex;

  private:
    CUiBitButton m_addPOI1Ctrl;
    CUiBitButton m_addPOI2Ctrl;
    CUiBitButton m_addPOI3Ctrl;
    CUiBitButton m_addPOI4Ctrl;
    CUiBitButton m_addPOI5Ctrl;
    CUiBitButton m_addPOI6Ctrl;
    CUiButton m_addPOIIconBakCtrl;
    CUiButton m_bottomBackCtrl;
    CUiButton m_demoGuidanceBtnCtrl;
    CUiButton m_hSeparatorCtrl;
    CUiBitButton m_pOI1BtnCtrl;
    CUiBitButton m_pOI1GpsCtrl;
    CUiButton m_pOI1NameCtrl;
    CUiBitButton m_pOI2BtnCtrl;
    CUiBitButton m_pOI2DeleteCtrl;
    CUiButton m_pOI2NameCtrl;
    CUiBitButton m_pOI3BtnCtrl;
    CUiBitButton m_pOI3DeleteCtrl;
    CUiButton m_pOI3NameCtrl;
    CUiBitButton m_pOI4BtnCtrl;
    CUiBitButton m_pOI4DeleteCtrl;
    CUiButton m_pOI4NameCtrl;
    CUiBitButton m_pOI5BtnCtrl;
    CUiBitButton m_pOI5DeleteCtrl;
    CUiButton m_pOI5NameCtrl;
    CUiBitButton m_pOI6BtnCtrl;
    CUiBitButton m_pOI6DeleteCtrl;
    CUiButton m_pOI6NameCtrl;
    CUiButton m_plainLineBtnCtrl;
    CUiBitButton m_routeTypeBtnCtrl;
    CUiButton m_routeTypeLabelCtrl;
    CUiButton m_saveLineBtnCtrl;
    CUiButton m_separator1Ctrl;
    CUiButton m_separator2Ctrl;
    CUiButton m_separator3Ctrl;
    CUiButton m_separator4Ctrl;
    CUiButton m_separator5Ctrl;
    CUiButton m_separator6Ctrl;
    CUiBitButton m_startGuidanceBtnCtrl;
  };
}
#endif
