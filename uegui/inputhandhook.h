#ifndef _UEGUI_INPUTHANDHOOK_H
#define _UEGUI_INPUTHANDHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#include "menubackgroundhook.h"

//#include "uilabel.h"
#include "uibutton.h"
//#include "uiradiobutton.h"
//#include "uicheckbutton.h"

#define INPUTCODENUM 10

namespace UeGui
{
  class UEGUI_CLASS CInputHandHook : public CMenuBackgroundHook
  {
  public:
    enum InputHandHookCtrlType
    {
      InputHandHook_Begin = MenuBackgroundHook_End,
      InputHandHook_CharBack,
      InputHandHook_InputCode1,
      InputHandHook_InputCode2,
      InputHandHook_InputCode3,
      InputHandHook_InputCode4,
      InputHandHook_InputCode5,
      InputHandHook_InputCode6,
      InputHandHook_InputCode7,
      InputHandHook_InputCode8,
      InputHandHook_InputCode9,
      InputHandHook_InputCode10,
      InputHandHook_WrittingArea,
      InputHandHook_WriteBackShade,
      InputHandHook_PageUpIcon,
      InputHandHook_PageDownIcon,
      InputHandHook_DistSwitchBtn,
      InputHandHook_DistSelectBtn,
      InputHandHook_PageUpBtn,
      InputHandHook_DistSelectBtnIcon,
      InputHandHook_PageDownBtn,
      InputHandHook_EditBox,
      InputHandHook_EditSelectBtn,
      InputHandHook_EditSelectBtnIcon,
      InputHandHook_KeyWordBox,
      InputHandHook_WordSeparation,
      InputHandHook_OtherSearchBtn,
      InputHandHook_InputSwitchBtn,
      InputHandHook_OtherSearchIcon,
      InputHandHook_InputSwitchBtnIcon,
      InputHandHook_DeleteBtn,
      InputHandHook_SearchBtn,
      InputHandHook_End
    };

    CInputHandHook();

    virtual ~CInputHandHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    void ResetKeyWord(const char *pchKeyWord);

    char* GetKeyWord();

    void SetQueryMode();

    //ʵʱ�жϵ�ǰ����д����
    void DoHandWriting(int curTime);

  protected:

    virtual void Load();

    virtual void Init();

    virtual void UnLoad();

    virtual void MakeNames();

    void MakeControls();

    bool EraseOneKeyWord();
    bool AddOneKeyWord(const char *pchLabelText);
    bool doAddOneKeyWord(TCHAR oneWord);
    void ClearKeyWord(void);
    void SetCursorPosX(int curIndex);

    bool GetAssociateThing();

    void SetAssociateBtnLabels();

  private:
    //��ʼ����д����
    static void InitHandWriting();
    //�ͷ���д������Դ
    static void UninitHandWriting();

    static void DistSwitchCallBack(void *pDoCallBackObj, const SQLRecord *pResult);

    void DoDistSwitchCallBack(const SQLRecord *pResult);

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
    CUiBitButton m_pageDownBtn;
    CUiBitButton m_pageUpBtn;

    int m_iCurCursorIndex;
    tstring m_tstrKeyWords;
    std::vector<int> m_vecWordPosX;
    //���ֺ���İ���
    GuiElement *m_pWordCursor;

    //��ǰ��ʾ�����ְ�ť�ϵ���������
    int m_iCurWordIndex;
    //���浱ǰ��Ҫ��ʾ�ڰ�ť�ϵ�����
    std::vector<string> m_vecWordsBuf;

    GuiElement *m_pWrittingArea;

    //��Ϊ���е���д��Ļһ�����Ҳ���ͬʱ����
    // Handwriting library
    //��д�����ֿ�
    static unsigned char *m_hwAddress;
    //����������д����ʱ�ĵ�����
    static short *m_writingPts;
    //���������Ļ����С
    static short m_writingNum;
    //��ǰ���Ա���������±�
    static short m_writingCursor;
    //
    bool m_isNewChar;
    int m_writingTime;
    short m_prevX;
    short m_prevY;
    bool m_isWriting;

    HPEN m_pen;
    HPEN m_oldPen;
    HDC m_renderingDC;
  };
}
#endif
