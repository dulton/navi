#ifndef _UEGUI_MAPQUERYMENUHOOK_H
#define _UEGUI_MAPQUERYMENUHOOK_H

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

namespace UeGui
{
  class UEGUI_CLASS CMapQueryMenuHook : public CAggHook
  {
  public:
    enum MapQueryMenuHookCtrlType
    {
      MapQueryMenuHook_Begin = 0,
      MapQueryMenuHook_ExpandBtn,
      MapQueryMenuHook_CloseBtn,
      MapQueryMenuHook_PreviousBtn,
      MapQueryMenuHook_PreviousLabel,
      MapQueryMenuHook_Delimiter1,
      MapQueryMenuHook_BackBtn,
      MapQueryMenuHook_BackLabel,
      MapQueryMenuHook_Delimiter2,
      MapQueryMenuHook_NextBtn,
      MapQueryMenuHook_NextLabel,
      MapQueryMenuHook_Delimiter3,
      MapQueryMenuHook_AroundBtn,
      MapQueryMenuHook_AroundIcon,
      MapQueryMenuHook_AroundLabel,
      MapQueryMenuHook_AroundBtnR,
      MapQueryMenuHook_ReturnBtnBack,
      MapQueryMenuHook_ReturnBtnIcon,
      MapQueryMenuHook_SelectPointBack,
      MapQueryMenuHook_SelectPointLabel,
      MapQueryMenuHook_End
    };
    //��ѯ�˵���������
    enum QueryMenuType
    {
      QMenu_QueryPoint,  //��ѯ�����
      QMenu_SelectPoint, //ѡ����棬 ���õ�ѡ��
      QMenu_SelectArea   //ѡ������
    };
  public:
    CMapQueryMenuHook();

    virtual ~CMapQueryMenuHook();

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
    * ���õ�ǰ�˵���ѯ����
    */
    void SetMenuType(QueryMenuType menuType);
    /*
    * չ���������˵�
    */
    void ExpandMenu(bool bExpand = true);
    /*
    * ���²˵�
    */
    void Update();
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /**
    * \brief ��λ��ָ����ѯ��λ��
    */
    void SetQueryPos(short posType);
    /**
    * \brief ���ð�ť״̬
    */
    void ResetQueryBtnStatus();
  private:
    //��ǰ��ѯ��������
    QueryMenuType m_menuType;
    // ��hook
    CAggHook* m_parentHook;
    //չ���˵�
    CUiButton m_expandBtn;
    //�رղ˵�
    CUiButton m_closeBtn;
    //��һ��
    CUiBitButton m_previousBtn;
    //��һ��
    CUiBitButton m_nextBtn;
    //��ԭλ
    CUiBitButton m_backBtn;
    //�ܱ�
    CUiBitButton m_aroundBtn;
    //����
    CUiBitButton m_returnBtn;
    //ѡ���趨
    CUiBitButton m_selectPointBtn;
    //�ָ���
    CUiButton m_delimiter1;
    CUiButton m_delimiter2;
    CUiButton m_delimiter3;
    //�˵�״̬
    bool m_expandStatus;
  };
}
#endif
