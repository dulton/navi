#ifndef _UEGUI_DETAILMESSAGEHOOK_H
#define _UEGUI_DETAILMESSAGEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "userdatawrapper.h"
#include "menubackgroundhook.h"
#include "guibasic.h"
#include "uilabel.h"
#include "uibutton.h"

namespace UeGui
{
  class UEGUI_CLASS CDetailMessageHook : public CMenuBackgroundHook
  {
  public:
    enum DetailMessageHookCtrlType
    {
      DetailMessageHook_Begin = MenuBackgroundHook_End,
      DetailMessageHook_TitleLabel,
      DetailMessageHook_AddressLabel,
      DetailMessageHook_AddressInfoLabel,
      DetailMessageHook_PhoneLabel,
      DetailMessageHook_PhoneInfoLabel,
      DetailMessageHook_CodeLabel,
      DetailMessageHook_CodeInfoLabel,
      DetailMessageHook_SaveLabel,
      DetailMessageHook_Home,
      DetailMessageHook_Company,
      DetailMessageHook_FavoratePosition1,
      DetailMessageHook_FavoratePosition2,
      DetailMessageHook_FavoratePosition3,
      DetailMessageHook_AvoidArea,
      DetailMessageHook_BootPosition,
      DetailMessageHook_AddressBook,
      DetailMessageHook_End
    };
    enum CommonPointType
    {
      CT_None = 0,
      CT_HOME,
      CT_COMPANY,
      CT_POINTONE,
      CT_POINTTWO,
      CT_POINTTHREE,
      CT_End,
    };

    CDetailMessageHook();

    virtual ~CDetailMessageHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    /**
    * \brief ��ʾ����֮ǰ������׼��
    */
    virtual void Load();

    /**
    * \brief �л�����ʱ�ͷ�����
    **/
    virtual void UnLoad();

    /**
    * \brief ��������
    **/
    void SetDetailInfoData(const DetailInfo& data);
  protected:

    virtual void MakeNames();

    void MakeControls();

  private:
    //�������ݵ���ַ��
    void SaveToAddressBook();
    //���浽���õ�
    void SaveToCommonPoint(short pointType);
    //��Ϊ����λ��
    void SaveToSysStartPosition();
  private:
    CUiLabel m_titleLabel;
    CUiLabel m_addressInfoLabel;
    CUiLabel m_phoneInfoLabel;
    CUiLabel m_codeInfoLabel;
    CUiButton m_addressBookBtn;
    CUiButton m_homeBtn;
    CUiButton m_companyBtn;
    CUiButton m_favoratePosition1Btn;
    CUiButton m_favoratePosition2Btn;
    CUiButton m_favoratePosition3Btn;
    CUiButton m_avoidAreaBtn;
    CUiButton m_bootPositionBtn;
    //������Ϣ
    DetailInfo m_detailInfo;
    //�û����ݽӿ�
    const CUserDataWrapper& m_userDataWrapper;
    //CUsuallyFile m_cFile;
  };
}
#endif
