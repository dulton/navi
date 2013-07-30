#ifndef _UEGUI_TRUCKMAINMENUHOOK_H
#define _UEGUI_TRUCKMAINMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CTruckMainMenuHook : public CAggHook
  {
  public:
    enum TruckMainMenuHookCtrlType
    {
      TruckMainMenuHook_Begin = 0,

      TruckMainMenuHook_Background,
      TruckMainMenuHook_ViewMap,
      TruckMainMenuHook_ViewPrevious,
      TruckMainMenuHook_NavigationTitle,
      TruckMainMenuHook_VehicleInformation,
      TruckMainMenuHook_VehicleInformationLabel,
      TruckMainMenuHook_FleetManagement,
      TruckMainMenuHook_FleetManagementLabel,
      TruckMainMenuHook_ViewSupply,
      TruckMainMenuHook_ViewSupplyLabel,
      TruckMainMenuHook_LogisticsTracking,
      TruckMainMenuHook_LogisticsTrackingLabel,
      TruckMainMenuHook_ViewPickingStation,
      TruckMainMenuHook_ViewPickingStationLabel,
      TruckMainMenuHook_ViewLogisticsCenter,
      TruckMainMenuHook_ViewLogisticsCenterLabel,
      TruckMainMenuHook_ViewParking,
      TruckMainMenuHook_ViewParkingLabel,
      TruckMainMenuHook_ViewWaterStations,
      TruckMainMenuHook_ViewWaterStationsLabel,

      TruckMainMenuHook_End
    };

    CTruckMainMenuHook();

    virtual ~CTruckMainMenuHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    /**
    * \brief ��ʾ������Ϣ
    */
    void ShowVehicleInformation();
    /**
    /**
    * \brief ��ʾ���ӹ���
    */
    void ShowFleetManagement();
        /**
    * \brief ��ʾ��Դ��Ϣ
    */
    void ShowViewSupply();
    /**
    /**
    * \brief ��ʾ��������
    */
    void ShowLogisticsTracking();
        /**
    * \brief ��ʾ���վ��Ϣ
    */
    void ShowPickingStation();
    /**
    /**
    * \brief ��ʾ����������Ϣ
    */
    void ShowLogisticsCenter();
        /**
    * \brief ��ʾͣ������Ϣ
    */
    void ShowParking();
    /**
    /**
    * \brief ��ʾ��ˮվ��Ϣ
    */
    void ShowWaterStations();

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

  private:
    //���ص�ͼ
    CUiButton m_viewMapCtrl;
    //����ǰһ����
    CUiButton m_viewPreviousCtrl;
    //������Ϣ
    CUiButton m_vehicleInformation;
    //���ӹ���
    CUiButton m_fleetManagement;
    //�鿴��Դ
    CUiButton m_viewSupply;
    //��������
    CUiButton m_logisticsTracking;
    //�鿴���վ
    CUiButton m_viewPickingStation;
    //�鿴��������
    CUiButton m_viewLogisticsCenter;
    //�鿴ͣ����
    CUiButton m_viewParking;
    //�鿴��ˮվ
    CUiButton m_viewWaterStations;
  };
}
#endif

