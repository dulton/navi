#include "updateservicehook.h"
using namespace UeGui;

CUpdateServiceHook::CUpdateServiceHook()
{
  m_strTitle = "��������";
  m_vecHookFile.push_back(_T("updateservicehook.bin"));
}

CUpdateServiceHook::~CUpdateServiceHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}


void CUpdateServiceHook::MakeNames()
{
  CMenuBackgroundHook::MakeNames();
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_TipText,	"TipText"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_TipText2,	"TipText2"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_TipText3,	"TipText3"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_Text1,	"Text1"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_TextDup1,	"TextDup1"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_Text2,	"Text2"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_Text3,	"Text3"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_Text4,	"Text4"));
  m_ctrlNames.insert(GuiName::value_type(updateservicehook_ServicePointBtn,	"ServicePointBtn"));
}

void CUpdateServiceHook::MakeControls()
{
  CMenuBackgroundHook::MakeControls();
  m_servicePointBtnCtrl.SetCenterElement(GetGuiElement(updateservicehook_ServicePointBtn));
  m_text1Ctrl.SetCenterElement(GetGuiElement(updateservicehook_Text1));
  m_text2Ctrl.SetCenterElement(GetGuiElement(updateservicehook_Text2));
  m_text3Ctrl.SetCenterElement(GetGuiElement(updateservicehook_Text3));
  m_text4Ctrl.SetCenterElement(GetGuiElement(updateservicehook_Text4));
  m_textDup1Ctrl.SetCenterElement(GetGuiElement(updateservicehook_TextDup1));
  m_tipTextCtrl.SetCenterElement(GetGuiElement(updateservicehook_TipText));
  m_tipText2Ctrl.SetCenterElement(GetGuiElement(updateservicehook_TipText2));
  m_tipText3Ctrl.SetCenterElement(GetGuiElement(updateservicehook_TipText3));
}

short CUpdateServiceHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseDown(scrPoint);
  switch(ctrlType)
  {
  case updateservicehook_ServicePointBtn:
    {
      m_servicePointBtnCtrl.MouseDown();
      AddRenderUiControls(&m_servicePointBtnCtrl);
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

short CUpdateServiceHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CUpdateServiceHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short ctrlType = CAggHook::MouseUp(scrPoint);
  switch(m_downElementType)
  {
  case updateservicehook_ServicePointBtn:
    {
      m_servicePointBtnCtrl.MouseUp();
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
void CUpdateServiceHook::Load()
{
  m_tipTextCtrl.SetCaption("���Ҫ��ȡ��������,����ҪЯ������ͨ�����ͼ���濨�����ͨ��");
  m_tipText2Ctrl.SetCaption("���ͼ�豸��ָ�����������������������(����˽����е�''����");
  m_tipText3Ctrl.SetCaption("����''��ť���¼����ͨ�Ĺٷ���վ��");
  m_text1Ctrl.SetCaption("http://www.ritu.cn/index.aspx,�����ҳ���½ǵ�''��ͼ����''��");
  m_textDup1Ctrl.SetCaption("���Բ�ѯ����ͨ����������Ϣ)��");
  m_text2Ctrl.SetCaption("�����û�ÿ�������2����������,���������ʱ���벦��ͷ��绰");
  m_text3Ctrl.SetCaption("��ѯ:400-8898-123��");
  m_text4Ctrl.SetCaption("�����Ҫ�˽��������������Ϣ,�ɲ���ͷ��绰��ѯ");
  m_servicePointBtnCtrl.SetEnable(false);
}

