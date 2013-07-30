#ifndef _UEGUI_DETAILMESSAGEHOOK_H
#define _UEGUI_DETAILMESSAGEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#ifndef __Q_CODE_H__
#include "QCode.h"
#pragma comment(lib,"QCode.lib")
#endif

#include "uibutton.h"
#include "usuallyfile.h"

namespace UeGui
{
  class UEGUI_CLASS CDetailMessageHook : public CAggHook
  {
  public:
    enum CommonType
    {
      CT_begin=0,
      CT_HOME,
      CT_COMPANY,
      CT_ONE,
      CT_TWO,
      CT_THREE,
      CT_End,
    };
    enum DetailMessageHookCtrlType
    {
      DetailMessageHook_Begin = 0,
      DetailMessageHook_AddressInfoLabel,
      DetailMessageHook_AddressLabel,
      DetailMessageHook_BlackGround,
      DetailMessageHook_CommonlyUsed1,
      DetailMessageHook_CommonlyUsed1Left,
      DetailMessageHook_CommonlyUsed1Right,
      DetailMessageHook_CommonlyUsed2,
      DetailMessageHook_CommonlyUsed2Left,
      DetailMessageHook_CommonlyUsed2Right,
      DetailMessageHook_CommonlyUsed3,
      DetailMessageHook_CommonlyUsed3Left,
      DetailMessageHook_CommonlyUsed3Right,
      DetailMessageHook_Company,
      DetailMessageHook_CompanyLeft,
      DetailMessageHook_CompanyRight,
      //һ����ʾ
      DetailMessageHook_HeadInfoLabel,
      //������ʾ
      DetailMessageHook_HeadInfoLabel1,
      DetailMessageHook_HeadInfoLabel2,
      DetailMessageHook_Home,
      DetailMessageHook_HomeLeft,
      DetailMessageHook_HomeRight,
      DetailMessageHook_QCodeInfoLabel,
      DetailMessageHook_QCodeLabel,
      DetailMessageHook_SaveInfo,
      DetailMessageHook_SaveInfoLeft,
      DetailMessageHook_SaveInfoRight,
      DetailMessageHook_SetCommonlyUsed,
      DetailMessageHook_SetCommonlyUsedLeft,
      DetailMessageHook_SetCommonlyUsedRight,
      DetailMessageHook_TelephoneInfoLabel,
      DetailMessageHook_TelephoneLabel,
      DetailMessageHook_MessageBoxBtn,
      DetailMessageHook_MessageBoxText,
      DetailMessageHook_RejectCtrlCenter,
      DetailMessageHook_RejectCtrlLeft,
      DetailMessageHook_RejectCtrlRight,
      DetailMessageHook_AcceptCtrlCenter,
      DetailMessageHook_AcceptCtrlLeft,
      DetailMessageHook_AcceptCtrlRight,
      DetailMessageHook_IconTip,
      DetailMessageHook_End
    };

    CDetailMessageHook();

    virtual ~CDetailMessageHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Init();

    //��ʱ��
    virtual void Timer();
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();

  private:

    CUiButton m_commonlyUsed1Ctrl;
    CUiButton m_commonlyUsed2Ctrl;
    CUiButton m_commonlyUsed3Ctrl;
    CUiButton m_companyCtrl;
    CUiButton m_homeCtrl;

    CUiButton m_addressInfoLabelCtrl;
    CUiButton m_telephoneInfoLabelCtrl;
    CUiButton m_qCodeInfoLabelCtrl;

    CUiButton m_saveInfoCtrl;
    CUiButton m_setCommonlyUsedCtrl;
    
    CUiBitButton m_messageBoxBtnCtrl;
    CUiButton m_messageBoxTextCtrl;
    CUiButton m_rejectCtrl;
    CUiButton m_acceptCtrl;

  public:
    typedef struct DetailInfo
    {
      //����
      char name[256];
      //��ַ
      char address[1024];
      //�绰
      char telephone[256];
      //λ����Ϣ
      CGeoPoint<long> position;
    } stDetailInfo;

    //��Ϣ
    stDetailInfo m_detailInfo;
    void SetDetailInfo(stDetailInfo* pDetailInfo);

    void AsMsgBox(stDetailInfo detailInfo);
  private:
    /**
    * \brief ���ó��õ�ģ�������
    */
    void SetCommonlyUsedVisiable(bool isVisiabled);
    /**
    * \brief ���ñ������ģ�������
    */
    void SetSaveControlVisiable(bool isVisiabled);

    void SetDetailEditHookDate();

    bool SetMessageVisble(bool value,CommonType type);

    bool IsCommonExist(CommonType type);

    void SetFavoFileContent(CommonType type);

    CommonType m_cType;

    CUsuallyFile m_cFile;

    double dX;
    double dY;
    unsigned short pCode[9];
    int nCode;

    //�Ƿ���Ҫ��ʱ
    bool needCountDown;
    //����ʱֵ
    int m_statusBarTimeInterval;
    const static int STATUSBAR_TIMEINTERVAL = 6; //��λ��
  };
}
#endif
