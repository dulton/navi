/*
*
* Copyright (C) 2012-06-20 By Hejd
* licensehook_new.h
*
*/

#ifndef _UEGUI_CTRLTYPES_H
#define _UEGUI_CTRLTYPES_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEMAP_VIEWHOOK_H
#include "uemap\viewhook.h"
#endif
#include "agghook.h"

using namespace UeMap;

namespace UeGui
{
  typedef CViewHook::GuiElement GuiElement;

  //���ؼ�����
  class CUiControl
  {
  protected:
    CUiControl() : m_parent(NULL), m_isEnable(true), m_isVisible(true), m_haveFocusKey(false) {}
  public:           
    virtual ~CUiControl() {}        
  public:
    /// ���ÿؼ�����
    virtual void SetParent(CAggHook* parent)
    {
      m_parent = parent;
    }
    /// ���down�¼�
    virtual void MouseDown() = 0;
    /// ���up�¼�
    virtual void MouseUp() = 0;
    /// ���mouve�¼�4
    virtual void MouseMove() = 0;
    /// ���ÿؼ���ʾ����
    virtual void SetCaption(const char* caption) = 0;
    /// ��տؼ���ʾ����
    virtual void ClearCaption() = 0;
    /// ��ȡ�ؼ�����ʾ������
    virtual char* GetCaption() = 0;
    /// ���ÿؼ��Ƿ����
    virtual void SetEnable(bool value)
    {
      m_isEnable = value;
    }
    /// ���ÿؼ��Ŀɼ���
    virtual void SetVisible(bool value)
    {
      m_isVisible = value;
    }
    /// ���ؿؼ��Ƿ���Ч
    inline bool IsEnable()
    {
      return m_isEnable;
    }
    /// ���ؿؼ��Ƿ�ɼ�
    inline bool IsVisible()
    {
      return m_isVisible;
    }
    //������Ҫ��ɫ������λ����Ϣ
    virtual void SetFocusKey(const unsigned char* fkey) = 0;
    //�����Ҫ��ɫ������λ����Ϣ
    virtual void ClearFocusKey() = 0;
  protected:
    //�ؼ���Ӧ�ĸ���
    CAggHook* m_parent;
    //�Ƿ���Ҫ������ʵ�н����ɫ
    bool m_haveFocusKey;
  private:
    //�Ƿ����
    bool m_isEnable;
    //�Ƿ�ɼ�
    bool m_isVisible;
  };
}
#endif