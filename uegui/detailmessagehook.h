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
    * \brief 显示界面之前的数据准备
    */
    virtual void Load();

    /**
    * \brief 切换界面时释放数据
    **/
    virtual void UnLoad();

    /**
    * \brief 设置数据
    **/
    void SetDetailInfoData(const DetailInfo& data);
  public:
    /**
    * \brief 常用点保存回调函数
    **/
    static void OnSaveUsuallyRecord(CAggHook* sender, ModalResultType modalResult);
    /**
    * \brief 保存常用点数据
    **/
    int SaveUsuallyRecord(UsuallyRecordType type);
    /**
    * \brief 读取要保存的常用点类型
    **/
    UsuallyRecordType GetUsuallyRecordType();
  protected:

    virtual void MakeNames();

    void MakeControls();

  private:
    //保存数据到地址簿
    void SaveToAddressBook();
    //保存到常用点
    void SaveToUsuallyRecord(UsuallyRecordType type);
    //读取提示消息
    const char* GetUsuallyRecordMsgInfo(UsuallyRecordType type);
    //读取提示消息
    const char* GetUsuallyRecordMsgInfo2(UsuallyRecordType type);
    //设为开机位置
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
    //详情信息
    DetailInfo m_detailInfo;
    //Q码
    unsigned short m_QCode[QCODE_LENGTH];
    //用户数据接口
    const CUserDataWrapper& m_userDataWrapper;
    //要保存的常用点类型
    UsuallyRecordType m_saveUsuallyRecordType;
  };
}
#endif
