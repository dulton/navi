#include "functionupdatehook.h"
using namespace UeGui;

CFunctionUpdateHook::CFunctionUpdateHook()
{
  m_strTitle = "��������";
  m_vecHookFile.push_back(_T("functionupdatehook.bin"));
}

CFunctionUpdateHook::~CFunctionUpdateHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}


void CFunctionUpdateHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_TipText,	"TipText"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_TipText2,	"TipText2"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_TipText3,	"TipText3"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_Text1,	"Text1"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_TextDup1,	"TextDup1"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_Text2,	"Text2"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_Text3,	"Text3"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_Text4,	"Text4"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_Text5,	"Text5"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_ElecEyeUpBtn,	"ElecEyeUpBtn"));
  m_ctrlNames.insert(GuiName::value_type(functionupdatehook_InterestPointUp,	"InterestPointUp"));
}

void CFunctionUpdateHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_elecEyeUpBtnCtrl.SetCenterElement(GetGuiElement(functionupdatehook_ElecEyeUpBtn));
  m_interestPointUpCtrl.SetCenterElement(GetGuiElement(functionupdatehook_InterestPointUp));
  m_text1Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_Text1));
  m_text2Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_Text2));
  m_text3Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_Text3));
  m_text4Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_Text4));
  m_text5Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_Text5));
  m_textDup1Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_TextDup1));
  m_tipTextCtrl.SetCenterElement(GetGuiElement(functionupdatehook_TipText));
  m_tipText2Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_TipText2));
  m_tipText3Ctrl.SetCenterElement(GetGuiElement(functionupdatehook_TipText3));
}

short CFunctionUpdateHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case functionupdatehook_ElecEyeUpBtn:
    {
      m_elecEyeUpBtnCtrl.MouseDown();
      if (!m_elecEyeUpBtnCtrl.IsEnable())
      {
        m_isNeedRefesh = false;
        break;
      }
      AddRenderUiControls(&m_elecEyeUpBtnCtrl);
    }
    break;
  case functionupdatehook_InterestPointUp:
    {
      m_interestPointUpCtrl.MouseDown();
    }
    break;
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

short CFunctionUpdateHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CFunctionUpdateHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case functionupdatehook_ElecEyeUpBtn:
    {
      m_elecEyeUpBtnCtrl.MouseUp();
    }
    break;
  case functionupdatehook_InterestPointUp:
    {
      m_interestPointUpCtrl.MouseUp();
    }
    break;
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

void CFunctionUpdateHook::Load()
{
  m_tipTextCtrl.SetCaption("ϵͳΪ���ṩ��ѵĵ�ͼ�������·����밴���²�����в���:");
  m_tipText2Ctrl.SetCaption("���ڲ�֧���������豸��");
  m_tipText3Ctrl.SetCaption("1.��½www.ritu.cn��վ,ѡ���''����ͨר����''ҳ��,");
  m_text1Ctrl.SetCaption("��''����ͨר����''ҳ����ѡ��''��������''");
  m_textDup1Ctrl.SetCaption("2.��''��������''ҳ����������Ӧ�������ݰ�");
  m_text2Ctrl.SetCaption("3.������ɺ�,�����ݰ��������豸��");
  m_text3Ctrl.SetCaption("4.������Ϻ�,���������ײ�����Ӧ���°�ť");
  m_text4Ctrl.SetCaption("5.������Ϻ�ϵͳ�������ʾ");
  m_elecEyeUpBtnCtrl.SetEnable(false);
}
