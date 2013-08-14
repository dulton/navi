#ifndef _UEGUI_PRODUCEACTIVATION_H
#define _UEGUI_PRODUCEACTIVATION_H

#ifndef _UEGUI_AGGHOOK_H
#include "agghook.h"
#endif

#include "uibutton.h"

namespace UeGui
{
  
  class UEGUI_CLASS CProduceActivationHook : public CAggHook
  {
  public:
    const static unsigned short MAX_NUM_LEN = 16;  
    const static unsigned short PART_LENT = 4; 

    enum ProduceActivationCtrlType
    {
      ProduceActivation_Begin = 0,
      ProduceActivation_Background,
      ProduceActivation_Title,
      ProduceActivation_Cancel,
      ProduceActivation_Cancel_qu,
      ProduceActivation_Cancel_xiao,
      ProduceActivation_VersionLabel,
      ProduceActivation_VersionCode,
      ProduceActivation_SeriesNumberLabel,
      ProduceActivation_SeriesNumberPart1,
      ProduceActivation_SeriesNumberPart2,
      ProduceActivation_SeriesNumberPart3,
      ProduceActivation_SeriesNumberPart4,
      ProduceActivation_ActivationCodeLabel,
      ProduceActivation_ActivationCodePart1,
      ProduceActivation_ActivationCodePart2,
      ProduceActivation_ActivationCodePart3,
      ProduceActivation_ActivationCodePart4,
      ProduceActivation_InputCode1,
      ProduceActivation_InputCode2,
      ProduceActivation_InputCode3,
      ProduceActivation_InputCode4,
      ProduceActivation_InputCode5,
      ProduceActivation_InputCode6,
      ProduceActivation_InputCode7,
      ProduceActivation_InputCode8,
      ProduceActivation_InputCode9,
      ProduceActivation_InputCode10,
      ProduceActivation_InputCode11,
      ProduceActivation_InputCode12,
      ProduceActivation_InputCode13,
      ProduceActivation_InputCode14,
      ProduceActivation_InputCode15,
      ProduceActivation_InputCode16,
      ProduceActivation_DeleteChar,
      ProduceActivation_Activation,
      ProduceActivation_Activation_an,
      ProduceActivation_Activation_zhuang,
      ProduceActivation_End
    };

    enum SectionPart{
      kPart1,
      kPart2,
      kPart3,
      kPart4
    };
  public:
    CProduceActivationHook();

    virtual ~CProduceActivationHook();

    virtual void MakeGUI();

    virtual short MouseDown(CGeoPoint<short> &scrPoint);

    virtual short MouseMove(CGeoPoint<short> &scrPoint);

    virtual short MouseUp(CGeoPoint<short> &scrPoint);

    virtual bool operator ()();

    virtual void Init();
  public:
    //�˳�ϵͳ
    void Close();
    //�˳�ϵͳ�¼�
    static void OnClose(CAggHook* sender, ModalResultType modalResult);
    //ϵͳ�����
    void ActivateProduct();
    //ϵͳ�����¼�
    static void OnActivateProduct(CAggHook* sender, ModalResultType modalResult);
  protected:
    virtual tstring GetBinaryFileName();

    virtual void MakeNames();

    void MakeControls();
  private:
    //����ַ�
    void DoAddChar(char addChar);
    //ɾ���ַ�
    void DoDeleteChar();

    //���һ���ַ������к�
    void AddSeriesNum(char addChar);
    //ɾ�����к����һ���ַ�
    void DeleteSeriesNum();
    //��ʾ���к�
    void ShowSeries(const char* series, unsigned short seriesLen);
    void ShowSeriesPart(unsigned int partID, char* partData);
    //������к�
    void ClearSeries();

    //���һ���ַ���������
    void AddActivationCode(char addChar);
    //ɾ�����������һ���ַ�
    void DeleteActivationCode();
    //��ʾ������
    void ShowActivationCode(const char* code, unsigned short codeLen);
    void ShowActivationCodePart(unsigned int partID, char* partData);
    //��ռ�����
    void ClearActivationCode();
    //�ر�ϵͳ
    void DoClose();
    //����
    void DoActivation();
    //��Ϣ�Ի���
    void ShowMessageDialog(MessageBoxType type, const char* caption);
  private:
    //�汾��
    CUiButton m_versionCodeCtrl;
    //���к�    
    CUiButton m_seriesNumberPart1Ctrl;
    CUiButton m_seriesNumberPart2Ctrl;
    CUiButton m_seriesNumberPart3Ctrl;
    CUiButton m_seriesNumberPart4Ctrl;
    //������
    CUiButton m_activationCodePart1Ctrl;
    CUiButton m_activationCodePart2Ctrl;
    CUiButton m_activationCodePart3Ctrl;
    CUiButton m_activationCodePart4Ctrl;
    //ȡ��
    CUiButton m_cancelCtrl;
    //ɾ������
    CUiButton m_deleteCharCtrl;
    //���̴���
    CUiButton m_inputCode1Ctrl;
    CUiButton m_inputCode2Ctrl;
    CUiButton m_inputCode3Ctrl;
    CUiButton m_inputCode4Ctrl;
    CUiButton m_inputCode5Ctrl;
    CUiButton m_inputCode6Ctrl;
    CUiButton m_inputCode7Ctrl;
    CUiButton m_inputCode8Ctrl;
    CUiButton m_inputCode9Ctrl;
    CUiButton m_inputCode10Ctrl;
    CUiButton m_inputCode11Ctrl;
    CUiButton m_inputCode12Ctrl;
    CUiButton m_inputCode13Ctrl;
    CUiButton m_inputCode14Ctrl;
    CUiButton m_inputCode15Ctrl;
    CUiButton m_inputCode16Ctrl;
    //����
    CUiButton m_activationCtrl;

    //���к�
    unsigned char m_seriesNum_Len;
    char m_seriesNum[MAX_NUM_LEN + 1];
    //������
    unsigned char m_activationCode_Len;
    char m_activationCode[MAX_NUM_LEN + 1];
  };
}
#endif
