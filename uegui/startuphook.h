#ifndef _UEGUI_STARTUPHOOK_H
#define _UEGUI_STARTUPHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"
#include "viewwrapper.h"
#include "routewrapper.h"
#include "usuallyfile.h"
#include "ueroute/routebasic.h"

namespace UeGui
{
  class UEGUI_CLASS CStartUpHook : public CAggHook
  {
  public:
    enum StartUpHookCtrlType
    {
      StartUpHook_Begin = 0,
      StartUpHook_Background,
      StartUpHook_BackLeftBtn,
      StartUpHook_BackCenterBtn,
      StartUpHook_BackRightBtn,
      StartUpHook_BackLeftBtnIcon,
      StartUpHook_BackCenterBtnIcon,
      StartUpHook_BackRightBtnIcon,
      StartUpHook_BackLeftBtnLabel,
      StartUpHook_BackCenterBtnLabel,
      StartUpHook_BackRightBtnLabel,
      StartUpHook_BackBottom,
      StartUpHook_NotAgainBtn,
      StartUpHook_LastNaviBtn,
      StartUpHook_BackHomeBtn,
      StartUpHook_BackCompanyBtn,
      StartUpHook_CloseBtn,
      StartUpHook_End
    };

    CStartUpHook();

    virtual ~CStartUpHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \brief ��ʾ����֮ǰ������׼��
    */
    virtual void Load();
    /**
    * \brief �л�����ʱ�ͷ�����
    **/
    virtual void UnLoad();
  public:
    /*
    * �����Ƿ���Ҫ�ָ��ϴε���·��
    */
    void SetRestoreRouteState(bool value);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /*
    * �رմ���
    */
    void Close();
    /**
    * \brief ����������
    */
    void OpenSearchMenu();
    /**
    * \brief ����ʷ��¼����
    */
    void OpenHistoryRecordMenu();
    /**
    * \brief ���ܱ���Ϣ�������
    */
    void OpenAroundMenu();
    /**
    * \brief �ظ�·��
    */
    void RestoreRote();
    /**
    * \brief �ؼ�
    */
    void BackHome();
    /**
    * \brief �ص�λ
    */
    void BackCompany();
    /**
    * \brief ָ��Ŀ�ĵ���·�߹滮
    */
    void DoRoutePlan(CGeoPoint<long>& endPos);
  private:
    //����
    CUiButton m_background;
    //�ر�
    CUiButton m_close;
    //����
    CUiBitButton m_searchBtn;
    //��ʷ��¼
    CUiBitButton m_historyRecord;
    //�ܱ�
    CUiBitButton m_around;
    //������ʾ
    CUiButton m_notAskAgain;
    //�ϴε���
    CUiButton m_lastNaigation;
    //�ؼ�
    CUiButton m_backHome;
    //�ص�λ
    CUiButton m_backCompany;
  private:
    //��ͼ��ȡ�ӿ�
    CViewWrapper &m_viewWrapper;
    //�滮ģ����ʽӿ�
    CRouteWrapper &m_routeWrapper;
    //��
    UsuallyRecord m_homePoi;    
    //��λ    
    UsuallyRecord m_companyPoi;
  };
}
#endif
