#include "versioncheckhook.h"
using namespace UeGui;

CVersionCheckHook::CVersionCheckHook()
{
  m_strTitle = "������֤";
  m_vecHookFile.push_back(_T("versioncheckhook.bin"));
}

CVersionCheckHook::~CVersionCheckHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}


void CVersionCheckHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_TipText,	"TipText"));
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_TipText3,	"TipText3"));
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_Text1,	"Text1"));
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_TextDup1,	"TextDup1"));
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_Text2,	"Text2"));
  m_ctrlNames.insert(GuiName::value_type(versioncheckhook_Text3,	"Text3"));
}

void CVersionCheckHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_text1Ctrl.SetCenterElement(GetGuiElement(versioncheckhook_Text1));
  m_text2Ctrl.SetCenterElement(GetGuiElement(versioncheckhook_Text2));
  m_text3Ctrl.SetCenterElement(GetGuiElement(versioncheckhook_Text3));
  m_textDup1Ctrl.SetCenterElement(GetGuiElement(versioncheckhook_TextDup1));
  m_tipTextCtrl.SetCenterElement(GetGuiElement(versioncheckhook_TipText));
  m_tipText3Ctrl.SetCenterElement(GetGuiElement(versioncheckhook_TipText3));
}

short CVersionCheckHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  default:
    return CMenuBackgroundHook::MouseDown(scrPoint);
    break;
  }

  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}

short CVersionCheckHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CVersionCheckHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  default:
    return CMenuBackgroundHook::MouseUp(scrPoint);
    break;
  }

  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return ctrlType;
}
void CVersionCheckHook::Load()
{
  m_tipTextCtrl.SetCaption("������֤����:");
  m_tipText3Ctrl.SetCaption("�ڵ����ϴ���ҳ�����,��¼http://www.ritu.cn/��վ");
  m_text1Ctrl.SetCaption("����վ��,���''����ͨר����''����");
  m_textDup1Ctrl.SetCaption("��''����ͨר����''ҳ���,�ڿͻ����񲿷ֵ��''������֤''����");
  m_text2Ctrl.SetCaption("��''������֤''ҳ���,����ʾ�����������������֤");
}


