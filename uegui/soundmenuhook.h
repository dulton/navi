#ifndef _UEGUI_SOUNDMENUHOOK_H
#define _UEGUI_SOUNDMENUHOOK_H

#ifndef _UEGUI_BASE_H
#include "uegui.h"
#endif

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uilabel.h"
#include "uibutton.h"
#include "uiradiobutton.h"
#include "uicheckbutton.h"
#include "settingwrapper.h"

namespace UeGui
{
  class UEGUI_CLASS CSoundMenuHook : public CAggHook
  {
  public:    
    enum SoundMenuHookCtrlType
    {
      SoundMenuHook_Begin = 0,
      SoundMenuHook_Background,
      SoundMenuHook_SoundBack,
      SoundMenuHook_Title,
      SoundMenuHook_SoundBarBack,
      SoundMenuHook_SoundBarProgress,
      SoundMenuHook_SoundBtn,
      SoundMenuHook_SoundMin,
      SoundMenuHook_SoundMax,
      SoundMenuHook_SoundMute,
      SoundMenuHook_SoundMuteLabel,
      SoundMenuHook_PromptLabel,
      SoundMenuHook_Concision,
      SoundMenuHook_ConsisionLabel,
      SoundMenuHook_General,
      SoundMenuHook_GeneralLabel,
      SoundMenuHook_Detail,
      SoundMenuHook_DetailLabel,
      SoundMenuHook_End
    };
    enum RadioButtonIndex
    {
      RB_Consion,  //���
      RB_General,  //һ��
      RB_Detail,   //��ϸ
    };
    CSoundMenuHook();

    virtual ~CSoundMenuHook();

    /**
    * \brief ��ʾ����֮ǰ������׼��
    */
    virtual void Load();

    /**
    * \brief �л�����ʱ�ͷ�����
    **/
    virtual void UnLoad();

    /**
    * ��ʱ��
    **/
    virtual void Timer();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    /**
    * \brief �رմ���
    */
    void DoClose();
    /**
    * \brief ����������С
    * param: bIncrease True(����) False(����)
    */
    void ChangeVolume(bool bIncrease);
    /**
    * \brief ��������ѡ��
    */
    void ClickOnSoundBar(CGeoPoint<short> &scrPoint);
    /**
    * \brief ������ʾѡ��
    */
    void BroadcastRadioCheck(RadioButtonIndex index);
    /**
    * \brief �����������Ŀ��������������
    */
    void SetSoundBar(unsigned short barWidth);
    /**
    * \brief ��������ֵ�Ĵ�С������������
    * \param volume:��С��Χ:0..100
    */
    void SetVolume(unsigned short volume);
    /**
    * \brief ���þ���
    */
    void SetMute();
    /**
    * \brief �������õ��ļ���
    */
    void SaveSoundSetting();
    /**
    * \brief �����������Ŀ������������ֵ
    */
    unsigned short GetVoume(unsigned short barWidth);
    /**
    * \brief ���¿�ʼ�����л���ʱ��
    */
    void RestarTimer();
    /**
    * \brief �رս����л���ʱ��
    */
    void CloseTimer();
    /**
    * \brief �ֲ�ˢ��
    */
    void PartRefresh();
  private:
    //��Ϣ�򱳾�
    CUiButton m_soundBack;
    //�����Ӵ�
    CUiButton m_soundMaxBtn;
    //������С
    CUiButton m_soundMinBtn;
    //�������ڰ�ť
    CUiButton m_soundBtn;
    //����������
    CUiButton m_soundBarBack;
    //������
    CUiButton m_soundBarProgress;
    //����
    CUiCheckButton m_soundMuteBtn;
    //���
    CUiRadioButton m_concisionBtn;
    //һ��
    CUiRadioButton m_generalBtn;
    //��ϸ
    CUiRadioButton m_detailBtn;
  private:
    //���ö���ӿ�
    CSettingWrapper& m_settingWrapper;
    //����������󳤶�
    short m_maxSoundBarWidth;
    //��ǰ�������ĳ���
    short m_curSoundBarWidth;
    //�����л���ʱ���
    short m_timerInterval;
  };
}
#endif
