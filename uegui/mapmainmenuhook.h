/*
* �ǵ�������ʵ����ʱ�Ĳ˵�����
*/
#ifndef _UEGUI_MAPMAINMENUHOOK_H
#define _UEGUI_MAPMAINMENUHOOK_H

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

namespace UeGui
{
  class UEGUI_CLASS CMapMainMenuHook : public CAggHook
  {
  public:
    enum MapMainMenuHookCtrlType
    {
      MapMainMenuHook_Begin = 0,
      MapMainMenuHook_ExpandBtn,
      MapMainMenuHook_CloseBtn,
      MapMainMenuHook_FunctionBtn,
      MapMainMenuHook_FunctionLabel,
      MapMainMenuHook_Delimiter1,
      MapMainMenuHook_ShortcutBtn,
      MapMainMenuHook_ShortcutLabel,
      MapMainMenuHook_Delimiter2,
      MapMainMenuHook_AroundBtn,
      MapMainMenuHook_AroundLabel,
      MapMainMenuHook_Delimiter3,
      MapMainMenuHook_SearchBtn,
      MapMainMenuHook_SearchIcon,
      MapMainMenuHook_SearchLabel,
      MapMainMenuHook_SearchBtnR,
      MapMainMenuHook_StopGuideBtn,
      MapMainMenuHook_StopGuideLabel,
      MapMainMenuHook_RouteBtn,
      MapMainMenuHook_RouteLabel,
      MapMainMenuHook_End
    };

    CMapMainMenuHook();

    virtual ~CMapMainMenuHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();
    /**
    * \���õ�ǰhook�Ƿ���ʾ
    */
    virtual void Show( bool show = true );
    /**
    * \brief ����Hook
    */
    virtual void Update(short type);
    /*
    * ���ø���hook
    */
    void SetParentHook(CAggHook* parentHook);
    /*
    * չ���������˵�
    */
    void ExpandMenu(bool bExpand = true);
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
    // ��hook
    CAggHook* m_parentHook;
    //չ���˵���ť
    CUiBitButton m_expandBtn;
    //�رղ˵���ť
    CUiBitButton m_closeBtn;
    //����
    CUiBitButton m_functionBtn;
    //���
    CUiBitButton m_shortcutBtn;
    //�ܱ�
    CUiBitButton m_aroundBtn;
    //����
    CUiBitButton m_searchBtn;
    //ֹͣ����
    CUiBitButton m_stopGuide;
    //·�߲���
    CUiBitButton m_routeOpe;
    //�ָ��
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
    CUiButton m_delimiter3;
  private:
    //��ͼ���ʽӿ�
    CViewWrapper& m_viewWrapper;
    //·���滮���ʽӿ�
    CRouteWrapper& m_routeWrapper;
    //�˵�״̬
    bool m_expandStatus;
  };
}
#endif
