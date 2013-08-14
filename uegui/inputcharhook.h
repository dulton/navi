#ifndef _UEGUI_INPUTCHARHOOK_H
#define _UEGUI_INPUTCHARHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

#define INPUTCODENUM 24
#define ASSOCIATEBTNNUM 6
#define MAXWORDNUM 20

namespace UeGui
{
  class UEGUI_CLASS CInputCharHook : public CMenuBackgroundHook
  {
  public:
    enum InputCharHookCtrlType
    {
      InputCharHook_Begin = MenuBackgroundHook_End,
      InputCharHook_CharBack,
      InputCharHook_InputCode1,
      InputCharHook_InputCode2,
      InputCharHook_InputCode3,
      InputCharHook_InputCode4,
      InputCharHook_InputCode5,
      InputCharHook_InputCode6,
      InputCharHook_InputCode7,
      InputCharHook_InputCode8,
      InputCharHook_InputCode9,
      InputCharHook_InputCode10,
      InputCharHook_InputCode11,
      InputCharHook_InputCode12,
      InputCharHook_InputCode13,
      InputCharHook_InputCode14,
      InputCharHook_InputCode15,
      InputCharHook_InputCode16,
      InputCharHook_InputCode17,
      InputCharHook_InputCode18,
      InputCharHook_InputCode19,
      InputCharHook_InputCode20,
      InputCharHook_InputCode21,
      InputCharHook_InputCode22,
      InputCharHook_InputCode23,
      InputCharHook_InputCode24,
      InputCharHook_PageUpBtn,
      InputCharHook_PageDownBtn,
      InputCharHook_InputSwitchBtn,
      InputCharHook_InputSwitchBtnIcon,
      InputCharHook_PageLeftBtn,
      InputCharHook_AssociateBtn1,
      InputCharHook_AssociateBtn2,
      InputCharHook_AssociateBtn3,
      InputCharHook_AssociateBtn4,
      InputCharHook_AssociateBtn5,
      InputCharHook_AssociateBtn6,
      InputCharHook_PageRightBtn,
      InputCharHook_PageLeftBtnIcon,
      InputCharHook_PageRightBtnIcon,
      InputCharHook_PageUpIcon,
      InputCharHook_PageDownIcon,
      InputCharHook_DistSwitchBtn,
      InputCharHook_DistSelectBtn,
      InputCharHook_DistSelectBtnIcon,
      InputCharHook_EditBox,
      InputCharHook_EditSelectBtn,
      InputCharHook_EditSelectBtnIcon,
      InputCharHook_WordSeparation,
      InputCharHook_KeyWordBox,
      InputCharHook_OtherSearchBtn,
      InputCharHook_OtherSearchIcon,
      InputCharHook_DeleteBtn,
      InputCharHook_SearchBtn,
      InputCharHook_End
    };

    CInputCharHook();

    virtual ~CInputCharHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    void ResetKeyWord(const char *pchKeyWord);

    char* GetKeyWord();

    void SetKeyWord(char* keyword);

    void SetQueryMode();

  protected:

    virtual void Load();

    virtual void UnLoad();

    virtual void Init();

    virtual void MakeNames();

    void MakeControls();

    void SetKeyBoard();

    bool EraseOneKeyWord();
    bool AddOneKeyWord(const char *pchLabelText);
    bool doAddOneKeyWord(TCHAR oneWord);
    void ClearKeyWord(void);
    void SetCursorPosX(int curIndex);

    void ShowKeyWord();

    bool GetAssociateThing();

    void SetAssociateBtnLabels();

  private:
    static void DistSwitchCallBack(void *pDoCallBackObj, const SQLRecord *pResult);

    void DoDistSwitchCallBack(const SQLRecord *pResult);

    static void InputSelectCallBack(void *pDoCallBackObj, char *keyword);

    void DoInputSelectCallBack(char *keyword);

  private:
    CUiButton m_distSwitchBtn;
    CUiBitButton m_distSelectBtn;
    CUiBitButton m_editSelectBtn;
    CUiLabel m_keyWordBox;
    CUiBitButton m_otherSearchBtn;
    CUiButton m_searchBtn;
    CUiButton m_deleteBtn;
    CUiBitButton m_inputSwitchBtn;

    CUiButton m_inputCode[INPUTCODENUM];
    CUiButton m_associateBtn[ASSOCIATEBTNNUM];
    CUiBitButton m_pageLeftBtn;
    CUiBitButton m_pageRightBtn;
    CUiBitButton m_pageUpBtn;
    CUiBitButton m_pageDownBtn;

    CUiBitButton m_returnBtn;

    int m_iCurCursorIndex;
    tstring m_tstrKeyWords;
    std::vector<int> m_vecWordPosX;
    //���ֺ���İ���
    GuiElement *m_pWordCursor;

    //��ǰ��ʾ�����ְ�ť�ϵ���������
    int m_iCurWordIndex;
    //��ǰ��ʾ�ڼ��̰�ť�ϵ���������
    int m_iCurCodeIndex;
    //���浱ǰ��Ҫ��ʾ�ڰ�ť�ϵ�����
    std::vector<string> m_vecWordsBuf;
    //���浱ǰ��Ҫ��ʾ�ڼ����ϵ�����
    std::vector<string> m_vecCodesBuf;
    //��������poi��·���õĹؼ���
    char m_poiKeyWord[128];
    //�������������õĹؼ���
    char m_distKeyWord[128];

    //�ؼ��ֹ�����ʾ��ȫʱ, ��ʶ�ӵڼ����ֿ�ʼ��ʾ
    int m_wordPosOffset;
    //���ڱ����ȡ��������ʾ���ַ���
    tstring m_cutKeyWords;
    //��¼�ؼ���������ԭʼλ��
    int m_orinBoxPos;
    //�������ƶ��������λ��
    int m_limitPoxX;
    //��¼��ǰ�Ƿ���ʾ�����Ĺؼ���
    bool m_isShowFullKeyWords;
  };
}
#endif
