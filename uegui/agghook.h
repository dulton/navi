/*
* The UrbanEye PND solution is a collection of packages based on native C++ classes
* that implement the fundamental algorithms & operations required to satisfy one kind
* of mobile or portable devices with competitive qualities being a leading one.
*
* Copyright (C) 2008 Xiujie Sheng
*
* This library isn't a free software, so you cann't take the sourcecode without author's permit.
* Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
* if you illegally got it. 
*
* NOTE: 
* AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
* LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
*
* For more information, contact:
*
* China University of Geoseciences(Wuhan)
* Graduate School
*
* Xiujie Sheng
* smartpoint@sohu.com
*/

#ifndef _UEGUI_AGGHOOK_H
#define _UEGUI_AGGHOOK_H

#include "portability.h"
#include "uebase\dbgmacro.h"
using namespace UeBase;

// Refer to its parent
#ifndef _UEMAP_VIEWHOOK_H
#include "uemap\viewhook.h"
#endif

#ifndef _UEGUI_GUIBASIC_H
#include "guibasic.h"
#endif

#ifdef FOR_TRUCK
#define __FOR_TRUCK__ 1
#else
#define __FOR_TRUCK__ 0
#endif

using namespace UeMap;

// Forward class
namespace UeXml
{
  class CXmlReader;
}

// UeGui package
namespace UeGui
{
  /**
  * \brief It mainly embrace AGG some definitions for its children rendering and implement common
  * rendering process for common GUI layout
  *
  * \detail 
  * Note:
  * As far, it doesn't move some implementations of CViewHook to here and they should be here not there since
  * the intention of CViewHook is pure interface class
  **/
  #define ENDKEY 255
  #define DEFAULT_DEMOSPEED 60

  class CFocusTextElement;
  class CAggHook;
  class CUiButton;
  class CUiControl;
  typedef std::map<short, CAggHook*> AggHookMap;
  typedef std::map<short, CFocusTextElement*> FocusTextElementsMap;

  class CAggHook : public CViewHook
  {
  protected:
    /**
    * \brief XML Nodes represent different style and extent etc setting
    */
    enum XmlCtrlDef
    {
      Ctrl_Unknown = -1,
      Ctrl_StartX,
      Ctrl_StartY,
      Ctrl_Width,
      Ctrl_Height,
      Ctrl_ID,
      Ctrl_Style,
      Ctrl_Name,
      Ctrl_FillColor,
      Ctrl_BorderColor,
      Ctrl_BorderStyle,
      Ctrl_BackStyle,
      Ctrl_TextStyle,
      Ctrl_Radius,
      Ctrl_BltType,
      Ctrl_OpType,
      Ctrl_ForegroundPic,
      Ctrl_UpPic,
      Ctrl_DownPic,
      Ctrl_Visible,
      Ctrl_Max,
    };
    /// Names of each XML node
    static const string m_xmlNodes[];

  protected:
    //
    // Only be used for its children not outside
    //
    /*!
    * \brief ���캯��
    */
    CAggHook();

    /*!
    * \brief ��������
    */
    virtual ~CAggHook();
  public:
    /**
    * \brief ����GUI��Ϣ
    */
    virtual void MakeGUI();
    /**
    * \brief ��ʼ��hook��Ϣ
    */
    virtual void Init();

    /**
    * \brief ��ʾ����֮ǰ������׼��
    */
    virtual void Load();
    /**
    * \brief �л�����ʱ�ͷ�����
    **/
    virtual void UnLoad();

    /**
    * \brief ���������淵�ص�ǰ����
    */
    virtual void ComeBack();

    /**
    * \brief Render each hook in dynamic way
    */
    virtual void DynamicShow();

    /**
    *
    */
    virtual void ExcludeClipRect(void *dc);

    /**
    *
    */
    virtual void DoDraw(const CGeoRect<short> &scrExtent);

    /**
    *
    */
    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    /**
    *
    */
    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    /**
    * ��ʱ��
    **/
    virtual void Timer() {};

    /**
    * \���õ�ǰhook�Ƿ���ʾ
    */
    virtual void Show( bool show = true );
#if __FOR_FPC__
    /**
    * 
    */
    virtual void GetPhoto(TCHAR *photoName);
#endif
  public:
    /**
    * \����hook·��
    */
    static void SetPath(TCHAR* path);

    /**
    * \��ӵ�ǰhook����hook
    */
    void AddChildHook(HookType childHookType, CAggHook* aggHook);

    /**
    * \��ʾ��ǰhook����hook
    */
    void ShowChildHook(HookType childHookType, bool show = true);

    /**
    * \��ǰhook�Ƿ�����ʾ״̬
    */
    bool IsShown();

    /**
    * �����hook
    */
    void ClearChildHookList();

    /**
    * \�����Ҫ�Խ��������ɫ�Ŀؼ�
    * param elementType Ԫ������
    * fkey Ҫ��ɫ������λ����Ϣ ��ŵ��Ǳ�ɫ���ֵ������±� 0 - len-1
    */  
    bool AddFocusTextElements(short elementType, const unsigned char* fkey);

    /**
    * \�����Ҫ�Խ��������ɫ�Ŀؼ�
    * param element Ԫ��
    * fkey Ҫ��ɫ������λ����Ϣ ��ŵ��Ǳ�ɫ���ֵ������±� 0 - len-1
    */  
    bool AddFocusTextElements(GuiElement* guielement, const unsigned char* fkey);

    /**
    * \ɾ��ָ����Ҫ��ɫ��Ԫ��
    */    
    void EraseFocusTextElements(short elementType);

    /**
    * \ɾ��ָ����Ҫ��ɫ��Ԫ��
    */    
    void EraseFocusTextElements(GuiElement* guielement);

    /**
    * \�����Ҫ�Խ��������ɫ�Ŀؼ�
    */    
    void ClearFocusTextElements();
  public:
    //��ת��ĳһ��hook�Ľ���
    void TurnTo(int hookType);
    //���ص�ǰһ��hook
    void Return();
    /**
    * ���ǰһ��hook������,û���򷵻�DHT_Unknown
    */
    int GetPrevHookType();
    //���ص�ͼ�İ�ť���ã������ջ��
    void GoToMapHook();
  protected:
    //
    // GUI response functions
    //
    /**
    * ��ȡ�������ļ����ƣ�������·������:licensehook.bin
    * �÷��������ฺ��ʵ�֣��������, �ұ���ʵ�֣�����Ӧ����Ϊ���鷽������Ҫ��Ϊ��ͳһ��ȡ�������ļ�����
    */
    virtual tstring GetBinaryFileName();

    /**
    * ����XML�����ļ��е��¼����ƶ�Ӧ��ö��IC    
    * �÷��������ฺ��ʵ�֣��������, �ұ���ʵ�֣�����Ӧ����Ϊ���鷽��
    */
    virtual void MakeNames();

    /** 
    * ���ɽ���ؼ����÷��������ฺ��ʵ�֣��������
    */
    virtual void MakeControls();

    /**
    * ���½ṹ�������ļ��ж�ȡ����
    */
    virtual void FetchWithBinary();

    /**
    * \brief ���ð�ť��ʽ(���»�����״̬)
    */
    virtual void SetCursor(short type, bool isfocus = false);
    //
    // Rendering functions
    //
    /**
    * \brief Render background of each GUI hook
    *
    * \param scrExtent the current size of screen for rendering
    */
    virtual void RenderHookWindow(const CGeoRect<short> &scrExtent);

    /**
    * \brief Render GUI outlook for one specified hook, it is a template method called by Draw() function in respective children
    *
    * \param scrExtent the current size of screen for rendering
    * \param oneElement one of GUI elements of current hook which carries size etc information
    **/
    virtual void RenderHookCommands(const CGeoRect<short> &scrExtent, const CViewHook::GuiElement &oneElement, const unsigned char* fKey = NULL, bool needRelesePic = true);

    /*!
    * \brief ��XML��Դ�ļ������ɶ�Ӧ�Ľ���Ԫ��
    * TODO: �ɰ汾���룬��ɾ��
    */
    virtual void FetchExtentWithXML(UeXml::CXmlReader& xmlReader, const std::string& nodeName, GuiElement& oneElement);

    /*!
    * \brief ��XML��Դ�ļ������ɶ�Ӧ�Ľ���Ԫ������
    * TODO: �ɰ汾���룬��ɾ��
    */
    virtual void FetchAttributeWithXML(UeXml::CXmlReader& xmlReader, const std::string& nodeName, GuiElement& oneElement);

    /**
    * TODO: �ɰ汾���룬��ɾ��
    * \brief Ϊ��ǰ�������ָ���Ľ���Ԫ��
    *
    * \param eleType ָ���Ľ���Ԫ�صı�ʶ
    * \param oneElement ����Ԫ�ض���
    */
    virtual bool AddGuiElement(int eleType, GuiElement &oneElement);

    /**
    * \brief Ϊ��ǰ�������ָ���Ľ���Ԫ��
    * \param eleType ָ���Ľ���Ԫ�صı�ʶ
    * \param oneElement ����Ԫ�ض���
    */
    virtual bool AddGuiElement(GuiElement &oneElement);

    /**
    * TODO: �ɰ汾���룬��ɾ��
    * \brief ��ȡ��ǰ����ָ���Ľ���Ԫ��
    *
    * \param eleType ָ���Ľ���Ԫ�صı�ʶ
    * \param oneElement ����Ԫ�ض���
    */
    virtual void GetGuiElement(int eleType, GuiElement &oneElement);

    /**
    * TODO: �ɰ汾���룬��ɾ��
    * \brief ���µ�ǰ����ָ���Ľ���Ԫ��
    *
    * \param eleType ָ���Ľ���Ԫ�صı�ʶ
    * \param oneElement ����Ԫ�ض���
    */
    virtual void UpdateGuiElement(int eleType, GuiElement &oneElement);

    /*
    * �����������λ�û�ȡ��ǰ����ؼ���Ϣ
    */
    CViewHook::GuiElement* GetGuiElement(CGeoPoint<short> &scrPoint);

    /**
    * ��ս���Ԫ��
    */
    void ClearElements();

    /**
    * �����¼�����������ȡ��Ӧ�������¼�����
    */
    short GetElementType(CGeoPoint<short> &scrPoint);

    /**
    * �����¼�����������ȡ��Ӧ�������¼�����
    */
    short GetElementType(char* elementName);

    /**
    * �����¼�����������ȡ��Ӧ�������¼�����
    */
    const char* GetElementName(short elementType);

    /**
    * ˢ�½���
    */
    void Refresh(short type = VT_Unknown);

    /**
    * ����ָ���ؼ���ʾ����
    */
    bool SetStyle(short elementType, bool focusStyle);

    /**
    * ���ݿؼ���ö��IDֵ�����ÿؼ�����ʾ״̬

    */
    void SetVisible(short elementType, bool visible);

    /**
    * ���������־
    */
    void LogMessage(const char* msg);
    void LogMessageF(const char* format, ...);

  protected:
    /*
    * \�����¼�ö��ID����ȡ�ؼ���Ϣ
    */
    CViewHook::GuiElement* GetGuiElement(const short elementType);

    /*
    * \�����¼���������ȡ�ؼ���Ϣ
    */
    CViewHook::GuiElement* GetGuiElement(const char* elementName);
 
    /**
    * \ֻ���Ҫˢ�µİ�ť�ؼ�����ʱֻ������ƽ׶Σ���û��ʹ�ã�
    */ 
    void ClearRenderElements();

    /**
    * \ֻ���Ҫˢ�µİ�ť�ؼ�����ʱֻ������ƽ׶Σ���û��ʹ�ã�
    */ 
    void AddRenderElements(GuiElement* element);

    void AddRenderUiControls(CUiControl* control);

    

  private:
    /**
    * \����hook�б��л�ȡ��hook
    */ 
    CAggHook* GetChildHook(HookType hookType);
    //�ж��Ƿ��Ǿֲ���Ⱦ
    bool IsPartRefresh(const CGeoRect<short> &scrExtent);

    /**
    * ��ȡ��ǰԪ����Ҫ���н����ɫ��������Ϣ
    * �����ȡ�����򷵻�NULL��֤����Ԫ�ز���Ҫ���н������ֱ�ɫ
    */ 
   const unsigned char* GetFocusText(CViewHook::GuiElement* guielement);
  protected:
    // Steps for dynamically rendering GUI elements of each hook
    int m_dynamics;
    int m_curDynamic;    
    /// ��¼��Ļ������Ϣ
    CGeoRect<short> m_scrExtent;
    /// ��¼ѡ�еĿؼ���Ӧ�¼�����
    short m_downElementType; 
    /// ��¼��갴��ʱ��Ӧ�Ŀؼ���Ϣ
    GuiElement* m_downElement;
    /// ��¼��굯��ʱ��Ӧ�ؼ�λ����Ϣ
    GuiElement* m_upElement;
    /// ��갴��ʱ����hook����
    HookType m_downChildHookType;
    /// ��굯��ʱ����hook����
    HookType m_upChildHookType;
    //�Ƶ�ViewHook�У��þ�̬�ķ�ʽ��
    ///// ��¼�Ƿ�����갴���¼�
    //bool m_isMouseDown;
    ///// ��¼�Ƿ�����굯���¼�
    //bool m_isMouseUp;
    //hook�ļ����·��
    static TCHAR m_hookPath[CPathBasic::MAXPATHLENGTH];
    //��¼�Ƿ���Ҫˢ��,Ĭ��ΪTrue
    bool m_isNeedRefesh;
    //��ǰhook��Ⱦ��ɺ��Ƿ���Ҫ�ͷ���Ⱦʱʹ�õ�ͼƬ��Դ,Ĭ��ΪTrue��Ҫ�ͷ�
    bool m_needReleasePic;
  private: 
    //��ǰhook�Ƿ�����ʾ״̬ ע���ñ�����Ҫ�ǵ�ǰhook��Ϊ����hook����hookʱ���á�
    bool m_isShown;
    //��ǰhook����hook�б�ʹ��map�洢
    AggHookMap m_childHookList;
    /// �µĿؼ���Žṹ
    GuiElements m_guiElements; 
    /// ֻ���Ҫˢ�µİ�ť�ؼ�����ʱֻ������ƽ׶Σ���û��ʹ�ã�
    std::vector<GuiElement*> m_renderElements;
    /// �����ı�
    char m_focusText[MAXELEMENTNAME];
    /// �����Ҫ�����ɫ�Ŀؼ�
    FocusTextElementsMap m_focusTextElements;
    //GUI��־�������
    static CDbgLogger m_guiLogger;
   //��¼���µİ�ť��λ�á�
    static CGeoPoint<short> m_downScrPoint;
   //����Hook�Ķ�ջ
    static std::vector<int> m_hookTypeStack; 
  };

  //�������ֱ�ɫ���װ
  class CFocusTextElement
  {
  public:
    CFocusTextElement();
    CFocusTextElement(CViewHook::GuiElement* focusElement, const unsigned char* fkey);
    virtual ~CFocusTextElement() {}
  public:
    /*
    * ������Ҫ�����ɫ��Ԫ�ؼ���ɫ��Ϣ
    * focusElement ��Ҫ�����ɫ��ԭɫ
    * �����ɫ�ı���λ����Ϣ�б�
    */
    void SetFocusKey(CViewHook::GuiElement* focusElement, const unsigned char* fkey);
    /*
    * ������Ҫ�����ɫ��Ԫ�ؼ���ɫ��Ϣ
    * �����ɫ�ı���λ����Ϣ�б�
    */
    void SetFocusKey(const unsigned char* fkey);
    /*
    * ��ȡ��������λ����Ϣ
    * focusElement ��Ҫ�����ɫ��ԭɫ
    */
    unsigned char* GetFocusKey();
    /*
    * �жϴ����Element�͵�ǰElement�Ƿ���ͬһ��
    * otherElement ����Ҫ��ɫ��Ԫ��
    */
    bool IsSameElement(const CViewHook::GuiElement* otherElement);
  private:
    //�����Ҫʵ�ֽ����ɫ��Ԫ����Ϣ
    CViewHook::GuiElement* m_focusElement;
    //�����Ҫ�����ɫ�����ֵ�λ����Ϣ
    unsigned char m_fTextPosList[CViewHook::MAXELEMENTNAME];

  };
}

#endif