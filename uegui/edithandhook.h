#ifndef _UEGUI_EDITHANDHOOK_H
#define _UEGUI_EDITHANDHOOK_H

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
  class UEGUI_CLASS CEditHandHook : public CMenuBackgroundHook
  {
  public:
    enum EditHandHookCtrlType
    {
      EditHandHook_Begin = MenuBackgroundHook_End,
      EditHandHook_CharBack,
      EditHandHook_InputCode1,
      EditHandHook_InputCode2,
      EditHandHook_InputCode3,
      EditHandHook_InputCode4,
      EditHandHook_InputCode5,
      EditHandHook_InputCode6,
      EditHandHook_InputCode7,
      EditHandHook_InputCode8,
      EditHandHook_InputCode9,
      EditHandHook_InputCode10,
      EditHandHook_WriteBack,
      EditHandHook_WriteBackShade,
      EditHandHook_PageUpIcon,
      EditHandHook_PageDownIcon,
      EditHandHook_PageUpBtn,
      EditHandHook_PageDownBtn,
      EditHandHook_SaveBtn,
      EditHandHook_InputSwitchBtn,
      EditHandHook_InputSwitchBtnIcon,
      EditHandHook_EditBox,
      EditHandHook_WordSeparation,
      EditHandHook_KeyWordBox,
      EditHandHook_DeleteBtn,
      EditHandHook_End
    };

    CEditHandHook();

    virtual ~CEditHandHook();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    void ResetKeyWord(const char *pchKeyWord);

    char* GetKeyWord();

    void SetKeyWord(char* keyword);

    void SetQueryMode();

    //ʵʱ�жϵ�ǰ����д����
    void DoHandWriting(int curTime);

  protected:

    virtual void Load();

    virtual void UnLoad();

    virtual void Init();

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

  private:
    CUiLabel m_keyWordBox;
    CUiBitButton m_otherSearchBtn;
    CUiButton m_saveBtn;
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
    //�����ַ���
    char m_keyWord[128];
    //
    bool m_isNewChar;
    int m_writingTime;
    short m_prevX;
    short m_prevY;
    bool m_isWriting;

    HPEN m_pen;
    HPEN m_oldPen;
    HDC m_renderingDC;
    //�жϵ�ǰ��׼��������Ҫ������ֻ���������һ��������
    bool m_isIdentify;
  };
}
#endif
