/*
*
* Copyright (C) 2012-07-02 By Hejd
* 
*
*/

#ifndef _UEGUI_BITBUTTON_H
#define _UEGUI_BITBUTTON_H

#include "uilabel.h"

namespace UeGui
{
  class CUiButton : public CUiControl
  {
  public:
    CUiButton() : CUiControl(), m_leftElement(NULL), m_rightElement(NULL), m_centerElement(NULL) {}
    virtual ~CUiButton() {}
  public:
    virtual void MouseDown();
    virtual void MouseUp();
    virtual void MouseMove();
    /// ���ÿؼ���ʾ����
    virtual void SetCaption(const char* caption);
    /// ��ȡ�ؼ�����ʾ������
    virtual char* GetCaption();
    /// ��տؼ���ʾ����
    virtual void ClearCaption();
    /// ���ÿؼ��Ƿ����
    virtual void SetEnable(bool value);
    /// ���ÿؼ��Ŀɼ���
    virtual void SetVisible(bool value);
    //������Ҫ��ɫ������λ����Ϣ
    virtual void SetFocusKey(const unsigned char* fkey);
    //�����Ҫ��ɫ������λ����Ϣ
    virtual void ClearFocusKey();
  public:
    void SetLeftElement(GuiElement* leftElement);
    void SetRightElement(GuiElement* rightElement); 
    void SetCenterElement(GuiElement* centerElement);
    GuiElement* GetLeftElement();
    GuiElement* GetRightElement();
    GuiElement* GetCenterElement();
    //���ÿؼ��ĳ���
    void SetWidth(int width);
  private:
    GuiElement* m_leftElement;  //��ť��߿ؼ�������Ϣ ��ΪNULL
    GuiElement* m_rightElement; //��ť�ұ߿ؼ�������Ϣ ��ΪNULL
    GuiElement* m_centerElement;  //��ť�м�ؼ�������Ϣ ��ΪNULL
  };

  /// ��ǰ��ͼƬ�İ�ť ע��һ������û�����ֵ�ͼƬ��ť����Ϊ������CenterElement������Icon���ܻ��ڵ�ס����
  class CUiBitButton : public CUiButton
  {
  public:
    CUiBitButton() : m_labelElement(NULL), m_iconElement(NULL), CUiButton() {}
    virtual ~CUiBitButton() {}
  public:
    virtual void MouseDown();
    virtual void MouseUp();
    virtual void MouseMove();
    /// ���ÿؼ���ʾ����
    virtual void SetCaption(const char* caption);
    /// ��ȡ�ؼ�����ʾ������
    virtual char* GetCaption();
    /// ��տؼ���ʾ����
    virtual void ClearCaption();
    /// ���ÿؼ��Ƿ����
    virtual void SetEnable(bool value);
    /// ���ÿؼ��Ŀɼ���
    virtual void SetVisible(bool value);
  public:
    void SetLabelElement(GuiElement* labelElement);
    void SetIconElement(GuiElement* iconElement);
    GuiElement* GetLabelElement();
    GuiElement* GetIconElement();
  protected:    
    GuiElement* m_labelElement; //��ť�м�ؼ�������Ϣ ��ΪNULL
    GuiElement* m_iconElement;  //��ť����ͼ��ؼ�������Ϣ ��ΪNULL
  };
}

#endif
