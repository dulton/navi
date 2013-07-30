#ifndef _UEGUI_MAPSIMULATIONMENUHOOK_H
#define _UEGUI_MAPSIMULATIONMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"
#include "routewrapper.h"

namespace UeGui
{
  class UEGUI_CLASS CMapSimulationMenuHook : public CAggHook
  {
  public:
    enum MapSimulationMenuHookCtrlType
    {
      MapSimulationMenuHook_Begin = 0,
      MapSimulationMenuHook_ExpandBtn,
      MapSimulationMenuHook_CloseBtn,
      MapSimulationMenuHook_SlowlyDownBtn,
      MapSimulationMenuHook_SlowlyDownLabel,
      MapSimulationMenuHook_Delimiter1,
      MapSimulationMenuHook_SpeedLevelBtn,
      MapSimulationMenuHook_SpeedLevelLabel,
      MapSimulationMenuHook_Delimiter2,
      MapSimulationMenuHook_SpeedUpBtn,
      MapSimulationMenuHook_SpeedUpLabel,
      MapSimulationMenuHook_Delimiter3,
      MapSimulationMenuHook_PauseBtn,
      MapSimulationMenuHook_PauseLabel,
      MapSimulationMenuHook_PauseBtnR,
      MapSimulationMenuHook_StopSimulationBtn,
      MapSimulationMenuHook_StopSimulationLabel,
      MapSimulationMenuHook_End
    };

    //�ٶ���Ϣ�ṹ
    struct SpeedInfo
    {
      char m_speedText[10];
      short m_speed;
    };
    typedef std::vector<SpeedInfo> SpeedInfoList;

    CMapSimulationMenuHook();

    virtual ~CMapSimulationMenuHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \���õ�ǰhook�Ƿ���ʾ
    */
    virtual void Show( bool show = true );
    /*
    * ���ø���hook
    */
    void SetParentHook(CAggHook* parentHook);
    /*
    * չ���������˵�
    */
    void ExpandMenu(bool bExpand = true);
    /*
    * ���²˵�
    */
    void Update();

    /*
    * ��ʼ��ģ�⵼����Ϣ
    */
    void ReseSimulation();
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
    * \brief ����
    */
    void SlowlyDown();
    /**
    * \brief ����
    */
    void SpeedUp();
    /**
    * \brief ���ð�ť״̬
    */
    void ResetSpeedBtnStatus();
    /**
    * \brief ���ð�ť����״̬
    */
    void ResetSpeedBtnCaption();
  private:
    CAggHook* m_parentHook;
    //չ���˵���ť
    CUiBitButton m_expandBtn;
    //�رղ˵���ť
    CUiBitButton m_closeBtn;
    //����
    CUiBitButton m_slowlyDownBtn;
    //��ǰ�ٶ�
    CUiBitButton m_speedLevelBtn;
    //����
    CUiBitButton m_speedUpBtn;
    //��ͣ
    CUiBitButton m_pauseBtn;
    //ֹͣ����
    CUiBitButton m_stopSimulation;
    //�ָ��
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
    CUiButton m_delimiter3;
    //·���滮���ʽӿ�
    CRouteWrapper& m_routeWrapper;
    //ģ�⵼��״̬
    bool m_simulationStatus;
    //ģ�⵼���ٶ�����ֵ
    char m_speedIndex;
    SpeedInfoList m_speedList;
    //�˵�״̬
    bool m_expandStatus;
  };
}
#endif
