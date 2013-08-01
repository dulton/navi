#ifndef _UEGUI_ROUNDSELECTIONHOOK_H
#define _UEGUI_ROUNDSELECTIONHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEQUERY_CODEINDEXCTRL_H
#include "uequery/codeindexctrl.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

namespace UeGui
{
  class UEGUI_CLASS CRoundSelectionHook : public CMenuBackgroundHook
  {
  public:
    enum RoundSelectionHookCtrlType
    {
      RoundSelectionHook_Begin = MenuBackgroundHook_End,
      RoundSelectionHook_TypeSelectLeftBtn,
      RoundSelectionHook_TypeSelectRightBtn,
      RoundSelectionHook_TypeSelectBtnLabel,
      RoundSelectionHook_TypeSelectBtnIcon,
      RoundSelectionHook_List1CenterBtn,
      RoundSelectionHook_List2CenterBtn,
      RoundSelectionHook_List3CenterBtn,
      RoundSelectionHook_List4CenterBtn,
      RoundSelectionHook_List5CenterBtn,
      RoundSelectionHook_List6CenterBtn,
      RoundSelectionHook_List7CenterBtn,
      RoundSelectionHook_List8CenterBtn,
      RoundSelectionHook_List9CenterBtn,
      RoundSelectionHook_List10CenterBtn,
      RoundSelectionHook_List11CenterBtn,
      RoundSelectionHook_List12CenterBtn,
      RoundSelectionHook_End
    };

    CRoundSelectionHook();

    virtual ~CRoundSelectionHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual void Load();

    bool IsFromMap();

  protected:

    virtual void MakeNames();

    void MakeControls();

    void PutItemToList();

  private:
    CUiButton m_listBtn[12];
    CUiBitButton m_switchBtn;

    CCodeIndexCtrl *m_pCurItemCtrl;
    std::vector<TCodeEntry> m_vecListItem;
    std::vector<TCodeEntry> m_vecQueryListItem;
    //�ж��Ƿ�ӵ�ͼ����
    //�Դ���������������б���������ʾ��ͼ�����ܱ߻��ǵ�ǰλ���ܱ�
    bool m_isFromMap;
    //���ڼ�¼���÷���ĸ���, ���11��, ���һ���� ������� ��ť
    int m_comSize;
  };
}
#endif
