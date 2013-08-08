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
    CUiControl() : m_parent(NULL), m_isEnable(true), m_isVisible(true), m_haveFocusKey(false), m_atoRefresh(false) {}
  public:           
    virtual ~CUiControl() {}        
  public:
    /// ���ÿؼ�����
    virtual void SetParent(CAggHook* parent)
    {
      m_parent = parent;
    }
    /// ���down�¼�
    virtual void MouseDown()
    {
      if (m_atoRefresh)
      {
        if (IsVisible() || IsEnable())
        {
          RenderElements();
        }   
      }   
    }
    /// ���up�¼�
    virtual void MouseUp()
    {
      if (m_atoRefresh)
      {
        if (IsVisible() || IsEnable())
        {
          RenderElements();
        }   
      }      
    }
    /// ���mouve�¼�4
    virtual void MouseMove() = 0;
    /// ���ÿؼ���ʾ����
    virtual void SetCaption(const char* caption)
    {
      if (m_atoRefresh && caption)
      {
        RenderElements();
      }
    }
    /// ��տؼ���ʾ����
    virtual void ClearCaption()
    {
      //RenderElements();
    }
    /// ��ȡ�ؼ�����ʾ������
    virtual char* GetCaption() = 0;
    /// ���ÿؼ��Ƿ����
    virtual void SetEnable(bool value)
    {
      m_isEnable = value;
      //RenderElements();
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
    virtual void SetFocusKey(const unsigned char* fkey)
    {
      m_haveFocusKey = true;
    }
    //�����Ҫ��ɫ������λ����Ϣ
    virtual void ClearFocusKey()
    {
      m_haveFocusKey = false;
    }
    //ˢ��
    virtual void Refresh()
    {
      RenderElements();
    }
    //�����Ƿ��Զ�ʵ�־ֲ�ˢ�¶���
    void SetAutoRefresh(bool value)
    {
      m_atoRefresh = value;
    }
  protected:
    //��Ⱦ�ؼ�Ԫ��
    virtual void RenderElements() = 0;
    //���Ҫ��Ⱦ�Ŀؼ�Ԫ��
    void AddRenderElement(GuiElement* element)
    {
      if (m_parent && element)
      {
        m_parent->AddRenderElements(element);
      }
    }
  protected:
    //�ؼ���Ӧ�ĸ���
    CAggHook* m_parent;
    //�Ƿ���Ҫ������ʵ�н����ɫ
    bool m_haveFocusKey;
    //�Ƿ�ʵ���Զ�ˢ��
    bool m_atoRefresh;
  private:
    //�Ƿ����
    bool m_isEnable;
    //�Ƿ�ɼ�
    bool m_isVisible;
  };
}
#endif