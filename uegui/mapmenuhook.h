#ifndef _UEGUI_MAPMENUHOOK_H
#define _UEGUI_MAPMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

namespace UeGui
{
  class UEGUI_CLASS CMapMenuHook : public CAggHook
  {
  public:
    enum MapMenuHookCtrlType
    {
      MapMenuHook_Begin = 0,
      MapMenuHook_Operation1Left,
      MapMenuHook_Operation1,
      MapMenuHook_Operation1Right,
      MapMenuHook_Delimiter1,
      MapMenuHook_Operation2,
      MapMenuHook_Delimiter2,
      MapMenuHook_Operation3,
      MapMenuHook_Delimiter3,
      MapMenuHook_Operation4,
      MapMenuHook_Delimiter4,
      MapMenuHook_Operation5,
      MapMenuHook_Delimiter5,
      MapMenuHook_Operation6,
      MapMenuHook_Operation6Right,
      MapMenuHook_End
    };

    //�˵����Ͷ���
    enum MapMenuType
    {
      MT_None,            //([    ][        ][        ][        ][        ][      ]) �޲�����״̬�˵�
      MT_Browse,          //([�˵�][�ܱ���Ϣ][        ][        ][�� �� ��][�����]) ���״̬�˵�
      MT_Default,         //([�˵�][�ܱ���Ϣ][        ][��Ŀ�ĵ�][�� �� ��][�����]) Ĭ�ϲ���״̬�˵�
      MT_RouteReady,      //([�˵�][��ʼ����][·�߲���][�� · ��][ģ�⵼��][ȡ  ��]) ·�߹滮���ʱ�˵�
      MT_RealGuidance,    //([�˵�][�ܱ���Ϣ][·�߲���][ӥ �� ͼ][ֹͣ����][�����]) ��ʵ����ʱ�˵�
      MT_RealGuidanceOpe, //([�˵�][�ܱ���Ϣ][·�߲���][��Ŀ�ĵ�][ֹͣ����][�����]) ��ʵ����ʱ�˵����ɲ�����ͼ
      MT_DemoGuidance,    //([�˵�][�ܱ���Ϣ][·�߲���][ӥ �� ͼ][ֹͣģ��][  1X  ]) ģ�⵼��ʱ�˵�
      MT_DemoGuidanceOpe, //([�˵�][�ܱ���Ϣ][·�߲���][��Ŀ�ĵ�][ֹͣģ��][  1X  ]) ģ�⵼��ʱ�˵����ɲ�����ͼ
      MT_MultiRoute,      //([�˵�][��ʼ����][·�߲���][        ][ģ�⵼��][ȡ  ��]) ��·���鿴ʱ�˵�
      MT_ResetRoute,      //([�˵�][�ܱ���Ϣ][·�߲���][��Ŀ�ĵ�][�� �� ��][�����]) �ѹ滮·�ߵ�û�п�ʼ����Ҳû�п�ʼģ�⵼��
      MT_OnlyMenu         //([�˵�][        ][        ][        ][        ][      ]) ֻ�в˵���ť
    };
    
    //�����¼����Ͷ���
    enum MapMenuOperation
    {
      MO_None,                 //�޲���
      MO_OpenMenu,             //�򿪲˵�
      MO_SurroundInfo,         //�ܱ���Ϣ
      MO_RouteOperation,       //·�߲���
      MO_MultiPath,            //��·�� 
      MO_SetStartingPoint,     //�����
      MO_SetDestinationPoint,  //��Ŀ�ĵ�            
      MO_StartRealGuidance,    //��ʼ����
      MO_StopRealGuidance,     //ֹͣ����
      MO_StartDemoGuidance,    //ģ�⵼��
      MO_StopDemoGuidance,     //ֹͣģ��
      MO_DemoSpeed,            //ģ�⵼���ٶ�ѡ��:1X,2X,4X,��ͣ
      MO_HawkEyeMap,           //ӥ��ͼ
      MO_FindPlaceName,        //�ҵط�
      MO_Cancel,               //ȡ��
    };

    struct DemoSpeedInfo
    {
      char m_speedText[5];
      short m_speed;
    };
    typedef std::vector<DemoSpeedInfo> DemoSpeedInfoList;

  public:
    CMapMenuHook();

    virtual ~CMapMenuHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
  public:
    /*
    * ����maphookָ��
    */
    void SetMapHook(CAggHook* mapHook);
    /*
    * ����routeָ��,��ȡ�滮״̬
    */
    void SetRoute(IRoute *route);
    /*
    * ���ݹ������ò˵�����
    */
    void MakeMapMenu(MapMenuType menuType);
    /*
    * ��ʼ��ģ���ٶ�
    */
    void InitDemoSpeed();
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    virtual void MakeControls();
  private:
    //��ʼ���ؼ�״̬
    void InitOperationCtrls();
    //ִ�в���
    void DoOperation(MapMenuOperation operation);
    //���ģ���ٶ�
    void UpdateDemoGuidanceSpeed();
  private:
    DemoSpeedInfoList m_speedList;
    //��ǰ�˵�����
    MapMenuType m_menuType;
    //ģ�⵼���ٶ�����ֵ 0:��ͣ 1: 1X 100km/h 2: 2X 200km/h 3: 4X 400km/h
    char m_demoSpeedIndex;
    //maphookָ��
    CAggHook* m_mapHook;
    //·�߹滮����
    IRoute *m_route;
    //�ָ���
    CUiButton m_delimiter1Ctrl;
    CUiButton m_delimiter2Ctrl;
    CUiButton m_delimiter3Ctrl;
    CUiButton m_delimiter4Ctrl;
    CUiButton m_delimiter5Ctrl;
    //������ť
    CUiButton m_operation1Ctrl;
    CUiButton m_operation1RightCtrl;
    CUiButton m_operation2Ctrl;
    CUiButton m_operation3Ctrl;
    CUiButton m_operation4Ctrl;
    CUiButton m_operation5Ctrl;
    CUiButton m_operation6Ctrl;
    //��������
    MapMenuOperation m_operation1;
    MapMenuOperation m_operation2;
    MapMenuOperation m_operation3;
    MapMenuOperation m_operation4;
    MapMenuOperation m_operation5;
    MapMenuOperation m_operation6;
  };
}
#endif
