#ifndef _UEGUI_COMPORTSETTINGHOOK_H
#define _UEGUI_COMPORTSETTINGHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
#include "uiradiobutton.h"

namespace UeGui
{
  class UEGUI_CLASS CCOMPortSettingHook : public CAggHook
  {
  public:
    enum COMPortSettingHookCtrlType
    {
      COMPortSettingHook_Begin = 0,
      COMPortSettingHook_BackGround,
      COMPortSettingHook_ViewMap,
      COMPortSettingHook_Previous,
      COMPortSettingHook_Title,
      COMPortSettingHook_COMPortLabel,
      COMPortSettingHook_COMLeft,
      COMPortSettingHook_COMLeftIcon,
      COMPortSettingHook_COMLeftIconBack,
      COMPortSettingHook_COMPort,
      COMPortSettingHook_COMRight,
      COMPortSettingHook_COMRightIcon,
      COMPortSettingHook_COMRightIconBack,
      COMPortSettingHook_BaudRateLabel,
      COMPortSettingHook_BaudRateLeft,
      COMPortSettingHook_BaudRateLeftIcon,
      COMPortSettingHook_BaudRateLeftIconBack,
      COMPortSettingHook_BaudRate,
      COMPortSettingHook_BaudRateRight,
      COMPortSettingHook_BaudRateRightIcon,
      COMPortSettingHook_BaudRateRightIconBack,
      COMPortSettingHook_CodeStartLeft,
      COMPortSettingHook_ColdStartCenter,
      COMPortSettingHook_CodeStartRight,
      COMPortSettingHook_ColdStartIcon,
      COMPortSettingHook_ColdStartLabel,
      COMPortSettingHook_WarmStartLeft,
      COMPortSettingHook_WarmStartCenter,
      COMPortSettingHook_WarmStartRight,
      COMPortSettingHook_WarmStartIcon,
      COMPortSettingHook_WarmStartLabel,
      COMPortSettingHook_NormalStartLeft,
      COMPortSettingHook_NormalStartCenter,
      COMPortSettingHook_NormalStartRight,
      COMPortSettingHook_NormalStartIcon,
      COMPortSettingHook_NormalStartLabel,
      COMPortSettingHook_End
    };

    CCOMPortSettingHook();

    virtual ~CCOMPortSettingHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Load();

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    void OpenMapHook();
    void DoReturn();
    /// ��ȡ����
    void ReadSettings();
    /// ����������Ϣ
    void UpdateSettings();
    //���ݶ˿ں��Ҷ˿�����
    unsigned int FinCOMPortIndex(unsigned char port);
    //���ݲ������Ҳ���������
    unsigned int FinBaudRateIndex(unsigned int baudRate);
    //����COM��
    void SetCOMPort(unsigned char port);
    //���ò�����
    void SetBaudRate(unsigned int baudRate);
    //���ö˿�ѡ��ؼ�״̬
    void SetCOMPortCtrlStatus();
    //���ò�����ѡ��ؼ�״̬
    void SetBaudRateCtrlStatus();
  private:
    bool m_isEdit;
    unsigned int m_COMIndex;
    unsigned int m_baudRateIndex;
    std::vector<unsigned char> m_COMPortList;
    std::vector<unsigned int> m_baudRateList;

    CUiBitButton m_previousCtrl;
    CUiBitButton m_viewMapCtrl;   

    CUiButton m_COMPortCtrl;
    CUiBitButton m_COMLeftCtrl;
    CUiBitButton m_COMRightCtrl;

    CUiButton m_baudRateCtrl;
    CUiBitButton m_baudRateLeftCtrl;
    CUiBitButton m_baudRateRightCtrl;

    CUiRadioButton m_codeStartCtrl;
    CUiRadioButton m_warmStartCtrl;
    CUiRadioButton m_normalStartCtrl;
  };
}
#endif
