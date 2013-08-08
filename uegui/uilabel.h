/*
*
* Copyright (C) 2012-07-02 By Hejd
* 
*
*/

#ifndef _UEGUI_LABEL_H
#define _UEGUI_LABEL_H

#include "uictrltypes.h"

namespace UeGui
{
  class CUiLabel : public CUiControl
  {
  public:
    CUiLabel() : CUiControl(), m_labelElement(NULL) {}
    virtual ~CUiLabel() {}
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
    void SetLabelElement(GuiElement* labelElement);
    GuiElement* GetLabelElement();
    //���ÿؼ��ĳ���
    void SetWidth(int width);
  protected:
    //��Ⱦ�ؼ�Ԫ��
    virtual void RenderElements();
  private:
    GuiElement* m_labelElement; //��ť�м�ؼ�������Ϣ ��ΪNULL
  };
}

#endif
