#ifndef _UEGUI_INPUTSPELLINGHOOK_H
#define _UEGUI_INPUTSPELLINGHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

#define INPUTCODENUM 26
#define ASSOCIATEBTNNUM 6
#define MAXWORDNUM 20

namespace UeGui
{
  class UEGUI_CLASS CInputSpellingHook : public CMenuBackgroundHook
  {
  public:
    enum InputSpellingHookCtrlType
    {
      InputSpellingHook_Begin = MenuBackgroundHook_End,
      InputSpellingHook_CharBack,
      InputSpellingHook_InputCode1,
      InputSpellingHook_InputCode2,
      InputSpellingHook_InputCode3,
      InputSpellingHook_InputCode4,
      InputSpellingHook_InputCode5,
      InputSpellingHook_InputCode6,
      InputSpellingHook_InputCode7,
      InputSpellingHook_InputCode8,
      InputSpellingHook_InputCode9,
      InputSpellingHook_InputCode10,
      InputSpellingHook_InputCode11,
      InputSpellingHook_InputCode12,
      InputSpellingHook_InputCode13,
      InputSpellingHook_InputCode14,
      InputSpellingHook_InputCode15,
      InputSpellingHook_InputCode16,
      InputSpellingHook_InputCode17,
      InputSpellingHook_InputCode18,
      InputSpellingHook_InputCode19,
      InputSpellingHook_InputCode20,
      InputSpellingHook_InputCode21,
      InputSpellingHook_InputCode22,
      InputSpellingHook_InputCode23,
      InputSpellingHook_InputCode24,
      InputSpellingHook_InputCode25,
      InputSpellingHook_InputCode26,
      InputSpellingHook_InputSwitchBtn,
      InputSpellingHook_InputSwitchBtnIcon,
      InputSpellingHook_PageLeftBtn,
      InputSpellingHook_AssociateBtn1,
      InputSpellingHook_AssociateBtn2,
      InputSpellingHook_AssociateBtn3,
      InputSpellingHook_AssociateBtn4,
      InputSpellingHook_AssociateBtn5,
      InputSpellingHook_AssociateBtn6,
      InputSpellingHook_PageRightBtn,
      InputSpellingHook_PageLeftBtnIcon,
      InputSpellingHook_PageRightBtnIcon,
      InputSpellingHook_PageUpIcon,
      InputSpellingHook_PageDownIcon,
      InputSpellingHook_DistSwitchBtn,
      InputSpellingHook_DistSelectBtn,
      InputSpellingHook_DistSelectBtnIcon,
      InputSpellingHook_EditBox,
      InputSpellingHook_EditSelectBtn,
      InputSpellingHook_EditSelectBtnIcon,
      InputSpellingHook_WordSeparation,
      InputSpellingHook_KeyWordBox,
      InputSpellingHook_OtherSearchBtn,
      InputSpellingHook_OtherSearchIcon,
      InputSpellingHook_DeleteBtn,
      InputSpellingHook_SearchBtn,
      InputSpellingHook_End
    };

    CInputSpellingHook();

    virtual ~CInputSpellingHook();

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

    void InitKeyBoard();

    bool EraseOneKeyWord();
    bool AddOneKeyWord(const char *pchLabelText);
    bool doAddOneKeyWord(TCHAR oneWord);
    void ClearKeyWord(void);
    void SetCursorPosX(int curIndex);

    void ShowKeyWord();

    bool GetAssociateThing();

    void SetAssociateBtnLabels();

    void SetKeyBoardBtnsEnable();

    void ResetSpellingToBtns(int chIndex);
    void ResetSpellingWordToBtns(const char *pchSpelling);
    //�жϸ�ƴ������Ƿ��ڸ������д��ڶ�Ӧ����
    bool IsKeyWordExist(const char *pchKeyWord);

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

    CUiBitButton m_returnBtn;

    int m_iCurCursorIndex;
    tstring m_tstrKeyWords;
    std::vector<int> m_vecWordPosX;
    //���ֺ���İ���
    GuiElement *m_pWordCursor;

    bool m_isWordsReady;

    //��ǰ��ʾ�����ְ�ť�ϵ���������
    int m_iCurWordIndex;
    //���浱ǰ��Ҫ��ʾ�ڰ�ť�ϵ�����
    std::vector<string> m_vecWordsBuf;

    //Ŀǰ���뵽ƴ����ϵĵڼ�����ĸ
    int m_curSpellingCursor;
    //���ڼ�¼���������ĸ��ɫ
    unsigned char m_posBuffer[10];
    //��������poi��·���õĹؼ���
    char m_poiKeyWord[128];
    //�������������õĹؼ���
    char m_distKeyWord[128];
    //�ж��Ƿ���������
    bool m_isAssociateExist;

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
