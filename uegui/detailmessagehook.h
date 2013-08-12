#ifndef _UEGUI_DETAILMESSAGEHOOK_H
#define _UEGUI_DETAILMESSAGEHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef __Q_CODE_H__
#include "QCode.h"
#pragma comment(lib, "QCode.lib")
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
    const static int QCODE_LENGTH = 9;
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
  public:
    /**
    * \brief ���õ㱣��ص�����
    **/
    static void OnSaveUsuallyRecord(CAggHook* sender, ModalResultType modalResult);
    /**
    * \brief ���泣�õ�����
    **/
    int SaveUsuallyRecord(UsuallyRecordType type);
    /**
    * \brief ��ȡҪ����ĳ��õ�����
    **/
    UsuallyRecordType GetUsuallyRecordType();
  protected:

    virtual void MakeNames();

    void MakeControls();

  private:
    //�������ݵ���ַ��
    void SaveToAddressBook();
    //���浽���õ�
    void SaveToUsuallyRecord(UsuallyRecordType type);
    //��ȡ��ʾ��Ϣ
    const char* GetUsuallyRecordMsgInfo(UsuallyRecordType type);
    //��ȡ��ʾ��Ϣ
    const char* GetUsuallyRecordMsgInfo2(UsuallyRecordType type);
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
    //Q��
    unsigned short m_QCode[QCODE_LENGTH];
    //�û����ݽӿ�
    const CUserDataWrapper& m_userDataWrapper;
    //Ҫ����ĳ��õ�����
    UsuallyRecordType m_saveUsuallyRecordType;
  };
}
#endif
