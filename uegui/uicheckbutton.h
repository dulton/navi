/*
*
* Copyright (C) 2012-07-02 By Hejd
* 
*
*/

#ifndef _UEGUI_CHECKTBUTTON_H
#define _UEGUI_CHECKTBUTTON_H

#include "uibutton.h"

namespace UeGui
{
  class CUiCheckButton : public CUiBitButton
  {
  public:
    CUiCheckButton() : CUiBitButton(), m_checked(false) {}
    virtual ~CUiCheckButton() {}        
  public:
    virtual void MouseDown();
    virtual void MouseUp();
    virtual void MouseMove();
    /// ���ÿؼ��Ƿ����
    virtual void SetEnable(bool value);
    /// ���ÿؼ��Ŀɼ���
    virtual void SetVisible(bool value);
  public:
    void SetCheck(bool value);
    bool Checked();
  protected:
    //��Ⱦ�ؼ�Ԫ��
    virtual void RenderElements();
  private:
    //ִ��ѡ����
    void DoCheck(bool value);
  private:
    bool m_checked;
  };
}

#endif
