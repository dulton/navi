#ifndef _UEGUI_MAPHOOK_H
#define _UEGUI_MAPHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
#include "viewwrapper.h"
#include "routewrapper.h"
#include "settingwrapper.h"
#include "userdatawrapper.h"
#include "mapmainmenuhook.h"
#include "mapsimulationmenuhook.h"
#include "mapoverviewmenuhook.h"
#include "mapguideinfoviewhook.h"
#include "mapquerymenuhook.h"
#include "maproutecalcmenuhook.h"
#include "uequery\querybasic.h"


//////////////////////////////////////////////////////////////////////////
//������
#include "QueryHookBase.h"
#include "uemap\viewcanvas.h"
//////////////////////////////////////////////////////////////////////////
//���ɹ滮��ĸ�����
#define MAXPOSTIONCOUNT  6

namespace UeGui
{
  //��ʼģ�⵼���ٶ�
  const static short INITIAL_DEMOSPEED = 30;
  //�����л���ʱ���
  const static short TIMER_INTERVAL = 6;

  class UEGUI_CLASS CMapHook : public CAggHook
  {
  public:
    enum MapHookCtrlType
    {
      MapHook_Begin = 0,
      MapHook_MiniMizeBack,
      MapHook_MiniMizeIcon,
      MapHook_AddElecEyeBack,
      MapHook_AddElecEyeIcon,
      MapHook_MapAzimuthBack,
      MapHook_NorthIcon,
      MapHook_HeadingIcon,
      MapHook_PerspectiveIcon,
      MapHook_CompassBack,
      MapHook_CompassIcon,
      MapHook_ZoomInBack,
      MapHook_ZoomInIcon,
      MapHook_ZoomOutBack,
      MapHook_ZoomOutIcon,
      MapHook_ScaleBack,
      MapHook_ScaleLabel,
      MapHook_SoundBack,
      MapHook_SoundIcon,
      MapHook_GPSBack,
      MapHook_GPSIcon,
      MapHook_GPSIcon0,
      MapHook_GPSIcon1,
      MapHook_GPSIcon2,
      MapHook_GPSIcon4,
      MapHook_GPSIcon3,
      MapHook_GPSIcon5,
      MapHook_GPSIcon6,
      MapHook_GPSIcon7,
      MapHook_GPSIcon8,
      MapHook_GPSIcon9,
      MapHook_GPSIcon10,
      MapHook_GPSIcon11,
      MapHook_GPSIcon12,
      MapHook_ScreenMoadlBack,
      MapHook_SingleScreenIcon,
      MapHook_DoubleScreenIcon,
      MapHook_SetStartBack,
      MapHook_SetStartIcon,
      MapHook_SetStartLabel,
      MapHook_SetWayBack,
      MapHook_SetWayIcon,
      MapHook_SetWayLabel,
      MapHook_SetEndBack,
      MapHook_SetEndIcon,
      MapHook_SetEndLabel,
      MapHook_FixedPostionBack,
      MapHook_FixedPostionIcon,
      MapHook_FixedPostionLabel,
      MapHook_TimerLabel,
      MapHook_DetailBack1,
      MapHook_DetailIcon1,
      MapHook_DetailLabe1,
      MapHook_DetailBack2,
      MapHook_DetailIcon2,
      MapHook_DetailLabe2,
      MapHook_GuideInfoLeftBack,
      MapHook_GuideInfoLeftIcon,
      MapHook_GuideInfoLeftLabe,
      MapHook_Delimiter1,
      MapHook_GuideInfoCenterBack,
      MapHook_GuideInfoCenterIcon,
      MapHook_GuideInfoCenterLabe,
      MapHook_Delimiter2,
      MapHook_GuideInfoRightBack,
      MapHook_GuideInfoRightIcon,
      MapHook_GuideInfoRightLabe,
      MapHook_OtherIcon,
      MapHook_End
    };
    //��ͼ�����������
    enum GUIType
    {
      GUI_None,
      GUI_MapBrowse,        //��ͼ�������
      GUI_RouteCalculate,   //·�߹滮��Ͻ���
      GUI_RealGuidance,     //��ʵ����״̬,��ʾ�˵���
      GUI_DemoGuidance,     //ģ�⵼��״̬,��ʾ�˵���
      GUI_OverviewRoute,    //����·�߽���
      GUI_QueryPoint,       //������
      GUI_SelectPoint,      //ѡ�����
      GUI_SelectArea        //ѡ�������
    };
    //��ͼ�˵���������
    enum MenuUpdateType
    {
      MUT_Normal,  //����ˢ�¸���
      MUT_Expand,  //�˵�չ������
      MUT_Close    //�˵���������
    };
    //��λö������
    enum PosType
    {
      PT_Current,   //��ǰ��
      PT_Previous,  //ǰһ��
      PT_Next       //��һ��
    };
    //�滮����
    enum PlanType
    {
      Plan_Single,   //��·���滮
      Plan_Multiple  //��·���滮
    };
  public:
    CMapHook();

    virtual ~CMapHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \brief ������Ⱦ
    */
    virtual void DoDraw(const CGeoRect<short> &scrExtent);
    /**
    * \brief ��ʼ��hook��Ϣ
    */
    virtual void Init();
    /**
    * \brief ����Hook
    */
    virtual void Update(short type);
    /**
    * ��ʱ��
    **/
    virtual void Timer();
    /**
    * \brief ����GUI��Ϣ
    */
    virtual void MakeGUI();
    /**
    * \brief ��ʾ����֮ǰ������׼��
    */
    virtual void Load();
    /**
    * \brief �л�����ʱ�ͷ�����
    **/
    virtual void UnLoad();
  public:
    /**
    * \brief �������
    */
    unsigned int SetRouteStart();
    /**
    * \brief ���þ�����
    */
    unsigned int SetRouteMiddle();
    /**
    * \brief �����յ�
    */
    unsigned int SetRouteEnd();
    /**
    * \brief ·���滮
    */
    unsigned int RoutePlane(PlanType planType = Plan_Single);
    /**
    * \brief ��ȡ��·���滮��ʽ
    */
    unsigned char GetMultiMethodType();
    /**
    * \brief ��ʼģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int StartDemo(short speed = INITIAL_DEMOSPEED);
    /**
    * \brief ֹͣģ�⵼��
    * \return ����ɹ�����PEC_Success�����򷵻ش������
    */
    unsigned int StopDemo();
    /**
    * \brief ��ʼ����
    */
    unsigned int StartGuidance();
    /**
    * \brief ֹͣ����
    */
    unsigned int StopGuidance();
    /**
    * \brief ɾ��·��
    */
    unsigned int  EraseRoute();
    /**
    * \brief ���õ�ǰѡ��ĵ�Ϊͼ�ϵ�,���ⲿ��ѯPOI���ߵ�·���ƽ���
    */
    void SetPickPos(const CGeoPoint<long> &point, const char* name);
    /**
    * \brief ���õ�ǰѡ��ĵ�Ϊͼ�ϵ�,���ⲿ��ѯPOI���ߵ�·���ƽ���
    * param pointList ���б�
    * param posIndex ��ǰ��λ����������:�±��0��ʼ
    */
    void SetPickPos(PointList pointList, unsigned short posIndex);
    /**
    * \brief ��ӳ��õ�����ѡ��
    * param point ����ĵ�
    * param name ����������
    * param selectPointObj ����ѡ��Ķ���
    * param selectEvent ѡ���Ļص��¼�
    */
    void SelectPoint(const CGeoPoint<long> &point, const char* name, void* selectPointObj, SelectPointEvent selectEvent);
    /**
    * \brief ����·��
    */
    void OverviewRoute();
  public:
    /**
    * \brief ���ص�ǰ�������а�ť�ؼ�
    */
    void HideAllCtrl();
    /**
    * \brief ��ʾ��������С�����������á������źš���Ļģʽ�Ȱ�ťͼ��
    */
    void ShowMinimizeBtn(bool show = true);
    /**
    * \brief ��ʾ��������ӵ�����ͼ��
    */
    void ShowAddElecEyeBtn(bool show = true);
    /**
    * \brief ��ʾ�����ص�ͼ����ͼ��
    */
    void ShowMapAzimuthBtn(bool show = true);
    /**
    * \brief ��ʾ�����طŴ���С��ťͼ��
    */
    void ShowMapScalingBtn(bool show = true);
    /**
    * \brief ��ʾ����������㡢�յ㡢;���㰴ťͼ��
    */
    void ShowSetDestPointBtn(bool show = true);
    /**
    * \brief ��ʾ�����ض�λ��ťͼ��
    */
    void ShowFixedPostionBtn(bool show = true);
    /**
    * \brief ��ʾ���������鰴ťͼ��
    */
    void ShowDetailBtn1(bool show = true);
    /**
    * \brief ��ʾ���������鰴ťͼ��
    */
    void ShowDetailBtn2(bool show = true);
    /**
    * \brief ��ʾ������������Ϣ��ťͼ��
    */
    void ShowGuideInfoBtn(bool show = true);
    /**
    * \brief ��ʾ������ʱ����ʾ��ǩ
    */
    void ShowTimeBtn(bool show = true);
    /**
    * \brief ��ʾ������ָ����
    */
    void ShowCompass(bool show = true);
    /**
    * \brief ���ش���
    */
    void MinMize();
    /**
    * \brief �����˵�����
    */
    void OpenFunctionMenu();
    /**
    * \brief �򿪿�ݲ˵�
    */
    void OpenShortCutMenu();
    /**
    * \brief ���ܱ�����
    */
    void OpenAroundSearchMenu();
    /**
    * \brief �������˵�
    */
    void OpenSearchMenu();
    /**
    * \brief ������˵�
    */
    void OpenDetailHook();
    /**
    * \brief �л���ͼ����
    */
    void ChangeMapAzimuth();
    /**
    * \brief ��ͼ�Ŵ�
    */
    void ZoomIn();
    /**
    * \brief ��ͼ��С
    */
    void ZoomOut();
    /**
    * \brief ȡ��
    */
    void Cancel();
    /**
    * \brief ѡ��
    */
    void Select();
    /**
    * \brief ����������Ϣ����ǰ�����ٶȺ͵�·����
    */
    void UpdateGuideInfo(const char* routeName, double speed, double distance);
    /**
    * \brief ���ص�ǰһ������
    */
    void ReturnToPrevGUI();
    /**
    * \brief ��λ��ָ����ѯ��λ��
    * param haveNext����ʶ�Ƿ�����һ��
    */
    void SetQueryPos(PosType posType);
    /**
    * \brief �Ƿ�����һ����ѯ��¼
    */
    bool HaveNextQueryPoint(PosType posType);
    /**
    * \brief ���¿�ʼ�����л���ʱ��
    */
    void RestarGuiTimer();
    /**
    * \brief �رս����л���ʱ��
    */
    void CloseGuiTimer();
    /**
    * \brief ��ǰ��ʱ����ʱ���
    */
    bool IsGuiTimerDown();
    /**
    * \brief ��ʾ·�ڷŴ�ͼ
    */
    void ShowGuideView();
    /**
    * \brief �Ƿ���ָ����״̬
    */
    bool IsShowCompass();
  protected:
    /**
    * \brief ����Ƥ�������ļ�����
    */
    virtual tstring GetBinaryFileName();
    /**
    * \brief ���ɿؼ�����
    */
    virtual void MakeNames();
    /**
    * \brief ���ɿؼ�
    */
    void MakeControls();
  private:
    /**
    * \brief ���ݵ�ǰ���������л�����
    **/
    void SwitchingGUI(GUIType guiType);
    /**
    * \brief ���²˵�
    */
    bool UpdateMenu(MenuUpdateType updateType = MUT_Normal);
    /**
    * \brief �����ͼ�¼�
    **/
    void MapTouch(CGeoPoint<short> &scrPoint);
    /**
    * \brief ˢ�µ�ǰ��ͼ����λ����Ϣ
    */    
    void RefreshLocationInfo(const char* name = NULL);
    /**
    * \brief ˢ�µ�ͼ����ͼ��
    */ 
    void RefreshMapAzimuthIcon();
    /**
    * \brief ˢ�·�����ť��������״̬
    */
    void RefreshZoomingInfo();
    /**
    * \brief ˢ�±����߱�ǩ
    */
    void RefreshScaleLabel(unsigned short scaleLevel);
    /**
    * \brief ��ʾ���Ƕ�λ����
    **/
    void ShowGPSNum(int locationNum);
    /**
    * \brief ˢ���辭�ɵ㰴ť״̬
    **/
    void RefreshSetPointStatus();
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
    * \brief ����ⲿ����Ĳ�ѯ�б�����
    */
    void ClearQueryPointList();
    /**
    * \brief ����������Ϣͼ����ʾ
    */
    void FillGuidanceInfo();
  private:
    //��ҳ����С��
    CUiBitButton m_miniMizeBtn;    
    //��ӵ�����
    CUiBitButton m_addElecEyeBtn;
    //��ͼ����
    CUiBitButton m_mapAzimuthBtn;
    //�Ŵ�
    CUiBitButton m_zoomInBtn;
    //��С
    CUiBitButton m_zoomOutBtn;
    //������
    CUiBitButton m_scaleBtn;
    //��������
    CUiBitButton m_soundBtn;
    //GPS�ź�
    CUiBitButton m_GPSBtn;
    //��Ļģʽ
    CUiBitButton m_screenMoadlBtn;
    //�����
    CUiBitButton m_setStartBtn;
    //��Ŀ�ĵ�
    CUiBitButton m_setEndBtn;
    //�辭����
    CUiBitButton m_setWayBtn;
    //��λ
    CUiBitButton m_fixedPostionBtn;
    //ϵͳʱ��
    CUiBitButton m_timerBtn;
    //ָ����
    CUiBitButton m_compassIcon;
    //����
    CUiBitButton m_detailBtn1;
    CUiBitButton m_detailBtn2;
    //����
    CUiBitButton m_guideInfoLeftBtn;
    CUiBitButton m_guideInfoCenterBtn;
    CUiBitButton m_guideInfoRightBtn;
    //�ָ��
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
  private:
    //��ǰ·���滮��ʽ
    PlanType m_planType;
    //��ͼ���ʽӿ�
    CViewWrapper& m_viewWrapper;
    //·���滮���ʽӿ�
    CRouteWrapper& m_routeWrapper;
    //���ò������ʽӿ�
    CSettingWrapper& m_settingWrapper;
    //�û����ݽӿ�
    const CUserDataWrapper& m_userDataWrapper;
    //���˵�������hook���ǵ����͵���ʱ���棩
    CMapMainMenuHook m_mapMainMenu;
    //·�߼���˵�����
    CMapRouteCalcMenuHook m_mapRouteCalcMenu;
    //ģ�⵼���˵���hook
    CMapSimulationMenuHook m_mapSimulationMenu;
    //·�߼������ʱ�˵��������·�߲˵�����
    CMapOverViewMenuHook m_mapOverViewMenu;
    //����ʱ������ͼ��˵�����һ��·���ơ��������򿴰塢���ٿ��塢���̵���ʾ��
    CMapGuideInfoViewHook m_mapGuideInfoView;
    //��ѯ����˵�
    CMapQueryMenuHook m_mapQueryMenu;
    //ѡ��ص�����
    void* m_selectPointObj;
    //ѡ��ص��¼�
    SelectPointEvent m_selectPointEvent;
    //��ǰ����˵�����
    GUIType m_curGuiType;
    //��һ������˵�����
    GUIType m_preGuiType;
    //���ⲿ��ѯת���ͼ����ʱ����ĵ��б����ݵ�ǰ�±�����
    int m_queryPointIndex;
    //��ǰ��λ������
    PointInfo m_curPoint;
    //���ⲿ��ѯת���ͼ����ʱ����ĵ��б�����
    PointList m_queryPointList;
    //�����л���ʱ���
    short m_guiTimerInterval;
    //��ǰѡ��Ĺ滮��ʽ����
    MethodType m_curPlanmethodType;
    //�Ƿ���ʾָ����
    bool m_bIsCompassShown;

  //////////////////////////////////////////////////////////////////////////
  //�ɴ���
  public:
    /**
    * \brief �����˵�
    */
    void OpenMainMenu(){}
    /**
    * \brief ˢ����ͼ��ť״̬
    */
    void SwitchViewStateBtn(){};
     /**
    * \brief ��ͼ�Ŵ�
    * \param count �Ŵ���ټ�
    */
    void MapZoomIn(unsigned short count = 1){};
    /**
    * \brief ��ͼ��С
    * @param count ��С���ٲ��
    */
    void MapZoomOut(unsigned short count = 1){};
    /**
    * /brief �ܱ�����
    */
    void OpenGridQuery(){};
    /**
    * /brief ��·����
    */
    void RouteOperation(){};
    /**
    * /brief �򿪶�·������
    */
    void OpenMultiRoutePath(){};
    /**
    * \brief �����
    */
    void FindPlaceName(){};
    /**
    * \brief ����ģ�⵼�����ٶ�
    */
    void SetDemoGuidanceSpeed(short speedTag){};
    /**
    * \brief ӥ��ͼ
    */
    void HawkEyeMap(){};
    /**
    *  \brief �ܱ���Ϣ�л���maphook����
    **/
    void PeripheralInformationSwitch(SQLRecord *pPoiRecord){};
    /**
    * \brief ��Ӿ��ɵ�
    **/
    bool AddThroughPoint(){return false;};
    /**
    * \brief ����Ŀ�ĵأ��������滮���ȴ��ں͵���ѡ�񴰿�
    */
    bool SetRouteEndA(){return false;};
    /**
    * \brief ����Ŀ�ĵأ����ж�������Ŀ�ĵػ�����Ӿ��ɵ㣬�ᵯ������Ŀ�ĵش���
    */
    bool SetRouteEndB(){return false;};
    /**
    * \brief ������������
    **/
    bool DoRouteGuidance(){return false;};
    /**
    * \brief ֹͣ����
    **/
    bool DoRouteStopGuidance(){return false;};
    /**
    * \brief ����ģ�⵼��
    **/
    bool DoDemoStart(short demoSpeed = DEFAULT_DEMOSPEED){return false;};
    /**
    * \brief ��ͣģ�⵼��
    **/
    bool DoDemoPause(){return false;};
    /**
    * \brief ֹͣģ�⵼��
    **/
    bool DoDemoStop(){return false;};
    /**
    * \brief ɾ��·��
    */
    bool DoEraseRoute(){return false;};
    /**
    * \brief ȡ��·���滮
    */
    bool DoRouteCancel(){return false;};
    /**
    * \brief �˳�����״̬,���������˵�
    */
    void DoExitGuidanceAndSwitchToMainMenu(){};
    /**
    * \brief ȡ���˳�����״̬
    */
    void DoCancelExitGuidance(){};
    /**
    * \brief �Ƿ��ڵ���ʱ״̬
    */
    bool IsCountDown(){return false;};
    /**
    * \brief ���ö�·���滮��ʽ
    */
    void SetMultiMethodType(MethodType methodType){};
    /**
    * \brief ���µ���ʱ״̬
    */
    void UpdateCountDown(){};
    /**
    *
    **/
    void SwitchState(bool isPerspective){};

    /**
    * \brief ���ܱߣ�ͼ��ѡ�� ��ť����ʱ�ṩ�ص������ӿ�
    **/
    void SetPoint(void *pDoCallBackObj, Query_CallBack *pCallBackEvent){};
    /**
    * �Ƿ��Ѿ�׼���ÿ�ʼ����
    **/
    bool IsReadyForPlanning(){return false;};
    /**
    * �Ƿ������������,�絯�������Ի���ѡ��ʱ��������ط�ֻ�ǹرմ��ڲ�������������
    **/
    bool InterfaceNotOperable(){return false;};
    /**
    * ����ѡ�㰴ť���ػ�����ʾ�����������Ҫ���´���
    **/
    void SetFavoritePickVisble(bool value){};
    /**
    * \brief ��ȫ���л�����������
    */
    void MoveToSplitGui(){};
    /**
    * \brief �ɰ����л���ȫ������
    */
    void MoveToFullGui(){};
    /**
    * \brief �л�������ʵ��������
    **/
    void MoveToRealGuidanceGUI(){};
    /**
    * \brief �л�����ģ�⵼������
    **/
    void MoveToDemoGuidanceGUI(){};
    /**
    * \brief ·�߸���
    **/
    void SwitchToRouteOverview(){};

    void GoToPosFromList(const CGeoPoint<long> &point, const char *name){};
    /**
    * \brief ·�߸���
    **/
    void SwitchToRoutePlanReadyGUI(){};
     /**
    * \brief �Ƿ���ʾ������
    */
    void ShowElecEye(bool isShown = false){};
    /**
    * \brief �Ƿ�򿪶�·���滮
    */
    bool ShowMultiMethod(){return false;};
    /**
    * \brief ��������SetMethod
    */
    void ReSetMethod(){};
    /**
    * \brief �ж��Ƿ���������SetMethod
    */
    void IsReSetMethod(bool TrueOrFalse){};
    /**
    * \brief ����Ļ���ĵ�ˢ��������ٶ���Ϣ
    **/
    void RefershLocationInfo(){};
    /**
    * \brief ���þ���
    **/
    void SetSlience(bool isSlience){};
  public:
    /**
    * \brief ��ͼ״̬��Ϣ
    */
    struct MapStateInfo
    {      
      int  m_curScaleLevel;               // ��ǰ������
      bool isOpenStopGuidanceMessageBox;  // �Ƿ��Ѿ���ֹͣ�����Ի���
      bool hasMoveCenter;                 // �Ƿ��ƶ�����ͼ���ĵ�      
      bool needCountDown;                 // �Ƿ���Ҫ���е���ʱ
      bool hasOpenRouteOption;            // �Ƿ��Ѿ��򿪹滮ѡ��
      bool hasOpenRoutePathOption;        // �Ƿ��Ѿ��򿪶�·��ѡ��
      bool needShowGudianceIcon;          // �Ƿ���Ҫ��ʾ����ͼ��
      bool needShowHighSpeedBoard;        // �Ƿ���Ҫ��ʾ���ٿ���
    };
  private: 
    /**
    * \brief ���ص�ǰ��������Ԫ��
    **/
    void HideAllGUIElements(){};
    /**
    * \brief ���ص���һ����������
    **/
    void ReturnToPreviousGUI(){};
    /**
    * \brief ��������ͼ��
    */
    void HideCurGuidanceIcon(){};
    /**
    * \brief ��ʾĿ�ĵؼ���㵽Ŀ�ĵؾ���
    */
    void ShowDestinationInfo(){};
    /**
    * \brief ��ʾ����������Ŀ�ĵؾ����״̬��
    */
    void ShowDestinationInfoBar(bool value = true){};
    /**
    * \brief ��ʾ��һ��·���Ƽ�����Ŀ�ĵؾ���
    */
    void ShowRouteInfo(const char* roadName, int distance){};
    /**
    * \brief ��ʾ������һ��·���Ƽ�����Ŀ�ĵؾ����״̬��
    */
    void ShowRouteInfoBar(bool value = true){};
    /**
    * \brief ���ݵ�ǰ������Ϣ��ʾ�ض���ͼ����ʾ(���䴦ͼƬ)
    * \param isShow ��ʾ��������
    */
    void ShowCurGuidanceIcon(bool isShow, int sndCode = 0, unsigned char infoCode = 0){};
    /**
    * \brief ������һ������Ϣ��ʾ�ض���ͼ����ʾ(���䴦ͼƬ)
    * \param isShow ��ʾ��������
    */
    void ShowNextGuidanceIcon(bool isShow, int sndCode = 0, unsigned char infoCode = 0){};
    /**
    * \brief �����Ͻ���ʾ·�ڷŴ�ͼ��
    * \param isShow ��ʾ��������
    * \param iconType ��ʾ��ͼ������
    */
    void ShowCrossingIcon(bool isShow, short iconType = 0, const char* content = NULL){};
    /**
    * \param iconType ��ʾĿ�ĵ�ͼ������
    */
    void ShowDestationPointIcon(short iconElementType){};
    /**
    * \brief ��ʾ����ͼ��
    * \param isShow ��ʾ��������
    */
    void ShowLimitIcon(bool isShow, short iconType = 0){};
    /**
    * \brief ��þ��յ�ʣ��ʱ��
    */
    double GetLeftTime(const UeRoute::GuidanceStatus &dirInfo){return 0;};
    /**
    * \brief ���ñ�������ʾ��ʶ
    */
    void ResetScaleLabel(int scaleLevel){};
    /**
    * \brief �򿪵���ѡ��Ի��򲢿�ʼ��ʱ
    */
    void OpenNavigationSelectionHook(){};
    /**
    * \brief ��������
    */
    void SetVolume(int volumeSize){};
    /**
    * \brief ѡ�� ���ҵ���Ϣ->���õ� ����
    */
    void DoSelectPoint(){};
    /**
    * \brief �趨 ���ҵط�->���ܱ�->ͼ��ѡ�㸽�� ����
    */
    void DoSetPoint(){};

    /**
    * \brief ���ݽ������͵����ؼ�λ��
    */
    void ResetGuiElementPosition(){};

    /**
    * \brief ���õ�����ͼ��λ������
    */
    void ResetEyePosition(){};

    /**
    * \brief ���ó�����Ϣλ������
    */
    void ResetLaneInfoPosition(){};

    /**
    * \brief �޸ߡ����ء��޿�ͼ�������
    */
    void TestLimitShow(int sumTimeLimit){};

    /**
    * \brief ��ȡ����ͼ��ͼ
    */
    CViewState* GetMainViewState(){return NULL;};

    /**
    * \brief �ı�����Ԫ�ص�ͼƬ
    */
    bool ChangeElementIcon(GuiElement* destElement, GuiElement* srcElement){return false;};

    /**
    * \brief ��ʾ·��ת��ͼ�ؼ�
    */
    void ShowCornerIconCtrl(CUiBitButton &cornerIconCtrl, bool isShown = true){};
    
    /**
    * \brief �Զ�������ͼ���浽�ɿ���ȫ·�ߵĺ��ʱ�����
    */ 
    void AutoScallingMap(){};

   /**
    * \�Ӱ����򵼺��������л���֮ǰ����
    */ 
   void FindFuturGUI2Switch( GUIType guiType ){};

   /**
    * \�ж��Ƿ��ǵ���״̬������ģ�⵼������ʵ����
    */ 
   bool IsGuidanceStatus(){return false;};

   void SwitchTopStateBar(bool isDetail){};

    /**
    * \���ٿ���
    */ 
   void HighSpeedBoard(){};
   /**
   * \brief ��ʾGPS��Ϣ
   **/
   void ShowGPS(){};
 public:
     //�ж��Ƿ�򿪲˵�
     bool m_isOpenMenu;
     //�Ƿ���˫����ʾ״̬
     bool m_isSplit;
  private:
  //////////////////////////////////////////////////////////////////////////
  };
}
#endif
