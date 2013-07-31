#include "voicesettinghook.h"
#include "uebase\customerfilereader.h"
#include "guisetting.h"
#include "ueroute\routebasic.h"
#include "ueroute\ueguider.h"
#include "maphook.h"

using namespace UeGui;

CVoiceSettingHook::CVoiceSettingHook()
{
  MakeGUI();
}

CVoiceSettingHook::~CVoiceSettingHook()
{
  m_elements.clear();
  m_ctrlNames.clear();
  m_imageNames.clear();
}

void CVoiceSettingHook::MakeGUI()
{ 
  FetchWithBinary();
  MakeNames();
  MakeControls();

  Set_VDialect();

  //��ʼ��ϵͳ����
  CGuiSettings* setting= CGuiSettings::GetGuiSettings();
  if (setting->IsLoudSpeakerMute())
  {
    setting->SetVoice(0);
  }
  else
  {
    unsigned int voice = setting->GetVoice();
    setting->SetVoice(voice);
  }
}

//void CVoiceSettingHook::Load()
//{
//  //��ȡϵͳ����  
//  CGuiSettings* setting= CGuiSettings::GetGuiSettings();
//  if (setting->IsLoudSpeakerMute())
//  {
//    m_silenceBtn.SetCheck(true);
//    SetVolumeBar(0);
//  }
//  else
//  {
//    m_silenceBtn.SetCheck(false);        
//    SetVolumeBar(setting->GetVoice());
//  }
//
//  //��������
//  m_initDialectType = (DialectType)setting->GetLanguage();
//  m_route->GetGuider()->SetRole((UETTS_Role)m_initDialectType);
//  m_dialectCtrl.SetCaption(m_dialectMap[m_initDialectType].c_str());
//
//  //���ð�����
//  unsigned char value = setting->GetVoicePrompt();
//  if((value & SystemSettings::VT_KeyVoice) > 0)
//  {
//    m_keytoneCheckBtn.SetCheck(true);
//    m_isKeytoneCheck = true;
//  } 
//  else
//  {
//    m_keytoneCheckBtn.SetCheck(false);
//    m_isKeytoneCheck = false;
//  }
//
//  //���ö�̬��
//  if ((value & SystemSettings::VT_DynamicVoice) > 0)
//  {
//    m_dynamicVolumeCheckBtn.SetCheck(true);
//    m_isDynamicVolumeCheck = true;
//  } 
//  else
//  {
//    m_dynamicVolumeCheckBtn.SetCheck(false);
//    m_isDynamicVolumeCheck = false;
//  }
//
//  //�ж��Ƿ���
//  if (setting->IsLoudSpeakerMute())
//  {
//    m_silenceBtn.SetCheck(true);
//    SetControls(false);//�ؼ�������
//  }
//  else
//  {
//    m_silenceBtn.SetCheck(false);
//    SetControls(true);
//  }
//}
tstring CVoiceSettingHook::GetBinaryFileName()
{
  return _T("voicesettinghook.bin");
}

void CVoiceSettingHook::MakeNames()
{
  m_ctrlNames.erase(m_ctrlNames.begin(), m_ctrlNames.end());
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_Voicelabel,	"VoiceLabel"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_DynamicVoiceBtn,	"DynamicVoiceBtn"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_DynamicVoiceIcon,	"DynamicVoiceIcon"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_DynamicVoiceLabel,	"DynamicVoiceLabel"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_TestListenBtn,	"TestListenBtn"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_VoiceLeftBtn,	"VoiceLeftBtn"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_VoiceLeftIcon,	"VoiceLeftIcon"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_VoiceCenterBtn,	"VoiceCenterBtn"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_VoiceRightBtn,	"VoiceRightBtn"));
  m_ctrlNames.insert(GuiName::value_type(VoiceSettingHook_VoiceRightIcon,	"VoiceRightIcon"));
}

void CVoiceSettingHook::MakeControls()
{
  m_voiceLabelCtrl.SetLabelElement(GetGuiElement(VoiceSettingHook_Voicelabel));
  m_dynamicVoiceLabelCtrl.SetLabelElement(GetGuiElement(VoiceSettingHook_DynamicVoiceLabel));
  m_dynamicVoiceCtrl.SetCenterElement(GetGuiElement(VoiceSettingHook_DynamicVoiceBtn));
  m_dynamicVoiceCtrl.SetIconElement(GetGuiElement(VoiceSettingHook_DynamicVoiceIcon));
  m_testListenCtrl.SetCenterElement(GetGuiElement(VoiceSettingHook_TestListenBtn));
  m_voiceLeftCtrl.SetCenterElement(GetGuiElement(VoiceSettingHook_VoiceLeftBtn));
  m_voiceLeftCtrl.SetIconElement(GetGuiElement(VoiceSettingHook_VoiceLeftIcon));
  m_voiceRightCtrl.SetCenterElement(GetGuiElement(VoiceSettingHook_VoiceRightBtn));
  m_voiceRightCtrl.SetIconElement(GetGuiElement(VoiceSettingHook_VoiceRightIcon));
  m_voiceCenterCtrl.SetCenterElement(GetGuiElement(VoiceSettingHook_VoiceCenterBtn));
}

CVoiceSettingHook::DialectType& operator++ (CVoiceSettingHook::DialectType& dt)
{
  return dt = ((dt == CVoiceSettingHook::DialectTaiWan) ? dt: CVoiceSettingHook::DialectType(dt+1));
}


CVoiceSettingHook::DialectType operator++ (CVoiceSettingHook::DialectType& dt,int)
{
  CVoiceSettingHook::DialectType type = dt;
  ++dt;
  return type;
}

CVoiceSettingHook::DialectType& operator-- (CVoiceSettingHook::DialectType& dt)
{
  return dt = ((dt == CVoiceSettingHook::DialectMandarinWoman) ? dt: CVoiceSettingHook::DialectType(dt-1));
}

CVoiceSettingHook::DialectType operator-- (CVoiceSettingHook::DialectType& dt,int)
{
  CVoiceSettingHook::DialectType type = dt;
  --dt;
  return type;
}

short CVoiceSettingHook::MouseDown(CGeoPoint<short> &scrPoint)
{
  short downElementType = CAggHook::MouseDown(scrPoint);
  switch(downElementType)
  {
  case VoiceSettingHook_DynamicVoiceBtn:
  case VoiceSettingHook_DynamicVoiceIcon:
  case VoiceSettingHook_DynamicVoiceLabel:
    {
      m_dynamicVoiceCtrl.MouseDown();
      m_dynamicVoiceLabelCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_VoiceLeftBtn:
  case VoiceSettingHook_VoiceLeftIcon:
    {
      m_voiceLeftCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_VoiceRightBtn:
  case VoiceSettingHook_VoiceRightIcon:
    {
      m_voiceRightCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_TestListenBtn:
    {
      m_testListenCtrl.MouseDown();
    }
    break;
  default:
    {
      m_isNeedRefesh = false;
      assert(false);
    }
    break;
  }
  if (m_isNeedRefesh)
  {
    this->Refresh();
  }
  m_isNeedRefesh = true;
  return downElementType;
}

short CVoiceSettingHook::MouseMove(CGeoPoint<short> &scrPoint)
{
  return -1;
}

short CVoiceSettingHook::MouseUp(CGeoPoint<short> &scrPoint)
{
  short upElementType = CAggHook::MouseUp(scrPoint);
  CGuiSettings* setting = CGuiSettings::GetGuiSettings();
  //bool canSet = (upElementType == m_downElementType) && (!m_silenceBtn.Checked());

  switch(upElementType)
  {
  case VoiceSettingHook_DynamicVoiceBtn:
  case VoiceSettingHook_DynamicVoiceIcon:
  case VoiceSettingHook_DynamicVoiceLabel:
    {
      m_dynamicVoiceCtrl.MouseDown();
      m_dynamicVoiceLabelCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_VoiceLeftBtn:
  case VoiceSettingHook_VoiceLeftIcon:
    {
      m_voiceLeftCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_VoiceRightBtn:
  case VoiceSettingHook_VoiceRightIcon:
    {
      m_voiceRightCtrl.MouseDown();
    }
    break;
  case VoiceSettingHook_TestListenBtn:
    {
      m_testListenCtrl.MouseDown();
    }
    break;
  default:
    {
      m_isNeedRefesh = false;
      assert(false);
    }
    break;
  }
  if (m_isNeedRefesh)
  {
    Refresh();
  }
  m_isNeedRefesh = true;
  return upElementType;
}

bool CVoiceSettingHook::operator ()()
{
  return false;
}

void CVoiceSettingHook::Set_VDialect()
{
  m_dialectMap.clear();
  m_dialectMap.insert(DialectMap::value_type(DialectMandarinWoman,"��ͨ��-Ů"));
  m_dialectMap.insert(DialectMap::value_type(DialectMandarinMan,"��ͨ��-��"));
  m_dialectMap.insert(DialectMap::value_type(DialectSiChuan,"�Ĵ���"));
  m_dialectMap.insert(DialectMap::value_type(DialectGuangDong,"�㶫��"));
  m_dialectMap.insert(DialectMap::value_type(DialectDongBei,"������"));
  m_dialectMap.insert(DialectMap::value_type(DialectTaiWan,"̨�廰"));
}

void CVoiceSettingHook::SaveSetting()
{
  //CGuiSettings* settingIO= CGuiSettings::GetGuiSettings();
  //if(settingIO) {
  //  CMapHook* mapHook = dynamic_cast<CMapHook*>(m_view->GetHook(DHT_MapHook));
  //  //���þ���
  //  if(m_silenceBtn.Checked()) 
  //  {
  //    settingIO->SetIsLoudSpeakerMute(true);  //����
  //    mapHook->SetSlience(true);
  //  }
  //  else
  //  {
  //    settingIO->SetIsLoudSpeakerMute(false);  //�Ǿ���
  //    mapHook->SetSlience(false);
  //  }

  //  //���ð������Ͷ�̬��
  //  unsigned char value = 0;
  //  if (m_keytoneCheckBtn.Checked())
  //  {
  //    value |= SystemSettings::VT_KeyVoice;
  //  }
  //  if (m_dynamicVolumeCheckBtn.Checked())
  //  {
  //    value |= SystemSettings::VT_DynamicVoice;
  //  }
  //  settingIO->SetVoicePrompt(value);

  //  //��������
  //  settingIO->SetLanguage(m_initDialectType);
  //  m_route->GetGuider()->SetRole((UETTS_Role)m_initDialectType);

  //  settingIO->SaveAllSettings();
  //}
}

void CVoiceSettingHook::PlaySounds() 
{
  UeRoute::UeSound snd;
  snd.m_priority = 0;
  //snd.Add(UeRoute::IVT_ReRoute);
  snd.Add("��ӭʹ�õ���ͨ����ϵͳ", ::strlen("��ӭʹ�õ���ͨ����ϵͳ"),  IVT_TTS);
  m_route->GetGuider()->PlayVoice(snd);
}

void UeGui::CVoiceSettingHook::SetVolumeBar( int soundSize )
{
  for (int i = 1; i <= SoundMaxVolume; i++)
  {
    if (i <= soundSize)
    {
      ChangeVolumeBarStatus(i, true);
    }
    else
    {
      ChangeVolumeBarStatus(i, false);
    }
  }
}

void UeGui::CVoiceSettingHook::ChangeVolumeBarStatus( unsigned short id, bool status )
{
  /*switch (id)
  {
  case 1 :
    {
      m_volume1Ctrl.SetEnable(status);
      break;
    }
  case 2 :
    {
      m_volume2Ctrl.SetEnable(status);
      break;
    }
  case 3 :
    {
      m_volume3Ctrl.SetEnable(status);
      break;
    }
  case 4 :
    {
      m_volume4Ctrl.SetEnable(status);
      break;
    }
  case 5 :
    {
      m_volume5Ctrl.SetEnable(status);
      break;
    }
  case 6 :
    {
      m_volume6Ctrl.SetEnable(status);
      break;
    }
  case 7 :
    {
      m_volume7Ctrl.SetEnable(status);
      break;
    }
  default:
    {
      break;
    }
  }*/
}

void UeGui::CVoiceSettingHook::SaveSoundSetting( int soundSize, bool isLoudSpeakerMute )
{
  CGuiSettings* setting = CGuiSettings::GetGuiSettings();
  if (setting->IsLoudSpeakerMute() | isLoudSpeakerMute)
  {
    m_changeSetting = true;
    setting->SetIsLoudSpeakerMute(isLoudSpeakerMute);    
  }

  if (!isLoudSpeakerMute)
  {
    if (setting->GetVoice() != soundSize)
    {
      m_changeSetting = true;
      setting->SetVoice(soundSize);
    }    
  }
}

void UeGui::CVoiceSettingHook::SetControls( bool isEnable )
{
  /*m_volumeIconCtrl.SetEnable(isEnable);
  m_keytoneBtn.SetEnable(isEnable);
  m_keytoneCheckBtn.SetEnable(isEnable);
  m_dynamicVolumeBtn.SetEnable(isEnable);
  m_dynamicVolumeCheckBtn.SetEnable(isEnable);
  m_auditionCtrl.SetEnable(isEnable);
  m_dialectCtrl.SetEnable(isEnable);
  m_dialectCtrlLeft.SetEnable(isEnable);
  m_dialectCtrlRight.SetEnable(isEnable);

  if (m_initDialectType == DialectMandarinWoman)
  {
    m_dialectCtrlLeft.SetEnable(false);
  } 
  if (m_initDialectType == DialectTaiWan)
  {
    m_dialectCtrlRight.SetEnable(false);
  }*/
}
